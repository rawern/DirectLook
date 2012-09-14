#pragma once

#include "../NonCopyable.h"
#include "../Image/DepthImage.h"
#include "../Image/RGBImage.h"
#include "AudioStream.h"

namespace DirectLook
{
	/// \brief Die Schnittstelle Sensor-Interface repraesentiert eine abstrakte Treiberschnittstelle zur Sensor-Hardware.
	class ISensorInterface : public NonCopyable 
	{

	public:
		////////////////////////////////////////////////////////////
		/// \brief Stellt eine Verbindung zur Sensor-Hardware her.
		////////////////////////////////////////////////////////////
		virtual bool connect(void) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Trennt die Verbindung zur Sensor-Hardware.
		////////////////////////////////////////////////////////////
		virtual void close(void) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Liest die aktuellen Daten des Tiefensensors der Sensor-Hardware aus und aktualisiert das Sensor-Image-Opjekt.
		///
		/// \param DepthImage Sensor-Image-Objekt
		///
		////////////////////////////////////////////////////////////
		virtual void getSegmentedDepthImage( DepthImage* DepthImage ) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Liest die aktuellen Daten der RGB-Kamera der Sensor-Hardware und aktualisiert das Camera-Image-Objekt.
		///
		/// \param RGBImage Camera-Image-Objekt
		///
		////////////////////////////////////////////////////////////
		virtual void getRgbMapImage( RGBImage* RGBImage ) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Liest die aktuellen Audio-Stream Daten der Sensor-Hardware und aktualisiert das Audio-Stream-Objekt.
		///
		/// \param audioStream Audio-Stream-Objekt
		///
		////////////////////////////////////////////////////////////
		virtual void getAudioStream( AudioStream* audioStream ) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Steuert den Kinect-Motor mit dem uebergebenen Winkel in der Einheit Grad.
		///
		/// Der Winkel muss im einem Wertebereich zwischen -30 ° und +30 ° angegeben werden.
		/// Betraegt der Wert ueber +30 °, wird der Motor auf +30 ° justiert.
		/// Betraegt der Wert unter -30 °, wird der Motor auf -30 ° justiert.
		///
		/// \param angle Winkel in der Einheit Grad
		/// 
		////////////////////////////////////////////////////////////
		virtual void controlMotor( const double angle ) = 0;
	};
};

