#ifndef STACK_H
#define STACK_H

#include<iostream>
using namespace std;

template<class T>
class Stack{

    T *arr;
    int capacity;
    int sz;
    int top;

    public:

      Stack<T>(){

        capacity = 100000;
        arr = new T[capacity];
        top = -1;
        sz = 0;
      }
      Stack<T>(int capacity){

        this->capacity = capacity;
        arr = new T[capacity];
        top = -1;
        sz = 0;
      }
      void push(T p_index){

          try{
            if(sz == capacity){
              throw "Stack overflow exception";
            }

            top++;
            sz++;
            arr[top] = p_index;
          }
          catch(const char *msg){

            cout<<msg<<endl;
            exit(0);
          }

      }
      T pop(){

          try{
            if(sz == 0){
              throw "Stack pop exception";
            }

            top--;
            sz--;

            return arr[top+1];
          }
          catch(const char *msg){

            cout<<msg<<endl;
            exit(0);
          }
      }
      T peek(){
        try{
          if(sz == 0){
            throw "Stack top exception";
          }

          return arr[top];
        }
        catch(const char *msg){
          cout<<msg<<endl;
          exit(0);
        }
      }
      int size(){
        return sz;
      }

      bool empty(){

        if(sz == 0) return true;
        else return false;
      }
      void print_stack(){

        for(int i=0;i<sz;i++){
          cout<<arr[i].print()<<" ";
        }
        cout<<endl;
      }
};

#endif
