#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
    int count;
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
	a->count = 0;
	return a;
}

struct tree* Rotateleft(struct tree *x)
{
    struct tree *y = x->right;
    struct tree *z = y->left;
    y->left = x;
    x->right = z;
    return y;
}
struct tree* Rotateright(struct tree *y)
{
    struct tree *x = y->left;
    struct tree *z = x->right;
    x->right = y;
    y->left = z;
    return x;
}

int height(struct tree * x)
{
    int left, right;
    int h;
    if(x == NULL)
        return -1;
    else
    {
        left = height(x->left);
        right = height(x->right);
        h = (left > right)?left : right ;
        h = h+1;
        return h;
    }
}
int balance(struct tree *x)
{
    if(x == NULL)
        return 0;
    int b;
    int l, h;
    l = height(x->left);
    h = height(x->right);
    b = l-h;
    return b;
}


struct tree* Insert(struct tree *T, int k)
{
    if(T == NULL)
    {
        struct tree *x;
        x = createtree(k);
        return x;
    }
    else if(k < T->data)
    {
            T->left = Insert(T->left, k);
            if(balance(T) > 1)
            {
                if(T->left->data > k)
                    T = Rotateright(T);
                else
                {
                    T->left = Rotateleft(T->left);
                    T = Rotateright(T);
                }

            }
    }
    else if(k > T->data)
    {
            T->right = Insert(T->right, k);
            if(balance(T) < -1)
            {
                if(T->right->data < k)
                    T = Rotateleft(T);
                else
                {
                    T->right = Rotateright(T->right);
                    T = Rotateleft(T);
                }

            }
    }
    else if(k == T->data)
    {
        T->count = T->count + 1;
    }
    return T;
}
void print(struct tree *x)
{
    if(x != NULL)
    {
        print(x->left);
        for(int i=0;i<=x->count;i++)
            printf("%d ",x->data);
        print(x->right);
    }
}
int main()
{
    struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
    T->root = (struct tree *)malloc(sizeof(struct tree));
    T->root = NULL;
    int k;
    int x;
    scanf("%d",&k);
    for(int i = 0;i < k; i++)
    {
        scanf("%d",&x);
        T->root = Insert(T->root,x);
    }
    print(T->root);
    printf("\n");
    return 0;
}
