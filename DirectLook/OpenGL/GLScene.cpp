#include "GLScene.h"

namespace DirectLook 
{
	
#pragma region Constructors
	GLScene::GLScene( const unsigned short nearThreshold, const unsigned short farThreshold, const unsigned int cameraWidth, const unsigned int cameraHeight, const unsigned int depthWidth, const unsigned int depthHeight, Shader* pShader, GLCamera* pCamera )
		:
		m_pCameraTexture( 0 ),
		m_pDepthTexture( 0 ),
		m_pBackgroundTexture( 0 ),
		m_pHeightMap( new GLSegmentedDepthImage( depthWidth, depthHeight, nearThreshold, farThreshold, false, true, 255.0f ) ),
		m_CameraWidth( cameraWidth ),
		m_CameraHeight( cameraHeight ),
		m_DepthWidth( depthWidth ),
		m_DepthHeight( depthHeight ),
		m_pRenderTarget( 0 ),
		m_SimpleTexture( m_CameraWidth, m_CameraHeight ),
		m_TextureMode( true ),
		m_Background( true )
		
	{
		m_IsInitialized = false;
		setShader( pShader );
		setCamera( pCamera );
		initialize();
	}

	GLScene::~GLScene(void)
	{
		//GLMesh::~GLMesh(); //done automatically
	}
#pragma endregion
	
#pragma region GLScene::updateData
	void GLScene::updateData( const void* pImagePixels, const unsigned short* pDepthPixels )
	{
		// Update camera texture object
		m_pCameraTexture->updateTexture( pImagePixels );	

		// smooth the depthmap and fill holes in it
		const unsigned short* pSmoothPixels = SmoothFilter(pDepthPixels);
		m_pHeightMap->updateImage( pSmoothPixels );

		if(pSmoothPixels)	{ delete[] pSmoothPixels; pSmoothPixels = 0; }		
				
		// Update depth texture object
		m_pDepthTexture->updateTexture( m_pHeightMap->getTextureHeightMap() );

		// Update vertex buffer
		m_pVertexBuffer->updateBuffer( m_pHeightMap->getVertexHeightMap() );
	}
#pragma endregion
	

#pragma region GLScene::SmoothFilter
	unsigned short* GLScene::SmoothFilter(const unsigned short* pDepthPixels)
	{
		unsigned short* smoothDepthArray = new unsigned short[ m_pHeightMap->getPixelSize() ];

		for(unsigned int i = 0; i < m_pHeightMap->getPixelSize(); i++)
			smoothDepthArray[i] = pDepthPixels[i];

		// We will be using these numbers for constraints on indexes
		int widthBound = 640 - 1;
		int heightBound = 480 - 1;

		// We process each row
#ifdef _WIN32
		Concurrency::parallel_for(size_t(0),size_t(480* 640),[&](size_t depthArrayIndex)
		{
#else
		for(int depthArrayIndex = 0; depthArrayIndex < (480* 640); depthArrayIndex++)
		{
#endif
			int depthIndex = depthArrayIndex;

			// We are only concerned with eliminating 'white' noise from the data.
			// We consider any pixel with a depth of 0 as a possible candidate for filtering.
			if (pDepthPixels[depthIndex] == 0)
			{
				// From the depth index, we can determine the X and Y coordinates that the index
				// will appear in the image. We use this to help us define our filter matrix.
				int x = depthIndex % 640;
				int y = (depthIndex - x) / 640;

				// The filter collection is used to count the frequency of each
				// depth value in the filter array. This is used later to determine
				// the statistical mode for possible assignment to the candidate.
				unsigned short filterCollection [24][2];

				for(int i = 0; i < 24; i++)
				for(int j = 0; j < 2; j++)
				filterCollection[i][j] = 0;

				// The inner and outer band counts are used later to compare against the threshold 
				// values set in the UI to identify a positive filter result.
				int innerBandCount = 0;
				int outerBandCount = 0;

				// The following loops will loop through a 5 X 5 matrix of pixels surrounding the 
				// candidate pixel. This defines 2 distinct 'bands' around the candidate pixel.
				// If any of the pixels in this matrix are non-0, we will accumulate them and count
				// how many non-0 pixels are in each band. If the number of non-0 pixels breaks the
				// threshold in either band, then the average of all non-0 pixels in the matrix is applied
				// to the candidate pixel.
				for (int yi = -2; yi < 3; yi++)
				{
					for (int xi = -2; xi < 3; xi++)
					{
						// yi and xi are modifiers that will be subtracted from and added to the
						// candidate pixel's x and y coordinates that we calculated earlier. From the
						// resulting coordinates, we can calculate the index to be addressed for processing.

						// We do not want to consider the candidate
						// pixel (xi = 0, yi = 0) in our process at this point.
						// We already know that it's 0
						if (xi != 0 || yi != 0)
						{
							// We then create our modified coordinates for each pass
							int xSearch = x + xi;
							int ySearch = y + yi;

							// While the modified coordinates may in fact calculate out to an actual index, it 
							// might not be the one we want. Be sure to check
							// to make sure that the modified coordinates
							// match up with our image bounds.
							if (xSearch >= 0 && xSearch <= widthBound && 
								ySearch >= 0 && ySearch <= heightBound)
							{
								int index = xSearch + (ySearch * 640);
								// We only want to look for non-0 values
								if (pDepthPixels[index] != 0)
								{
									// We want to find count the frequency of each depth
									for (int i = 0; i < 24; i++)
									{
										if (filterCollection[i][0] == pDepthPixels[index])
										{
											// When the depth is already in the filter collection
											// we will just increment the frequency.
											filterCollection[i][1]++;
											break;
										}
										else if (filterCollection[i][0] == 0)
										{
											// When we encounter a 0 depth in the filter collection
											// this means we have reached the end of values already counted.
											// We will then add the new depth and start it's frequency at 1.
											filterCollection[i][0] = pDepthPixels[index];
											filterCollection[i][1]++;
											break;
										}
									}

									// We will then determine which band the non-0 pixel
									// was found in, and increment the band counters.
									if (yi != 2 && yi != -2 && xi != 2 && xi != -2)
									innerBandCount++;
									else
									outerBandCount++;
								}
							}
						}
					}
				}

				int innerBandThreshold = 1;
				int outerBandThreshold = 1;

				// Once we have determined our inner and outer band non-zero counts, and 
				// accumulated all of those values, we can compare it against the threshold
				// to determine if our candidate pixel will be changed to the
				// statistical mode of the non-zero surrounding pixels.
				if (innerBandCount >= innerBandThreshold || outerBandCount >= outerBandThreshold)
				{
					short frequency = 0;
					short depth = 0;
					// This loop will determine the statistical mode
					// of the surrounding pixels for assignment to
					// the candidate.
					for (int i = 0; i < 24; i++)
					{
						// This means we have reached the end of our
						// frequency distribution and can break out of the
						// loop to save time.
						if (filterCollection[i][0] == 0)
							break;

						if (filterCollection[i][1] > frequency)
						{
							depth = filterCollection[i][0];
							frequency = filterCollection[i][1];
						}
					}
 
					smoothDepthArray[depthIndex] = depth;
				}
			}
			else
			{
				// If the pixel is not zero, we will keep the original depth.
				smoothDepthArray[depthIndex] = pDepthPixels[depthIndex];
			}
		}

#ifdef _WIN32		
		); //PPL closing
#endif

		return smoothDepthArray;
	}
#pragma endregion




	void GLScene::switchTextureMode(void)
	{
		if(m_TextureMode)
		{
			m_TextureMode = false;
		}
		else
		{
			m_TextureMode = true;
		}
	}

	void GLScene::showControlMenu( double motorAngle )
	{
		cout << "---DirectLook Status---" << endl;
		cout << "Motor : " << motorAngle << endl;
		cout << "Near Threshold : " << m_pHeightMap->getNearThreshold() << " mm" << endl;
		cout << "Far Threshold  : " << m_pHeightMap->getFarThreshold() << " mm" << endl;
		cout << "------------------------\n" << endl;
	}

	void GLScene::resetCamera(void)
	{
		if(m_pCamera)
		{
			m_pCamera->reset();
			m_pCamera->rotateAroundPosition( 0.0f, 0.0f );
			m_pCamera->addToCamera( 0.0f, 0.0f, (float)(m_pHeightMap->getNearThreshold() - m_pHeightMap->getFarThreshold()) / 4.0f );
		}
	}

	void GLScene::resetModel(void)
	{
		m_MatWorld.identity();
		m_Position = Vector3();
		m_Rotation = Vector3();
		m_Scale    = Vector3( 1.0f, 1.0f, 1.0f );
	}

	void GLScene::reloadShaderProgram(void)
	{
		if(m_pShader)
		{
			if(m_pShader->reload())
			{
				// Show status
				std::cout << std::endl;
				std::cout << "Shader Code reloaded    : OK" << std::endl;
				std::cout << "Shader Program reloaded : OK" << std::endl;
			}
		}
	}

	void GLScene::initBackgroundVideo(void){
		//z = -50;
		m_pAvVidDecoder.init(m_pVideoPath);

		m_pRatioW = m_pRatioH = 1.0f;
					
		//this->ratioW = (float)avTest.getWidth() / (float) avTest.getHeight();
		m_pRatioH = (float)m_pAvVidDecoder.getHeight() / (float)m_pAvVidDecoder.getWidth();
		if (m_pRatioH <= 0)
			m_pRatioH = 1;
	
		m_pScaleX = abs(this->m_pCamera->m_FarClipPlane) * tan(this->m_pCamera->m_FieldOfView/2) * m_pRatioW;
		m_pScaleY = abs(this->m_pCamera->m_FarClipPlane) * tan(this->m_pCamera->m_FieldOfView/2) * m_pRatioH;
		//scaleX = 50 * tan(22.5);
		//scaleY = 50 * tan(22.5) * ratioH;

		glGenTextures(1, &m_pVidTexture[0]);
		glBindTexture(GL_TEXTURE_2D, m_pVidTexture[0]);
	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_pAvVidDecoder.getWidth(), m_pAvVidDecoder.getHeight(),
																0, GL_RGB, GL_UNSIGNED_BYTE, NULL);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	void GLScene::initialize(void)
	{
		// Is the DirectLook initialized?
		if(!m_IsInitialized)
		{
			std::cout << "Initializes DirectLook:" << std::endl;
			
			m_pIsVideoPathSet = false;

			// Set camera to default values
			resetCamera();

			// Create and initialize the element buffer objects
			initElementBuffer();
			
			// Create and initialize the vertex buffer object
			initVertexBuffer();

			// Create and initialize the camera- and depth texture object
			initTextures();

			// Create and initialize the simple texture object
			std::string vFilename = "..//data//shader//vertexTexture.glsl";
			std::string fFilename = "..//data//shader//fragmentTexture.glsl";
			m_SimpleTexture.init( vFilename, fFilename );

			// Create and initialize the render target object

			m_pRenderTarget = new RenderTarget( m_CameraWidth, m_CameraHeight );

			// Create and initialize the shader object
			if(!m_pShader->compile())
			{
				fprintf( stderr, "Failed to load resources\n" );
				return;
			}

			// Initializing complete
			m_IsInitialized = true;
			m_IsUpdated		= false;
			update();
		}
	}

	void GLScene::drawBackgroundVideo(void){
		
		glDepthMask(false);		
		glEnable(GL_TEXTURE_2D);

		glLoadIdentity();									// Reset The Current Modelview Matrix	
		glScalef	(1.0f,	 -1.0f,  1.0f);					//For flipping the texture
		glBindTexture(GL_TEXTURE_2D, m_pVidTexture[0]);

		m_pAvVidDecoder.run();

		if(m_pAvVidDecoder.getLatestFrame()->data != 0)
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_pAvVidDecoder.getWidth(), m_pAvVidDecoder.getHeight(), 
									GL_RGB, GL_UNSIGNED_BYTE, m_pAvVidDecoder.getLatestFrame()->data[0]);	

		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  -1.0f);		
		glEnd();
		
