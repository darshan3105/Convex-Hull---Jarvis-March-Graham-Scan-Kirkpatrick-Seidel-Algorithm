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
float partition(float arr[], int l, int r, int k); 
  
	float findMedian(float arr[], int n) 
	{ 
	    sort(arr, arr+n);  // Sort the array 
	    return arr[n/2];   // Return middle element 
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
  
	/*
	void swap(float *a, float *b) 
	{ 
	    float temp = *a; 
	    *a = *b; 
	    *b = temp; 
	} 
  	*/

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
	
	//UPPER BRIDGE STARTS HERE
	
pair<Point,Point> upper_bridge(list<Point>s,float a)
{
	if(sizeof(s)==2)
	{
		auto it=s.begin();
		Point p=*it;
		it++;
		Point q=*it;
		return make_pair(p,q);
	}
	list<pair<Point,Point>>li;
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p = *it;
		if((it++)!=s.end())
		{
			Point q = *(it);
			pair<Point,Point>pq = make_pair(p,q);
			li.push_back(pq);
		}
	}
	for(auto it=li.begin();it!=li.end();it++)
	{
		pair<Point,Point>p= *it;
		cout<<p.first.x<<endl;
	}
	int n = sizeof(li);
	auto it = s.begin();
	int i=0;
	int c1=0;
	// list<Point>c;
	if(n%2==1)
	{
		Point p =*it;
		c.push_back(p);
		it=c.begin();
		for(i=0;i<n-1;i++)
		{
			it++;
		}
		//p = *it;
		//cout<<p.x<<endl;
	}
	
	vector<float> slopes;
	int c1=0;
	map<pair<Point,Point>, float>mp;
	for(auto it=li.begin();it!=li.end();it++)
	{
		pair<Point,Point>p=*it;
		Point p1 = p.first;
		Point p2 = p.second;
		if(p1.x==p2.x)
		{
			if(p1.y >p2.y)
			{
				c.push_back(p1);
			}
			else
			{
				c.push_back(p2);
			}
		}
		else
		{
			int s = (p1.y-p2.y)/(p1.x-p2.x);
			slopes.push_back(s);
			c1++;
			pair<Point,Point>p=make_pair(p1,p2);
			mp[p]=s;
			
		}
		
	}
	float arr[c1];
	/*for(int i=0;i<c1;i++)
	{
		arr[i]= slopes[i];
		cout<<"slopes"<<arr[i]<<endl;
	}*/
	for(auto it = mp.begin();it!=mp.end();it++)
	{
		pair<Point,Point>p1= it->first;
		Point p = p1.first;
		Point q = p1.second;
	}
	int n = sizeof(slopes);
	
	float k = kthSmallest(arr, 0, c1-1,c1/2);
	cout<<k<<endl;
	
	list<pair<Point,Point>>small;
	list<pair<Point,Point>>equal;
	list<pair<Point,Point>>large;
	
	for(auto it=mp.begin();it!=mp.end();it++)
	{
		if(it->second < k)
		{
			pair<Point,Point>sm=it->first;
			small.push_back(sm);
		}
		else if(it->second == k)
		{
			pair<Point,Point>eq=it->first;
			equal.push_back(eq);
		}
		else
		{
			pair<Point,Point>lg = it->first;
			large.push_back(lg);
		}
	}
	//finding max intercept
	
	float max=0;
	list<Point>maxm; // to store all point with max intercept
	
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;
		
		float cept= p.y- k*(p.x);
		if(cept>max)
		{
			max=cept;
		}	
	}
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;
		
		float cept= p.y- k*(p.x);
		if(cept==max)
		{
			maxm.push_back(p);
		}
	}
	float min=100000.0;
	Point pk(-1,-1),pm(-1,-1);
	 max=0.0;
	for(auto it=maxm.begin();it!=maxm.end();it++)
	{
		Point p=*it;
		if(p.x<min)
		{
			min=p.x;
			pk=p;
			}
		if(p.x>max)
		{
			max=p.x;
			pm=p;
			}
		
	}
	n=sizeof(s);
	
	float xarr[n];
	int k1=0;
	
	for(auto it=s.begin();it!=s.end();it++)
	{
		
		Point p=*it;
		xarr[k1++]=p.x;
	}
	a = kthSmallest(xarr, 0, k1-1,k1/2); //to get x=a line
	cout<<"medan of x:"<<a<<endl;
	
	if(pk.x <=a && pm.x>a) //when pk is on left and pm is on right side of line
	{
		pair<Point,Point>p= make_pair(pk,pm);
		return p;
	}
	
	else if(pk.x >a)
	{
		for(auto it=small.begin();it!=small.end();it++)
		{
		
			pair<Point,Point> p=*it;
			c.push_back(p.first);
		}
		for(auto it=equal.begin();it!=equal.end();it++)
		{
		
			pair<Point,Point> p=*it;
			c.push_back(p.first);
		}
		for(auto it=large.begin();it!=large.end();it++)
		{
		
			pair<Point,Point> p =*it;
			c.push_back(p.first);
			c.push_back(p.second);
		}
		
		
	}
	else
	{
		for(auto it=small.begin();it!=small.end();it++)
		{
		
			pair<Point,Point> p=*it;
			c.push_back(p.first);
			c.push_back(p.second);
		}
		for(auto it=equal.begin();it!=equal.end();it++)
		{
		
			pair<Point,Point> p=*it;
			c.push_back(p.second);
		}
		for(auto it=large.begin();it!=large.end();it++)
		{
		
			pair<Point,Point> p =*it;
			c.push_back(p.second);
		}
	}
	
	return upper_bridge(c,a);
}

