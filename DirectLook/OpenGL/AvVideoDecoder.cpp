#include "AvVideoDecoder.h"

namespace DirectLook 
{
	AvVideoDecoder::AvVideoDecoder()
	{	
	}

	AvVideoDecoder::~AvVideoDecoder()
	{
		av_free(m_pBuffer);
		av_free(m_pFrameRGB);

		av_free(m_pFrame);

		avcodec_close(m_pCodecCtx);
		av_close_input_file(m_pFormatCtx);
	}

	void AvVideoDecoder::init(std::string path)
	{
		av_register_all();	//standard function which has to be called to ensure ffmpeg can be run on the system

		m_pVideostream = -1;	//predeclaring of this variable ensures that no videostream inside the file has been selected yet
		m_pFormatCtx = avformat_alloc_context();	//allocates memory for the FFMpeg FormatContext
		m_pFrame = m_pFrameRGB = m_pResultFrame = 0;	//initializes the Frame pointer. this value will be set to zero so 
												//that frames cannot be seen as falsely initialized

		//this function opens the file using the path. it stores the entire information of the video inside the FormatContext
		if (avformat_open_input(&m_pFormatCtx, path.c_str(), NULL, NULL) != 0)
		{
			handle_error(1);
		}
		//Checks if any stream info on the selected media is available
		if (av_find_stream_info(m_pFormatCtx) < 0)
		{
			handle_error(2);
		}
		
		//loop which runs until the first videostream inside the file is found.
		for (unsigned int i = 0; i < m_pFormatCtx->nb_streams; i++)
		{
			if(m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				m_pVideostream = i;
				break;
			}
		}
		//if no video stream is found a error handling is used
		if (m_pVideostream == -1)
			handle_error(3);

		//sets the CodecContext of the specified videostream
		m_pCodecCtx = m_pFormatCtx->streams[m_pVideostream]->codec;
		//the next check looks up the ffmpeg database and sees if any codec for the selected videostream is available
		m_pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
		if (m_pCodec == NULL)
		{
			handle_error(4);
		}
		//checks if the found codec can be opened with the declared codecContext
		if (avcodec_open(m_pCodecCtx, m_pCodec) < 0)
		{
			handle_error(5);
		}

		//some ffmpeg stuff to allocate memory for the frames
		m_pFrame = avcodec_alloc_frame();
		m_pFrameRGB = avcodec_alloc_frame();

		//checks if the frames could be allocated
		if (m_pFrameRGB == NULL){
			handle_error(6);
		}
		int numBytes;

		//sets the amount of bytes which is needed for the RGB24 format with the specified height and weight
		numBytes = avpicture_get_size(PIX_FMT_RGB24, m_pCodecCtx->width, m_pCodecCtx->height);

		//allocates the buffer
		m_pBuffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

		//initializes the pFrameRGB with the specified buffer size, ColorFormat, Width and height
		avpicture_fill( (AVPicture *) m_pFrameRGB, m_pBuffer, PIX_FMT_RGB24, m_pCodecCtx->width, m_pCodecCtx->height );

		m_pResultFrame = 0;
		run();	
		//runs until the finished frame has actual some valid data
		while (getLatestFrame() == 0)
			run();	
	}

	void AvVideoDecoder::handle_error(int i)
	{
		switch (i)
		{
			case 1: 
				//MessageBox(NULL,"Cannot open File.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Cannot open File." << std::endl;
				break;
			case 2: 
				//MessageBox(NULL,"Couldn't find Stream Info.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Couldn't find Stream Info." << std::endl;
				break;
			case 3: 
				//MessageBox(NULL,"Couldn't find VideoStream.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Couldn't find VideoStream." << std::endl;
				break;
			case 4: 
				//MessageBox(NULL,"Codec not Supported.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Codec not Supported." << std::endl;
				break;
			case 5: 
				//MessageBox(NULL,"Codec not Opened.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Codec not Opened." << std::endl;
				break;
			case 6: 
				//MessageBox(NULL,"Frame not allocated.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Frame not allocated." << std::endl;
				break;
			case 7: 
				//MessageBox(NULL,"Frame not converted.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Frame not converted." << std::endl;
				break;
			case 8: 
				//MessageBox(NULL,"SWS_Scale failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "SWS_Scale failed." << std::endl;
				break;
			case 9: 			
				//MessageBox(NULL,"Cann't read frame.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Cann't read frame." << std::endl;
				break;
			case 10: 
				//MessageBox(NULL,"Cann't loop.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION); 
				std::cout << "Cann't loop." << std::endl;
				break;
		}	
	}

