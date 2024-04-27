using UnityEngine;

public class CameraReset : MonoBehaviour
{
    [SerializeField] Transform resetTransform;
    public GameObject player;
    public Camera playerHead;

    [ContextMenu("Reset Position")]
    public void ResetPosition(){
        var rotationAngleY = playerHead.transform.rotation.eulerAngles.y - 
                                resetTransform.rotation.eulerAngles.y;

        player.transform.Rotate(0, -rotationAngleY, 0);

        var distanceDiff = resetTransform.position- playerHead.transform.position;
        player.transform.position += distanceDiff;
    }

    void Update(){
        if(Input.GetKeyDown(KeyCode.Alpha1)){
            ResetPosition();
        }
    }
}

