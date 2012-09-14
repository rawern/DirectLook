#pragma once

#include <XnUSB.h>
#include <stdio.h>
#include <time.h>

namespace DirectLook 
{
	/// \brief Die Klasse Kinect-Motor ist fuer die Steuerung des Motors ueber den OpenNI-Treiber zustaendig.
	class KinectMotor 
	{
	
	public: 
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein neues Kinect-Motor-Objekt.
		///
		////////////////////////////////////////////////////////////
		KinectMotor(void); 

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		////////////////////////////////////////////////////////////
		virtual ~KinectMotor(void); 

		////////////////////////////////////////////////////////////
		/// \brief Stellt eine Verbindung zum Kinect-Motor ueber den OpenNI-Treiber her.
		///
		/// \return War die Verbindung erfolgreich: true, ansonsten false
		///
		////////////////////////////////////////////////////////////
		bool open(void); 

		////////////////////////////////////////////////////////////
		/// \brief Trennt die Verbindung zum Kinect-Motor.
		////////////////////////////////////////////////////////////
		void close(void); 

		////////////////////////////////////////////////////////////
		/// \brief Steuert den Kinect-Motor mit dem uebergebenen Winkel in der Einheit Grad.
		///
		/// Der Winkel muss im einem Wertebereich zwischen -30 ° und +30 ° angegeben werden.
		/// Betraegt der Wert ueber +30 °, wird der Motor auf +30 ° justiert.
		/// Betraegt der Wert unter -30 °, wird der Motor auf -30 ° justiert.
		///
		/// \param angle Winkel in der Einheit Grad
		///
		/// \return True wenn erfolgreisch, ansonsten false 
		///
		////////////////////////////////////////////////////////////
		bool move( int angle ); 

	private: 
		XN_USB_DEV_HANDLE m_Device;	///< Sensor-Device-Objekt
		bool m_IsOpen;				///< Wurde eine Verbindung zum Kinect-Motor hergestellt?
	};
};
