#ifndef POINT_H
#define POINT_H

#include<iostream>

using namespace std;

class Point{

  double x;
  double y;

  public:

    Point(){

      this->x = -1;
      this->y = -1;
    }
    Point(double x,double y){

      this->x = x;
      this->y = y;
    }
    double get_X(){

      return this->x;
    }
    double get_Y(){

      return this->y;
    }
    void set_point(double x,double y){

      this->x = x;
      this->y = y;
    }
    void set_point(Point pt){

      this->x = pt.get_X();
      this->y = pt.get_Y();
    }
    void set_X(double x){
      this->x = x;
    }
    void set_Y(double y){

      this->y = y;
    }
    int orientation(Point p1,Point p2){

        int val = (p1.y - this->y)*(p2.x - p1.x) - (p1.x - this->x)*(p2.y-p1.y);
        if(val == 0) return  0;
        else if(val > 0) return 1;
        else return 2;
    }
    float sq_dist(Point p){

      return (this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y);
    }
    bool equals(Point pt){
      if(x == pt.x && y == pt.y)
        return true;
      else
        return false;
    }
    void print(){
      cout<<"("<<x<<","<<y<<")";
    }
};

#endif
