#include<iostream>
#include<string>
#include "classes/data_types.h"
#include "classes/Point.h"
#include "classes/List.h"
#include "classes/Stack.h"
#include "utils.h"

using namespace std;

class GrahamScan{

    List<Point> points;

  public:
    void fit_set(string addr){
      points = make_list(addr);
    }
    void add_point(Point pt){
      points.add(point);
    }
    List compute_hull(){
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
      hull.print();
      cout<<endl;
      make_result(hull,1);
    }
};
