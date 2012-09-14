#include "TextureObject.h"

namespace DirectLook
{
	TextureObject::TextureObject(void)
		:
		m_Border( 0 ),
		m_ExternalFormat( GL_RGB ),
		m_Height( 0 ),
		m_ID( 0 ),
		m_InternalFormat( GL_RGB8 ),
		m_Level( 0 ),
		m_Target( GL_TEXTURE_2D ),
		m_Type( GL_UNSIGNED_BYTE ),
		m_Width( 0 )
	{
	}
	
	TextureObject::TextureObject( 
		const GLsizei width,
		const GLsizei height,
		const GLint border,
		const GLenum externalFormat,
		const GLint internalFormat,
		const GLint level,
		const GLenum target,
		const GLenum type
	)
		:
		m_Border( border ),
		m_Height( height ),
		m_ID( 0 ),
		m_Level( level ),
		m_Width( width )
	{
		setExternalFormat( externalFormat );
		setInternalFormat( internalFormat );
		setTarget( target );
		setType( type );
	}

	TextureObject::~TextureObject(void)
	{
		deleteTexture();
	}

	GLint TextureObject::getBorder(void) const
	{
		return m_Border;
	}
	
	GLenum TextureObject::getExternalFormat(void) const
	{
		return m_ExternalFormat;
	}
	
	GLsizei TextureObject::getHeight(void) const
	{
		return m_Height;
	}
	
	GLuint TextureObject::getID(void) const
	{
		return m_ID;
	}
	
	GLint TextureObject::getInternalFormat(void) const
	{
		return m_InternalFormat;
	}
	
	GLint TextureObject::getLevel(void) const
	{
		return m_Level;
	}
	
	GLenum TextureObject::getTarget(void) const
	{
		return m_Target;
	}
	
	GLenum TextureObject::getType(void) const
	{
		return m_Type;
	}
	
	GLsizei TextureObject::getWidth(void) const
	{
		return m_Width;
	}

	void TextureObject::setBorder( GLint border )
	{
		m_Border = border;
	}
	
	void TextureObject::setExternalFormat( GLenum externalFormat )
	{
		switch(externalFormat)
		{
			case GL_COLOR_INDEX:		m_ExternalFormat = externalFormat; break;
			case GL_RED:				m_ExternalFormat = externalFormat; break;
			case GL_GREEN:				m_ExternalFormat = externalFormat; break;
			case GL_BLUE:				m_ExternalFormat = externalFormat; break;
			case GL_ALPHA:				m_ExternalFormat = externalFormat; break;
			case GL_RGB:				m_ExternalFormat = externalFormat; break;
			case GL_BGR:				m_ExternalFormat = externalFormat; break;
			case GL_RGBA:				m_ExternalFormat = externalFormat; break;
			case GL_BGRA:				m_ExternalFormat = externalFormat; break;
			case GL_LUMINANCE:			m_ExternalFormat = externalFormat; break;			
			case GL_LUMINANCE_ALPHA:	m_ExternalFormat = externalFormat; break;

			default:
				m_ExternalFormat = GL_RGB;
		}
	}
	
	void TextureObject::setHeight( GLsizei height )
	{
		m_Height = height;
	}
	
