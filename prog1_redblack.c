#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int match;
int a=0;

typedef struct rbtNode{
int key;
char color;
struct rbtNode *left;
struct rbtNode *right;
struct rbtNode *parent;
int count;

}rbtNode;


struct rbtNode* root = NULL;

void leftRotate(struct rbtNode *x)
{

	struct rbtNode *y;
	y = x->right;  //Set y
	x->right = y->left; // Turn y's left subtree into x's right subtree

	if( y->left != NULL)
	{
    		y->left->parent = x; //Bridge the y's left sublink
	}

	y->parent = x->parent; //Bridge x's old parent and y's parent
	
	if( x->parent == NULL)
	{
    		root = y;
	}
	else if((x->parent->left!=NULL) && ( x->key == x->parent->left->key))
	{
    		x->parent->left = y; //Bridge x's old parent's left or right child
	}

	else x->parent->right = y;
	y->left = x; //put x on y's left
	x->parent = y; //Take care of x's parent

	return;
}


void rightRotate(struct rbtNode *y)
{
	struct rbtNode *x;
	x = y->left; //set x
	y->left = x->right; //Turn x's right subtree into y's left subtree

	if ( x->right != NULL)
	{
    		x->right->parent = y;
	}

	x->parent = y->parent; //Bridge y's old parent and x's parent
	if( y->parent == NULL)
	{
    		root = x;
	} 

	else if((y->parent->left!=NULL) && ( y->key == y->parent->left->key))	
	{
    		y->parent->left = x; //Bridge y's old parent's left or right child
	}

	else y->parent->right = x;
	x->right = y; //put y on x's right
	y->parent = x; //Take care of y's parent

	return;

}


void rbInsertFix(struct rbtNode *z)
{
	struct rbtNode *y=NULL;
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





void rbInsert(int val)
{
	struct rbtNode *x, *y;
	struct rbtNode *z = (struct rbtNode*)malloc(sizeof(struct rbtNode));
	z->key = val;
	z->left = NULL;
	z->right = NULL;
	z->color = 'r';
	x = root;
	
	

	if ( root == NULL )
	{
		
    		root = z;
		root->count=0;
    		root->color = 'b';
		
    		return;
	}
        
        
        else if (root!=NULL)
	{
        	if(z->key==root->key){
		root->count++;
		return;}
	}
       
       
	
	
	while ( x != NULL)
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
	

	
	
	rbInsertFix(z);

	

	return;
}





int search(int val)
{
	struct rbtNode* temp=root;
	int diff;

	while(temp!=NULL)
	{
	 	diff=val - temp->key;
		
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
        		a+=(temp->count+1)*match;
        		printf("\nSum=%d\n",a);
        		return 1;
		}
		}

		return 0;
}


int bst_height(struct rbtNode *root)
{
    int tmp1=0;
    int tmp2=0;
    if (root)
    {
        tmp1 = bst_height(root->left);
        tmp2 = bst_height(root->right);
        if (tmp1>tmp2)
            return tmp1+1;
	    
        else
            return tmp2+1;
	
	 
    }
}

void inorderTree(struct rbtNode* root){
struct rbtNode* temp = root;

if (temp != NULL){
    inorderTree(temp->left);
    printf("%d(%d) - %c --> ",temp->key, temp->count+1, temp->color);
    inorderTree(temp->right);
}
return;
}


int main ( void )
{
  struct rbtNode *tree = NULL;
  int i, n = 0;
  int b=1;
  
  
  //srand(time(NULL));
  for ( i = 0; i < 500; i++ )
  {
  	int x=rand() % 100+1;
 	printf("\nElement inserted:%d\n",x);
  	rbInsert (x);
       
  }
     printf("\nInorder Traversal : number(count)-tag\n");
     inorderTree(root);
  
  while(b<=100)
  {
  	match=1;
  	search(b);
  	b++;

  }

  printf("\n Total sum of key comparisons :%d\n",a);
  printf("\n\n Average number of key comparisons for a successful search :%d\n\n", a/500);
  printf("\n\nThe height of tree is :%d\n",bst_height(root));
 
}
