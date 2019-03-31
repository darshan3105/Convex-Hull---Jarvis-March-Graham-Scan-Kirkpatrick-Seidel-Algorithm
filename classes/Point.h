#ifndef POINT_H
#define POINT_H

#include<iostream>

using namespace std;

/** Point is class for generating points on a 2D plane.
 */

class Point{

  double x;
  double y;

  public:

    /** Contructor.
      * This is the default constructor for the class Point.It creates a point with x and y coordinates equal to -1.
     */
    Point(){

      this->x = -1;
      this->y = -1;
    }
    /** Contructor.
      * creates a point with x and y coordinates passd as arguments.
      * @param a double value for x coordinate.
      * @param a double value for y coordinate.
     */
    Point(double x,double y){

      this->x = x;
      this->y = y;
    }
    /** return the x coordinate of the point.
      * @param a double value equal to the x coordinate.
     */
    double get_X(){

      return this->x;
    }
    /** return the y coordinate of the point.
      * @param a double value equal to the y coordinate.
     */
    double get_Y(){

      return this->y;
    }
    /** sets the x and y coordinates of the point to the values passed as argumensts.
      * @param a double value equal to the new x coordinate.
      * @param a double value equal to the new y coordinate.
     */
    void set_point(double x,double y){

      this->x = x;
      this->y = y;
    }
    /** sets the x and y coordinates of the point to values of the point passed as argument.
      * @param an object of type point.
     */
    void set_point(Point pt){

      this->x = pt.get_X();
      this->y = pt.get_Y();
    }
    /** sets the x coordinate of the point equal to the value passed as the argument.
      * @param a double value equal to the new x coordinate.
     */
    void set_X(double x){
      this->x = x;
    }
    /** sets the y coordinate of the point equal to the value passed as the argument.
      * @param a double value equal to the new y coordinate.
     */
    void set_Y(double y){

      this->y = y;
    }
    /** returns the orientation of the point with two other points passed as arguments.
      * returns 0 the points are collinear,1 if they are clockwise and 2 if anticlockwise.
      * @param point1 of type Point.
      * @param point2 of type Point.
      * @return an integer value denoting the orientation.
     */
    int orientation(Point p1,Point p2){

        int val = (p1.y - this->y)*(p2.x - p1.x) - (p1.x - this->x)*(p2.y-p1.y);
        if(val == 0) return  0;
        else if(val > 0) return 1;
        else return 2;
    }
    /** returns the square of the euclidian distance between the invoking point and the point passed as an argument.
      * @param point of type Point.
      * @return a float value denoting the  square distance.
     */
    float sq_dist(Point p){

      return (this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y);
    }
    /** accepts a point as an argument, and returns true if they are equal, else returns false.
      * @param point of type Point.
      * @return a boolean value.
     */
    bool equals(Point pt){
      if(x == pt.x && y == pt.y)
        return true;
      else
        return false;
    }
    /** prints the point.
     */
    void print(){
      cout<<"("<<x<<","<<y<<")";
    }
};

#endif
