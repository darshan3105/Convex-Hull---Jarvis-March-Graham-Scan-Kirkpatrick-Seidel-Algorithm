#ifndef UTILS_H
#define UTILS_H

#include<iostream>
#include<climits>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include "classes/List.h"
#include "classes/Point.h"

using namespace std;

float findMedian(double arr[], int n)
{
	sort(arr, arr+n); // Sort the array
	return arr[n/2]; // Return middle element
}

void swap(double *a, double *b)
{
	double temp = *a;
	*a = *b;
	*b = temp;
}

int partition(double arr[], int l, int r, double x)
{
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i=l; i<r; i++)
		if (arr[i] == x)
		break;
	swap(&arr[i], &arr[r]);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}

float kthSmallest(double arr[], int l, int r, int k)
{
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		int n = r-l+1; // Number of elements in arr[l..r]

		// Divide arr[] in groups of size 5, calculate median
		// of every group and store it in median[] array.
		int i;
    double median[(n+4)/5]; // There will be floor((n+4)/5) groups;
		for (i=0; i<n/5; i++)
			median[i] = findMedian(arr+l+i*5, 5);
		if (i*5 < n) //For last group with less than 5 elements
		{
			median[i] = findMedian(arr+l+i*5, n%5);
			i++;
		}

		// Find median of all medians using recursive call.
		// If median[] has only one element, then no need
		// of recursive call
		double medOfMed = (i == 1)? median[i-1]:
								kthSmallest(median, 0, i-1, i/2);

		// Partition the array around a random element and
		// get position of pivot element in sorted array
		int pos = partition(arr, l, r, medOfMed);

		// If position is same as k
		if (pos-l == k-1)
			return arr[pos];
		if (pos-l > k-1) // If position is more, recur for left
			return kthSmallest(arr, l, pos-1, k);

		// Else recur for right subarray
		return kthSmallest(arr, pos+1, r, k-pos+l-1);
	}

	// If k is more than number of elements in array
	return INT_MAX;
}

void make_result(List<Point> list,string addr){

    fstream file;
    ostringstream str1;
    file.open(addr,ios::out);
    for(int i=0;i<list.size();i++){
      Point p = list.get(i);
      file <<p.get_X()<<","<<p.get_Y()<<"\n";
    }
    file.close();
}

List<Point> make_list(string addr){

    List<Point> list;

    fstream file;
    file.open(addr);
    string line;
    while(getline(file,line,'\n')){
      istringstream templine(line);
      string data;
      int i=0;
      double a[2];
      while(getline(templine,data,',')){
          a[i] = stof(data);
          i++;
      }
      Point p(a[0],a[1]);
      list.add(p);

    }
    file.close();
    return list;
}

#endif
