#ifndef LIST_H
#define LIST_H

#include<iostream>
using namespace std;

template<class T>
class List{

    T *arr;
    int sz;
    int capacity;

    public:
      List<T>(){

        arr = new T[100000];
        capacity = 100000;
        sz = 0;
      }
      List<T>(int capacity){
        arr = new T[capacity];
        this->capacity = capacity;
        sz = 0;
      }
      void add(T t){
          arr[sz] = t;
          sz++;
      }
      T get(int index){
          T t = arr[index];
          return t;
      }
      void edit(int index,T val){
          arr[index] = val;
      }
      int size(){
        return sz;
      }
      void remove(){
        sz--;
      }
      void swap(int i1,int i2){

        T temp;
        temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
      }
      void reverse(){

        for(int i=0;i<sz/2;i++){

          T temp;
          temp = arr[i];
          arr[i] = arr[sz-i-1];
          arr[sz-i-1] = temp;
        }
      }
      void print(){

        for(int i=0;i<sz;i++){
          arr[i].print();
          cout<<" ";
        }
      }

};

#endif
