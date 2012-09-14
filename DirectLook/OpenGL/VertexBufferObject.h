#pragma once

#include "BufferObject.h"

namespace DirectLook
{
	/// \brief Die Klasse Vertex-Buffer-Object repraesentiert einen OpenGL Vertex-Buffer. 
	class VertexBufferObject : public BufferObject {

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein neues Verex-Buffer-Objekt.
		///
		////////////////////////////////////////////////////////////
		VertexBufferObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor A
		///
		/// Erzeugt ein Vertex-Buffer-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param bufferElements Anzahl der Bufferelemente
		/// \param length		  Die Laenge eines Bufferelementes
		/// \param target		  OpenGL Buffer-Target (Standardwert: GL_ARRAY_BUFFER)
		/// \param updateTarget	  OpenGL Buffer-Update-Target (Standardwert: GL_ARRAY_BUFFER_ARB)
		///
		////////////////////////////////////////////////////////////
		VertexBufferObject(
			const GLsizei bufferElements,						// Number of vertex buffer elements
			const GLint length,									// Length of each vertex buffer element
			const GLenum target = GL_ARRAY_BUFFER,				// OpenGL buffer target
			const GLenum updateTarget = GL_ARRAY_BUFFER_ARB		// OpenGL buffer update target
		);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor B
		///
		/// Erzeugt ein Vertex-Buffer-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param pBufferData	  Daten des Element-Buffers
		/// \param bufferElements Anzahl der Bufferelemente
		/// \param length		  Die Laenge eines Bufferelementes
		/// \param target		  OpenGL Buffer-Target (Standardwert: GL_ARRAY_BUFFER)
		/// \param updateTarget	  OpenGL Buffer-Update-Target (Standardwert: GL_ARRAY_BUFFER_ARB)
		///
		////////////////////////////////////////////////////////////
		VertexBufferObject(
			const void* pBufferData,							// Vertex buffer data
			const GLsizei bufferElements,						// Number of vertex buffer elements
			const GLint length,									// Length of each vertex buffer element
			const GLenum target = GL_ARRAY_BUFFER,				// OpenGL buffer target
			const GLenum updateTarget = GL_ARRAY_BUFFER_ARB		// OpenGL buffer update target
		);

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das Vertex-Buffer-Obekt aus dem Videospeicher der Grafikkarte.
		///
		////////////////////////////////////////////////////////////
		virtual ~VertexBufferObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Generiert eine eindeutige OpenGL Buffer ID und laedt die Buffer-Daten in den Videospeicher der Grafikkarte.
		/// Wird als Parameter ein Null-Pointer uebergeben, werden keine Buffer-Daten in den Videospeicher geladen und keine OpenGL Buffer ID generiert.
		///
		/// \param pBufferData Die neuen Dates des Vertex-Buffers
		///
		////////////////////////////////////////////////////////////
		void generateBuffer( const void* pBufferData );

		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Vertex-Buffer-Daten im Videospeicher der Grafikkarte.
		/// Wird als Parameter ein Null-Pointer uebergeben, werden die Buffer-Daten nicht aktualisiert.
		///
		/// \param pBufferData Vertex-Buffer-Daten
		///
		////////////////////////////////////////////////////////////
		void updateBuffer( const void* pBufferData );

		////////////////////////////////////////////////////////////
		/// \brief Loescht die Vertex-Buffer-Daten aus dem Videospeicher der Grafikkarte.
		/// Die Methode wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		void deleteBuffer(void);
	};
};
