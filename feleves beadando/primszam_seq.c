#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

bool primszam_e(int num)
{
	int count = 0;
	for (int i = 2; i <= (double)(num / 2); i++)
	{
		if (num % i == 0)
		{
			count++;
		}
	}
	if (count != 0)
	{
		//printf("%d nem primszam\n", num);
		return false;
	}
	else
	{
		//printf("%d primszam\n", num);
		return true;
	}
}

int main(int argc, char *argv[])
{
	int stop_values[] = {10000,50000,100000,200000,350000};
	int stop_values_length = sizeof(stop_values) / sizeof(stop_values[0]);
	double meresek[stop_values_length];
	printf("Primek szekvencialis keresese\n");

	for (int i = 0; i < stop_values_length; i++)
	{
		int a = 2;
		start = clock();
		do
		{
			primszam_e(a);
			a++;
		} while (a < stop_values[i]);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		meresek[i] = cpu_time_used;
	}

	FILE * fp;

   	fp = fopen("seq_meres.csv", "w+");
	for (int i = 0; i < stop_values_length; i++)
	{
		fprintf(fp, "%d,%lf\n",  stop_values[i], meresek[i]);
	}

   	fclose(fp);
	printf("Meres veget ert, eredmeny seq_meres.csv fajlban.\n");
	return 0;
}