		glDisable(GL_TEXTURE_2D);		
		glDepthMask(true);		
	}

	void GLScene::draw(void)
	{
		// Clear color and depth buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		// Enable render to texture
		m_pRenderTarget->enable();
				
		if (m_pIsVideoPathSet)
			drawBackgroundVideo();

		// Draw GLScene
		drawScene();
		
		// Disable render to texture
		m_pRenderTarget->disable();

		// Read raw pixels from frame buffer texture
		m_SimpleTexture.update( m_pRenderTarget->getPixels() );
		m_SimpleTexture.draw();
	}

	void GLScene::deleteResources(void)
	{
		//GLMesh::~GLMesh();
				GLMesh::deleteResources();

		if(m_pCameraTexture){ delete m_pCameraTexture;	m_pCameraTexture = 0; }
		if(m_pDepthTexture)	{ delete m_pDepthTexture;	m_pDepthTexture	 = 0; }
		if(m_pBackgroundTexture) { delete m_pBackgroundTexture; m_pBackgroundTexture = 0; }
		if(m_pHeightMap)	{ delete m_pHeightMap;		m_pHeightMap	 = 0; }
		if(m_pRenderTarget)	{ delete m_pRenderTarget;	m_pRenderTarget	 = 0; }
		
	}

	unsigned int GLScene::getCameraWidth(void) const
	{
		return m_CameraWidth;
	}

	unsigned int GLScene::getCameraHeight(void) const
	{
		return m_CameraHeight;
	}

	unsigned int GLScene::getDepthWidth(void) const
	{
		return m_DepthWidth;
	}

	unsigned int GLScene::getDepthHeight(void) const
	{
		return m_DepthHeight;
	}

	unsigned short GLScene::getNearThreshold(void) const
	{
		return m_pHeightMap->getNearThreshold();
	}

	unsigned short GLScene::getFarThreshold(void) const
	{
		return m_pHeightMap->getFarThreshold();
	}

	const GLubyte* GLScene::getRGBPixels(void) const
	{
		return m_pRenderTarget->getPixels();
	}

	bool GLScene::getRGBPixels(GLubyte* pBuffer, const unsigned int size) const
	{
		return m_pRenderTarget->getPixels(pBuffer, size, GL_RGB);
	}

	bool GLScene::getBGRPixels(GLubyte* pBuffer, const unsigned int size) const
	{
		return m_pRenderTarget->getPixels(pBuffer, size, GL_BGR);
	}

	void GLScene::switchBackround(void)
	{
		if(m_Background)
		{
			m_Background = false;
		}
		else
		{
			m_Background = true;
		}
	}

	void GLScene::setVideoPath(string path){		
		m_pVideoPath = path;
		if (m_pVideoPath.size() > 0){
			initBackgroundVideo();
			m_pIsVideoPathSet = true;
		}
	}

	void GLScene::setNearThreshold( const unsigned short nearThreshold )
	{
		float deltaOld = (float) m_pHeightMap->getFarThreshold() - (float) m_pHeightMap->getNearThreshold();
		m_pHeightMap ->setNearThreshold( nearThreshold );
		float deltaNew = (float) m_pHeightMap->getFarThreshold() - (float) m_pHeightMap->getNearThreshold();
		setPosition( 0.0f, 0.0f, m_Position.z + ((deltaNew - deltaOld) * 0.5f) );
	}

	void GLScene::setFarThreshold( const unsigned short farThreshold )
	{
		float deltaOld = (float) m_pHeightMap->getFarThreshold() - (float) m_pHeightMap->getNearThreshold();
		m_pHeightMap ->setFarThreshold( farThreshold );
		float deltaNew = (float) m_pHeightMap->getFarThreshold() - (float) m_pHeightMap->getNearThreshold();
		setPosition( 0.0f, 0.0f, m_Position.z - ((deltaNew - deltaOld) * 0.5f) );
	}

	void GLScene::setBackgroundTexture( const unsigned int width, const unsigned int height, const GLubyte* pPixels )
	{
		if(pPixels)
		{
			if(m_pBackgroundTexture)
			{
				delete m_pBackgroundTexture;
				m_pBackgroundTexture = 0;
			}
			
			m_pBackgroundTexture = new TextureObject( width, height, 0,
				GL_RGB,	// External texture color format
				GL_RGB,	// Internal texture color format
				0, GL_TEXTURE_2D, GL_UNSIGNED_BYTE
			);
			m_pBackgroundTexture->generateTexture( pPixels );
		}
	}

	void GLScene::initElementBuffer(void)
	{
		// (Width - 1) * (Height - 1) cells, 2 triangles per cell, 3 indices per triangle
		unsigned int nIndices = (m_DepthWidth - 1) * (m_DepthHeight - 1) * 6;

		// Neuen Element Buffer erzeugen
		GLuint* pBuffer = new GLuint[nIndices];
		unsigned int index = 0;

		// For each cell
		for(unsigned int x = 0; x < m_DepthWidth - 1; x++)
		{
			for(unsigned int y = 0; y < m_DepthHeight - 1; y++)
			{
				// Find the indices of the corners
				GLuint upperLeft  = y * m_DepthWidth + x;
				GLuint upperRight = upperLeft + 1;
				GLuint lowerLeft  = upperLeft + m_DepthWidth;
				GLuint lowerRight = lowerLeft + 1;
				
				// Specify upper triangle
				pBuffer[index++] = upperLeft;
				pBuffer[index++] = upperRight;
				pBuffer[index++] = lowerLeft;
				
				// Specify lower triangle
				pBuffer[index++] = lowerLeft;
				pBuffer[index++] = upperRight;
				pBuffer[index++] = lowerRight;
			}
		}

		// Neues Element-Buffer-Object erzeugen
		m_pElementBuffer = new ElementBufferObject( pBuffer, nIndices );

		// Speicher freigeben
		delete[] pBuffer;
		pBuffer = 0;
	}

	void GLScene::initVertexBuffer(void)
	{		
		if(m_pHeightMap)
		{
			if(m_pHeightMap->getVertexHeightMap())
			{
				// Neues Vertex-Buffer-Object erzeugen
				m_pVertexBuffer = new VertexBufferObject( m_pHeightMap->getVertexHeightMap(), m_DepthWidth * m_DepthHeight, 3 );
			}
		}
	}

	void GLScene::initTextures(void)
	{
		// Create and initialize the camera texture object
		const unsigned int cameraBufferSize = m_CameraWidth * m_CameraHeight * 3;
		GLubyte* pCameraData = new GLubyte[cameraBufferSize];
		for(unsigned int i = 0; i < cameraBufferSize; i += 3)
		{
			// Black
			pCameraData[i]	   = 0;
			pCameraData[i + 1] = 0;
			pCameraData[i + 2] = 0;
		}
		m_pCameraTexture = new TextureObject( m_CameraWidth, m_CameraHeight, 0,
			GL_RGB,	// External texture color format
			GL_RGB,	// Internal texture color format
			0, GL_TEXTURE_2D, GL_UNSIGNED_BYTE
		);
		m_pCameraTexture->generateTexture( pCameraData );
		m_pBackgroundTexture = new TextureObject( m_CameraWidth, m_CameraHeight, 0,
			GL_RGB,	// External texture color format
			GL_RGB,	// Internal texture color format
			0, GL_TEXTURE_2D, GL_UNSIGNED_BYTE
		);
		m_pBackgroundTexture->generateTexture( pCameraData );
		delete[] pCameraData;
	
		// Create and initialize the depth texture object
		const unsigned int depthBufferSize = m_DepthWidth * m_DepthHeight;
		GLubyte* pDepthData = new GLubyte[depthBufferSize];
		for(unsigned int i = 0; i < depthBufferSize; i++)
		{
			pDepthData[i] = 0;	// Black
		}
		m_pDepthTexture = new TextureObject( m_DepthWidth, m_DepthHeight, 0,
			GL_RED,	// External texture color format
			1,		// Internal texture color format : 1 for RED color channel only
			0, GL_TEXTURE_2D, GL_UNSIGNED_BYTE
		);
		m_pDepthTexture->generateTexture( pDepthData );
		delete[] pDepthData;
	}

	void GLScene::drawScene(void)
	{
		// Activating the shader program and assigning uniforms
		m_pShader->enable();

		// Activating the camera view projection matrix uniform variable
		m_pShader->setMatrix( &m_pCamera->m_MatViewProjection, "matVP" );

		// Activating the GLScene world matrix uniform variable
		m_pShader->setMatrix( &m_MatWorld, "matW" );

		// Activating the min depth map distance
		m_pShader->setFloatValue( (GLfloat) m_pHeightMap->getMinDistance(), "minDistance" );
		
		// Activating the max depth map distance
		m_pShader->setFloatValue( (GLfloat) m_pHeightMap->getMaxDistance(), "maxDistance" );
		
		// Activating the near threshold
		m_pShader->setFloatValue( (GLfloat) m_pHeightMap->getNearThreshold(), "nearThreshold" );

		// Activating the far threshold
		m_pShader->setFloatValue( (GLfloat) m_pHeightMap->getFarThreshold(), "farThreshold" );

		// Activating the camera- and depth image resolutions
		m_pShader->setFloatValue( (GLfloat) m_CameraWidth,  "cameraWidth"  );
		m_pShader->setFloatValue( (GLfloat) m_CameraHeight, "cameraHeight" );
		m_pShader->setFloatValue( (GLfloat) m_DepthWidth,   "depthWidth"   );
		m_pShader->setFloatValue( (GLfloat) m_DepthHeight,  "depthHeight"  );

		// Texture mode camera- or depth texture?
		if(m_TextureMode)
			m_pShader->setIntValue( 1, "textureMode" );
		else
			m_pShader->setIntValue( 0, "textureMode" );

		// Hintergrund ein- oder ausblenden?
		if(m_Background)
			m_pShader->setIntValue( 1, "backgroundPlane" );
		else
			m_pShader->setIntValue( 0, "backgroundPlane" );

		// Activating the camera texture
		m_pShader->setTexture( m_pCameraTexture, GL_TEXTURE0, 0, "textures[0]" );

		// Activating the depth texture
		m_pShader->setTexture( m_pDepthTexture, GL_TEXTURE1, 1, "textures[1]" );

		// Activating the background texture
		m_pShader->setTexture( m_pBackgroundTexture, GL_TEXTURE2, 2, "textures[2]" );

		// Enable and setting up the vertex buffer object
		m_pShader->setVertexAttribute( m_pVertexBuffer, "position" );
		
		// Submitting the rendering job with an element buffer object
		glBindBuffer( m_pElementBuffer->getTarget(), m_pElementBuffer->getID() );
		glDrawElements(
			GL_TRIANGLES,					// mode 
			m_pElementBuffer->getSize(),	// count
			GL_UNSIGNED_INT,				// type
			(void*) 0						// element array buffer offset
		);

		// Cleaning up after ourselves
		m_pShader->resetVertexAttribute( "position" );

		// Disable shader program
		m_pShader->disable();
	}

};
