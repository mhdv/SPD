#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <string.h>
#include <values.h>
#include <math.h>

#define SS  sizeof(char)
#define MS  sizeof(int)
#define LS  sizeof(long)

#define OK                   0                 // OK finished
#define ERR                  1                 // memory allocation error

float t;

void intime();
float showtime();
int unif(long *seed, int low, int high);
void ex_gen1(long r[], long p[], long q[], int n, int k);
void ex_gen2(long r[], long p[], long q[], int n, int k);
void ex_gen3(long r[], long p[], long q[], int n, int k);
void ex_genx(long r[], long p[], long q[], int n, int k);

void quicksort(long a[], int pi[], int n, int m);
void _quicksort(long a[], int pi[], int n, int m);
long max(long x, long y);
int  max(int x,  int y);
long min(long x, long y);
int  min(int x,  int y);
long cmax_(long r[], long p[], long q[], int pi[], int n);
void cmax_f(long r[], long p[], long q[], int pi[], long c[], int n);
int __schrage(long r[], long p[], long q[], int pi[], int n, long *c, int *jc, int *jy);
int schrage(long r[], long p[], long q[], int pi[], int n, long *c, int *jc, int *jy);
int __potts(long r[], long p[], long q[], int ppot[], int n, int ln, long *c, int a, int b);
int potts(long r[], long p[], long q[], int ppot[], int n, int ln, long *c, int a, int b);
int __hs(long r[], long p[], long q[], int p_hs[], int n, long *c_hs);
int hs(long r[], long p[], long q[], int p_hs[], int n, long *c_hs);
int ns(long r[], long p[], long q[], int p_ns[], int n, long *c_ns);
int pmtn_bound(long r[], long p[], long q[], int n, long *lb);

void main()
{
  int m=2000;                   // max size of problem

  long *r=NULL;                   // head
  long *p=NULL;                   // body
  long *q=NULL;                   // tail
  int *ps=NULL;                  // permutation
  int n,ln;                     // current problem size
  int k,i1;                     // generator's parameters
  int s;                        // sample size

  long cs,cpot,cpot_hs,ct,_ct,lb;
  int is,i,j,ipots,ihs,jc,jy,jz,ipot_hs,lg,l1,l2,lhs,lp1,lp2;

  int lx=0,ls,lp,lp_hs,lt,lo,xa,ya;

  float ta,tb;
  float tic,tir,tip,tis;

  n=100; k=19; s=20;

  r=(long *)calloc(n+1,LS);
  p=(long *)calloc(n+1,LS);
  q=(long *)calloc(n+1,LS);

  ps=(int *)calloc(n+1,MS);

  clrscr(); q[0]=r[0]=p[0]=0;
  for (is=1;is<=s;is++)
  { lx++;
    ex_gen1(r,p,q,n,k);

    intime();
   ns(r,p,q,ps,n,&ct);
   __hs(r,p,q,ps,n,&cpot_hs);
   __potts(r,p,q,ps,n,n,&cpot,0,0);
   __schrage(r,p,q,ps,n,&cs,&jc,&jy);
//   schrage(r,p,q,ps,n,&ct,&jc,&jy);
   potts(r,p,q,ps,n,n,&ct,0,0);
   pmtn_bound(r,p,q,n,&lb);
   tip=showtime();

   printf("%5d %5d %5d %5ld %5ld %5ld %5ld %5ld %8.3f\n",is,k,n,cs,cpot,cpot_hs,ct,lb,tip);
   getch();

  }

  free(r); free(p); free(q); free(ps);
}

// timer
void intime()
{ struct time s;
  gettime(&s); t=3600.0*s.ti_hour+60.0*s.ti_min+s.ti_sec+0.01*s.ti_hund;
}

float showtime()
{ struct time s;
  gettime(&s); return(3600.0*s.ti_hour+60.0*s.ti_min+s.ti_sec+0.01*s.ti_hund-t);
}

