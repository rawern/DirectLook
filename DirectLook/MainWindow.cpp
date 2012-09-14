#include "MainWindow.h"

namespace DirectLook
{
	MainWindow::MainWindow(void)
		:
		m_MotorAngle( 0.0 ),
		m_HeadMove( 6.4f ),
		m_RotateAngle( 1.5f ),
		m_Width( 640 ),
		m_Height( 480 ),
		m_pSensorDevice( 0 ),
		m_pSensorWidget( 0 ),
		m_IsConnected( false )
	{
		createActions();
		createMenus();
		createGUI();
	}

	void MainWindow::closeEvent( QCloseEvent* event )
	{
		disconnect();
		if(m_pSensorDevice)
		{
			m_pSensorDevice->close();
			delete m_pSensorDevice;
			m_pSensorDevice = 0;
		}
	}

	void MainWindow::keyPressEvent( QKeyEvent* event )
	{
		switch(event->key())
		{	
			// GLScene moving:
			case Qt::Key_Up:
				m_pSensorWidget->getGLScene()->translate( 0.0f, 0.0f, -m_HeadMove );
				m_pSensorWidget->repaint();
				break;
			case Qt::Key_Down:
				m_pSensorWidget->getGLScene()->translate( 0.0f, 0.0f, m_HeadMove );
				m_pSensorWidget->repaint();
				break;

			// Camera moving:
			case Qt::Key_W:
				m_pSensorWidget->getCamera()->addToCamera( 0.0f, 0.0f, m_HeadMove );
				m_pSensorWidget->repaint();
				break;			
			case Qt::Key_S:
				m_pSensorWidget->getCamera()->addToCamera( 0.0f, 0.0f, -m_HeadMove );
				m_pSensorWidget->repaint();
				break;		
			case Qt::Key_A:
				m_pSensorWidget->getCamera()->addToCamera( -m_HeadMove, 0.0f, 0.0f );
				m_pSensorWidget->repaint();
				break;
			case Qt::Key_D:
				m_pSensorWidget->getCamera()->addToCamera( m_HeadMove, 0.0f, 0.0f );
				m_pSensorWidget->repaint();
				break;

			case Qt::Key_F1:
				m_pSensorWidget->getGLScene()->reloadShaderProgram();
				break;
		}
	}

	void MainWindow::connectToSensorDevice(void)
	{	
		m_pSensorWidget->stop();
		m_pSensorDevice = new SensorOpenNI( "../data/SamplesConfig.xml", false ); // m_Width, m_Height, false );
		m_pSensorWidget->setSensorDevice( m_pSensorDevice );
	
		if(m_pSensorWidget->start( 120 ))
		{
			m_IsConnected = true;
			m_ConnectAction->setEnabled( false );
			m_DisconnectAction->setEnabled( true );
			m_LoadONIAction->setEnabled( false );
			m_UnloadONIAction->setEnabled( false );
		}
	}

	void MainWindow::disconnect(void)
	{
		m_pSensorWidget->stop();
		m_pSensorDevice = 0;
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		m_pSensorWidget->resetGLScene();

		m_IsConnected = false;
		m_ConnectAction->setEnabled( true );
		m_DisconnectAction->setEnabled( false );
		m_LoadONIAction->setEnabled( true );
		m_UnloadONIAction->setEnabled( false );
	}

	bool MainWindow::loadONI(void)
	{
		QString fileName = QFileDialog::getOpenFileName( this, tr( "Load OpenNI video file" ), ".",  tr( "ONI files (*.oni)" ) );
		if(!fileName.isEmpty())
		{
			m_pSensorWidget->stop();
			m_pSensorDevice = new SensorOpenNI( fileName.toStdString().c_str() );
			m_pSensorWidget->setSensorDevice( m_pSensorDevice );
			m_pSensorWidget->start( 120 );

			m_ConnectAction->setEnabled( false );
			m_DisconnectAction->setEnabled( false );
			m_LoadONIAction->setEnabled( false );
			m_UnloadONIAction->setEnabled( true );

			statusBar()->showMessage( tr( "OpenNI video file loaded" ), 2000 );
			return true;
		}
		else
		{
			statusBar()->showMessage( tr( "Loading OpenNI video file canceled" ), 2000 );
			return false;
		}

		m_IsConnected = false;
	}

