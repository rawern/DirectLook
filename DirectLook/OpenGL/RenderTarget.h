#pragma once

#include "../NonCopyable.h"

#include <GL/glew.h>
#include <iostream>

namespace DirectLook
{
	/// \brief Die Klasse Render-Target dient zum rendern einer 3D-Szene in eine RGB-Textur. 
	class RenderTarget : NonCopyable
	{

	private:
		GLuint m_FrameBufferID;		///< OpenGL Frame-Buffer ID
		GLuint m_RenderBufferID;	///< OpenGL Render-Buffer ID
		GLuint m_TextureID;			///< Render-Target OpenGL Textur ID
		unsigned int m_Width;		///< Breite des Render-Targets
		unsigned int m_Height;		///< Hoehe des Render-Targets
		bool m_IsInitialized;		///< Wurde das Render-Target ?
		GLubyte* m_pPixels;			///< Die RGB-Textur-Buffer des Render-Target

	public:
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein Render-Target-Objekt mit den Eigenscahften der uebergebenen Parameter.
		///
		/// \param width  Breite des Render-Targets
		/// \param height Hoehe des Render-Targets
		///
		////////////////////////////////////////////////////////////
		RenderTarget( unsigned int width, unsigned int height );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das Render-Target-Obekt aus dem Videospeicher der Grafikkarte.
		///
		////////////////////////////////////////////////////////////
		~RenderTarget(void);

		////////////////////////////////////////////////////////////
		/// \brief Aktiviert das Render-Target-Objekt.
		////////////////////////////////////////////////////////////
		void enable(void);

		////////////////////////////////////////////////////////////
		/// \brief Deaktiviert das Render-Target-Objekt.
		////////////////////////////////////////////////////////////
		void disable(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert einen RGB-Textur-Buffer mit der Groesse des Render-Targets zurueck.
		/// Buffergroesse: m_Width * m_Height * 3
		///
		/// \return RGB-Textur-Buffer (Buffergroesse: m_Width * m_Height * 3)
		///
		////////////////////////////////////////////////////////////
		GLubyte* getPixels(void);

		////////////////////////////////////////////////////////////
		/// \brief Schreibt einen Textur-Buffer mit der Groesse des Render-Targets in den uebergebenen Puffer.
		/// Die Puffergroesse Buffergroesse: m_Width * m_Height * 3
		///
		/// \param buffer  Zeiger auf den zu beschreibenden Puffer
		/// \param size    Groesse des zu beschreibenden Puffer
		/// \param format  Zu schreibendes Pixelformat. GL_RGB und GL_BGR sind moegliche Parameter.
		/// \return        True wenn erfolgreich, false wenn fehlgeschlagen
		///
		////////////////////////////////////////////////////////////
		bool getPixels(GLubyte* pBuffer, const unsigned int size, GLint format);

	private:
		////////////////////////////////////////////////////////////
		/// \brief Erzeugt und initialisiert das Render-Target-Objekt im Videospeicher der Grafikkarte.
		////////////////////////////////////////////////////////////
		void initialize(void);

		////////////////////////////////////////////////////////////
		/// \brief ueberprueft das OpenGL Frame-Buffer-Objekt bei der Initialisierung auf Fehler.
		////////////////////////////////////////////////////////////
		void checkFrameBufferObject(void);
	};
};
