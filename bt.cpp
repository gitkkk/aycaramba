
#include<iostream>


class Node
{
	public:
	Node(int data=-999):
	_data(data)
	,_left(nullptr)
	,_right(nullptr)
	,_height(1)
	,_size(1)
	{
	}
	int 	_data;
	Node*	_left;
	Node*	_right;
	int		_height;
	int		_size;	
};

void visit(Node* node)
{
	if(node!=nullptr)
	{
		std::cout<< node->_data<<std::endl;
	}
	else
	{
		std::cout<<"visited empty Node"<<std::endl;
	}
}

void morrisInorder(Node* root)
{
	Node* current = root ;
	Node* predecessor;
	while(current != nullptr)
	{
		if(current->_left == nullptr)
		{
			visit(current);
			current = current->_right;
		}
		else
		{
			predecessor = current->_left;

			while( predecessor->_right != current && predecessor->_right != nullptr )
			{
				predecessor = predecessor->_right;
			}

			if(predecessor->_right == nullptr)
			{
				predecessor->_right = current;				
				current = current->_left;
			}
			else
			{
				predecessor->_right=nullptr;
				visit(current);
				current=current->_right;
			}
		}
	}
}



Node* insert(Node* root , int data)
{
	Node* freshNode = new Node;
	freshNode->_data = data ;

	if(root==nullptr)
		return freshNode;

	Node* parent=nullptr;
	Node* current=root;

	while(current !=nullptr )
	{
		parent = current ;
		if(data < root->_data)
			current = current->_left;
		else
			current = current->_right;
	}

	if( freshNode->_data < parent->_data )
		parent->_left = freshNode;
	else
		parent->_right = freshNode;
#if 0
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);   
 
    /* return the (unchanged) node pointer */
    return node;
}
#endif	
}

int setHeight(Node* node)
{
	if(nullptr==node)
	{
		return 0;
	}
	else
	{
		return 1+std::max(node->_left != nullptr ? node->_left->_height : 0,
						  node->_right!= nullptr ? node->_right->_height : 0);
	}
}

int setSize(Node* node)
{
	if(nullptr==node)
	{
		return 0;
	}
	else
	{
		return 1+std::max(node->_left != nullptr ? node->_left->_size: 0,
						  node->_right!= nullptr ? node->_right->_size : 0);
	}
}

int height(Node* node)
{
	if(nullptr==node)
	{
		return 0;
	}
	else
	{
		return node->_height;
	}
}

int getbalance(Node* rootLeft, Node* rootRight){
        return height(rootLeft) - height(rootRight);
}

Node* rotateLeft(Node* node)
{
	Node* newNode = node->_right;
	node->_right = node->_right->_left;
	newNode->_left = node ;

	node->_height=setHeight(node);
	node->_size=setSize(node);	

	newNode->_height=setHeight(newNode);
	newNode->_size=setSize(newNode);		

	return newNode;
}

Node* rotateRight(Node* node)
{
	Node* newNode = node->_left;
	node->_left = node->_left->_right;
	newNode->_right=node;
	
	node->_height=setHeight(node);
	node->_size=setSize(node);	

	newNode->_height=setHeight(newNode);
	newNode->_size=setSize(newNode);		

	return newNode;	
}

Node* avlInsert(Node* root , int data)
{
    if(nullptr == root){
        return new Node(data);
    }
    if(root->_data <= data){
        root->_right = insert(root->_right,data);
    }
    else{
        root->_left = insert(root->_left,data);
    }
	
    int balance = getbalance(root->_left, root->_right);
	
    if(balance > 1){
        if(height(root->_left->_left) >= height(root->_left->_right)){
            root = rotateRight(root);
        }else{
            root->_left = rotateLeft(root->_left);
            root = rotateRight(root);
        }
    }else if(balance < -1){
        if(height(root->_right->_right) >= height(root->_right->_left)){
            root = rotateLeft(root);
        }else{
            root->_right = rotateRight(root->_right);
            root = rotateLeft(root);
        }
    }
    else{
        root->_height = setHeight(root);
        root->_size = setSize(root);
    }
return root;	
}

int main()
{

	std::cout << "hello world"<<std::endl;

	Node* node = nullptr;

	node = avlInsert(node, -10);
	node = avlInsert(node, 2);
	node = avlInsert(node, 13);
	node = avlInsert(node, -13);
	node = avlInsert(node, 15);
	node = avlInsert(node, 17);
	node = avlInsert(node, 20);

	morrisInorder(node);
	
	return 0;
}