// --- random generator with uniform intger distribution over [low,high]
int unif(long *seed, int low, int high)
{ long k;  double value_0_1;
  long m=2147483647l, a=16807l, b=127773l, c=2836l;

  k=*seed/b; *seed=a*(*seed%b)-k*c;
  if (*seed < 0) *seed=*seed+m;
  value_0_1=*seed; value_0_1/=m;
  return(low+(int)floor(value_0_1*(high-low+1)));
}

// --- nondecreasing sorting
void quicksort(long a[], int pi[], int n, int m)
{
  int i,j,p; long x;

  if (m <= n) return;
  i=n; j=m; x=a[pi[(i+j)>>1]];
  do
  {  while (a[pi[i]] < x) i++;
     while (x < a[pi[j]]) j--;
     if (i <= j) { p=pi[j]; pi[j]=pi[i]; pi[i]=p; i++; j--; }
  }  while (i < j);
  quicksort(a,pi,n,j); quicksort(a,pi,i,m);
}

// --- nondecreasing sorting
void quicksort(int a[], int pi[], int n, int m)
{
  int i,j,p,x;

  if (m <= n) return;
  i=n; j=m; x=a[pi[(i+j)>>1]];
  do
  {  while (a[pi[i]] < x) i++;
     while (x < a[pi[j]]) j--;
     if (i <= j) { p=pi[j]; pi[j]=pi[i]; pi[i]=p; i++; j--; }
  }  while (i < j);
  quicksort(a,pi,n,j); quicksort(a,pi,i,m);
}

// --- decreasing sorting
void _quicksort(long a[], int pi[], int n, int m)
{
  int i,j,p; long x;

  if (m <= n) return;
  i=n; j=m; x=a[pi[(i+j)>>1]];
  do
  {  while (a[pi[i]] > x) i++;
     while (x > a[pi[j]]) j--;
     if (i <= j) { p=pi[j]; pi[j]=pi[i]; pi[i]=p; i++; j--; }
  }  while (i < j);
  _quicksort(a,pi,n,j); _quicksort(a,pi,i,m);
}

long max(long x, long y) { return (x<=y)?y:x; }
int  max(int x,  int y)  { return (x<=y)?y:x; }

long min(long x, long y) { return (x<=y)?x:y; }
int  min(int x, int y)   { return (x<=y)?x:y; }

// --- generator: single long job
void ex_gen1(long r[], long p[], long q[], int n, int k)
{
  int i; long s=0,nk=2*long(n-1)*k;

  for (i=1;i<=n;i++) { r[i]=random(nk); p[i]=1+random(50); s+=p[i];
		       q[i]=random(nk); }
  p[n]=s;
}

// --- generator: two long jobs
void ex_gen2(long r[], long p[], long q[], int n, int k)
{
  int i; long s=0, nk=5*long(n-2)*k;

  for (i=1;i<=n;i++) { r[i]=random(nk); p[i]=1+random(50); s+=p[i];
		       q[i]=random(nk); }
  s=s-p[n-1]-p[n]; p[n-1]=s+random(5); p[n]=s+random(5);
}

// ---> generator: uniform jobs
void ex_gen3(long r[], long p[], long q[], int n, int k)
{
  int i; long nk=long(n)*k;

  for (i=1;i<=n;i++) { r[i]=random(nk); p[i]=1+random(50);
		       q[i]=random(nk); }
}

// ---> generator: ad hoc uniform jobs
void ex_genx(long r[], long p[], long q[], int n, int k)
{
  int i;
  for (i=1;i<=n;i++)
    { r[i]=random(100); p[i]=random(100); q[i]=random(100); }
}

// ---> cmax goal function calculator
long cmax_(long r[], long p[], long q[], int pi[], int n)
{
  int i,j; long t=0,u=0;

  for (i=1;i<=n;i++) { j=pi[i]; t=max(t,r[j])+p[j]; u=max(u,t+q[j]); }
  return u;
}

// ---> provides job completion times
void cmax_f(long r[], long p[], long q[], int pi[], long c[], int n)
{
  int i,j;  for (i=1;i<=n;i++) { j=pi[i]; t=max(t,r[j])+p[j]; c[j]=t; }
}

