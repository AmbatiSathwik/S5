#include <stdio.h>
#include <stdlib.h>

struct list
{
    int A[10000][10000];
    int n
};

void List(struct list *M)
{
    for(int i = 0; i<M->n ; i++)
    {
        printf("%d ",i);
        for(int j = 0; j<M->n ; j++)
        {
            if(M->A[i][j] == 1)
                printf("%d ",j);
        }
        printf("\n");
    }
}
int main()
{

    struct list *M;
    M = (struct list*)malloc(sizeof(struct list));
    scanf("%d",&M->n);
    for(int i = 0; i<M->n ; i++)
    {
        for(int j = 0; j<M->n ; j++)
            scanf("%d",&M->A[i][j]);
    }
    List(M);
}
