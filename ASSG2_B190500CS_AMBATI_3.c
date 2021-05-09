#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char *word;
    struct node *next;
};
int m;
struct node* createnode(char *k)
{
    struct node *p;
    int s;
    s = strlen(k);
    p = (struct node*)malloc(sizeof(struct node));
    p->word = (char*)malloc(sizeof(char)*(s+1));
    strcpy(p->word,k);
    p->next = NULL;
    return p;
}
int power(int n)
{
    int i=0;
    int sum = 1;
    for(i = 0;i<n;i++)
        sum = sum * 2;
    return sum;
}


int index1(char *a)
{

    int h;
    int x = 0;
    int q[8];

    for(int i =0;i<8;i++)
    {

        q[i] = 0;
    }
    while(*a != '\0')
    {
        h = *a - 97;
        q[h] = 1;
        a++;
    }
    int sum = 0;
    int i =0;
    while(i<8)
    {
        if(q[i] == 1)
            sum = sum + power(i);
        i++;
    }

    return sum;
}

void Insert(struct node *H[],char *c)
{
    struct node *x;
    x = NULL;
    x = createnode(c);
    int ind;
    ind = index1(c);
    //printf("%s ",x->word);
    //printf("%d\n",ind);
    struct node *y;
    y = H[ind];
    if(H[ind] == NULL){
        H[ind] = x;
        //printf("%s\n",H[ind]->word);
    }
    else
    {
        struct node *z;
        z = y;
        while(y != NULL)
        {


            if(strcmp(y->word,c)>0)
            {
                break;

            }

            if(strcmp(y->word,c)<0)
            {
                z = y;
                y = y->next;
            }

        }

        if(y != z){
            x->next = y;
            z->next = x;
        }
        else if(y == z)
        {
            x->next = y;
            H[ind]=x;
        }


    }

}

void print(struct node* H[])
{
    int i = 0;
    struct node *y;
    while(i<255)
    {
        y = H[i];
        if(H[i] != NULL)
        {
            while(y != NULL)
            {
                printf("%s ",y->word);
                y = y->next;
            }
            printf("\n");
        }
        i++;
    }
}

int main() {
    struct node *H[255];
    scanf("%d",&m);
    int j=0;
    while(j<255)
    {
        H[j] = NULL;
        j++;
    }
    char *a;
    char b[100];
    a = b;
    int i = 0;
    scanf("\n");
    for(i = 0;i < m;i++)
    {
        scanf("%s",a);
        scanf("\n");
        Insert(H,a);
    }
    print(H);
   //printf("%d",index1("eah"));
}


