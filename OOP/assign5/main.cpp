//
//  ExtendableArray.cpp
//  assign5
//
//  Created by InJung Chung on 2015. 4. 26..
//  Copyright (c) 2015 InJung Chung. All rights reserved.
//

#include "ExtendableArray.h" 
#include <iostream>
using namespace std;
void stuff_20(ExtendableArray arr) {
    for (int i = 0; i < 20; i++) {
        arr[i] = i;
    }
    
    cout << arr << endl; // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
}
int main() {
    ExtendableArray a1;
    a1[26] = 10;
    cout << a1 << endl;
    
    ExtendableArray a2;
    a2[4] = a1[26];
    a2[8] = 20;
    cout << a2 << endl;
    
    ExtendableArray a3;
    a3 = a2;
    for (int i = 0; i < 10; i++) {
        a3[i + 10] = i;
    }
    cout << a3 << endl;
    /*
    ExtendableArray a1;
    for (int i=0;i<20;i++) {
        a1[i] = i;
    }
    cout << a1 << endl; //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
    
    if(1){
        ExtendableArray a2;
        for (int i = 0; i < 10; i++)
            a2[i + 5] = a1[i];
        cout << a2 << endl; //0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
    
        a1 = a2;
        for (int i=0;i<10;i++)
            a2[i] = i;
        
        cout << a1 << endl; //0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
        cout << a2 <<endl; //0 1 2 3 4 5 6 7 8 9 5 6 7 8 9
    }
    
    cout << a1 << endl; //0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
    
    ExtendableArray a3;
    a3[0] = 1;
    cout << a3 << endl; // 1 0
    
    stuff_20(a3);
    cout << a3 << endl; // 1 0
    cout << a3[2147483647] << endl; // 0
    */
    return 0;
}
