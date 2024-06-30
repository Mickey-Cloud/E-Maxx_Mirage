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
