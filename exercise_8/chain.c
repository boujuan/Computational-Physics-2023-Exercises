/****************************************************************/
/*** Simulates chain of hard particles                        ***/
/*** A.K. Hartmann May 2004                                   ***/
/*** Rechnergestütztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** data structure for one particle **/
typedef struct
{
  double  m;                            /* mass */
  double  x;       /* position at last collision*/
  double  t;          /* time of last collision */
  double  v;   /* velocity after last collision */
} particle_t;

/** event= particle p1 hits on particle **/
/** p2 at time t                        **/
typedef struct
{
  double   t;                  /* time of event */
} event_t;

/** global data of simulation **/
typedef struct
{
  int        n;          /* number of particles */
  double     L;               /* size of system */
  double     t;                 /* current time */
  double t_end;            /* end of simulation */
  double T1,T2;        /* temperatures at walls */
} global_t;



/****************** init_particles() *****************/
/** Initialises data of particles. 2+glob->n        **/
/** particles will be initialzed, particle 0 and    **/
/** particles 1+glob-N are walls                    **/
/** PARAMETERS: (*)= return-paramter                **/
/**       glob: global data                         **/
/** RETURNS:                                        **/
/**    pointer to particle array                    **/
/*****************************************************/
particle_t *init_particles(global_t *glob)
{
  int p;
  particle_t *part;

  part = (particle_t *) malloc( (2+glob->n)*sizeof(particle_t));

  part[0].x = 0;                           /* left wall */
  part[0].t = 0;
  part[0].v = 0;
  part[0].m = 1e50;
  part[1+glob->n].x = glob->L;            /* right wall */
  part[1+glob->n].t = 0;
  part[1+glob->n].v = 0; 
  part[1+glob->n].m = 1e50; 
  for(p=1; p<=glob->n; p++)          /* other particles */
  {
    part[p].x = (double) p*glob->L/(1+glob->n);
    part[p].v = 2*drand48()-1;  /* velocities in [-1,1] */
    part[p].t = 0;
    part[p].m = 1+(p%2)*1.4;      /* alternating masses */
  }

  return(part);
}


/********************* event_time() ******************/
/** Calculates time of collision for particles 'pl' **/
/** and 'pr'. if no collision larger than current   **/
/** time glob->t, then glob->t_end+1 is returned.   **/
/** PARAMETERS: (*)= return-paramter                **/
/**      pl,pr: ids of particles                    **/
/**       glob: global data                         **/
/**       part: data of particles                   **/
/** RETURNS:                                        **/
/**    pointer to event array                       **/
/*****************************************************/
double event_time(int pl, int pr, global_t *glob, particle_t *part)
{
  int exch;                          /* for exchanging ids */
  double time;                               /* next event */

  if(pl>pr)   /* left paricle id should be the smaller one */
  {
    exch = pl; pl = pr; pr = exch;
  }
  if( ((part[pl].v <= 0)&&(part[pr].v >= 0)) || 
      (part[pl].v == part[pr].v))   /* 1st test for no collision */
    return(glob->t_end+1);                       /* no collision */
  time = ((part[pl].x - part[pl].t*part[pl].v) - 
	     (part[pr].x-part[pr].t*part[pr].v))/
            (part[pr].v - part[pl].v);
  if(time <= glob->t)                     /* collision in past ? */
    return(glob->t_end+1);                       /* no collision */
  else
    return(time);                              /* collision time */
}

/********************* init_events() *****************/
/** Initialises data of events. Event i contains    **/
/** the next collision between particle i and i+1   **/
/** PARAMETERS: (*)= return-paramter                **/
/**       glob: global data                         **/
/**       part: data of particles                   **/
/** RETURNS:                                        **/
/**    pointer to event array                       **/
/*****************************************************/
event_t *init_events(global_t *glob, particle_t *part)
{
  int ev;
  event_t *event;                   /* array of events */

  event = (event_t *) malloc( (glob->n+1)*sizeof(event_t));
  for(ev=0; ev<=glob->n; ev++)
  {
    event[ev].t = event_time(ev, ev+1, glob, part);
  }

  return(event);
}


/******************** next_event0() ******************/
/** Finds next event from list by linear search     **/
/** PARAMETERS: (*)= return-paramter                **/
/**       glob: global data                         **/
/**      event: array of events                     **/
/** RETURNS:                                        **/
/**    id of next event                             **/
/*****************************************************/
int next_event0(global_t *glob, event_t *event)
{
  int ev;
  int ev_min;
  ev_min = 0;
  for(ev=1; ev<=glob->n; ev++)       /* scan all events */
    if(event[ev].t < event[ev_min].t)      /* earlier ? */
      ev_min = ev;
  return(ev_min);
}