	void MainWindow::unloadONI(void)
	{
		m_pSensorWidget->stop();
		m_pSensorDevice = 0;
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		m_pSensorWidget->resetGLScene();

		m_IsConnected = false;
		m_ConnectAction->setEnabled( true );
		m_DisconnectAction->setEnabled( false );
		m_LoadONIAction->setEnabled( true );
		m_UnloadONIAction->setEnabled( false );

		statusBar()->showMessage( tr( "OpenNI video file unloaded" ), 2000 );
	}

	void MainWindow::set4To3(void)
	{
		m_pSensorWidget->getCamera()->m_AspectRatio = (4.0f / 3.0f);
		m_pSensorWidget->getCamera()->update();
		m_pSensorWidget->repaint();
	}

	void MainWindow::set16To9(void)
	{
		m_pSensorWidget->getCamera()->m_AspectRatio = (16.0f / 9.0f);
		m_pSensorWidget->getCamera()->update();
		m_pSensorWidget->repaint();
	}

	void MainWindow::loadBackgroundImage(void)
	{
		/*
		QString fileName = QFileDialog::getOpenFileName( this, tr( "Open image file" ), ".",
			tr( "BMP (*.bmp);;GIF (*.gif);;JPEG (*.jpg *.jpeg);;PNG (*.png);;PBM (*.pbm);;PGM (*.pgm);;PPM (*.ppm);;TIFF (*.tief);;XBM (*.xbm);;XPM (*.xpm)" ) );
		if(!fileName.isEmpty())
		{
			QImage image( fileName );
			if(!image.isNull())
			{
				m_pSensorWidget->getGLScene()->setBackgroundTexture(
					image.width(),
					image.height(),
					image.convertToFormat( QImage::Format_RGB888 ).bits()
				);
				m_pSensorWidget->repaint();
			}
		}
		*/
		loadBackgroundVideo();
	}

	void MainWindow::loadBackgroundVideo(void)
	{	
		QString fileName = QFileDialog::getOpenFileName( this, tr( "Open Video file" ), ".",
			tr( "AVI (*.avi);; MP4 (*.mp4);; MPEG (*.mpeg);; *.* (*.*)" ) );
		if(!fileName.isEmpty())
		{		
			m_pSensorWidget->getGLScene()->setVideoPath(fileName.toStdString());		
		}
	}

	void MainWindow::switchBackground(void)
	{
		if(m_BackgroundOnButton->isChecked() && !m_pSensorWidget->getGLScene()->getBackground())
		{
			m_pSensorWidget->getGLScene()->switchBackround();
			m_pSensorWidget->repaint();
		}

		if(m_BackgroundOffButton->isChecked() && m_pSensorWidget->getGLScene()->getBackground())
		{
			m_pSensorWidget->getGLScene()->switchBackround();
			m_pSensorWidget->repaint();
		}
	}

	void MainWindow::nearThreshold( int nearThreshold )
	{
		if((nearThreshold * 10) <= m_pSensorWidget->getGLScene()->getFarThreshold())
		{
			m_pSensorWidget->getGLScene()->setNearThreshold( nearThreshold * 10 );
			m_NearValueLabel->setText( QString::number( nearThreshold ).append( " cm" ) );
			m_pSensorWidget->repaint();
		}
		else
		{
			m_NearThresholdSlider->setValue( m_pSensorWidget->getGLScene()->getNearThreshold() / 10 );
		}
	}

	void MainWindow::farThreshold( int farThreshold )
	{
		if((farThreshold * 10) >= m_pSensorWidget->getGLScene()->getNearThreshold())
		{
			m_pSensorWidget->getGLScene()->setFarThreshold( farThreshold * 10 );
			m_FarValueLabel->setText( QString::number( farThreshold ).append( " cm" ) );
			m_pSensorWidget->repaint();
		}
		else
		{
			m_FarThresholdSlider->setValue( m_pSensorWidget->getGLScene()->getFarThreshold() / 10 );
		}
	}

	void MainWindow::cameraUp(void)
	{
		m_pSensorWidget->getCamera()->addToCamera( 0.0f,  m_HeadMove, 0.0f );
		m_pSensorWidget->repaint();
	}

	void MainWindow::cameraDown(void)
	{
		m_pSensorWidget->getCamera()->addToCamera( 0.0f, -m_HeadMove, 0.0f );
		m_pSensorWidget->repaint();
	}