// ---> swap function
void swap(int *x,  int *y)  { int z;  z=*x; *x=*y; *y=z; }
void swap(long *x, long *y) { long z; z=*x; *x=*y; *y=z; }

// ---> inverse sleave function
void check(int m, int ps[], long q[])
{
  int k=m/2; if (k) { if (q[ps[k]]<q[ps[m]]) { swap(ps+k,ps+m); check(k,ps,q); }}
}

// ---> sleave function
void sleave(int i, int m, int ps[], long q[])
{
   int k=i<<1,u; if (k>m) return;
   u=((k<m)&&(q[ps[k]]<q[ps[k+1]]))?(k+1):k;
   if (q[ps[u]]>q[ps[i]]) { swap(ps+u,ps+i); sleave(u,m,ps,q); }
}

// ---> Schrage's algorithm; O(nlogn); S=2; original (reccursive) implementation
// pi - permutation, c - makespan; pi[iy] - critical job
// pi[ic] - interference job (zero if not exists)
int schrage(long r[], long p[], long q[], int pi[], int n, long *c, int *ic, int *iy)
{
  int *ps=(int *)calloc(n+1,MS); long *_c=(long *)calloc(n+1,LS);
  int i,j,k=0,m=1,e=2,jy; long t,mq;

  if ((!ps)||(!_c)) { free(ps); free(_c); return ERR; } // allocation error

  for (i=1;i<=n;i++) ps[i]=i; quicksort(r,ps,1,n);      // r order
  t=r[ps[1]]; *c=0;                                     // initialize
  while (m||(e<=n))                                     // main loop
  {                                                     // exapand S
    while (e<=n) { if (r[ps[e]]<=t) { ps[++m]=ps[e++]; check(m,ps,q); } else break; }

    if (m)                                              // S non-empty
    { j=ps[1]; pi[++k]=j; t+=p[j]; _c[j]=t;             // schedule j
      if (*c<(t+q[j]))  { *c=t+q[j]; *iy=k; }           // find makespan
      ps[1]=ps[m]; sleave(1,--m,ps,q);                  // remove j from S
    }
    else t=r[ps[e]];                                    // S empty: push time
  }

  jy=pi[*iy]; *ic=0; mq=q[jy]; t=_c[jy]-p[jy];         // find ic,iy
  for (i=*iy-1;i>=1;i--)
  { j=pi[i]; if (_c[j]<t) break;
    if (q[j]<mq) { *ic=i; break; }
    t-=p[j];
  }
  free(ps); free(_c); return OK;
}

// ---> Potts' algorithm; O(n*nlogn); S=3/2; own implementation
// ppot - permutation; cp - makespan; ln - number of repetitions of Schrage
// (a,b) - precedence constraint; a = 0 if such constraint does not exist
int potts(long r[], long p[], long q[], int ppot[], int n, int ln, long *cp, int a, int b)
{
  int i,jcd,jyd;  long cmax;
  long *rd=(long *)calloc(n+1,LS);                   // auxiliary head
  int *pd=(int *)calloc(n+1,MS);                     // auxiliary permutation

  if ((!rd)||(!pd)) goto error;                      // allocation error

  *cp=MAXLONG; memcpy(rd+1,r+1,n*LS);
  for (i=1;i<=ln;i++)                                // main loop
  { if (schrage(rd,p,q,pd,n,&cmax,&jcd,&jyd)) goto error;
    cmax=cmax_(r,p,q,pd,n);
    if (cmax<*cp) { *cp=cmax; memcpy(ppot+1,pd+1,n*MS); }
    if (!jcd) break;                                 // no interference job
    rd[pd[jcd]]=rd[pd[jyd]]; if (a==pd[jcd]) rd[b]=max(rd[b],rd[pd[jyd]]);
  }
  free(rd); free(pd); return OK;
error:
  free(rd); free(pd); return ERR;
}

