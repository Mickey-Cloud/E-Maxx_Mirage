using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateHead : MonoBehaviour
{
    private int pos;
    // Start is called before the first frame update
    void Start()
    {
        pos = 0;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.LeftArrow)){
            Debug.Log("left key pressed"); 
            pos = pos + 1;
            transform.eulerAngles = new Vector3(0, pos, 0);

        }
        if (Input.GetKeyDown(KeyCode.RightArrow)){
            Debug.Log("right key pressed");
            pos = pos - 1;
            transform.eulerAngles = new Vector3(0, pos, 0);
        }
        
    }

}
