#pragma once

#define _CRT_SECURE_NO_DEPRECATE 
#define _SCL_SECURE_NO_DEPRECATE

//since the ffmpeg headers are written in c they have to be included as that
extern "C"
{
	#include <avcodec.h>
	#include <avformat.h>
	#include <swscale.h>
}

#include <iostream>
#include <string.h>

namespace DirectLook 
{
	/*
	*	The AvVideoDecoder class serves the purpose of loading videos independant of the codec.
	*	- To keep it simple the only thing the class needs is the file location of the video using the init function.
	*	- running an update to load and decode next video frame the run function needs to be called when the video frame 
	*	should update
	*	- The information of the last loaded frame will be available through the getLatestFrame method.
	*/
	class AvVideoDecoder
	{
		private:
			AVFormatContext *m_pFormatCtx;
			AVCodecContext *m_pCodecCtx;	
			AVCodec *m_pCodec;		
			AVFrame *m_pFrame, *m_pFrameRGB, *m_pResultFrame;
			AVPacket m_pPacket;
				
			uint8_t *m_pBuffer;
			int m_pFrameFinished;
			int m_pVideostream;

		public:
			AvVideoDecoder();
			/*
			*	frees all the allocated storage used by this class
			*/
			~AvVideoDecoder();

			/*
			*	initializes the class and takes as parameter the path to the video file.
			*	this function will be used instead of a constructor to dynamically load
			*	new videos without recreating the entire class
			*/
			void init(std::string path);
			/*
			*	old function from the test project. 
			*	to determine which error has occured the error handlers can be implemented here
			*/
			void handle_error(int i);
			/*
			*	this stores an video frame into a ppm file. can be used as a screenshot for the video.
			*/
			void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);
			/*
			*	like the name indicates its the main function for updating the frame informations.
			*	once started the function runs until a frame is found, loaded and decoded completely.
			*	It doesn't ensure the frame which has been decoded actually stores real data.
			*	@see getLastestFrame to validate the frame data
			*	
			*	this function will also be called by the init function to ensure that a frame as
			*	been initialized per default.
			*/
			void run();
			/*
			*	wrapper function which simply returns the height of the video
			*/
			int getHeight();
			/*
			*	wrapper function which simply returns the width of the video
			*/
			int getWidth();
			/*
			*	returns an AVFrame which holds the rgb information of the video in
			*	AVFrame->data[0]. 
			*	
			*	this data can be used to store them inside an opengl texture.
			*	BEWARE: the imagedata isn't flipped around the Y-Axis. to ensure the data will be displayed corretly
			*	use glScale(1.0f, -1.0f, 1.0f) after texture has been loaded.
			*/
			AVFrame* getLatestFrame();
	};
};
