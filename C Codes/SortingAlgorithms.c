/* COP 3502C Final term Assignment 1
This program is written by: Brian Simpson */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct point        //creating the structure
{
    int x, y;
}point;

point *ReadData(int no_coords, FILE*ifp);                       //functions
int FilterData(int no_coords, point *arr, int testval);
void mergeSort(point *arr, int l, int r);
void merge(point *arr, int l, int m, int r );
void SearchPhase(point *arr, int n);
int BinarySearch(point *arr, int l, int r, int x, int y);

int main()
{
    FILE *ifp, *out;                              //opening the file and making sure it opened properly
    ifp = fopen ("in.txt", "r");
    if(ifp == NULL)
    {
        printf("Error opening file.");
        exit(1);
    }

    int center_x, center_y, radius, no_coords;          //Scanning the first line of the file and calculating the test value to determine what is inside or outside of the circle
    fscanf(ifp, "%d", &center_x);
    fscanf(ifp, "%d", &center_y);
    fscanf(ifp, "%d", &radius);
    fscanf(ifp, "%d", &no_coords);
    int testval = pow(radius, 2);

    point *arr = ReadData(no_coords, ifp);                      //calls the Read data function to return an array of structures containing the points from the input file                     
    
    int x = FilterData(no_coords, arr, testval);                //calls the Filter data function to return an array of structures containing only the points that lie on or inside the circle
    
    no_coords = x;
    mergeSort(arr, 0, no_coords-1);                             //calls the mergeSort function to sort the filtered list by X-axis, and then by Y-axis if two X are the same    
    fclose(ifp);
    int i;
    out = fopen ("out.txt", "w");                               //closes the input file and opens the output file to be written to
    for(i=0;i<no_coords;i++)
    {
        fprintf(out, "%d %d\n", arr[i].x, arr[i].y);            //writing the filtered and sorted list to the output file
    }
    printf("filtered and sorted data written to out.txt\n");
    fclose(out);
    SearchPhase(arr, no_coords);
}



point *ReadData(int no_coords, FILE*ifp)            //takes down the points from the input file into an array of structures and returns it
{
point *arr;
arr = (point*)malloc(sizeof(point)*no_coords);
int i;
for(i=0;i<no_coords;i++)
{
    fscanf(ifp, "%d", &arr[i].x);
    fscanf(ifp, "%d", &arr[i].y);
}
return arr;
}
int FilterData(int no_coords, point *arr, int testval)          //filers the list from the array of structures to only keep points on or within the circle.
{
int i;
for(i=0;i<no_coords;i++)
{
    int check1 = pow(arr[i].x, 2);
    int check2 = pow(arr[i].y, 2);
    int comparison = check1+check2;
    if((comparison)>testval)
    {
        int pos=i;
        for(pos;pos<no_coords;pos++)
        {
            arr[pos] = arr[pos+1];
        }
        no_coords--;
        i--;  
    }
}
return no_coords;                                           //returns the adjusted number of coordinates to be used later for mergesort and binary search.
}
void mergeSort(point *arr, int l, int r)
{
if (l < r)
    {
        //find the middle
        int m = (l+r)/2;
        //sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void merge(point *arr, int l, int m, int r )
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    point *L, *R;
    L = (point*)malloc(sizeof(point)*n1);           //Dynamically Allocate memory to store the two halves of the array
    R = (point*)malloc(sizeof(point)*n2);           

    for (i = 0; i < n1; i++)                        //Use for loops with the values passed into the function to separate the two new halves of the array
    {
        L[i].x = arr[l + i].x;
        L[i].y = arr[l + i].y;
    }
    for (j = 0; j < n2; j++)
    {
        R[j].x = arr[m + 1+ j].x;
        R[j].y = arr[m + 1+ j].y;
    }
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)                //while loop to place the sorted halves back into the original array in the correct order
    {
        if (L[i].x < R[j].x)                /*the following set of if else if statements are explained further down in the binary search function
                                            they follow the same principle of comparing x values against each other from two halves */
        {
            arr[k] = L[i];
            i++;
        }
        else if (L[i].x == R[j].x)
        {
            int testval1 = L[i].y;
            int testval2 = R[j].y;
            if(testval1<testval2)
            {
                arr[k] = L[i];
                i++;
            }
            else if(testval1>=testval2)
            {
                arr[k] = R[j];
                j++;
            }
        }
        else if(L[i].x>R[j].x){
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    //Copy the remaining elements of the left half, if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    //Copy the remaining elements of the right half, if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
      free(L);
      free(R);
      return;
}


void SearchPhase(point *arr, int n)
{
int x, y, result;
while(1)
{
    printf("Search input (x y):");
    scanf(" %d %d", &x, &y);
    if(x!=-999 && y!=-999)                                  //if statement to stop prompting the user if x or y is -999
    {
    result = BinarySearch(arr, 0, n-1, x, y );
    if(result == -1)                                        //if binarysearch returns -1 it means the entered coordinate was not found
    {
        printf("Not found\n");
    }
    else{
    printf("Found at record %d\n", result+1);               //add 1 to the displayed index to account for the 0th index of an array
    }
    }
    else
    {
        free(arr);
        exit(1);
    }
}

}
int BinarySearch(point *arr, int l, int r, int x, int y)
{
if (r >= l) { 
        int mid = l + (r - l) / 2; 
        // If the element is directly in the middle of the array no work is needed 
        if (arr[mid].x == x && arr[mid].y ==y) 
            return mid; 
  
        
        
        if (arr[mid].x > x)                                 //if the x value of the middle is greater than the user's x, we know the theoretical point would be in the left half
        {
            return BinarySearch(arr, l, mid - 1, x, y); 
        }
        else if(arr[mid].x < x)                             //vice versa, if the middle's x value is less than we know the point would be in the right half
        {
            return BinarySearch(arr, mid + 1, r, x, y); 
        }
        else if(arr[mid].x == x && arr[mid].y < y)         //if the middle and entered point share an x, we then perform the above two comments again based on y
        {
            return BinarySearch(arr, mid + 1, r, x, y); 
        }
        else if(arr[mid].x == x && arr[mid].y > y)         
        {
            return BinarySearch(arr, l, mid - 1, x, y);
        }  
    } 
    return -1; //if the element entered does not exist we return -1
}