#include "SegmentedDepthImage.h"

namespace DirectLook
{
	SegmentedDepthImage::SegmentedDepthImage(void)
		:
		DepthImage(),
		m_MinDistance( 0 ),
		m_MaxDistance( 0 ),
		m_NearThreshold( MIN_OPEN_NI_THRESHOLD ),
		m_FarThreshold( MAX_OPEN_NI_THRESHOLD )
	{
	}

	SegmentedDepthImage::SegmentedDepthImage( const SegmentedDepthImage& copy )
		:
		DepthImage( copy ),
		m_MinDistance( copy.m_MinDistance ),
		m_MaxDistance( copy.m_MaxDistance ),
		m_NearThreshold( copy.m_NearThreshold ),
		m_FarThreshold( copy.m_FarThreshold )
	{
	}

	SegmentedDepthImage::SegmentedDepthImage(
		const unsigned short width,
		const unsigned short height,
		const unsigned short nearThreshold,
		const unsigned short farThreshold,
		const bool mirrorMode
	)
		:
		DepthImage( width, height, mirrorMode ),
		m_MinDistance( 0 ),
		m_MaxDistance( 0 ),
		m_NearThreshold( nearThreshold ),
		m_FarThreshold( farThreshold )
	{	
	}

	SegmentedDepthImage::SegmentedDepthImage(
		const unsigned short* pDepthPixels,
		const unsigned short width,
		const unsigned short height,
		const unsigned short nearThreshold,
		const unsigned short farThreshold,
		const bool mirrorMode
	)
		:
		DepthImage( pDepthPixels, width, height, mirrorMode ),
		m_MinDistance( 0 ),
		m_MaxDistance( 0 ),
		m_NearThreshold( nearThreshold ),
		m_FarThreshold( farThreshold )
	{
		setImage( pDepthPixels, width, height );
	}

	SegmentedDepthImage::~SegmentedDepthImage(void)
	{
		clear();
	}

	void SegmentedDepthImage::setImage( const unsigned short* pImagePixels, const unsigned short width, const unsigned short height )
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

	void SegmentedDepthImage::updateImage( const unsigned short* pDepthPixels )
	{
		if(pDepthPixels)
		{
			m_MinDistance = m_FarThreshold;
			m_MaxDistance = m_NearThreshold;
	
			if(m_MirrorMode)
			{
				for(int y = 0; y < m_Height; y++)
				{
					for(int x = 0; x < m_Width; x++)
					{
						unsigned short pixelValue = pDepthPixels[y * m_Width + (m_Width - 1) - x];
						if(m_NearThreshold > pixelValue)
						{
							pixelValue = 0;
						}
						else if(m_MinDistance > pixelValue)
						{
							m_MinDistance = pixelValue;
						}
						
						if(m_FarThreshold  < pixelValue)
						{
							pixelValue = 0;
						}
						else if(m_MaxDistance < pixelValue)
						{
							m_MaxDistance = pixelValue;
						}			
						
						m_pImagePixels[y * m_Width + x] = pixelValue;
					}
				}
			}
			else
			{
				for(int y = 0; y < m_Height; y++)
				{
					for(int x = 0; x < m_Width; x++)
					{
						unsigned short pixelValue = pDepthPixels[y * m_Width + x];
						if(m_NearThreshold > pixelValue)
						{
							pixelValue = 0;
						}
						else if(m_MinDistance > pixelValue)
						{
							m_MinDistance = pixelValue;
						}
						
						if(m_FarThreshold  < pixelValue)
						{
							pixelValue = 0;
						}
						else if(m_MaxDistance < pixelValue)
						{
							m_MaxDistance = pixelValue;
						}			
						
						m_pImagePixels[y * m_Width + x] = pixelValue;
					}
				}
			}
	
			if(m_MinDistance == m_FarThreshold)  m_MinDistance = m_NearThreshold;
			if(m_MaxDistance == m_NearThreshold) m_MaxDistance = m_FarThreshold;
		}
	}
	
	const unsigned short SegmentedDepthImage::getMinDistance(void)
	{
		return m_MinDistance;
	}

	const unsigned short SegmentedDepthImage::getMaxDistance(void)
	{
		return m_MaxDistance;
	}

	const unsigned short SegmentedDepthImage::getNearThreshold(void)
	{
		return m_NearThreshold;
	}

	const unsigned short SegmentedDepthImage::getFarThreshold(void)
	{
		return m_FarThreshold;
	}

	void SegmentedDepthImage::setThreshold( const unsigned short nearThreshold, const unsigned short farThreshold )
	{
		m_NearThreshold = nearThreshold;
		m_FarThreshold = farThreshold;
	}

	void SegmentedDepthImage::setNearThreshold( const unsigned short nearThreshold )
	{
		m_NearThreshold = nearThreshold;
	}

	void SegmentedDepthImage::setFarThreshold( const unsigned short farThreshold )
	{
		m_FarThreshold = farThreshold;
	}
}
