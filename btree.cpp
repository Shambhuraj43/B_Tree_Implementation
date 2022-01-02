/*
    Shambhuraj Wadghule
    CSCI 36200 Assignment 3:B Tree generation using random numbers
    Due Date: 10/15/2021
*/

//#include "Node.h"
//#include"Btree.h"

#include<iostream>
#include<stdlib.h>
#include<queue>
#include<algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//Global variables
int d = 5;
int *array_;
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*
  Node definition using struct
  Entity: key, pointer to child
*/

struct Node{

  int *key;

  Node **child;

};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//function declarations
void printNode(Node *n);
int updateStatus(Node* T,int &k,Node* &newNode);
void insertion(Node* &N,int k,Node* newNode);
void split(Node* oldNode,Node* &newNode,int &k,int address);
void searchNode(int N);
bool check(Node* N);int createBTree(Node *root);
void addNode(Node* oldNode,int k,Node* &newNode,int address);
void createNode(Node* &N);
Node* createRootOfTree(Node* N,Node* newNode,int k);

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/*Main function*/
int main(){

  Node *root=NULL;

      int N;

      N = createBTree(root);

      searchNode(N);

  return 0;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*
  printNode function
  purpose: Print the elements of the B-Tree created
*/
void printNode(Node *n){

  if(n ==NULL){
    //cout<<"";
    return;
  }


  for(int i; i<2*d;i++){

    printNode(n->child[i]);

		if(n->key[i]!=-1)
		    cout<<n->key[i]<<"  |  ";
  }

  printNode(n->child[2*d]);

}
////////////////////////////////////////////////////////////////////////////////
/*
  Check Node function
  purpose: Check if the node exists in the B Tree or not and update the status using flag
*/
bool check(Node* N)
{
	//update status first
	int flag=0;

	for(int i=0;i<2*d+1;i++)
	if(N->child[i]!=NULL)
	flag=1;
	if(flag==0)
	return (1);
	else
	return (0);
}
////////////////////////////////////////////////////////////////////////////////
/*
  addNode Function
  purpose: Add the node to the tree at a specific address
*/
void addNode(Node* oldNode,int k,Node* &newNode,int address)
{

    int i,j;

	for( i=0;i<2*d&&oldNode->key[i]!=-1;i++);
	for( j=i-1;j>=address&&oldNode->key[j]>k;j--)
	{
		oldNode->key[j+1]=oldNode->key[j];
		oldNode->child[j+2]=oldNode->child[j+1];
	}
	oldNode->key[address]=k;
	oldNode->child[address+1]=newNode;
}

////////////////////////////////////////////////////////////////////////////////
/*
  Create Node Function
  purpose: Create a new node to be inserted in the B Tree
*/
void createNode(Node* &N)
{
	int i;

	N=new Node;

	N->key=new int[2*d];

	N->child=new Node*[2*d+1];

	for(i=0;i<2*d;i++)
			N->key[i]=-1;

	for(i=0;i<2*d+1;i++)
			N->child[i]=NULL;
}////////////////////////////////////////////////////////////////////////////////

/*
  Create Root of the Tree function
  purpose: Create the root of the B Tree (Special Function) and update the entities of the root
*/
Node* createRootOfTree(Node* N,Node* newNode,int k)
{

	//initializig the root to Null and  inserting it to the B-TREE
	Node* root=NULL;

				createNode(root);

				//initializing teh NOde properties
		  root->key[0]=k;
			root->child[0]=N;
			root->child[1]=newNode;

		return (root);
}

////////////////////////////////////////////////////////////////////////////////
/*
  Split function
  purpose: As per the rules of B Tree, split the nodes if the number of nodes exceeds the given degree used for
  Self balancing
*/
void split(Node* oldNode,Node* &newNode,int &k,int address)
{
	Node* N=NULL;
	createNode(N);
	if(address<=d)
	{
		for(int i=d;i<2*d;i++)
		{
			N->key[i-d]=oldNode->key[i];
			N->child[i-d+1]=oldNode->child[i+1];
			oldNode->key[i]=-1;
			oldNode->child[i+1]=NULL;
		}
		N->child[0]=oldNode->child[d];
		addNode(oldNode,k,newNode,address);
	}
	else
	{
		for(int i=d+1;i<2*d;i++)
		{
			N->key[i-(d+1)]=oldNode->key[i];
			N->child[i-d]=oldNode->child[i+1];
			oldNode->key[i]=-1;
			oldNode->child[i+1]=NULL;
		}
		N->child[0]=oldNode->child[d+1];
        oldNode->child[d+1]=NULL;
		addNode(N,k,newNode,address-(d+1));
	}
	k=oldNode->key[d];
	oldNode->key[d]=-1;
	newNode=N;
}

////////////////////////////////////////////////////////////////////////////////
/*
  search a node in the tree Function
  purpose: Searches the given node using the key passed to the function
*/
void searchNode(int N)
{
	//USing sort function for balancing purpose
		sort(array_, array_+N);

		cout<<"\n***************************************************\n"<<endl;

		cout<<"\n\n Keys b/w  ["<< N <<"-" << 2*N<<"]\n\n"<<endl;
		cout<<"\n***************************************************\n"<<endl;

		for(int i = 0; i<N; i++)
    {
        if(array_[i]>=N && array_[i]<= 2*N)
        {
            cout<<array_[i]<< " | ";
        }
    }

		cout<<"\n****************************************************\n"<<endl;
}

////////////////////////////////////////////////////////////////////////////////
/*
  Update status Function
  purpose: Updates the status of the nodes inthe B Tree using flag entity of the node
*/
int updateStatus(Node* N,int &k,Node* &newNode)
{
	int temp;
	if(N==NULL)
	{
		return (1);
	}
	for(temp=0;temp<2*d&&N->key[temp]!=-1;temp++)
	{
		if(k<N->key[temp]) break;
	}
	if(check(N))
	{
		if(N->key[2*d-1]==-1)
		{
			addNode(N,k,newNode,temp);
			return (0);
		}
		else
		{
			split(N,newNode,k,temp);
			return (1);
		}
	}
	else
	{
		int flag=updateStatus(N->child[temp],k,newNode);
		if(flag==1)
		{
			if(N->key[2*d-1]==-1)
			{
				addNode(N,k,newNode,temp);
				return (0);
			}
		    else
		    {
			    split(N,newNode,k,temp);
			    return (1);
		    }
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
/*
  Insertion Function
  purpose: Inserts the node in the B Tree if already exists
*/
void insertion(Node* &N,int k,Node* newNode)
{
	Node* root=NULL;

	int flag=updateStatus(N,k,newNode);

	if(flag) N=createRootOfTree(N,newNode,k);
}

////////////////////////////////////////////////////////////////////////////////
/*
  Create B Tree Function
  purpose: Create teh B TREE using random number generation.
           The user enters the N. This function creates the nodes b/w N-3N and inserts them to the B Tree hence creating a B TREE
*/
int createBTree(Node *root)
{

  //take the input from the user to create teh B-TREE using random umber generator
    cout<<"Enter N for the range"<<endl;

    int N;
    cin>>N;
    cout<<"\n***************************************************\n"<<endl;
    cout<<"B-Tree b/w ["<<N<<"-"<<3*N<<"]"<<endl;
    cout<<"\n***************************************************\n"<<endl;

    array_ = new int[N];

	for(int i = 0; i<N; i++){

				int r = rand()%(3*N);
        array_[i] = r;

        //insertioning random number to the tree
        insertion(root,array_[i],NULL);
    }

		printNode(root);
    return N;
}
////////////////////////////////////////////////////////////////////////////////
