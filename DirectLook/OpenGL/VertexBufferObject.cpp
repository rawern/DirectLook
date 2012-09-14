#include "VertexBufferObject.h"

namespace DirectLook
{
	VertexBufferObject::VertexBufferObject(void) : BufferObject()
	{
	}

	VertexBufferObject::VertexBufferObject(
		const GLsizei bufferElements,
		const GLint length,
		const GLenum target,
		const GLenum updateTarget
	)
		: BufferObject( bufferElements, length, sizeof( GLfloat ) * length, target, updateTarget )
	{
	}

	VertexBufferObject::VertexBufferObject(
		const void* pBufferData,
		const GLsizei bufferElements,
		const GLint length,
		const GLenum target,
		const GLenum updateTarget
	)
		: BufferObject( bufferElements, length, sizeof( GLfloat ) * length, target, updateTarget )
	{
		generateBuffer( pBufferData );
	}

	VertexBufferObject::~VertexBufferObject(void)
	{
		deleteBuffer();
	}

	void VertexBufferObject::generateBuffer( const void* pBufferData )
	{
		if(pBufferData && m_ID == 0)
		{
			glGenBuffers( 1, &m_ID );
			glBindBuffer( m_Target, m_ID );
			glBufferData( m_Target, sizeof( GLfloat ) * m_Size, pBufferData, GL_STATIC_DRAW );
		}
	}

	void VertexBufferObject::updateBuffer( const void* pBufferData )
	{
		if(pBufferData && m_ID > 0)
		{
			glBindBuffer( m_Target, m_ID );
			glBufferData( m_Target, sizeof( GLfloat ) * m_Size, pBufferData, GL_STATIC_DRAW );
		}
	}

	void VertexBufferObject::deleteBuffer(void)
	{
		if(m_ID > 0)
		{
			glDeleteBuffers( 1, &m_ID );
		}
	}
};
