#ifndef LIST_H
#define LIST_H

#include<iostream>
using namespace std;

/** List is a sequence container for storing objects.
 */

template<class T>
class List{

    T *arr;
    int sz;
    int capacity;

    public:
      /** Contructor.
        * This is the default constructor for the class List.It creates a list with capacity 1000000.
       */
      List<T>(){

        arr = new T[1000000];
        capacity = 1000000;
        sz = 0;
      }
      /** Contructor.
        * It creates a list with capacity equal to the capacity passed as an argument.
        * @param capacity of type integer.
       */
      List<T>(int capacity){
        arr = new T[capacity];
        this->capacity = capacity;
        sz = 0;
      }
      /** appends the object passed, to the end of the list.
        * @param accepts an object of the type contained by the invoking list.
       */
      void add(T t){
          arr[sz] = t;
          sz++;
      }
      /** appends a list passed, to the end of the list.
        * @param accepts a list of type similar to the invoking list.
       */
      void append_list(List<T> list){
        for(int i=0;i<list.size();i++){
          T temp = list.get(i);
          add(temp);
        }
      }
      /** returns the object in the list at the index passed to the function.
        * @param accepts an integer argument i.e the index of the object.
        * @return returns the object at the index.
       */
      T get(int index){
          T t = arr[index];
          return t;
      }
      /** accepts two arguments, index and an object,and changes the object present at the index passed to the new object.
        * @param accepts integer value index.
        * @param accepts an object of type similar to that contained in the invoking list.
       */
      void edit(int index,T val){
          arr[index] = val;
      }
      /** returns the size of the list.
       */
      int size(){
        return sz;
      }
      /** removes the last element present in the list.
       */
      void remove(){
        sz--;
      }
      /** removes all elements present in the list.
       */
      void clear(){
        sz = 0;
      }
      /** accepts two integer indices and swaps the objects present at those indices.
        * @param an integer(first index).
        * @param an integer(second index).
       */
      void swap(int i1,int i2){

        T temp;
        temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
      }
      /** reverses the list.
       */
      void reverse(){

        for(int i=0;i<sz/2;i++){

          T temp;
          temp = arr[i];
          arr[i] = arr[sz-i-1];
          arr[sz-i-1] = temp;
        }
      }
      /** returns a pointer to the first element of the list.
       */
      T* begin(){
        return &arr[0];
      }
      /** returns a pointer to the index one greater than the last element in the list.
       */
      T* end(){
        return &arr[sz];
      }
      /** prints the elements present in the list.
       */
      void print(){

        for(int i=0;i<sz;i++){
          arr[i].print();
          cout<<" ";
        }
      }

};

#endif