// ---> Hall and Shmoys' algorithm; O(n*nlogn); S=4/3; own implementation
// p_hs - permutation; c_hs - makespan
int hs(long r[], long p[], long q[], int p_hs[], int n, long *c_hs)
{
  int i,u,v,flag;
  long cp,sum;
  long *rp=(long *)calloc(n+1,LS);                   // auxiliary head
  long *qp=(long *)calloc(n+1,LS);                   // auxiliary tail
  int *ppot=(int *)calloc(n+1,MS);                   // auxiliary permutation

  if ((!rp)||(!qp)||(!ppot)) goto error;             // allocation error

  memcpy(rp+1,r+1,n*LS); memcpy(qp+1,q+1,n*LS);
  sum=0; for (i=1;i<=n;i++) sum+=p[i];               // set sum of p
  sum/=3; u=0; v=0; flag=0;                          // find u,v jobs
  for (i=1;i<=n;i++)
  { if ((p[i]>=sum)&&(flag==0)) { u=i; flag=1; break; }
    if ((p[i]>=sum)&&(flag==1)) { v=i; flag=2; }
  }

  if (flag<=1)                                        // no or single big job
  { if (potts(r,p,q,p_hs,n,n,c_hs,0,0)) goto error;
    if (potts(q,p,r,ppot,n,n,&cp,0,0)) goto error;
    if (*c_hs>cp) { *c_hs=cp; for (i=1;i<=n;i++) p_hs[i]=ppot[n-i+1]; }
  }
  else                                                       // two big jobs
  {
    rp[v]=max(rp[v],rp[u]); qp[u]=max(qp[u],p[v]+qp[v]);     // u->v, basic
    if (potts(rp,p,qp,p_hs,n,2*n-3,c_hs,u,v)) goto error;
    rp[v]=r[v]; qp[u]=q[u];

    qp[u]=max(qp[u],qp[v]); rp[v]=max(rp[v],p[u]+rp[u]);     // u->v, inverse
    if (potts(qp,p,rp,ppot,n,2*n-3,&cp,v,u)) goto error;
    if (*c_hs>cp) { *c_hs=cp; for (i=1;i<=n;i++) p_hs[i]=ppot[n-i+1]; }
    qp[u]=q[u]; rp[v]=r[v];

    rp[u]=max(rp[u],rp[v]); qp[v]=max(qp[v],p[u]+qp[u]);     // v->u, basic
    if (potts(rp,p,qp,ppot,n,2*n-3,&cp,v,u)) goto error;
    if (*c_hs>cp) { *c_hs=cp; memcpy(p_hs+1,ppot+1,n*MS); }
    rp[u]=r[u]; qp[v]=q[v];

    qp[v]=max(qp[v],qp[u]); rp[u]=max(rp[u],p[v]+rp[v]);     // v->u, inverse
    if (potts(qp,p,rp,ppot,n,2*n-3,&cp,u,v)) goto error;
    if (*c_hs>cp) { *c_hs=cp; for (i=1;i<=n;i++) p_hs[i]=ppot[n-i+1]; }
    qp[v]=q[v]; rp[u]=r[u];
  }
  free(rp); free(qp); free(ppot); return OK;
 error:
  free(rp); free(qp); free(ppot); return ERR;
}

// ---> Nowicki and Smutnicki algorithm: O(nlogn); S=3/2; own implementation
// p_ns - permutation; c_ns - makespan
int ns(long r[], long p[], long q[], int p_ns[], int n, long *c_ns)
{
  int i,j=0,k=n+1,jcd,jyd; long cmax;
  int *pd=(int *)calloc(n+1,MS);             // auxiliary permutation

  if (!pd) goto error;                       // allocation error

  if (schrage(r,p,q,p_ns,n,c_ns,&jcd,&jyd)) goto error;
  for (i=1;i<=n;i++) {if (r[i]<=q[i]) pd[++j]=i; else pd[--k]=i; }
  quicksort(r,pd,1,j); _quicksort(q,pd,k,n);
  cmax=cmax_(r,p,q,pd,n);
  if (cmax<*c_ns) { *c_ns=cmax; memcpy(p_ns+1,pd+1,n*MS); }
  free(pd); return OK;
 error:
  free(pd); return ERR;
}

