#include "GLSegmentedDepthImage.h"

namespace DirectLook
{
	GLSegmentedDepthImage::GLSegmentedDepthImage(void)
		:
		SegmentedDepthImage(),
		m_pTextureHeightMap( 0 ),
		m_pVertexHeightMap( 0 ),
		m_Invert( false ),
		m_VertexRangeFactor( 1.0f )
	{
		initVertexHeightMap();
	}

	GLSegmentedDepthImage::GLSegmentedDepthImage( const GLSegmentedDepthImage& copy )
		:
		SegmentedDepthImage( copy ),
		m_pTextureHeightMap( new GLubyte[m_PixelSize] ),
		m_pVertexHeightMap( new GLfloat[m_PixelSize * 3] ),
		m_Invert( copy.m_Invert ),
		m_VertexRangeFactor( copy.m_VertexRangeFactor )
	{
		if(copy.m_pTextureHeightMap)
		{
			for(unsigned int i = 0; i < m_PixelSize; i++)
			{
				m_pTextureHeightMap[i] = copy.m_pTextureHeightMap[i];
			}
		}

		if(copy.m_pVertexHeightMap)
		{
			unsigned int size = m_PixelSize * 3;
			for(unsigned int i = 0; i < size; i++)
			{
				m_pVertexHeightMap[i] = copy.m_pVertexHeightMap[i];
			}
		}
	}

	GLSegmentedDepthImage::GLSegmentedDepthImage(
		const unsigned short width,
		const unsigned short height,
		const unsigned short nearThreshold,
		const unsigned short farThreshold,
		const bool mirrorMode,
		const bool invert,
		const GLfloat vertexRangeFactor
	)
		:
		SegmentedDepthImage( width, height, nearThreshold, farThreshold, mirrorMode ),
		m_pTextureHeightMap( new GLubyte[m_Height * m_Width] ),
		m_pVertexHeightMap( 0 ),
		m_Invert( invert ),
		m_VertexRangeFactor( 1.0f )
	{
		setVertexRangeFactor( vertexRangeFactor );
		initVertexHeightMap();
	}

	GLSegmentedDepthImage::GLSegmentedDepthImage(
		const unsigned short* pDepthPixels,
		const unsigned short width,
		const unsigned short height,
		const unsigned short nearThreshold,
		const unsigned short farThreshold,
		const bool mirrorMode,
		const bool invert,
		const GLfloat vertexRangeFactor
	)
		:
		SegmentedDepthImage( pDepthPixels, width, height, nearThreshold, farThreshold, mirrorMode ),
		m_pTextureHeightMap( 0 ),
		m_pVertexHeightMap( 0 ),
		m_Invert( invert ),
		m_VertexRangeFactor( 1.0f )
	{
		setVertexRangeFactor( vertexRangeFactor );
		setImage( pDepthPixels, width, height );
	}

	GLSegmentedDepthImage::~GLSegmentedDepthImage(void)
	{
		clear();
	}

	void GLSegmentedDepthImage::setImage( const unsigned short* pDepthPixels, const unsigned short width, const unsigned short height )
	{
		if(pDepthPixels)
		{
			clear();
			m_Width = width;
			m_Height = height;
			m_PixelSize = m_Width * m_Height;
			m_pImagePixels = new unsigned short[m_PixelSize];
			m_pTextureHeightMap = new GLubyte[m_PixelSize];
			initVertexHeightMap();
			updateImage( pDepthPixels );
		}
	}

	void GLSegmentedDepthImage::updateImage( const unsigned short* pDepthPixels )
	{
		if(pDepthPixels)
		{
			m_MinDistance = m_FarThreshold;
			m_MaxDistance = m_NearThreshold;
	
			// Create index
			unsigned int index = 0;

			if(m_MirrorMode)
			{
				for(int y = m_Height - 1; y > 0; y--)
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

						// Compute current index
						index = y * m_Width + x;
						
						// Write height map value
						m_pImagePixels[index]			  = pixelValue;
						m_pTextureHeightMap[index]		  = mapToRangeUByte( pixelValue );
						m_pVertexHeightMap[index * 3 + 2] = (GLfloat) pixelValue;	//mapToRangeFloat( pixelValue );
					}
				}
			}
			else
			{
				for(unsigned int y = m_Height - 1; y > 0; y--)
				{
					for(unsigned int x = 0; x < m_Width; x++)
					{
						unsigned short pixelValue = pDepthPixels[y * m_Width + x];
						
						if(pixelValue < m_NearThreshold)
						{
							pixelValue = 0;
						}
						else if(m_MinDistance > pixelValue)
						{
							m_MinDistance = pixelValue;
						}
						
						if(pixelValue > m_FarThreshold)
						{
							pixelValue = 0;
						}
						else if(m_MaxDistance < pixelValue)
						{
							m_MaxDistance = pixelValue;
						}
						
						// Compute current index
						index = (m_Height - 1 - y) * m_Width + x;
						
						// Write height map value
						m_pImagePixels[index]			  = pixelValue;
						m_pTextureHeightMap[index]		  = mapToRangeUByte( pixelValue );
						m_pVertexHeightMap[index * 3 + 2] = (GLfloat) pixelValue;	//mapToRangeFloat( pixelValue );
					}
				}
			}
	
