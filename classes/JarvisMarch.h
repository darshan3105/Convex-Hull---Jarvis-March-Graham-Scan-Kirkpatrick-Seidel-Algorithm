#include<iostream>
#include<string>
#include "data_types.h"
#include "Point.h"
#include "List.h"
#include "Stack.h"
#include "../utils.h"

using namespace std;

class JarvisMarch{

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

  public:
    JarvisMarch(){
      points = List<Point>();
    }
    void fit_set(List<Point> list){
      points = list;
    }
    void add_point(Point pt){
      points.add(pt);
    }
    List<Point> compute_hull(){
      if(points.size() < 3){

        cout<<"Convex hull doesn't exist!!"<<endl;
        return 0;
      }

      int pt_index = get_min_Y(points);

      List<Point> hull;
      int l = pt_index;
      int p = l,q;
      do{
          hull.add(points.get(p));
          int n = points.size();
          q = (p+1)%n;

          for(int i=0;i<n;i++){
            if(points.get(p).orientation(points.get(i),points.get(q)) == 2)
              q = i;
          }

           p = q;

      }while(p != l);

      return hull;
    }
};
