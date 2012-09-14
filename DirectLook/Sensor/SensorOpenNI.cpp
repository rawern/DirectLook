#include "SensorOpenNI.h"
#include <QMessageBox>

namespace DirectLook 
{
	SensorOpenNI::SensorOpenNI( const XnChar* videoFileName )
		:
		m_ConfigFlag( false ),
		m_VideoFlag( true ),
		m_MirrorMode( false ),
		m_VideoFileName( videoFileName ),
		m_CameraWidth( 0 ),
		m_CameraHeight( 0 ),
		m_DepthWidth( 0 ),
		m_DepthHeight( 0 ),
		m_ImageMapPixelSize( 0 ),
		m_DepthMapPixelSize( 0 ),
		m_Status( 0 )
	{
	}

	SensorOpenNI::SensorOpenNI( const XnChar* configFileName, const bool mirrorMode )
		:
		m_ConfigFlag( true ),
		m_VideoFlag( false ),
		m_MirrorMode( mirrorMode ),
		m_ConfigFileName( configFileName ),
		m_CameraWidth( 0 ),
		m_CameraHeight( 0 ),
		m_DepthWidth( 0 ),
		m_DepthHeight( 0 ),
		m_ImageMapPixelSize( 0 ),
		m_DepthMapPixelSize( 0 ),
		m_Status( 0 )
	{
	}

	SensorOpenNI::SensorOpenNI( const XnUInt32 width, const XnUInt32 height, const bool mirrorMode )
		:
		m_ConfigFlag( false ),
		m_VideoFlag( false ),
		m_MirrorMode( mirrorMode ),
		m_CameraWidth( width ),
		m_CameraHeight( height ),
		m_DepthWidth( width ),
		m_DepthHeight( height ),
		m_ImageMapPixelSize( m_CameraWidth * m_CameraHeight * 3 ),
		m_DepthMapPixelSize( m_DepthWidth * m_DepthHeight ),
		m_Status( 0 )
	{
	}

	SensorOpenNI::SensorOpenNI( const XnUInt32 widthCamera, const XnUInt32 heightCamera, const XnUInt32 widthDepth, const XnUInt32 heightDepth, const bool mirrorMode )
		:
		m_ConfigFlag( false ),
		m_VideoFlag( false ),
		m_MirrorMode( mirrorMode ),
		m_CameraWidth( widthCamera ),
		m_CameraHeight( heightCamera ),
		m_DepthWidth( widthDepth ),
		m_DepthHeight( heightDepth ),
		m_ImageMapPixelSize( m_CameraWidth * m_CameraHeight * 3 ),
		m_DepthMapPixelSize( m_DepthWidth * m_DepthHeight ),
		m_Status( 0 )
	{
	}

	SensorOpenNI::~SensorOpenNI(void)
	{
	}

