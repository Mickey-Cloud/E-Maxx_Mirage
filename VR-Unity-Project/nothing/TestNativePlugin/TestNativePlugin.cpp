// TestNativePlugin.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "TestNativePlugin.h"


// This is an example of an exported variable
TESTNATIVEPLUGIN_API int nTestNativePlugin=0;

// This is an example of an exported function.
TESTNATIVEPLUGIN_API int fnTestNativePlugin(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CTestNativePlugin::CTestNativePlugin()
{
    return;
}
