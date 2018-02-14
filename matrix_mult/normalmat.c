#include <sys/times.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

	volatile int *mem;
	sem_t *sem;

	double start, stop, used, mf;

	double ftime(void);

	void multiply (double **a, double **b, double **c, int n);

	void transpose(double **a, double **b, double **c, int n);

	void blocked(double **a, double **b, double **c, int n);

	void forked(double **a, double **b, double *d, int n);

	int min(int a, int b){
	return a < b ? a : b;
	}
	
	 void work ( int me )
  {
      int i, n;
      //n = 10000;
      for ( i = 0; i < n; i++ ) {
          sem_wait ( sem );
          *mem = *mem ;
          sem_post ( sem );
          //usleep ( 100 );
        }
  }
	

	double ftime (void)
	{
    struct tms t;
    
    times ( &t );
 
    return (t.tms_utime + t.tms_stime) / 100.0;
	}

	void transpose (double **a, double **b, double **c, int n)
  	{
     int i, j, k;
 
     for (i=0; i<n; i++)
     {
       for (j=0; j<n; j++)
 
           c[i][j] = 0;
      }
 
      for (i=0; i<n; i++)
      {
         for (j=0; j<n; j++)
         {
          for (k=0; k<n; k++)
             c[i][j]= c[i][j] + a[i][k] * b[j][k];
          }
       }
	printf("----------TRANSPOSE-----------\n");
  for(i=0; i<n;i++){
     	 for(j=0;j<n;j++){
  printf(" %.2f ",c[i][j]);
  }
  printf("\n");
  }
  printf("\n");
  }


	void blocked(double **a, double **b, double **c, int n){
	int i, j, k, ii, jj, kk;
	int bb = n/2;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			c[i][j] = 0;
		}

		for(ii=0;ii<n;ii+=bb){
			for( jj=0;jj<n;jj+=bb){
				for(kk=0;kk<n;kk+=bb){
					for(i=ii;i<min(ii+bb,n);i++){
						for(j = jj; j<min(jj+bb,n);j++){
							for(k=kk;k<min(kk+bb,n);k++){
							c[i][j] = c[i][j] + a[i][k] * b[k][j];
						}
					}
				}
			}
		}
	}
	printf("----------BLOCKED----------\n");
	for(i=0; i<n;i++){
		for(j=0;j<n;j++){
		printf(" %.2f ",c[i][j]);
	}
	printf("\n");
	}
	printf("\n");
	}

	void forked(double **a, double **b, double *d,  int n){
 	
	int i, j, k, kk, jj, ii, pid,shmfd,status;
	int bb=128;
	
	shmfd = shm_open ( "/huynha5_memory", O_RDWR | O_CREAT, 0666 );
      if ( shmfd < 0 ) {
          fprintf(stderr,"Could not create huynha5_memory\n");
          exit(1);
      }
      ftruncate ( shmfd, sizeof(double) );
      mem = (int*)mmap ( NULL, n*sizeof(double), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0 );
      if ( mem < 0 ) {
          fprintf(stderr,"Could not map huynha5_memory\n");
          exit(1);
      }
      close ( shmfd );
      shm_unlink ( "/huynha5_memory" );
 
      sem = sem_open ( "huynha5_sem", O_CREAT, 0666, 1 );
      if ( sem == NULL ) {
         fprintf(stderr,"Could not create huynha5 semaphore\n");
         exit(1);
      }
      sem_unlink ( "huynha5_sem" );
      mem[0] = 0;
	  
	  for(ii=0;ii<n;ii+=bb){
              for( jj=0;jj<n;jj+=bb){
                  for(kk=0;kk<n;kk+=bb){
						wait(NULL);
						pid = fork();
          				if ( pid < 0 ) {
              				fprintf(stderr,"fork failed at %d\n",ii);
							exit(1);
          		} else if ( pid > 0 ) {
              	wait(&status);
			//	printf("parent: new child is %d\n",pid);
				} else{
             //	printf("child %d, parent is %d\n",i, getppid());
                      for(i=ii;i<min(ii+bb,n);i++){
                          for(j = jj; j<min(jj+bb,n);j++){
                              for(k=kk;k<min(kk+bb,n);k++){
								//sem_wait(sem);
                          		mem[i*n+j] = mem[i*n+j] + a[i][k] * b[k][j];
								//sem_post(sem);
			}	
			}
    		}
	work(kk);
	exit(0);
		}
		}
		}		
		}
	printf("----------FORKED-----------\n");
	for(i=0; i<n;i++){
		for(j=0; j<n;j++){
   printf(" %.2d ",mem[i]);
   }
   printf("\n");
  	} 
	printf("\n");
	}



	void multiply (double **a, double **b, double **c, int n)
	{
   	int i, j, k;

   	for (i=0; i<n; i++)
   	{
     for (j=0; j<n; j++)
       
         c[i][j] = 0;
    }

    for (i=0; i<n; i++)
    {
       for (j=0; j<n; j++)
       {
         for (k=0; k<n; k++)
           c[i][j]= c[i][j] + a[i][k] * b[k][j];
        }
     }
	printf("-------MULTIPLY--------\n");
 	for(i=0; i<n;i++){
      for(j=0;j<n;j++){
 		 printf(" %.2f ",c[i][j]);
  		}
  	printf("\n");
  	}
  	printf("\n");
  	}
  

	int main (void)
	{
   	int i, j, n;
   	double **a, **b, **c, *d;
	
    printf ( "Enter the value of n: ");
    scanf ( "%d", &n);

   //Populate arrays....
        a= (double**)malloc(n*sizeof(double));
        b= (double**)malloc(n*sizeof(double));
        c= (double**)malloc(n*sizeof(double));
		d= (double*)malloc(n*n*sizeof(double));
   
	for (i=0; i<n; i++)
	{
	a[i]= malloc(sizeof(double)*n);
	b[i]= malloc(sizeof(double)*n);
	c[i]= malloc(sizeof(double)*n);
	}
	for (i=0; i<n; i++)
	{
	for (j=0; j<n; j++)
		a[i][j]=8;
	}   
	for (i=0; i<n; i++)
	{

	for (j=0; j<n; j++)
	b[i][j]=7;
	}
   
	start = ftime();
	multiply (a,b,c,n);
	stop = ftime();
	used = stop - start;
	mf = (n*n*n *2.0) / used / 1000000.0;
	printf ("\n");
	printf ( "Elapsed time:   %10.2f \n", used);
	printf ( "DP MFLOPS:       %10.2f \n", mf);

	start = ftime();
	transpose(a,b,c,n);
	stop = ftime();
	used = stop - start;
	mf = (n*n*n *2.0) / used / 1000000.0;
	printf ("\n");
	printf ( "Elapsed time:   %10.2f \n", used);
	printf ( "DP MFLOPS:       %10.2f \n", mf);


	start = ftime();
	blocked(a,b,c,n);
	stop = ftime();
	used = stop - start;
	mf = (n*n*n *2.0) / used / 1000000.0;
	printf ("\n");
	printf ( "Elapsed time:   %10.2f \n", used);
	printf ( "DP MFLOPS:       %10.2f \n", mf);

 	start = ftime();
 	forked(a,b,d,n);
 	stop = ftime();
 	used = stop - start;
 	mf = (n*n*n *2.0) / used / 1000000.0;
 	printf ("\n");
 	printf ( "Elapsed time:   %10.2f \n", used);
 	printf ( "DP MFLOPS:       %10.2f \n", mf);

	return (0);
}   