// ---> preemptive bound r-p-q using Schrage's algorithm; own implementation
int pmtn_bound(long r[], long p[], long q[], int n, long *lb)
{ int *ps=(int *)calloc(n+1,MS); long *_p=(long *)calloc(n+1,LS);
  int i,j=0,m=1,e=2; long t,c;

  if (!ps) return ERR; if (!_p) { free(ps); return ERR; }

  for (i=1;i<=n;i++) ps[i]=i; quicksort(r,ps,1,n);        // r order
  t=c=r[ps[1]]; *lb=0; memcpy(_p+1,p+1,n*LS);             // initialize
  while (m||(e<=n))
  { while (e<=n) { if (r[ps[e]]<=t) { ps[++m]=ps[e++]; check(m,ps,q); } else break; }

    if (m)                                                // S non-empty
    { if ((c>t)&&(q[ps[1]]>q[j])) { ps[++m]=j; check(m,ps,q); _p[j]=c-t; c=t; }
      if (c<=t)
      { j=ps[1]; c=t+_p[j];                             // schedule j
	if (*lb<(c+q[j])) *lb=c+q[j];                   // find makespan
	ps[1]=ps[m]; sleave(1,--m,ps,q);                // remove j from S
      }
      t=(e<=n)?min(r[ps[e]],c):c;                       // new time
    }
    else t=c=r[ps[e]];                                  // S empty - push time
  }

  free(ps); free(_p); return OK;
}

// ------------------------------------------------------------------
// old implementations

// ---> Schrage's algorithm; O(nlogn); S=2; own implementation
int __schrage(long r[], long p[], long q[], int pi[], int n, long *c, int *jc, int *jy)
{
  int *ps=NULL; long *_c=NULL;
  int i,j,k=0,m=1,e=2,iy,u,v,par,kx,son; long t,mq;

  ps=(int *)calloc(n+1,MS); if (!ps) goto error;
  _c=(long *)calloc(n+1,LS); if (!_c) goto error;

  for (i=1;i<=n;i++) ps[i]=i; quicksort(r,ps,1,n);
  t=r[ps[1]]; *c=0;
reps:
  if (e<=n)                                        // check non-scheduled yet
  { j=ps[e];
    if (r[j]<=t)                                             // if active
    { ps[++m]=j; i=m; par=i>>1;                              // add j to S
      while (par)
      { if (q[ps[par]]<q[ps[i]])                             // check heap
	{ v=ps[par]; ps[par]=ps[i]; ps[i]=v; i=par; par=i>>1; }
	else break;
      }
      e++; goto reps;
    }
  }
  if (m)                                                   // S non-empty
  { j=ps[1]; pi[++k]=j; t+=p[j]; _c[j]=t;                  // schedule j
    if (*c<(t+q[j]))  { *c=t+q[j]; iy=k; }
    ps[1]=ps[m]; i=1; kx=(--m)>>1;                         // remove j from S
    while (i<=kx)                                          // sleave heap
    { son=i<<1;                                            // son
      u=((son<m)&&(q[ps[son]]<q[ps[son+1]]))?(son+1):son;
      if (q[ps[u]]>q[ps[i]]) { v=ps[u]; ps[u]=ps[i]; ps[i]=v; i=u; } else i=m;
    }
    goto reps;
  }
  else if (e<=n) { t=r[ps[e]]; goto reps; }                 // move time t forward

  *jy=pi[iy]; *jc=0; mq=q[*jy]; t=_c[*jy]-p[*jy]; i=iy-1;   // find jc,jy
next:
  if (i<1) goto end;
  j=pi[i]; if (_c[j]<t) goto end;
  if (q[j]<mq) { *jc=j; goto end; }
  t-=p[j]; i--; goto next;
end:
  free(ps); free(_c); return OK;
error:
  free(ps); free(_c); return ERR;
}

