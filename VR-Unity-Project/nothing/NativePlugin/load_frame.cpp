
#include "DebugCPP.h"
#include "load_frame.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <inttypes.h>
}

bool video_reader_open(VideoReaderState* state, const char* input_url) {
	auto& av_format_ctx = state->av_format_ctx;
	auto& av_codec_ctx = state->av_codec_ctx;
	auto& av_frame = state->av_frame;
	auto& av_packet = state->av_packet;
	auto& video_stream_index = state->video_stream_index;
	auto& width = state->width;
	auto& height = state->height;
	Debug::Log("We Got to the reader", Color::Blue);
	Debug::Log("Ran Once: ", Color::White);
	Debug::Log(state->ranOnce, Color::White);
	Debug::Log("We Got to the start of setup", Color::Blue);

	av_format_ctx = avformat_alloc_context();
	if (!av_format_ctx) {
		Debug::Log("Couldn't create AVFormatContext", Color::Red);
		return false;
	}
	if (avformat_open_input(&av_format_ctx, input_url, NULL, NULL) != 0) {
		Debug::Log("Couldn't open video file", Color::Red);
		return false;
	}
	// Retrieve stream information
	if (avformat_find_stream_info(av_format_ctx, NULL) < 0) {
		fprintf(stderr, "Could not find stream information\n");
		return -1;
	}

	//find video stream within the file
	for (int i = 0; i < av_format_ctx->nb_streams; ++i) {
		Debug::Log("Video Stream Index:");
		Debug::Log(video_stream_index, Color::Green);
		Debug::Log(i);

		auto stream = av_format_ctx->streams[i];
		AVCodecParameters* av_codec_params_i = av_format_ctx->streams[i]->codecpar;
		const AVCodec* av_codec_i = avcodec_find_decoder(av_codec_params_i->codec_id);

		if (!av_codec_i) {
			continue;
		}
		if (av_codec_params_i->codec_type == AVMEDIA_TYPE_VIDEO) {
			video_stream_index = i;
			width = av_codec_params_i->width;
			height = av_codec_params_i->height;
		}
	}

	if (video_stream_index == -1) {
		Debug::Log("Couldn't find valid video stream inside file", Color::Red);
		return false;
	}
	Debug::Log(video_stream_index, Color::Green);

	AVCodecParameters* av_codec_params = av_format_ctx->streams[video_stream_index]->codecpar;
	const AVCodec* av_codec = avcodec_find_decoder(av_codec_params->codec_id);
	Debug::Log(av_codec->type, Color::Black);
	if (!av_codec) {
		Debug::Log("No AVCodec", Color::Red);
		return false;
	}
	if (!av_codec_params) {
		Debug::Log("No AVCodecParams", Color::Red);
		return false;
	}

	//setup a codec context for the decoder
	av_codec_ctx = avcodec_alloc_context3(av_codec);
	if (!av_codec_ctx) {
		Debug::Log("Couldn't create AVCodecContext", Color::Red);
		return false;
	}
	if (avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0) {
		Debug::Log("Couldn't initialize AVCodecContext", Color::Red);
		return false;
	}
	if (avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
		Debug::Log("Couldn't open Codec", Color::Red);
		return false;
	}

	av_frame = av_frame_alloc();
	if (!av_frame) {
		Debug::Log("Couldn't allocate AVFrame", Color::Red);
		return false;
	}
	av_packet = av_packet_alloc();
	if (!av_packet) {
		Debug::Log("Couldn't allocate AVPacket", Color::Red);
		return false;
	}

	state->ranOnce = true;
	Debug::Log("Ran Once: ", Color::White);
	Debug::Log(state->ranOnce, Color::White);
	Debug::Log("Setup Finished", Color::Green);


}

bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer) {
	auto& av_format_ctx = state->av_format_ctx;
	auto& av_codec_ctx = state->av_codec_ctx;
	auto& av_frame = state->av_frame;
	auto& av_packet = state->av_packet;
	auto& sws_scaler_ctx = state->sws_scaler_ctx;
	auto& video_stream_index = state->video_stream_index;
	auto& width = state->width;
	auto& height = state->height;

	while (av_read_frame(av_format_ctx, av_packet) >= 0) {
		if (av_packet->stream_index != video_stream_index) {
			continue;
		}
		//sent a packet to get decoded by the codec
		int response = avcodec_send_packet(av_codec_ctx, av_packet);
		if (response < 0) {
			Debug::Log("Failed to decode packet: some error but I cannot print it out but the error number is", Color::Red);
			Debug::Log(response, Color::Red);
			return false;
		}
		//recieve the frame back from the codec
		response = avcodec_receive_frame(av_codec_ctx, av_frame);
		if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
			continue;
		}
		else if (response < 0) {
			Debug::Log("Failed to decode packet: Some error but I cannot print it but here is the error number", Color::Red);
			Debug::Log(response, Color::Red);
			return false;
		}

		av_packet_unref(av_packet);
		break;
	}

	if (!sws_scaler_ctx) {
		sws_scaler_ctx = sws_getContext(width, height,
			av_codec_ctx->pix_fmt,
			width, height,
			AV_PIX_FMT_RGBA,
			0, 0, 0, 0);
		if (!sws_scaler_ctx) {
			Debug::Log("Couldn't initialize sw Scaler");
			return false;
		}
	}

	int dest_linesize[1] = { width * 4 };
	uint8_t* dest[1] = { frame_buffer };

	sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, dest, dest_linesize);

	return true;
}

//close the whole file
bool video_reader_close(VideoReaderState* state) {
	auto& av_format_ctx = state->av_format_ctx;
	auto& av_codec_ctx = state->av_codec_ctx;
	auto& av_frame = state->av_frame;
	auto& av_packet = state->av_packet;
	auto& sws_scaler_ctx = state->sws_scaler_ctx;
	state->ranOnce = false;
	sws_freeContext(sws_scaler_ctx);
	avformat_close_input(&av_format_ctx);
	avformat_free_context(av_format_ctx);
	av_frame_free(&av_frame);
	av_packet_free(&av_packet);
	avcodec_free_context(&av_codec_ctx);
	return true;
}
