#include "NativePlugin.h"

extern "C" {
	int DLL_EXPORT SimpleReturnFun() {
		return 10;
	}
}