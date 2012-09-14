#pragma once

namespace DirectLook 
{
	/// \brief Die Klasse Audio-Stream repraesentiert einen Audio-Buffer der Sensor-Hardware.
	class AudioStream 
	{

	private:
		unsigned short m_BitsPerSample;	///< Anzahl der Bits pro Audiosample
		unsigned char m_Channels;		///< Anzahl der Audiokanaele
		unsigned int m_SampleRate;		///< Samplerate
		unsigned char* m_pAudioBuffer;	///< Audio-Daten-Buffer
		unsigned int m_BufferSize;		///< Audio-Buffergroesse

	public:

		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein neues Audio-Stream-Objekt.
		///
		////////////////////////////////////////////////////////////
		AudioStream(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Audio-Stream Objektes.
		///
		/// \param copy
		///
		////////////////////////////////////////////////////////////
		AudioStream( const AudioStream& copy );
		
		///////////////////////////////////////////////////////////
		/// \brief Destruktor
		///////////////////////////////////////////////////////////
		virtual ~AudioStream(void);

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Bits pro Audiosample.
		///
		/// \param bitsPerSample Bits pro Audiosample
		///
		////////////////////////////////////////////////////////////
		void setBitsPerSample( const unsigned short bitsPerSample );
		
		////////////////////////////////////////////////////////////
		/// \brief Setzt die Anzahl der Audiokanaele.
		///
		/// \param channels Anzahl der Audiokanaele
		///
		////////////////////////////////////////////////////////////
		void setChannels( const unsigned char channels );
		
		////////////////////////////////////////////////////////////
		/// \brief Setzt die Samplerate.
		///
		/// \param sampleRate Samplerate
		///
		////////////////////////////////////////////////////////////
		void setSampleRate( const unsigned int sampleRate );
		
		////////////////////////////////////////////////////////////
		/// \brief Setzt einen neuen Audio-Buffer.
		///
		/// \param pAudioBuffer Neuer Audio-Buffer
		///
		////////////////////////////////////////////////////////////
		void setAudioBuffer( const unsigned char* pAudioBuffer );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Audio-Buffergroesse.
		///
		/// \param bufferSize Audio-Buffergroesse
		///
		////////////////////////////////////////////////////////////
		void setBufferSize( const unsigned int bufferSize );

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Bits pro Audiosample zurueck.
		///
		/// \return Bits pro Audiosample
		///
		////////////////////////////////////////////////////////////
		unsigned short getBitsPerSample(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Anzahl der Audiokanaele zurueck.
		///
		/// \return Anzahl der Audiokanaele.
		///
		////////////////////////////////////////////////////////////
		unsigned char getChannels(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Samplerate zurueck.
		///
		/// \return Samplerate
		///
		////////////////////////////////////////////////////////////
		unsigned int getSampleRate(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Audio-Stream Daten als konstanten 8 bit Daten-Pointer zurueck.
		///
		/// \return 8 bit Audio-Stream Daten
		///
		////////////////////////////////////////////////////////////
		const unsigned char* getAudioBuffer(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Buffergroesse des Audio-Streams zurueck.
		///
		/// \return Audio-Buffergroesse
		///
		////////////////////////////////////////////////////////////
		unsigned int getBufferSize(void) const;
	};
};