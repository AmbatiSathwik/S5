#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data,degree;
    struct node *p;
    struct node *child;
    struct node *siblings;
};
struct heap
{
    struct node *head;
};

struct heap *Makeheap()
{
    struct heap *h;
    h = (struct heap*)malloc(sizeof(struct heap));
    h->head = NULL;
    return h;
}
struct node *createnode(int k)
{
    struct node *x;
    x = (struct node*)malloc(sizeof(struct node));
    x->data = k;
    x->degree = 0;
    x->p = NULL;
    x->child = NULL;
    x->siblings = NULL;
    return x;
}
void link(struct node *x, struct node *y)
{
    //linking x to y
    x->p = y;
    x->siblings = y->child;
    y->child = x;
    y->degree = y->degree + 1;
}

struct node *merge(struct node *x, struct node *y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;
    struct node *t;
    t = NULL;
    if(x->degree <= y->degree)
        t = x;
    else t = y;

    while(x != NULL && y != NULL)
    {
        if(x->degree < y->degree)
        {
            x = x->siblings;
        }
        else if(x->degree == y->degree)
        {
            struct node *temp;
            temp = x->siblings;
            x->siblings = y;
            x = temp;
        }
        else
        {
            struct node *temp;
            temp = y->siblings;
            y->siblings = x;
            y = temp;
        }
    }
    return t;
}
struct heap *Union(struct heap *h1, struct heap *h2)
{
    struct heap *h;
    h = Makeheap();
    h->head = merge(h1->head,h2->head);
    struct node *prev, *x, *next;
    prev = NULL;
    x = h->head;
    next = x->siblings;
    while(next != NULL)
    {
        if(x->degree != next->degree || (next->siblings != NULL && next->siblings->degree == x->degree))
        {
            prev = x;
            x = next;
        }
        else if(x->data <= next->data)
        {
            x->siblings = next->siblings;
            link(next,x);
        }
        else
        {
            if(prev == NULL)
                h->head = next;
            else
                prev->siblings = next;
           link(x,next);
        }
        next = x->siblings;
    }
    return h;
}
struct node *insert(struct heap *H, struct node *x)
{
    if(H->head == NULL)
        return x;
    struct heap *H1;
    H1 = Makeheap();
    H1->head = x;
    H = Union(H,H1);
    return H->head;
}
int minimum(struct heap *H)
{
    struct node *t;
    t = H->head;
    int min = 999999;
    while(t != NULL)
    {
        if(t->data < min)
            min = t->data;
        t = t->siblings;
    }
    return min;
}
struct node* revert(struct node *x)
{
    if(x == NULL)
        return NULL;
    struct node *t;
    if(x->siblings != NULL)
    {
        t = revert(x->siblings);
        x->siblings->siblings = x;
    }
    else
    {
        t = x;
    }
    return t;
}
struct heap* Extractmin(struct heap *H)
{
    struct node *t;
    t = H->head;
    struct node *x;
    x = NULL;
    struct node *pre;
    pre = NULL;
    int min = 999999;
    while(t != NULL)
    {
        if(t->data < min)
        {
            min = t->data;
            x = t;
        }
        t = t->siblings;
    }
    t = H->head;
    while(t != NULL)
    {
        if(t == x)
            break;
        pre = t;
        t = t->siblings;
    }
    if(pre != NULL)
        pre->siblings = x->siblings;
    else
    {
        H->head = x->siblings;
    }
    struct heap *H1;
    H1 = Makeheap();
    H1->head = revert(x->child);
    if(x->child != NULL)
        x->child->siblings = NULL;
    H = Union(H,H1);
    return H;
}
struct node * search(struct node *x, int k)
{
    if(x != NULL)
    {
        if(x->data == k)
            return x;
        struct node *t;
        t = search(x->child, k);
        if(t != NULL)
            return t;
        return search(x->siblings, k);
    }
    return NULL;
}
struct heap * Decrease(struct heap *H, struct node *x,int k)
{
    struct node *t;
    t = x;
    x->data = x->data - k;
    while(t->p != NULL && t->data < t->p->data)
    {
        int temp;
        temp = t->data;
        t->data = t->p->data;
        t->p->data = temp;
        t = t->p;
    }
    return H;

}
struct heap *Delete(struct heap *H, struct node *x)
{
    if(H == NULL)
        return NULL;
    H = Decrease(H,x,99999);
    H = Extractmin(H);
    return H;

}
struct Qnode
{
    struct node *t;
    struct Qnode *next;
};
struct queue
{
    struct Qnode *head;
    struct Qnode *tail;
};
struct Qnode *createQnode(struct node *t){
struct Qnode *x;
x=(struct Qnode *)malloc(sizeof(struct Qnode));
x->t=t;
x->next=NULL;
return x;
}
struct Qnode*  enqueue(struct queue *Q,struct node *t){
struct Qnode *x;

x = createQnode(t);
struct Qnode *p;
p=Q->tail;
if(Q->tail==NULL){
    Q->head=x;
    Q->tail=x;
    }
else{
    Q->tail->next=x;
    Q->tail=x;
}
return Q->head;
}

struct node* dequeue(struct queue *Q)
{
    struct Qnode *p;
    p = Q->head;
    if(Q->head->next != NULL)
        Q->head = p->next;
    else
        Q->head = NULL;
    return Q->head->t;
}

int queue_empty(struct queue *Q){
if(Q->head==NULL)
    return -1;
else
    return 1;
}

void print(struct heap *H)
{
    struct node* t = H->head;
    while(t != NULL)
    {
        struct queue *x = (struct queue *)malloc(sizeof(struct queue));
        x->head = NULL;
        x->tail = NULL;
        printf("%d ", t->data);
        if(t->child != NULL)
            x->head = enqueue(x,t->child);
        struct node *j,*m;
        while(x->head != NULL)
        {
            j = x->head->t;
            while(j != NULL)
            {
                printf("%d ", j->data);
                if(j->child != NULL)
                    x->head = enqueue(x,j->child);
                j = j ->siblings;
            }
            m = dequeue(x);
        }
        t = t->siblings;
    }
}
int main()
{
    struct heap *H;
    H = Makeheap();
    int k,y,z;
    struct node *x;
    char c;
    while(1)
    {
        scanf("%c",&c);
        if(c == 'i')
        {
            scanf("%d",&k);
            x = createnode(k);
            H->head = insert(H,x);
        }
        if(c == 'd')
        {
            scanf("%d",&k);
            x = search(H->head,k);
            if(x == NULL)
                printf("-1\n");
            else
            {
                H = Delete(H,x);
            }
        }

        if(c == 'm')
        {
            int min;
            min = minimum(H);
            printf("%d\n",min);
        }
        if(c == 'p')
        {
              print(H);
              printf("\n");
        }

        if(c == 'x')
        {
            int min;
            min = minimum(H);
            printf("%d\n",min);
            H = Extractmin(H);
        }
        if(c == 'r')
        {
            scanf("%d %d",&y,&z);
            x = search(H->head,y);
            if(x == NULL)
                printf("-1\n");
            else if(y<z)
                printf("-1\n");
            else
            {
                H = Decrease(H,x,z);
            }
        }
        if(c == 'e')
            break;
    }
}
