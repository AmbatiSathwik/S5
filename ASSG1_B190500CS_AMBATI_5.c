#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tree
{
    int data;
    int l;
    struct tree *p;
    struct tree *left;
    struct tree *right;
};

struct treehead
{
    struct tree *root;
};
int level = 0;
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
    p->l = level;
    level++;

    int i = -1;
    if(l<h && c[l] == '(')
        i = find(c,l,h);
    if(i != -1)
    {

        p->left = Insert(c,l+1,i-1);

        if(p->left != NULL){
            p->left->p = p;
            level--;
        }

        p->right = Insert(c,i+2,h-1);
        if(p->right != NULL){
            p->right->p = p;
            level--;
        }


    }
    return p;
    }
    return NULL;
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
int count = 0;
int a[10000];
void small(struct tree *T)
{
	if(T != NULL)
	{

		small(T->left);
		a[count++]=T->data;
		small(T->right);
	}
}

int main()
{
    struct treehead *T = (struct treehead *)malloc(sizeof(struct treehead));
    T->root = (struct tree *)malloc(sizeof(struct tree));
    T->root = NULL;
    char c[10000];
    char *s;
    scanf("%[^\n]%*c",c);
    n = strlen(c);
    s = space(c);

    T->root = Insert(s,1,n-1);
    int k;
    scanf("%d",&k);
    small(T->root);
    printf("%d",a[k-1]);
}