	void MainWindow::cameraReset(void)
	{
		m_pSensorWidget->getGLScene()->resetCamera();
		m_pSensorWidget->repaint();
	}

	void MainWindow::textureMode(void)
	{
		if(m_TextureModeOnButton->isChecked() && !m_pSensorWidget->getGLScene()->getTextureMode())
		{
			m_pSensorWidget->getGLScene()->switchTextureMode();
			m_pSensorWidget->repaint();
		}

		if(m_TextureModeOffButton->isChecked() && m_pSensorWidget->getGLScene()->getTextureMode())
		{
			m_pSensorWidget->getGLScene()->switchTextureMode();
			m_pSensorWidget->repaint();
		}
	}

	void MainWindow::sensorUpdate(void)
	{
		if(m_SensorUpdateOn->isChecked() && !m_pSensorWidget->getSensorUpdate())
		{
			m_pSensorWidget->switchSensorUpdate();
		}

		if(m_SensorUpdateOff->isChecked() && m_pSensorWidget->getSensorUpdate())
		{
			m_pSensorWidget->switchSensorUpdate();
		}
	}

	void MainWindow::translateUp(void)
	{
		m_pSensorWidget->getGLScene()->translate( 0.0f, m_HeadMove, 0.0f );
		m_pSensorWidget->repaint();
	}

	void MainWindow::translateDown(void)
	{
		m_pSensorWidget->getGLScene()->translate( 0.0f, -m_HeadMove, 0.0f );
		m_pSensorWidget->repaint();
	}

	void MainWindow::translateLeft(void)
	{
		m_pSensorWidget->getGLScene()->translate( -m_HeadMove, 0.0f, 0.0f );
		m_pSensorWidget->repaint();
	}

	void MainWindow::translateRight(void)
	{
		m_pSensorWidget->getGLScene()->translate( m_HeadMove, 0.0f, 0.0f );
		m_pSensorWidget->repaint();
	}

	void MainWindow::translateReset(void)
	{
		m_pSensorWidget->getGLScene()->resetModel();
	
		m_pSensorWidget->getGLScene()->setRotation( 0.0f, 0.0f, 0.0f );
		m_RotateXSlider->setValue( 0 );
		m_RotateXValueLabel->setText( "  0°" );

		m_pSensorWidget->getGLScene()->setRotation( 0.0f, 0.0f, 0.0f );
		m_RotateYSlider->setValue( 0 );
		m_RotateYValueLabel->setText( "  0°" );

		m_pSensorWidget->getGLScene()->setRotation( 0.0f, 0.0f, 0.0f );
		m_RotateZSlider->setValue( 0 );
		m_RotateZValueLabel->setText( "  0°" );
	
		m_pSensorWidget->repaint();
	}

	void MainWindow::reset(void)
	{
		m_pSensorWidget->getGLScene()->resetCamera();
		m_pSensorWidget->getGLScene()->resetModel();

		m_pSensorWidget->getGLScene()->setRotation( 0.0f, 0.0f, 0.0f );
		m_RotateXSlider->setValue( 0 );
		m_RotateXValueLabel->setText( "  0°" );

		m_pSensorWidget->getGLScene()->setRotation( 0.0f, 0.0f, 0.0f );
		m_RotateYSlider->setValue( 0 );
		m_RotateYValueLabel->setText( "  0°" );

		m_pSensorWidget->getGLScene()->setRotation( 0.0f, 0.0f, 0.0f );
		m_RotateZSlider->setValue( 0 );
		m_RotateZValueLabel->setText( "  0°" );

		m_pSensorWidget->repaint();
	}

	void MainWindow::rotateX( int angle )
	{
		m_RotateXValueLabel->setText( QString::number( angle ).append( "°" ) );
		m_pSensorWidget->getGLScene()->setRotation( (double) angle * DEG_TO_RAD, (double) m_RotateYSlider->value() * DEG_TO_RAD, (double) m_RotateZSlider->value() * DEG_TO_RAD );
		m_pSensorWidget->repaint();
	}

	void MainWindow::rotateY( int angle )
	{
		m_RotateYValueLabel->setText( QString::number( angle ).append( "°" ) );
		m_pSensorWidget->getGLScene()->setRotation( (double) m_RotateXSlider->value() * DEG_TO_RAD, (double) angle * DEG_TO_RAD, (double) m_RotateZSlider->value() * DEG_TO_RAD );
		m_pSensorWidget->repaint();
	}

