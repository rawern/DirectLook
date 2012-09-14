#pragma once

#include <GL/glew.h>
#include "SegmentedDepthImage.h"
#include <iostream>

using namespace std;

namespace DirectLook
{
	/// \brief Die Klasse GLSegmentedDepthImage repraesentiert eine 3D-Height-Map, die aus den Tiefenwerten des Sensors ein 3D-Model erzeugt.
	class GLSegmentedDepthImage : public SegmentedDepthImage
	{

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein leeres GLSegmentedDepthImage-Objekt.
		///
		////////////////////////////////////////////////////////////
		GLSegmentedDepthImage(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen GLSegmentedDepthImage-Objektes.
		///
		/// \param copy	
		///
		////////////////////////////////////////////////////////////
		GLSegmentedDepthImage( const GLSegmentedDepthImage& copy );
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor A
		///
		/// Erzeugt ein leeres GLSegmentedDepthImage-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param width			 Breite des 3D-Grids
		/// \param height			 Hoehe des 3D-Grids
		/// \param nearThreshold	 Near Threshold fuer die Tiefensegmentierung
		/// \param farThreshold		 Far Threshold fuer die Tiefensegmentierung
		/// \param mirrorMode		 Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		/// \param invert			 Tiefenwerte invertieren : "Kleine Werte in weiss und grosse Werte in schwarz" oder "kleine Werte in schwarz und grosse Werte in weiss"
		/// \param vertexRangeFactor Wird in der Methode "mapToRangeFloat" verwendet um den maximalen Hoehenwert zu bestimmen
		///
		////////////////////////////////////////////////////////////
		GLSegmentedDepthImage(
			const unsigned short width,													// Depth-Map Breite
			const unsigned short height,												// Depth-Map Hoehe
			const unsigned short nearThreshold = SegmentedDepthImage::MIN_OPEN_NI_THRESHOLD,	// Near Threshold
			const unsigned short farThreshold = SegmentedDepthImage::MAX_OPEN_NI_THRESHOLD,	// Far Threshold
			const bool mirrorMode = false,												// Spiegelmodus: an / aus
			const bool invert = false,													// Invertierung: an / aus
			const GLfloat vertexRangeFactor = 1.0f										// Vertex Height Map Range Faktor
		);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor B
		///
		/// Erzeugt ein GLSegmentedDepthImage-Objekt mit den Eigenschaften der uebergebenen Parameter.
		/// Der Tiefenwerte werden durch "pImagePixels" gesetzt.
		///
		/// \param pImagePixels		 Die Tiefenwerte von GLSegmentedDepthImage
		/// \param width			 Breite des 3D-Grids
		/// \param height			 Hoehe des 3D-Grids
		/// \param nearThreshold	 Near Threshold fuer die Tiefensegmentierung
		/// \param farThreshold		 Far Threshold fuer die Tiefensegmentierung
		/// \param mirrorMode		 Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		/// \param invert			 Tiefenwerte invertieren : "Kleine Werte in weiss und grosse Werte in schwarz" oder "kleine Werte in schwarz und grosse Werte in weiss"
		/// \param vertexRangeFactor Wird in der Methode "mapToRangeFloat" verwendet um den maximalen Hoehenwert zu bestimmen
		///
		////////////////////////////////////////////////////////////
		GLSegmentedDepthImage(
			const unsigned short* pImagePixels,											// Bilddaten
			const unsigned short width,													// Depth-Map Breite
			const unsigned short height,												// Depth-Map Hoehe
			const unsigned short nearThreshold = SegmentedDepthImage::MIN_OPEN_NI_THRESHOLD,	// Near Threshold
			const unsigned short farThreshold = SegmentedDepthImage::MAX_OPEN_NI_THRESHOLD,	// Far Threshold
			const bool mirrorMode = false,												// Spiegelmodus: an / aus
			const bool invert = false,													// Invertierung: an / aus
			const GLfloat vertexRangeFactor = 1.0f										// Vertex Height Map Range Faktor
		);

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Gibt den belegten Speicher von GLSegmentedDepthImage wieder frei.
		///
		////////////////////////////////////////////////////////////
		virtual ~GLSegmentedDepthImage(void);
		
		//////////////////////////////////////////
		// ueberschriebene Sensor-Image Methoden //
		//////////////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Erzeugt einen neues 3D-Grid mit der Aufloesung "width" x "height".
		/// Die alten Tiefenwerte werden durch "pImagePixels" ersetzt.
		///
		/// \param pImagePixels	Die neuen Tiefenwerte des 3D-Grids
		/// \param width		Breite des 3D-Grids
		/// \param height		Hoehe des 3D-Grids
		///
		////////////////////////////////////////////////////////////
		virtual void setImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height );
		
		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Tiefenwerte.
		///
		/// \param pImagePixels	Die neuen Tiefenwerte
		///
		////////////////////////////////////////////////////////////
		virtual void updateImage( const unsigned short* pImagePixels );

