using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class CppBackend : MonoBehaviour
{
    
    [DllImport("NativePlugin")]
    private static extern int SimpleReturnFun();

    private void Start(){
        Debug.Log(SimpleReturnFun());
    }
}
