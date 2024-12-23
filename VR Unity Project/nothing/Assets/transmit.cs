using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System;

public class Transmit : MonoBehaviour
{
    private TcpListener listener;
    private TcpClient client;
    private NetworkStream stream;
    private Thread clientThread;
    private bool isRunning = true;
    // private int thingy = 0;
    public bool usingMurphs;

    void Start()
    {
        listener = new TcpListener(IPAddress.Any, 8080);
        listener.Start();
        Debug.Log("Server started on localhost:8080 " + IPAddress.Any.ToString());
        clientThread = new Thread(new ThreadStart(HandleClient));
        clientThread.Start();
        StartCoroutine(SendDataCoroutine());
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
                    Thread.Sleep(10);
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

    IEnumerator SendDataCoroutine()
    {
        while (isRunning)
        {
            if (stream != null && client != null && client.Connected)
            {
                try
                {
                    double xAxis = Math.Round(gameObject.transform.eulerAngles.x, 3);
                    double yAxis = Math.Round(gameObject.transform.eulerAngles.y, 3);
                    double zAxis = Math.Round(gameObject.transform.eulerAngles.z, 3);
                    /*                    thingy += 1;
                                        string thing = "";
                                        if (thingy > 2)
                                        {
                                            thingy = 0;
                                        }
                                        switch (thingy)
                                        {
                                            case 0:
                                                thing = $"Y{Math.Round(xAxis, 2)}" + '\r';
                                                break;
                                            case 1:
                                                thing = $"P{Math.Round(yAxis, 2)}" + '\r';
                                                break;
                                            case 2:
                                                thing = $"R{Math.Round(zAxis, 2)}" + '\r';
                                                break;
                                        }*/
                    string stringData = usingMurphs ? $"{xAxis} {yAxis}\n" : "R" + (zAxis.ToString().Contains('.') ? zAxis : zAxis.ToString() + ".0") + '\r' + "Y" + (yAxis.ToString().Contains('.') ? yAxis : yAxis.ToString() + ".0")+ '\r' + "P" + (xAxis.ToString().Contains('.') ? xAxis : xAxis.ToString() + ".0") + '\r';
                    byte[] data = Encoding.ASCII.GetBytes(stringData);
                    stream.Write(data, 0, data.Length);
                }
                catch (System.Exception e)
                {
                    Debug.Log("Failed to send data: " + e.Message);
                }
            }
            yield return new WaitForSeconds(0.1f); // Send data every 100ms
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
