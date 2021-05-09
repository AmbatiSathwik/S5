#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tree
{
    int data;
    int l;
    int bst;
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
	a->bst = 1;
	a->p = NULL;
	a->left = NULL;
	a->right = NULL;
	return a;
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
int checkBST(struct tree *T)
{
    if(T->left != NULL && T->right != NULL)
    {
    if(checkBST(T->left) && checkBST(T->right))
        T->bst = 1;
    else T->bst = 0;
    if(T->bst == 1 && T->data > (Tree_maximum(T->left))->data)
        T->bst = 1;
    else T->bst = 0;
    if(T->bst == 1 && T->data < (Tree_minimum(T->right))->data)
        T->bst = 1;
    else T->bst = 0;
    }
    else if(T->left != NULL && T->right == NULL)
    {
        if(checkBST(T->left))
        T->bst = 1;
        else T->bst = 0;
        if(T->bst == 1 && T->data > (Tree_maximum(T->left))->data)
            T->bst = 1;
        else T->bst = 0;
    }
    else if(T->left == NULL && T->right != NULL)
    {
        if(checkBST(T->right))
        T->bst = 1;
        else T->bst = 0;
        if(T->bst == 1 && T->data > (Tree_minimum(T->right))->data)
            T->bst = 1;
        else T->bst = 0;
    }
    else T->bst = 1;
    return T->bst;
}
int count = 0;
int m;
void SUM(struct tree *T)
{
    if(T != NULL)
    {
        m = m + T->data;
        SUM(T->left);
        SUM(T->right);
    }
}
void BST_1(struct tree *T)
{
    if(T != NULL)
    {
        checkBST(T);
        BST_1(T->left);
        BST_1(T->right);
    }
}
void BST(struct tree *T,int k)
{
    if(T != NULL)
    {
        m = 0;
        SUM(T);
        if(m == k && T->bst == 1){
            count++;

        }
        BST(T->left,k);
        BST(T->right,k);
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
    BST_1(T->root);
    int k;
    scanf("%d",&k);
    BST(T->root,k);
    if(count == 0)
        printf("-1");
    else printf("%d",count);
    //printf("%d ",T->root->right->right->left->data);
    //printf("%d ",T->root->left->left->bst);
    //printf("%d",(Tree_maximum(T->root->left))->data);
}