	bool SensorOpenNI::connect(void)
	{
		// Connect to kinect motor driver and set the angle to 0 °
		std::cout << std::endl;
		if(m_Motor.open())
		{
			m_Motor.move( (int)0 );
			std::cout << "Kinect motor connection: OK\n" << std::endl;
		}
		else
		{
			std::cout << "Connection to kinect motor failed!\n" << std::endl;
		}

		m_Status = XN_STATUS_OK;
	
		if(m_ConfigFlag)		// Case 1 - Loading OpenNI settings by XML-File
		{
			initialize();
		}
		else if(m_VideoFlag)	// Case 2 - Loading OpenNI image data by Oni-File
		{
			// Initialize OpenNI context-object
			m_Status = m_Context.Init();
			if(!printStatus( "Initializes OpenNI sensor", "Couldn't initializes OpenNI sensor" ))
			{
				return false;
			}

			// Read sensor data from oni file
			std::cout << "Loading Videofile: " << m_VideoFileName << std::endl;			
			m_Status = m_Context.OpenFileRecording( m_VideoFileName.c_str() );
			if(!printStatus( "Sucessfully opened Oni file", "Couldn't open Oni file" ))
			{
				return false;
			}
			std::cout << std::endl;

			m_Status = m_Context.FindExistingNode( XN_NODE_TYPE_DEPTH, m_DepthGenerator );
			if(!printStatus( "Found Depth Node in Oni", "Couldn't find Depth Node in Oni File" ))
			{
				return false;
			}
			
			// Show depth map output mode
			XnMapOutputMode depthMapMode;
			m_DepthGenerator.GetMapOutputMode( depthMapMode );
			std::cout << "Depth map width  : " << depthMapMode.nXRes << std::endl;
			std::cout << "Depth map height : " << depthMapMode.nYRes << std::endl;
			std::cout << "Depth map FPS    : " << depthMapMode.nFPS << std::endl;
			std::cout << std::endl;

			// Set depth map resolution
			m_DepthWidth  = depthMapMode.nXRes;
			m_DepthHeight = depthMapMode.nYRes;
			m_DepthMapPixelSize = m_DepthWidth * m_DepthHeight;

			m_Status = m_Context.FindExistingNode( XN_NODE_TYPE_IMAGE, m_ImageGenerator );
			if(!printStatus( "Found Image Node in Oni", "Couldn't find Image Node in Oni File" ))
			{
				return false;
			}

			// Show camera map output mode
			XnMapOutputMode cameraMapMode;
			m_ImageGenerator.GetMapOutputMode( cameraMapMode );
			std::cout << "Camera width  : " << cameraMapMode.nXRes << std::endl;
			std::cout << "Camera height : " << cameraMapMode.nYRes << std::endl;
			std::cout << "Camera FPS    : " << cameraMapMode.nFPS << std::endl;
			std::cout << std::endl;

			// Set camera resolution
			m_CameraWidth  = cameraMapMode.nXRes;
			m_CameraHeight = cameraMapMode.nYRes;
			m_ImageMapPixelSize = m_CameraWidth * m_CameraHeight * 3;

			/* AUDIO SUPPORT FOR ONI FILES DISAPLED: NOT TESTED
			m_Status = m_Context.FindExistingNode( XN_NODE_TYPE_AUDIO, m_AudioGenerator );
			if(!printStatus( "Found Audio Node in Oni", "Couldn't find Audio Node in Oni File" ))
			{
				return false;
			}
			*/
		}
		else	// Case 3 - Initialize OpenNI settings
		{
			// Initialize OpenNI context-object
			m_Status = m_Context.Init();
			if(!printStatus( "Initializes OpenNI sensor", "Couldn't initializes OpenNI sensor" ))
			{
				return false;
			}

			m_Status = m_Context.SetGlobalMirror( m_MirrorMode );
			printStatus( "Set to Mirror Mode" , "Couldn't set to Mirror Mode" );

			// Create a depth generator
			m_Status = m_DepthGenerator.Create( m_Context );
			if(!printStatus( "Generating Depth Generator", "Couldn't generate Depth Generator" ))
			{
				return false;
			}

			// Create a image generator
			m_Status = m_ImageGenerator.Create( m_Context );
			if(!printStatus( "Generating Image Generator", "Couldn't generate Image Generator" ))
			{
				return false;
			}

			// Set it to VGA depth map at 30 FPS
			XnMapOutputMode depthMapMode;
			depthMapMode.nXRes = m_DepthWidth;
			depthMapMode.nYRes = m_DepthHeight;
			depthMapMode.nFPS  = 30;

			m_Status = m_DepthGenerator.SetMapOutputMode( depthMapMode );	
			if(!printStatus( "Set to VGA depth map at 30 FPS", "Couldn't set to VGA depth map at 30 FPS" ))
			{
				return false;
			}

			// Set it to VGA image map at 30 FPS
			XnMapOutputMode imageMapMode;
			imageMapMode.nXRes = m_CameraWidth;
			imageMapMode.nYRes = m_CameraHeight;
			imageMapMode.nFPS  = 30;

			m_Status = m_ImageGenerator.SetMapOutputMode( imageMapMode );	
			if(!printStatus( "Set to VGA image map at 30 FPS", "Couldn't set to VGA image map at 30 FPS" ))
			{
				return false;
			}

			// Create a audio generator
			m_Status = m_AudioGenerator.Create( m_Context );
			if(!printStatus( "Generating Audio Generator", "Couldn't generate Audio Generator" ))
			{
				return false;
			}

			// Set the audio output mode
			XnWaveOutputMode audioMode;
			audioMode.nBitsPerSample = 16;
			audioMode.nChannels = 2;
			audioMode.nSampleRate = 44100;

			m_Status = m_AudioGenerator.SetWaveOutputMode( audioMode );	
			if(!printStatus( "Set audio stream to CD-Quality", "Couldn't set audio stream to CD-Quality" ))
			{
				return false;
			}

			// Set sensor interface to mirror mode
			m_Status = m_Context.SetGlobalMirror( m_MirrorMode );
			printStatus( "Set to Mirror mode" , "Couldn't set to Mirror mode" );
		}

		// Start generating
		m_Status = m_Context.StartGeneratingAll();
		if(!printStatus( "Start generating data", "Couldn't start generate data" ))
		{
			return false;
		}

		// Connection to OpenNI sensor was successful
		return true;
	}

