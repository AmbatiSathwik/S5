#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct tree
{
    struct tree *p;
    int data;
    int l;
    struct tree *left;
    struct tree *right;
};

struct treehead
{
    struct tree *root;
};
int n;
struct tree* createtree(int k)
{
	struct tree *a;
	a = (struct tree*)malloc(sizeof(struct tree));
	a->data = k;
	a->l = 0;
	a->p = NULL;
	a->left = NULL;
	a->right = NULL;
	return a;
}

struct tree* Insert(struct treehead *T,int m)
{
   struct tree *z;
   z = createtree(m);
   struct tree *y = NULL;
   struct tree *x = T->root;
   while(x != NULL)
   {
       y = x;
       if(z->data < x->data)
        x = x->left;
       else
        x = x->right;
       z->l = z->l + 1;
   }
   z->p = y;
   if(y == NULL)
    T->root = z;
   else if(z->data < y->data)
    y->left = z;
   else
    y->right = z;
   return T->root;
}
void InsertTo(struct treehead* T,int A[],int l,int h)
{
    int m = (l+h)/2;
    if(l<=h && m < n)
    {
        Insert(T,A[m]);
        InsertTo(T,A,l,m-1);
        InsertTo(T,A,m+1,h);
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
    printf(")");
}
void Levelsum(struct tree *T,int *B)
{
    if(T != NULL)
    {
        B[T->l] = B[T->l] + T->data;
        Levelsum(T->left,B);
        Levelsum(T->right,B);
    }
}
int main()
{

    struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
    T->root = (struct tree *)malloc(sizeof(struct tree));
    T->root = NULL;
    scanf("%d",&n);
    int A[n];
    for(int i = 0;i < n;i++)
    {
        scanf("%d",&A[i]);
    }
    InsertTo(T,A,0,n);
    print(T->root);
    printf("\n");
    int m = log(n)/log(2) + 1;
    int *B = (int*)malloc(m*sizeof(int));
    for(int i=0 ;i<m;i++)
        B[i] = 0;
    Levelsum(T->root,B);
    for(int i=0 ;i<m;i++)
        printf("%d ",B[i]);
    return 0;
}
