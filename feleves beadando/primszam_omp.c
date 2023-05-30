#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <omp.h>

clock_t start, end;
double cpu_time_used;

bool primszam_e(int n)
{
	bool is_prime = true;
	bool kilepes = false;
	if (n == 2 || n == 3)
	{
		kilepes = true;
		is_prime = true;
	}
	if ((n <= 1 && kilepes == false) || (n % 2 == 0 && kilepes == false) || (n % 3 == 0 && kilepes == false) )
	{
		kilepes = true;
		is_prime = false;
	}
	if(kilepes == false){	
	
	for (int i = 5; i <= (sqrt(n)); i += 6)
	{		
		if (((n % i == 0) && (kilepes == false)) || ( (n % (i + 2) == 0) && (kilepes == false) ) ) 
		{
			is_prime = false;
			kilepes = true;
		}
	}	
	}	
	if (kilepes == false)
	{
		is_prime = true;
	}
	
	return is_prime;
}

int main(int argc, char *argv[])
{
	int stop_values[] = {10000,50000,100000,200000,350000,1000000,4000000,10000000,20000000};
	int stop_values_length = sizeof(stop_values) / sizeof(stop_values[0]);
	double meresek[stop_values_length];
	int szalak[] = {2,3,4,10};
	int szalak_length = sizeof(szalak) / sizeof(szalak[0]);

	printf("Primek keresese OpenMP API-val\n");
		
	FILE * fp;	
   	fp = fopen("omp_meres.csv", "w+");
	
	for (int j = 0; j < szalak_length; j++)
	{
				
		for (int i = 0; i < stop_values_length; i++)
		{
						
			start = clock();

				#pragma omp parallel for num_threads(szalak[j])
				for (int a = 0; a < stop_values[i]; a++)
				{
					primszam_e(a);
				}			
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			meresek[i] = cpu_time_used;
			fprintf(fp, "%d,%d,%lf\n",  stop_values[i], szalak[j], meresek[i]);
		}
	}
	
   	fclose(fp);
	printf("Meres veget ert, eredmeny omp_meres.csv fajlban.\n");

	return 0;
}