	void SensorOpenNI::close(void)
	{
		// Close connection from OpenNI sensor
		//m_Context.Shutdown();
		m_Context.Release();
	}

	bool SensorOpenNI::printStatus( const char* message, const char* error )
	{
		if(m_Status != XN_STATUS_OK)
		{
			
			#if _DEBUG
				std::cout << error << ":" << std::endl << "Failed: " << xnGetStatusString( m_Status ) << std::endl;
			#else
				QMessageBox mb;
				mb.setText(QString(error)+": \nFailed: "+xnGetStatusString( m_Status ));
				mb.setIcon(QMessageBox::Critical);
				mb.exec();
			#endif
			return false;
		}
		else
		{
			std::cout << message << ": " << xnGetStatusString( m_Status ) << std::endl;
			return true;
		}


		
	}

	void SensorOpenNI::initialize(void)
	{	
		xn::EnumerationErrors errors;
		m_Status = m_Context.InitFromXmlFile( m_ConfigFileName.c_str(), &errors );
	
		if(m_Status == XN_STATUS_NO_NODE_PRESENT)
		{
			XnChar strError[1024];
			errors.ToString(strError, 1024);
			
			#if _DEBUG
				std::cout << strError << std::endl;
			#else
				QMessageBox mb;
				mb.setText("Open configuration file failed: "+ QString(reinterpret_cast<const char*>(strError)));
				mb.setIcon(QMessageBox::Critical);
				mb.exec();
			#endif

		}
		else if(m_Status != XN_STATUS_OK)
		{
			
			#if _DEBUG
				std::cout << "Open configuration file failed: " << xnGetStatusString( m_Status ) << std::endl;
			#else
				QMessageBox mb;
				mb.setText("Open configuration file failed: "+ QString(reinterpret_cast<const char*>(glewGetErrorString( m_Status ))));
				mb.setIcon(QMessageBox::Critical);
				mb.exec();
			#endif
		}
		else
		{
			m_Status = m_Context.FindExistingNode( XN_NODE_TYPE_DEPTH, m_DepthGenerator );
			printStatus( "Loading Depth Generator", "Couldn't load Depth Generator from configuration file" );
		
			if(m_Status == XN_STATUS_OK)
			{
				m_DepthGenerator.GetMetaData( m_DepthMetaData );
				m_DepthWidth  = m_DepthMetaData.FullXRes();
				m_DepthHeight = m_DepthMetaData.FullYRes();
			}

			m_Status = m_Context.FindExistingNode( XN_NODE_TYPE_IMAGE, m_ImageGenerator );
			printStatus( "Loading Image Generator" , "Couldn't load Image Generator from configuration file" );
		
			if(m_Status == XN_STATUS_OK)
			{
				m_ImageGenerator.GetMetaData( m_ImageMetaData );		
				m_CameraWidth  = m_DepthMetaData.FullXRes();
				m_CameraHeight = m_DepthMetaData.FullYRes();
			}

			// Compute camera- and depth map pixel size
			m_DepthMapPixelSize = m_DepthWidth  * m_DepthHeight;
			m_ImageMapPixelSize = m_CameraWidth * m_CameraHeight * 3;

			// Set sensor interface to mirror mode
			m_Status = m_Context.SetGlobalMirror( m_MirrorMode );
			printStatus( "Set to Mirror mode" , "Couldn't set to Mirror mode" );

			m_Status = m_Context.FindExistingNode( XN_NODE_TYPE_AUDIO, m_AudioGenerator );
			printStatus( "Loading Audio Generator" , "Couldn't load Audio Generator from configuration file" );
		}
	}
	
