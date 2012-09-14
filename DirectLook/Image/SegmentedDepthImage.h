#pragma once

#include "DepthImage.h"

namespace DirectLook
{
	/// \brief Die Klasse Depth-Map-Image repraesentiert die tiefensegmentierten Daten des Sensor-Tiefensensors.
	class SegmentedDepthImage : public DepthImage
	{

	public:
		static const unsigned short MIN_OPEN_NI_THRESHOLD = 500;	///< 0.50 m
		static const unsigned short MAX_OPEN_NI_THRESHOLD = 10000;	///< 10.0 m

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein leeres Depth-Map-Image Objekt.
		///
		////////////////////////////////////////////////////////////
		SegmentedDepthImage(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Depth-Map-Image Objektes.
		///
		/// \param copy	
		///
		////////////////////////////////////////////////////////////
		SegmentedDepthImage( const SegmentedDepthImage& copy );
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor A
		///
		/// Erzeugt ein leeres Depth-Map-Image Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param width			Breite des Depth-Map-Image
		/// \param height			Hoehe des Depth-Map-Image
		/// \param nearThreshold	Near Threshold fuer die Tiefensegmentierung
		/// \param farThreshold		Far Threshold fuer die Tiefensegmentierung
		/// \param mirrorMode		Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		SegmentedDepthImage( const unsigned short width, const unsigned short height, const unsigned short nearThreshold = MIN_OPEN_NI_THRESHOLD, const unsigned short farThreshold = MAX_OPEN_NI_THRESHOLD, const bool mirrorMode = false );

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor B
		///
		/// Erzeugt ein Depth-Map-Image Objekt mit den Eigenschaften der uebergebenen Parameter.
		/// Der Bilddaten werden durch "pImagePixels" gesetzt.
		///
		/// \param pImagePixels		Die Bilddaten von Depth-Map-Image
		/// \param width			Breite des Depth-Map-Image
		/// \param height			Hoehe des Depth-Map-Image
		/// \param nearThreshold	Near Threshold fuer die Tiefensegmentierung
		/// \param farThreshold		Far Threshold fuer die Tiefensegmentierung
		/// \param mirrorMode		Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		SegmentedDepthImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height, const unsigned short nearThreshold = MIN_OPEN_NI_THRESHOLD,	const unsigned short farThreshold = MAX_OPEN_NI_THRESHOLD, const bool mirrorMode = false );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Gibt den belegten Speicher vom Depth-Map-Image Objekt wieder frei.
		///
		////////////////////////////////////////////////////////////
		virtual ~SegmentedDepthImage(void);

		//////////////////////////////////////////
		// ueberschriebene Sensor-Image Methoden //
		//////////////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Erzeugt einen neuen Depth-Map-Image Datenzeiger mit der Aufloesung "width" x "height".
		/// Die alten Tiefenwerte werden durch "pImagePixels" ersetzt.
		///
		/// \param pImagePixels	Die neuen Bilddaten von Depth-Map-Image
		/// \param width		Breite des Depth-Map-Image
		/// \param height		Hoehe des Depth-Map-Image
		///
		////////////////////////////////////////////////////////////
		virtual void setImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height );
		
		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Bilddaten des Depth-Map-Image.
		///
		/// \param pImagePixels	Die neuen Bilddaten von Depth-Map-Image
		///
		////////////////////////////////////////////////////////////
		virtual void updateImage( const unsigned short* pImagePixels );
	
		//////////////////////////////
		// Depth-Map-Image Methoden //
		//////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Liefert den kleinsten Tiefenwert zurueck.
		///
		/// \return Kleinster Tiefenwert in Millimeter
		///
		////////////////////////////////////////////////////////////
		const unsigned short getMinDistance(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert den groessten Tiefenwert zurueck.
		///
		/// \return Groesster Tiefenwert in Millimeter
		///
		////////////////////////////////////////////////////////////
		const unsigned short getMaxDistance(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Near Threshold zurueck.
		///
		/// \return Near Threshold
		///
		////////////////////////////////////////////////////////////
		const unsigned short getNearThreshold(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Far Threshold zurueck.
		///
		/// \return Far Threshold
		///
		////////////////////////////////////////////////////////////
		const unsigned short getFarThreshold(void);

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Werte fuer den Near- und den Far Threshold.
		///
		/// \param nearThreshold	Near Threshold fuer die Tiefensegmentierung
		/// \param farThreshold		Far Threshold fuer die Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		void setThreshold( const unsigned short nearThreshold, const unsigned short farThreshold ); 

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Near Threshold.
		///
		/// \param nearThreshold Near Threshold fuer die Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		void setNearThreshold( const unsigned short nearThreshold );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Far Threshold.
		///
		/// \param farThreshold Far Threshold fuer die Tiefensegmentierung
		///
		////////////////////////////////////////////////////////////
		void setFarThreshold( const unsigned short farThreshold );

	protected:	
		unsigned short m_MinDistance;	///< Kleinster Tiefenwert
		unsigned short m_MaxDistance;	///< Groesster Tiefenwert
		unsigned short m_NearThreshold;	///< Nearest Threshold
		unsigned short m_FarThreshold;	///< Farest Threshold
	};
}
