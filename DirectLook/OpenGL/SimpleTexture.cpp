#include "SimpleTexture.h"

namespace DirectLook
{
	SimpleTexture::SimpleTexture( const unsigned short width, const unsigned short height )
		:
		m_pElementBuffer( 0 ),
		m_pVertexBuffer( 0 ),
		m_pTexture( 0 ),
		m_pShader( 0 ),
		m_Width( width ),
		m_Height( height ),
		m_IsInitialized( false )
	{
	}

	SimpleTexture::~SimpleTexture(void)
	{
		if(m_pElementBuffer)
		{
			delete m_pElementBuffer;
			m_pElementBuffer = 0;
		}
		
		if(m_pVertexBuffer)
		{
			delete m_pVertexBuffer;
			m_pVertexBuffer = 0;
		}
		
		if(m_pTexture)
		{
			delete m_pTexture;
			m_pTexture = 0;
		}

		if(m_pShader)
		{
			delete m_pShader;
			m_pShader = 0;
		}
	}

	void SimpleTexture::init( std::string& vertexShaderFilename, std::string& fragmentShaderFilename )
	{
		if(!m_IsInitialized)
		{
			// Create and initialize the texture object
			const unsigned int bufferSize = m_Width * m_Height * 3;
			GLubyte* pData = new GLubyte[bufferSize];
			for(unsigned int i = 0; i < bufferSize; i += 3)
			{
				pData[i]	 = 0;
				pData[i + 1] = 0;
				pData[i + 2] = 0;
			}
			m_pTexture = new TextureObject( m_Width, m_Height, 0,
				GL_RGB,	// External texture color format
				GL_RGB,	// Internal texture color format
				0, GL_TEXTURE_2D, GL_UNSIGNED_BYTE
			);
			m_pTexture->generateTexture( pData );
			delete[] pData;

			// Create and initialize the vertex buffer object
			GLfloat vertices[8] =
			{
				-1.0f,  1.0f,
				 1.0f,  1.0f,
				 1.0f, -1.0f,
				-1.0f, -1.0f
			};
			m_pVertexBuffer = new VertexBufferObject( vertices, 4, 2 );

			// Neues Element-Buffer-Object erzeugen
			GLuint indices[6] =
			{
				0, 1, 3,
				1, 2, 3
			};
			m_pElementBuffer = new ElementBufferObject( indices, 6 );

			initShader( vertexShaderFilename, fragmentShaderFilename );

			// Initializing complete
			m_IsInitialized = true;
		}
	}
	
	int SimpleTexture::initShader( std::string& vertexShaderFilename, std::string& fragmentShaderFilename )
	{
		// Create and initialize the shader object
		m_pShader = new Shader( vertexShaderFilename, fragmentShaderFilename );

		// Generate Shader Object
		if(!m_pShader->compile())
		{
			return 0;
		}

		// Show Status
		std::cout << std::endl;
		std::cout << "Simple Texture : OK" << std::endl;
		std::cout << "Shader Code    : OK" << std::endl;
		std::cout << "Shader Program : OK" << std::endl;

		return 1;
	}
	
	void SimpleTexture::update( const GLubyte* pPixels )
	{
		// Update texture object
		m_pTexture->updateTexture( pPixels );
	}
	
	void SimpleTexture::draw(void)
	{
		// Activating the shader program and assigning uniforms
		m_pShader->enable();

		// Activating the  texture
		m_pShader->setTexture( m_pTexture, GL_TEXTURE0, 0, "texture" );

		// Enable shader attribute and setting up the vertex buffer object
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
}
