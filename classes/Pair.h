#ifndef PAIR_H
#define PAIR_H

#include<iostream>
using namespace std;

template<class S,class T>
class Pair{

    S first;
    T second;

  public:
    Pair<S,T>(){
      this->first = S();
      this->second = T();
    }
    Pair<S,T>(S first,T second){
      this->first = first;
      this->second = second;
    }
     void make_pair(S first,T second){
       this->first = first;
       this->second = second;
     }
     void print(){

       cout<<"(";
       first.print();
       cout<<",";
       second.print();
       cout<<")";
     }
     S get_first(){
       return first;
     }
     T get_second(){
       return second;
     }
};
#endif
