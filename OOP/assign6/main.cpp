// main.cpp
//	g++ main.cpp Buffer.cpp Node.cpp Iterator.cpp

#include <iostream>
#include "Buffer.h"
#include "Iterator.h"

using namespace std;

int main() {
    Buffer v1;
    Iterator it;
    
    v1.produceAtHead("Is");
    v1.produceAtHead("Name");
    v1.produceAtHead("My");
    v1.produceAtTail("James");
    v1.produceAtTail("Bond");
    
    v1.produceAtTail("My");
    v1.produceAtTail("Name");
    v1.produceAtTail("Is");
    v1.produceAtTail("James");
    v1.produceAtTail("Bond");
    // My -> Name -> Is -> James -> Bond -> My -> Name -> Is -> James -> Bond
    v1.print();
    
    v1.consumeAtHead();
    it = v1.getHeadItr();
    it = v1.getNextItr(it);
    v1.consume(it, it + 3);
    v1.consumeAtTail();
    // Name -> My -> Name -> Is -> James
    v1.print();
    
    // insert in middle
    it = v1.getTailItr();
    it = v1.produceAtMiddle(it, "Porter");
    // Name -> My -> Name -> Is -> Porter -> James
    v1.print();
    
    return 0;
}
