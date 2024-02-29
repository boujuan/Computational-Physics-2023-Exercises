/******************** treat_event() ******************/
/** Treat event ’ev’ from ’event’ array:            **/
/** calculate new velocities of particles ev,ev+1   **/
/** recalculate events ev-1, ev, ev+1               **/
/** PARAMETERS: (*)= return-paramter                **/
/**       glob: global data                         **/
/**       part: data of particles                   **/
/**      event: array of events                     **/
/*          ev: id of event                         **/
/** RETURNS:                                        **/
/**    nothing                                      **/
/*****************************************************/
void treat_event(global_t *glob, particle_t *part, event_t *event, int ev)
{
    int pl, pr; /* particles of collision */
    double vl, vr; /* velocities of particles */

    pl = ev;
    pr = ev + 1;

    part[pl].x += (event[ev].t - part[pl].t) * part[pl].v;
    part[pr].x += (event[ev].t - part[pr].t) * part[pr].v;
    part[pl].t = event[ev].t;
    part[pr].t = event[ev].t;

    if (pl == 0) /* collision w. left wall */
    {
        part[pr].v = generate_maxwell(part[pr].m, glob->T1);
        event[pl].t = glob->t_end + 1;
        event[pr].t = event_time(pr, pr + 1, glob, part);
    }
    else if (pr == (glob->n + 1)) /* collision w. right wall */
    {
        part[pl].v = -generate_maxwell(part[pl].m, glob->T2);
        event[pl].t = glob->t_end + 1;
        event[pl - 1].t = event_time(pl - 1, pl, glob, part);
    }
    else
    {
        vl = part[pl].v;
        vr = part[pr].v;

        part[pl].v = ((part[pl].m - part[pr].m) * vl + 2 * part[pr].m * vr) / (part[pl].m + part[pr].m);
        part[pr].v = (2 * part[pl].m * vl - (part[pl].m - part[pr].m) * vr) / (part[pl].m + part[pr].m);

        event[pl - 1].t = event_time(pl - 1, pl, glob, part);
        event[pl].t = glob->t_end + 1;
        event[pr].t = event_time(pr, pr + 1, glob, part);
    }
}