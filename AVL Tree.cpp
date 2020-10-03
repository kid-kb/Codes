#include <bits/stdc++.h>

using namespace std;

typedef struct node
{
    int data=0;
    struct node *left=NULL, *right=NULL;
    int height = 1;
}node;


void preOrder(node* root);
node* insert(node* root, int key);
int getBalance(node *root);
node* deleteNode(node *root, int val);
int height(node *root);
node* leftRotate(node *a);
node* rightRotate(node *a);
node* minValNode(node *root);

int main()
{

    node *root = NULL;
    
    cout<<"Inserting 40"<<endl;
    root = insert(root, 40);
    // Tree: 40
    preOrder(root);
    cout<<endl<<endl;
    
    cout<<"Inserting 20"<<endl;
    root = insert(root, 20);
    // Tree:    40
    //        /
    //      20
    preOrder(root);
    cout<<endl<<endl;
    
    cout<<"Inserting 10"<<endl;
    root = insert(root, 10);
    // Tree:      20
    //          /   \
    //         10   40   
    preOrder(root);
    cout<<endl<<endl;
    
    cout<<"Inserting 25"<<endl;
    root = insert(root, 25);
    // Tree:      20
    //          /   \
    //         10   40 
    //              /
    //             25
    preOrder(root);
    cout<<endl<<endl;
    
    cout<<"Inserting 30"<<endl;
    root = insert(root, 30);
    // Tree:      20
    //          /   \
    //         10   30 
    //             / \
    //           25  40
    
    preOrder(root);
    cout<<endl<<endl;
    
    cout<<"Inserting 22"<<endl;
    root = insert(root, 22);
    // Tree:      25
    //          /   \
    //         20   30 
    //        /  \    \
    //       10  22   40
    preOrder(root);
    cout<<endl<<endl;
    
    cout<<"Inserting 50"<<endl;
    root = insert(root, 50);
    // Tree:      25
    //          /    \
    //        20     40 
    //       /  \   /  \
    //      10  22 30  50
    preOrder(root);
    cout<<endl<<endl;
    
    preOrder(root);
    cout<<endl;
    cout<<"Deletion in LL imbalance"<<endl;
    cout<<"Deleting 40, 30 and 50"<<endl;
    root = deleteNode(root, 40);
    root = deleteNode(root, 30);
    root = deleteNode(root, 50);
    // Tree:      20
    //          /   \
    //        10    25
    //             /
    //            22
    preOrder(root);
    cout<<endl<<endl;
    
    // insert back the 40, 30 and 50
    root = insert(root, 40);
    root = insert(root, 30);
    root = insert(root, 50);
    // Tree:      25
    //          /    \
    //        20     40 
    //       /  \   /  \
    //      10  22 30  50
    preOrder(root);
    cout<<endl;
    cout<<"Deletion in RR imbalance"<<endl;
    cout<<"Deleting 20, 10 and 22"<<endl;
    root = deleteNode(root, 20);
    root = deleteNode(root, 10);
    root = deleteNode(root, 22);
    // Tree:      40
    //          /    \
    //        25     50 
    //          \   
    //          30
    preOrder(root);
    cout<<endl<<endl;
    
    // insert back the 20, 10 and 22
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 22);
    // Tree:      25
    //          /    \
    //        20     40 
    //       /  \   /  \
    //      10  22 30  50
    preOrder(root);
    cout<<endl;
    cout<<"Deletion in LR imbalance"<<endl;
    cout<<"Deleting 10, 30, 50 and 40"<<endl;
    root = deleteNode(root, 10);
    root = deleteNode(root, 30);
    root = deleteNode(root, 50);
    root = deleteNode(root, 40);
    // Tree:      22
    //          /    \
    //        20     25 
    preOrder(root);
    cout<<endl<<endl;
    
    // insert back the 10, 30, 50 and 40
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 50);
    root = insert(root, 40);
    // Tree:      25
    //          /    \
    //        20     40 
    //       /  \   /  \
    //      10  22 30  50
    preOrder(root);
    cout<<endl;
    cout<<"Deletion in RL imbalance"<<endl;
    cout<<"Deleting 50, 10, 22 and 20"<<endl;
    root = deleteNode(root, 50);
    root = deleteNode(root, 10);
    root = deleteNode(root, 22);
    root = deleteNode(root, 20);
    // Tree:      30
    //          /    \
    //        25     40 
    preOrder(root);
    cout<<endl<<endl;
    
    return 0;
}

