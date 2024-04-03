#include <iostream>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;
uint32_t getrand ( uint32_t min, uint32_t max)
{
    return (double) rand()/ (RAND_MAX+1.0)*(max-min)+min;
}

int findMax(uint32_t arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) 
        if (arr[i] > max) 
            max = arr[i];
    return max;
}
void inputarray(int n, uint32_t array[])
{
    for (int i = 0; i<n ; i++)
        array [i] = getrand(1,100);
    
}

void outputarray(int n, uint32_t array[])
{
    for (int i = 0; i<n ; i++)
        cout << array[i] << endl;

}

void Swap (uint32_t *leftValue, uint32_t *rightValue)
{
    int temp = *leftValue;
    *leftValue = *rightValue;
    *rightValue = temp;
}
int GetPivotInd(uint32_t array[], int minInd, int maxInd)
{
    uint32_t pivot = array[maxInd];
    int i = minInd;
    for(int j = minInd; j <= maxInd - 1; j++ )
    {
        if ( array[j] < pivot)
        {
            Swap(&array[i], &array[j]);
            i++;
        }
    }
    Swap(&array[i], &array[maxInd]);
    return i;
}

void quicksort(uint32_t array[], int minInd, int maxInd)
{
    if (minInd < maxInd)
    {
        int pivot = GetPivotInd(array, minInd, maxInd);
        quicksort(array, minInd, pivot - 1);
        quicksort(array, pivot + 1, maxInd);
    }
}
void selectionSort(uint32_t array[], int n)
{
    int i, j, minInd, temp;
    for (i = 0; i < n - 1; i++)
    {
        minInd = i;
        for (j = i + 1; j < n; j++)
        {
            if (array[j] < array[minInd])
                minInd = j;
        }
        temp = array[i];
        array[i] = array[minInd];
        array[minInd] = temp;
    }
}
void radixSort(uint32_t array[], int n)
{
    int max = findMax(array, n);
    for (int exp = 1; max/exp > 0; exp *= 10)
    {
        int output[n];
        int count[10] = {0};
        for (int i = 0; i < n; i++) 
            count[(array[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) 
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            output[count[(array[i] / exp) % 10] - 1] = array[i];
            count[(array[i] / exp) % 10]--;
        }
        for (int i = 0; i < n; i++) 
            array[i] = output[i];
    }
}

int main()
{
    clock_t start = clock();
    srand(time(NULL));
    for (int n = 50000; n <=1000000; n+=50000)
    {
        uint32_t *array = new uint32_t[n];
        inputarray(n, array);
        //cout << "--nonsort--" << endl;
        //outputarray(n, array);
        quicksort(array, 0, n - 1);
        //cout << "--sort--" << endl;
        //outputarray(n, array);
        cout << "quicksort" << " ("<< n << ")" << endl;
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "time  " << seconds <<  " sec" << endl;
        cout << "\n" << endl;
        //cout << "****NEXT****" << endl;
    }

    for (int n = 50000; n <=1000000; n+=50000)
    {
        uint32_t *array = new uint32_t[n];
        inputarray(n, array);
        //cout << "--nonsort--" << endl;
        //outputarray(n, array);
        selectionSort(array, n - 1);
        //cout << "--sort--" << endl;
        //outputarray(n, array);
        cout << "seletcionsort" << " ("<< n << ")" << endl;
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "time  " << seconds <<  " sec" << endl;
        cout << "\n" << endl;
        //cout << "****NEXT****" << endl;
    }
    for (int n = 50000; n <=1000000; n+=50000)
    {
        uint32_t *array = new uint32_t[n];
        inputarray(n, array);
        //cout << "--nonsort--" << endl;
        //outputarray(n, array);
        radixSort(array, n);
        //cout << "--sort--" << endl;
        //outputarray(n, array);
        cout << "radixsort" << " ("<< n << ")" << endl;
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "time  " << seconds <<  " sec" << endl;
        cout << "\n" << endl;
        //cout << "****NEXT****" << endl;
    }
}
