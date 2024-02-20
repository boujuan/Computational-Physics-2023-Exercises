void queens(int c, int N, int *pos, int *row, int *diag_up, int *diag_down)
{
    int r, c2; /* loop counters */

    if (c == -1) /* solution found ? */
    {
        /* omitted here */
        /* print solution */
    }

    for (r = N - 1; r >= 0; r--) /* place queen in all rows of column c */
    {
        if (!row[r] && !diag_up[c - r + (N - 1)] && !diag_down[c + r]) /* place ?*/
        {
            row[r] = 1;
            diag_up[c - r + (N - 1)] = 1;
            diag_down[c + r] = 1;
            pos[c] = r;
            queens(c - 1, N, pos, row, diag_up, diag_down);
            row[r] = 0;
            diag_up[c - r + (N - 1)] = 0;
            diag_down[c + r] = 0;
        }
    }

    pos[c] = 0;
}