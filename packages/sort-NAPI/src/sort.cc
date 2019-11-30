#include <stdio.h>

void swap(unsigned int *a, unsigned int *b)
{
  unsigned int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(unsigned int *array, unsigned int length)
{
  unsigned int i, j;
  for (i = 0; i < (length - 1); ++i)
  {
    for (j = 0; j < length - 1 - i; ++j)
    {
      if (*(array + j) > *(array + j + 1))
      {
        swap(array + j, array + j + 1);
      }
    }
  }
}

void quickSort(unsigned int *array, unsigned int length)
{
  unsigned int partition;
  unsigned int i, j;
  unsigned int rightLength, leftLength;
  unsigned int *rightArray, *leftArray;

  if (length < 2)
  {
    return;
  }
  partition = *(array);
  i = 1;

  for (j = 1; j <= length; j++)
  {
    if (*(array + j) < partition)
    {
      swap(array + i, array + j);
      i++;
    }
  }
  swap(array, array + i - 1);

  leftLength = i - 1;
  leftArray = array;
  rightArray = array + i;
  rightLength = length - i;

  quickSort(rightArray, rightLength);
  quickSort(leftArray, leftLength);
}
