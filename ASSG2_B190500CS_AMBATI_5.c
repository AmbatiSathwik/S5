#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int i = 1;
int n;
int find(char c[], int l,int h)
{
    if(l>h)
        return -1;
    int open = 1;
    int close = 0;
    for(int i = l+1;i<=h;i++)
    {
        if(c[i] == ')')
            close++;
        else if(c[i] == '(')
            open++;
        if(open - close == 0)
            return i;
    }
    return -1;
}
struct tree * Insert(char c[],int l,int h)
{

    if(l>h)
        return NULL;
    if(c[l] != '(' && c[l] != ')'){
    struct tree *p;
    int neg = 0;
    if(c[l] == '-')
    {
        neg = 1;
        l++;
    }
    int num=0;

    while(l <= h && c[l] != '(' && c[l] != ')')
    {
        int a = c[l] - '0';
        num = num*10 + a;
        l++;
    }
    if(neg) num = -num;
    p = createtree(num);

    int i = -1;
    if(l<h && c[l] == '(')
        i = find(c,l,h);
    if(i != -1)
    {

        p->left = Insert(c,l+1,i-1);

        p->right = Insert(c,i+2,h-1);

    }
    return p;
    }
    return NULL;
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
struct tree* search(struct tree *T,int k)
{
    struct tree *m;
    struct tree *n;
    if(T == NULL)
        return NULL;
    if(T->data == k)
        return T;
    m = search(T->left,k);
    if(m != NULL)
        return m;
    n = search(T->right,k);
    if(n != NULL)
        return n;
}
struct tree *predecessor(struct treehead *T,int k)
{
    struct tree *x;
    x = search(T->root,k);
    struct tree *c;
    c = Tree_minimum(T->root);
    if(x != NULL)
    {
        struct tree *p;

        p = NULL;
        if(x == c)
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
            struct tree *b;
            b = T->root;
            while(b != x)
            {
                if(b->data < x->data)
                {
                    if(b->data > c->data  && b->data < x->data)
                        c = b;
                    b = b->right;
                }
                else
                {
                    if(b->data > c->data && b->data < x->data)
                        c = b;
                    b = b->left;
                }
            }
            return c;
        }
    }
    return x;
}

struct tree *successor(struct treehead *T,int k)
{
    struct tree *x;
    x = search(T->root,k);
     struct tree *c;
    c = Tree_maximum(T->root);
    if(x != NULL)
    {
        struct tree *p;

        p = NULL;
        if(x == c)
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
            struct tree *b;
            b = T->root;
            while(b != x)
            {
                if(b->data > x->data)
                {
                    if(b->data < c->data  && b->data > x->data)
                        c = b;
                    b = b->left;
                }
                else
                {
                    if(b->data < c->data  && b->data > x->data)
                        c = b;
                    b = b->right;
                }
            }
            return c;
        }
    }
    return x;
}
char *space(char c[])
{
    char *s;
    char m[10000];
    s = m;

    int i = 0;
    int j = 0;
    while(c[i] != '\0')
    {
        if(c[i] != ' ')
        {
            m[j] = c[i];
            j++;
        }
        i++;
    }

    return s;
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
int count = 0;
int array[10000];
void small(struct tree *T)
{
	if(T != NULL)
	{

		small(T->left);
		array[count++]=T->data;
		small(T->right);
	}
}

int main()
{
   struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
   T->root = (struct tree *)malloc(sizeof(struct tree));
   T->root = NULL;
   char c[10000];
   struct tree *x;
    char *s;
    scanf("%[^\n]%*c",c);
    n = strlen(c);
    s = space(c);
    char a;
    T->root = Insert(s,1,n-1);
    while(1)
    {
        scanf("%c",&a);
        if(a == 'r')
        {
            int r;
            scanf("%d",&r);
            x = predecessor(T,r);
            if(x != NULL)
                printf("%d\n",x->data);
            else printf("-1\n");
        }
        else if(a == 'u')
        {
            int u;
            scanf("%d",&u);
            x = successor(T,u);
            if(x != NULL)
                printf("%d\n",x->data);
            else printf("-1\n");
        }
        else if(a == 'i')
        {
            inorder(T->root);
            printf("\n");
        }
        else if(a == 's')
        {
            int k;
            scanf("%d",&k);
            small(T->root);
            if(k<count)
                printf("%d\n",array[k-1]);
            else printf("-1\n");
        }
        else if(a == 'l')
        {
            int k;
            scanf("%d",&k);
            small(T->root);
            if(k<count)
                printf("%d\n",array[count-k-1]);
            else printf("-1\n");
        }
        else if(a == 'e')
            break;
    }

}
