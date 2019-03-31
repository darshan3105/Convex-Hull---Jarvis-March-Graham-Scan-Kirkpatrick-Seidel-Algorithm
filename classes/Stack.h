#ifndef STACK_H
#define STACK_H

#include<iostream>
using namespace std;

/** Stacks is a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out),
  *  where elements are inserted and extracted only from one end of the container.
 */
template<class T>
class Stack{

    T *arr;
    int capacity;
    int sz;
    int top;

    public:

      /** Contructor.
        * This is the default constructor for the class Stack.It creates a stack with capacity 1000000.
       */
      Stack<T>(){

        capacity = 1000000;
        arr = new T[capacity];
        top = -1;
        sz = 0;
      }
      /** Contructor.
        * It creates a stack with capacity equal to the capacity passed as an argument.
        * @param capacity of type integer. 
       */
      Stack<T>(int capacity){

        this->capacity = capacity;
        arr = new T[capacity];
        top = -1;
        sz = 0;
      }
      /** it pushes the object passed onto the top of the stack.
        * @param accepts an object of type similar to that contained in the stack.
       */
      void push(T p){

          try{
            if(sz == capacity){
              throw "Stack overflow exception";
            }

            top++;
            sz++;
            arr[top] = p;
          }
          catch(const char *msg){

            cout<<msg<<endl;
            exit(0);
          }

      }
      /** pops an element from the top of the stack.
       */
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
      /** returns the element present at the top of the stack.
        * @return returns an object of type similar to that contained in the stack.
       */
      T peek(){
        try{
          if(sz == 0){
            throw "Stack peek exception";
          }

          return arr[top];
        }
        catch(const char *msg){
          cout<<msg<<endl;
          exit(0);
        }
      }
      /** returns the size of the stack.
       */
      int size(){
        return sz;
      }
      /** returns 'true' if the stack is empty else returns 'false'.
        * @return a variable of type bool.
       */
      bool empty(){

        if(sz == 0) return true;
        else return false;
      }
      /** returns the element that is next to the top element in the stack.
        * @return returns an object of type similar to that contained in the stack.
       */
      T next_to_top(){
        try{
          if(sz == 1){
            throw "Stack underflow exception";
          }

          return arr[top-1];
        }
        catch(const char *msg){
          cout<<msg<<endl;
          exit(0);
        }

      }
      /** printd the elements present in the  stack.
       */
      void print(){

        for(int i=0;i<sz;i++){
          cout<<arr[i]<<" ";
        }
        cout<<endl;
      }
};

#endif
