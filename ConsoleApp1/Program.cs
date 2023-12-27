// See https://aka.ms/new-console-template for more information
namespace ConsApp1
{
    using System.Threading.Tasks;
    public class Program
    {
        static Int32[] MergeSort(Int32[] array)
        {
            if (array.Length == 1)
            {
                return array;
            }

            Int32 middle = array.Length / 2;
            int[] ar1=null, ar2=null;
            Task t1 = Task.Run(() =>
            {
                ar1 = MergeSort(array.Take(middle).ToArray());
            });
            Task t2 = Task.Run(() => {
                ar2 = MergeSort(array.Skip(middle).ToArray());
            });
            Task.Run(async delegate {
                await t1;
                await t2;   
            }).Wait();
            return Merge(ar1, ar2);
        }

        static Int32[] Merge(Int32[] arr1, Int32[] arr2)
        {
            Int32 ptr1 = 0, ptr2 = 0;
            Int32[] merged = new Int32[arr1.Length + arr2.Length];

            for (Int32 i = 0; i < merged.Length; ++i)
            {
                if (ptr1 < arr1.Length && ptr2 < arr2.Length)
                {
                    merged[i] = arr1[ptr1] > arr2[ptr2] ? arr2[ptr2++] : arr1[ptr1++];
                }
                else
                {
                    merged[i] = ptr2 < arr2.Length ? arr2[ptr2++] : arr1[ptr1++];
                }
            }

            return merged;
        }

        static void Main(string[] args)
        {
            Int32[] arr = new Int32[1000];

            //заполняем массив случайными числами
            Random rd = new Random();
            for (Int32 i = 0; i < arr.Length; ++i)
            {
                arr[i] = rd.Next(-101, 101);
            }

            System.Console.WriteLine("The array before sorting:");
            foreach (Int32 x in arr)
                System.Console.Write(x + " ");

            //сортировка
            arr = MergeSort(arr);

            System.Console.WriteLine("\n\nThe array after sorting:");
            foreach (Int32 x in arr)
                System.Console.Write(x + " ");

            System.Console.WriteLine("\n\nPress the <Enter> key");
            System.Console.ReadLine();
        }
    }
}
