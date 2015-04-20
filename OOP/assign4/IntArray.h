//
//  IntArray.h
//  assign4
//
//  Created by InJung Chung on 2015. 3. 30..
//  Copyright (c) 2015 InJung Chung. All rights reserved.
//
//
//  If I put 0, 1, 2, 3, 4, 5 to IntArray, then
//
//  - - - 5 4 3 2 1 0
//        |
//  here is marker(4)
//  nelements = 6
//  total allocated size : marker + nelements = 10
//

// FILO
#include <iostream>
#include <stdlib.h>
using namespace std;
const int DEFAUlT_SIZE = 5;

class IntArray{
private:
    int marker;
    int nelements;
    int *elements;
    
public:
    // default constructor
    IntArray() {
        // initialize variables
        elements = new int[DEFAUlT_SIZE];
        nelements = 0;
        marker = DEFAUlT_SIZE;
    }
    
    // copy constructor
    IntArray(IntArray& array) {
        // copy array's nelements, elements, and marker
        elements = new int[array.nelements + array.marker];
        nelements = array.nelements;
        marker = array.marker;
        for (int i = marker; i < marker + nelements; i++) {
            elements[i] = array.elements[i];
        }
    }
    
    // destructor
    ~IntArray() {
        delete[] elements;
    }
    
    // remove first element and pull every element by one index
    int pop() {
        // and it works like 'pull every element by one index' with less effort
        nelements--;
        marker++;
        // return removed elements
        return elements[marker - 1];
    }
    
    // check if empty
    bool empty() const {
        return nelements == 0;
    }
    
    // returns the first element of array
    int top() const {
        if (empty()) {
            cout << "Error: invalid memory" << endl;
            exit(1);
        }
        
        return elements[marker];
    }
    
    // push one element at the first of array
    void push(int _value) {
        // if array is full, reallocate
        if (marker == 0) {
            // copy to temp variables
            int *temp = new int[nelements];
            for (int i = 0; i < nelements; i++) {
                temp[i] = elements[i];
            }
            
            // reallocate array
            delete[] elements;
            elements = new int[nelements + DEFAUlT_SIZE];
            for (int i = DEFAUlT_SIZE; i < nelements + DEFAUlT_SIZE; i++) {
                elements[i] = temp[i - DEFAUlT_SIZE];
            }
            
            // delete temp variables and set marker
            delete[] temp;
            marker = DEFAUlT_SIZE;
        }
        
        // marker moves forward and put elements
        elements[--marker] = _value;
        // add 1 to nelements
        nelements++;
    }
    
    // return selected index of elements
    int& operator[](int _index) {
        // error handling
        if (_index >= nelements || _index < 0) {
            cout << "Error: invalid memory access" << endl;
            exit(1);
        }
        
        return elements[marker + _index];
    }
    
    // copy array at the end of elements
    void appendCopyAtEnd(const IntArray& array) {
        // copy to temp variables
        int *temp = new int[nelements];
        for (int i = 0; i < nelements; i++) {
            temp[i] = elements[marker + i];
        }
        
        // reallocate array
        delete[] elements;
        elements = new int[nelements + marker + array.nelements];
        for (int i = 0; i < nelements; i++) {
            elements[marker + i] = temp[i];
        }
        
        // start append
        delete[] temp;
        for (int i = 0; i < array.nelements; i++) {
            elements[marker + nelements + i] = array.elements[array.marker + i];
        }
        // set nelements
        nelements += array.nelements;
    }
    
    void operator=(const IntArray& array) {
        // reuse existing memory when possible
        if (nelements + marker < array.nelements + array.marker) {
            // reallocate array
            delete[] elements;
            elements = new int[array.nelements + array.marker];
        }
        // set variables
        nelements = array.nelements;
        marker = array.marker;
        // start copy
        for (int i = marker; i < marker + nelements; i++) {
            elements[i] = array.elements[i];
        }
    }
    
    friend ostream& operator<<(ostream& os, const IntArray& arg) {
        for (int i = 0; i < arg.nelements; i++) {
            // fix : i -> arg.marker + i
            os << arg.elements[arg.marker + i] << ' ';
        }
        return os;
    }
};
