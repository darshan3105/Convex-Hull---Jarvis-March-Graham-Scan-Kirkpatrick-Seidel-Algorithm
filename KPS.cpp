#include<iostream>
#include<algorithm>
#include<climits>
#include "classes/List.h"
#include "classes/Pair.h"
#include "classes/Point.h"
#include "classes/data_types.h"
#include "utils.h"

using namespace std;

double abss(double a){

  if(a < 0) return 0-a;
  else return a;
}

bool sort_by_x(Point a,Point b){

  return a.get_X() < b.get_X();
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
      sort(points.begin(),points.end(),sort_by_x);
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

    // points.print();
    // cout<<endl;
    // cout<<"a: "<<median<<endl;
    if(points.size() <= 2){
      Point first = points.get(0);
      Point second = points.get(1);
      Pair<Point,Point> lower_bridge(first,second);

      return lower_bridge;
    }
    else{
      sort(points.begin(),points.end(),sort_by_x);
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
      //cout<<"cccccc"<<endl;
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

void get_upper_hull(Point pmin,Point pmax,List<Point> points){

    int n = points.size();
    double arr[n];
    for(int i=0;i<n;i++){
      arr[i] = points.get(i).get_X();
    }
    double median = kthSmallest(arr,0,n-1,(n+1)/2);
    Pair<Point,Point> upper_bridge = get_upper_bridge(points,median);
    if(!upper_bridge.get_first().equals(upper_bridge.get_second())){
      upper_bridge.get_first().print();
      upper_bridge.get_second().print();
      cout<<endl;
    }
    else{
      upper_bridge.get_first().print();
      cout<<endl;
    }

    Point pl = upper_bridge.get_first();
    Point pr = upper_bridge.get_second();

    if(!pmin.equals(pl)){
      List<Point> upper_T_left = get_T(pmin,pl,points);
      //cout<<"yes"<<endl;
      get_upper_hull(pmin,pl,upper_T_left);
    }

    if(!pmax.equals(pr)){
      List<Point> upper_T_right = get_T(pr,pmax,points);
      //cout<<"yes"<<endl;
      get_upper_hull(pr,pmax,upper_T_right);
    }

}

void get_lower_hull(Point pmin,Point pmax,List<Point> points){

    int n = points.size();
    double arr[n];
    for(int i=0;i<n;i++){
      arr[i] = points.get(i).get_X();
    }
    double median = kthSmallest(arr,0,n-1,(n+1)/2);
    Pair<Point,Point> lower_bridge = get_lower_bridge(points,median);
    if(!lower_bridge.get_first().equals(lower_bridge.get_second())){
      lower_bridge.get_first().print();
      lower_bridge.get_second().print();
      cout<<endl;
    }
    else{
      lower_bridge.get_first().print();
      cout<<endl;
    }

    Point pl = lower_bridge.get_first();
    Point pr = lower_bridge.get_second();


    if(!pmin.equals(pl)){
      List<Point> lower_T_left = get_T(pmin,pl,points);
      //cout<<"yes"<<endl;
      get_lower_hull(pmin,pl,lower_T_left);

    }
    if(!pmax.equals(pr)){
      List<Point> lower_T_right = get_T(pr,pmax,points);
      //cout<<"yes"<<endl;
      get_lower_hull(pr,pmax,lower_T_right);
    }


}

int main(){

    List<Point> points = make_list("datasets/points.csv");
    // points.add(*(new Point(0,3)));
    // points.add(*(new Point(1,1)));
    // points.add(*(new Point(2,2)));
    // points.add(*(new Point(4,4)));
    // points.add(*(new Point(0,0)));
    // points.add(*(new Point(1,2)));
    // points.add(*(new Point(3,1)));
    // points.add(*(new Point(3,3)));

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
    get_upper_hull(pmin_u,pmax_u,upper_T);

    List<Point> lower_T = get_T(pmin_l,pmax_l,points);
    get_lower_hull(pmin_l,pmax_l,lower_T);

}
