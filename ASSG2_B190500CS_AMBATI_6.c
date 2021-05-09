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

struct tree* createtree(int k)
{
	struct tree *a;
	a = (struct tree*)malloc(sizeof(struct tree));
	a->data = k;
	a->left = NULL;
	a->right = NULL;
	return a;
}

struct tree* Insert(struct treehead *T,struct tree *z)
{
   struct tree *y = NULL;
   struct tree *x = T->root;
   while(x != NULL)
   {
       y = x;
       if(z->data < x->data)
        x = x->left;
       else
        x = x->right;

   }
   if(y == NULL)
    T->root = z;
   else if(z->data < y->data)
    y->left = z;
   else
    y->right = z;
   return T->root;
}

struct tree* find_root(struct tree *T,int a,int b)
{
        struct tree *x;
        x = T;
        if(x->data >= a && x->data <= b)
            return x;
        else if(x->data > b)
            return find_root(x->left,a,b);
        else if(x->data < a)
            return find_root(x->right,a,b);
}
int Max_path(struct treehead *T,int a,int b)
{
    struct tree *t;
    struct tree *x;
    t = find_root(T->root,a,b);
    x = t;
    int max = t->data;
    while(x->data != b)
    {
        if(x->data > max)
            max = x->data;
        if(x->data < b)
            x = x->right;
        else x = x->left;
    }
    return max;
}
int main()
{
   struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
   T->root = (struct tree *)malloc(sizeof(struct tree));
   T->root = NULL;
   int x,a,b;
   char c;
   int max;
   struct tree *p;
   while(1)
   {
        scanf("%d%c",&x,&c);
        p = createtree(x);
        T->root = Insert(T,p);
        if(c == '\n')
            break;
   }
   scanf("%d %d",&a,&b);
   max = Max_path(T,a,b);
   printf("%d",max);
}
