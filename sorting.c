/*
 * File:  sorting.c
 * Author:  Gonçalo Nunes (99074)
 * Description: Sorting algorithms and auxiliary functions.
*/


#include "auxiliary.h"


/* Compares two strings and returns TRUE if the first string is alphabeticaly 
 * lower than the second one. Returns FALSE otherwise.
*/
int less(char *s1, char *s2) {
    if (strcmp(s1, s2) < 0)
        return TRUE;
    else
        return FALSE;
}


/* Swaps strings by swapping pointers. */ 
void exch(char **s1_ptr, char **s2_ptr)
{
  char *temp = *s1_ptr;
  *s1_ptr = *s2_ptr;
  *s2_ptr = temp;
}  


/* Implementation of insertion sort to sort the given array. */
void insertion_sort(char **str, int l, int r) {
    int i, j;
    char v[BUF_SIZE] = {0};

    for (i = l+1; i <= r; i++) {
        strcpy(v, str[i]);
        j = i-1;
        while(j >= l && less(v, str[j])) {
            str[j+1] = realloc(str[j+1], (strlen(str[j]) + 1) * sizeof(char));
            strcpy(str[j+1], str[j]); 
            j--;
        }
        str[j+1] = realloc(str[j+1], (strlen(v) + 1) * sizeof(char));
        strcpy(str[j+1], v);
    }
}


/* Partition function of the quick sort algorithm. */
int partition(char **string, int l, int r) {
    int i = l-1;
    int j = r;
    char v[BUF_SIZE] = {0};
    strcpy(v, string[r]);

    while (i < j) {
        while (less(string[++i], v));
        while (less(v, string[--j]))
            if (j == l)
                break;
        if (i < j)
            exch(&string[i], &string[j]);
    }
    exch(&string[i], &string[r]);
    return i;
}


/* Implementation of quick sort algorithm to sort 
 * the given array of strings by alphabetical order.
*/
void quick_sort(char **string, int l, int r) {
    int i;

    if (r-l <= 4) {
        insertion_sort(string, l, r);
        return;
    }
    
    i = partition(string, l, r);
    quick_sort(string, l, i-1);
    quick_sort(string, i+1, r);
}