	void TextureObject::setInternalFormat( GLint internalFormat )
	{
		switch(internalFormat)
		{
			case 1:	m_InternalFormat = internalFormat; break;	// 1 fuer R
			case 2:	m_InternalFormat = internalFormat; break;	// 2 fuer R und A
			case 3:	m_InternalFormat = internalFormat; break;	// 3 fuer RGB
			case 4:	m_InternalFormat = internalFormat; break;	// 4 fuer RGBA

			case GL_ALPHA:						m_InternalFormat = internalFormat; break;
			case GL_ALPHA4:						m_InternalFormat = internalFormat; break;
			case GL_ALPHA8:						m_InternalFormat = internalFormat; break;
			case GL_ALPHA12:					m_InternalFormat = internalFormat; break;
			case GL_ALPHA16:					m_InternalFormat = internalFormat; break;
			case GL_COMPRESSED_ALPHA:			m_InternalFormat = internalFormat; break;
			case GL_COMPRESSED_LUMINANCE:		m_InternalFormat = internalFormat; break;
			case GL_COMPRESSED_LUMINANCE_ALPHA:	m_InternalFormat = internalFormat; break;
			case GL_COMPRESSED_INTENSITY:		m_InternalFormat = internalFormat; break;
			case GL_COMPRESSED_RGB:				m_InternalFormat = internalFormat; break;
			case GL_COMPRESSED_RGBA:			m_InternalFormat = internalFormat; break;
			case GL_DEPTH_COMPONENT:			m_InternalFormat = internalFormat; break;
			case GL_DEPTH_COMPONENT16:			m_InternalFormat = internalFormat; break;
			case GL_DEPTH_COMPONENT24:			m_InternalFormat = internalFormat; break;
			case GL_DEPTH_COMPONENT32:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE:					m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE4:					m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE8:					m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE12:				m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE16:				m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE_ALPHA:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE4_ALPHA4:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE6_ALPHA2:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE8_ALPHA8:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE12_ALPHA4:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE12_ALPHA12:		m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE16_ALPHA16:		m_InternalFormat = internalFormat; break;
			case GL_INTENSITY:					m_InternalFormat = internalFormat; break;
			case GL_INTENSITY4:					m_InternalFormat = internalFormat; break;
			case GL_INTENSITY8:					m_InternalFormat = internalFormat; break;
			case GL_INTENSITY12:				m_InternalFormat = internalFormat; break;
			case GL_INTENSITY16:				m_InternalFormat = internalFormat; break;
			case GL_R3_G3_B2:					m_InternalFormat = internalFormat; break;
			case GL_RGB:						m_InternalFormat = internalFormat; break;
			case GL_RGB4:						m_InternalFormat = internalFormat; break;
			case GL_RGB5:						m_InternalFormat = internalFormat; break;
			case GL_RGB8:						m_InternalFormat = internalFormat; break;
			case GL_RGB10:						m_InternalFormat = internalFormat; break;
			case GL_RGB12:						m_InternalFormat = internalFormat; break;
			case GL_RGB16:						m_InternalFormat = internalFormat; break;
			case GL_RGBA:						m_InternalFormat = internalFormat; break;
			case GL_RGBA2:						m_InternalFormat = internalFormat; break;
			case GL_RGBA4:						m_InternalFormat = internalFormat; break;
			case GL_RGB5_A1:					m_InternalFormat = internalFormat; break;
			case GL_RGBA8:						m_InternalFormat = internalFormat; break;
			case GL_RGB10_A2:					m_InternalFormat = internalFormat; break;
			case GL_RGBA12:						m_InternalFormat = internalFormat; break;
			case GL_RGBA16:						m_InternalFormat = internalFormat; break;
			case GL_SLUMINANCE:					m_InternalFormat = internalFormat; break;
			case GL_SLUMINANCE8:				m_InternalFormat = internalFormat; break;
			case GL_SLUMINANCE_ALPHA:			m_InternalFormat = internalFormat; break;
			case GL_SLUMINANCE8_ALPHA8:			m_InternalFormat = internalFormat; break;
			case GL_SRGB:						m_InternalFormat = internalFormat; break;
			case GL_SRGB8:						m_InternalFormat = internalFormat; break;
			case GL_SRGB_ALPHA:					m_InternalFormat = internalFormat; break;
			case GL_SRGB8_ALPHA8:				m_InternalFormat = internalFormat; break;
			
			// New Formats
			case GL_RGB32F_ARB:				m_InternalFormat = internalFormat; break;			
			case GL_FLOAT_RGB32_NV:			m_InternalFormat = internalFormat; break;
			case GL_RGBA32F_ARB:			m_InternalFormat = internalFormat; break;			
			case GL_FLOAT_RGBA32_NV:		m_InternalFormat = internalFormat; break;
			case GL_FLOAT_R32_NV:			m_InternalFormat = internalFormat; break;
			case GL_LUMINANCE_FLOAT32_ATI:	m_InternalFormat = internalFormat; break;
			//case GL_RGBA_FLOAT32_ATI:		m_InternalFormat = internalFormat; break;

			default:
				m_InternalFormat = 3; break;	// Default RGB
		}
	}
	
