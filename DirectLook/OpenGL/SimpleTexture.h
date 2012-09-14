#pragma once

#include "ElementBufferObject.h"
#include "TextureObject.h"
#include "VertexBufferObject.h"
#include "Shader.h"

#include <iostream>

namespace DirectLook
{
	/// \brief Die Klasse SimpleTexture dient zum anzeigen einer einfachen RGB-Textur.
	class SimpleTexture {

	private:
		ElementBufferObject* m_pElementBuffer;	///< Element-Buffer
		VertexBufferObject* m_pVertexBuffer;	///< Vertex-Buffer
		TextureObject* m_pTexture;				///< Textur-Objekt
		Shader* m_pShader;						///< Shader-Objekt
		unsigned short m_Width;					///< Texturbreite
		unsigned short m_Height;				///< Texturhoehe
		bool m_IsInitialized;					///< Wurde das SimpleTexture-Objekt initialisiert?

	public:
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein SimpleTexture-Objekt mit den Eigenscahften der uebergebenen Parameter.
		///
		/// \param width  Texturbreite
		/// \param height Texturhoehe
		///
		////////////////////////////////////////////////////////////
		SimpleTexture( const unsigned short width, const unsigned short height );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das SimpleTexture-Obekt aus dem Videospeicher der Grafikkarte.
		///
		////////////////////////////////////////////////////////////
		~SimpleTexture(void);

		////////////////////////////////////////////////////////////
		/// \brief Initialisiert das SimpleTexture-Objekt.
		///
		/// \param vertexShaderFilename	  Dateipfad des Vertex-Shader Codes
		/// \param fragmentShaderFilename Dateipfad des Fragment-Shader Codes
		///
		////////////////////////////////////////////////////////////
		void init( std::string& vertexShaderFilename, std::string& fragmentShaderFilename );

		////////////////////////////////////////////////////////////
		/// \brief Laedt und kompiliert das Shaderprogramm von SimpleTexture.
		///
		/// \param vertexShaderFilename	  Dateipfad des Vertex-Shader Codes
		/// \param fragmentShaderFilename Dateipfad des Fragment-Shader Codes
		///
		////////////////////////////////////////////////////////////
		int initShader( std::string& vertexShaderFilename, std::string& fragmentShaderFilename );

		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die RGB-Textur.
		///
		/// \param pPixels RGB-Textur-Pointer
		///
		////////////////////////////////////////////////////////////
		void update( const GLubyte* pPixels );

		////////////////////////////////////////////////////////////
		/// \brief Zeichnet das SimpleTexture-Objekt.
		////////////////////////////////////////////////////////////
		void draw(void);
	};
}
