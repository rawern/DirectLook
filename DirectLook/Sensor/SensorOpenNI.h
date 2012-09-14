#pragma once

#include "../OpenGL/GLScene.h"
#include "ISensorInterface.h"
#include "KinectMotor.h"

#include <XnCppWrapper.h>
#include <iostream>
#include <string>

namespace DirectLook 
{
	/// \brief Die Klasse SensorOpenNI repraesentoert eine OpenNI-Treiberschnittstelle zur Sensor-Hardware.
	class SensorOpenNI : public ISensorInterface 
	{
	
	public:
		////////////////////////////////////////////////////////////
		/// \brief Konstructor A - Info: Die Oni-Datei muss existieren!
		///
		/// Erzeugt ein neues SensorOpenNI-Objekt.
		/// Als Datenquelle dient eine OpenNI-Video-Datei, die ueber den Dateipfad "videoFileName" angegeben wird.
		/// Ist der Dateipfad ungueltig, wird das Programm beendet und eine Fehlermeldung in der Konsole ausgegeben.
		///
		/// \param videoFileName Dateipfad zur OpenNI-Video-Datei
		///
		////////////////////////////////////////////////////////////
		SensorOpenNI( const XnChar* videoFileName );
	
		////////////////////////////////////////////////////////////
		/// \brief Konstructor B - Info: XML-Datei muss exexFile must exist!!!
		///
		/// Erzeugt ein neues SensorOpenNI-Objekt.
		/// Die Sensor-Hardware wird ueber eine XML-Datei initialisiert, die ueber den Dateipfad "configFileName" angegeben wird.
		/// Ist der Dateipfad ungueltig, wird das Programm beendet und eine Fehlermeldung in der Konsole ausgegeben.
		///
		/// \param configFileName Dateipfad zur XML-Datei
		/// \param mirrorMode     Sollen die Bilddaten der RGB-Kamera und des Tiefensensors gespiegelt werden?
		///
		////////////////////////////////////////////////////////////
		SensorOpenNI( const XnChar* configFileName, const bool mirrorMode );
	
		////////////////////////////////////////////////////////////
		/// \brief Konstructor C
		///
		/// Erzeugt ein neues SensorOpenNI-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param width	  Breite der RGB-Kamera und des Tiefensensors
		/// \param height	  Hoehe der RGB-Kamara und des Tiefensensors
		/// \param mirrorMode Sollen die Bilddaten der RGB-Kamera und des Tiefensensors gespiegelt werden?
		///
		////////////////////////////////////////////////////////////
		SensorOpenNI( const XnUInt32 width, const XnUInt32 height, const bool mirrorMode );

		////////////////////////////////////////////////////////////
		/// \brief Konstructor D
		///
		/// Erzeugt ein neues SensorOpenNI-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param cameraWidth	Breite der RGB-Kamera
		/// \param cameraHeight Hoehe der RGB-Kamara
		/// \param depthWidth	Breite des Tiefensensors
		/// \param depthHeight  Hoehe des Tiefensensors
		/// \param mirrorMode   Sollen die Bilddaten der RGB-Kamera und des Tiefensensors gespiegelt werden?
		///
		////////////////////////////////////////////////////////////
		SensorOpenNI( const XnUInt32 cameraWidth, const XnUInt32 cameraHeight, const XnUInt32 depthWidth, const XnUInt32 depthHeight, const bool mirrorMode );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		////////////////////////////////////////////////////////////
		virtual ~SensorOpenNI(void);
	
	
		/***** SensorInterface methods *****/
	
		////////////////////////////////////////////////////////////
		/// \brief Stellt eine Verbindung zur Sensor-Hardware her.
		////////////////////////////////////////////////////////////
		virtual bool connect(void);
	
		////////////////////////////////////////////////////////////
		/// \brief Trennt die Verbindung zur Sensor-Hardware.
		////////////////////////////////////////////////////////////
		virtual void close(void);

		////////////////////////////////////////////////////////////
		/// \brief Liest die aktuellen Daten des Tiefensensors der Sensor-Hardware aus und aktualisiert das Sensor-Image-Opjekt.
		///
		/// \param DepthImage Sensor-Image-Objekt
		///
		////////////////////////////////////////////////////////////
		virtual void getSegmentedDepthImage( DepthImage* DepthImage );
	
		////////////////////////////////////////////////////////////
		/// \brief Liest die aktuellen Daten der RGB-Kamera der Sensor-Hardware und aktualisiert das Camera-Image-Objekt.
		///
		/// \param RGBImage Camera-Image-Objekt
		///
		////////////////////////////////////////////////////////////
		virtual void getRgbMapImage( RGBImage* RGBImage );
		
