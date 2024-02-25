/******************* percol_cluster() *******************/
/** Calculates the connected clusters of the lattice **/
/** ’site’. Occupied sites have ’site[i]=1’ (i=1..N). **/
/** Neigbours of occupied sites form clusters. **/
/** For each site, in ’cluster[i]’ the id of the **/
/** cluster (starting at 0) is stored **/
/** PARAMETERS: (*)= return-paramter **/
/** num_n: number of neighbours **/
/** N: number of sites **/
/** next: gives neighbours (0..N)x(0..num_n-1) **/
/** 0 not used here. Use NEXT() to access **/
/** site: tells whether site is occupied **/
/** (*) cluster: id of clusters sites are contained in **/
/** RETURNS: number of clusters **/
/********************************************************/
int percol_cluster(int num_n, int N, int *next, short int *site, int *cluster)
{
    int num_clusters = 0;
    int t, r; /* loop counters over sites, directions */
    int current, neighbour; /* sites */
    lstack_t *members; /* stack of members for cluster */

    for (t = 1; t <= N; t++) /* initialise all clusters empty */
        cluster[t] = -1;

    members = lstack_new(N, sizeof(int));

    for (t = 1; t <= N; t++) /* loop over all sites */
    {
        if ((site[t] == 1) && (cluster[t] == -1)) /* new cluster ? */
        {
            lstack_push(members, &t); /* start cluster */
            cluster[t] = num_clusters;

            while (!lstack_is_empty(members)) /* extend cluster */
            {
                lstack_pop(members, &current);

                for (r = 0; r < num_n; r++) /* loop over neighbours */
                {
                    neighbour = NEXT(current, r);

                    if ((site[neighbour] == 1) && (cluster[neighbour] == -1))
                    { /* neighbour belongs to same cluster */
                        lstack_push(members, &neighbour);
                        cluster[neighbour] = num_clusters;
                    }
                }
            }

            num_clusters++;
        }
    }

    lstack_delete(members);
    return num_clusters;
}