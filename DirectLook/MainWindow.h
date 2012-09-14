#pragma once

#include <Qt>
#include <QObject>
#include <QtGui>
#include <QtGui/QMainWindow>
#include "SensorGLWidget.h"

namespace DirectLook
{
	class MainWindow : public QMainWindow 
	{
		Q_OBJECT

	private:
		double m_MotorAngle;
		float m_HeadMove;
		float m_RotateAngle;

		unsigned int m_Width;
		unsigned int m_Height;

		SensorOpenNI* m_pSensorDevice;
		SensorGLWidget* m_pSensorWidget;
		bool m_IsConnected;

		/////////////////////////
		// Qt Control elements //
		/////////////////////////

		// Background mode control:
		QGroupBox*    m_BackgroundControlGroup;
		QRadioButton* m_BackgroundOnButton;
		QRadioButton* m_BackgroundOffButton;

		// Depth segmentation controls:
		QGroupBox* m_ThresholdControlGroup;
		QLabel*    m_NearThresholdLabel;
		QLabel*    m_FarThresholdLabel;
		QSlider*   m_NearThresholdSlider;
		QSlider*   m_FarThresholdSlider;
		QLabel*    m_NearValueLabel;
		QLabel*    m_FarValueLabel;

		// Camera controls:
		QGroupBox*	 m_CameraControlGroup;
		QPushButton* m_CameraUpButton;
		QPushButton* m_CameraDownButton;
		QPushButton* m_CameraResetButton;

		// Texture mode control:
		QGroupBox*    m_TextureModeControlGroup;
		QRadioButton* m_TextureModeOnButton;
		QRadioButton* m_TextureModeOffButton;

		// Sensor update control:
		QGroupBox*    m_SensorUpdateControlGroup;
		QRadioButton* m_SensorUpdateOn;
		QRadioButton* m_SensorUpdateOff;

		// Head translate controls:
		QGroupBox*	 m_TranslateControlGroup;
		QPushButton* m_TranslateUpButton;
		QPushButton* m_TranslateDownButton;
		QPushButton* m_TranslateLeftButton;
		QPushButton* m_TranslateRightButton;
		QPushButton* m_TranslateResetButton;
	
		// Complete reset button:
		QPushButton* m_ResetButton;

		// Head rotate controls:
		QGroupBox* m_RotateControlGroup;
		QLabel*    m_RotateXLabel;
		QLabel*    m_RotateYLabel;
		QLabel*    m_RotateZLabel;
		QSlider*   m_RotateXSlider;
		QSlider*   m_RotateYSlider;
		QSlider*   m_RotateZSlider;
		QLabel*    m_RotateXValueLabel;
		QLabel*    m_RotateYValueLabel;
		QLabel*    m_RotateZValueLabel;

		// Kinect motor controls:
		QGroupBox*	 m_MotorControlGroup;
		QPushButton* m_MotorUpButton;
		QPushButton* m_MotorDownButton;
		QPushButton* m_MotorResetButton;
		QLabel*		 m_MotorControlLabel;

		// Main window central widget:
		QWidget* m_CentralWidget;

		QMenu* m_FileMenu;
		QMenu* m_CameraMenu;
		QMenu* m_BackgroundMenu;

		QAction* m_ConnectAction;
		QAction* m_DisconnectAction;
		QAction* m_LoadONIAction;
		QAction* m_UnloadONIAction;
		QAction* m_CloseAction;
	
		QAction* m_4to3Action;
		QAction* m_16to9Action;

		QAction* m_LoadImageAction;
		QAction* m_LoadVideoAction;

	public:
		MainWindow(void);
	
	protected:
		void closeEvent( QCloseEvent* event );
		void keyPressEvent( QKeyEvent* event );

	private slots:
		// File menu controls:
		void connectToSensorDevice(void);
		void disconnect(void);
		bool loadONI(void);
		void unloadONI(void);

		// Camere menu controls:
		void set4To3(void);
		void set16To9(void);

		// Background menu controls:
		void loadBackgroundImage(void); //actually misused for the BackgroundVideo because the lazyness to recompile the gui with qt is too great
		void loadBackgroundVideo(void);

		// Background controls:
		void switchBackground(void);

		// Depth segmentation controls:
		void nearThreshold( int nearThreshold );
		void farThreshold( int farThreshold );

		// Camera control:
		void cameraUp(void);
		void cameraDown(void);
		void cameraReset(void);

		// Texturemode:
		void textureMode(void);

		// Sensor update:
		void sensorUpdate(void);

		// Head translations:
		void translateUp(void);
		void translateDown(void);
		void translateLeft(void);
		void translateRight(void);
		void translateReset(void);

		// Complete reset:
		void reset(void);

		// Head rotations:
		void rotateX( int angle );
		void rotateY( int angle );
		void rotateZ( int angle );

		// Kinect motor control:
		void motorUp(void);
		void motorDown(void);
		void motorReset(void);

	private:
		void createActions(void);
		void createMenus(void);
		void createGUI(void);
	};
}
