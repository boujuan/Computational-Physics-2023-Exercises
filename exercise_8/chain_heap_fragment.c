/****************************************************************/
/*** Simulates chain of hard particles                        ***/
/*** A.K. Hartmann May 2004                                   ***/
/*** Rechnergest�tztes Wissenschaftliches Rechnen             ***/
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
/** pr at time t                        **/
typedef struct
{
  int pl, pr;  /* ids of particles (left,right) */
  double   t;                  /* time of event */
  int pos;         /* position of event in heap */
} event_t;


/** heap stores events: one element: **/
typedef struct
{
  double     t;                /* time of event */
  int event;                     /* id of event */
} heap_elem_t;


/** global data of simulation **/
typedef struct
{
  int              n;          /* number of particles */
  double           L;               /* size of system */
  double           t;                 /* current time */
  double       t_end;            /* end of simulation */
  double       T1,T2;        /* temperatures at walls */
  int       heap_num; /*NEW*/   /* # elements of heap */
  heap_elem_t  *heap; /*NEW*/        /* stores events */
} global_t;



/******************** heap_insert() ******************/
/** Insert event 'event[ev]' into heap 'glob->heap' **/
/**  (and stores position in heap in event          **/
/** PARAMETERS: (*)= return-paramter                **/
/**       glob: global data                         **/
/**      event: array of events                     **/
/*          ev: id of event                         **/
/** RETURNS:                                        **/
/**    nothing                                      **/
/*****************************************************/
void heap_insert(global_t *glob, event_t *event, int ev)
{
  int pos, father;                   /* heap positions */
  heap_elem_t elem;          /* for exchanging elements */

  pos = glob->heap_num++;             /* insert at end */

  // TODO: 1 COMPLETE THIS FUNCTION
  // 1. Insert new event at the end of the heap
  // 2. Compare inserted event with parent and swap if necessary (When the parent's time is greater than the current event's time)
  // 3. Repeat step 2 until the parent's time is not greater than the current event's time
  // heap_elem_t has two parameters: t and event
  // event_t has three parameters: pl, pr, and t
  
  glob->heap[pos].event = ev;         // assign event id to the new heap element at position pos
  glob->heap[pos].t = event[ev].t;    // assign event time

  // Step 2 and 3 loop
  while (pos != 0) // Because at 0, there is no parent (root)
  {
    father = (pos - 1) / 2; // Calculate the parent's position
    // If the parent's time is greater than the current event's time, swap them
    if (glob->heap[father].t > glob->heap[pos].t)
    {
      elem = glob->heap[father]; // temporal variable to store the father's element
      glob->heap[father] = glob->heap[pos]; 
      glob->heap[pos] = elem; // swap the father's element with the current element

      // Update the event's position in the heap
      event[glob->heap[pos].event].pos = pos;
    }
    else
    {
      //Heap is in order
      break;
    }

    pos = father; // Move up to the parent after swapping
  }

  // Position of current element may have changed. Update the event's position in the heap again.
  event[glob->heap[pos].event].pos = pos;
}

