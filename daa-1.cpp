#include<bits/stdc++.h>
#include<iostream>
#include<climits>
using namespace std;

class Point
{
	public:
	float x,y;
	Point(float x,float y)
	{

        	this->x = x;
        	this->y = y;
    	}

    	bool operator<(const Point& p) const
    	{
    		return (this->x < p.x);
    	}
};

//list<Point>s;
//list<Point>c;
//list<pair<Point,Point>>li;
//float partition(float arr[], int l, int r, int k);

float findMedian(float arr[], int n)
{
    sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}
float partition(float arr[], int l, int r, int x)
{
    int i;
    for (i=l; i<r; i++)
	if (arr[i] == x)
	   break;
    swap(arr[i], arr[r]);
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
	if (arr[j] <= x)
	{
	    swap(arr[i], arr[j]);
	    i++;
	}
    }
    swap(arr[i], arr[r]);
    return i;
}


float kthSmallest(float arr[], int l, int r, int k)
{

    if (k > 0 && k <= r - l + 1)
    {
	int n = r-l+1;
	int i;
	float median[(n+4)/5];
	for (i=0; i<n/5; i++)
	    median[i] = findMedian(arr+l+i*5, 5);
	if (i*5 < n)
	{
	    median[i] = findMedian(arr+l+i*5, n%5);
	    i++;
	}

	float medOfMed = (i == 1)? median[i-1]:
	                         kthSmallest(median, 0, i-1, i/2);

	int pos = partition(arr, l, r, medOfMed);
	if (pos-l == k-1)
	    return arr[pos];
	if (pos-l > k-1)
	    return kthSmallest(arr, l, pos-1, k);
	return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }

    return INT_MAX;
}


list<Point> upperhull(Point pmin,Point pmax,list<Point>s)
{

	int n = s.size();
	float xarr[n];
	int k1=0;
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;
		xarr[k1++]=p.x;
	}
	if(k1==2)
	{
		return s; //to end recursion
	}
	float a = kthSmallest(xarr, 0, k1-1,k1/2);  //to get x=a line
	cout<<a<<endl;
	// pair<Point,Point> up=upper_bridge(s,a); //calling upper bridge
	// Point pl=up.first;
	// Point pr=up.second;
	// list<Point>Tleft,Tright;
	//
	// Tleft=above(pmin,pl,s);
  //   Tleft.push_back(pl);
	//
  //   Tright=above(pmax,pr,s);
  //   Tright.push_back(pr);
	// return upperhull(pl,pmin,Tleft) + upperhull(pr,pmax,Tright);
  //  // list<Point>LUH=upperhull(pl,pmin,Tleft);
  //  // list<Point>RUH=upperhull(pr,pmax,Tright);
}

int main()
{
	list<Point>s;
	s.push_back(Point(0,3));
	s.push_back(Point(1,1));
	s.push_back(Point(2,2));
	s.push_back(Point(4,4));
	s.push_back(Point(0,0));
	s.push_back(Point(1,2));
	s.push_back(Point(3,1));
	s.push_back(Point(3,3));

	float min=10000,max=-100000;
	Point pmin,pmax;
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;
		if(p.x>max)
		{
			max=p.x;
			max=p;
		}
		if(p.x<min)
		{
			min=p.x;
			min=p;
		}
	}
	list<Point>upper,lower;
	upper= upperhull(pmin,pmax,s);
	// lower=lowerhull(pmin,pmax,s);
	// for(auto it=lower.begin();it!=lower.end();it++)  //concatenating two upper and lower hulls
	// {
	// 	Point p=*it;
	// 	upper.push_back(p);
	// }

}
