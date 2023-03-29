
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char name[500];
    struct node *left;
    struct node *right;
}node;
node *insert(node *root, node *element);
void preOrder(node *p, FILE *ofp);
void inOrder(node *p, FILE *ofp);
void postOrder(node *p, FILE *ofp);
int totalCharacters(node *p, int sum);
int isBalanced(node *p, FILE *ofp);
int maxDepth(node *p);
int countBefore(node *p, char *searchKey, int total);
node *Delete(node *p, char *searchKey);

int main()
{
    int i, sum, test, total,  total_calculated;
    int no_nodes, no_searched, no_deleted;
    char searchKey[500];

    node *root;
    node *temp=NULL;
    FILE *ifp, *ofp;
//Initial File IO
    ifp = fopen ("in.txt", "r");
    ofp = fopen ("out.txt", "w");
    fscanf(ifp, "%d", &no_nodes);
    fscanf(ifp, "%d", &no_searched);
    fscanf(ifp, "%d", &no_deleted);
//malloc for and create the nodes in the binary tree, as well as inserting the data into them.
    for(i=0;i<no_nodes;i++)
    {
        root = (node*)malloc(sizeof(node));
    root->left=NULL;
    root->right=NULL;
    fscanf(ifp, "%s", root->name);
        temp = insert(temp, root);
    }
//print the newly created tree in pre, in, and post order.
    fprintf(ofp, "Pre Order:");
    preOrder(temp, ofp);
     fprintf(ofp, "\nIn Order:");
    inOrder(temp, ofp);
     fprintf(ofp, "\nPost Order:");
    postOrder(temp, ofp);

//use recursion to find the total number of characters and the height of the subtrees.
    sum = totalCharacters(temp, 0);
    fprintf(ofp, "\nTotal Characters: %d", sum);
    test = isBalanced(temp, ofp);
    if(test==1)
        fprintf(ofp, "The tree is balanced.");

    else
        fprintf(ofp, "The tree is imbalanced.");
    
fprintf(ofp, "\nSearch Phase:");
//for loop to validate that the name is indeed within the tree, if it is then it is searched for.
for(i=0;i<no_searched;i++)
{
    int num = 0;
    node *temproot=temp;
    fscanf(ifp, "%s", searchKey);
        while(temproot != NULL)
         {
            if(strcmp(temproot->name, searchKey) < 0)
                {
                    temproot = temproot->right;
                }
            else if(strcmp(temproot->name, searchKey) > 0)
                {
                    temproot = temproot->left;
                }
            else if(strcmp(temproot->name, searchKey) == 0)
                {
                    num = 1;
                    break;
                }
        }
    if(num==1)
    {
        int total_calculated = countBefore(temp, searchKey, 0);
        fprintf(ofp, "\n%s: Found, Items before: %d", searchKey, total_calculated);
    }  
    else
    {
        fprintf(ofp, "\n%s: Not found, Items Before: 0", searchKey);
    } 
    }
    fprintf(ofp, "\nDelete Phase:");

//for loop to find and delete specific names and fix the tree afterwards
for(i=0;i<no_deleted;i++)
{
    
    fscanf(ifp, "%s", searchKey);
    temp = Delete(temp, searchKey);
    fprintf(ofp, "\n%s: deleted", searchKey);
}
fprintf(ofp, "\nIn Order after deleting:");
inOrder(temp, ofp);
sum = totalCharacters(temp, 0);
fprintf(ofp, "\nTotal Characters: %d", sum);
fclose(ifp);
fclose(ofp);
return 0;   
}

node *insert(node *root, node *element) //recursive function to insert values into nodes in the proper order.
{  
int test;
if (root == NULL){
        return element;
    }
test = strcmp(element->name, root->name);
//set of if statements to determine where values should be placed when making the tree.
if(test <= 0)
{
    if(root->left != NULL){
        root->left = insert(root->left, element);
    }
    else
        root->left = element;
}
else if(test > 0)
{
    if(root->right != NULL){
        root->right = insert(root->right, element);
    }
    else
        root->right = element;
    
}
return root;

}

void preOrder(node *p, FILE *ofp)   //recursive function to print in pre order.
{
if(p!=NULL)
{
    fprintf(ofp, " %s", p->name);
    preOrder(p->left, ofp);
    preOrder(p->right, ofp);
}
}
void inOrder(node *p, FILE *ofp)    //recursive function to print in In Order, same concept is also used in the search and total characters functions.
{
    if(p!=NULL)
    {
        inOrder(p->left, ofp);
        fprintf(ofp, " %s", p->name);
        inOrder(p->right, ofp);
    }
}
void postOrder(node *p, FILE *ofp)  //recursive function to print in Post Order.
{
    if(p!=NULL){
        postOrder(p->left, ofp);
        postOrder(p->right, ofp);
        fprintf(ofp, " %s", p->name);
    }
}
int totalCharacters(node *p, int sum)   //recursive function that uses the In Order principle with added steps to count number of letters.
{
 if(p!=NULL)
    {
         sum= totalCharacters(p->left, sum);
        int len = strlen(p->name);
        sum+=len;
         sum= totalCharacters(p->right, sum);
    }
    else
        return sum;  
}
int isBalanced(node *p, FILE *ofp)  //recursive function to find the depth of each subtree and compare them.
{
int ldepth, rdepth;
int test;
ldepth = maxDepth(p->left)-1;
fprintf(ofp, "\nHeight left = %d, ", ldepth);
rdepth = maxDepth(p->right)-1;
fprintf(ofp, "height right = %d. ", rdepth);
if(ldepth-rdepth>1 || ldepth-rdepth<-1)
  test = 0;  

else
    test = 1;

return test;
}
int maxDepth(node *p)
{
if (p==NULL)  
       return 0; 
   else 
   { 
      
       int lDepth = maxDepth(p->left); 
       int rDepth = maxDepth(p->right); 
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
}
}
int countBefore(node *p, char *searchKey, int total)
{
  	if(p == NULL)
    {
      return total;
    }
  
    if(strcmp(p->name, searchKey) < 0)
    {
      return countBefore(p->left, searchKey, total+1) + countBefore(p->right, searchKey, 0);
    }
  	else if(strcmp(p->name, searchKey) > 0)
    {
      return countBefore(p->left, searchKey, total);
    }
  	else if(strcmp(p->name, searchKey) == 0)
    {
      return countBefore(p->left, searchKey, total) + total;
    }
}

node *Delete( node* root, char *key) 
{ 
    int ret = strcmp(key, root->name);
    if (root == NULL) 
        return root; 

    if (ret < 0) 
    {
        root->left = Delete(root->left, key); 
    }
       
  
    else if (ret > 0)
    {
        root->right = Delete(root->right, key); 
    } 
        
  
    else
    { 
        if (root->left == NULL) 
        { 
            node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            node *temp = root->left; 
            free(root); 
            return temp; 
        } 
       node* temp = root->right;
        while (temp && temp->left != NULL)
        {
            temp = temp->left; 
        } 

        strcpy(root->name,temp->name);
        root->right = Delete(root->right, temp->name);
    } 
    return root; 
} 
