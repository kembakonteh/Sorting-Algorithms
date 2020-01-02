
/* This program is designed to give an instinctive understanding of how different sorting algorithms perform at load.
   Introduce the idea of monitoring what the  program is doing, also gives practice in various sorting algorithms. The program
   prints out the given stats, and gives the number of times each sort method has been accessed from the data.
*/
#include <cstdio>
#include <stdexcept>
#include <string>
#include "ArrayList.h"
#include <iostream>
#include <fstream>
#include <vector>

/* Insertion sort method */
template<class TYPE>
void insertionSort(ArrayList<TYPE> &theItemArray, int arrayLength);

/* Quick sort method */
template<class TYPE>
void quickSort(ArrayList<TYPE> &items, int startIndex, int HighestIndex);

/* partition */
template<class TYPE>
int partition(ArrayList<TYPE> &items, int low, int High);

/* Merge sort method */
template<class TYPE>
void merge(ArrayList<TYPE> &theItemArray, int, int, int);

/* Method merges the sorted arrays */
template<class TYPE>
void mergeSort(ArrayList<TYPE> &items, int lowIndex, int highIndex);

/* Method prints out needed method or data */
template<class TYPE>
void printArray(ArrayList<TYPE> &items);


/* Main to execute the program. The file is being read here and other important info printed out as per instructions */
int main(int argc, char *argv[])
{
    ArrayList<int> OriginalArray;
    int number;
    ifstream file;
    string filename=argv[argc-1];
    file.open(filename);
    while (file >> number ) {
        OriginalArray.append(number);
    }
    file.close();

    // Create copies of the given arrayList
    ArrayList<int> InsertionTest(OriginalArray);
    ArrayList<int> Merge_sort(OriginalArray);
    ArrayList<int> Quick_Sort(OriginalArray);

    OriginalArray.clearStatistics();

    // create a vector "storeStats" to help store the data
    vector<int> storeStats;

    insertionSort(InsertionTest, InsertionTest.getSize());

    // storing the first value into storeStat using vector function push_back
    storeStats.push_back(InsertionTest.getNumAccess());
    storeStats.push_back(InsertionTest.getNumSwap());
    storeStats.push_back(InsertionTest.getNumRemove());
    storeStats.push_back(InsertionTest.getNumInsertAt());
    storeStats.push_back(InsertionTest.getNumAppends());

    // clears stats
    InsertionTest.clearStatistics();

    //sort the merge sort method
    mergeSort(Merge_sort, 0, Merge_sort.getSize() - 1);

    //storing the data of the stat in storeStat using vector function push_back
    storeStats.push_back(Merge_sort.getNumAccess());
    storeStats.push_back(Merge_sort.getNumSwap());
    storeStats.push_back(Merge_sort.getNumRemove());
    storeStats.push_back(Merge_sort.getNumInsertAt());
    storeStats.push_back(Merge_sort.getNumAppends());

    // clears the starts
    InsertionTest.clearStatistics();

    //sort the quickSort
    quickSort(Quick_Sort, 0, Quick_Sort.getSize() - 1);

    //storing  the data into storeStat using vector function push_back
    storeStats.push_back(Quick_Sort.getNumAccess());
    storeStats.push_back(Quick_Sort.getNumSwap());
    storeStats.push_back(Quick_Sort.getNumRemove());
    storeStats.push_back(Quick_Sort.getNumInsertAt());
    storeStats.push_back(Quick_Sort.getNumAppends());

    //clears stat the stat
    InsertionTest.clearStatistics();

    // Using command line -d, data is displayed as per assignment instruction with required info shown.
    if (argc == 3 && string(argv[1]) == "-d") {
        printf("\n%s %s", "Filename: ", string(argv[2]).c_str());
        printf("\n%s %d", "Number of Items: ", OriginalArray.getSize());


        //prints the array before it is sorted
        printf("\n%s", "Original ArrayList: \n");
        printArray(OriginalArray);


        //prints the array after it is sorted for each sort method
        printf("\n%s", "After Sorting Methods called:");
        printf("\n%s", "MergeSortResults: \n");
        printArray(Merge_sort);
        printf("\n%s", "InsertionSortResults: \n");
        printArray(InsertionTest);
        printf("\n%s", "QuickSortResult: \n");
        printArray(Quick_Sort);
        printf("\n%s %10s  %10s %10s %10s %10s ", "Number Of: ", "Access", "Swap", "Remove", "InsertAt", "Append");


        //prints the InsertSort stat
        printf("\n%s %8d %10d %10d %10d %10d", "InsertionSort", storeStats[0], storeStats[1],
               storeStats[2], storeStats[3], storeStats[4]);



        //prints the merge sort start
        printf("\n%s %11d %10d %10d %10d %10d", "MergerSort", storeStats[5], storeStats[6],
               storeStats[7], storeStats[8], storeStats[9]);



        //prints the Quick sort stat
        printf("\n%s %12d %10d %10d %10d %10d", "QuickSort", storeStats[10], storeStats[11],
               storeStats[12], storeStats[13], storeStats[14]);
    }
    else if (argc == 2 ) {

        printf("\n%s %s", "Filename: ", string(argv[1]).c_str());
        printf("\n%s %d", "Number of Items: ", OriginalArray.getSize());
        printf("\n%s %10s  %10s %10s %10s %10s ", "Number Of: ", "Access", "Swap", "Remove", "InsertAt", "Append");


        //prints the InsertSort stat
        printf("\n%s %8d %10d %10d %10d %10d", "InsertionSort", storeStats[0], storeStats[1],
               storeStats[2], storeStats[3], storeStats[4]);


        //Prints the merge sort stat
        printf("\n%s %11d %10d %10d %10d %10d", "MergerSort", storeStats[5], storeStats[6],
               storeStats[7], storeStats[8], storeStats[9]);


        //prints the Quick sort stat
        printf("\n%s %12d %10d %10d %10d %10d", "QuickSort", storeStats[10], storeStats[11],
               storeStats[12], storeStats[13], storeStats[14]);
        cout << endl;
    }
    else {
        cout << " Please ensure that arcg is of length 2 or 3 in order to display array the  stats " << endl;
    }
    cout << endl;
    return 0;
}