//LOWER BRIDGE STARTS HERE

pair<Point,Point> lower_bridge(list<Point>s,float a)
{
	if(sizeof(s)==2)
	{
		auto it=s.begin();
		Point p=*it;
		it++;
		Point q=*it;
		return make_pair(p,q);
	}
	list<pair<Point,Point>>li;   //for storing pair of points
	for(auto it=s.begin();it!=s.end();it++) //making pairs
	{
		Point p = *it;
		if((it++)!=s.end())
		{
			Point q = *(it);
			pair<Point,Point>pq = make_pair(p,q);
			li.push_back(pq);
		}
	}
	/*for(auto it=li.begin();it!=li.end();it++)
	{
		pair<Point,Point>p= *it;
		cout<<p.first.x<<endl;
	}*/
	int n = sizeof(li);  // n= no. of pairs
	auto it = s.begin();
	int i=0;
	int c1=0;
	// list<Point>c;
	if(n%2==1) //if there are odd number of points in S
	{
		Point p =*it;
		c.push_back(p);  //adding points in candidates
		it=c.begin();
		for(i=0;i<n-1;i++)
		{
			it++;
		}
		//p = *it;
		//cout<<p.x<<endl;
	}

	vector<float> slopes;
	int c1=0;
	map<pair<Point,Point>, float>mp;  // to store pair of points and their corresponding slope
	for(auto it=li.begin();it!=li.end();it++)
	{
		pair<Point,Point>p=*it;
		Point p1 = p.first;
		Point p2 = p.second;
		if(p1.x==p2.x)
		{
			if(p1.y <p2.y)
			{
				c.push_back(p1);
			}
			else
			{
				c.push_back(p2);
			}
		}
		else
		{
			int s = (p1.y-p2.y)/(p1.x-p2.x);
			slopes.push_back(s);
			c1++;
			pair<Point,Point>p=make_pair(p1,p2);
			mp[p]=s;

		}

	}
	float arr[c1];
	for(int i=0;i<c1;i++)
	{
		arr[i]= slopes[i];
		//cout<<"slopes"<<arr[i]<<endl;
	}

	for(auto it = mp.begin();it!=mp.end();it++)
	{
		pair<Point,Point>p1= it->first;
		Point p = p1.first;
		Point q = p1.second;
	}
	int n = sizeof(slopes);

	float k = kthSmallest(arr, 0, c1-1,c1/2);  //getting median slope
	//cout<<k<<endl;

	list<pair<Point,Point>>small;
	list<pair<Point,Point>>equal;
	list<pair<Point,Point>>large;

	for(auto it=mp.begin();it!=mp.end();it++)
	{
		if(it->second < k)
		{
			pair<Point,Point>sm=it->first;
			small.push_back(sm);
		}
		else if(it->second == k)
		{
			pair<Point,Point>eq=it->first;
			equal.push_back(eq);
		}
		else
		{
			pair<Point,Point>lg = it->first;
			large.push_back(lg);
		}
	}
	//finding min intercept

	float min=10000;
	list<Point>minm; // to store all point with min intercept

	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;

		float cept= p.y- k*(p.x);
		if(cept<min)
		{
			min=cept;
		}
	}
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;

		float cept= p.y- k*(p.x);
		if(cept==min)
		{
			minm.push_back(p);
		}
	}
	min=100000.0;
	Point pk(-1,-1),pm(-1,-1);
	float max=0.0;
	for(auto it=maxm.begin();it!=maxm.end();it++)
	{
		Point p=*it;
		if(p.x<min)
		{
			min=p.x;
			pk=p;    //point with min x coordinate
		}
		if(p.x>max)
		{
			max=p.x;  //point with maxm x coordinate
			pm=p;
		}

	}
	n=sizeof(s);

	float xarr[n];
	int k1=0;

	for(auto it=s.begin();it!=s.end();it++)
	{

		Point p=*it;
		xarr[k1++]=p.x;
	}
	a = kthSmallest(xarr, 0, k1-1,k1/2); //to get x=a line
