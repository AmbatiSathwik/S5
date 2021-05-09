#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *p;
    int key;
    int mark;
    int visit;
    int degree;
    struct node *left;
    struct node *right;
    struct node *child;
};
struct heap
{
    struct node *head;
    struct node *min;
    int n;
    int count;
};

struct node* createnode(int k)
{
    struct node *x;
    x = (struct node*)malloc(sizeof(struct node));
    x->p = NULL;
    x->key = k;
    x->mark = 0;
    x->degree = 0;
    x->visit = 0;
    x->left = x;
    x->right = x;
    x->child = NULL;
    return x;
}

struct heap* makeHeap()
{
    struct heap *H;
    H = (struct heap*)malloc(sizeof(struct heap));
    H->head = NULL;
    H->min = NULL;
    return H;
}

struct node* Insert(struct heap* H,struct node *x)
{
    if(x == NULL)
        return H->head;
    if(H->min == NULL)
    {
        H->head = x;
        H->min = x;
        H->n = H->n + 1;
    }
    else
    {
        H->min->left->right = x;
        x->left = H->min->left;
        x->right = H->min;
        H->min->left = x;
        if(x->key < H->min->key)
            H->min = x;
        H->n = H->n + 1;
    }
    return H->head;
}

struct node* Minimum(struct heap *H)
{
    return H->min;
}

struct node* Link(struct node *n1, struct node *n2)
{
    //linking n1 to n2
    //printf("%d ",n1->key);
    //printf("%d\n",n2->key);
    n1->left->right = n1->right;
    n1->right->left = n1->left;
    n1->p = n2;
    n1->left = n1;
    n1->right = n1;
    if(n2->child == NULL)
        n2->child = n1;
    else
    {
        n1->right = n2->child;
        n1->left = n2->child->left;
        n2->child->left->right = n1;
        n2->child->left = n1;
    }
    if(n2->child->key > n1->key)
        n2->child = n1;
    n2->degree = n2->degree + 1;
    n2->mark = 0;
    return n2;

}

struct heap* Consolidate(struct heap *H)
{
    struct node *A[H->n];
    for(int i = 0; i<H->n ; i++)
        A[i] = NULL;
    struct node *a,*b,*c,*d;
    a = H->min;
    int deg;
    int t;
    t = H->n;
    do
    {
        deg = a->degree;
        while(A[deg] != NULL)
        {
            b = A[deg];
            if(a->key > b->key)
            {
                d = a;
                a = b;
                b = d;
            }
            if(b == H->min)
                H->min = a;
            a = Link(b,a);
            if(b->right == a)
                H->min = a;
            A[deg] = NULL;
            deg++;
        }
        A[deg] = a;
        a = a->right;
    }
    while(a != H->min);
    H->min = NULL;
    H->head = NULL;
    for(int i = 0;i<t; i++)
    {
        if(i == 0)
            H->n = 0;
        if(A[i] != NULL)
        {
            A[i]->left = A[i];
            A[i]->right = A[i];

            H->head = Insert(H,A[i]);
            if(H->min->key > A[i]->key)
                H->min = A[i];

        }
    }
    return H;

}

struct heap* ExtractMin(struct heap *H)
{
    if(H->min == NULL)
        return NULL;
    else
    {
        struct node *t;
        t = H->min;
        struct node *m;
        m = H->min;
        struct node *x;
        x = NULL;
        if(t->child != NULL)
        {
            x = t->child;
            do
            {
                m = x->right;
                x->left = x;
                x->right = x;
                H->head = Insert(H,x);
                x->p = NULL;
                x = m;
            }while(m != t->child);
        }


        t->left->right = t->right;
        t->right->left = t->left;
        H->min = t->right;
        if(t == t->right && t->child == NULL)
            H->min = NULL;
        else
        {
            H->min = t->right;
            H = Consolidate(H);
        }

        return H;
    }
}


struct node* search(struct heap *H,struct node *t,int x)
{
    t->visit = 1;
    struct node *a;
    a = NULL;
    if(t->key == x)
    {
        t->visit = 0;
        return t;
    }

    if(t->child != NULL)
        a = search(H,t->child,x);

    if(t->right->visit != 1)
        a = search(H,t->right,x);
    t->visit = 0;
    return a;
}

void Cut(struct heap *H,struct node *x,struct node *y)
{
    if(x->right == x)
        y->child = NULL;
    if(x == y->child)
        y->child = x->right;
    x->right = x;
    x->left = x;
    struct node *t;
    t = y;
    while(t != NULL)
    {
        t->degree = t->degree - 1;
        t = t->p;
    }
    H->head = Insert(H,x);
    x->p = NULL;
    x->mark = 0;
}

void Cascade(struct heap *H, struct node *t)
{
    struct node *y;
    y = t->p;
    if(y != NULL)
    {
        if(t->mark == 0)
            t->mark = 1;
        else {
            Cut(H,t,y);
            Cascade(H, y);
        }
    }
}

struct heap* DecreseKey(struct heap *H,struct node *x,int y)
{
    x->key = y;
    struct node *t;
    t = x->p;
    if(t != NULL && x->key < t->key)
    {
        Cut(H,x,t);
        Cascade(H,t);
    }
    if(x->key < H->min->key)
        H->min = x;
    return H;
}

struct heap* Delete(struct heap *H,struct node *x)
{
    H = DecreseKey(H,x,-9999);
    H = ExtractMin(H);
    return H;
}
int count;
void print(struct node *H)
{
    struct node *x;
    x = H;
    while(1)
    {
        printf("%d ",x->key);
        if(x->right == H)
            break;
        x = x->right;
    }
}

int main()
{
    struct heap *H;
    H = makeHeap();
    int k,y;
    struct node *x;
    char c;
    while(1)
    {
        scanf("%c",&c);
        if(c == 'i')
        {
            scanf("%d",&k);
            x = createnode(k);
            H->head = Insert(H,x);
            H->count++;
        }
        if(c == 'm')
        {
            printf("%d\n",H->min->key);
        }
        if(c == 'x')
        {
            printf("%d\n",H->min->key);
            H = ExtractMin(H);
            H->count--;
            //printf("%d\n",H->min->key);
        }
        if(c == 'r')
        {
            scanf("%d",&k);
            scanf("%d",&y);
            x = search(H, H->min,k);
            //printf("%d",x->key);
            if(x != NULL)
            {
                if(k < y)
                    printf("-1\n");
                else {
                H = DecreseKey(H, x, y);

                printf("%d\n",y);
                }
            }
            else printf("-1\n");
        }
        if(c == 'd')
        {
            scanf("%d",&k);
            x = search(H, H->min,k);
            if(x != NULL)
            {
                printf("%d\n",x->key);
                H = Delete(H, x);
                H->count--;
            }
            else printf("-1\n");

        }
        if(c == 'p')
        {
            count = H->count;
            print(H->min);
            printf("\n");
        }
        if(c == 'e')
            break;
    }
    //printf(" %d",H->min->right->key);


}