	void MainWindow::rotateZ( int angle )
	{
		m_RotateZValueLabel->setText( QString::number( angle ).append( "°" ) );
		m_pSensorWidget->getGLScene()->setRotation( (double) m_RotateXSlider->value() * DEG_TO_RAD, (double) m_RotateYSlider->value() * DEG_TO_RAD, (double) angle * DEG_TO_RAD );
		m_pSensorWidget->repaint();
	}

	void MainWindow::motorUp(void)
	{
		if(m_IsConnected)
		{
			m_MotorAngle++;
			if(m_MotorAngle > 30) m_MotorAngle = 30;
			m_pSensorDevice->controlMotor( m_MotorAngle );
			m_MotorControlLabel->setText( QString::number( m_MotorAngle ).append( "°" ) );
		}
	}

	void MainWindow::motorDown(void)
	{
		if(m_IsConnected)
		{
			m_MotorAngle--;
			if(m_MotorAngle < -30) m_MotorAngle = -30;
			m_pSensorDevice->controlMotor( m_MotorAngle );
			m_MotorControlLabel->setText( QString::number( m_MotorAngle ).append( "°" ) );
		}
	}

	void MainWindow::motorReset(void)
	{
		if(m_IsConnected)
		{
			m_MotorAngle = 0;
			m_pSensorDevice->controlMotor( m_MotorAngle );
			m_MotorControlLabel->setText( QString::number( m_MotorAngle ).append( "°" ) );
		}
	}

	void MainWindow::createActions(void)
	{
		// Hinzufuegen der Connect-Action:
		m_ConnectAction = new QAction( tr( "&Connect" ), this );
		m_ConnectAction->setStatusTip( tr( "Connect to Sensor device" ) );
		connect( m_ConnectAction, SIGNAL( triggered() ), this, SLOT( connectToSensorDevice() ) );

		// Hinzufuegen der Disconnect-Action:
		m_DisconnectAction = new QAction( tr( "&Disconnect" ), this );
		m_DisconnectAction->setStatusTip( tr( "Disconnects for Sensor device" ) );
		connect( m_DisconnectAction, SIGNAL( triggered() ), this, SLOT( disconnect() ) );
	
		// Hinzufuegen der Load-Action:
		m_LoadONIAction = new QAction( tr( "&Load ONI" ), this );
		m_LoadONIAction->setShortcut( QKeySequence::Open );
		m_LoadONIAction->setStatusTip( tr( "Load a exist OpenNI video file" ) );
		connect( m_LoadONIAction, SIGNAL( triggered() ), this, SLOT( loadONI() ) );

		// Hinzufuegen der Unload-Action:
		m_UnloadONIAction = new QAction( tr( "&Unload ONI" ), this );
		m_UnloadONIAction->setStatusTip( tr( "Unload OpenNI video file" ) );
		connect( m_UnloadONIAction, SIGNAL( triggered() ), this, SLOT( unloadONI() ) );

		// Hinzufuegen der Close-Action:
		m_CloseAction = new QAction( tr( "&Exit" ), this );
		m_CloseAction->setShortcut( tr( "Ctrl+Q" ) );
		m_CloseAction->setStatusTip( tr( "Exit the application" ) );
		connect( m_CloseAction, SIGNAL( triggered() ), this, SLOT( close() ) );

		m_4to3Action = new QAction( tr( "&4 : 3" ), this );
		m_4to3Action->setStatusTip( tr( "Set camera to 4 : 3" ) );
		connect( m_4to3Action, SIGNAL( triggered() ), this, SLOT( set4To3() ) );

		m_16to9Action = new QAction( tr( "&16 : 9" ), this );
		m_16to9Action->setStatusTip( tr( "Set camera to 16 : 9" ) );
		connect( m_16to9Action, SIGNAL( triggered() ), this, SLOT( set16To9() ) );

		m_LoadImageAction = new QAction( tr( "&Load Image" ), this );
		m_LoadImageAction->setStatusTip( tr( "Load a background image" ) );
		connect( m_LoadImageAction, SIGNAL( triggered() ), this, SLOT( loadBackgroundImage() ) );
		/*
		m_LoadVideoAction = new QAction( tr( "&Load Video" ), this );
		m_LoadVideoAction->setStatusTip( tr( "Load a background video" ) );
		connect( m_LoadVideoAction, SIGNAL( triggered() ), this, SLOT( loadBackgroundVideo() ) );
		*/

		m_ConnectAction->setEnabled( true );
		m_DisconnectAction->setEnabled( false );
		m_LoadONIAction->setEnabled( true );
		m_UnloadONIAction->setEnabled( false );
	}