	void TextureObject::setLevel( GLint level )
	{
		m_Level = level;
	}
	
	void TextureObject::setTarget( GLenum target )
	{
		switch(target)
		{
			case GL_TEXTURE_2D:						m_Target = target; break;
			case GL_PROXY_TEXTURE_2D:				m_Target = target; break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_X:	m_Target = target; break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:	m_Target = target; break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:	m_Target = target; break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:	m_Target = target; break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:	m_Target = target; break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:	m_Target = target; break;
			case GL_PROXY_TEXTURE_CUBE_MAP:			m_Target = target; break;
			
			default: 
				m_Target = GL_TEXTURE_2D; break;
		}
	}
	
	void TextureObject::setType( GLenum type )
	{
		switch(type)
		{
			case GL_UNSIGNED_BYTE:					m_Type = type; break;
			case GL_BYTE:							m_Type = type; break;
			case GL_BITMAP:							m_Type = type; break;
			case GL_UNSIGNED_SHORT:					m_Type = type; break;
			case GL_SHORT:							m_Type = type; break;
			case GL_UNSIGNED_INT:					m_Type = type; break;
			case GL_INT:							m_Type = type; break;
			case GL_FLOAT:							m_Type = type; break;
			case GL_UNSIGNED_BYTE_3_3_2:			m_Type = type; break;
			case GL_UNSIGNED_BYTE_2_3_3_REV:		m_Type = type; break;
			case GL_UNSIGNED_SHORT_5_6_5:			m_Type = type; break;
			case GL_UNSIGNED_SHORT_5_6_5_REV:		m_Type = type; break;
			case GL_UNSIGNED_SHORT_4_4_4_4:			m_Type = type; break;
			case GL_UNSIGNED_SHORT_4_4_4_4_REV:		m_Type = type; break;
			case GL_UNSIGNED_SHORT_5_5_5_1:			m_Type = type; break;
			case GL_UNSIGNED_SHORT_1_5_5_5_REV:		m_Type = type; break;
			case GL_UNSIGNED_INT_8_8_8_8:			m_Type = type; break;
			case GL_UNSIGNED_INT_8_8_8_8_REV:		m_Type = type; break;
			case GL_UNSIGNED_INT_10_10_10_2:		m_Type = type; break;
			case GL_UNSIGNED_INT_2_10_10_10_REV:	m_Type = type; break;
		
			default: 
				m_Type = GL_UNSIGNED_BYTE; break;
		}
	}
	
	void TextureObject::setWidth( GLsizei width )
	{
		m_Width = width;
	}

	void TextureObject::generateTexture(void)
	{
		if(m_ID == 0)
		{
			glGenTextures( 1, &m_ID );
		}
	}

	void TextureObject::generateTexture( const void* pPixels )
	{
		if(pPixels && m_ID == 0)
		{
			glGenTextures( 1, &m_ID );
			updateTexture( pPixels );
		}
	}

	void TextureObject::updateTexture( const void* pPixels )
	{
		if(pPixels && m_ID > 0)
		{
			glBindTexture( m_Target, m_ID );
			
			// FESTE FILTERWERTE
			glTexParameteri( m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( m_Target, GL_TEXTURE_WRAP_S,     GL_REPEAT );
			glTexParameteri( m_Target, GL_TEXTURE_WRAP_T,     GL_REPEAT );
			
			/*
			// Only for vertex shader 
			glTexParameteri( m_Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( m_Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
			*/
			glTexImage2D(
				m_Target, m_Level,				/* target, level */
				m_InternalFormat,				/* internal format */
				m_Width, m_Height, m_Border,	/* width, height, border */
				m_ExternalFormat, m_Type,		/* external format, type */
				pPixels							/* pixels */
			);
		}
	}

	void TextureObject::deleteTexture(void)
	{
		if(m_ID > 0)
		{
			glDeleteTextures( 1, &m_ID );
		}
	}
};
