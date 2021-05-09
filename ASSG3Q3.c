#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int data;
    int colour;
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
    a->colour = 0; //red = 0; black = 1
    a->left = NULL;
    a->right = NULL;
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
            if(T->left->colour == 0)
            {
                if((T->left->left != NULL && T->left->left->colour == 0) ||(T->left->right != NULL && T->left->right->colour == 0))
                {
                    if(T->right != NULL && T->right->colour == 0)
                    {
                        T->right->colour = 1;
                        T->left->colour = 1;
                        T->colour = 0;
                    }
                    else
                    {
                        if(T->left->right != NULL && T->left->right->colour == 0)
                            T->left = Rotateleft(T->left);
                        T = Rotateright(T);
                        T->right->colour = 0;
                        T->colour = 1;
                    }
                }
                }
    }
    else if(k > T->data)
    {
            T->right = Insert(T->right, k);
           if(T->right->colour == 0)
            {

                    if((T->right->right != NULL && T->right->right->colour == 0) ||(T->right->left != NULL && T->right->left->colour == 0))
                    {
                        if(T->left != NULL && T->left->colour == 0)
                        {
                            T->left->colour = 1;
                            T->right->colour = 1;
                            T->colour = 0;
                        }
                        else
                        {
                            if(T->right->left != NULL && T->right->left->colour == 0)
                                T->right = Rotateright(T->right);
                            T = Rotateleft(T);
                            T->left->colour = 0;
                            T->colour = 1;
                        }
                    }
            }
        }

    return T;
}
void print(struct tree *T)
{
    printf("( ");
    if(T != NULL){
    printf("%d ",T->data);
    if(T->colour == 1)
        printf("B ");
    else printf("R ");
    print(T->left);
    print(T->right);
    }
    printf(") ");
}
int main()
{
   struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
   T->root = (struct tree *)malloc(sizeof(struct tree));
   T->root = NULL;
   int k;
   while(scanf("%d",&k)==1)
   {
            T->root = Insert(T->root,k);
            T->root->colour = 1;
            print(T->root);
            printf("\n");
   }
}