	void MainWindow::createMenus(void)
	{
		m_FileMenu = menuBar()->addMenu( tr( "&File" ) );
		m_FileMenu->addAction( m_ConnectAction  );
		m_FileMenu->addAction( m_DisconnectAction );
		m_FileMenu->addSeparator();
		m_FileMenu->addAction( m_LoadONIAction );
		m_FileMenu->addAction( m_UnloadONIAction );
		m_FileMenu->addSeparator();
		m_FileMenu->addAction( m_CloseAction );

		m_CameraMenu = menuBar()->addMenu( tr( "&Camera" ) );
		m_CameraMenu->addAction( m_4to3Action );
		m_CameraMenu->addAction( m_16to9Action );

		m_BackgroundMenu = menuBar()->addMenu( tr( "&Background" ) );
		m_BackgroundMenu->addAction( m_LoadImageAction );
		//m_BackgroundMenu->addAction( m_LoadVideoAction );
	}

	void MainWindow::createGUI(void)
	{
		////////////////////////
		// Depth segmentation //
		////////////////////////
		m_NearThresholdLabel = new QLabel( tr( "Near Threshold:" ) );
		m_NearThresholdSlider = new QSlider( Qt::Horizontal );
		m_NearThresholdSlider->setRange( 50, 400 );
		m_NearThresholdSlider->setSingleStep( 10 );
		m_NearThresholdSlider->setPageStep( 10 );
		m_NearThresholdSlider->setTickInterval( 10 );
		m_NearThresholdSlider->setTickPosition( QSlider::TicksRight );
		m_NearThresholdSlider->setValue( 50 );
		m_NearThresholdSlider->setFocusPolicy( Qt::NoFocus );
		connect( m_NearThresholdSlider, SIGNAL( valueChanged( int ) ), this, SLOT( nearThreshold( int ) ) );
		m_NearValueLabel = new QLabel( tr( " 50 cm" ) );
		m_NearValueLabel->setAlignment( Qt::AlignRight );
		m_NearValueLabel->setFixedWidth( 35 );

		m_FarThresholdLabel = new QLabel( tr( "Far Threshold:" ) );
		m_FarThresholdSlider = new QSlider( Qt::Horizontal );
		m_FarThresholdSlider->setRange( 50, 400 );
		m_FarThresholdSlider->setSingleStep( 10 );
		m_FarThresholdSlider->setPageStep( 10 );
		m_FarThresholdSlider->setTickInterval( 10 );
		m_FarThresholdSlider->setTickPosition( QSlider::TicksRight );
		m_FarThresholdSlider->setValue( 80 );
		m_FarThresholdSlider->setFocusPolicy( Qt::NoFocus );
		connect( m_FarThresholdSlider, SIGNAL( valueChanged( int ) ), this, SLOT( farThreshold( int ) ) );
		m_FarValueLabel	= new QLabel( tr( " 80 cm" ) );
		m_FarValueLabel->setAlignment( Qt::AlignRight );
		m_FarValueLabel->setFixedWidth( 35 );

		QGridLayout* pThresholdLayout = new QGridLayout();
		pThresholdLayout->addWidget( m_NearThresholdLabel, 0, 0 );
		pThresholdLayout->addWidget( m_NearThresholdSlider, 0, 1 );
		pThresholdLayout->addWidget( m_NearValueLabel, 0, 2 );	
		pThresholdLayout->addWidget( m_FarThresholdLabel, 1, 0 );
		pThresholdLayout->addWidget( m_FarThresholdSlider, 1, 1 );
		pThresholdLayout->addWidget( m_FarValueLabel, 1, 2 );

		m_ThresholdControlGroup = new QGroupBox( tr( "Depth Segmentation" ) );
		m_ThresholdControlGroup->setLayout( pThresholdLayout );

		////////////////////
		// Camera control //
		////////////////////
		m_CameraUpButton = new QPushButton( tr( "Up" ) );
		m_CameraUpButton->setFocusPolicy( Qt::NoFocus );
		connect( m_CameraUpButton, SIGNAL( pressed() ), this, SLOT( cameraUp() ) );
		m_CameraDownButton = new QPushButton( tr( "Down" ) );
		m_CameraDownButton->setFocusPolicy( Qt::NoFocus );
		connect( m_CameraDownButton, SIGNAL( pressed() ), this, SLOT( cameraDown() ) );
		m_CameraResetButton = new QPushButton( tr( "Reset" ) );
		m_CameraResetButton->setFocusPolicy( Qt::NoFocus );
		connect( m_CameraResetButton, SIGNAL( clicked() ), this, SLOT( cameraReset() ) );

		QGridLayout* pCameraLayout = new QGridLayout();
		pCameraLayout->addWidget( m_CameraUpButton, 0, 0 );
		pCameraLayout->addWidget( m_CameraResetButton, 1, 0 );
		pCameraLayout->addWidget( m_CameraDownButton, 2, 0 );

		m_CameraControlGroup = new QGroupBox( tr( "Camera" ) );
		m_CameraControlGroup->setLayout( pCameraLayout );

		/////////////////////
		// Background mode //
		/////////////////////
		m_BackgroundOnButton = new QRadioButton( tr( "On" ) );
		m_BackgroundOnButton->setFocusPolicy( Qt::NoFocus );
		connect( m_BackgroundOnButton, SIGNAL( clicked( bool ) ), this, SLOT( switchBackground() ) );
		m_BackgroundOffButton = new QRadioButton( tr( "Off" ) );
		m_BackgroundOffButton->setFocusPolicy( Qt::NoFocus );
		connect( m_BackgroundOffButton, SIGNAL( clicked( bool ) ), this, SLOT( switchBackground() ) );
		m_BackgroundOnButton->setChecked( true );
		m_BackgroundOffButton->setChecked( false );

		QGridLayout* pBackgroundLayout = new QGridLayout();
		pBackgroundLayout->addWidget( m_BackgroundOnButton, 0, 0 );
		pBackgroundLayout->addWidget( m_BackgroundOffButton, 1, 0 );
	
		m_BackgroundControlGroup = new QGroupBox( tr( "Background Plane" ) );
		m_BackgroundControlGroup->setLayout( pBackgroundLayout );

		/////////////////
		// Texturemode //
		/////////////////
		m_TextureModeOnButton = new QRadioButton( tr( "Camera" ) );
		m_TextureModeOnButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TextureModeOnButton, SIGNAL( clicked( bool ) ), this, SLOT( textureMode() ) );
		m_TextureModeOffButton = new QRadioButton( tr( "Depth Map" ) );
		m_TextureModeOffButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TextureModeOffButton, SIGNAL( clicked( bool ) ), this, SLOT( textureMode() ) );
		m_TextureModeOnButton->setChecked( true );
		m_TextureModeOffButton->setChecked( false );

		QGridLayout* pTextureLayout = new QGridLayout();
		pTextureLayout->addWidget( m_TextureModeOnButton, 0, 0 );
		pTextureLayout->addWidget( m_TextureModeOffButton, 1, 0 );
	
		m_TextureModeControlGroup = new QGroupBox( tr( "Texture Mode" ) );
		m_TextureModeControlGroup->setLayout( pTextureLayout );

		///////////////////
		// Sensor update //
		///////////////////
		m_SensorUpdateOn = new QRadioButton( tr( "On" ), this );
		m_SensorUpdateOn->setFocusPolicy( Qt::NoFocus );
		connect( m_SensorUpdateOn, SIGNAL( clicked( bool ) ), this, SLOT( sensorUpdate() ) );
		m_SensorUpdateOff = new QRadioButton( tr( "Off" ), this );
		m_SensorUpdateOff->setFocusPolicy( Qt::NoFocus );
		connect( m_SensorUpdateOff, SIGNAL( clicked( bool ) ), this, SLOT( sensorUpdate() ) );
		m_SensorUpdateOn->setChecked( true );
		m_SensorUpdateOff->setChecked( false );
	
		QGridLayout* pSensorLayout = new QGridLayout();
		pSensorLayout->addWidget( m_SensorUpdateOn, 0, 0 );
		pSensorLayout->addWidget( m_SensorUpdateOff, 1, 0 );

		m_SensorUpdateControlGroup = new QGroupBox( tr( "Sensor Update" ) );
		m_SensorUpdateControlGroup->setLayout( pSensorLayout );

		///////////////////////
		// Head translations //
		///////////////////////
		m_TranslateUpButton = new QPushButton( tr( "Up" ), this );
		m_TranslateUpButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TranslateUpButton, SIGNAL( pressed() ), this, SLOT( translateUp() ) );
		m_TranslateDownButton = new QPushButton( tr( "Down" ), this );
		m_TranslateDownButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TranslateDownButton, SIGNAL( pressed() ), this, SLOT( translateDown() ) );
		m_TranslateLeftButton = new QPushButton( tr( "Left" ), this );
		m_TranslateLeftButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TranslateLeftButton, SIGNAL( pressed() ), this, SLOT( translateLeft() ) );
		m_TranslateRightButton = new QPushButton( tr( "Right" ), this );
		m_TranslateRightButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TranslateRightButton, SIGNAL( pressed() ), this, SLOT( translateRight() ) );
		m_TranslateResetButton = new QPushButton( tr( "Reset" ), this );
		m_TranslateResetButton->setFocusPolicy( Qt::NoFocus );
		connect( m_TranslateResetButton, SIGNAL( clicked() ), this, SLOT( translateReset() ) );

		QGridLayout* pTranslateLayout = new QGridLayout();
		pTranslateLayout->addWidget( m_TranslateUpButton, 0, 1 );
		pTranslateLayout->addWidget( m_TranslateLeftButton, 1, 0 );
		pTranslateLayout->addWidget( m_TranslateResetButton, 1, 1 );
		pTranslateLayout->addWidget( m_TranslateRightButton, 1, 2 );
		pTranslateLayout->addWidget( m_TranslateDownButton, 2, 1 );

		m_TranslateControlGroup = new QGroupBox( tr( "Head Movements" ) );
		m_TranslateControlGroup->setLayout( pTranslateLayout );

		////////////////////
		// Complete reset //
		////////////////////
		m_ResetButton = new QPushButton( tr( "Complete Reset" ), this );
		m_ResetButton->setFocusPolicy( Qt::NoFocus );
		connect( m_ResetButton, SIGNAL( clicked() ), this, SLOT( reset() ) );

		////////////////////
		// Head rotations //
		////////////////////
		m_RotateXSlider = new QSlider( Qt::Horizontal, this );
		m_RotateXSlider->setRange( -360, 360 );
		m_RotateXSlider->setSingleStep( 1 );
		m_RotateXSlider->setPageStep( 10 );
		m_RotateXSlider->setTickInterval( 18 );
		m_RotateXSlider->setTickPosition( QSlider::TicksRight );
		m_RotateXSlider->setValue( 0 );
		m_RotateXSlider->setFocusPolicy( Qt::NoFocus );
		connect( m_RotateXSlider, SIGNAL( valueChanged( int ) ), this, SLOT( rotateX( int ) ) );
		m_RotateXLabel = new QLabel( tr( "X-Axis:" ) );
		m_RotateXValueLabel = new QLabel( tr( "0°" ) );
		m_RotateXValueLabel->setFixedWidth( 25 );
		m_RotateXValueLabel->setAlignment( Qt::AlignRight );

		m_RotateYSlider = new QSlider( Qt::Horizontal, this );
		m_RotateYSlider->setRange( -360, 360 );
		m_RotateYSlider->setSingleStep( 1 );
		m_RotateYSlider->setPageStep( 10 );
		m_RotateYSlider->setTickInterval( 18 );
		m_RotateYSlider->setTickPosition( QSlider::TicksRight );
		m_RotateYSlider->setValue( 0 );
		m_RotateYSlider->setFocusPolicy( Qt::NoFocus );
		connect( m_RotateYSlider, SIGNAL( valueChanged( int ) ), this, SLOT( rotateY( int ) ) );
		m_RotateYLabel = new QLabel( tr( "Y-Axis:" ) );
		m_RotateYValueLabel = new QLabel( tr( "0°" ) );
		m_RotateYValueLabel->setFixedWidth( 25 );
		m_RotateYValueLabel->setAlignment( Qt::AlignRight );

		m_RotateZSlider = new QSlider( Qt::Horizontal, this );
		m_RotateZSlider->setRange( -360, 360 );
		m_RotateZSlider->setSingleStep( 1 );
		m_RotateZSlider->setPageStep( 10 );
		m_RotateZSlider->setTickInterval( 18 );
		m_RotateZSlider->setTickPosition( QSlider::TicksRight );
		m_RotateZSlider->setValue( 0 );
		m_RotateZSlider->setFocusPolicy( Qt::NoFocus );
		connect( m_RotateZSlider, SIGNAL( valueChanged( int ) ), this, SLOT( rotateZ( int ) ) );
		m_RotateZLabel = new QLabel( tr( "Z-Axis:" ) );
		m_RotateZValueLabel = new QLabel( tr( "0°" ) );
		m_RotateZValueLabel->setFixedWidth( 25 );
		m_RotateZValueLabel->setAlignment( Qt::AlignRight );

		QGridLayout* pRotateLayout = new QGridLayout();
		pRotateLayout->addWidget( m_RotateXLabel, 0, 0 );
		pRotateLayout->addWidget( m_RotateXSlider, 0, 1 );
		pRotateLayout->addWidget( m_RotateXValueLabel, 0, 2 );
		pRotateLayout->addWidget( m_RotateYLabel, 1, 0 );
		pRotateLayout->addWidget( m_RotateYSlider, 1, 1 );
		pRotateLayout->addWidget( m_RotateYValueLabel, 1, 2 );
		pRotateLayout->addWidget( m_RotateZLabel, 2, 0 );
		pRotateLayout->addWidget( m_RotateZSlider, 2, 1 );
		pRotateLayout->addWidget( m_RotateZValueLabel, 2, 2 );

		m_RotateControlGroup = new QGroupBox( tr( "Head Rotations" ) );
		m_RotateControlGroup->setLayout( pRotateLayout );

		//////////////////////////
		// Sensor motor control //
		//////////////////////////
		m_MotorUpButton = new QPushButton( tr( "Up" ), this );
		m_MotorUpButton->setFocusPolicy( Qt::NoFocus );
		connect( m_MotorUpButton, SIGNAL( pressed() ), this, SLOT( motorUp() ) );
		m_MotorDownButton = new QPushButton( tr( "Down" ), this );
		m_MotorDownButton->setFocusPolicy( Qt::NoFocus );
		connect( m_MotorDownButton, SIGNAL( pressed() ), this, SLOT( motorDown() ) );
		m_MotorResetButton = new QPushButton( tr( "Reset" ), this );
		m_MotorResetButton->setFocusPolicy( Qt::NoFocus );
		connect( m_MotorResetButton, SIGNAL( clicked() ), this, SLOT( motorReset() ) );
		m_MotorControlLabel = new QLabel( tr( "0°" ) );

		QGridLayout* pMotorLayout = new QGridLayout();
		pMotorLayout->addWidget( m_MotorUpButton, 0, 0 );
		pMotorLayout->addWidget( m_MotorResetButton, 0, 1 );
		pMotorLayout->addWidget( m_MotorDownButton, 1, 0 );
		pMotorLayout->addWidget( m_MotorControlLabel, 1, 1, Qt::AlignCenter );

		m_MotorControlGroup = new QGroupBox( tr( "Motor Control" ) );
		m_MotorControlGroup->setLayout( pMotorLayout );

		m_pSensorWidget = new SensorGLWidget( m_Width, m_Height, this );

		QGridLayout* pMainLayout = new QGridLayout();
		pMainLayout->addWidget( m_ThresholdControlGroup, 0, 0, 1, 3 );
		pMainLayout->addWidget( m_MotorControlGroup, 1, 1, 1, 2 );
		pMainLayout->addWidget( m_SensorUpdateControlGroup, 2, 2 );
		pMainLayout->addWidget( m_pSensorWidget, 1, 0, 5, 1 );
		pMainLayout->addWidget( m_CameraControlGroup, 3, 1, 1, 2 );
		pMainLayout->addWidget( m_TextureModeControlGroup, 2, 1 );
		pMainLayout->addWidget( m_TranslateControlGroup, 4, 1, 1, 2 );
		pMainLayout->addWidget( m_BackgroundControlGroup, 5, 1 );
		pMainLayout->addWidget( m_ResetButton, 5, 2, Qt::AlignCenter );
		pMainLayout->addWidget( m_RotateControlGroup, 6, 0, 1, 3 );	

		m_CentralWidget = new QWidget( this );
		m_CentralWidget->setLayout( pMainLayout );
		setCentralWidget( m_CentralWidget );	
		setWindowTitle( "DirectLook" );
	}
}
