#include "ElementBufferObject.h"

namespace DirectLook
{
	ElementBufferObject::ElementBufferObject(void) : BufferObject()
	{
		m_Length = 1;
		m_Stride = sizeof( GLuint );
	}

	ElementBufferObject::ElementBufferObject(
		const GLsizei bufferElements,
		const GLenum target,
		const GLenum updateTarget
	) : BufferObject( bufferElements, 1, sizeof( GLuint ), target, updateTarget )
	{
		m_Length = 1;
		m_Stride = sizeof( GLuint );
	}

	ElementBufferObject::ElementBufferObject(
		const void* pBufferData,
		const GLsizei bufferElements,
		const GLenum target,
		const GLenum updateTarget
	) :	BufferObject( bufferElements, 1, sizeof( GLuint ), target, updateTarget )
	{
		generateBuffer( pBufferData );
	}

	ElementBufferObject::~ElementBufferObject(void)
	{
		deleteBuffer();
	}

	void ElementBufferObject::generateBuffer( const void* pBufferData )
	{
		if(pBufferData && m_ID == 0)
		{
			glGenBuffers( 1, &m_ID );
			glBindBuffer( m_Target, m_ID );
			glBufferData( m_Target, sizeof( GLuint ) * m_Size, pBufferData, GL_STATIC_DRAW );
		}
	}

	void ElementBufferObject::updateBuffer( const void* pBufferData )
	{
		if(pBufferData && m_ID > 0)
		{
			glBindBuffer( m_Target, m_ID );
			glBufferData( m_Target, sizeof( GLuint ) * m_Size, pBufferData, GL_STATIC_DRAW );
		}
	}

	void ElementBufferObject::deleteBuffer(void)
	{
		if(m_ID > 0)
		{
			glDeleteBuffers( 1, &m_ID );
		}
	}
}
