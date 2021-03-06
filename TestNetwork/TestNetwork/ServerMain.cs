﻿using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using Chat = System.Net;
using System.Net;
using System.Net.Sockets;
using Play;

namespace TestNetwork
{
    class ServerMain
    {
        System.Net.Sockets.TcpListener server;
        public static Hashtable userName;
        public static Hashtable userNameByConnect;

        public static void Main()
        {
            ServerMain server = new ServerMain();
        }

        //gets local IP address of host
        public IPAddress LocalIPAddress()
        {
            IPHostEntry host;
            host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip;
                }
            }
            return null;
        }

        public ServerMain()
        {
            userName = new Hashtable(100);
            userNameByConnect = new Hashtable(100);
            IPAddress serverIP = LocalIPAddress();
            server = new System.Net.Sockets.TcpListener(serverIP, 800);
            Console.WriteLine("Server Start....");
            Console.WriteLine("Server IP: " + serverIP.ToString());
            while (true)
            {
                server.Start();
                if (server.Pending())
                {
                    Chat.Sockets.TcpClient connection = server.AcceptTcpClient();
                    Console.WriteLine("You have connected");
                    Player play = new Player(connection);
                }

            }
            
        }

        //this broadcasts messages to all in server from a specific user
        public static void BroadcastChatMsg(string usrNm, string mesg)
        {
            StreamWriter writer;
            ArrayList ToRemove = new ArrayList(0);
            Chat.Sockets.TcpClient[] tcpClient = new Chat.Sockets.TcpClient[ServerMain.userName.Count];
            ServerMain.userName.Values.CopyTo(tcpClient, 0);

            for (int i = 0; i < tcpClient.Length; i++)
            {
                try
                {
                    if (mesg.Trim() == "" || tcpClient[i] == null)
                    {
                        writer = new StreamWriter(tcpClient[i].GetStream());
                        writer.WriteLine(usrNm + " : " + mesg);
                        writer.Flush();
                        writer = null;
                    }
                }
                catch (Exception e)
                {
                    string str = (string)ServerMain.userNameByConnect[tcpClient[i]];
                    ServerMain.SystemMessage("*** " + str + " *** Has Disconnected");
                    ServerMain.userName.Remove(str);
                    ServerMain.userNameByConnect.Remove(tcpClient[i]);
                }
            }

        }
        
        //this is system messages
        public static void SystemMessage(string msg)
        {
            StreamWriter writer;
            ArrayList ToRemove = new ArrayList(0);
            Chat.Sockets.TcpClient[] tcpClient = new Chat.Sockets.TcpClient[ServerMain.userName.Count];
            ServerMain.userName.Values.CopyTo(tcpClient, 0);

            for(int i = 0; i< tcpClient.Length; i ++){
                try{
                    if(msg.Trim() == "" || tcpClient[i] == null)
                        continue;
                    writer = new StreamWriter(tcpClient[i].GetStream());
                    writer.WriteLine(msg);
                    writer.Flush();
                    writer = null;
                }
                //throws exception if user disconnects
                ///user disconnects the removes from list of users
                catch(Exception e){
                    Console.WriteLine("User " + ServerMain.userName[tcpClient[i]] + " has disconnected.");
                    ServerMain.userName.Remove(ServerMain.userNameByConnect[tcpClient[i]]);
                    ServerMain.userNameByConnect.Remove(tcpClient[i]);
                }
            }
        }

        //Gets in the Players location, and broadcasts out to all players     
        public static void BroadcastCharMove(String player)
        {
            StreamWriter send;
            ArrayList ToRemove = new ArrayList(0);
            Chat.Sockets.TcpClient[] tcpClient = new Chat.Sockets.TcpClient[ServerMain.userName.Count];
            ServerMain.userName.Values.CopyTo(tcpClient, 0);

            for (int i = 0; i < tcpClient.Length; i++)
            {
                try
                {
                    if (player.Trim() == "" || tcpClient[i] == null)
                    {
                        send = new StreamWriter(tcpClient[i].GetStream());
                        send.WriteLine(player);
                        send.Flush();
                        send = null;
                    }
                }
                catch (Exception e)
                {
                    string str = (string)ServerMain.userNameByConnect[tcpClient[i]];
                    ServerMain.SystemMessage("*** " + str + " *** Has Disconnected");
                    ServerMain.userName.Remove(str);
                    ServerMain.userNameByConnect.Remove(tcpClient[i]);
                }
            }
        }
    }
}
