#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

NODE;

typedef struct g
{
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct s
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v)
{
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    } /*/*/
    return g;
}

STK *create_s(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(STK *s, int pshd)
{
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr)
{
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(s, v_nr);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
}

int pot_sa_se_intalneasca(GPH *g, int start1, int start2)
{
    STK *s1 = create_s(2 * g->v);
    STK *s2 = create_s(2 * g->v);

    DFS(g, s1, start1);
    wipe(g, g->v);
    DFS(g, s2, start2);

    for (int i = 0; i <= s1->t; i++)
    {
        for (int j = 0; j <= s2->t; j++)
        {
            if (s1->arr[i] == s2->arr[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    int nrv, edg_nr;
    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr, nrv);

    int start1, start2;
    printf("Persoana 1 pleaca din nodul: ");
    scanf("%d", &start1);
    printf("Persoana 2 pleaca din nodul: ");
    scanf("%d", &start2);

    if (pot_sa_se_intalneasca(g, start1, start2))
    {
        printf("Cei doi pot sa se intalneasca intr un nod comun \n");
    }
    else
    {
        printf("Cei doi nu se pot intalni.\n");
    }

    return 0;
}
