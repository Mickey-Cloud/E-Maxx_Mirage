using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFlipper : MonoBehaviour
{
    public GameObject player;
    public Camera playerHead;

    [ContextMenu("Flipper")]
    public void Flipper(){
        var initialHeadPosition = playerHead.transform.position;
        player.transform.Rotate(0, 180, 0);
        var distanceDiff = initialHeadPosition - playerHead.transform.position;
        player.transform.position += distanceDiff;
    }

    void Update(){
        if(Input.GetKeyDown(KeyCode.F)){
            Flipper();
        }
    }
}
