/**
 * @class ClientThreads
 * @author Tewelle
 * @version version 1.0
 * @copy-right - use it as long as you give credit to the author .
 * @date 21-06-2012
 */

//package clientthread;

import java.io.*;
import java.net.*;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class ClientThreads implements Runnable
{
    //declare variables
    int numberOfThreads;
    String host=null;
    int port;
    private volatile boolean mustStop=false;
    private final Thread client;
    public static Map map = new HashMap(); // to store words along with their frequency
    Socket clientSocket = null; // a socket to connect to a server
    DataInputStream is = null; // a data stream reader coming through the socket
    PrintStream os = null; // stream writer to write data into the socket
    DataInputStream inputLine =null;

     /**
     * @param host the host address where the server resides/runs.
     * (only one host is assumed in this case)
     * @param port the ports on which the servers are running.
     * A different client thread will be connected to each server
     */
    public ClientThreads(String host, int port) // constructor
    {
        //construct object properties.
        this.host=host;
        this.port=port;
        client = new Thread(this);
    }

    // The runnable section of the threads. It counts the frequency of words.

    @Override
    public void run()
    {
        Map map = new HashMap();
        // Initialization section:
        // Try to open a socket on some port
        // Try to open input and output streams
    try
    {
        clientSocket = new Socket(host, port);
        os = new PrintStream(clientSocket.getOutputStream());
        is = new DataInputStream(clientSocket.getInputStream());
    }
    catch (UnknownHostException e)
    {
        System.err.println("Unknown host");
    }
    catch (IOException e)
    {
        System.err.println("Couldn't get I/O for the connection to host");
    }

    //If everything has been initialized then client can read/write data
    //to the socket we opened a connection to.
    if (clientSocket != null && os != null && is != null)
    {
        try
        {
            // keep on reading from/to the socket till we receive the
            // "EndOfFile!" from the server, once the client received 'EndOfFile!'
            // word will it break and display the results.
            String responseLine;
            while ((responseLine = is.readLine()) != null)
            {
                if (responseLine.indexOf("EndOfFile!")!=-1)
                {
                   // System.out.println(Thread.currentThread().getName()+" Finished counting word-frequency from ");
                   // os.print("COSE-CONNECTION");
                    break;
                }
                //check if the word read already exists in our map and
                //update its frequency
                else if(map.containsKey(responseLine))
                    {
                        Integer frequency =  (Integer)map.get(responseLine);
                        Integer newFrequency = new Integer(frequency.intValue()+1);
                        map.put(responseLine, newFrequency);
                    }
                else /*If it is occuring for the first time, then give it 1*/
                {
                   map.put(responseLine, new Integer(1));
                }
              }
            // close the output/input streasms and the socket
            os.close();
            is.close();
            clientSocket.close();
        }
        catch (UnknownHostException e)
        {
            System.err.println("Trying to connect to unknown host: " + e);
        }
        catch (IOException e)
        {
            System.err.println("IOException:  " + e);
        }
    }
    //let the thread put its word-frequency count into the main map
    constructMap(map);
}
public void start()
{
    client.start();
}
public void stop()
{
     mustStop = true;
}

/**
 * Merge the words-frequency lists from the threads synchronously.
 * @param map2 a map of word-frequency collected by a thread
 */
synchronized void constructMap( Map map2)
{
    Map temp = new HashMap(); // temporary storage
    for(Object key : map2.keySet())
    {
        if(map.containsKey(key))//if the word exists, update its frequency
        {
            temp.put(key, (Integer)map.get(key) + (Integer) map2.get(key));
        }
        else //if the word doesn't exist, add it to the temporay map with its frequency
        {
            temp.put(key, map2.get(key));
        }
    }
    //finally copy the contents of the temporary temp Hashmap to the main Hashmap
    map.putAll(temp);
}
/**
 * @param map Hashmap of word-frequency to be sorted
 * @return a sorted Map<String, Integer>
 */
public static Map<String, Integer> sortByValue(Map<String, Integer> map)
{
    List<Map.Entry<String, Integer>> list = new LinkedList<Map.Entry<String, Integer>>(map.entrySet());

    Collections.sort(list, new Comparator<Map.Entry<String, Integer>>()
    {
        public int compare(Map.Entry<String, Integer> m1, Map.Entry<String, Integer> m2)
        {
            return (m2.getValue()).compareTo(m1.getValue());
        }
    });

    Map<String, Integer> result = new LinkedHashMap<String, Integer>();
    for (Map.Entry<String, Integer> entry : list)
    {
        result.put(entry.getKey(), entry.getValue());
    }
    return result;
}
/**
 * The main entry point(main function) of the class.
 * @param args[] an array to store/receive arguments passed to the file.
 */
public static void main(String[] args)
{
    //check if the required arguments are passed before doing anything.
    if(args.length != 1)
    {
        System.err.println("Invalid arguments");
        System.out.println("Usage: java -jar ClientThreads.jar [N]\n N: Number of frequent words to print");
        System.exit(1);
    }
    int ports[]={1111,2222}; // The list of ports on which the servers are running.
    int topNFrequentWords=Integer.parseInt(args[0]); // user requested number of words to display.
    int numberOfThreads = ports.length; // threads/subprocesses to connect to each server.
    int counter=0;

    /* declare, clreate and start the client threads.
     * We will use two for-loops, the first to create and start each thread, and
     * the second loop to join each thread.
     */
    Thread threads[] = new Thread[numberOfThreads];
    for (int i = 0; i < numberOfThreads; i++) {
        threads[i] = new Thread(new ClientThreads("localhost", ports[i]));
        threads[i].start();
    }
    //Join all the threads (by waiting till each finishes)
    for (int i = 0; i < numberOfThreads; i++)
    {
        try
        {
            threads[i].join();
        }
        catch (InterruptedException e)
        {
            System.out.println("Parent interrupted while waiting for child threads");
        }
    }
    // Having collected all the results from all threads, we sort the list by freqency of words
    map=sortByValue(map);

    //then print the required number of word-frequency list.
    System.out.println("\tTop "+topNFrequentWords+" frequent words:");
    System.out.println("\t------------------");
    System.out.println("\tWord --> Frequency");
    System.out.println("\t------------------");
    for (Object key : map.keySet())
    {
        if(key!=null && !" ".equals(key.toString()))
        {
        System.out.println("\t"+(counter+1)+". "+ key + " --> "+map.get(key)+" times");
        ++counter;
        if (counter==topNFrequentWords)//stop after printing topNFrequentWords
            break;
        }
    }
   }
}
