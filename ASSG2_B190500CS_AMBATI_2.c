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

int index1(char *c)
{
    int l;
    l = strlen(c);
    return (l*l)%m;
}

void insertword(struct node *H[],char *c)
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
        //printf("%s",H[ind]->word);
    }
    else
    {
        while(y->next != NULL){
            if(strcmp(y->word,x->word) == 0)
                return;
            y = y->next;
            if(strcmp(y->word,x->word) == 0)
                return;
        }
       if(strcmp(y->word,x->word) != 0)
        	y->next = x;
        //printf("%s",y->word);
    }

}

struct node * insert(struct node *H[],char *c)
{
    char *a;
    char b[500];
    int i=0;
    a = b;
    while(*c != '\0')
    {
        if(*c == ' ')
        {
            insertword(H,a);
            //printf("%s\n",a);
            //printf("%s\n",H[index1(a)]->word);
            while(i != -1)
            {
                b[i] = '\0';
                i--;
            }
            i = 0;
            c++;
            continue;
        }
        if(*c != ' '){
        b[i] = *c;
        i++;
        c++;
        }
    }
    insertword(H,a);
    //printf("%s ",a);
    //printf("%s\n",H[index1(a)]->word);
    return *H;
}

void print(struct node *H[])
{
    int i = 0;
    struct node *y;
    while(i<m)
    {
        printf("%d:",i);
        y = H[i];
        if(H[i] == NULL)
            printf("null\n");
        else
        {
            while(y != NULL)
            {
                printf("%s",y->word);
                if(y->next != NULL)
                    printf("-");
                y = y->next;
            }
            printf("\n");
        }
        i++;
    }
}

int main()
{
    scanf("%d",&m);
    int i = 0;
    struct node *H[m];
    while(i<m)
    {
        H[i] = NULL;
        i++;
    }
    char *c;
    char a[500];
    c = a;
    scanf("\n");
    scanf("%[^\n]%*c",c);

    *H = insert(H,c);
    //printf("%s",H[4]->word);
    print(H);

}
