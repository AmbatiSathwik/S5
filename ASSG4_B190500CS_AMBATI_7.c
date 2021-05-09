#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *p;
    int key;
    int rank;
};

struct node* MakeSet(int a)
{
    struct node *x;
    x = (struct node*)malloc(sizeof(struct node));
    x->p = x;
    x->key = a;
    x->rank = 0;
}
int count[3];
struct node* find(struct node *x,int k)
{
    if(k == 0)
        count[0]++;
    if(k == 1)
        count[1]++;
    if(x->p != x)
        return find(x->p,k);
    else
        return x;
}

struct node* find_compression(struct node *x,int k)
{
    if(k == 2)
        count[2]++;
    if(k == 3)
        count[3]++;
    if(x->p != x)
        x->p = find_compression(x->p,k);
    return x->p;
}

struct node* Union1(struct node *x,struct node *y,int k)
{
    struct node *a,*b;
    a = find(x,k);
    b = find(y,k);
    if(a == b)
        return a;
    else
    {
        b->p = a;
        return a;
    }
}

struct node* Union2(struct node *x,struct node *y,int k)
{
    struct node *a,*b;
    a = find(x,k);
    b = find(y,k);
    if(a == b)
        return a;
    else
    {
        if(a->rank >= b->rank)
        {
            b->p = a;
            if(a->rank == b->rank)
                a->rank = a->rank + 1;
            return a;
        }
        else
        {
            a->p = b;
            return b;
        }
    }
}

struct node* Union3(struct node *x,struct node *y,int k)
{
    struct node *a,*b;
    a = find_compression(x,k);
    b = find_compression(y,k);
    if(a == b)
        return a;
    else
    {
        b->p = a;
        return a;
    }
}

struct node* Union4(struct node *x,struct node *y,int k)
{
    struct node *a,*b;
    a = find_compression(x,k);
    b = find_compression(y,k);
    if(a == b)
        return a;
    else
    {
        if(a->rank >= b->rank)
        {
            b->p = a;
            if(a->rank == b->rank)
                a->rank = a->rank + 1;
            return a;
        }
        else
        {
            a->p = b;
            return b;
        }
    }
}


int main()
{
    struct node *a[50],*b[50],*c[50],*d[50];
    for(int i =0;i<50;i++)
    {
        a[i] = NULL;
        b[i] = NULL;
        c[i] = NULL;
        d[i] = NULL;
    }
    char ch;
    int x,y;
    struct node *m,*n,*o,*p;
    while(1)
    {
        scanf("%c",&ch);
        if(ch == 'm')
        {
            scanf("%d",&x);
            if(a[x] == NULL)
            {a[x] = MakeSet(x);
            b[x] = MakeSet(x);
            c[x] = MakeSet(x);
            d[x] = MakeSet(x);
            printf("%d\n",a[x]->key);}
            else
                printf("-1\n");
        }
        if(ch == 'u')
        {
            scanf("%d %d",&x,&y);
            if(a[x] != NULL || a[y] != NULL)
            {m = Union1(a[x],a[y],0);
            n = Union2(b[x],b[y],1);
            o = Union3(c[x],c[y],2);
            p = Union4(d[x],d[y],3);
            printf("%d %d %d %d\n",m->key,n->key,o->key,p->key);}
            else
                printf("-1 -1 -1 -1\n");
        }
        if(ch == 'f')
        {
            scanf("%d",&x);
            if(a[x] != NULL)
            {m = find(a[x],0);
            n = find(b[x],1);
            o = find_compression(c[x],2);
            p = find_compression(d[x],3);
            printf("%d %d %d %d\n",m->key,n->key,o->key,p->key);}
            else
                printf("-1 -1 -1 -1\n");
        }
        if(ch == 's')
        {
            printf("%d %d %d %d\n",count[0],count[1],count[2],count[3]);
        }
        if(ch == 'e')
            break;

    }
}
