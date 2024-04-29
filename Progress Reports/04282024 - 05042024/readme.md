# 4/29/2024
Opened mikes unity project and got it running on my headset. camera view is locked to headset. The environment moves with the headset rather than the headset moving in the enviornment. Went back to my default enviornment i set up. Figured out that it was probably a simulater option that was enabled in mikes unity project. Anyways, I made a completely blank unity project and got the very minimum bare bones vr working. No move z axis. y axis is side to side.

Wrote a simple c# script to transmit vr rotation values to raspberry pi just through the already existing connection through wifi. here is the c# script, I attached it to the camera object in unity:
```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public class transmit : MonoBehaviour
{
    private TcpListener listener;
    private TcpClient client;
    private NetworkStream stream;
    private Thread clientThread;
    private bool isRunning = true;

    void Start()
    {
        listener = new TcpListener(IPAddress.Any, 8080);
        listener.Start();
        Debug.Log("Server started on localhost:8080");
        clientThread = new Thread(new ThreadStart(HandleClient));
        clientThread.Start();
    }

    void HandleClient()
    {
        try
        {
            while (isRunning)
            {
                client = listener.AcceptTcpClient();
                Debug.Log("Client connected");
                stream = client.GetStream();
                while (client.Connected)
                {
                    // Keep this thread alive as long as the client is connected
                    Thread.Sleep(100);
                }
                if (!isRunning) break;
                Debug.Log("Client disconnected. Waiting for new connection...");
            }
        }
        catch (SocketException e)
        {
            Debug.Log("SocketException: " + e.ToString());
        }
        finally
        {
            if (client != null)
            {
                client.Close();
            }
            client = null;
            stream = null;
        }
    }

    void Update()
    {
        if (stream != null && client != null && client.Connected)
        {
            try
            {
                double xAxis = gameObject.transform.localRotation.eulerAngles.x;
                double yAxis = gameObject.transform.localRotation.eulerAngles.y;
                byte[] data = Encoding.ASCII.GetBytes($"{xAxis} {yAxis}\n");
                stream.Write(data, 0, data.Length);
            }
            catch (System.Exception e)
            {
                Debug.Log("Failed to send data: " + e.Message);
            }
        }
    }

    void OnDestroy()
    {
        isRunning = false;
        if (stream != null)
        {
            stream.Close();
        }
        if (client != null)
        {
            client.Close();
        }
        listener.Stop();
        if (clientThread != null)
        {
            clientThread.Interrupt();
            clientThread.Join();
        }
    }
}
```

And here is the clieent code in python for the raspberry pi:
```
#!/usr/bin/python

import socket
import sys

def main():
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect(('10.42.0.46', 8080))
                try:
                        while True:
                                data = s.recv(1024)
                                if data:
                                        print("Received: ", data.decode().strip())
                                else:
                                        break;
                except KeyboardInterrupt:
                        print("\nProgram terminated by user.")
                except Exception as e:
                        print(f"An error occurred: {e}")
                finally:
                        print("Closing connection.")
                        s.close()
if __name__ == "__main__":
        main()
```

The python code was put in the Documents folder, called it receive.py, run it with ```./receive.py```
Right now, the raspberry pi just outputs the two values in degrees into the console
Oh and the ```10.42.0.46``` is the ip address of the computer running the unity program, that has the vr headset connected to it. I've gotta try connecting my vr headset to my laptop and just using a single baseestation for headset tracking. Good progress made today.  