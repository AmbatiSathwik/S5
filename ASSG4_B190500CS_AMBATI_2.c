#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int w;
    struct node *next;
};

struct node* createnode(int v)
{
    struct node *x = (struct node*)malloc(sizeof(struct node));
    x->vertex = v;
    x->w = 0;
    x->next = NULL;
    return x;
}

struct graph* MakeGraph(int v)
{
    struct graph *G = (struct graph*)malloc(sizeof(struct graph));
    G->v = v;
    G->e = 0;
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

int d[100];
int min(struct graph *G)
{
    int min_node = -1;
    int min;
    min = 99999;
    for(int i = 0; i<G->v ; i++)
    {
        if(d[i] <= min && G->visit[i] == 0)
        {
            min = d[i];
            min_node = i;
        }
    }
    return min_node;
}

void prims(struct graph *G)
{
    int minval = 0;
    for(int i = 0; i<G->v ; i++)
    {
        d[i] = 99999;
        G->visit[i] = 0;
    }
    d[0] = 0;
    for(int i = 0;i < G->v-1; i++)
    {
        int u = min(G);
        if(u != -1 && G->visit[u] == 0)
        {
            G->visit[u] = 1;
            struct node *t;
            t = G->l[u];
            t = t->next;
            while(t != NULL)
            {
                if(G->visit[t->vertex] == 0 && d[t->vertex] > t->w)
                    d[t->vertex] = t->w;
                t = t->next;
            }
        }
    }
    for(int i = 0;i<G->v;i++)
    {
        minval = minval + d[i];
    }
    printf("%d",minval);
}

struct edge
{
    int s;
    int d;
    int w;
};

struct graph1
{
    int v;
    int e;
    struct edge *edges[100];
};

struct graph1* MakeGraph1(int v)
{
    struct graph1 *G = (struct graph1*)malloc(sizeof(struct graph1));
    G->v = v;
    G->e = 0;
    for(int i = 0;i<100;i++)
    {
        G->edges[i] = (struct edge*)malloc(sizeof(struct edge));
    }
    return G;
}

struct graph1* sort(struct graph1 *G)
{
    for(int i = 1; i<G->e; i++)
    {
        for(int j = 0; j < G->e-1; j++)
        {
            if(G->edges[j]->w > G->edges[j+1]->w)
            {
                struct edge *temp;
                temp = G->edges[j];
                G->edges[j] = G->edges[j+1];
                G->edges[j+1] = temp;
            }
        }
    }
    return G;
}

struct set
{
    int parent;
    int rank;
};

int find(struct set *s[],int k)
{
    if(s[k]->parent != k)
        s[k]->parent = find(s,s[k]->parent);
    return s[k]->parent;
}

void Union(struct set *s[],int a,int b)
{
    int x,y;
    x = find(s,a);
    y = find(s,b);
    if(x != y)
    {
        if(s[x]->rank >= s[y]->rank)
        {
            s[y]->parent = x;
            if(s[x]->rank == s[y]->rank)
                s[x]->rank = s[x]->rank + 1;
        }
        else
        {
            s[x]->parent = y;
        }
    }
}

void kruskal(struct graph1 *G)
{
    G = sort(G);
    /*for(int i = 0;i < G->e;i++)
    {
        printf("%d ",G->edges[i]->s);
        printf("%d ",G->edges[i]->d);
        printf("%d ",G->edges[i]->w);
        printf("\n");
    }*/
    struct set *s[G->v];
    for(int i = 0; i<G->v;i++)
    {
        s[i] = (struct set*)malloc(sizeof(struct set));
        s[i]->parent = i;
        s[i]->rank = 0;
    }
    int min = 0;
    int e = 0;
    for(int i = 0; i<G->e; i++)
    {
        int x,y;
        x = find(s,G->edges[i]->s);
        y = find(s,G->edges[i]->d);
        if(x != y)
        {
            min = min + G->edges[i]->w;
            /*printf("%d ",G->edges[i]->s);
            printf("%d ",G->edges[i]->d);
            printf("%d ",G->edges[i]->w);
            printf("\n");*/
            Union(s,x,y);
            e++;
        }
        if(e >= G->v-1)
            break;

    }
    printf("%d",min);

}

int main()
{
    char ch;
    scanf("%c",&ch);
    if(ch == 'b')
    {
        int v,e;
        struct graph *G;
        scanf("%d",&v);
        G = MakeGraph(v);
        int x,y;
        char c;
        for(int i = 0;i < v;i++)
        {
            scanf("%d%c",&y,&c);
            if(c == '\n')
                continue;
            while(1)
            {
                scanf("%d%c",&x,&c);
                G->l[y] = edge(G,y,x);
                G->e = G->e + 1;
                if(c == '\n')
                    break;
            }
        }
        for(int i = 0;i < v;i++)
        {
            scanf("%d%c",&y,&c);
            if(c == '\n')
                continue;
            struct node *t;
            t = G->l[y];
            t = t->next;
            while(t != NULL)
            {
                scanf("%d%c",&x,&c);
                t->w = x;
                t = t->next;
                if(c == '\n')
                    break;
            }
        }
        /*for(int i = 0;i < v;i++)
        {
            struct node *t;
            t = G->l[i];
            while(t != NULL)
            {
                printf("%d ",t->w);
                t = t->next;
            }
            printf("\n");
        }*/
        prims(G);
        for(int i = 0; i<v ; i++)
        {
            G->visit[i] = 0;
        }
    }
    else if(ch == 'a')
    {
        int v,e;
        struct graph1 *G;
        scanf("%d",&v);
        G = MakeGraph1(v);
        int x,y;
        char c;
        int j = 0;
        for(int i = 0;i < v;i++)
        {
            scanf("%d%c",&y,&c);
            if(c == '\n')
                continue;
            while(1)
            {
                scanf("%d%c",&x,&c);
                G->edges[j]->s = y;
                G->edges[j]->d = x;
                G->e = G->e + 1;
                j++;
                if(c == '\n')
                    break;
            }
        }
        j = 0;
        for(int i = 0;i < v;i++)
        {
            scanf("%d%c",&y,&c);
            if(c == '\n')
                continue;
            while(1)
            {
                scanf("%d%c",&x,&c);
                G->edges[j]->w = x;
                j++;
                if(c == '\n')
                    break;
            }
        }
        /*for(int i = 0;i < G->e;i++)
        {
            printf("%d ",G->edges[i]->s);
            printf("%d ",G->edges[i]->d);
            printf("%d ",G->edges[i]->w);
            printf("\n");
        }*/
        kruskal(G);

    }
}