	void SensorOpenNI::getSegmentedDepthImage( DepthImage* DepthImage )
	{
		// Update to next frame
		m_Status = m_Context.WaitOneUpdateAll( m_DepthGenerator );
	
		// Process the data
		m_DepthGenerator.GetMetaData( m_DepthMetaData );
		const XnDepthPixel* pDepthPixels = m_DepthMetaData.Data();

		// Copy depth map raw data to DepthImage
		DepthImage->updateImage( pDepthPixels );
	}

	void SensorOpenNI::getRgbMapImage( RGBImage* RGBImage )
	{
		// Update to next frame
		m_Status = m_Context.WaitOneUpdateAll( m_ImageGenerator );
	
		// Process the data
		m_ImageGenerator.GetMetaData( m_ImageMetaData );
		const XnUInt8* pImagePixels = m_ImageMetaData.Data();

		// Copy image map raw data to DepthImage
		RGBImage->updateImage( pImagePixels );
	}
	
	void SensorOpenNI::getAudioStream( AudioStream* audioStream )
	{
		// Update to next data
		m_Status = m_Context.WaitOneUpdateAll( m_AudioGenerator );
		
		// Get the audio buffer
		m_AudioGenerator.GetMetaData( m_AudioMetaData );
				
		// Copy audio buffer raw data to AudioStream
		audioStream->setBitsPerSample( m_AudioMetaData.BitsPerSample() );
		audioStream->setChannels( m_AudioMetaData.NumberOfChannels() );
		audioStream->setSampleRate( m_AudioMetaData.SampleRate() );
		audioStream->setBufferSize( m_AudioMetaData.DataSize() );
		audioStream->setAudioBuffer( m_AudioMetaData.Data() );
	}

	void SensorOpenNI::controlMotor( const double angle )
	{
		bool errorStatus = true;
		if(angle > 30)			// If angle bigger than 30 ° set motor to angle 30 °
		{
			errorStatus = m_Motor.move( 30 );
		}
		else if(angle < -30)	// If angle smaller than -30 ° set motor to angle -30 °
		{
			errorStatus = m_Motor.move( -30 );
		}
		else
		{
			errorStatus = m_Motor.move( (int) angle );
		}

		if(!errorStatus)
		{
			

			#if _DEBUG
				//std::cout << "Couldn't control the kinect motor!" << std::endl;
				std::cout << "No connection to kinect motor!\n" << std::endl;
			#else
				QMessageBox mb;
				mb.setText("Kinect motor failed: No connection to kinect motor!");
				mb.setIcon(QMessageBox::Critical);
				mb.exec();
			#endif
		}
	}

	XnUInt32 SensorOpenNI::getCameraWidth(void) const
	{
		return m_CameraWidth;
	}
		
	XnUInt32 SensorOpenNI::getCameraHeight(void) const
	{
		return m_CameraHeight;
	}
		
	XnUInt32 SensorOpenNI::getDepthWidth(void) const
	{
		return m_DepthWidth;
	}
		
	XnUInt32 SensorOpenNI::getDepthHeight(void) const
	{
		return m_DepthHeight;
	}

	XnUInt32 SensorOpenNI::getImageMapPixelSize(void) const
	{
		return m_ImageMapPixelSize;
	}

	XnUInt32 SensorOpenNI::getDepthMapPixelSize(void) const
	{
		return m_DepthMapPixelSize;
	}

	void SensorOpenNI::getSensorData( GLScene& GLScene )
	{
		// Offset zwischen den Tiefen- und RGB-Werten korrigieren:
		m_DepthGenerator.GetAlternativeViewPointCap().SetViewPoint( m_ImageGenerator );
		//m_ImageGenerator.GetAlternativeViewPointCap().SetViewPoint( m_DepthGenerator );

		// Update to next frame
		m_Status = m_Context.WaitOneUpdateAll( m_ImageGenerator );
		m_Status = m_Context.WaitOneUpdateAll( m_DepthGenerator );
	
		// Process the image data
		m_ImageGenerator.GetMetaData( m_ImageMetaData );
		const XnUInt8* pImagePixels = m_ImageMetaData.Data();
		
		// Process the depth map data
		m_DepthGenerator.GetMetaData( m_DepthMetaData );
		const XnDepthPixel* pDepthPixels = m_DepthMetaData.Data();

		// Copy image and depth map raw data to GLScene object
		GLScene.updateData( pImagePixels, pDepthPixels );
	}
}
