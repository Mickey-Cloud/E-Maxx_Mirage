#include "NativePlugin.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "IUnityRenderingExtensions.h"
#include "DebugCPP.h"
#include "load_frame.h"


VideoReaderState vr_state;
// Old school plasma effect
uint32_t Plasma(int x, int y, int width, int height, unsigned int frame)
{
    float px = (float)x / width;
    float py = (float)y / height;
    float time = frame / 60.0f;

    float l = sinf(px * sinf(time * 1.3f) + sinf(py * 4 + time) * sinf(time));

    uint32_t r = 0xff;
    uint32_t g = 0x00;
    uint32_t b = 0x00;

    return r + (g << 8) + (b << 16) + 0x00000000u;
}

void CloseVideoConnection() {
    if (!video_reader_close(&vr_state)) {
        Debug::Log("Couldn't Close video reader", Color::Red);
    }
}

// Callback for texture update events
void TextureUpdateCallback(int eventID, void* data)
{
    if (eventID == kUnityRenderingExtEventUpdateTextureBeginV2)
    {
        // UpdateTextureBegin: Generate and return texture image data.
        UnityRenderingExtTextureUpdateParamsV2* params = (UnityRenderingExtTextureUpdateParamsV2*)data;
        unsigned int frame = params->userData;

        if (!vr_state.ranOnce) {
            if (!video_reader_open(&vr_state, "tcp://hdr.local:8000")) {
                Debug::Log("Couldn't open video reader", Color::Red);
            }
        Debug::Log("Video width:");
        Debug::Log(vr_state.width);
        Debug::Log("Video Height:");
        Debug::Log(vr_state.height);
        }
        const int frame_width = vr_state.width;
        const int frame_height = vr_state.height;
        uint8_t* frame_data = new uint8_t[frame_width * frame_height * 4];

        if (!video_reader_read_frame(&vr_state, frame_data)) {
            Debug::Log("Couldn't load video frame");
        }

        uint32_t* img = (uint32_t*) malloc(params->width * params->height * 4);
        Debug::Log((double)params->width, Color::Blue);
        Debug::Log((double)params->height, Color::Green);

        img = (uint32_t*)frame_data;

        params->texData = img;
    }
    else if (eventID == kUnityRenderingExtEventUpdateTextureEndV2)
    {
        // UpdateTextureEnd: Free up the temporary memory.
        UnityRenderingExtTextureUpdateParamsV2* params = (UnityRenderingExtTextureUpdateParamsV2*)data;
        free(params->texData);
    }
}

extern "C" {
	int DLL_EXPORT SimpleReturnFun() {
		return 10;
	}

    int DLL_EXPORT CloseVideoConnectionExport() {
        Debug::Log("Closed Video Connection");
        CloseVideoConnection();
        return 10;
    }

    UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback()
    {
        return TextureUpdateCallback;
    }
}