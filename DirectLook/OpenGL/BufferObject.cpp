#include "BufferObject.h"

namespace DirectLook 
{

	BufferObject::BufferObject(void)
		:
		m_Target( GL_ARRAY_BUFFER ),
		m_UpdateTarget( GL_ARRAY_BUFFER_ARB ),
		m_ID( 0 ),
		m_Size( 0 ),
		m_Length( 0 ),
		m_Stride( 0 )
	{
	}

	BufferObject::BufferObject( const GLsizei bufferElements, const GLint length, const GLsizei stride, const GLenum target, const GLenum updateTarget )
		:
		m_Target( target ),
		m_UpdateTarget( updateTarget ),
		m_ID( 0 ),
		m_Size( bufferElements * length ),
		m_Length( length ),
		m_Stride( stride )
	{
	}

	BufferObject::~BufferObject(void)
	{
	}

	GLenum BufferObject::getTarget(void) const
	{
		return m_Target;
	}

	void BufferObject::setTarget( const GLenum target )
	{
		switch(target)
		{
			case GL_ARRAY_BUFFER:			m_Target = target; break;
			case GL_ELEMENT_ARRAY_BUFFER:	m_Target = target; break;
		}
	}
	
	GLenum BufferObject::getUpdateTarget(void) const
	{
		return m_UpdateTarget;
	}

	void BufferObject::setUpdateTarget( const GLenum updateTarget )
	{
		switch(updateTarget)
		{
			case GL_ARRAY_BUFFER_ARB:			m_UpdateTarget = updateTarget; break;
			case GL_ELEMENT_ARRAY_BUFFER_ARB:	m_UpdateTarget = updateTarget; break;
		}
	}

	GLuint BufferObject::getID(void) const
	{
		return m_ID;
	}

	GLsizei BufferObject::getSize(void) const
	{
		return m_Size;
	}

	GLint BufferObject::getLength(void) const
	{
		return m_Length;
	}
		
	GLsizei BufferObject::getStride(void) const
	{
		return m_Stride;
	}
}
