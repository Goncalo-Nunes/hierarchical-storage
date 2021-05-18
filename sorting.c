#include "auxiliary.h"


/* Compares two Tasks and returns True if the first Task's start_time is lower then the other
or in case they are equal, returns True if the first Task description is first in alphabetical order then the second.
Returns False in any other case. */
int less(char *s1, char *s2) {
    if (strcmp(s1, s2) < 0)
        return TRUE;
    else
        return FALSE;
}


/* Swaps strings by swapping pointers */ 
void exch(char **s1_ptr, char **s2_ptr)
{
  char *temp = *s1_ptr;
  *s1_ptr = *s2_ptr;
  *s2_ptr = temp;
}  


/* Implementation of insertion sort to sort the given array */
void insertion_sort(char **string, int l, int r) {
    int i, j;
    char v[BUF_SIZE];

    for (i = l+1; i <= r; i++) {
        strcpy(v, string[i]);
        j = i-1;
        while(j >= l && less(v, string[j])) {
            strcpy(string[j+1], string[j]);
            j--;
        }
        strcpy(string[j+1], v);
    }
}


/* Partition function of the quick sort algorithm. */
int partition(char **string, int l, int r) {
    int i = l-1;
    int j = r;
    int mid = l+(r-l)/2;
    char v[BUF_SIZE];

    if (less(string[mid], string[l])) exch(&string[mid], &string[l]);
    if (less(string[mid], string[r])) exch(&string[mid], &string[r]); /* string[mid] is higher */
    if (less(string[r], string[l])) exch(&string[r], &string[l]);
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
the given array of tasks by their start time as the primary criteria 
and their alphabetical order as the secondery criteria.  */
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