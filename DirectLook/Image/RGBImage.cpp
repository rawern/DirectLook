#include "RGBImage.h"

namespace DirectLook
{
	RGBImage::RGBImage(void)
		:
		m_pImagePixels( 0 ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_PixelSize( 0 ),
		m_MirrorMode( false )
	{
	}

	RGBImage::RGBImage( const RGBImage& copy )
		:
		m_pImagePixels( 0 ),
		m_Width( copy.m_Width ),
		m_Height( copy.m_Height ),
		m_PixelSize( copy.m_PixelSize ),
		m_MirrorMode( copy.m_MirrorMode )
	{
		if(copy.m_pImagePixels)
		{
			m_pImagePixels = new unsigned char[m_PixelSize];
			for(unsigned int i = 0; i < m_PixelSize; i++)
			{
				m_pImagePixels[i] = copy.m_pImagePixels[i];
			}
		}
	}

	RGBImage::RGBImage( const unsigned short width, const unsigned short height, const bool mirrorMode )
		:
		m_pImagePixels( new unsigned char[width * height * 3] ),
		m_Width( width ),
		m_Height( height ),
		m_PixelSize( m_Width * m_Height * 3 ),
		m_MirrorMode( mirrorMode )
	{
	}

	RGBImage::RGBImage(
		const unsigned char* pImagePixels,
		const unsigned short width,
		const unsigned short height,
		const bool mirrorMode
	)
		:
		m_pImagePixels( 0 ),
		m_MirrorMode( mirrorMode )
	{
		setImage( pImagePixels, width, height );
	}
		
	RGBImage::~RGBImage(void)
	{
		clear();
	}
		
	void RGBImage::setImage( const unsigned char* pImagePixels, const unsigned short width, const unsigned short height )
	{
		if(pImagePixels)
		{
			clear();
			m_Width = width;
			m_Height = height;
			m_PixelSize = m_Width * m_Height * 3;
			m_pImagePixels = new unsigned char[m_PixelSize];
			updateImage( pImagePixels );
		}
	}

	void RGBImage::updateImage( const unsigned char* pImagePixels )
	{
		if(pImagePixels)
		{
			if(m_MirrorMode)
			{
				unsigned int index = 0;
				for(unsigned int y = 0; y < m_Height; y++)
				{
					for(unsigned int x = 0; x < (unsigned int)m_Width * 3; x += 3)
					{
						m_pImagePixels[index]	  = pImagePixels[(y * m_Width + m_Width - 1) * 3 - x];
						m_pImagePixels[index + 1] = pImagePixels[(y * m_Width + m_Width - 1) * 3 - x + 1];
						m_pImagePixels[index + 2] = pImagePixels[(y * m_Width + m_Width - 1) * 3 - x + 2];
						index += 3;
					}
				}
			}
			else
			{
				for(unsigned int i = 0; i < m_PixelSize; i++)
				{
					m_pImagePixels[i] = pImagePixels[i];
				}
			}
		}
	}

	void RGBImage::replacePixelAt( const unsigned int x, const unsigned int y, const unsigned char red, const unsigned char green, const unsigned char blue )
	{
		unsigned int index =  (y * m_Width + x) * 3;
		if(index < (m_PixelSize - 3))
		{
			m_pImagePixels[index]	  = red;
			m_pImagePixels[index + 1] = green;
			m_pImagePixels[index + 2] = blue;
		}
	}
	
	void RGBImage::setResolution( const unsigned short width, const unsigned short height )
	{
		clear();
		m_Width = width;
		m_Height = height;
		m_PixelSize = m_Width * m_Height * 3;
		m_pImagePixels = new unsigned char[m_PixelSize];
	}

	const unsigned char RGBImage::pixelRedAt( const unsigned int x, const unsigned int y )
	{
		unsigned int index =  (y * m_Width + x) * 3;
		if(index < (m_PixelSize - 3)) return m_pImagePixels[index];
		return 0;
	}

	const unsigned char RGBImage::pixelGreenAt( const unsigned int x, const unsigned int y )
	{
		unsigned int index =  (y * m_Width + x) * 3;
		if(index < (m_PixelSize - 3)) return m_pImagePixels[index + 1];
		return 0;
	}

	const unsigned char RGBImage::pixelBlueAt( const unsigned int x, const unsigned int y )
	{
		unsigned int index =  (y * m_Width + x) * 3;
		if(index < (m_PixelSize - 3)) return m_pImagePixels[index + 2];
		return 0;
	}
		
	const unsigned short RGBImage::getWidth(void)
	{
		return m_Width;
	}

	const unsigned short RGBImage::getHeight(void)
	{
		return m_Height;
	}
		
	const bool RGBImage::getMirrorMode(void)
	{
		return m_MirrorMode;
	}

	void RGBImage::setMirrorMode( const bool mirrorMode )
	{
		m_MirrorMode = mirrorMode;
	}

	void RGBImage::clone( const unsigned char* pImagePixels )
	{
		if(pImagePixels)
		{
			m_PixelSize = m_Width * m_Height * 3;
			m_pImagePixels = new unsigned char[m_PixelSize];
			for(unsigned int i = 0; i < m_PixelSize; i++)
			{
				m_pImagePixels[i] = pImagePixels[i];
			}
		}
	}

	const unsigned int RGBImage::getPixelSize(void)
	{
		return m_PixelSize;
	}

	void RGBImage::clear(void)
	{
		if(m_pImagePixels != 0)
		{
			delete[] m_pImagePixels;
			m_pImagePixels = 0;
		}
	}
}
