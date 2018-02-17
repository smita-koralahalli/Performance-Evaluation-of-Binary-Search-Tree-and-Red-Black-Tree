#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int match;							//key comparisons//
int sum=0;	

typedef struct node{
int key;
char color;						        //count for repeating values//
struct node *left;
struct node *right;
struct node *parent;
int count;
}node;

struct node* root = NULL;

/*************Left Rotate************/
void leftRotate(struct node *x)
{

	struct node *y;
	y = x->right;  						//Set y
	x->right = y->left; 					// Initialize y's left subtree into x's right subtree

	if( y->left != NULL)
	{
    		y->left->parent = x; 				//Connect the y's left sublink
	}

	y->parent = x->parent; 					//Connect x's old parent and y's parent
	
	if( x->parent == NULL)
	{
    		root = y;
	}
	else if((x->parent->left!=NULL) && ( x->key == x->parent->left->key))
	{
    		x->parent->left = y; 				//Connect x's old parent's left or right child
	}

	else x->parent->right = y;
	y->left = x; 						//put x on y's left
	x->parent = y; 						// x's parent

	return;
}


/*************Right Rotate************/
void rightRotate(struct node *y)
{
	struct node *x;
	x = y->left; 						//set x
	y->left = x->right; 					//Turn x's right subtree into y's left subtree

	if ( x->right != NULL)
	{
    		x->right->parent = y;
	}

	x->parent = y->parent; 					//Connect y's old parent and x's parent
	if( y->parent == NULL)
	{
    		root = x;
	} 

	else if((y->parent->left!=NULL) && ( y->key == y->parent->left->key))	
	{
    		y->parent->left = x; 				//Connect y's old parent's left or right child
	}

	else y->parent->right = x;
	x->right = y; 						//put y on x's right
	y->parent = x; 						//Take care of y's parent

	return;

}

/***********Perform operations to fix the node***************/
//If parent black exit//
//If parent red
//a.Red sibling: Change color//
//b.Black or absent sibling: Rotate and recolor//

void insertFix(struct node *z)
{
	struct node *y=NULL;
	while((z->parent!=NULL) && (z->parent->color == 'r'))
	{
    		if ((z->parent->parent->left!=NULL) && (z->parent->key == z->parent->parent->left->key))
		{
       			if(z->parent->parent->right!=NULL)
        		y = z->parent->parent->right;
      			if((y!=NULL) && (y->color == 'r'))
			{
             			z->parent->color = 'b';
            			y->color = 'b';
           			z->parent->parent->color = 'r';
	    			if(z->parent->parent!=NULL)
            			z = z->parent->parent;
        		}
        
			else 
			{
       				if ((z->parent->right!=NULL) &&(z->key == z->parent->right->key))
				{
            				z = z->parent;
            				leftRotate(z);
        			}
        
				z->parent->color = 'b';
        			z->parent->parent->color = 'r';
        			rightRotate(z->parent->parent);
   		 	}
    		}
    
		else 
		{
         		if(z->parent->parent->left!=NULL)
        		y = z->parent->parent->left;
        		if ((y!=NULL) && (y->color == 'r'))
			{
            			z->parent->color = 'b';
           			y->color = 'b';
            			z->parent->parent->color = 'r';
            			if(z->parent->parent!=NULL)
            			z = z->parent->parent;
        		}
        		
			else
        		{
       				if ((z->parent->left!=NULL) && (z->key == z->parent->left->key))
				{
            				z = z->parent;
            				rightRotate(z);
        			
				}
        			z->parent->color = 'b';
        			z->parent->parent->color = 'r';
        			leftRotate(z->parent->parent);
    			}
		}
	}

        root->color = 'b';
}




/***********Insert operation*********************/
void insert(int val)
{
	struct node *x, *y;
	struct node *z = (struct node*)malloc(sizeof(struct node));
	z->key = val;
	z->left = NULL;
	z->right = NULL;
	z->color = 'r';
	x = root;
	
	

	if ( root == NULL )                                 // root insertion and setting color to black//
	{
		
    		root = z;
		root->count=0;
    		root->color = 'b';
		
    		return;
	}
        
        
        else if (root!=NULL)				    // same element found in root just increment count//
	{
        	if(z->key==root->key){
		root->count++;
		return;}
	}
       
       
	
	
	while ( x != NULL)				    // subsequent node insertion and increment//
	{
                
    		y = x;
 		
                
                if ( z->key < x->key)
		{
       			x = x->left;
    		}
    
		else if (z->key > x->key)
		{
			x = x->right;
		}
		
		else 
		{
			x->count++;
			return;
		}
   
	}

	z->parent = y;
	
	if ( y == NULL)
	{
    		root = z;
		
	}

        else if( z->key < y->key )
	{
    		y->left = z;
	}

	else if (z->key > y->key)
	{
		y->right = z;
	}
	
	else 
	{
		y->count++;
		return;
	}
	

	
	
	insertFix(z);

	

	return;
}



/***********Search operation*********************/

int search(int val)
{
	struct node* temp=root;
	int diff;

	while(temp!=NULL)
	{
	 	diff=val - temp->key;                               //calculate diff with key and value and traverse//
		
		if(diff>0)
		{
			temp=temp->right;
			match++;
		}

		else if (diff<0)
		{
			temp=temp->left;
			match++;
		}

		else
		{
			
			printf("\n\nElement to be searched is %d and its height is %d with count: %d\n",temp->key, match, temp->count+1);
        		sum+=(temp->count+1)*match;
        		printf("\nSum=%d\n",sum);
        		return 1;
		}
		}

		return 0;
}


/*********Height*******************/
int rbt_height(struct node *root)
{
    int tmp1=0;
    int tmp2=0;
    if (root)
    {
        tmp1 = rbt_height(root->left);
        tmp2 = rbt_height(root->right);
        if (tmp1>tmp2)
            return tmp1+1;
	    
        else
            return tmp2+1;
	
	 
    }
}

/*********In-Order Traversal*******************/
void inorderTree(struct node* root){
struct node* temp = root;

if (temp != NULL){
    inorderTree(temp->left);
    printf("%d-%d - %c\t\t ",temp->key, temp->count+1, temp->color);
    inorderTree(temp->right);
}
return;
}


int main ( void )
{
  struct node *tree = NULL;
  int i;
  int odd, even;
  int b=1;
  
//function for different random numbers for each iteration; commented for same sequence for both binary search tree and red black tree// 
  //srand(time(NULL));
  

/******** Odd number generation ***********/
	for(odd=1; odd<=99; odd+=2)
    	{
        	insert(odd); 
        	printf("Element inserted : %d\n",odd);
    	}
 

/******** Even number generation ***********/  
    	for(even=2; even<=100; even+=2)
    	{
      
        	insert(even);   
        	printf("Element inserted : %d\n",even);
    	}


	for ( i = 0; i < 400; i++ )
  	{
  		int x=rand() % 100+1;
 		printf("\nElement inserted:%d\n",x);
  		insert (x);
       
  	}
        printf("\nInorder Traversal : number-count-tag\n");
        inorderTree(root);
  
  	while(b<=100)
  	{
  		match=1;
  		search(b);
  		b++;

  	}

  printf("\n Total sum of key comparisons :%d\n",sum);
  printf("\n\n Average number of key comparisons for a successful search :%d\n\n", sum/500);
  printf("\n\nThe height of tree is :%d\n",rbt_height(root));
 
}
