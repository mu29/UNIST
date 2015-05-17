//
//  ExtendableArray.cpp
//  assign5
//
//  Created by InJung Chung on 2015. 4. 26..
//  Copyright (c) 2015 InJung Chung. All rights reserved.
//

#include "ExtendableArray.h"
#include <iostream>
#include <cmath>

// ElementRef constructor
ElementRef::ElementRef(ExtendableArray& theArray, int i) {
    intArrayRef = &theArray;
    index = i;
}

// ElementRef copy constructor
ElementRef::ElementRef(const ElementRef& other) {
    intArrayRef = other.intArrayRef;
    index = other.index;
}

// ElementRef destructor
ElementRef::~ElementRef() {
    intArrayRef = NULL;
}

// operator implement
ElementRef& ElementRef::operator=(const ElementRef& rhs) {
    // if rhs is equal to self
    if (this == &rhs) return *this;
    
    // calculate log to determine whether need to extend its size
    int logIndex = (int)(log(index) / log(2));
    int logSize = (int)(log(intArrayRef->size - 1) / log(2));
    
    // when need to extend its size
    if (index > 1 && logIndex >= logSize + 1) {
        // calculate new size (n power of 2)
        int new_size = (int)pow(2.0, logIndex + 1);
        // make temp variable
        int *temp = new int[intArrayRef->size];
        // copy all values
        for (int n = 0; n < intArrayRef->size; n++) {
            temp[n] = intArrayRef->arrayPointer[n];
        }
        // delete arrayPointer
        delete[] intArrayRef->arrayPointer;
        // allocate arrayPointer
        intArrayRef->arrayPointer = new int[new_size];
        // restore all values
        for (int n = 0; n < intArrayRef->size; n++) {
            intArrayRef->arrayPointer[n] = temp[n];
        }
        // delete temp
        delete[] temp;
        // set 0 to variables which do not have values
        for (int n = intArrayRef->size; n < new_size; n++) {
            intArrayRef->arrayPointer[n] = 0;
        }
    }
    
    // assign value
    *(intArrayRef->arrayPointer + index) = *(rhs.intArrayRef->arrayPointer + rhs.index);
    // set size
    if (index >= intArrayRef->size)
        intArrayRef->size = index + 1;
    
    // return self
    return *this;
}

// operator implement
ElementRef& ElementRef::operator=(int val) {
    // calculate log to determine whether need to extend its size
    int logIndex = (int)(log(index) / log(2));
    int logSize = (int)(log(intArrayRef->size - 1) / log(2));
    
    // when need to extend its size
    if (index > 1 && logIndex >= logSize + 1) {
        // calculate new size (n power of 2)
        int new_size = (int)pow(2.0, logIndex + 1);
        // make temp variable
        int *temp = new int[intArrayRef->size];
        // copy all values
        for (int n = 0; n < intArrayRef->size; n++) {
            temp[n] = intArrayRef->arrayPointer[n];
        }
        // delete arrayPointer
        delete[] intArrayRef->arrayPointer;
        // allocate arrayPointer
        intArrayRef->arrayPointer = new int[new_size];
        // restore all values
        for (int n = 0; n < intArrayRef->size; n++) {
            intArrayRef->arrayPointer[n] = temp[n];
        }
        // delete temp
        delete[] temp;
        // set 0 to variables which do not have values
        for (int n = intArrayRef->size; n < new_size; n++) {
            intArrayRef->arrayPointer[n] = 0;
        }
    }
    
    // assign value
    *(intArrayRef->arrayPointer + index) = val;
    // set size
    if (index >= intArrayRef->size)
        intArrayRef->size = index + 1;
    
    // return self
    return *this;
}

// type convert
ElementRef::operator int() const {
    // if index require variables that is out of bound, return 0
    if (index >= intArrayRef->size)
        return 0;
    
    // return variables
    return *(intArrayRef->arrayPointer + index);
}

// ExtendableArray constructor
ExtendableArray::ExtendableArray() {
    // allocate memory
    arrayPointer = new int[2];
    // set value as 0
    arrayPointer[0] = arrayPointer[1] = 0;
    size = 2;
}

// ExtendableArray copy constructor
ExtendableArray::ExtendableArray(const ExtendableArray& other) {
    // copy size
    size = other.size;
    // allocate memory
    arrayPointer = new int[size];
    // copy all values
    for (int i = 0; i < other.size; i++) {
        arrayPointer[i] = other.arrayPointer[i];
    }
}

// ExtendableArray destructor
ExtendableArray::~ExtendableArray() {
    delete[] arrayPointer;
    arrayPointer = NULL;
}

// assign operator implement
ExtendableArray& ExtendableArray::operator=(const ExtendableArray& rhs) {
    // if rhs is equal to self
    if (this == &rhs) return *this;
    
    // delete arrayPointer
    delete[] arrayPointer;
    // copy size
    size = rhs.size;
    // calculate new size
    int new_size = (int)pow(2.0, (int)(log(size - 1) / log(2)) + 1);
    // allocate memory
    arrayPointer = new int[new_size];
    // copy all values
    for (int i = 0; i < rhs.size; i++) {
        arrayPointer[i] = rhs.arrayPointer[i];
    }
    // set 0 to variables which do not have values
    for (int i = size; i < new_size; i++) {
        arrayPointer[i] = 0;
    }
    
    return *this;
}

// operator implement
ElementRef ExtendableArray::operator[](int i) {
    // create ElementRef object to check lvalue/rvalue
    ElementRef ref = *new ElementRef(*this, i);
    return ref;
}
