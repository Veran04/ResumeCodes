import java.util.*;
import java.io.*;

public class Warshall {
	
private int adjMatrix[][];
private int numVertices;


public Warshall(int numVertices) {
 this.numVertices = numVertices;
 adjMatrix = new int[numVertices][numVertices];
}


public void addEdge(int i, int j, int weight) {	
 adjMatrix[i-1][j-1] = weight;
 adjMatrix[j-1][i-1] = weight;
}


public void WarshallAlgorithm(Warshall chart, int srcVertex) throws Exception
{
	//copy the values from the matrix into the 2D array paths
	int paths[][] = new int[numVertices][numVertices];
	int i, j, k;
	for(i=0;i<numVertices;i++)
		for(j=0;j<numVertices;j++)
			paths[i][j] = adjMatrix[i][j];
	//use a triple nested loop to iterate through the matrix making sure to compare all weights, replacing when needed.
	for(k=0;k<numVertices;k++)
		for(i=0;i<numVertices;i++)
			for(j=0;j<numVertices;j++)
			{
				 if (paths[i][k] + paths[k][j] < paths[i][j]) 
                     paths[i][j] = paths[i][k] + paths[k][j]; 
				
			}
	System.out.printf("\n\n");
	
	Output(paths);
	
	
	
	
}
public static void Output(int paths[][]) throws Exception
{
	FileWriter fw=new FileWriter("cop3503-asn3-output-simpson-brian-fw.txt");
	int len=paths.length;
	fw.write(Integer.toString(len));
	fw.write("\n");
	for (int i=0; i<len; i++) 
	 { 
	     for (int j=0; j<len; j++) 
	     { 
	         
	             fw.write(paths[i][j]+"   "); 
	     } 
	     fw.write("\n"); 
	 }
	
	fw.close();
	
}

public static void main(String args[]) {
	try {
		//used an arbitrary value instead of Integer.MAXVALUE due to overflow issues.
int maxval=99999;
 Scanner in=new Scanner(new File("cop3503-asn3-input.txt"));
 int noVertices=in.nextInt();
 int srcVertex=in.nextInt();
 int noEdges=in.nextInt();
 //Instantiate an instance of the class and fill the matrix with 0's and maxvals as necessary.
 Warshall chart = new Warshall(noVertices);
 for (int i=0; i<noVertices; i++) 
 { 
     for (int j=0; j<noVertices; j++) 
     { 
    	 if(i==j)
    		 continue;
             chart.adjMatrix[i][j]=maxval;
     } 
     
     System.out.println(); 
 } 
 //Store the data in the matrix from the input file.
 for(int i=0;i<noEdges;i++) {
     int srcPoint=in.nextInt();
     int dest=in.nextInt();
     int weight=in.nextInt();
     chart.addEdge(srcPoint, dest, weight);
 }
 chart.WarshallAlgorithm(chart, srcVertex);
 
}
	catch(Exception ex) {
        System.out.println("An Error Has Occurred. Have you tried turning it off and on again?");
    }
}
}
