/* this is the second of 3 programs for determining the change in excess */
/* Gibbs free energy for mixing of hard sphere monomer with hard sphere */
/* chains by means of calculating insertion probabilities.  */
/* This program in particular calculates G/kT for the polymer chain. */
/* chains.c */ 

#include "../general/graphics.c"
#include "../general/rng.c"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NMAX 1000 /* max # of monomers */
#define PI 3.14159
#define WSIZE 512 /* size of display window only */
#define DP 10 /* degree of polymerization/size of chains */
#define R .015 /* monomer radius */

double D2=R*R*4; /* diameter squared */
double eta = 0.25; /* occupied volume/total volume */
int Nm=0; /* number of monomer units */
int Nc; /* number of chains */
double X[NMAX], Y[NMAX];
//double test_chain_X[DP]; /* for growing a chain before committing */
//double test_chain_Y[DP]; /* for growing a chain before committing */
int graphics = 1;  /* run display or not */

int main(int argc, char *argv[])
{
  int i,j,k; /* loop indices */

  Nc = floor(eta / (PI * R * R * DP));
  if (Nc*DP>NMAX) 
  {
    printf("too many chains: Nc=%d\n", Nc);
    exit(0);
  }

  printf("using %d chains for actual eta = %lf\n", Nc, (double)(DP*Nc*PI*R*R));

  if (graphics) startgraphics();
  randinit();

  /* insert Nc chains */
  i = 0;
  loop_insert: while(i<Nc) // for each chain
  {
    double end_x, end_y;

    // first drop chain end
    end_x=RND();
    end_y=RND();
    if (Pinsert(end_x, end_y))
    {
      X[Nm]=end_x;
      Y[Nm]=end_y;
      Nm++;
//printf("chain end at %lf, %lf\n", end_x, end_y);
//fflush(stdout);
//sleep(1);
    }
    else continue;

    // then grow the chain....    
    loop_chain:for (j=1; j<DP;) // for each monomer in chain
    {
      double test_theta = RND()*PI*2;
      double deltaX, deltaY;
      double testx, testy;
      deltaX = 2*R * cos(test_theta);
      deltaY = 2*R * sin(test_theta);
      testx = end_x + deltaX;
      testy = end_y + deltaY; 
      if (Pinsert(testx, testy))
      {
        X[Nm] = testx;
        Y[Nm] = testy;
        end_x = testx;
        end_y = testy;
        Nm++;
        j++;
//printf("  chain link at %lf, %lf\n", end_x, end_y);
//fflush(stdout);
      }
      else
      {
         /* rollback */
         Nm-=j;
         goto loop_insert; // insert failed, start over
      }
    } /* end loop_chain */
 
printf(" Nm = %d\n", Nm);
printf(" i = %d\n", i);
fflush(stdout);

    drawObjects();
    check4event();

    i++;

  } /* end loop_insert */
 
} /* end main */

int Pinsert(double x, double y)
{
  int i;
  for (i=0; i<Nm; i++)
  {
    if (checkOverlap(i, x, y)) return 0;
  }
  return 1;
}

int checkOverlap(int n1, double x, double y)
{ 
  // returns 0 if x,y doesn't overlap n1
  double r2, dx, dy;

  box5:
  {
    dx = X[n1] - x;
    dy = Y[n1] - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box1:
  {
    dx = X[n1] - 1 - x;
    dy = Y[n1] - 1 - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box2:
  {
    dx = X[n1] - x;
    dy = Y[n1] - 1 - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box3:
  {
    dx = X[n1] + 1 - x;
    dy = Y[n1] - 1 - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box4:
  {
    dx = X[n1] - 1 - x;
    dy = Y[n1] - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box6:
  {
    dx = X[n1] + 1 - x;
    dy = Y[n1] - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box7:
  {
    dx = X[n1] - 1 - x;
    dy = Y[n1] + 1 - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box8:
  {
    dx = X[n1] - x;
    dy = Y[n1] + 1 - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  box9:
  {
    dx = X[n1] + 1 - x;
    dy = Y[n1] + 1 - y;
    r2=dx*dx + dy*dy;
    if (r2 < D2) return 1;
  }

  return 0;
}

void drawObjects()
{
  int i=0;
  gcvalues.foreground = BG_COLOR;
  XChangeGC(dpy, context, GCForeground, &gcvalues);
  XFillRectangle(dpy, window, context, 0, 0, WSIZE*2, WSIZE*2);
  
  gcvalues.foreground = FG_COLOR;
  XChangeGC(dpy, context, GCForeground, &gcvalues);
  for(i=0;i<Nm;i++)
  {
    int XX, YY;
    XX=X[i]*WSIZE;
    YY=Y[i]*WSIZE;
    XFillArc(dpy, window, context, XX-R, YY-R, R*2*WSIZE, R*2*WSIZE, 0, 360*64);
  }
  XFlush(dpy);
}

