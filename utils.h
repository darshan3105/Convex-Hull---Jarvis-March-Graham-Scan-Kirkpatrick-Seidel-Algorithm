#ifndef UTILS_H
#define UTILS_H

#include<iostream>
#include<climits>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include "classes/List.h"
#include "classes/Point.h"

using namespace std;

void make_result(List<Point> list,string addr){

    fstream file;
    ostringstream str1;
    file.open(addr,ios::out);
    for(int i=0;i<list.size();i++){
      Point p = list.get(i);
      file <<p.get_X()<<","<<p.get_Y()<<"\n";
    }
    file.close();
}

List<Point> make_list(string addr){

    List<Point> list;

    fstream file;
    file.open(addr);
    string line;
    while(getline(file,line,'\n')){
      istringstream templine(line);
      string data;
      int i=0;
      double a[2];
      while(getline(templine,data,',')){
          a[i] = stof(data);
          i++;
      }
      Point p(a[0],a[1]);
      list.add(p);

    }
    file.close();
    return list;
}

#endif
