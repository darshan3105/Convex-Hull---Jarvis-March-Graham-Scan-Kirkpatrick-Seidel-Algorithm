#include<iostream>
#include<string>
#include "data_types.h"
#include "Point.h"
#include "List.h"
#include "Stack.h"
#include "../utils.h"

using namespace std;

class GrahamScan{

    List<Point> points;

    int get_min_Y(List<Point> points){

      int i,curr_y,curr_x,index = 0;
      float min_y = points.get(0).get_Y();


      for (i=1;i<points.size();i++){

        curr_y = points.get(i).get_Y();
        curr_x = points.get(i).get_X();
        if((curr_y < min_y) || (curr_y == min_y && curr_x < points.get(index).get_X())){

          min_y = curr_y;
          index = i;
        }
      }

      return index;
    }

    void merge(List<Point> points,int l,int m,int r,Point ref){

      int i,j,k;
      int n1 = m-l+1;
      int n2 = r-m;

      List<Point> L(n1);
      List<Point> R(n2);

      for(i=0;i<n1;i++){

        L.add(points.get(l+i));
      }
      for(i=0;i<n2;i++){

        R.add(points.get(m+1+i));
      }

      i=0;
      j=0;
      k=l;

      while(i<n1 && j<n2){

        Point p1;
        Point p2;

        //p1.set_point(L.get(i));
        //p2.set_point(R.get(j));

        p1 = L.get(i);
        p2 = R.get(j);

        int o = ref.orientation(p1,p2);
        if(o==0){
          if(ref.sq_dist(p2) >= ref.sq_dist(p1)){

            points.edit(k,p2);
            j++;
          }
          else{

            points.edit(k,p1);
            i++;
          }
        }
        else if(o == 2){
          points.edit(k,p1);
          i++;
        }
        else{
          points.edit(k,p2);
          j++;
        }
        k++;
      }
      while(i<n1){

        points.edit(k,L.get(i));
        i++;
        k++;
      }
      while(j<n2){
        points.edit(k,R.get(j));
        j++;
        k++;
      }
    }
    void mergesort(List<Point> points,int l,int r,Point ref){

      if(l < r){

        int m = (l+r)/2;
        mergesort(points,l,m,ref);
        mergesort(points,m+1,r,ref);
        merge(points,l,m,r,ref);
      }
    }
    void sort_by_angle(List<Point> points,int index){

        points.swap(0,index);
        mergesort(points,1,points.size()-1,points.get(0));
    }

  public:
    GrahamScan(){
      points = List<Point>();
    }

    void fit_set(List<Point> list){
      points = list;
    }
    void add_point(Point pt){
      points.add(pt);
    }
    List<Point> compute_hull(){
      int pt_index = get_min_Y(points);
      sort_by_angle(points,pt_index);

      if(points.size() < 3){

        cout<<"Convex hull doesn't exist!!"<<endl;
        return 0;
      }

      Stack<int> s;
      s.push(0);
      s.push(1);
      s.push(2);

      for(int i=3;i<points.size();i++){

        while(points.get(s.next_to_top()).orientation(points.get(s.peek()),points.get(i)) != 2){
          s.pop();
        }

        s.push(i);
      }

      List<Point> hull(s.size());
      while(!s.empty()){
          int index = s.pop();
          hull.add(points.get(index));
      }
      hull.reverse();
      make_result(points,"datasets/points_sorted.csv");
      return hull;
    }
};
