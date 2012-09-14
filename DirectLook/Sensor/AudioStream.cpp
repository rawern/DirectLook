#include "AudioStream.h"

namespace DirectLook 
{
	AudioStream::AudioStream(void)
		:
		m_BitsPerSample( 16 ),
		m_Channels( 2 ),
		m_SampleRate( 44100 ),
		m_pAudioBuffer( 0 ),
		m_BufferSize( 0 )
	{
	}

	AudioStream::AudioStream( const AudioStream& copy )
		:
		m_BitsPerSample( copy.m_BitsPerSample ),
		m_Channels( copy.m_Channels ),
		m_SampleRate( copy.m_SampleRate ),
		m_pAudioBuffer( 0 ),
		m_BufferSize( 0 )
	{
		setBufferSize( copy.m_BufferSize );
		setAudioBuffer( copy.m_pAudioBuffer );
	}
	
	AudioStream::~AudioStream(void)
	{
		if(m_pAudioBuffer)
		{
			delete[] m_pAudioBuffer;
			m_pAudioBuffer = 0;
		}
	}

	void AudioStream::setBitsPerSample( const unsigned short bitsPerSample )
	{
		m_BitsPerSample = bitsPerSample;
	}
	
	void AudioStream::setChannels( const unsigned char channels )
	{
		m_Channels = channels;
	}
	
	void AudioStream::setSampleRate( const unsigned int sampleRate )
	{
		m_SampleRate = sampleRate;
	}
	
	void AudioStream::setAudioBuffer( const unsigned char* pAudioBuffer )
	{
		if(pAudioBuffer)
		{
			if(!m_pAudioBuffer)
			{
				m_pAudioBuffer = new unsigned char[m_BufferSize];
			}

			for(unsigned int i = 0; i < m_BufferSize; i++)
			{
				m_pAudioBuffer[i] = pAudioBuffer[i];
			}
		}
	}
	
	void AudioStream::setBufferSize( const unsigned int bufferSize )
	{
		if(m_pAudioBuffer)
		{
			delete[] m_pAudioBuffer;
			m_pAudioBuffer = 0;
		}
		
		m_pAudioBuffer = new unsigned char[bufferSize];
		m_BufferSize = bufferSize;
	}

	unsigned short AudioStream::getBitsPerSample(void) const
	{
		return m_BitsPerSample;
	}
	
	unsigned char AudioStream::getChannels(void) const
	{
		return m_Channels;
	}
	
	unsigned int AudioStream::getSampleRate(void) const
	{
		return m_SampleRate;
	}
	
	const unsigned char* AudioStream::getAudioBuffer(void) const
	{
		return m_pAudioBuffer;
	}
	
	unsigned int AudioStream::getBufferSize(void) const
	{
		return m_BufferSize;
	}
};
