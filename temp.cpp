void pqueue_sort_key(Pqueue pq1, Pqueue pq2)
{
    int k, j;
 
    for (k = 1; k <= pq1->count; k++) {
        /* Verifichiamo le chiavi */
        if (pq1->key[k] != pq2->key[k]) {
            /* Non corrisposte */
            for (j = 1; j <= pq2->count; j++) {
                /* Cerchiamo quella corretta */
                if (pq1->key[k] == pq2->key[j]) {
                    /* Trovata! */
                    swap(&pq2->h[k], &pq2->h[j]);
                    swap(&pq2->key[k], &pq2->key[j]);
                }
            }
        }
    }
}


static int cmp(int i, int j)
{
 
    if (i < j) {
        return (-1);
    } else if (i > j) {
        return (1);
    }
 
    return (0);
}
 
static int father(Pqueue pq, int i)
{
 
    if (pq == NULL) {
        fprintf(stderr, "father(): non esiste una coda\n");
        return (-1);
    }
         
    if (i >= 2 && i <= pq->count) {
        return (i / 2);
    }
     
    return (i);
}
 