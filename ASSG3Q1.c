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
int isAVL(struct tree *T)
{
    int k = balance(T);
    if(k > 1 || k < -1)
        return 0;
    return 1;
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
    return T;
}
struct tree* Tree_minimum(struct tree *x)
{
    struct tree *a = x;
    while(a->left != NULL)
        a = a->left;
    return a;
}
struct tree* Delete(struct tree *T, int x)
{
    if(T == NULL)
        return T;
    if(x < T->data)
    {
        T->left = Delete(T->left,x);
        if(balance(T) > 1)
            {
                if(balance(T->left) > 0)
                    T = Rotateright(T);
                else
                {
                    T->left = Rotateleft(T->left);
                    T = Rotateright(T);
                }

            }
    }

    else if(x > T->data)
    {
        T->right = Delete(T->right,x);
        if(balance(T) < -1)
            {
                if(balance(T->left) > 0)
                    T = Rotateleft(T);
                else
                {
                    T->right = Rotateright(T->right);
                    T = Rotateleft(T);
                }

            }
    }
    else
    {
        if( (T->left == NULL) || (T->right == NULL) )
        {
            struct tree *temp;
            if(T->left != NULL)
                temp = T->left;
            else temp = T->right;

            if (temp == NULL)
            {
                temp = T;
                T = NULL;
            }
            else
             *T = *temp;
            free(temp);
        }
        else
        {
            struct tree* temp = Tree_minimum(T->right);
            T->data = temp->data;
            T->right = Delete(T->right, temp->data);
        }
    }
    if(T == NULL)
        return T;

    return T;
}
struct tree* search(struct tree *x,int k)
{
        if(x == NULL || k == x->data)
            return x;
        else if(x->data < k)
            return search(x->right,k);
        else if(x->data > k)
            return search(x->left,k);
        return NULL;
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
   struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
   T->root = (struct tree *)malloc(sizeof(struct tree));
   T->root = NULL;
   int k;
   char c;
   struct tree *p;
   while(1)
   {
        scanf("%c",&c);
        if(c == 'i')
        {
            scanf("%d",&k);
            T->root = Insert(T->root,k);
        }
        if(c == 's')
        {
           scanf("%d",&k);
           p = search(T->root, k);
           if(p != NULL)
            printf("TRUE\n");
           else printf("FALSE\n");
        }
        if(c == 'd')
        {
            scanf("%d",&k);
            p = search(T->root, k);
            if(p != NULL){
                T->root = Delete(T->root,k);
                printf("%d\n",k);
            }
            else printf("FALSE\n");
        }
        if(c == 'b')
        {
            scanf("%d",&k);
            p = search(T->root, k);
            if(p != NULL)
                printf("%d\n",balance(p));
            else printf("FALSE\n");
        }
        if(c == 'p')
        {
            print(T->root);
            printf("\n");
        }
        if(c == 'e')
            break;
   }
}