		////////////////////////////////////////////////////////////
		/// \brief Liest die aktuellen Audio-Stream Daten der Sensor-Hardware und aktualisiert das Audio-Stream-Objekt.
		///
		/// \param audioStream Audio-Stream-Objekt
		///
		////////////////////////////////////////////////////////////
		virtual void getAudioStream( AudioStream* audioStream );

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
		virtual void controlMotor( const double angle );
	
	
		/***** SensorOpenNI methods *****/	
	
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Breite der RGB-Kamera Bilder zurueck.
		///
		/// \return Breite der RGB-Kamera Bilder
		///
		////////////////////////////////////////////////////////////
		XnUInt32 getCameraWidth(void) const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Hoehe der RGB-Kamera Bilder zurueck.
		///
		/// \return Hoehe der RGB-Kamera Bilder
		///
		////////////////////////////////////////////////////////////
		XnUInt32 getCameraHeight(void) const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Breite der Tiefensensor Bilder zurueck.
		///
		/// \return Breite der Tiefensensor Bilder
		///
		////////////////////////////////////////////////////////////
		XnUInt32 getDepthWidth(void) const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Hoehe der Tiefensensor Bilder zurueck.
		///
		/// \return Hoehe der Tiefensensor Bilder
		///
		////////////////////////////////////////////////////////////
		XnUInt32 getDepthHeight(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Anzahl der RGB-Kamera Pixel zurueck (m_CameraWidth * m_CameraHeight * 3).
		///
		/// \return Anzahl der RGB-Kamera pixel (m_CameraWidth * m_CameraHeight * 3)
		///
		////////////////////////////////////////////////////////////
		XnUInt32 getImageMapPixelSize(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Anzahl der Pixel des Tiefensensors zurueck (m_DepthWidth * m_DepthHeight).
		///
		/// \return Anzahl der Tiefenwertpixel (m_DepthWidth * m_DepthHeight)
		///
		////////////////////////////////////////////////////////////
		XnUInt32 getDepthMapPixelSize(void) const;
				
		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Kamera- und Tiefenwerte des GLScene-Objektes.
		///
		/// \param GLScene 3D-Kopf
		///
		////////////////////////////////////////////////////////////
		void getSensorData(	GLScene& GLScene );
		
	private:
		////////////////////////////////////////////////////////////
		/// \brief Zeigt den aktuellen Treiberstatus in der Konsole an.
		///
		/// \param message Statusmeldung
		/// \param error   Fehlermeldung
		///
		/// \return True alles in Ordnung - false bei einem Fehler
		///
		////////////////////////////////////////////////////////////
		bool printStatus( const char* message, const char* error );
	
		////////////////////////////////////////////////////////////
		/// \brief Initialisiert das OpenNI Kontext-Objekt.
		////////////////////////////////////////////////////////////
		void initialize(void);

		///////////////////////////////////
		// SensorOpenNI member variables //
		///////////////////////////////////

		const bool m_ConfigFlag;				///< Laedt die Treiber-Einstellungen ueber eine XML-Datei
		const bool m_VideoFlag;					///< Laedt die OpenNI-Daten ueber eine Oni-Datei
		const bool m_MirrorMode;				///< Sollen die Bilddaten der RGB-Kamera und des Tiefensensors gespiegelt werden?
		std::string m_ConfigFileName;			///< Dateipfad zur XML-Konfigurationsdatei
		std::string m_VideoFileName;			///< Dateipfad zur OpenNI Videodatei (Oni-Datei)
	
		XnUInt32 m_CameraWidth;					///< Breite der RGB-Kamera Bilder
		XnUInt32 m_CameraHeight;				///< Hoehe der RGB-Kamera Bilder
		XnUInt32 m_DepthWidth;					///< Depth-Map Breite
		XnUInt32 m_DepthHeight;					///< Depth-Map Hoehe
		XnUInt32 m_ImageMapPixelSize;			///< Anzahl der RGB-Kamera Pixel (m_CameraWidth * m_CameraHeight * 3)
		XnUInt32 m_DepthMapPixelSize;			///< Anzahl der Depth-Map Pixel (m_DepthWidth * m_DepthHeight)
		XnStatus m_Status;						///< Aktuelle Statusmeldungen
	
		xn::Context m_Context;					///< Kontext-Objekt des OpenNI-Treibers
		xn::DepthGenerator m_DepthGenerator;	///< Depth-Generator
		xn::DepthMetaData m_DepthMetaData;		///< Metadaten des Tiefensensors
		xn::ImageGenerator m_ImageGenerator;	///< Image-Generator
		xn::ImageMetaData m_ImageMetaData;		///< Metadaten der RGB-Kamera
		xn::AudioGenerator m_AudioGenerator;	///< Audio-Generator
		xn::AudioMetaData m_AudioMetaData;		///< Metadaten des Audio-Streams
		KinectMotor m_Motor;					///< Ist fuer die Steuerung des Kinect-Motors ueber den OpenNI-Treiber verantwortlich
	};
}