			if(m_MinDistance == m_FarThreshold)  m_MinDistance = m_NearThreshold;
			if(m_MaxDistance == m_NearThreshold) m_MaxDistance = m_FarThreshold;
		}
	}

	void GLSegmentedDepthImage::replacePixelAt( const unsigned int x, const unsigned int y, const unsigned short pixelValue )
	{
		unsigned int index =  y * m_Width + x;
		if(index < m_PixelSize)
		{
			// Write height map value
			m_pImagePixels[index]			  = pixelValue;
			m_pTextureHeightMap[index]		  = mapToRangeUByte( pixelValue );
			m_pVertexHeightMap[index * 3 + 2] = (GLfloat) pixelValue;//mapToRangeFloat( pixelValue );
		}
	}

	void GLSegmentedDepthImage::setResolution( const unsigned short width, const unsigned short height )
	{
		clear();
		m_Width = width;
		m_Height = height;
		m_PixelSize = m_Width * m_Height;

		m_pImagePixels		= new unsigned short[m_PixelSize];
		m_pTextureHeightMap = new GLubyte[m_PixelSize];
		m_pVertexHeightMap	= new GLfloat[m_PixelSize * 3];
		
		initVertexHeightMap();
	}

	const GLubyte* GLSegmentedDepthImage::getTextureHeightMap(void)
	{
		return m_pTextureHeightMap;
	}

	const GLfloat* GLSegmentedDepthImage::getVertexHeightMap(void)
	{
		return m_pVertexHeightMap;
	}

	void GLSegmentedDepthImage::setVertexRangeFactor( const GLfloat vertexRangeFactor )
	{
		if(vertexRangeFactor > 0.0f)
		{
			m_VertexRangeFactor = vertexRangeFactor;
		}
		else
		{
			m_VertexRangeFactor = 1.0f;
		}

	}
	
	GLfloat GLSegmentedDepthImage::getVertexRangeFactor(void)
	{
		return m_VertexRangeFactor;
	}

	void GLSegmentedDepthImage::initVertexHeightMap(void)
	{
		// Leeren Vertex-Buffer erzeugen
		unsigned int bufferSize = m_Height * m_Width * 3;
		m_pVertexHeightMap = new GLfloat[bufferSize];

		// Halbe Hoehe und Breite berechnen
		GLfloat widthHalf  = (GLfloat) m_Width  * 0.5f;
		GLfloat heightHalf = (GLfloat) m_Height * 0.5f;

		// 3D-Grid fuer die Depth Map erzeugen
		for(unsigned int y = 0; y < m_Height; y++)
		{
			unsigned int x = 0;
			unsigned int index = y * m_Width * 3;			
			for(unsigned int i = 0; i < (unsigned int)m_Width * 3; i += 3)
			{
				m_pVertexHeightMap[index + i]	  = (GLfloat) x - widthHalf;
				m_pVertexHeightMap[index + i + 1] = (GLfloat) y - heightHalf;
				m_pVertexHeightMap[index + i + 2] = 0.0f;
				x++;
			}
		}
	}

	GLubyte GLSegmentedDepthImage::mapToRangeUByte( const unsigned short pixelValue )
	{
		GLubyte returnValue;
	
		if(pixelValue > m_FarThreshold)
		{
			returnValue = 0;
		}
		else if(pixelValue < m_NearThreshold)
		{
			returnValue = 255;
		}
		else
		{
			returnValue = (GLubyte) ((255.0f / (m_FarThreshold - m_NearThreshold)) * (pixelValue - m_NearThreshold));
			if(m_Invert)
			{
				returnValue = 255 - returnValue;
			}
		}

		return returnValue;
	}

	GLfloat GLSegmentedDepthImage::mapToRangeFloat( const unsigned short pixelValue )
	{
		GLfloat returnValue;
	
		if(pixelValue > m_FarThreshold || pixelValue < m_NearThreshold)
		{
			returnValue = 0.0f;
		}
		else
		{
			GLfloat n = (GLfloat) m_NearThreshold;
			GLfloat f = (GLfloat) m_FarThreshold;
			returnValue = (GLfloat) ((m_VertexRangeFactor / (m_FarThreshold - m_NearThreshold)) * (pixelValue - m_NearThreshold));
			if(m_Invert)
			{
				returnValue = m_VertexRangeFactor - returnValue;
			}
		}

		return returnValue;
	}

	void GLSegmentedDepthImage::clear(void)
	{
		SegmentedDepthImage::clear();
		if(m_pTextureHeightMap)
		{
			delete[] m_pTextureHeightMap;
			m_pTextureHeightMap = 0;
		}
		
		if(m_pVertexHeightMap)
		{
			delete[] m_pVertexHeightMap;
			m_pVertexHeightMap = 0;
		}
	}
};