		////////////////////////////////////////////////////////////
		/// \brief Ersetzt den Tiefenwert an der Bildposition (x, y).
		/// Falls die Bildposition ungueltig ist, wird der Tiefenwert nicht ersetzt.
		///
		/// \param x			Position x
		/// \param y			Position y
		/// \param pixelValue	Neuer Tiefenwert
		///
		////////////////////////////////////////////////////////////
		virtual void replacePixelAt( const unsigned int x, const unsigned int y, const unsigned short pixelValue );
		
		////////////////////////////////////////////////////////////
		/// \brief Setzt die 3D-Grid Aufloesung.
		///
		/// \param width	Neue Breite des 3D-Grids
		/// \param height	Neue Hoehe des 3D-Grids
		///
		////////////////////////////////////////////////////////////
		virtual void setResolution( const unsigned short width, const unsigned short height );

		///////////////////////////
		// GL Depth Map Methoden //
		///////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Tiefenwerte als 8 bit Grauwert-Textur zurueck.
		///
		/// \return Height-Map-Textur
		///
		////////////////////////////////////////////////////////////
		const GLubyte* getTextureHeightMap(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert das erzeugte 3D-Grid als Vertex-Buffer zurueck.
		///
		/// \return Height-Map Vertex-Buffer
		///
		////////////////////////////////////////////////////////////
		const GLfloat* getVertexHeightMap(void);

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Vertex-Range-Faktor.
		///
		/// \param vertexRangeFactor Vertex-Range-Faktor
		///
		////////////////////////////////////////////////////////////
		void setVertexRangeFactor( const GLfloat vertexRangeFactor );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Vertex-Range-Faktor zurueck.
		///
		/// \return Vertex-Range-Faktor
		///
		////////////////////////////////////////////////////////////
		GLfloat getVertexRangeFactor(void);

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Erzeugt und initialisiert das 3D-Grid der Height-Map.
		///
		////////////////////////////////////////////////////////////
		void initVertexHeightMap(void);

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Height-Map-Textur.
		/// Der maximale Grauwert wird durch den Vertex-Range-Faktor angegeben.
		///
		////////////////////////////////////////////////////////////
		GLubyte mapToRangeUByte( const unsigned short pixelValue );

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Height-Map-Textur.
		/// Der maximale Grauwert wird durch den Vertex-Range-Faktor angegeben.
		///
		////////////////////////////////////////////////////////////
		GLfloat mapToRangeFloat( const unsigned short pixelValue );

		////////////////////////////////////////////////////////////
		/// \brief Loescht alle Daten aus dem Speicher.
		/// Wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		virtual void clear(void);

		GLubyte* m_pTextureHeightMap;	///< Die Tiefenwerte werden als Grauwert-Textur mit der Groesse "Breite x Hoehe" gespeichert
		GLfloat* m_pVertexHeightMap;	///< Die Tiefenwerte werden als OpenGL Vertex-Buffer mit der Groesse "Breite x Hoehe x 3" gespeichert
		bool m_Invert;					///< Tiefenwerte invertieren : "Kleine Werte in weiss und grosse Werte in schwarz" oder "kleine Werte in schwarz und grosse Werte in weiss"
		GLfloat m_VertexRangeFactor;	///< Wird in der Methode "mapToRangeFloat" verwendet um den maximalen Hoehenwert zu bestimmen
	};
}
