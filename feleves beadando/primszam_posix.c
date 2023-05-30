#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

clock_t start, end;
double cpu_time_used;
static int start_val = 0;
static int leptetes = -1;

bool primszam_e(int n)
{

	bool is_prime = true;
	bool kilepes = false;
	if (n == 2 || n == 3)
	{
		kilepes = true;
		is_prime = true;
		//printf("%d primszam! tID: %d\n", n, pthread_self());
	}
	if ((n <= 1 && kilepes == false) || (n % 2 == 0 && kilepes == false) || (n % 3 == 0 && kilepes == false) )
	{
		kilepes = true;
		is_prime = false;
		//printf("%d nem primszam! tID: %d\n", n, pthread_self());
	}
	if(kilepes == false){	
	
	for (int i = 5; i <= (sqrt(n)); i += 6)
	{		
		if (((n % i == 0) && (kilepes == false)) || ( (n % (i + 2) == 0) && (kilepes == false) ) ) 
		{
			is_prime = false;
			kilepes = true;
			//printf("%d nem primszam! tID: %d\n", n, pthread_self());
		}
	}	
	}	
	if (kilepes == false)
	{
		//printf("%d primszam! tID: %d\n", n, pthread_self());
		is_prime = true;
	}
	
	return is_prime;
}

void* routine(void* arg1){
	int stop_val = *(int *)arg1;

	for (int a = start_val; a < stop_val; a+=leptetes)
	{
		primszam_e(a);
	}		
}


int main(int argc, char *argv[])
{
	int stop_values[] = {10000,50000,100000,200000,350000,1000000,4000000,10000000,20000000};
	int stop_values_length = sizeof(stop_values) / sizeof(stop_values[0]);
	double meresek[stop_values_length];
	int szalak[] = {2,3,4,10};
	int szalak_length = sizeof(szalak) / sizeof(szalak[0]);

	printf("Primek keresese Posix szalakkal\n");
		
	FILE * fp;	
   	fp = fopen("posix_meres.csv", "w+");
	
	for (int j = 0; j < szalak_length; j++)
	{
		pthread_t threads[ (szalak[j]) ];
		leptetes = szalak[j];
		for (int i = 0; i < stop_values_length; i++)
		{
				start = clock();
				for (int x = 0; x < szalak[j]; x++)
				{
					start_val = x + 0;
					
					int stop_val = stop_values[i];
					if( pthread_create(&threads[x], NULL, &routine, &stop_val) == 0 ){
						printf("---------thread elinditva----\n");
					}					
				}

				for (int x = 0; x < szalak[j]; x++)
				{
					if (pthread_join(threads[x], NULL) == 0)
					{
						printf("---------thread leallitva----\n");
					}
					
					
				}
				end = clock();
				cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
				meresek[i] = cpu_time_used;
				fprintf(fp, "%d,%d,%lf\n",  stop_values[i], szalak[j], meresek[i]);
						
			
		}
	}
	
   	fclose(fp);
	printf("Meres veget ert, eredmeny posix_meres.csv fajlban.\n");

	return 0;
}
