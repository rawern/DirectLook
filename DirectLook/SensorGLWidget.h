#pragma once

#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include <QTime>
#include <QMessageBox>

#include <iostream>

#include "Sensor/SensorOpenNI.h"
#include "OpenGL/GLScene.h"
#include "OpenGL/GLCamera.h"
#include "OpenGL/Shader.h"


namespace DirectLook
{
	class SensorGLWidget : public QGLWidget 
	{
		Q_OBJECT

	private:
		SensorOpenNI* m_pSensorDevice;	///< OpenNI Sensor driver
		GLScene* m_pGLScene;			///< OpenGL scene
		GLCamera* m_pCamera;			///< Virtual camera
		Shader* m_pShader;				///< Shader programm for DirectLook
		bool m_SensorUpdate;			///< Sensor update on or off
		QPoint m_LastMousePosition;		///< Last mouse position
		QTimer* m_pTimer;				///< Timer for render and Sensor update process

	public:
		// Constructor
		SensorGLWidget( unsigned int width, unsigned int height, QWidget* parent = 0 );
	
		// Destructor
		~SensorGLWidget(void);

		// Start the render and Sensor update process
		bool start( unsigned int fps );

		// Stop the render and Sensor update process
		void stop(void);

		// Get the GLScene object as normal pointer
		GLScene* getGLScene(void);

		// Get the camera object as normal pointer
		GLCamera* getCamera(void);

		// Set Sensor update on or off
		void switchSensorUpdate(void);

		// Get the status if the Sensor update process on or off
		bool getSensorUpdate(void) const;

		// Set a new Sensor device
		void setSensorDevice( SensorOpenNI* pSensorDevice );

		void resetGLScene(void);

	protected:
		void initializeGL(void);
		void paintGL(void);
		void mousePressEvent( QMouseEvent* event );
		void mouseMoveEvent( QMouseEvent* event );

	private:
		void initialize(void);

	private slots:
		void sensorUpdate(void);
	};
}
