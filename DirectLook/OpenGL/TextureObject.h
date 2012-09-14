#pragma once

#include <GL/glew.h>
#include "../NonCopyable.h"

namespace DirectLook
{
	/// \brief Die Klasse Textur-Objekt repraesentiert eine OpenGL Textur.
	class TextureObject
	{

	protected:
		GLint m_Border;				///< Texturrand
		GLenum m_ExternalFormat;	///< Externes Texturformat
		GLsizei m_Height;			///< Texturhoehe
		GLuint m_ID;				///< Textur ID
		GLint m_InternalFormat;		///< Internes Texturformat
		GLint m_Level;				///< Mipmap Leveldetail
		GLenum m_Target;			///< 1D-, 2D-, 3D- oder Cube-Textur
		GLenum m_Type;				///< Texturtyp
		GLsizei m_Width;			///< Texturbreite

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein neues Textur-Objekt.
		///
		////////////////////////////////////////////////////////////
		TextureObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein Textur-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param width		  Texturbreite
		/// \param height		  Texturhoehe
		/// \param border		  Texturrand
		/// \param externalFormat Externes Texturformat
		/// \param internalFormat Internes Texturformat
		/// \param level		  Mipmap Leveldetail
		/// \param target		  1D-, 2D-, 3D- oder Cube-Textur
		/// \param type			  Texturtyp
		///
		////////////////////////////////////////////////////////////
		TextureObject( 
			const GLsizei width,			// Texture width
			const GLsizei height,			// Texture height
			const GLint border,				// Texture border
			const GLenum externalFormat,	// External texture format
			const GLint internalFormat,		// Internal texture format
			const GLint level,				// Mipmap detail level
			const GLenum target,			// 1D, 2D, 3D or cube
			const GLenum type				// Texture type
		);

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das Textur-Obekt aus dem Videospeicher der Grafikkarte.
		///
		////////////////////////////////////////////////////////////
		virtual ~TextureObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Texturrand zurueck.
		///
		/// \return Texturrand
		///
		////////////////////////////////////////////////////////////
		GLint getBorder() const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert das externe Texturformat zurueck.
		///
		/// \return Externes Texturformat
		///
		////////////////////////////////////////////////////////////
		GLenum getExternalFormat() const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Texturhoehe zurueck.
		///
		/// \return Texturhoehe
		///
		////////////////////////////////////////////////////////////
		GLsizei getHeight() const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Textur ID zurueck.
		///
		/// \return Textur ID
		///
		////////////////////////////////////////////////////////////
		GLuint getID() const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert das interne Texturformat zurueck.
		///
		/// \return Internes Texturformat
		///
		////////////////////////////////////////////////////////////
		GLint getInternalFormat() const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Detailgrad des Mipmap Levels zurueck.
		///
		/// \return Mipmap Leveldetail
		///
		////////////////////////////////////////////////////////////
		GLint getLevel() const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert das Textur-Target zurueck.
		///
		/// \return Textur-Target
		///
		////////////////////////////////////////////////////////////
		GLenum getTarget() const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Texturtyp zurueck.
		///
		/// \return Texturtyp
		///
		////////////////////////////////////////////////////////////
		GLenum getType() const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die Texturbreite zurueck.
		///
		/// \return Texturbreite
		///
		////////////////////////////////////////////////////////////
		GLsizei getWidth() const;

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Texturrand.
		///
		/// \param border Texturrand
		///
		////////////////////////////////////////////////////////////
		void setBorder( GLint border );

		////////////////////////////////////////////////////////////
		/// \brief Setzt das externe Texturformat.
		///
		/// \param externalFormat Externes Texturformat
		///
		////////////////////////////////////////////////////////////
		void setExternalFormat( GLenum externalFormat );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Texturhoehe.
		///
		/// \param height Texturhoehe
		///
		////////////////////////////////////////////////////////////
		void setHeight( GLsizei height );

		////////////////////////////////////////////////////////////
		/// \brief Setzt das interne Texturformat.
		///
		/// \param internalFormat Internes Texturformat
		///
		////////////////////////////////////////////////////////////
		void setInternalFormat( GLint internalFormat );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Detailgrad des Mipmap Levels.
		///
		/// \param level Mipmap Leveldetail
		///
		////////////////////////////////////////////////////////////
		void setLevel( GLint level );

		////////////////////////////////////////////////////////////
		/// \brief Setzt ein neues Textur-Target.
		///
		/// Moegliche Werte sind case GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		/// GL_TEXTURE_CUBE_MAP_NEGATIVE_X,	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		/// GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z und GL_PROXY_TEXTURE_CUBE_MAP.
		///
		/// Falls der Target-Wert ungueltig ist, wird er auf den Wert GL_TEXTURE_2D gesetzt. 
		///
		/// \param target Textur-Target
		///
		////////////////////////////////////////////////////////////
		void setTarget( GLenum target );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Texturtyp.
		///
		/// Moegliche Werte sind GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT,
		/// GL_INT,	GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
		///	GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV,
		///	GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2 und GL_UNSIGNED_INT_2_10_10_10_REV.
		///
		/// Falls der Texturtyp ungueltig ist, wird er auf den Wert GL_UNSIGNED_BYTE gesetzt. 
		///
		/// \param type Texturtyp
		///
		////////////////////////////////////////////////////////////
		void setType( GLenum type );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Texturbreite.
		///
		/// \param width Texturbreite
		///
		////////////////////////////////////////////////////////////
		void setWidth( GLsizei width );

		////////////////////////////////////////////////////////////
		/// \brief Generiert eine eindeutige OpenGL Textur ID.
		/// Wird als Parameter ein Null-Pointer uebergeben, wird keine OpenGL Textur ID generiert.
		///
		////////////////////////////////////////////////////////////
		void generateTexture(void);

		////////////////////////////////////////////////////////////
		/// \brief Generiert eine eindeutige OpenGL Textur ID und laedt die Texturdaten in den Videospeicher der Grafikkarte.
		/// Wird als Parameter ein Null-Pointer uebergeben, werden keine Texturdaten in den Videospeicher geladen und keine OpenGL Textur ID generiert.
		///
		/// \param pPixels Texturdaten
		///
		////////////////////////////////////////////////////////////
		void generateTexture( const void* pPixels );

		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Texturdaten im Videospeicher der Grafikkarte.
		/// Wird als Parameter ein Null-Pointer uebergeben, werden die Texturdaten nicht aktualisiert.
		///
		/// \param pPixels Texturdaten
		///
		////////////////////////////////////////////////////////////
		void updateTexture( const void* pPixels );
		
		////////////////////////////////////////////////////////////
		/// \brief Loescht die Texturdaten aus dem Videospeicher der Grafikkarte.
		/// Die Methode wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		void deleteTexture(void);
	};
};
