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

  public:
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
