#ifndef NATIVEPLUGIN_H
#define NATIVEPLUGIN_H

#define DLL_EXPORT _declspec(dllexport)

extern "C" {
	int DLL_EXPORT SimpleReturnFun();
}
#endif
