#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include<iostream>

using namespace std;

class Integer{

    int val;
    public:
      Integer(){
        val = 0;
      }
      Integer(int val){
        this->val = val;
      }
      int get(){
        return this->val;
      }
      void set(int x){
        this->val = x;
      }
      void print(){
        cout<<val;
      }
};
class Float{

    float val;
    public:
      Float(){
        val = 0;
      }
      Float(float val){
        this->val = val;
      }
      float get(){
        return this->val;
      }
      void set(float x){
        this->val = x;
      }
      void print(){
        cout<<val;
      }
};
class Double{

    double val;
    public:
      Double(){
        val = 0;
      }
      Double(double val){
        this->val = val;
      }
      double get(){
        return this->val;
      }
      void set(double x){
        this->val = x;
      }
      void print(){
        cout<<val;
      }
};
class Long{

    long val;
    public:
      Long(){
        val = 0;
      }
      Long(long val){
        this->val = val;
      }
      long get(){
        return this->val;
      }
      void set(long x){
        this->val = x;
      }
      void print(){
        cout<<val;
      }
};

#endif