/*************** generate_maxwell() ******************/
/** Generates random number according the distr.    **/
/** F(v)=1-exp(-mv^2/2T) (v>0), F(u)=0 (v<0)        **/
/** PARAMETERS: (*)= return-paramter                **/
/**      m: mass of particle                        **/
/**      T: temperature                             **/
/** RETURNS:                                        **/
/**    random number                                **/
/*****************************************************/
double generate_maxwell(double m, double T)
{
  return(sqrt(-2*T*log(drand48())/m));
}

/******************** treat_event() ******************/
/** Treat event 'ev' from 'event' array:            **/
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
  int pl, pr;               /* particles of collision */
  double vl, vr;           /* velocities of particles */

  pl = ev;
  pr = ev+1;
  
  part[pl].x += (event[ev].t-  part[pl].t)*part[pl].v;
  part[pr].x += (event[ev].t - part[pr].t)*part[pr].v;
  part[pl].t = event[ev].t;
  part[pr].t = event[ev].t;

  if(pl==0)                 /* collision w. left wall */
  {
    part[pr].v = generate_maxwell(part[pr].m, glob->T1);
    event[pl].t = glob->t_end+1;
    event[pr].t = event_time(pr, pr+1, glob, part);
  }
  else if(pr==(glob->n+1)) /* collision w. right wall */
  {
    part[pl].v = -generate_maxwell(part[pl].m, glob->T2);
    /*printf("v=%f\n", part[pl].v);*/
    event[pl].t = glob->t_end+1;
    event[pl-1].t = event_time(pl-1, pl, glob, part);
  }
  else
  {
    vl = part[pl].v; vr = part[pr].v;
    part[pl].v = ( (part[pl].m-part[pr].m)*vl + 2*part[pr].m*vr )/
      (part[pl].m + part[pr].m);
    part[pr].v = ( 2*part[pl].m*vl - (part[pl].m-part[pr].m)*vr )/
      (part[pl].m + part[pr].m);
    event[pl-1].t = event_time(pl-1, pl, glob, part);
    event[pl].t = glob->t_end+1;
    event[pr].t = event_time(pr, pr+1, glob, part);
  }

}


int main(int argc, char *argv[])
{
  global_t glob;                 /* global system data */
  particle_t *part;             /* particles of system */
  int p;                             /* id of particle */
  int ev;                               /* id of event */
  event_t *event;   /* next events for particles i,i+1 */
  double t_next;                 /* time of next event */
  double num_events;         /* count number of events */
  double *density;             /* for measuring rho(x) */
  int bin, num_bins;
  double delta_x;
  double t_measure, delta_measure;
  int num_measure;

  srand48(1000);          /* initialize random numbers */
  glob.n = atoi(argv[1]);  /* read number of particles */
  sscanf(argv[2], "%lf", &glob.t_end);
  glob.L = (double) glob.n;
  glob.t = 0;                       /* start at time 0 */
  glob.T1 = 2.0;
  glob.T2 = 8.0;

  num_bins = 50;
  delta_x = glob.L/num_bins;
  density = (double *) malloc(num_bins*sizeof(double));
  for(bin=0; bin<num_bins; bin++)
    density[bin] = 0;

  part = init_particles(&glob);
  event = init_events(&glob, part);

  /*for(p=0; p<=glob.n+1; p++)
    printf("%d %f %f\n", p, part[p].x, part[p].v);
  for(ev=0; ev<=glob.n; ev++)
    printf("%d [%d,%d] %f\n", ev, event[ev].pl, 
    event[ev].pr, event[ev].t);*/

  num_events = 0;
  num_measure = 0;  delta_measure = 10;  
  t_measure = glob.t_end/2;   /* half time = equil. */
  while(glob.t < glob.t_end)              /* main loop */
  {
    ev = next_event0(&glob, event);/* treat next event */
    t_next = event[ev].t;
    if(t_next < glob.t_end) /* next event before end ? */
    {
      while( (t_next - t_measure) > delta_measure)
      {
	num_measure++;          /* perform measurement */
	t_measure += delta_measure;
	for(p=1; p<=glob.n; p++) 
	{
	  bin = (int) floor( 
	     (part[p].x+(t_measure-part[p].t)*part[p].v)/
	     delta_x);
	  density[bin]+= 1/delta_x;
	}
      }

      treat_event(&glob, part, event, ev);
      num_events++;
    }
    glob.t = t_next;              /* wind forward time */
  }

  for(bin=0; bin<num_bins; bin++)
    printf("%f %f\n", (bin+0.5)*delta_x, (double) 
	   density[bin]/num_measure);
  fprintf(stderr, "# %e events\n", num_events);

  free(part);
  free(density);
  free(event);
  return(0);
}
