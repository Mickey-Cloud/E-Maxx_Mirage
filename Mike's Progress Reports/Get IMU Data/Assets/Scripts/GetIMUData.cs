using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR;
using UnityEngine.UI;

public class GetIMUData : MonoBehaviour
{
    [SerializeField]
    public Text lValues;
    public Text hValues;

    private XRNode lxRNode = XRNode.LeftHand;
    private XRNode hxRNode = XRNode.Head;
    private List<InputDevice> devices = new List<InputDevice>();
    private InputDevice hdevice;
    private bool hdeviceRotationChosen;
    private Quaternion hdeviceRotationValue = Quaternion.identity;
    private Quaternion prevhdeviceRotationValue;
    private bool hdevicePositionChosen;
    private Vector3 hdevicePositionValue = Vector3.zero;
    private Vector3 prevhdevicePositionValue;
    private InputDevice ldevice;
    private bool ldevicePositionChosen;
    private Vector3 ldevicePositionValue = Vector3.zero;
    private Vector3 prevldevicePositionValue;
    //Access to the hardware device and gets its information saving it in the variable device
    void GetDevice()
    {
        hdevice = InputDevices.GetDeviceAtXRNode(hxRNode);
        InputDevices.GetDevicesAtXRNode(lxRNode, devices);
        ldevice = devices[0];
    }
    // Checks if the device is enable, if not it takes action and calls the GetDevice function
    void OnEnable()
    {
        if (!ldevice.isValid || !hdevice.isValid)
        {
            GetDevice();
        }
    }
    void Update()
    {
        if (!ldevice.isValid || !hdevice.isValid)
        {
            GetDevice();
        }
        
                //Head Position
                // capturing position changes
        InputFeatureUsage<Vector3> hdevicePositionsUsage = CommonUsages.devicePosition;
                // make sure the value is not zero and that it has changed
        if (hdevicePositionValue != prevhdevicePositionValue)
        {
            hdevicePositionChosen = false;
        }
        if (hdevice.TryGetFeatureValue(hdevicePositionsUsage, out hdevicePositionValue) && hdevicePositionValue != Vector3.zero && !hdevicePositionChosen)
        {
            hValues.text = hdevicePositionValue.ToString("F3");
            prevhdevicePositionValue = hdevicePositionValue;
            hdevicePositionChosen = true;
        }
        else if (hdevicePositionValue == Vector3.zero && hdevicePositionChosen)
        {
            hValues.text = hdevicePositionValue.ToString("F3");
            prevhdevicePositionValue = hdevicePositionValue;
            hdevicePositionChosen = false;
        }
                // Head Rotation
                // capturing position changes
        InputFeatureUsage<Quaternion> hdeviceRotationsUsage = CommonUsages.deviceRotation;
                // make sure the value is not zero and that it has changed
        if (hdeviceRotationValue != prevhdeviceRotationValue)
        {
            hdeviceRotationChosen = false;
        }
        if (hdevice.TryGetFeatureValue(hdeviceRotationsUsage, out hdeviceRotationValue) && hdeviceRotationValue != Quaternion.identity && !hdeviceRotationChosen)
        {
            hValues.text = hValues.text + hdeviceRotationValue.ToString("F3");
            prevhdeviceRotationValue = hdeviceRotationValue;
            hdeviceRotationChosen = true;
        }
        else if (hdeviceRotationValue == Quaternion.identity && hdeviceRotationChosen)
        {
            hValues.text = hValues.text + hdeviceRotationValue.ToString("F3");
            prevhdeviceRotationValue = hdeviceRotationValue;
            hdeviceRotationChosen = false;
        }
                //left Controller
                // capturing position changes
        InputFeatureUsage<Vector3> ldevicePositionsUsage = CommonUsages.devicePosition;
                // make sure the value is not zero and that it has changed
        if (ldevicePositionValue != prevldevicePositionValue)
        {
            ldevicePositionChosen = false;
        }
        if (ldevice.TryGetFeatureValue(ldevicePositionsUsage, out ldevicePositionValue) && ldevicePositionValue != Vector3.zero && !ldevicePositionChosen)
        {
            lValues.text = ldevicePositionValue.ToString("F3");
            prevldevicePositionValue = ldevicePositionValue;
            ldevicePositionChosen = true;
        }
        else if (ldevicePositionValue == Vector3.zero && ldevicePositionChosen)
        {
            lValues.text = ldevicePositionValue.ToString("F3");
            prevldevicePositionValue = ldevicePositionValue;
            ldevicePositionChosen = false;
        }
    }
}