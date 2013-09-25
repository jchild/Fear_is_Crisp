using System;

public class Chatserver
{
	 public Chatserver()
        {
	        //create our nickname and nickname by connection variables
	        nickName = new Hashtable(100);
	        nickNameByConnect = new Hashtable(100);
	        //create our TCPListener object
	        chatServer = new System.Net.Sockets.TcpListener(4296);
	        //check to see if the server is running
	        //while (true) do the commands
	        while (true)
	        {
		        //start the chat server
		        chatServer.Start();
		        //check if there are any pending connection requests
		        if (chatServer.Pending())
		        {
			         //if there are pending requests create a new connection
			        Chat.Sockets.TcpClient chatConnection = chatServer.AcceptTcpClient();
			        //display a message letting the user know they're connected
			        Console.WriteLine("You are now connected");
			        //create a new DoCommunicate Object
			        DoCommunicate comm = new DoCommunicate(chatConnection);
		        }
	        }
        }
}
