#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int match; 						//key comparisons//
int sum=0;

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
  int count;  						//count for repeating values//
}node;


/*********Insertion Function*******************/
struct node *insert ( struct node *tree, int key)
{
  
  if ( tree == NULL ) 
  {
    
	tree = malloc ( sizeof *tree ); 		//Initialize tree//
    	if ( tree == NULL )
        return tree;
 
    	tree->data = key;
    
    
    	tree->left = tree->right = NULL;
    	tree->count = 1;
  }
   
	else if (key == tree->data) 			//Same element increment count//
    
        {
        (tree->count)++;
        return tree;
        }
   
        else if ( key < tree->data )  			//Compare data inserted with key if less insert to left//
	{
        tree->left = insert ( tree->left, key );

        } 
	else 
	{
        tree->right = insert ( tree->right, key); 	//if greater insert to right//
  
  	}
  
        return tree;
  }


/*********Search Function*******************/
struct node *search(struct node* tree, int key)
{ 
   
    
    if(tree == NULL)
    {
    	printf("No element found\n");
    }
    else if(key==tree->data)
    {
	
        
    	printf("\n\nElement to be searched is %d and its height is %d with count: %d\n",tree->data, match, tree->count);
        sum+=tree->count*match;                         // Calculation of total key comparisons
        printf("\nSum=%d\n",sum);
        return tree;
    }
   
    else if(key < tree->data)                           //Increment the comparisons as each element is compared//
    {
	match++;
        return search(tree->left,key);
	
        
    }
    else if(key > tree->data)
    {
	match++;
        return search(tree->right,key);
	
        
    }
  
    return tree;
 

}

/*********Height*******************/
int bst_height(struct node *tree)
{
    int tmp1=0;
    int tmp2=0;
    
    if (tree)
    {
        
	tmp1 = bst_height(tree->left);       		  // Maximum Depth//
        tmp2 = bst_height(tree->right);
        
	if (tmp1>tmp2)
            return tmp1+1;
	    
        else
            return tmp2+1;
	
	 }
}

/*********In-Order Traversal*******************/
void inorderTree(struct node *tree)			  //left, root, right//
{
	struct node* temp = tree;
	if (temp != NULL)
	{
    
		inorderTree(temp->left);
    
    		printf("%d - %d\t\t ",temp->data, temp->count);
    
		inorderTree(temp->right);
	}
	return;
}

int main ( void )
{
  struct node *tree = NULL;

  int i;
  int odd,even;
  int b=1;

//function for different random numbers for each iteration; commented for same sequence for both binary search tree and red black tree//
  //srand(time(NULL));  
    

/******** Odd number generation ***********/
	for(odd=1; odd<=99; odd+=2)
    	{
        	tree=insert(tree,odd); 
        	printf("Element inserted : %d\n",odd);
    	}
 

/******** Even number generation ***********/  
    	for(even=2; even<=100; even+=2)
    	{
      
        tree=insert(tree,even);   
        printf("Element inserted : %d\n",even);
    	}

    

    	for ( i = 0; i < 400; i++ )				// For 400 numbers
    	{
	int x=rand() % 100+1;					//Random Function for generation of 100 numbers
 	printf("Element inserted : %d\n",x);
        tree = insert ( tree, x);

    	}
   

	printf("\nInorder Traversal : number - count\n");
  	inorderTree(tree);

    	while(b<=100)						//Search for all 100 numbers
  	{
  		match=1;
  		search(tree,b);
  		b++;

  	}
  
  printf("\n Total sum of key comparisons :%d\n",sum);
  printf("\n\n Average number of key comparisons for a successful search :%d\n\n", sum/500);
  printf("The height of tree is :%d\n",bst_height(tree));

  
 
 
}
