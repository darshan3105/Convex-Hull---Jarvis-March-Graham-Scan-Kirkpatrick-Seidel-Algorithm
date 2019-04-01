#include<iostream>
#include<ctime>
#include "classes/List.h"
#include "classes/Point.h"
#include "classes/GrahamScan.h"
#include "classes/JarvisMarch.h"
#include "classes/KPS.h"
#include "utils.h"


using namespace std;

int main(){

    KPS jm;
    time_t time1,time2;
    List<Point> points = make_list("datasets/points.csv");
    jm.fit_set(points);
    //time1 = time(NULL);
    List<Point> hull = jm.compute_hull();
    //time2 = time(NULL);
    hull.print();cout<<endl;
    //cout<<"time :"<<time2-time1<<endl;
    cout<<endl;

}
