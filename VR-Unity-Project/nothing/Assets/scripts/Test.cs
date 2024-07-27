using UnityEngine;
using UnityEngine.Rendering;
using System.Runtime.InteropServices;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using System.Net;
using System.Net.Sockets;

public class Test : MonoBehaviour
{
    Texture2D _texture;
    CommandBuffer _command;
    bool start = false;
    bool startReceiving = true;
    public string host = "hdr3.local";
    public int port = 8000;

#if PLATFORM_IOS
    [System.Runtime.InteropServices.DllImport("__Internal")]
#else
    [System.Runtime.InteropServices.DllImport("NativePlugin")]
#endif
    static extern System.IntPtr GetTextureUpdateCallback();
    [DllImport("NativePlugin")]
    private static extern int CloseVideoConnectionExport();
    [DllImport("NativePlugin")]
    private static extern int StartVideoConnectionExport();

    void Start()
    {
        Application.targetFrameRate = 90;
        _command = new CommandBuffer();
        _texture = new Texture2D(1280, 720, TextureFormat.RGBA32, false);
        _texture.wrapMode = TextureWrapMode.Clamp;

        // Set the texture to the renderer with using a property block.
        var prop = new MaterialPropertyBlock();
        prop.SetTexture("_MainTex", _texture);
        GetComponent<Renderer>().SetPropertyBlock(prop);
        
    }

    void OnDestroy()
    {
        CloseVideoConnectionExport();
        _command.Dispose();
        Destroy(_texture);
    }


    void CheckPort(string host, int port)
    {
        using (TcpClient client = new TcpClient())
        {
            try
            {
                client.ReceiveTimeout = 1000;
                client.SendTimeout = 1000;
                var result = client.BeginConnect(host, port, null, null);
                bool success = result.AsyncWaitHandle.WaitOne(1000, true);
                
                if (success && client.Connected)
                {
                    Debug.Log($"Port {port} on {host} is open.");
                }
                else
                {
                    Debug.Log($"Port {port} on {host} is closed.");
                }
                client.EndConnect(result);
            }
            catch
            {
                Debug.Log($"Port {port} on {host} is closed.");
            }
        }
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.P)){
            Debug.Log("Checking Port");
            CheckPort(host, port);
        }
        if (Input.GetKeyDown(KeyCode.C)){
            Debug.Log("close");
            start = false;
            CloseVideoConnectionExport();
        }
        if (Input.GetKeyDown(KeyCode.S)){
            Debug.Log("start");
            start = true;
        }
        if(start){
            //StartVideoConnectionExport();
            if (Input.GetKeyDown(KeyCode.A)) {
                Debug.Log("Activate");
                startReceiving = true;
            }
            if (Input.GetKeyDown(KeyCode.D)) {
                Debug.Log("Deactivate");
                startReceiving = false;
            }
            if(startReceiving){
                // Request texture update via the command buffer.
                _command.IssuePluginCustomTextureUpdateV2(
                    GetTextureUpdateCallback(), _texture, (uint)(Time.time * 90)
                );
                Graphics.ExecuteCommandBuffer(_command);
                _command.Clear();
            }
        }
    }
}