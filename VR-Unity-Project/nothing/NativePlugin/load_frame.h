extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <libswscale/swscale.h>
#include <inttypes.h>
}

struct VideoReaderState {
	//public things for other parts of the program
	int width, height;
	bool ranOnce = false;
	// private internal state
	AVFormatContext* av_format_ctx;
	AVCodecContext* av_codec_ctx;
	int video_stream_index = -1;
	AVFrame* av_frame;
	AVPacket* av_packet;
	SwsContext* sws_scaler_ctx;
};

bool video_reader_open(VideoReaderState* state, const char* filename);

bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer);

bool video_reader_close(VideoReaderState* state);

bool load_frame(VideoReaderState* state, const char* filename, int* width, int* height, unsigned char** data);