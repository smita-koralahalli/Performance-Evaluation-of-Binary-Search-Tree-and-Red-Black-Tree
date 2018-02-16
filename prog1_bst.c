#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int match;
int a=0;

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
  int count;
}node;


/*********Insertion Function*******************/
struct node *insert ( struct node *tree, int key)
{
  
  if ( tree == NULL ) {
    tree = malloc ( sizeof *tree );
    if ( tree == NULL )
      return tree;
 
    tree->data = key;
    
    
    tree->left = tree->right = NULL;
    tree->count = 1;}
   else if (key == tree->data)
    {
       (tree->count)++;
        return tree;
    }
   else if ( key < tree->data ) {
    tree->left = insert ( tree->left, key );

  } else {
    tree->right = insert ( tree->right, key);
  
  }
  
  return tree;
}



struct node *search(struct node* tree, int key)
{ 
   
    
    if(tree == NULL)
    {
    	printf("No element found\n");
    }
    else if(key==tree->data)
    {
	
        
    	printf("\n\nElement to be searched is %d and its height is %d with count: %d\n",tree->data, match, tree->count);
        a+=tree->count*match;
        printf("\nSum=%d\n",a);
        return tree;
    }
   
    else if(key < tree->data)
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


int bst_height(struct node *tree)
{
    int tmp1=0;
    int tmp2=0;
    if (tree)
    {
        tmp1 = bst_height(tree->left);
        tmp2 = bst_height(tree->right);
        if (tmp1>tmp2)
            return tmp1+1;
	    
        else
            return tmp2+1;
	
	 
    }
}


void inorderTree(struct node *tree){
struct node* temp = tree;
if (temp != NULL){
    inorderTree(temp->left);
    
    printf("%d(%d) --> ",temp->data, temp->count);
    inorderTree(temp->right);
}
return;
}


int main ( void )
{
  struct node *tree = NULL;
  int i, n = 0;
  int b=1;
  
  
  //srand(time(NULL));
  for ( i = 0; i < 500; i++ )
  {
  	int x=rand() % 100+1;
 	printf("\n\nElement inserted:%d\n\n",x);
  	tree = insert ( tree, x);
       
  }
  printf("\nInorder Traversal : number(count)\n");
  inorderTree(tree);
  while(b<=100)
  {
  	match=1;
  	search(tree,b);
  	b++;

  }
  printf("\n Total sum of key comparisons :%d\n",a);
  printf("\n\n Average number of key comparisons for a successful search :%d\n\n", a/500);
  printf("\n\nThe height of tree is :%d\n",bst_height(tree));
 
}
