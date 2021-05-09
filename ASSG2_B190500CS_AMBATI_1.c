#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *createnode(int k)
{
    struct node *p;
    p = (struct node*)malloc(sizeof(struct node));
    p->data = k;
    p->next = NULL;
    return p;
}

int R,m,c1,c2;
int h1(int k)
{
    return k%m;
}

int hquad(int k,int i)
{
    int j;
    j = h1(k);
    return (j+c1*i+c2*i*i)%m;
}


int h2(int k)
{
    return R - (k % R);
}

int findR()
{

    for(int i = m-1;i > 0;i--)
    {
        int count = 0;
        for(int j = 1;j<i;j++)
        {
            if(i%j == 0)
                count++;
        }
        if(count == 1)
            return i;
    }
}

int hdouble(int k,int i)
{
    int a,b;
    a = h1(k);
    b = h2(k);
    return (a + i * b)%m;
}

void InsertQuad(struct node *H[],int k)
{
    int i = 0;
    struct node *x;
    int h = k%m;
    while(H[h] != NULL && i < m)
    {
        h = hquad(k,i);
        i++;
    }
    x = createnode(k);
    H[h] = x;


}
void InsertDouble(struct node *H[],int k)
{
    int i = 0;
    struct node *x;
    int h = k%m;
    while(H[h] != NULL && i < m)
    {
        h = hdouble(k,i);
        i++;
    }
    x = createnode(k);
    H[h] = x;


}

struct node *searchQuad(struct node *H[],int k)
{
   int i = 0;
   struct node *x;
   x = NULL;
   int h = k%m;
   while(i<m)
   {
       h = hquad(k,i);
       if(H[h] != NULL && H[h]->data == k)
        break;
       i++;
   }
   if(H[h] != NULL && i<m)
        x = H[h];
   return x;
}

struct node *searchDouble(struct node *H[],int k)
{
   int i = 0;
   struct node *x;
   x = NULL;
   int h = k%m;
   while(i<m)
   {
       h = hdouble(k,i);
       if(H[h] != NULL && H[h]->data == k)
        break;
       i++;
   }
   if((H[h] != NULL && i<m))
        x = H[h];
   return x;
}

void DeleteQuad(struct node *H[],int k)
{
    int i = 0;
    int h = k%m;
    while(i<m)
    {
        h = hquad(k,i);
        if(H[h] != NULL && H[h]->data == k)
         break;
        i++;
    }
    if((H[h] != NULL && i<m)&&H[h]->data == k)
       H[h] = NULL;

}

void DeleteDouble(struct node *H[],int k)
{
    int i = 0;
    int h = k%m;
    while(i<m)
    {
        h = hdouble(k,i);
        if(H[h] != NULL && H[h]->data == k)
         break;
        i++;
    }
    if((H[h] != NULL && i<m)&&H[h]->data == k)
       H[h] = NULL;

}

void print(struct node *H[])
{
    int i = 0;
    while(i<m)
    {
        printf("%d ",i);
        printf("(");
        if(H[i] != NULL)
            printf("%d",H[i]->data);
        printf(")\n");
        i++;
    }
}

int main()
{
    char c,a;
    int i;
    int k;
    struct node *x;
    scanf("%c",&c);
    scanf("%d",&m);
    struct node* H[m];
    for(i = 0;i<m;i++)
        H[i] = NULL;
    R = findR();
    if(c == 'a')
    {
        scanf("%d %d",&c1,&c2);
        while(1)
        {
            scanf("%c",&a);
            if(a == 'i')
            {
                scanf("%d",&k);
                InsertQuad(H,k);
            }
            else if(a == 's')
            {
                scanf("%d",&k);
                x = searchQuad(H,k);
                if(x == NULL)
                    printf("-1\n");
                else printf("1\n");
            }
            else if(a == 'd')
            {
                scanf("%d",&k);
                DeleteQuad(H,k);
            }
            else if(a == 'p')
                print(H);
            else if(a == 't')
                break;
        }

    }
    else if(c == 'b')
    {
        while(1)
        {
            scanf("%c",&a);
            if(a == 'i')
            {
                scanf("%d",&k);
                InsertDouble(H,k);
            }
            else if(a == 's')
            {
                scanf("%d",&k);
                x = searchDouble(H,k);
                if(x == NULL)
                    printf("-1\n");
                else printf("1\n");
            }
            else if(a == 'd')
            {
                scanf("%d",&k);
                DeleteDouble(H,k);
            }
            else if(a == 'p')
                print(H);
            else if(a == 't')
                break;
        }

    }
}