void preOrder(node *root)  
{  
    if(root != NULL)  
    {  
        cout << root->data << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  

node* insert(node* root, int key)
{
    if(root==NULL){
        root = new node;
        root->data = key;
        return root;
    }
    
    if(key < root->data)
        root->left = insert(root->left, key);
    else if(key > root->data)
        root->right = insert(root->right, key);
    else
    {
        cout<<"Duplicates not allowed !!"<<endl;
        return root;
    }
    
    root->height = 1 + max(height(root->left), height(root->right));
    
    int balance = getBalance(root);
    
    if(balance == 2 && key < root->left->data)
    {
        // LL imbalance
        return rightRotate(root);
    }
    if(balance == -2 && key > root->right->data)
    {
        // RR imbalance
        return leftRotate(root);
    }
    if(balance == 2 && key > root->left->data)
    {
        // LR imbalance
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance == -2 && key < root->right->data)
    {
        // RL imbalance
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

node* deleteNode(node *root, int val)
{
    if(root==NULL){
        cout<<"Empty tree !!"<<endl;
        return root;
    }

    if(val < root->data)
        root->left = deleteNode(root->left, val);
    else if(val > root->data)
        root->right = deleteNode(root->right, val);
    else if(val == root->data)
    {
        // step 1 deletion
        
        // when the node is a leaf node
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            root = NULL;
        }       
        // when the node has single child
        else if(root->left==NULL || root->right==NULL)
        {
            node *childNode;
            if(root->left != NULL)
                childNode = root->left;
            else
                childNode = root->right;
            
            free(root);
            root = childNode;
        }
        // when the node has both children
        else
        {
            node *succ = minValNode(root->right);
            
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
    }
    else{
        cout<<"Value not found!!"<<endl;
        return root;
    }
    

    // step 2 balance the tree

    // if nothing to balance, return
    if(root == NULL)
        return root;
    
    root->height = 1 + max(height(root->left), height(root->right));
    
    int balance = getBalance(root);

    if(balance==2 && getBalance(root->left) >= 0)
    {
        // LL imbalance
        return rightRotate(root);
    }
    else if(balance==-2 && getBalance(root->right) <= 0)
    {
        // RR imbalance
        return leftRotate(root);
    }
    else if(balance==2 && getBalance(root->left) < 0)
    {
        // LR imbalance
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if(balance==-2 && getBalance(root->right) > 0)
    {
        // RL imbalance
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}


int height(node *root)
{
    if(root==NULL)
        return 0;
    return root->height;
}

int getBalance(node *root)
{
    if(root==NULL)
        return 0;
    return height(root->left) - height(root->right);
}

node* leftRotate(node *a)
{
    node *b = a->right;
    node *bl = b->left;
    
    b->left = a;
    a->right = bl;
    
    a->height = 1 + max(height(a->left), height(a->right));
    b->height = 1 + max(height(b->left), height(b->right));
    
    return b;
}

node* rightRotate(node *a)
{
    node *b = a->left;
    node *br = b->right;
    
    b->right = a;
    a->left =  br;
    
    a->height = 1 + max(height(a->left), height(a->right));
    b->height = 1 + max(height(b->left), height(b->right));
    
    return b;
}

node* minValNode(node *root)
{
    if(root==NULL)
        return root;
    node *curr = root;
    while(curr->left != NULL)
        curr = curr->left;
    return curr;
}