/* This is the insertion sort method. The order of time is O(n^2) which means that
 it is a bit faster sorting than bubble and selection. */
template<class TYPE>
void insertionSort(ArrayList<TYPE> &arr, int length) {
    int i, j, tmp;
    for (i = 1; i < arr.getSize(); i++) {
        j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            arr.swap(j, j-1);
            j--;
        }
    }
}


/* This is the merge sort helper method. It splits and sorts it using
 divide and conquer strategy
  */
template <class TYPE>
void merge(ArrayList<TYPE> &items, int low, int mid, int high) {
    int l = mid - low + 1;
    int r = high - mid;


    //creates copies
    ArrayList<int> first_Array(l);
    ArrayList<int> second_Array(r);
    int i;
    int j;
    int k;

    for(i = 0; i<l; i++)
        first_Array.append(items[low + i]);
    for(j = 0; j<r; j++)
        second_Array.append(items[mid + 1 + j]);
    i = 0; j = 0; k = low;



    while(i < l && j<r) {
        if(first_Array[i] <= second_Array[j]) {
            items[k] = first_Array[i];
            i++;
        }else{
            items[k] = second_Array[j];
            j++;
        }
        k++;
    }
    while(i < l) {
        items[k] = first_Array[i];
        i++; k++;
    }
    while(j < r) {
        items[k] = second_Array[j];
        j++; k++;
    }
}

/* This is the mergeSort method and it will do the sorting.
 It also makes use of the  helper method.
 */
template <class TYPE>
void mergeSort(ArrayList<TYPE> &items, int l, int r) {
    int m;
    if(l < r) {
        int m = l+(r-l)/2;
        // Sort first and second item arrays
        mergeSort(items, l, m);
        mergeSort(items, m+1, r);
        merge(items, l, m, r);
    }
}


/* This is the quick sort method. */
template<class TYPE>
void quickSort(ArrayList<TYPE> &items, int startIndex, int HighestIndex) {
    int mid;
    if (startIndex < HighestIndex) {
        mid = partition(items, startIndex, HighestIndex);
        quickSort(items, startIndex, mid);
        quickSort(items, mid + 1, HighestIndex);
    }
}


/* Method uses the last element as pivot. It makes use of a do while loop. It places the pivot element at its correct position in sorted
   array and places all smaller elements (smaller than pivot) to left of the pivot and all greater elements to right of the  pivot
   */
template<class TYPE>
int partition(ArrayList<TYPE> &items, int startIndex, int highestIndex) {
    int pivot = items[startIndex];
    int lowStartIndex = startIndex - 1;
    int arrayLength = highestIndex + 1;
    do {
        do {
            arrayLength--;
        } while (pivot < items[arrayLength]);
        do {
            lowStartIndex++;
        } while (pivot > items[lowStartIndex]);
        if (lowStartIndex < arrayLength) {
            items.swap(lowStartIndex, arrayLength);
        }
    } while (lowStartIndex < arrayLength);
    return arrayLength;
}



/* Method prints out data */
template<class TYPE>
void printArray(ArrayList<TYPE> &items) {
    cout << "[";
    for (int i = 0; i < items.getSize(); i++) {
        cout << items[i] << ",";
    }
    cout << "]"<<endl;
}
