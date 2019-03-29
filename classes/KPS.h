#ifndef KPS_H
#define KPS_H

#include<iostream>
#include<algorithm>
#include<climits>
#include "List.h"
#include "Pair.h"
#include "Point.h"
#include "data_types.h"
#include "../utils.h"

using namespace std;

class KPS{

    List<Point> points;

    double findMedian(double arr[], int n){
    	sort(arr, arr+n); // Sort the array
    	return arr[n/2]; // Return middle element
    }

    void swap(double *a, double *b){
    	double temp = *a;
    	*a = *b;
    	*b = temp;
    }

    int partition(double arr[], int l, int r, double x){
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

    double kthSmallest(double arr[], int l, int r, int k){
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

    double abss(double a){

      if(a < 0) return 0-a;
      else return a;
    }

    List<Point> get_T(Point p1,Point p2,List<Point> points){


      List<Point> upper_T;

      for(int i=0;i<points.size();i++){
        Point curr_point = points.get(i);
        if(curr_point.get_X() > p1.get_X() && curr_point.get_X() < p2.get_X()){
          upper_T.add(curr_point);
        }
      }
      upper_T.add(p1);
      upper_T.add(p2);

      return upper_T;

    }

    Pair<Point,Point> get_upper_bridge(List<Point> points,double median){

        // points.print();
        // cout<<endl;
        // cout<<"a:"<<median<<endl;
        if(points.size() <= 2){
          Point first = points.get(0);
          Point second = points.get(1);
          Pair<Point,Point> upper_bridge(first,second);

          return upper_bridge;
        }
        else{
          sort(points.begin(),points.end(),[](Point a,Point b){ return a.get_X() < b.get_X();});
          // cout<<"sorted: ";
          // points.print();

          List<Point> candidates;
          List<Pair<Point,Point> > pairs;
          if(points.size()%2==0){
            for(int i=0;i<points.size();i+=2){
              Point first_pt = points.get(i);
              Point second_pt = points.get(i+1);

              Pair<Point,Point> curr_pair(first_pt,second_pt);
              pairs.add(curr_pair);
            }
          }
          else{
            candidates.add(points.get(0));
            for(int i=1;i<points.size();i+=2){
              Point first_pt = points.get(i);
              Point second_pt = points.get(i+1);

              Pair<Point,Point> curr_pair(first_pt,second_pt);
              pairs.add(curr_pair);
            }
          }
          int slopes_len = pairs.size();
          double slopes[slopes_len];
          for(int i=0;i<pairs.size();i++){

            Point p1= pairs.get(i).get_first();
            Point p2 = pairs.get(i).get_second();
            double x1 = p1.get_X();
            double x2 = p2.get_X();
            double y1 = p1.get_Y();
            double y2 = p2.get_Y();

            if(x1 == x2){
              if(y1 > y2){
                candidates.add(p1);
              }
              else{
                candidates.add(p2);
              }
              slopes[i] = INT_MAX;
            }
            else{
                double slope = (y2-y1)/(double)(x2-x1);
                slopes[i] = slope;
            }

          }

          double arr[slopes_len];
          int len = 0;
          for(int i=0;i<slopes_len;i++){
            if(slopes[i] != INT_MAX){
              arr[len++] = slopes[i];
            }
          }
          // cout<<endl;
          // for(int i=0;i<len;i++) cout<<arr[i]<<" ";
          //   cout<<endl;
          double median_slope = kthSmallest(arr,0,len-1,(len+1)/2);
          // cout<<"\n"<<"median slope:"<<median_slope<<endl;
          // cout<<"\n"<<"pairs: ";
          //
          // pairs.print();
          // cout<<endl;


          List<Pair<Point,Point> > SMALL,EQUAL,LARGE;
          for(int i=0;i<pairs.size();i++){
            Point p1= pairs.get(i).get_first();
            Point p2 = pairs.get(i).get_second();
            double x1 = p1.get_X();
            double x2 = p2.get_X();
            double y1 = p1.get_Y();
            double y2 = p2.get_Y();

            if(x1 != x2){
              double slope = (y2-y1)/(x2-x1);
              if(abss(slope - median_slope) < 0.001){
                Pair<Point,Point> curr_pair(p1,p2);
                EQUAL.add(curr_pair);
              }
              else if(slope < median_slope){
                Pair<Point,Point> curr_pair(p1,p2);
                SMALL.add(curr_pair);
              }
              else if(slope > median_slope){
                Pair<Point,Point> curr_pair(p1,p2);
                LARGE.add(curr_pair);
              }

            }
          }


          double max_c = INT_MIN;
          for(int i=0;i<points.size();i++){

            double x = points.get(i).get_X();
            double y = points.get(i).get_Y();
            double curr_c = (y - (double)median_slope*x);

            if(curr_c > max_c){
              max_c = curr_c;
            }

          }

          Point pmin(INT_MAX,INT_MAX);
          Point pmax(INT_MIN,INT_MIN);


          // cout<<"ccccccc"<<endl;
          for(int i=0;i<points.size();i++){

            double x = points.get(i).get_X();
            double y = points.get(i).get_Y();

            double curr_c = y - (double)median_slope*x;

            if(abss((double)curr_c-max_c) < 0.001){
              //points.get(i).print();cout<<" "<<curr_c<<" "<<max_c<<endl;
              if(x < pmin.get_X()){
                pmin.set_point(x,y);
              }
              if(x > pmax.get_X()){
                pmax.set_point(x,y);
              }
            }


          }

          // cout<<"pmin :";
          // pmin.print();
          // cout<<" pmax :";
          // pmax.print();
          // cout<<"\n"<<"***************"<<endl;

          if(pmin.get_X() <= median && pmax.get_X() > median){
            Pair<Point,Point> upper_bridge(pmin,pmax);
            return upper_bridge;
          }
          else if(pmax.get_X() <= median){
            for(int i=0;i<EQUAL.size();i++){
              Point pt = EQUAL.get(i).get_second();
              candidates.add(pt);
            }
            for(int i=0;i<LARGE.size();i++){
              Point pt = LARGE.get(i).get_second();
              candidates.add(pt);
            }
            for(int i=0;i<SMALL.size();i++){
              Point pt1 = SMALL.get(i).get_first();
              Point pt2 = SMALL.get(i).get_second();
              candidates.add(pt1);
              candidates.add(pt2);
            }
            return get_upper_bridge(candidates,median);

          }
          else if(pmin.get_X() > median){
            for(int i=0;i<EQUAL.size();i++){
              Point pt = EQUAL.get(i).get_first();
              candidates.add(pt);
            }
            for(int i=0;i<LARGE.size();i++){
              Point pt1 = LARGE.get(i).get_first();
              Point pt2 = LARGE.get(i).get_second();
              candidates.add(pt1);
              candidates.add(pt2);
            }
            for(int i=0;i<SMALL.size();i++){
              Point pt = SMALL.get(i).get_first();
              candidates.add(pt);
            }
            return get_upper_bridge(candidates,median);
          }

        }
    }

    Pair<Point,Point> get_lower_bridge(List<Point> points,double median){
        if(points.size() <= 2){
          Point first = points.get(0);
          Point second = points.get(1);
          Pair<Point,Point> lower_bridge(first,second);

          return lower_bridge;
        }
        else{
          sort(points.begin(),points.end(),[](Point a,Point b){ return a.get_X() < b.get_X();});
          //points.reverse();
          // cout<<"sorted ";
          // points.print();
          // cout<<"\n";

          List<Point> candidates;
          List<Pair<Point,Point> > pairs;
          if(points.size()%2==0){
            for(int i=0;i<points.size();i+=2){
              Point first_pt = points.get(i);
              Point second_pt = points.get(i+1);

              Pair<Point,Point> curr_pair(first_pt,second_pt);
              pairs.add(curr_pair);
            }
          }
          else{
            candidates.add(points.get(0));
            for(int i=1;i<points.size();i+=2){
              Point first_pt = points.get(i);
              Point second_pt = points.get(i+1);

              Pair<Point,Point> curr_pair(first_pt,second_pt);
              pairs.add(curr_pair);
            }
          }

          int slopes_len = pairs.size();
          double slopes[slopes_len];
          for(int i=0;i<pairs.size();i++){

            Point p1= pairs.get(i).get_first();
            Point p2 = pairs.get(i).get_second();
            double x1 = p1.get_X();
            double x2 = p2.get_X();
            double y1 = p1.get_Y();
            double y2 = p2.get_Y();

            if(x1 == x2){
              if(y1 > y2){
                candidates.add(p2);
              }
              else{
                candidates.add(p1);
              }
              slopes[i] = INT_MAX;
            }
            else{
                double slope = (y2-y1)/(x2-x1);
                slopes[i] = slope;
            }

          }

          double arr[slopes_len];
          int len = 0;
          for(int i=0;i<slopes_len;i++){
            if(slopes[i] != INT_MAX){
              arr[len++] = slopes[i];
            }
          }
          // cout<<endl;
          // for(int i=0;i<len;i++) cout<<arr[i]<<" ";
          //   cout<<endl;
          double median_slope = kthSmallest(arr,0,len-1,(len+1)/2);

          // cout<<"\n"<<"median slope:"<<median_slope<<endl;
          // cout<<"\n"<<"pairs: ";

          // pairs.print();
          // cout<<endl;
          List<Pair<Point,Point> > SMALL,EQUAL,LARGE;
          for(int i=0;i<pairs.size();i++){
            Point p1= pairs.get(i).get_first();
            Point p2 = pairs.get(i).get_second();
            double x1 = p1.get_X();
            double x2 = p2.get_X();
            double y1 = p1.get_Y();
            double y2 = p2.get_Y();

            if(x1 != x2){
              double slope = (y2-y1)/(x2-x1);
              if(abss(slope - median_slope) < 0.001){
                Pair<Point,Point> curr_pair(p1,p2);
                EQUAL.add(curr_pair);
              }
              else if(slope < median_slope){
                Pair<Point,Point> curr_pair(p1,p2);
                SMALL.add(curr_pair);
              }
              else if(slope > median_slope){
                Pair<Point,Point> curr_pair(p1,p2);
                LARGE.add(curr_pair);
              }

            }
          }


          double min_c = INT_MAX;
          // cout<<"cccccc"<<endl;
          for(int i=0;i<points.size();i++){

            double x = points.get(i).get_X();
            double y = points.get(i).get_Y();
            double curr_c = (y - median_slope*x);

            if(curr_c < min_c){
              min_c = curr_c;
            }

          }

          Point pmin(INT_MAX,INT_MAX);
          Point pmax(INT_MIN,INT_MIN);

          for(int i=0;i<points.size();i++){

            double x = points.get(i).get_X();
            double y = points.get(i).get_Y();
            double curr_c = (y - median_slope*x);

            if(abss(curr_c - min_c) < 0.001){
              //points.get(i).print();cout<<" "<<curr_c<<" "<<min_c<<endl;
              if(x < pmin.get_X()){
                pmin.set_point(x,y);
              }
              if(x > pmax.get_X()){
                pmax.set_point(x,y);
              }
            }
          }

          // cout<<"pmin :";
          // pmin.print();
          // cout<<" pmax :";
          // pmax.print();
          // cout<<endl;


          // cout<<"EQUAL: ";EQUAL.print();cout<<endl;
          // cout<<"LARGE: ";LARGE.print();cout<<endl;
          // cout<<"SMALL: ";SMALL.print();cout<<endl;
          // cout<<"\n"<<"***************"<<endl;
          if(pmin.get_X() <= median && pmax.get_X() > median){
            Pair<Point,Point> lower_bridge(pmin,pmax);
            return lower_bridge;
          }
          else if(pmax.get_X() <= median){

            for(int i=0;i<EQUAL.size();i++){
              Point pt = EQUAL.get(i).get_second();
              candidates.add(pt);
            }
            for(int i=0;i<LARGE.size();i++){
              Point pt1 = LARGE.get(i).get_first();
              Point pt2 = LARGE.get(i).get_second();
              candidates.add(pt1);
              candidates.add(pt2);
            }
            for(int i=0;i<SMALL.size();i++){
              Point pt = SMALL.get(i).get_second();
              candidates.add(pt);
            }
            return get_lower_bridge(candidates,median);


          }
          else if(pmin.get_X() > median){
            for(int i=0;i<EQUAL.size();i++){
              Point pt = EQUAL.get(i).get_first();
              candidates.add(pt);
            }
            for(int i=0;i<LARGE.size();i++){
              Point pt = LARGE.get(i).get_first();
              candidates.add(pt);
            }
            for(int i=0;i<SMALL.size();i++){
              Point pt1 = SMALL.get(i).get_first();
              Point pt2 = SMALL.get(i).get_second();
              candidates.add(pt1);
              candidates.add(pt2);
            }
            return get_lower_bridge(candidates,median);
          }

        }
    }

    List<Point> get_upper_hull(Point pmin,Point pmax,List<Point> points){

        List<Point> upper_hull;
        int n = points.size();
        double arr[n];
        for(int i=0;i<n;i++){
          arr[i] = points.get(i).get_X();
        }
        double median = kthSmallest(arr,0,n-1,(n+1)/2);
        Pair<Point,Point> upper_bridge = get_upper_bridge(points,median);


        Point pl = upper_bridge.get_first();
        Point pr = upper_bridge.get_second();

        upper_hull.add(pl);
        upper_hull.add(pr);

        if(!pmin.equals(pl)){
          List<Point> upper_T_left = get_T(pmin,pl,points);
          //cout<<"yes"<<endl;
          List<Point> left = get_upper_hull(pmin,pl,upper_T_left);
          upper_hull.append_list(left);
        }

        if(!pmax.equals(pr)){
          List<Point> upper_T_right = get_T(pr,pmax,points);
          //cout<<"yes"<<endl;
          List<Point> right = get_upper_hull(pr,pmax,upper_T_right);
          upper_hull.append_list(right);
        }

        return upper_hull;

    }

    List<Point> get_lower_hull(Point pmin,Point pmax,List<Point> points){

        List<Point> lower_hull;
        int n = points.size();
        double arr[n];
        for(int i=0;i<n;i++){
          arr[i] = points.get(i).get_X();
        }
        double median = kthSmallest(arr,0,n-1,(n+1)/2);
        Pair<Point,Point> lower_bridge = get_lower_bridge(points,median);

        Point pl = lower_bridge.get_first();
        Point pr = lower_bridge.get_second();


        lower_hull.add(pl);
        lower_hull.add(pr);

        if(!pmin.equals(pl)){
          List<Point> lower_T_left = get_T(pmin,pl,points);
          //cout<<"yes"<<endl;
          List<Point> left = get_lower_hull(pmin,pl,lower_T_left);
          lower_hull.append_list(left);

        }
        if(!pmax.equals(pr)){
          List<Point> lower_T_right = get_T(pr,pmax,points);
          //cout<<"yes"<<endl;
          List<Point> right = get_lower_hull(pr,pmax,lower_T_right);
          lower_hull.append_list(right);
        }

        return lower_hull;
    }

  public:
    KPS(){
      points = List<Point>();
    }
    void fit_set(List<Point> list){
      points = list;
    }
    void add_point(Point pt){
      points.add(pt);
    }
    List<Point> compute_hull(){

      points = make_list("datasets/points.csv");

      Point pmin_u,pmin_l,pmax_u,pmax_l;

      pmin_l = pmin_u = pmax_u = pmax_l = points.get(0);
      for(int i=1;i<points.size();i++){
          Point curr_point = points.get(i);
          if(curr_point.get_X() < pmin_l.get_X()){
            pmin_l = curr_point;
            pmin_u = curr_point;
          }
          else if(curr_point.get_X() > pmax_l.get_X()){
            pmax_l = curr_point;
            pmax_u = curr_point;
          }
          else if(curr_point.get_X() == pmin_l.get_X()){
            if(curr_point.get_Y() > pmin_u.get_Y()){
              pmin_u = curr_point;
            }
            else if(curr_point.get_Y() < pmin_l.get_Y()){
              pmin_l = curr_point;
            }
          }
          else if(curr_point.get_X() == pmax_l.get_X()){
            if(curr_point.get_Y() > pmax_u.get_Y()){
              pmax_u = curr_point;
            }
            else if(curr_point.get_Y() < pmax_l.get_Y()){
              pmax_l = curr_point;
            }
          }
      }

      List<Point> upper_T = get_T(pmin_u,pmax_u,points);
      List<Point> upper_hull = get_upper_hull(pmin_u,pmax_u,upper_T);

      List<Point> lower_T = get_T(pmin_l,pmax_l,points);
      List<Point> lower_hull = get_lower_hull(pmin_l,pmax_l,lower_T);


      List<Point> hull_edges;
      hull_edges.append_list(upper_hull);
      hull_edges.append_list(lower_hull);

      if(!pmin_u.equals(pmin_l)){
        hull_edges.add(pmin_l);
        hull_edges.add(pmin_u);
      }
      if(!pmax_l.equals(pmax_u)){
        hull_edges.add(pmax_l);
        hull_edges.add(pmax_u);
      }


      make_result(hull_edges,"results/results_1.csv");

      sort(hull_edges.begin(),hull_edges.end(),[](Point a,Point b){if(a.get_X() < b.get_X()) return true;else if(a.get_X() > b.get_X())
      return false;else return a.get_Y() < b.get_Y();});

      List<Point> hull;
      for(int i=0;i<hull_edges.size();i+=2){
        hull.add(hull_edges.get(i));
      }

      return hull;
    }

};
#endif
