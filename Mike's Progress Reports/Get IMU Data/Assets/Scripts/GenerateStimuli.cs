using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class GenerateStimuli : MonoBehaviour
{
    public GameObject Small;
    public GameObject Medium;
    public GameObject Large;
    public Camera Player;

    private MeshRenderer mediumMesh;
    private MeshRenderer smallMesh;
    private MeshRenderer largeMesh;
    private bool activated = false;
    private float timeElapsed = 0;
    void Start(){
        smallMesh = Small.GetComponent<MeshRenderer>();
        mediumMesh = Medium.GetComponent<MeshRenderer>();
        largeMesh = Large.GetComponent<MeshRenderer>();
    }
    // Update is called once per frame
    void Update()
    {
        timeElapsed += Time.deltaTime;
        //depending on my position to the red ball and my position to the blue balls change their size
        if(activated){
            ChangeSizes();
        }
        
        if(Input.GetKeyDown(KeyCode.Alpha2)){
            activated = true;
            timeElapsed = 0;
            if(mediumMesh.enabled){
                mediumMesh.enabled = false;
            }else{
                mediumMesh.enabled = true;
            }
        }
        if(mediumMesh.enabled && !smallMesh.enabled){
            if(timeElapsed > 2.0f){
                smallMesh.enabled = true;
                largeMesh.enabled = true;
            }
        }else if(!mediumMesh.enabled && smallMesh.enabled){
            if(timeElapsed > 2.0f){
                smallMesh.enabled = false;
                largeMesh.enabled = false;
            }
        }
    }

    private void ChangeSizes(){
        //get their distances from the player
        var distanceDiffSmall = Player.transform.position - Small.transform.position;
        var distanceDiffMedium = Player.transform.position - Medium.transform.position;
        var distanceDiffLarge = Player.transform.position - Large.transform.position;

        //get the proportion
        var distanceRatioMedium = 1/distanceDiffMedium.magnitude;
        float ratio = Medium.transform.localScale.x * distanceRatioMedium;

        //apply ratio to the spheres
        float largeDistanceRatio = ratio * distanceDiffLarge.magnitude;
        float smallDistanceRatio = ratio * distanceDiffSmall.magnitude;
        Large.transform.localScale = new Vector3(largeDistanceRatio, largeDistanceRatio,largeDistanceRatio);
        Small.transform.localScale = new Vector3(smallDistanceRatio,smallDistanceRatio,smallDistanceRatio);
    }
}
