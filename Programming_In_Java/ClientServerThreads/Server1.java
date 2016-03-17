/**
 * @class Server1
 * @author Tewelle
 * @version version 1.0
 * @copy-right - use it as long as you give credit to the author
 * @date 21-06-2012
 */
//package server1;

import java.io.DataInputStream;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Server1
{
    /***
     * @param args an array to store arguments passed to this class at run time.
     */
    public static void main(String args[])
    {
        // Declare a server socket and a client socket for the server.
        // Declare an input and an output stream.
        if(args.length != 1)
        {
        System.err.println("Invalid command, only one argument is required");
        System.out.println("Usage: java -jar Server.jar textfil1_lasse_solen_i_ogonen.txt");
        System.exit(1);
        }

        ServerSocket serverSocket = null;
        int port = 2222;
        DataInputStream is = null;
        PrintStream os = null;
        Socket clientSocket = null;

        //Open a server socket on port @port.
        try
        {
            serverSocket = new ServerSocket(port);
        }
        catch (Exception e)
        {
            System.out.println("Server unable to create socket on port " +port);
        }

        //Create a socket object from the Server Socket to listen and accept
        // connections.
        System.out.println("Server started successfully");
        while (true)
        {
            try
            {
                clientSocket = serverSocket.accept();
                is = new DataInputStream(clientSocket.getInputStream());
                os = new PrintStream(clientSocket.getOutputStream());

                //Assuing connection is established,let the server read a file
                // into an array list.
                Scanner s = new Scanner(new File(args[0]));
                ArrayList<String> list = new ArrayList<String>();
                while (s.hasNext())
                {
                    list.add(s.next());
                }

                //close scanner. File contents are already stored in the array list.
                s.close();
               //declare a flag to track if the file is sent fully to the client.
                Boolean fileSent = false;
                for (int i = 0; i < list.size() && !fileSent; i++)
                {
                    //send words to output stream i.e. to client
                    if(list.get(i)!=null && !list.get(i).equals(" "))
                    os.println(list.get(i).toString());
                }

                //finished sending file.
                fileSent = true;
                os.println("EndOfFile!");// notify client
                //The next commented lines are for later use;
                //in case we want to let the server close by client notification.
               /*
                * while(!is.readLine().equalsIgnoreCase("CLOSE-CONNECTION"))
                {}
                close the input and output sreams
                os.close();
                is.close();
                serverSocket.close();
                *
                */
            }
            catch (IOException e)
            {
                System.out.println(e);
            }
        }
    }
}
