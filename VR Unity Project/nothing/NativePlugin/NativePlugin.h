#ifndef NATIVEPLUGIN_H
#define NATIVEPLUGIN_H

#include "Unity/IUnityGraphics.h"

#include <stddef.h>

struct IUnityInterfaces;

#define DLL_EXPORT _declspec(dllexport)

extern "C" {
	int DLL_EXPORT SimpleReturnFun();

	UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback();
}
#endif
