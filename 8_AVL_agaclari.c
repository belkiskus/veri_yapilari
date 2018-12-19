#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    struct node *left;
    struct node *right;
    int height;//derinlik
};

int max(int a,int b)
{
    return a>b ? a:b;
}

struct node *newNode(int key)
{
    struct node *node=(struct node*)malloc(sizeof(struct node));
    node->key=key;
    node->left=node->right=NULL;
    node->height=1;
    return node;
}

int height(struct node *node)
{
    if(node==NULL)return 0;
    return node->height;
}

int getBalance(struct node *node)
{
    if(node==NULL)return 0;
    return height(node->left) - height(node->right);
}

struct node *rightRotate(struct node *y)
{
    struct node *x=y->left,*t=x->right;
    x->right=y;
    y->left=t;

    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

    return x;
}//sol soll

struct node *leftRotate(struct node *x)
{
    struct node *y=x->right,*t=y->left;
    y->left=x;
    x->right=t;

    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;

    return y;
}//sað sað

void insert(struct node **node,int key)
{
    int balance;
    if(*node==NULL){
        *node=newNode(key);
    }
    else if(key<(*node)->key)
        insert(&((*node)->left),key);
    else
        insert(&((*node)->right),key);


    (*node)->height=max(height((*node)->left),height((*node)->right))+1;
    balance=getBalance(*node);

    if(balance>1 && key<(*node)->left->key)//sol sol
    {
        (*node)=rightRotate(*node);
    }
    if(balance<-1 && key>(*node)->right->key)//sað sað
    {
        (*node)=leftRotate(*node);
    }
    if(balance>1 && key>(*node)->left->key)//sol sað
    {
        (*node)->left=leftRotate((*node)->left);
        (*node)=rightRotate(*node);
    }
    if(balance<-1 && key<(*node)->right->key)//sað sol
    {
        (*node)->right=rightRotate((*node)->right);
        (*node)=leftRotate(*node);
    }

}

void preOrder_yardimci(struct node *node)
{
    if(node!=NULL)
    {
        printf("%d (%2d) ",node->key,node->height);
        preOrder_yardimci(node->left);
        preOrder_yardimci(node->right);
    }
}

int main()
{
    struct node *root=NULL;

    insert(&root,40);
    insert(&root,35);
    insert(&root,38);
    insert(&root,60);
    insert(&root,80);
    insert(&root,50);
    insert(&root,21);

    preOrder_yardimci(root);

    return 0;
}
