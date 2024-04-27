using System.Collections;
using System.Collections.Generic;
using Unity.Mathematics;
using UnityEngine;

public class VRMirror : MonoBehaviour
{
    public Camera playerHead;
    public GameObject mirrorHead;
    public GameObject mirror;

    private bool mirroring;
    private Vector3 prevPosition;
    private Quaternion prevRotation;
    private bool prevMirroring;
    // Start is called before the first frame update
    void Start(){
        prevPosition = playerHead.transform.position;
        prevRotation = playerHead.transform.rotation;
    }
     public void mirrorHeadPosition(){
        Debug.Log("Mirroring");
        //rotation
       var rotationAngle = new Vector3(0,90,0);
        mirrorHead.transform.rotation = new Quaternion(-playerHead.transform.rotation.x, -playerHead.transform.rotation.y, -playerHead.transform.rotation.z, playerHead.transform.rotation.w);
        mirrorHead.transform.Rotate(rotationAngle);

        //position
        var playerDistanceFromMirror = playerHead.transform.position - mirror.transform.position;
        var mirrorHeadDistanceFromMirror = new Vector3(mirror.transform.position.x+playerDistanceFromMirror.x,
                     mirror.transform.position.y+playerDistanceFromMirror.y, mirror.transform.position.z-playerDistanceFromMirror.z);
        mirrorHead.transform.position = mirrorHeadDistanceFromMirror;
       
    }

    public void MatchHeadPosition(){
        Debug.Log("matching");
        //rotation
        var rotationAngle = new Vector3(0,-90,0);
        mirrorHead.transform.rotation = new Quaternion(playerHead.transform.rotation.x, playerHead.transform.rotation.y, playerHead.transform.rotation.z, playerHead.transform.rotation.w);
        mirrorHead.transform.Rotate(rotationAngle);


        //lets say the room is 11 units long
        //position
        var playerDistanceFromMirror = new Vector3(0,0,11) - (mirror.transform.position - playerHead.transform.position);
        var mirrorHeadDistanceFromMirror = new Vector3(mirror.transform.position.x+playerDistanceFromMirror.x,
                     mirror.transform.position.y+playerDistanceFromMirror.y, mirror.transform.position.z+playerDistanceFromMirror.z);
        mirrorHead.transform.position = mirrorHeadDistanceFromMirror;
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.M)){
            mirroring = !mirroring;
        }
        if(mirroring){
            mirrorHeadPosition();
            prevMirroring = mirroring;
        }else{
            MatchHeadPosition();
            prevMirroring = mirroring;
        }
        
    }
}
