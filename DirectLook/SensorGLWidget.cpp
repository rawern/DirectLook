#include "SensorGLWidget.h"

namespace DirectLook
{
	SensorGLWidget::SensorGLWidget( unsigned int width, unsigned int height, QWidget* parent )
		: QGLWidget( parent )
	{
		m_pSensorDevice = 0;
		setFixedSize( width, height );
		m_SensorUpdate = true;
		
		// QTimer controls the render process:
		m_pTimer = new QTimer( this );
		connect( m_pTimer, SIGNAL( timeout() ), this, SLOT( sensorUpdate() ) );
	}

	SensorGLWidget::~SensorGLWidget(void)
	{
		if(m_pGLScene){ delete m_pGLScene;	m_pGLScene = 0; }
		if(m_pCamera){ delete m_pCamera;	m_pCamera = 0; }
		if(m_pShader){ delete m_pShader;	m_pShader = 0; }
		if(m_pTimer) { delete m_pTimer;		m_pTimer  = 0; }
	}

	bool SensorGLWidget::start( unsigned int fps )
	{
		if(m_pSensorDevice->connect())
		{
			glClearColor( 100.0f / 255.0f, 149.0f / 255.0f, 1.0f, 1.0f );
			std::cout << "sensor started\n" << std::endl;
	
			// Konvert fps to milliseconds:
			double ms = 1000.0 / (double) fps;

			// QTimer controls the render process:
			m_pTimer->start( (int) ms );
			return true;
		}
		else
		{
			return false;
		}
	}

	void SensorGLWidget::stop(void)
	{
		if(m_pSensorDevice)
		{
			m_pSensorDevice->close();
			delete m_pSensorDevice;
			m_pSensorDevice = 0;
		}

		m_pTimer->stop();
	}

	GLScene* SensorGLWidget::getGLScene(void)
	{
		return m_pGLScene;
	}

	GLCamera* SensorGLWidget::getCamera(void)
	{
		return m_pCamera;
	}

	bool SensorGLWidget::getSensorUpdate(void) const
	{
		return m_SensorUpdate;
	}

	void SensorGLWidget::setSensorDevice( SensorOpenNI* pSensorDevice )
	{
		m_pSensorDevice = pSensorDevice;
	}

	void SensorGLWidget::resetGLScene(void)
	{
		unsigned int cameraSize = m_pGLScene->getCameraWidth() * m_pGLScene->getCameraHeight() * 3;
		unsigned int depthSize = m_pGLScene->getDepthWidth() * m_pGLScene->getDepthHeight();
		float* pImagePixels = new float[cameraSize];
		unsigned short* pDepthPixels = new unsigned short[depthSize];
		for(unsigned int i = 0; i < cameraSize; i++) { pImagePixels[i] = 0.0f; }
		for(unsigned int i = 0; i < depthSize; i++) { pDepthPixels[i] = 0; }
		m_pGLScene->updateData( pImagePixels, pDepthPixels );
		delete[] pImagePixels;
		delete[] pDepthPixels;
		repaint();
	}

	void SensorGLWidget::switchSensorUpdate(void)
	{
		if(m_SensorUpdate)
		{
			m_SensorUpdate = false;
		}
		else
		{
			m_SensorUpdate = true;
		}
	}

	void SensorGLWidget::initializeGL(void)
	{
		makeCurrent();
		std::cout << "Initializes OpenGL:" << std::endl;
		GLenum errorCode = glewInit();
	
		if(GLEW_OK != errorCode)
		{
	#if _DEBUG
			std::cerr << "GlEW-Initialization gave error: " << glewGetErrorString( errorCode ) << std::endl << std::endl;
			std::cin.clear();
			std::cin.sync();
			std::cin.get();
	#else
			QMessageBox mb;
			mb.setText("GlEW-Initialization gave error: " + QString(reinterpret_cast<const char*>(glewGetErrorString( errorCode ))));
			mb.setIcon(QMessageBox::Critical);
			mb.exec();
	#endif
			exit(1);
		}
		std::cout << "Using GLEW" << std::endl;

		if(!GLEW_VERSION_2_0)
		{
	#if _DEBUG
			std::cerr << "GL 2.0 is not supported.\nGet proper Hardware.\n Press Enter to Exit..." << std::endl;
			std::cin.clear();
			std::cin.sync();
			std::cin.get();
	#else
			QMessageBox mb;
			mb.setText("GL 2.0 is not supported.\n Get proper Hardware.");
			mb.setIcon(QMessageBox::Critical);
			mb.exec();
	#endif
			exit(1);
		}
		std::cout << "Using GL 2.0\n" << std::endl;

		// Set color and depth clear value
		glClearDepth( 1.0f );
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		std::cout << "Clear color : cornflower blue" << std::endl;

		// Enable Z-buffer read and write
		glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );
		std::cout << "Depth test  : ON\n" << std::endl;

		initialize();
	}

	void SensorGLWidget::paintGL(void)
	{
		// Update and draw the 3D-Model
		//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		//m_pBackgroundVideo->drawBackgroundVideo();
		m_pGLScene->update();
		m_pGLScene->draw();
	}

	void SensorGLWidget::mousePressEvent( QMouseEvent* event )
	{
		m_LastMousePosition = event->pos();
	}

	void SensorGLWidget::mouseMoveEvent( QMouseEvent* event )
	{
		int dX = event->x() - m_LastMousePosition.x();
		int dY = event->y() - m_LastMousePosition.y();

		if(event->buttons() & Qt::LeftButton)
		{
			m_pCamera->rotateAroundPosition( -(float) dX / 100.0f, -(float) dY / 100.0 );
			repaint();
		}
	
		m_LastMousePosition = event->pos();
	}

	void SensorGLWidget::initialize(void)
	{
		// Create a camera and shader
		m_pCamera = new GLCamera();
		m_pShader = new Shader( "..//data//shader//vertex.glsl", "..//data//shader//fragment.glsl" );
		
		// Create a GLScene object
		m_pGLScene = new GLScene(
			500,	// Near threshold
			800,	// Far threshold
			640, 480, 640, 480,
			m_pShader, m_pCamera

		);
	}

	void SensorGLWidget::sensorUpdate(void)
	{
		if(m_SensorUpdate)
		{
					// Read RGB- and DepthMap-Image from Sensor
					m_pSensorDevice->getSensorData( *m_pGLScene );	
		}

		// Update and draw the 3D-Model
		repaint();
	}
}
