import java.util.*;
import java.io.*;
public class Graph {
	   public static void main(String args[]) {
	       try {
	    	   //Creating an array list of lists (2D) that contain the Edge objects which contain destination node and weight variables.
	    	   ArrayList<List<Edge>> chart= new ArrayList<List<Edge>>();
	           Scanner in=new Scanner(new File("cop3503-asn3-input.txt"));
	           /*Use the newly defined scanner to store the total number of vertices and edges, as well as what the source
	           vertex for the algorithm to be performed on will be.*/
	           int noVertices=in.nextInt();
	           int srcVertex=in.nextInt();
	           int noEdges=in.nextInt();
	           //loop to fill the created array list of lists with empty edge objects in order to allocate the number needed
	           for(int i=0;i<noVertices;i++) {
	               chart.add(new ArrayList<Edge>());
	           }
	           /*loop to take in a source, destination, and weight between them, and then navigates to the proper index
	           of the array list for that source, adding an edge connecting it to the destination, ensuring to also
	           connect from dest to source afterwards. -1 is used to ensure that the proper index is chosen */
	           for(int i=0;i<noEdges;i++) {
	               int srcPoint=in.nextInt();
	               int dest=in.nextInt();
	               int weight=in.nextInt();
	               //combine get and add into one statement here to avoid having to create unnecessary objects with each get call
	               chart.get(srcPoint-1).add(new Edge(dest-1,weight));
	               chart.get(dest-1).add(new Edge(srcPoint-1,weight));
	           }
	           bellmanFordAlg(chart,srcVertex-1 );
	           in.close();
	       }
	       //display a simple error message if anything goes wrong in the try block
	       catch(Exception ex) {
	           System.out.println("An Error Has Occurred. Have you tried turning it off and on again?");
	       }
	   }
	   /*method to perform the algorithm, taking in parameters of the Array list of lists now populated with proper Edges
	   as well as the source point to run bellman-ford's on. It also includes the throws keyword to handle unforseen exceptions
	   so that try catch need not be implemented in a repetitive manner.*/
	   public static void bellmanFordAlg(ArrayList<List<Edge>> chart,int srcVertex) throws Exception {
		   /* The number of vertices is equal to the size of the created Arraylist. Two integer arrays are created
		    with the size of noVertices. the first one is to  fill with a nonsense value in order to compare individual weights vs 
		    the calculated weights that later replace the nonsense values to see if they need
		    to be updated in the output. The second is  used to keep track of parent (preceding)
		    nodes to make sure the paths can be maintained. */
	       int noVertices=chart.size();
	       
	       int [] paths=new int[noVertices];
	       int [] parent=new int[noVertices];
	       
	       
	       Arrays.fill(paths,Integer.MAX_VALUE);
	       //use a priorityqueue to take advantage of natural ordering. the comparator constructor is to ensure weight is considered.
	       PriorityQueue<Node> que=new PriorityQueue<Node>(new edgeComparator());
	       
	       paths[srcVertex]=0;
	       //for loop to fill the new queue with Node objects containing src vertex i and weight paths[i].
	       for(int i=0;i<noVertices;i++) {
	           que.add(new Node(i,paths[i]));
	           
	       }
	       int count=0;
	       Node node;
	       List<Edge> list = new ArrayList<Edge>();
	       while(count<noVertices) {
	    	   
	    	   //use the poll keyword to pop the node off the front of the que
	           node=que.poll();
	           //the flag that this node has now been visited is switched on
	           
	           /*we only need a list here instead of an ArrayList of lists because it is one individual node within the while loop.
	             create a for loop within the while loop to iterate through the created List in its entirety. Whenever the nodes
	              weight from the source to it is higher than the combined weight of the src vertex's 
	             path to the preceding node + the edge connecting to the new node then the shortest path is updated. The parent 
	             is also updated to reflect the change in the flow of the chart, and a node is added to fix the src vertex and weight.  */
	           list=chart.get(node.srcVertex);
	           for(Edge edge: list) {
	        	   if( paths[edge.dest]>paths[node.srcVertex]+edge.weight) {
	            	   parent[edge.dest]=node.srcVertex+1;
	            	   
	                   paths[edge.dest]=paths[node.srcVertex]+edge.weight;
	   
	                   que.add(new Node(edge.dest,paths[edge.dest]));
	               }
	           }
           count++;
	       }
	       
	       //add a for loop to check for negative cycles
	       
	       for(Edge edge: list) {
	    	   node=que.poll();
        	   if(paths[edge.dest]>paths[node.srcVertex]+edge.weight) {
            	   System.out.println("Graph contains negative weight cycle"); 
                   break; 
               }
           }
	       
       //the path to the source vertex from the source vertex, and the source vertex's parent, are both flagged back to 0.
	       paths[srcVertex]=0;
	       parent[srcVertex]=0;
       Output(paths, parent);
	   }
	   /* This method creates and writes to an output file, taking in parameters of the paths array now filled with
	      proper numbers and not max integer values. The total number of vertices is printed at the top, followed by a
	      sequence of three things within a for loop repeated for the total number of vertices. The first thing that
	      happens is the node number is printed, which starts from 1 and increments by 1. Then, the weight from the
	      src vertex to said node is printed. The last thing printed is what the parent(preceding) node is on the path
	      to said node from the src. */
	   public static void Output(int paths[], int parent[]) throws Exception {
	       FileWriter fw=new FileWriter("cop3503-asn3-output-simpson-brian-bf.txt");
	       int length=paths.length;
	       fw.write(Integer.toString(length));
	       fw.write("\n");
	       for(int i=0;i<length;i++) {
	    	   fw.write(Integer.toString(i+1));
	    	   fw.write(" ");
	    	   fw.write(Integer.toString(paths[i]));
	    	   fw.write(" ");
	    	   fw.write(Integer.toString(parent[i]));
	    	   fw.write("\n");
	       }
	       //close the filewriter
	       fw.close();
	   }
	}
	/* This class ensures that the source vertex and weights stored remain when the constructor is called using the
	   "this" keyword.(they would reset to 0 if this was not here) */
	class Node {
	   int srcVertex,weight;
	   Node(int srcVertex,int weight) {
	       this.srcVertex=srcVertex;
	       this.weight=weight;
	   }
	}
	/* This class ensures that the destination vertex and weights stored remain when the constructor is called using the
	   "this" keyword.(they would reset to 0 if this was not here) */
	class Edge {
	   int dest,weight;
	   Edge(int dest,int weight) {
	       this.dest=dest;
	       this.weight=weight;
	   }
	} 
	/*This class implements the comparator interface, and contains the method compare from it which takes in
	the parameters Node_1 and Node_2 which are each individual instances of a class themselves. The weight of 
	node_2 is then subtracted from node_1 and returned. */
	class edgeComparator implements Comparator<Node> {
		   public int compare(Node node_1,Node node_2) {
		       return node_1.weight-node_2.weight;
		   }  
	}