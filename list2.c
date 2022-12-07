#include <stdio.h>
#include <stdlib.h>

typedef struct dlist_tag{
    int data;
    struct dlist_tag *next, *prev;

}dlist;

dlist * first(dlist*L) { return L; }
dlist * next(dlist*L) { return L->next; }



int isempty(dlist*L)
{
        return L->next ? 1 : 0;
}
dlist* last(dlist*L)
{
   return L->prev;
}


dlist *search(dlist *L, int key)
{
    L = L->next;
    while (L->next){
        if (L->data == key) return L;
        L = L->next;
    }
    return 0;
}

dlist* delete(dlist*L, dlist* n)
{
     if(n == L) return n;
     printf("------%d------", last(L)->next);
     printf("%p", n);
     printf("%p", last(L));
     /*if(n == last(L)){
            printf("aaaaaaaaaaaaaaa");
            n->prev->next = first(L)->next;
            first(L)->prev = n->prev;
            n->next = 0;
            n->prev = 0;
     }
     */
     
     printf("\ndeleting %d\n", n->data);
     n->prev->next = n->next;
     n->next->prev = n->prev;
     free(n);
     return n;

}

void destroy(dlist*L)
{
    while(!isempty(L)) {
        dlist * n = first(L);
        delete(L, n);
        free(n);
    }
    free(L);
}
void insert_after(dlist*L,dlist*p,dlist*n)
{
    if(!(p->next)){
        n->next = L;
        L->prev = n;
        n->prev->next = n;
        p->next = n;
    }
    n->next = p->next; n->prev = p;
    p->next = n;
    n->next->prev = n;
    if(n == last(L)) L->prev = n;
}
void delete_by_data(dlist*L, int n)
{

    dlist* dip = search(L, n);
    if(dip!=0 && dip!=L){
        printf("deleting %d\n", dip->data);
        dip->prev->next = dip->next;
        dip->next->prev = dip->prev;
        dip->prev = 0;
        dip->next = 0;
    }

}
dlist* create(int data)
{
    dlist *n = malloc(sizeof(dlist));
    n->next = n->prev = n;
    n->data = data;
    return n;
}

dlist* fill(dlist*L, int N){
    dlist *n;
    for(int i = 0; i <= N; i++){
        n = create(rand());
        insert_after(L, L, n);
    }
}

dlist* print_dlist(dlist *L){
    printf("-----------------------\n");
    for(dlist* i = L->next; i != L; i=i->next){
        printf("%d\n", i->data);
    }
}
int main(void){
    dlist* dL = create(0);
    //printf("%p\n", dL)
    fill(dL, 10);
    print_dlist(dL);
    //printf("%d", last(dL)->next->next->data);
    //printf("-%d-", dL->prev->data);
    delete(dL, search(dL, 0));
    print_dlist(dL);
}