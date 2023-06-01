using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;

class Program
{
    static Stopwatch stopwatch = new Stopwatch();

    static bool IsPrime(int n)
    {
        bool is_prime = true;
        bool kilepes = false;

        if (n == 2 || n == 3)
        {
            kilepes = true;
            is_prime = true;
        }

        if ((n <= 1 && !kilepes) || (n % 2 == 0 && !kilepes) || (n % 3 == 0 && !kilepes))
        {
            kilepes = true;
            is_prime = false;
        }

        if (!kilepes)
        {
            for (int i = 5; i <= Math.Sqrt(n); i += 6)
            {
                if (((n % i == 0) && !kilepes) || ((n % (i + 2) == 0) && !kilepes))
                {
                    is_prime = false;
                    kilepes = true;
                }
            }
        }

        if (!kilepes)
        {
            is_prime = true;
        }

        return is_prime;
    }

    static void Main(string[] args)
    {
        int[] stopValues = { 10000, 50000, 100000, 200000, 350000, 1000000, 4000000, 10000000, 20000000 };
        int stopValuesLength = stopValues.Length;
        double[] measurements = new double[stopValuesLength];
        int[] szalak = { 2, 3, 4, 10 };
        int szalakLength = szalak.Length;

        Console.WriteLine("Primek keresése párhuzamosan");

        using (StreamWriter file = new StreamWriter("csharp_parhuzamositott_meres.csv"))
        {
            for (int j = 0; j < szalakLength; j++)
            {
                int szalakSzama = szalak[j];

                for (int i = 0; i < stopValuesLength; i++)
                {
                    int stopValue = stopValues[i];
                    double measurement = 0;

                    stopwatch.Start();

                    Parallel.For(0, stopValue, new ParallelOptions { MaxDegreeOfParallelism = szalakSzama }, a =>
                    {
                        IsPrime(a);
                    });

                    stopwatch.Stop();

                    measurement = stopwatch.Elapsed.TotalSeconds;
                    measurements[i] = measurement;
                    stopwatch.Reset();

                    file.WriteLine("" + stopValues[i] +","+ szalakSzama +","+ measurements[i]+"");
                }
            }
        }

        Console.WriteLine("Mérés befejeződött, az eredmények az csharp_parhuzamositott_meres.csv fájlban találhatók.");
    }
}
