#include <stdio.h>
#include <stdlib.h>

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

struct tree* createtree(int k)
{
	struct tree *a;
	a = (struct tree*)malloc(sizeof(struct tree));
	a->data = k;
	a->p = NULL;
	a->l = 1;
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

struct tree* search(struct tree *x,int k)
{
        if(x == NULL || k == x->data)
            return x;
        else if(x->data < k)
            return search(x->right,k);
        else if(x->data > k)
            return search(x->left,k);
}

void Transplant(struct treehead *T,struct tree *u,struct tree *v)
{
    if(u->p == NULL)
        T->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    if(v != NULL)
        v->p = u->p;
}

struct tree* Tree_minimum(struct tree *x)
{
    struct tree *a = x;
    while(a->left != NULL)
        a = a->left;
    return a;
}
struct tree* Tree_maximum(struct tree *x)
{
    struct tree *a = x;
    while(a->right != NULL)
        a = a->right;
    return a;
}

struct tree *Delete(struct treehead *T,struct tree *z)
{
    if(z->left == NULL)
        Transplant(T,z,z->right);
    else if(z->right == NULL)
        Transplant(T,z,z->left);
    else
    {
        struct tree *y = Tree_minimum(z->right);
        if(y->p != z)
        {
            Transplant(T,y,y->right);
            y->right = z->right;
            y->right->p = y;
        }
        Transplant(T,z,y);
        y->left = z->left;
        y->left->p = y;
    }
    printf("%d\n",z->data);
    return T->root;
    return T->root;
}

void inorder(struct tree *T)
{
	if(T != NULL)
	{
		inorder(T->left);
		printf("%d ",T->data);
		inorder(T->right);
	}
}

void preorder(struct tree *T)
{
	if(T != NULL)
	{
		printf("%d ",T->data);
		preorder(T->left);
		preorder(T->right);
	}
}

void postorder(struct tree *T)
{
	if(T != NULL)
	{
		postorder(T->left);
		postorder(T->right);
		printf("%d ",T->data);
	}
}
struct tree* level(struct tree *T,int a)
{
    if(T!=NULL)
    {
        if(T->data == a)
            return T;
        level(T->left,a);
        level(T->right,a);
    }
}
struct tree* predecessor(struct treehead *T,struct tree *x)
{
    struct tree *p;
    p = NULL;
    if(x == Tree_minimum(T->root))
    {
        return NULL;
    }
    if(x->left != NULL)
    {
        p = x->left;
        while(p->right != NULL)
        {
            p = p->right;
        }
        return p;
    }
    else
    {
        while(x->p->right != x)
        {
            x = x->p;
        }
        if(x != T->root)
            return x->p;
        else return NULL;
    }
}
struct tree* successor(struct treehead *T,struct tree *x)
{
    struct tree *p;
    p = NULL;
    if(x == Tree_maximum(T->root))
    {
        return NULL;
    }
    if(x->right != NULL)
    {
        p = x->right;
        while(p->left != NULL)
        {
            p = p->left;
        }
        return p;
    }
    else
    {
        while(x->p->left != x)
        {
            x = x->p;
        }
        if(x != T->root)
            return x->p;
        else return NULL;
    }
}
int main()
{
   struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
   T->root = (struct tree *)malloc(sizeof(struct tree));
   T->root = NULL;
   char c;
   int k;
   struct tree *x;
   while(1)
   {
       scanf("%c",&c);
       if(c == 'a')
       {
           scanf("%d",&k);
           x = createtree(k);
           T->root = Insert(T,x);
       }
       else if(c == 's')
       {
           scanf("%d",&k);
           x = search(T->root,k);
           if(x == NULL)
            printf("-1\n");
           else printf("1\n");
       }
       else if(c == 'd')
       {
           scanf("%d",&k);
           x = search(T->root,k);
           if(x != NULL)
            T->root = Delete(T,x);
           else printf("-1\n");
       }
       else if(c == 'i')
       {
			inorder(T->root);
			printf("\n");
       }
       else if(c == 'p')
		{
			preorder(T->root);
			printf("\n");
		}
		else if(c == 't')
		{
			postorder(T->root);
			printf("\n");
		}
		else if(c == 'l')
        {
            int a;
            struct tree *z;
            scanf("%d",&a);
            z = level(T->root,a);
            if(z!=NULL)
                printf("%d\n",z->l);
            else printf("-1\n");
        }
        else if(c == 'm')
        {
            struct tree* a;
            a = Tree_minimum(T->root);
            printf("%d\n",a->data);
        }
        else if(c == 'x')
        {
            struct tree* a;
            a = Tree_maximum(T->root);
            printf("%d\n",a->data);
        }
        else if(c == 'r')
        {
            int a;
            scanf("%d",&a);
            struct tree *x,*y;
            x = search(T->root,a);
            if(x != NULL){
                y = predecessor(T,x);
                printf("%d\n",y->data);
            }
            else
                printf("-1\n");
        }
        else if(c == 'u')
        {
            int a;
            scanf("%d",&a);
            struct tree *x,*y;
            x = search(T->root,a);
            if(x != NULL){
                y = successor(T,x);
                printf("%d\n",y->data);
            }
            else
                printf("-1\n");
        }
		else if(c == 'e')
			break;
   }
}
