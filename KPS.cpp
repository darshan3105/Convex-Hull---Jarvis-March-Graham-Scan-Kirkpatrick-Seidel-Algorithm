#include<iostream>
#include<climits>
#include "classes/List.h"
#include "classes/Pair.h"
#include "classes/Point.h"
#include "classes/data_types.h"
#include "utils.h"

using namespace std;

bool sort_by_x(Point a,Point b){

  return a.get_X() < b.get_X();
}

Pair<Point,Point> get_upper_bridge(List<Point> points,float median){

    if(points.size() == 2){
      Point first = points.get(0);
      Point second = points.get(1);
      Pair<Point,Point> upper_bridge(first,second);

      return upper_bridge;
    }
    else{
      sort(points.begin(),points.end(),sort_by_x);

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
      float slopes[slopes_len];
      for(int i=0;i<pairs.size();i++){

        Point p1= pairs.get(i).get_first();
        Point p2 = pairs.get(i).get_second();
        int x1 = p1.get_X();
        int x2 = p2.get_X();
        int y1 = p1.get_Y();
        int y2 = p2.get_Y();

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
            float slope = (float)(y2-y1)/(x2-x1);
            slopes[i] = slope;
        }

      }

      float arr[slopes_len];
      int len = 0;
      for(int i=0;i<slopes_len;i++){
        if(slopes[i] != INT_MAX){
          arr[len++] = slopes[i];
        }
      }
      float median_slope = kthSmallest(arr,0,len-1,(len+1)/2);

      List<Pair<Point,Point> > SMALL,EQUAL,LARGE;
      for(int i=0;i<pairs.size();i++){
        Point p1= pairs.get(i).get_first();
        Point p2 = pairs.get(i).get_second();
        int x1 = p1.get_X();
        int x2 = p2.get_X();
        int y1 = p1.get_Y();
        int y2 = p2.get_Y();

        if(x1 != x2){
          float slope = (float)(y2-y1)/(x2-x1);
          if(slope < median_slope){
            Pair<Point,Point> curr_pair(p1,p2);
            SMALL.add(curr_pair);
          }
          else if(slope > median_slope){
            Pair<Point,Point> curr_pair(p1,p2);
            LARGE.add(curr_pair);
          }
          else{
            Pair<Point,Point> curr_pair(p1,p2);
            EQUAL.add(curr_pair);
          }
        }
      }

      float max_c = INT_MIN;
      for(int i=0;i<points.size();i++){

        int x = points.get(i).get_X();
        int y = points.get(i).get_Y();
        float curr_c = (float)(y - median_slope*x);

        if(curr_c > max_c){
          max_c = curr_c;
        }

      }

      Point pmin(INT_MAX,INT_MAX);
      Point pmax(INT_MIN,INT_MIN);

      for(int i=0;i<points.size();i++){

        int x = points.get(i).get_X();
        int y = points.get(i).get_Y();
        float curr_c = (float)(y - median_slope*x);

        if(curr_c == max_c){
          if(x < pmin.get_X()){
            pmin.set_point(x,y);
          }
          if(x > pmax.get_X()){
            pmax.set_point(x,y);
          }
        }
      }

      if(pmin.get_X() <= median && pmax.get_X() < median){
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
      else if(pmin.get_X() > median_slope){
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
          Point pt1 = SMALL.get(i).get_first();
          candidates.add(pt1);
        }
        return get_upper_bridge(candidates,median);
      }

    }
}

void get_upper_hull(Point pmin,Point pmax,List<Point> points){

    int n = points.size();
    float arr[n];

    for(int i=0;i<n;i++){
      arr[i] = points.get(i).get_X();
    }
    float median = kthSmallest(arr,0,n-1,(n+1)/2);
    Pair<Point,Point> upper_bridge = get_upper_bridge(points,median);
    if(!upper_bridge.get_first().equals(upper_bridge.get_second())){
      upper_bridge.get_first().print();
      upper_bridge.get_second().print();
    }
    else{
      upper_bridge.get_first().print();
    }

    Point pl = upper_bridge.get_first();
    Point pr = upper_bridge.get_second();

    List<Point> upper_T;
    for(int i=0;i<points.size();i++){
      Point curr_point = points.get(i);
      if(curr_point.get_X() > pmin.get_X() && curr_point.get_X() < pl.get_X()){
        upper_T.add(curr_point);
      }
    }
    upper_T.add(pmin);
    upper_T.add(pl);

    get_upper_hull(pmin,pl,upper_T);

    upper_T.clear();

    for(int i=0;i<points.size();i++){
      Point curr_point = points.get(i);
      if(curr_point.get_X() > pr.get_X() && curr_point.get_X() < pmax.get_X()){
        upper_T.add(curr_point);
      }
    }
    upper_T.add(pr);
    upper_T.add(pmax);

    get_upper_hull(pr,pmax,upper_T);


}

int main(){

    List<Point> points;
    points.add(*(new Point(0,3)));
    points.add(*(new Point(1,1)));
    points.add(*(new Point(2,2)));
    points.add(*(new Point(4,4)));
    points.add(*(new Point(0,0)));
    points.add(*(new Point(1,2)));
    points.add(*(new Point(3,1)));
    points.add(*(new Point(3,3)));

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

    List<Point> upper_T;
    for(int i=0;i<points.size();i++){
      Point curr_point = points.get(i);
      if(curr_point.get_X() > pmin_u.get_X() && curr_point.get_X() < pmax_u.get_X()){
        upper_T.add(curr_point);
      }
    }
    upper_T.add(pmin_u);
    upper_T.add(pmax_u);

    get_upper_hull(pmin_u,pmax_u,upper_T);

}