/******************** heap_remove() ******************/
/** Deletes event at position 'pos' from heap       **/
/** (and updates positions in heap in 'event')      **/
/** PARAMETERS: (*)= return-paramter                **/
/**       glob: global data                         **/
/**      event: array of events                     **/
/*         pos: ps of event in heap                 **/
/** RETURNS:                                        **/
/**    nothing                                      **/
/*****************************************************/
void heap_remove(global_t *glob, event_t *event, int pos)
{
  int finished;
  int left, right, father, min;
  heap_elem_t elem;

  event[glob->heap[pos].event].pos = -1;           /* remove last */
  if(pos == (glob->heap_num-1))                 /* last element ? */
  {
    glob->heap_num--;
    return;                                           /* finished */
  }
  glob->heap[pos] =                    /* put last element at pos */
    glob->heap[--glob->heap_num];
  father = (pos-1)/2; // Calculate the parent's position
  if(glob->heap[father].t > glob->heap[pos].t)
    while((pos > 0)&&                          /* move up in heap */
	  (glob->heap[father].t > glob->heap[pos].t)) 
    {
      elem = glob->heap[father];           /* exchange father/son */
      glob->heap[father] = glob->heap[pos];
      glob->heap[pos] = elem;
      event[glob->heap[pos].event].pos = pos;
      pos = father;                                    /* move up */
      father = (pos-1)/2;   
    }
  else
  {
    finished = 0;
    while(!finished)               /* move element down until all */
    {                                   /* sons have higher times */
      left = 2*pos+1;
      right = 2*pos+2;
      if(left >= glob->heap_num)                       /* no sons */
      {
	finished = 1;
	break;
      }
      else if(right >= glob->heap_num)                 /* one son */
      {
	min = left;
      }
      else                                            /* two sons */
      {
	if(glob->heap[left].t < glob->heap[right].t)
	  min = left;
	else
	  min = right;
      }
      if(glob->heap[pos].t < glob->heap[min].t)
      {
	finished = 1;     /* minimum son does NOT have lower time */
	break;
      }
      elem = glob->heap[pos];                 /* exchange pos,min */
      glob->heap[pos] = glob->heap[min];
      glob->heap[min] = elem;
      event[glob->heap[pos].event].pos = pos;          /* connect */
      pos = min;
    }
  }
  event[glob->heap[pos].event].pos = pos;              /* connect */
 
}


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
/** time glob->t, then glob->t+1 is returned.       **/
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
    event[ev].pl = ev;
    event[ev].pr = ev+1;
    event[ev].t = event_time(ev, ev+1, glob, part);
    heap_insert(glob, event, ev);
  }

  return(event);
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

  heap_remove(glob, event, event[ev].pos);
  if(pl==0)                 /* collision w. left wall */
  {
    part[pr].v = generate_maxwell(part[pr].m, glob->T1);
    event[pl].t = glob->t_end+1;
    heap_remove(glob, event, event[pr].pos);
    event[pr].t = event_time(pr, pr+1, glob, part);
    heap_insert(glob, event, pr);
  }
  else if(pr==(glob->n+1)) /* collision w. right wall */
  {
    part[pl].v = -generate_maxwell(part[pl].m, glob->T2);
    /*printf("v=%f\n", part[pl].v);*/
    event[pl].t = glob->t_end+1;
    heap_remove(glob, event, event[pl-1].pos);
    event[pl-1].t = event_time(pl-1, pl, glob, part);
    heap_insert(glob, event, pl-1);
  }
  else
  {
    vl = part[pl].v; vr = part[pr].v;
    part[pl].v = ( (part[pl].m-part[pr].m)*vl + 2*part[pr].m*vr )/
      (part[pl].m + part[pr].m);
    part[pr].v = ( 2*part[pl].m*vl - (part[pl].m-part[pr].m)*vr )/
      (part[pl].m + part[pr].m);
    heap_remove(glob, event, event[pl-1].pos);
    event[pl-1].t = event_time(pl-1, pl, glob, part);
    heap_insert(glob, event, pl-1);
    event[pl].t = glob->t_end+1;
    heap_remove(glob, event, event[pr].pos);
    event[pr].t = event_time(pr, pr+1, glob, part);
    heap_insert(glob, event, pr);
  }
  heap_insert(glob, event, pl);

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
  double t_measure, delta_measure;
  int bin, num_bins;
  int num_measure;
  double delta_x;

  srand48(1000);          /* initialize random numbers */
  glob.n = atoi(argv[1]);  /* read number of particles */
  sscanf(argv[2], "%lf", &glob.t_end);
  glob.L = (double) glob.n;
  glob.t = 0;                       /* start at time 0 */
  glob.T1 = 2.0;
  glob.T2 = 8.0;

  glob.heap = (heap_elem_t *) 
    malloc((glob.n+1)*sizeof(heap_elem_t));
  glob.heap_num = 0;

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
    /*ev = next_event0(&glob, event);*//* treat next event */
    ev = glob.heap[0].event;
    t_next = event[ev].t;
    if(t_next < glob.t_end) /* next event before end ? */
    {
      if( (t_next - t_measure) > delta_measure)
      {
	num_measure++;          /* perform measurement */
	t_measure += delta_measure;
	for(p=1; p<=glob.n; p++) 
	{
	  bin = (int) floor( 
	     (part[p].x+(t_measure-part[p].t)*part[p].v)/
	     delta_x);
	  /*density[bin]+= part[p].m*part[p].v*part[p].v/
	    delta_x;*/
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
  free(glob.heap);
  return(0);
}
