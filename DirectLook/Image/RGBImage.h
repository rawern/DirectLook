#pragma once

namespace DirectLook
{
	/// \brief Die Klasse RGBImage repraesentiert eine einheitliche Datenstruktor der Sensor-Kameradaten.
	class RGBImage
	{
	
	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein leeres Camera-Image Objekt.
		///
		////////////////////////////////////////////////////////////
		RGBImage(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Camera-Image Objektes.
		///
		/// \param copy
		///
		////////////////////////////////////////////////////////////
		RGBImage( const RGBImage& copy );
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor A
		///
		/// Erzeugt ein leeres Camera-Image Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param width		Breite des Camera-Image
		/// \param height		Hoehe des Camera-Image
		/// \param mirrorMode	Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		RGBImage( const unsigned short width, const unsigned short height, const bool mirrorMode = false );
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor B
		///
		/// Erzeugt ein Camera-Image Objekt mit den Eigenschaften der uebergebenen Parameter.
		/// Der Bilddaten werden durch "pImagePixels" gesetzt.
		///
		/// \param pImagePixels	Die Bilddaten von Camera-Image
		/// \param width		Breite des Camera-Image
		/// \param height		Hoehe des Camera-Image
		/// \param mirrorMode	Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		RGBImage( const unsigned char* pImagePixels, const unsigned short width, const unsigned short height, const bool mirrorMode = false );
		
		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Gibt den belegten Speicher vom Camera-Image Objekt wieder frei.
		///
		////////////////////////////////////////////////////////////
		virtual ~RGBImage(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Erzeugt einen neuen Camera-Image Datenzeiger mit der Aufloesung "width" x "height".
		/// Die alten Bilddaten werden durch "pImagePixels" ersetzt.
		///
		/// \param pImagePixels	Die neuen Bilddaten von Camera-Image
		/// \param width		Breite des Camera-Image
		/// \param height		Hoehe des Camera-Image
		///
		////////////////////////////////////////////////////////////
		virtual void setImage( const unsigned char* pImagePixels, const unsigned short width, const unsigned short height );
		
		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Bilddaten des Camera-Image.
		///
		/// \param pImagePixels	Die neuen Bilddaten von Camera-Image
		///
		////////////////////////////////////////////////////////////
		virtual void updateImage( const unsigned char* pImagePixels );
		
		////////////////////////////////////////////////////////////
		/// \brief Ersetzt den RGB-Pixelwert an der Bildposition (x, y).
		/// Falls die Bildposition ungueltig ist, wird der Pixelwert nicht ersetzt.
		///
		/// \param x		Position x
		/// \param y		Position y
		/// \param red		Roter 8 bit Farbwert 
		/// \param green	Gruener 8 bit Farbwert
		/// \param blue		Blauer 8 bit Farbwert
		///
		////////////////////////////////////////////////////////////
		virtual void replacePixelAt( const unsigned int x, const unsigned int y, const unsigned char red, const unsigned char green, const unsigned char blue );
		
		////////////////////////////////////////////////////////////
		/// \brief Setzt die Camera-Image-Aufloesung.
		///
		/// \param width	Neue Breite des Camera-Image
		/// \param height	Neue Hoehe des Camera-Image
		///
		////////////////////////////////////////////////////////////
		virtual void setResolution( const unsigned short width, const unsigned short height );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den roten 8 bit Farbwert an der Position (x, y) zurueck.
		/// Falls die Bildposition ungueltig ist, wird eine 0 zurueckgeliefert.
		///
		/// \param x	Position x
		/// \param y	Position y
		///
		/// \return		Roter 8 bit Farbwert
		///
		////////////////////////////////////////////////////////////
		const unsigned char pixelRedAt( const unsigned int x, const unsigned int y );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den gruenen 8 bit Farbwert an der Position (x, y) zurueck.
		/// Falls die Bildposition ungueltig ist, wird eine 0 zurueckgeliefert.
		///
		/// \param x	Position x
		/// \param y	Position y
		///
		/// \return		Gruener 8 bit Farbwert
		///
		////////////////////////////////////////////////////////////
		const unsigned char pixelGreenAt( const unsigned int x, const unsigned int y );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den blauen 8 bit Farbwert an der Position (x, y) zurueck.
		/// Falls die Bildposition ungueltig ist, wird eine 0 zurueckgeliefert.
		///
		/// \param x	Position x
		/// \param y	Position y
		///
		/// \return		Blauer 8 bit Farbwert
		///
		////////////////////////////////////////////////////////////
		const unsigned char pixelBlueAt( const unsigned int x, const unsigned int y );
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Breite des Camera-Image Objektes zurueck.
		///
		/// \return Breite des Camera-Image
		///
		////////////////////////////////////////////////////////////
		const unsigned short getWidth(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Hoehe des Camera-Image Objektes zurueck.
		///
		/// \return Hoehe des Camera-Image
		///
		////////////////////////////////////////////////////////////
		const unsigned short getHeight(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert den aktuellen Status des Spiegelmodus zurueck.
		///
		/// \return true: Spiegelmodus an - flase: Spiegelmodus aus
		///
		////////////////////////////////////////////////////////////
		const bool getMirrorMode(void);

		////////////////////////////////////////////////////////////
		/// \brief Schaltet den Spiegelmodus an oder aus.
		///
		/// \param mode (true: Spiegelmodus an - flase: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		void setMirrorMode( const bool mode );

		////////////////////////////////////////////////////////////
		/// \brief Gibt die Pixelanzahl des Camera-Image Objektes zurueck (Breite x Hoehe x 3).
		///
		/// \return Pixelanzahl des Camera-Image
		///
		////////////////////////////////////////////////////////////
		const unsigned int getPixelSize(void);

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Erzeugt eine Kopie der Bilddaten. Wird im Kopierkonstruktor aufgerufen.
		///
		/// \param pImagePixels
		///
		////////////////////////////////////////////////////////////
		virtual void clone( const unsigned char* pImagePixels );

		////////////////////////////////////////////////////////////
		/// \brief Loescht die Bilddaten. Wird im Destruktor aufgerufen.
		////////////////////////////////////////////////////////////
		virtual void clear(void);

		unsigned char* m_pImagePixels;	///< 8 bit RGB-Daten
		unsigned short m_Width;			///< Bildbreite
		unsigned short m_Height;		///< Bildhoehe
		unsigned int m_PixelSize;		///< Pixelanzahl
		bool m_MirrorMode;				///< Spiegelmodus an oder aus
	};
};