// ---> Potts' algorithm; O(n*nlogn); S=3/2; own implementation
// (a,b) - precedence constraint; a = 0 if such constraint does not exist
int __potts(long r[], long p[], long q[], int ppot[], int n, int ln, long *c, int a, int b)
{
  int i,jcd,jyd;
  long cmax;
  long *rd=NULL;                       // auxiliary head
  int *pd=NULL;                       // auxiliary permutation

  rd=(long *)calloc(n+1,LS); if (!rd) goto error;
  pd=(int *)calloc(n+1,MS); if (!pd) goto error;

  *c=MAXLONG; memcpy(rd+1,r+1,n*LS);
  for (i=1;i<=ln;i++)
  { if (__schrage(rd,p,q,pd,n,&cmax,&jcd,&jyd)) goto error;
    cmax=cmax_(r,p,q,pd,n);
    if (cmax<*c) { *c=cmax; memcpy(ppot+1,pd+1,n*MS); }
    if (!jcd) goto end;
    rd[jcd]=rd[jyd]; if (a==jcd) rd[b]=max(rd[b],rd[jyd]);
  }
 end:
  free(rd); free(pd); return OK;
 error:
  if (rd) free(rd); if (pd) free(pd); return ERR;
}

// ---> Hall and Shmoys' algorithm; O(n*nlogn); S=4/3; own implementation
int __hs(long r[], long p[], long q[], int p_hs[], int n, long *c_hs)
{
  int i,u,v,flag;
  long cp,sum;
  long *rp;                                      // auxiliary head
  long *qp;                                      // auxiliary tail
  int *ppot;                                    // auxiliary permutation

  rp=(long *)calloc(n+1,LS); if (!rp) goto error;
  qp=(long *)calloc(n+1,LS); if (!qp) goto error;
  ppot=(int *)calloc(n+1,MS); if (!ppot) goto error;

  memcpy(rp+1,r+1,n*LS); memcpy(qp+1,q+1,n*LS);
  sum=0; for (i=1;i<=n;i++) sum+=p[i];
  sum/=3; u=0; v=0; flag=0;
  for (i=1;i<=n;i++)
  { if ((p[i]>=sum)&&(flag==0)) { u=i; flag=1; break; }
    if ((p[i]>=sum)&&(flag==1)) { v=i; flag=2; }
  }

  if (flag<=1)
  { if (__potts(r,p,q,p_hs,n,n,c_hs,0,0)) goto error;
    if (__potts(q,p,r,ppot,n,n,&cp,0,0)) goto error;
    if (*c_hs>cp) { *c_hs=cp; for (i=1;i<=n;i++) p_hs[i]=ppot[n-i+1]; }
  }
  else
  {
    rp[v]=max(rp[v],rp[u]); qp[u]=max(qp[u],p[v]+qp[v]);     // u->v, basic
    if (__potts(rp,p,qp,p_hs,n,2*n-3,c_hs,u,v)) goto error;
    rp[v]=r[v]; qp[u]=q[u];

    qp[u]=max(qp[u],qp[v]); rp[v]=max(rp[v],p[u]+rp[u]);    // u->v, inverse
    if (__potts(qp,p,rp,ppot,n,2*n-3,&cp,v,u)) goto error;
    if (*c_hs>cp) { *c_hs=cp; for (i=1;i<=n;i++) p_hs[i]=ppot[n-i+1]; }
    qp[u]=q[u]; rp[v]=r[v];

    rp[u]=max(rp[u],rp[v]); qp[v]=max(qp[v],p[u]+qp[u]);     // v->u, basic
    if (__potts(rp,p,qp,ppot,n,2*n-3,&cp,v,u)) goto error;
    if (*c_hs>cp) { *c_hs=cp; memcpy(p_hs+1,ppot+1,n*MS); }
    rp[u]=r[u]; qp[v]=q[v];

    qp[v]=max(qp[v],qp[u]); rp[u]=max(rp[u],p[v]+rp[v]);     // v->u, inverse
    if (__potts(qp,p,rp,ppot,n,2*n-3,&cp,u,v)) goto error;
    if (*c_hs>cp) { *c_hs=cp; for (i=1;i<=n;i++) p_hs[i]=ppot[n-i+1]; }
    qp[v]=q[v]; rp[u]=r[u];
  }
  free(rp); free(qp); free(ppot); return OK;
 error:
  if (rp) free(rp); if (qp) free(qp); if (ppot) free(ppot);
  return ERR;
}

