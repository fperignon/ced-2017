#include <stdio.h>
#include <stdlib.h>

/* 
    1. constructs an array of 10 integers
    2. sorts the array in ascending or descending order (this example sorts 
       the array in ascending order)
    3. calculates the average value of the 10 elements in the array
       computes the frequency of occurrence of each different integer 
       value in the array
    4. checks the results of the frequency computation by calculating the 
       sum of the individual frequencies (which must add up to 1.0)     */

int i, j, indx;
int sflag;
int sum;

void populateArray(int nelem_in_array, int *intArray);
void sortArray(int nelem_in_array, int *array, int *fcn(int sortFlag, int *n, int *m));
void exchange(int *elem1, int *elem2);
int ascending(int sortFlag, int *n, int *m);
int descending(int sortFlag, int *n, int *m);
float getAverage(int nelem_in_array, int *array);
float *computeFreq(int nelem_in_array, int *array, float *freq);
float *fqsum(int nelem_in_array, float *freq);

int main(void)
{
  const int nelem = 10;

  int *array;
  float *freq;
  float *pfsum = 0;

  array = (int *)malloc(nelem*sizeof(int));
  freq = (float *)malloc(nelem*sizeof(float));

/*  Initialize the arrays  */
  for (indx = 0; indx < nelem; indx++)
  {
    array[indx] = 0;
    freq[indx] = 0.0;
  }

/* Replace initial values of array elements  */
  populateArray(nelem, array);

/* Print the elements of the unsorted array  */
  printf("The sequence of elements in the unsorted array are: [ ");

  for (indx = 0; indx < nelem; indx++)
  { 
    printf("%d ", array[indx]);
  }
  printf("]\n\n");

/* Sort the array of integers  */
  sortArray(nelem, array, ascending);





/* Print the elements of the sorted array  */
  printf("The sequence of elements in the sorted array are: [ ");
  for (indx = 0; indx < nelem; indx++)
  {
    printf("%d ", array[indx]);
  }
  printf("]\n\n");

/*  Compute average value of elements in array  */
  getAverage(nelem, array);

/*  Print average */
  printf("The average value of the array elements is: %f\n\n ", getAverage(nelem, array));

/* Compute the frequency of each element in the array  */
  computeFreq(nelem, array, freq); 

/* Print frequencies */
  printf("The frequencies of the elements in the sorted array are: [ ");
  for (indx = 0; indx < nelem; indx++)
  {
    printf("%f ", freq[indx]);
  }
  printf("]\n\n");

/* Compute the sum of the frequencies of the array elements  */
  *pfsum = *fqsum(nelem, freq);

/* Print the sum of the frequencies of the array elements  */
  printf("The sum of the element frequencies is: %f\n\n", *pfsum);

  free(array);
  free(freq);

  return 0;
}



void populateArray(const int nelem_in_array, int *intArray)
{
  for (j = 0; j < nelem_in_array; j++)
  {
    if ((j % 2) == 0)
    {
      *intArray = (2*j + 1);
    }
    else
    {
      *intArray = (j - 1);
    }
 
  intArray += 1;
  }  
}  

void sortArray(const int nelem_in_array, int *array, int *order(int, int *, int *))
{
  for (i = 0; i < nelem_in_array; i++)
  {
    for (indx = 0; indx < (nelem_in_array - 1); indx++)
    {
      sflag = 0;

      if (!*order(sflag, (array + indx) , (array + (indx + 1))))
      {
        exchange((array + indx), (array + (indx + 1)));
      }
    }
  }
}      

void exchange(int *elem1, int *elem2)
{
  int *tmp;

  tmp = elem1;
  *elem1 = *elem2;
  elem2 = tmp;
}

int ascending(int sflag, int *n, int *m)
{
  sflag = 0;

  if (m > n)
  {
   sflag = 1;
  }
  return sflag;
}

int decending(int sflag, int *n, int *m)
{
  sflag = 0;

  if (n > m)
  {
    sflag = 1;
  }
  return sflag;
}

float getAverage(int nelem_in_array, int *array) 
{
  sum = 0;

  for (indx = 0; indx < nelem_in_array; indx++)
  {
    sum += *(array + indx);
  }
  return (float)sum/nelem_in_array;
}

float *computeFreq(int nelem_in_array, int *array, float *freq)  
{
  int k = 0;
  float *p, *numfreq;
  numfreq = (float *)malloc(nelem_in_array*sizeof(float)); 

  *numfreq = 1.0;  

  for (indx = 0; indx < (nelem_in_array - 1); indx++)
  {
    *(freq + k) += (float)(*(numfreq + k))/nelem_in_array;

    if (*(array + (indx + 1)) == *(array + indx))
    {
      *(numfreq + k) += 1;
    }
    else
    {
      k++;
      *(numfreq + k) = 1;
    }
  }
    
  return freq;
}

float *fqsum(int nelem_in_array, float *freq)
{
  float *fsum = (float *)malloc(sizeof(float));
  *fsum = 0.0;

  for (indx = 0; indx < nelem_in_array; indx++)
  {
    *fsum += freq[indx];
  }

  return fsum;
}
