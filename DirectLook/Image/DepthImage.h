#pragma once

namespace DirectLook
{
	/// \brief Die Klasse DepthImage repraesentiert eine einheitliche Datenstruktur des Tiefensensors.
	class DepthImage
	{
	
	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein leeres Sensor-Image Objekt.
		///
		////////////////////////////////////////////////////////////
		DepthImage(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Sensor-Image Objektes.
		///
		/// \param copy	
		///
		////////////////////////////////////////////////////////////
		DepthImage( const DepthImage& copy );

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor A
		///
		/// Erzeugt ein leeres Sensor-Image Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param width		Breite des Sensor-Image
		/// \param height		Hoehe des Sensor-Image
		/// \param mirrorMode	Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		DepthImage( const unsigned short width, const unsigned short height, const bool mirrorMode = false );
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor B
		///
		/// Erzeugt ein Sensor-Image Objekt mit den Eigenschaften der uebergebenen Parameter.
		/// Der Bilddaten werden durch "pImagePixels" gesetzt.
		///
		/// \param pImagePixels	Die Bilddaten von Sensor-Image
		/// \param width		Breite des Sensor-Image
		/// \param height		Hoehe des Sensor-Image
		/// \param mirrorMode	Gibt an ob der Bildinhalt gespiegelt wird. (true: Spiegelmodus an - false: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		DepthImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height, const bool mirrorMode = false );
		
		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Gibt den belegten Speicher vom Sensor-Image Objekt wieder frei.
		///
		////////////////////////////////////////////////////////////
		virtual ~DepthImage(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Erzeugt einen neuen Sensor-Image Datenzeiger mit der Aufloesung "width" x "height".
		/// Die alten Tiefenwerte werden durch "pImagePixels" ersetzt.
		///
		/// \param pImagePixels	Die neuen Bilddaten von Sensor-Image
		/// \param width		Breite des Sensor-Image
		/// \param height		Hoehe des Sensor-Image
		///
		////////////////////////////////////////////////////////////
		virtual void setImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height );
		
		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Bilddaten des Sensor-Image.
		///
		/// \param pImagePixels	Die neuen Bilddaten von Sensor-Image
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
		/// \brief Setzt die Sensor-Image-Aufloesung.
		///
		/// \param width	Neue Breite des Sensor-Image
		/// \param height	Neue Hoehe des Sensor-Image
		///
		////////////////////////////////////////////////////////////
		virtual void setResolution( const unsigned short width, const unsigned short height );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Tiefenwert an der Position "index" zurueck.
		/// Falls der Index ungueltig ist, wird eine 0 zurueckgeliefert.
		///
		/// \param index Index des Tiefenwertes
		///
		/// \return	Tiefenwert an der Position "index"
		///
		////////////////////////////////////////////////////////////
		const unsigned short pixelAt( const unsigned int index );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Tiefenwert an der Position (x, y) zurueck.
		/// Falls die Bildposition ungueltig ist, wird eine 0 zurueckgeliefert.
		///
		/// \param x	Position x
		/// \param y	Position y
		///
		/// \return		Tiefenwert an der Position (x, y)
		///
		////////////////////////////////////////////////////////////
		const unsigned short pixelAt( const unsigned int x, const unsigned int y );
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Breite des Sensor-Image Objektes zurueck.
		///
		/// \return Breite des Sensor-Image
		///
		////////////////////////////////////////////////////////////
		const unsigned short getWidth(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Hoehe des Sensor-Image Objektes zurueck.
		///
		/// \return Hoehe des Sensor-Image
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
		/// \param mirrorMode (true: Spiegelmodus an - flase: Spiegelmodus aus)
		///
		////////////////////////////////////////////////////////////
		void setMirrorMode( const bool mirrorMode );
		
		////////////////////////////////////////////////////////////
		/// \brief Gibt die Pixelanzahl des Sensor-Image Objektes zurueck (Breite x Hoehe x 3).
		///
		/// \return Pixelanzahl des Sensor-Image
		///
		////////////////////////////////////////////////////////////
		const unsigned int getPixelSize(void);

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Loescht die Bilddaten. Wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		virtual void clear(void);

		unsigned short* m_pImagePixels;	///< 16 bit Tiefenwert in der Einheit Millimeter
		unsigned short m_Width;			///< Bildbreite
		unsigned short m_Height;		///< Bildhoehe
		unsigned int m_PixelSize;		///< Pixelanzahl
		bool m_MirrorMode;				///< Spiegelmodus an oder aus
	};
}
