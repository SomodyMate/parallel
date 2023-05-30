using System;
using System.Diagnostics;
using System.IO;

class Program
{
    static Stopwatch stopwatch = new Stopwatch();

    static bool IsPrime(int num)
    {
        int count = 0;
        for (int i = 2; i <= (double)(num / 2); i++)
        {
            if (num % i == 0)
            {
                count++;
            }
        }
        return count == 0;
    }

    static void Main(string[] args)
    {
        int[] stopValues = { 10000, 50000, 100000, 200000, 350000 };
        int stopValuesLength = stopValues.Length;
        double[] measurements = new double[stopValuesLength];

        Console.WriteLine("Primek szekvencialis keresese");

        for (int i = 0; i < stopValuesLength; i++)
        {
            int a = 2;
            stopwatch.Start();
            do
            {
                IsPrime(a);
                a++;
            } while (a < stopValues[i]);
            stopwatch.Stop();
            double cpuTimeUsed = stopwatch.Elapsed.TotalSeconds;
            measurements[i] = cpuTimeUsed;
        }

        using (StreamWriter file = new StreamWriter("csharp_meres.csv"))
        {
            for (int i = 0; i < stopValuesLength; i++)
            {
                file.WriteLine("" + stopValues[i] +","+ measurements[i] + "");
            }
        }

        Console.WriteLine("Meres veget ert, eredmeny csharp_meres.csv fajlban.");
    }
}
