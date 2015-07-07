// Iterator.h
//	circular doubly-linked list iterator class for Buffer

#ifndef ITERATOR
#define ITERATOR

#include <string>
#include "Node.h"

// circular doubly-linked list iterator
class Iterator {
    
private:
    Node *curr;   // points to current node
    
public:
    // initializes curr to currIn
    Iterator(Node *currIn = NULL);
    
    // dereference curr, returns plaintext string
    const std::string operator*() const;
    
    // pre-increment operator
    Iterator& operator++();
    
    // post-increment operator
    Iterator operator++(int);
    
    // for iterator math
    // for example it = it + 2;
    Iterator operator+(const int &);
    
    // for iterator math
    // for example it += 2;
    Iterator operator+=(const int &);
    
    // pre-decrement operator
    Iterator& operator--();
    
    // post-decrement operator
    Iterator operator--(int);
    
    // for iterator math
    // for example it = it - 2;
    Iterator operator-(const int &);
    
    // for iterator math
    // for example it -= 2;
    Iterator operator-=(const int &);
    
    // equality operator
    // is true if 2 iterators are pointing to the same node
    bool operator==(const Iterator &other);
    
    // inequality operator
    // is true if 2 iterators are pointing to different nodes
    bool operator!=(const Iterator &other);
    
    // returns the node to which the iterator points
    Node *& getCurr();
    
private:
    
    // YOU MAY ADD ANY OTHER PRIVATE FUNCTIONS HERE
    Iterator& copy(const Iterator&);
    
};

#endif // ITERATOR
