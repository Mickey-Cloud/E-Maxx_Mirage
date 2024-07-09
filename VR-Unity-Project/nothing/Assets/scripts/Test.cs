using UnityEngine;
using UnityEngine.Rendering;
using System.Runtime.InteropServices;

public class Test : MonoBehaviour
{
    Texture2D _texture;
    CommandBuffer _command;

#if PLATFORM_IOS
    [System.Runtime.InteropServices.DllImport("__Internal")]
#else
    [System.Runtime.InteropServices.DllImport("NativePlugin")]
#endif
    static extern System.IntPtr GetTextureUpdateCallback();
    [DllImport("NativePlugin")]
    private static extern int CloseVideoConnectionExport();

    void Start()
    {
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

    void Update()
    {
        // Request texture update via the command buffer.
        _command.IssuePluginCustomTextureUpdateV2(
            GetTextureUpdateCallback(), _texture, (uint)(Time.time * 60)
        );
        Graphics.ExecuteCommandBuffer(_command);
        _command.Clear();

        // Debug.Log("Rotate");
        // // Rotation
        // transform.eulerAngles = new Vector3(10, 20, 30) * Time.time;
    }
}