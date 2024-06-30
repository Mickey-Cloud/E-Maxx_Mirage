// using System.Collections;
// using System.Collections.Generic;
// using UnityEngine;

// public class rotatecamera : MonoBehaviour
// {
//     float tim = 0;
//     // Start is called before the first frame update
//     void Start()
//     {
        
//     }

//     // Update is called once per frame
//     void Update()
//     {
//         float xaxis = -80;
//         float yaxis = 0;
//         float y = 0;
//         float zaxis = -80;
//         float z = 0;
//         if (tim<10){
//             tim = tim + Time.deltaTime;
//             transform.eulerAngles = new Vector3(10, 0, 0) * Time.time;
//         }
//         if(tim>10 && tim< 20){
//             y = tim -10;
//             yaxis = (y*160)/10-80;
//             tim = tim + Time.deltaTime;
//             transform.eulerAngles = new Vector3(0, (int)yaxis, 0);
//             Debug.Log(yaxis);
//         }
//         if(tim>20 && tim<30){
//             z = tim -20;
//             zaxis = (z*180)/10-80;
//             tim = tim + Time.deltaTime;
//             transform.eulerAngles = new Vector3(0, 0, (int)zaxis);
//             Debug.Log(zaxis);
//         }
//         if(tim>30){
//             tim = 0;

//         }
        
//     }
// }
