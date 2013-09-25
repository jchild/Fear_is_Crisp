using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using Chat = System.Net;
using System.Net;
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
        public ServerMain()
        {
            userName = new Hashtable(100);
            userNameByConnect = new Hashtable(100);
            IPAddress serverIP = null;//need to find a way to change thig to server address
            server = new System.Net.Sockets.TcpListener(serverIP, 800);

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
                    ServerMain.userName.Remove(ServerMain.userNameByConnect[tcpClient[i]]);
                    ServerMain.userNameByConnect.Remove(tcpClient[i]);
                }
            }
        }
   /*     public static void BroadcastCharMove(Player player)
        {
            Chat.Sockets.TcpClient[] tcpClient = new Chat.Sockets.TcpClient[ServerMain.userName.Count];
            ServerMain.userName.Values.CopyTo(tcpClient, 0);
            
            for (int i = 0; i < tcpClient.Length; i++)
            { 
                try
                {
                  //push packets to each connected user on the server
                }
                catch (Exception e)
                {
                    ServerMain.userName.Remove(ServerMain.userNameByConnect[tcpClient[i]]);
                    ServerMain.userNameByConnect.Remove(tcpClient[i]);
                }
            }
        }*/
    }
}