//	cout<<"medan of x:"<<a<<endl;

	if(pk.x <=a && pm.x>a) //when pk is on left and pm is on right side of line
	{
		pair<Point,Point>p = make_pair(pk,pm);
		return p;
	}

	else if(pk.x <=a)
	{
		for(auto it=small.begin();it!=small.end();it++)
		{

			pair<Point,Point> p=*it;
			c.push_back(p.first);
		}
		for(auto it=equal.begin();it!=equal.end();it++)
		{

			pair<Point,Point> p=*it;
			c.push_back(p.first);
		}
		for(auto it=large.begin();it!=large.end();it++)
		{

			pair<Point,Point> p =*it;
			c.push_back(p.first);
			c.push_back(p.second);
		}


	}
	else
	{
		for(auto it=small.begin();it!=small.end();it++)
		{

			pair<Point,Point> p=*it;
			c.push_back(p.first);
			c.push_back(p.second);
		}
		for(auto it=equal.begin();it!=equal.end();it++)
		{

			pair<Point,Point> p=*it;
			c.push_back(p.second);
		}
		for(auto it=large.begin();it!=large.end();it++)
		{

			pair<Point,Point> p =*it;
			c.push_back(p.second);
		}
	}
	return lower_bridge(c,a);

}
//upperhull starts here

list<Point> upperhull(Point pmin,Point pmax,list<Point>s)
{

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
	a = kthSmallest(xarr, 0, k1-1,k1/2);  //to get x=a line
	pair<Point,Point> up=upper_bridge(s,a); //calling upper bridge
	Point pl=up.first;
	Point pr=up.second;
	list<Point>Tleft,Tright;

	Tleft=above(pmin,pl,s);
    Tleft.push_back(pl);

    Tright=above(pmax,pr,s);
    Tright.push_back(pr);
	return upperhull(pl,pmin,Tleft) + upperhull(pr,pmax,Tright);
   // list<Point>LUH=upperhull(pl,pmin,Tleft);
   // list<Point>RUH=upperhull(pr,pmax,Tright);
}


list<Point> above(Point p1,Point p2,list<Point>s)
{
    list<Point> abovel;
	   if(p2.x == p1.x ==0)
	        return abovel;
	   float m=p2.y-p1.y / p2.x-p1.x;
	   float c= -m*(p1.x) + p1.y;
    for(auto it=s.begin();it!=s.end();it++) {
        Point p = *it;
        if (p.y > m * p.x + c)
            abovel.push_back(p);
    }
    return abovel;
}
//lowerhull starts here

list<Point> lowerhull(Point pmin,Point pmax,list<Point>s)
{

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
	a = kthSmallest(xarr, 0, k1-1,k1/2);  //to get x=a line
	pair<Point,Point> up=lower_bridge(s,a); //calling upper bridge
	Point pl=up.first;
	Point pr=up.second;
	list<Point>Tleft,Tright;

	Tleft=below(pmin,pl,s);
	Tleft.push_back(pl);

	Tright=below(pmax,pr,s);
	Tright.push_back(pr);
 return lowerhull(pl,pmin,Tleft) + lowerhull(pr,pmax,Tright);
	//list<Point>LLH=upperhull(pl,pmin,Tleft);
	//list<Point>RLH=upperhull(pr,pmax,Tright);
}


list<Point> below(Point p1,Point p2,list<Point>s)
{
    list<Point> belowl;
    if(p2.x == p1.x ==0)
        return belowl;
    float m=p2.y-p1.y / p2.x-p1.x;
    float c= -m*(p1.x) + p1.y;
    for(auto it=s.begin();it!=s.end();it++) {
        Point p = *it;
        if (p.y < m * p.x + c)
            belowl.push_back(p);
    }
    return lowerl;
}

int main()
{
	//list<Point>s;
	s.push_back(Point(0,3));
	s.push_back(Point(1,1));
	s.push_back(Point(2,2));
	s.push_back(Point(4,4));
	s.push_back(Point(0,0));
	s.push_back(Point(1,2));
	s.push_back(Point(3,1));
	s.push_back(Point(3,3));

	s.sort();

	float min=10000,max=-100000;
	Point pmin,pmax;
	for(auto it=s.begin();it!=s.end();it++)
	{
		Point p=*it;
		if(p.x>max)
		{
			max=p.max;
			pmax=p;
		}
		if(p.x<min)
		{
			min=p.x;
			pmin=p;
		}
	}
	list<Point>upper,lower;
	upper= upperhull(pmin,pmax,s);
	lower=lowerhull(pmin,pmax,s);
	for(auto it=lower.begin();it!=lower.end();it++)  //concatenating two upper and lower hulls
	{
		Point p=*it;
		upper.push_back(p);
	}


}