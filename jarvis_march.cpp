#include<iostream>
#include<string>
#include "classes/data_types.h"
#include "classes/Point.h"
#include "classes/List.h"
#include "classes/Stack.h"
#include "utils.h"

using namespace std;

int main(){

  List<Point> points = make_list("datasets/1.csv");
  /*points.add(*(new Point(0,3)));
  points.add(*(new Point(1,1)));
  points.add(*(new Point(2,2)));
  points.add(*(new Point(4,4)));
  points.add(*(new Point(0,0)));
  points.add(*(new Point(1,2)));
  points.add(*(new Point(3,1)));
  points.add(*(new Point(3,3)));*/

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

  make_result(hull,1);

  hull.print();
  cout<<endl;
}
