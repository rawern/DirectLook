#pragma once

#include <GL/glew.h>
#include "../NonCopyable.h"

namespace DirectLook 
{
	/// \brief Die Klasse BufferObject repraesentiert einen einfachen OpenGL Buffer.
	class BufferObject  : public NonCopyable 
	{

	protected:
		GLenum m_Target;		///< OpenGL Buffer Target
		GLenum m_UpdateTarget;	///< OpenGL Buffer Update Target
		GLuint m_ID;			///< Buffer ID
		GLsizei m_Size;			///< Buffergroesse (bufferElements * length)
		GLint m_Length;			///< Die Laenge eines Bufferelementes
		GLsizei m_Stride;		///< sizeof( Primitiver Datentyp )

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt einen neues Buffer-Objekt.
		///
		////////////////////////////////////////////////////////////
		BufferObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein Buffer-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param bufferElements Anzahl der Bufferelemente
		/// \param length		  Die Laenge eines Bufferelementes
		/// \param stride		  Groesse eines Bufferelements (Normalerweise: sizeof( Datentyp des Bufferelements ))
		/// \param target		  OpenGL Buffer-Target
		/// \param updateTarget	  OpenGL Buffer-Update-Target
		///
		////////////////////////////////////////////////////////////
		BufferObject(
			const GLsizei bufferElements,	// Number of buffer elements
			const GLint length,				// Length of each buffer element
			const GLsizei stride,			// sizeof( used data type )
			const GLenum target,			// OpenGL buffer target
			const GLenum updateTarget		// OpenGL buffer update target
		);

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das Buffer-Obekt aus dem Videospeicher.
		///
		////////////////////////////////////////////////////////////
		virtual ~BufferObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert das aktuelle Buffer-Target zurueck.
		///
		/// \return Buffer-Target
		///
		////////////////////////////////////////////////////////////
		GLenum getTarget(void) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Setzt ein neues Buffer-Target.
		///
		/// Moegliche Werte sind GL_ARRAY_BUFFER und GL_ELEMENT_ARRAY_BUFFER.
		/// Falls der Target-Wert ungueltig ist, bleibt der alte Wert erhalten. 
		///
		/// \param target Buffer-Target
		///
		////////////////////////////////////////////////////////////
		void setTarget( const GLenum target );

		////////////////////////////////////////////////////////////
		/// \brief Liefert das aktuelle Update-Target zurueck.
		///
		/// \return Update-Traget
		///
		////////////////////////////////////////////////////////////
		GLenum getUpdateTarget(void) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Setzt ein neues Update-Target.
		///
		/// Moegliche Werte sind GL_ARRAY_BUFFER_ARB und GL_ELEMENT_ARRAY_BUFFER_ARB.
		/// Falss der Update-Target-Wert ungueltig ist, bleibt der alte Werte erhalten.
		///
		/// \param updateTarget Buffer-Update-Target
		///
		////////////////////////////////////////////////////////////
		void setUpdateTarget( const GLenum updateTarget );

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Buffrt ID zurueck.
		///
		/// \return Buffer ID
		///
		////////////////////////////////////////////////////////////
		GLuint getID(void) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Buffergroesse zurueck. (m_Length * bufferSize)
		///
		/// \return Buffergroesse
		///
		////////////////////////////////////////////////////////////
		GLsizei getSize(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Anzahl der Bufferelemente zurueck.
		///
		/// \return Anzahl der Bufferelemente
		///
		////////////////////////////////////////////////////////////
		GLint getLength(void) const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Groesse eines Bufferelements zurueck.
		///
		/// \return Groesse eines Bufferelements
		///
		////////////////////////////////////////////////////////////
		GLsizei getStride(void) const;
	};
};
