#include "RenderTarget.h"

namespace DirectLook
{
	RenderTarget::RenderTarget( unsigned int width, unsigned int height )
		:
		m_FrameBufferID( 0 ),
		m_RenderBufferID( 0 ),
		m_TextureID( 0 ),
		m_Width( width ),
		m_Height( height ),
		m_IsInitialized( false ),
		m_pPixels( new GLubyte[width * height * 3] )
	{
		initialize();
	}

	RenderTarget::~RenderTarget(void)
	{
		if(m_pPixels)
		{
			delete[] m_pPixels;
			m_pPixels = 0;
		}

		glDeleteFramebuffersEXT( GL_FRAMEBUFFER_EXT, &m_FrameBufferID );
	}

	void RenderTarget::enable(void)
	{
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_FrameBufferID );
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, m_Width, m_Height );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void RenderTarget::disable(void)
	{
		glPopAttrib();
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	}

	GLubyte* RenderTarget::getPixels(void)
	{
		if(!m_pPixels)
		{
			m_pPixels = new GLubyte[m_Width * m_Height * 3];
		}

		// Read texture raw data from frame buffer object and save it in pPixels
		glBindTexture( GL_TEXTURE_2D, m_TextureID );
		glGetTexImage( GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pPixels );

		return m_pPixels;
	}

	bool RenderTarget::getPixels(GLubyte* pBuffer, const unsigned int size, GLint format)
	{
		if(size < m_Width * m_Height * (24 / 8))
			return false; //Too small buffer

		// Read texture raw data from frame buffer object and save it in pPixels
		glBindTexture( GL_TEXTURE_2D, m_TextureID );
		glGetTexImage( GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, pBuffer );

		return true;
	}

	void RenderTarget::initialize(void)
	{
		if(!m_IsInitialized)
		{
			// Generate frame buffer object
			glGenFramebuffersEXT( 1, &m_FrameBufferID );
			glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_FrameBufferID );
			
			// Generate depth buffer object
			glGenRenderbuffersEXT( 1, &m_RenderBufferID );
			glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_RenderBufferID );
			glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, m_Width, m_Height );
			glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_RenderBufferID ); 
		
			// Generate texture object
			glGenTextures( 1, &m_TextureID );
			glBindTexture( GL_TEXTURE_2D, m_TextureID );
			glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,  m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 );
			glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureID, 0 );
		
			// Check frame buffer object
			checkFrameBufferObject();
			std::cout << std::endl;

			// Initializing complete
			m_IsInitialized = true;
		}
	}

	void RenderTarget::checkFrameBufferObject(void)
	{
		GLenum error;
		error = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
		
		// Show Status
		std::cout << std::endl;
		std::cout << "Render Target       : OK" << std::endl;
		std::cout << "Frame Buffer Object : ";
		
		switch(error)
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				std::cout << "OK" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
				std::cout << "Incomplete attachment" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
				std::cout << "Missing attachment" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
				std::cout << "Incomplete dimensions" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
				std::cout << "Incomplete formats" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
				std::cout << "Incomplete draw buffer" << std::endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
				std::cout << "Incomplete read buffer" << std::endl;
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				std::cout << "Framebufferobjects unsupported" << std::endl;
				break;
		}
	}
}
