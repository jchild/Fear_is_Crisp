using System.IO;
using System.Net;
using System;
using System.Threading;
using Chat = System.Net;
using System.Collections;
using TestNetwork;

namespace Play
{
    class Player
    {
        Chat.Sockets.TcpClient client;
        System.IO.StreamReader reader;
        System.IO.StreamWriter writer;
        string UserName;

        public Player(System.Net.Sockets.TcpClient TcpClient)
        {
            client = TcpClient;
            Thread chatTread = new Thread(new ThreadStart(login));
            chatTread.Start();
        }

        private string getUserName()
        {
            writer.WriteLine("Enter User Name: ");
            writer.Flush();
            return reader.ReadLine();
        }
        private void write()
        {
            try
            {
                string line = "";
                while(true)
                {
                    line = reader.ReadLine();
                    TestNetwork.ServerMain.BroadcastChatMsg(UserName, line);

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
        private void login()
        {
            reader = new System.IO.StreamReader(client.GetStream());
            writer = new System.IO.StreamWriter(client.GetStream());

            UserName = getUserName();

            while (TestNetwork.ServerMain.userName.Contains(UserName))
            {
                writer.WriteLine("taken, Try again: ");
                UserName = getUserName();
            }

            TestNetwork.ServerMain.userName.Add(UserName, client);
            TestNetwork.ServerMain.userNameByConnect.Add(client, UserName);
            TestNetwork.ServerMain.SystemMessage("*** " + UserName + " *** has joined");
            writer.WriteLine("typing...\r\n---");
            writer.Flush();
            Thread chatThread = new Thread(new ThreadStart(write));
            chatThread.Start();
        }

    }
}
