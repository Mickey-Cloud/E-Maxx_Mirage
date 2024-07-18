#ifndef NATIVEPLUGIN_H
#define NATIVEPLUGIN_H

#include "Unity/IUnityGraphics.h"
#include "ffmpeg-master-latest-win64-gpl-shared/include/libavcodec/avcodec.h"

#include <stddef.h>

struct IUnityInterfaces;

#define DLL_EXPORT _declspec(dllexport)

extern "C" {
	int DLL_EXPORT SimpleReturnFun();

	int DLL_EXPORT CloseVideoConnectionExport();

	int DLL_EXPORT StartVideoConnectionExport();

	UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback();
}
#endif