	void AvVideoDecoder::SaveFrame(AVFrame *pFrame, int width, int height, int iFrame)
	{
		FILE *pFile;
		char szFilename[32];
		int  y;

		// Open file
		sprintf(szFilename, "frame%d.ppm", iFrame);
		pFile=fopen(szFilename, "wb");
		if(pFile==NULL)
			return;

		// Write header
		fprintf(pFile, "P6\n%d %d\n255\n", width, height);

		// Write pixel data
		for(y=0; y<height; y++)
			fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

		// Close file
		fclose(pFile);
	}

	void AvVideoDecoder::run()
	{
		//reads the actual frame depending on the FormatContext and stores the information inside the packet
		if(av_read_frame(m_pFormatCtx, &m_pPacket) >= 0)
		{
			//checks if the packet actually uses the declared video stream
			if (m_pPacket.stream_index == m_pVideostream)
			{
				//the actual decoding is done here. 
				//-using the CodecContext for the decoding, 
				//-storing the data inside pFrame, 
				//-sets the frameFinished variable to mark if the Frame has been completely loaded and decoded.
				//	if not the frame will be marked as not finished and the function has to be called until the frame
				//  is actually finished.
				//-stores the data inside the packet
				avcodec_decode_video2(m_pCodecCtx, m_pFrame, &m_pFrameFinished, &m_pPacket);
				//checks if the frame is completely decoded
				if (m_pFrameFinished){
					static struct SwsContext *img_convert_ctx;

					//if the context hasn't been initialized
					if (img_convert_ctx == NULL){						
						int w = m_pCodecCtx->width;
						int h = m_pCodecCtx->height;

						//context will be set with the ffmpeg function sws_getContext

						//parameter for sws:getContext:
						//width of the source, height of the source,
						//Pixel format (primarily know by the CodecContext, destination width, destination height
						//Pixel format of the destination (RGB24 is similar to GL_RGB), some flags for the converting,
						//source Filter, destination Filter, parameter for the filter

						img_convert_ctx = sws_getContext(w, h,
														m_pCodecCtx->pix_fmt, w, h, 
														PIX_FMT_RGB24, SWS_BICUBIC,
														NULL, NULL, NULL);

						//if the image conversion failed the error handling can do something
						if (img_convert_ctx == NULL)
						{
							handle_error(7);
						}						
					}
					//depending on the context the scale function actually converts the frame
					//parameter: SWSContext holding the conversion information, data of the source, linesize of the source,
					//slizeY, slizeH (height), destination data, destination linesize
					int ret = sws_scale(img_convert_ctx, m_pFrame->data, m_pFrame->linesize, 
										0, m_pCodecCtx->height, m_pFrameRGB->data, m_pFrameRGB->linesize);

					/*
					*the result is stored to another pointer to have the possibility to check the ret value and see 
					*if errors occured without overwriting the last frames data in case something failed
					*BEWARE: this structure needs to be modified if used in multiple threads
					*/
					m_pResultFrame = m_pFrameRGB;
				}
				else
				{
					//simply runs this function until a full frame has been finished the decoding
					run();
				}
			}
			//frees the allocated packet
			av_free_packet(&m_pPacket);
		}
		else
		{
			//this block simply seeks to position 0 (which is defined as the start of the video)
			//in case the time of the video has reached the end (video has been fully playbacked)
			int64_t pos = 0;
			int64_t seek_target = 0;
		
			AVRational myAVTIMEBASEQ = {1, AV_TIME_BASE};

			seek_target = av_rescale_q(seek_target, (AVRational) myAVTIMEBASEQ, m_pFormatCtx->streams[m_pVideostream]->time_base);

			if (av_seek_frame(m_pFormatCtx, m_pVideostream, seek_target, AVSEEK_FLAG_ANY))
			{
				handle_error(10);
			}
		}
	
	}

	AVFrame* AvVideoDecoder::getLatestFrame()
	{
		return m_pResultFrame;
	}

	int AvVideoDecoder::getHeight()
	{
		return m_pCodecCtx->height;
	}

	int AvVideoDecoder::getWidth()
	{
		return m_pCodecCtx->width;
	}
};