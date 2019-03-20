#include<iostream>
#include<string>
#include "classes/data_types.h"
#include "classes/Point.h"
#include "classes/List.h"
#include "classes/Stack.h"
#include "utils.h"

using namespace std;

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


    int pt_index = get_min_Y(points);
    sort_by_angle(points,pt_index);

    if(points.size() < 3){

      cout<<"Convex hull doesn't exist!!"<<endl;
      return 0;
    }

    Stack<Integer> s;
    s.push(0);
    s.push(1);
    s.push(2);

    for(int i=3;i<points.size();i++){

      int temp = s.pop().get();
      int first = s.peek().get();
      s.push(temp);
      int second = s.peek().get();
      int third = i;
      while(points.get(first).orientation(points.get(second),points.get(third)) != 2){
        s.pop();
        temp = s.pop().get();
        first = s.peek().get();
        s.push(temp);
        second = s.peek().get();
        third = i;
      }

      s.push(i);
    }

    while(!s.empty()){

      int index = s.pop().get();
      points.get(index).print();
      cout<<endl;
    }

}
