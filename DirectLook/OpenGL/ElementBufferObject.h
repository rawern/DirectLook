#pragma once

#include "BufferObject.h"

namespace DirectLook 
{
	/// \brief Die Klasse Element-Buffer-Object repraesentiert einen OpenGL Element-Buffer. 
	class ElementBufferObject : public BufferObject 
	{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein neues Element-Buffer-Objekt.
		///
		////////////////////////////////////////////////////////////
		ElementBufferObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor A
		///
		/// Erzeugt ein Element-Buffer-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param bufferElements Anzahl der Bufferelemente
		/// \param target		  OpenGL Buffer-Target (Standardwert: GL_ELEMENT_ARRAY_BUFFER)
		/// \param updateTarget	  OpenGL Buffer-Update-Target (Standardwert: GL_ELEMENT_ARRAY_BUFFER_ARB)
		///
		////////////////////////////////////////////////////////////
		ElementBufferObject(
			const GLsizei bufferElements,								// Number of buffer elements
			const GLenum target = GL_ELEMENT_ARRAY_BUFFER,				// OpenGL element buffer target
			const GLenum updateTarget = GL_ELEMENT_ARRAY_BUFFER_ARB		// OpenGL element buffer update target
		);

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor B
		///
		/// Erzeugt ein Element-Buffer-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param pBufferData	  Daten des Element-Buffers
		/// \param bufferElements Anzahl der Bufferelemente
		/// \param target		  OpenGL Buffer-Target (Standardwert: GL_ELEMENT_ARRAY_BUFFER)
		/// \param updateTarget	  OpenGL Buffer-Update-Target (Standardwert: GL_ELEMENT_ARRAY_BUFFER_ARB)
		///
		////////////////////////////////////////////////////////////
		ElementBufferObject(
			const void* pBufferData,									// Element buffer data
			const GLsizei bufferElements,								// Number of buffer elements
			const GLenum target = GL_ELEMENT_ARRAY_BUFFER,				// OpenGL element buffer target
			const GLenum updateTarget = GL_ELEMENT_ARRAY_BUFFER_ARB		// OpenGL element buffer update target
		);

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das Element-Buffer-Obekt aus dem Videospeicher der Grafikkarte.
		///
		////////////////////////////////////////////////////////////
		virtual ~ElementBufferObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Generiert eine eindeutige OpenGL Buffer ID und laedt die Buffer-Daten in den Videospeicher der Grafikkarte.
		/// Wird als Parameter ein Null-Pointer uebergeben, werden keine Buffer-Daten in den Videospeicher geladen und keine OpenGL Buffer ID generiert.
		///
		/// \param pBufferData Die neuen Dates des Element-Buffers
		///
		////////////////////////////////////////////////////////////
		void generateBuffer( const void* pBufferData );

		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Element-Buffer-Daten im Videospeicher der Grafikkarte.
		/// Wird als Parameter ein Null-Pointer uebergeben, werden die Buffer-Daten nicht aktualisiert.
		///
		/// \param pBufferData Element-Buffer-Daten
		///
		////////////////////////////////////////////////////////////
		void updateBuffer( const void* pBufferData );

		////////////////////////////////////////////////////////////
		/// \brief Loescht die Element-Buffer-Daten aus dem Videospeicher der Grafikkarte.
		/// Die Methode wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		void deleteBuffer(void);
	};
};
