// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the TESTNATIVEPLUGIN_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// TESTNATIVEPLUGIN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTNATIVEPLUGIN_EXPORTS
#define TESTNATIVEPLUGIN_API __declspec(dllexport)
#else
#define TESTNATIVEPLUGIN_API __declspec(dllimport)
#endif

// This class is exported from the dll
class TESTNATIVEPLUGIN_API CTestNativePlugin {
public:
	CTestNativePlugin(void);
	// TODO: add your methods here.
};

extern TESTNATIVEPLUGIN_API int nTestNativePlugin;

TESTNATIVEPLUGIN_API int fnTestNativePlugin(void);
