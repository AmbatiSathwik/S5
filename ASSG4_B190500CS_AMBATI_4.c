#include <stdio.h>
#include <stdlib.h>
struct graph
{
    int v;
    int e;
    struct node *l[100];
    int visit[100];
};

struct node
{
    int vertex;
    struct node *next;
};

struct node* createnode(int v)
{
    struct node *x = (struct node*)malloc(sizeof(struct node));
    x->vertex = v;
    x->next = NULL;
    return x;
}

struct graph* MakeGraph(int v,int e)
{
    struct graph *G = (struct graph*)malloc(sizeof(struct graph));
    G->v = v;
    G->e = e;
    for(int i = 0; i<v ;i++)
    {
        G->l[i] = (struct node*)malloc(sizeof(struct node));
        G->l[i] = createnode(i);
        G->visit[i] = 0;
    }
    return G;
}

struct node* edge(struct graph *G,int a,int b)
{
    struct node *x;
    x = createnode(b);
    struct node *t;
    t = G->l[a];
    while(t->next != NULL)
        t = t->next;
    t->next = x;
    return G->l[a];

}

struct Qnode
{
    int v;
    struct Qnode *next;
};
struct queue
{
    struct Qnode *head;
    struct Qnode *tail;
};
struct Qnode *createQnode(int v){
struct Qnode *x;
x=(struct Qnode *)malloc(sizeof(struct Qnode));
x->v=v;
x->next=NULL;
return x;
}
void enqueue(struct queue *Q,int t){
struct Qnode *x;

x = createQnode(t);
if(Q->tail == NULL)
{
    Q->head = x;
    Q->tail = x;
    return;
}
else
{
    Q->tail->next = x;
    Q->tail = x;
}
}

int dequeue(struct queue *Q)
{
    struct Qnode *p;
    p = Q->head;
    Q->head = Q->head->next;
    if(Q->head == NULL)
        Q->tail = NULL;
    return p->v;
}

int queue_empty(struct queue *Q){
if(Q->head==NULL)
    return -1;
else
    return 1;
}

void bfs(struct graph *G,int s)
{
    struct queue *Q;
    Q = (struct queue*)malloc(sizeof(struct queue));
    Q->head = NULL;
    Q->tail = NULL;
    G->visit[s] = 1;
    enqueue(Q,s);
    while(queue_empty(Q) != -1)
    {

        int k = dequeue(Q);
        printf("%d ",k);
        struct node *t;
        t = G->l[k];
        while(t != NULL)
        {
            int v;
            v = t->vertex;

            if(G->visit[v] == 0)
            {
                G->visit[v] = 1;
                enqueue(Q,v);
                if(Q->head == NULL)
                    printf("-1");
                //printf("%d",Q->head->v);
            }
            t = t->next;
        }

    }

}

void dfs(struct graph *G,int s)
{
    struct node *t;
    t = G->l[s];
    G->visit[s] = 1;
    printf("%d ",s);
    while(t != NULL)
    {
        if(G->visit[t->vertex] == 0)
        {
            dfs(G,t->vertex);
        }
        t = t->next;
    }
}

int main()
{
    int v,e;
    struct graph *G;
    scanf("%d %d",&v,&e);
    G = MakeGraph(v,e);
    int x,y;
    for(int i = 0;i < e;i++)
    {
        scanf("%d %d",&x,&y);
        G->l[x] = edge(G,x,y);
    }
    int s;
    scanf("%d",&s);
    bfs(G,s);
    printf("\n");
    for(int i = 0;i < v;i++)
    {

        G->visit[i] = 0;
    }
    dfs(G,s);


}
