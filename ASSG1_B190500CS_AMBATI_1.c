#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};

struct treehead
{
    struct tree *root;
};

struct node{
struct tree *t;
struct node *next;
};
struct queue{
struct node *head;
struct node *tail;
};
struct queue *Q;

struct node *createnode(struct tree *t){
struct node *x;
x=(struct node *)malloc(sizeof(struct node));
x->t=t;
x->next=NULL;
return x;
}

struct node* enqueue(struct queue *Q,struct tree *t){
struct node *x;

x = createnode(t);
struct node *p;
p=Q->tail;
if(Q->tail==NULL){
	Q->head=x;
	Q->tail=x;
	}
else{
	Q->tail->next=x;
	Q->tail=x;
}
return Q->head;
}

struct tree*  dequeue(struct queue *Q)
{
    struct node *p;
    p = Q->head;
    if(Q->head->next != NULL)
        Q->head = p->next;
    else
        Q->head = NULL;
    return Q->head->t;

}

int queue_empty(struct queue *Q){
if(Q->head==NULL)
	return -1;
else
	return 1;
}


struct tree* createtree(int k)
{
	struct tree *a;
	a = (struct tree*)malloc(sizeof(struct tree));
	a->data = k;
	a->left = NULL;
	a->right = NULL;
	return a;
}

struct tree* Insert(struct treehead *T,struct tree *x)
{
    if(T->root == NULL)
    {
        T->root = x;
        return T->root;
    }

    Q->head = enqueue(Q,T->root);
    struct tree *temp;
    temp = T->root;
    while(1){
    if(temp->right != NULL)
    {
        temp = dequeue(Q);
    }

    if (temp->left != NULL)
        Q->head = enqueue(Q,temp->left);
    else {
            temp->left = x;
            return T->root;
        }
    if (temp->right != NULL)
            Q->head = enqueue(Q,temp->right);
    else {
            temp->right = x;

            return T->root;
        }
    }
}

void print(struct tree *T)
{
    printf("( ");
    if(T != NULL){
    printf("%d ",T->data);
	print(T->left);
	print(T->right);
    }
    printf(") ");
}

int main()
{
    Q=(struct queue *)malloc(sizeof(struct queue));
    Q->head=(struct node *)malloc(sizeof(struct node));
    Q->tail=(struct node *)malloc(sizeof(struct node));
    Q->head=NULL;
    Q->tail=NULL;
   struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
   T->root = (struct tree *)malloc(sizeof(struct tree));
   T->root = NULL;
   char c;
   int k;
   struct tree *x;
   while(1)
   {
       scanf("%c",&c);
       if(c == 'i')
       {
           scanf("%d",&k);
           x = createtree(k);
           T->root = Insert(T,x);

       }
       else if(c == 'p')
       {
           print(T->root);
           printf("\n");
       }
		else if(c == 'e')
			break;
   }
}
