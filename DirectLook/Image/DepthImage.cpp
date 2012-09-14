#include "DepthImage.h"

namespace DirectLook
{
	DepthImage::DepthImage(void)
		:
		m_pImagePixels( 0 ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_PixelSize( 0 ),
		m_MirrorMode( false )
	{
	}

	DepthImage::DepthImage( const DepthImage& copy )
		:
		m_pImagePixels( 0 ),
		m_Width( copy.m_Width ),
		m_Height( copy.m_Height ),
		m_PixelSize( copy.m_PixelSize ),
		m_MirrorMode( copy.m_MirrorMode )
	{
		if(copy.m_pImagePixels)
		{
			m_pImagePixels = new unsigned short[m_PixelSize];
			for(unsigned int i = 0; i < m_PixelSize; i++)
			{
				m_pImagePixels[i] = copy.m_pImagePixels[i];
			}
		}
	}
	
	DepthImage::DepthImage( const unsigned short width, const unsigned short height, const bool mirrorMode )
		:
		m_Width( width ),
		m_Height( height ),
		m_PixelSize( m_Width * m_Height ),
		m_MirrorMode( mirrorMode )	
	{
		m_pImagePixels = new unsigned short[m_PixelSize];
	}

	DepthImage::DepthImage(
		const unsigned short* pImagePixels,
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

	DepthImage::~DepthImage(void)
	{
		clear();
	}

	void DepthImage::setImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height )
	{
		if(pImagePixels)
		{
			clear();
			m_Width = width;
			m_Height = height;
			m_PixelSize = m_Width * m_Height;
			m_pImagePixels = new unsigned short[m_PixelSize];
			updateImage( pImagePixels );
		}
	}

	void DepthImage::updateImage( const unsigned short* pImagePixels )
	{
		if(pImagePixels)
		{
			if(m_MirrorMode) {
				for(unsigned int y = 0; y < m_Height; y++) {
					for(unsigned int x = 0; x < m_Width; x++) {
						m_pImagePixels[y * m_Width + x] = pImagePixels[y * m_Width + (m_Width - 1) - x];
					}
				}
			}else {
				for(int y = 0; y < m_Height; y++) {
					for(int x = 0; x < m_Width; x++) {
						m_pImagePixels[y * m_Width + x] = pImagePixels[y * m_Width + x];
					}
				}
			}
		}
	}

	void DepthImage::replacePixelAt( const unsigned int x, const unsigned int y, const unsigned short pixelValue )
	{
		unsigned int index =  y * m_Width + x;
		if(index < m_PixelSize) m_pImagePixels[index] = pixelValue;
	}

	void DepthImage::setResolution( const unsigned short width, const unsigned short height )
	{
		clear();
		m_Width = width;
		m_Height = height;
		m_PixelSize = m_Width * m_Height;
		m_pImagePixels = new unsigned short[m_PixelSize];
	}

	const unsigned short DepthImage::pixelAt( const unsigned int index )
	{
		if(index < m_PixelSize) return m_pImagePixels[index];
		return 0;
	}

	const unsigned short DepthImage::pixelAt( const unsigned int x, const unsigned int y )
	{
		unsigned int index =  y * m_Width + x;
		if(index < m_PixelSize) return m_pImagePixels[index];
		return 0;
	}

	const unsigned short DepthImage::getWidth(void)
	{
		return m_Width;
	}

	const unsigned short DepthImage::getHeight(void)
	{
		return m_Height;
	}

	const bool DepthImage::getMirrorMode(void)
	{
		return m_MirrorMode;
	}

	void DepthImage::setMirrorMode( const bool mirrorMode )
	{
		m_MirrorMode = mirrorMode;
	}

	const unsigned int DepthImage::getPixelSize(void)
	{
		return m_PixelSize;
	}

	void DepthImage::clear(void)
	{
		if(m_pImagePixels != 0)
		{
			delete[] m_pImagePixels;
			m_pImagePixels = 0;
		}
	}
}
