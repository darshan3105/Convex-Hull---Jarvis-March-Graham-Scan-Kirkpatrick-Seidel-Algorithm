#include<iostream>
#include "classes/List.h"
#include "classes/Point.h"
#include "classes/GrahamScan.h"
#include "classes/JarvisMarch.h"

using namespace std;

int main(){

    JarvisMarch jm;
    List<Point> points = make_list("datasets/points.csv");
    jm.fit_set(points);
    List<Point> hull = jm.compute_hull();
    hull.print();
    cout<<endl;
    make_result(hull,"results/results_1.csv");
}
