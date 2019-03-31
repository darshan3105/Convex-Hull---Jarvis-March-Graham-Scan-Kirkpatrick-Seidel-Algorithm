#ifndef JARVIS_MARCH_H
#define JARVIS_MARCH_H


#include<iostream>
#include<string>
#include "data_types.h"
#include "Point.h"
#include "List.h"
#include "Stack.h"
#include "../utils.h"

using namespace std;

/** Jarvis march is an algorithm used for getting the convex hull of a set of points.
  * The object of this class uses JarvisMarch algorithm to find the convex hull.
 */


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

    /** Contructor.
      * This is the default constructor for the class JarvisMarch.It creates an empty list of type List<Point>.
     */
    JarvisMarch(){
      points = List<Point>();
    }

    /** accepts a list of type List<Point> to make the dataset for finding the convex hull.
      * @param a list of type List<Point>
     */
    void fit_set(List<Point> list){
      points = list;
    }

    /** accepts a point of type Point and adds it to the dataset.
      * @param a point of type Point
     */
    void add_point(Point pt){
      points.add(pt);
    }

    /** returns a list of type List<Point> containing the points on the convex hull.
     */
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

      make_result(hull,"results/results_1.csv");
      return hull;
    }
};
#endif
