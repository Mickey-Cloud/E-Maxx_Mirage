using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem.XR;

public class ToggleTracking : MonoBehaviour
{
    public Camera player;
    private TrackedPoseDriver playerTracker;
    // Start is called before the first frame update
    void Start()
    {
        playerTracker = player.GetComponent<TrackedPoseDriver>();
    }

    // Update is called once per frame
    void Update()
    {
        //Toggle Rotation tracking
        if(Input.GetKeyDown(KeyCode.R)){
            
            if(playerTracker.trackingType == TrackedPoseDriver.TrackingType.RotationAndPosition){
                playerTracker.trackingType = TrackedPoseDriver.TrackingType.PositionOnly;
                Debug.Log($"changed Tracking type to {playerTracker.trackingType}");
            }else if(playerTracker.trackingType == TrackedPoseDriver.TrackingType.PositionOnly){
                playerTracker.trackingType = TrackedPoseDriver.TrackingType.RotationAndPosition;
                Debug.Log($"changed Tracking type to {playerTracker.trackingType}");
            }else if(playerTracker.trackingType == TrackedPoseDriver.TrackingType.RotationOnly){
                Debug.Log($"changed Tracking type to {playerTracker.trackingType}");
                if(playerTracker.enabled == false){
                playerTracker.enabled = true;
                }else{
                playerTracker.enabled = false;
                }
            }
        }
        //Toggle Position tracking
        if(Input.GetKeyDown(KeyCode.P)){
             if(playerTracker.trackingType == TrackedPoseDriver.TrackingType.RotationAndPosition){
                playerTracker.trackingType = TrackedPoseDriver.TrackingType.RotationOnly;
                Debug.Log($"changed Tracking type to {playerTracker.trackingType}");
            }else if(playerTracker.trackingType == TrackedPoseDriver.TrackingType.RotationOnly){
                playerTracker.trackingType = TrackedPoseDriver.TrackingType.RotationAndPosition;
                Debug.Log($"changed Tracking type to {playerTracker.trackingType}");
            }else if(playerTracker.trackingType == TrackedPoseDriver.TrackingType.PositionOnly){
                Debug.Log($"changed Tracking type to {playerTracker.trackingType}");
                if(playerTracker.enabled == false){
                playerTracker.enabled = true;
                }else{
                playerTracker.enabled = false;
                }
            }
        }
        
    }
}
