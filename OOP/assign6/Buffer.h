// Buffer.h
//	a circular, double linked list (ll) of Nodes
//	dynamically resizes
// 	uses iterators to move through the data structure

#ifndef BUFFER_CLASS
#define BUFFER_CLASS

#include <iostream>
#include "Node.h"
#include "Iterator.h"

class Buffer {
private:
    unsigned count;	// the number of actual items in the ll
    Node * head;	// points to the head node
    
public:
    // default constructor
    // creates empty linked list of count = 0
    Buffer();
    
    // copy constructor for buffer
    // creates a deep copy, of the ll,
    // and stores it in other
    // calls copy()
    Buffer(const Buffer & other);
    
    // destructor
    // calls clear();
    ~Buffer();
    
    // overloaded assignment operator
    // calls copy()
    Buffer & operator=(const Buffer & original);
    
    // accessor
    // returns the head
    Node * getHead();
    
    // accessor
    // returns the tail node
    Node * getTail();
    
    // returns the string in the head node of the ll
    // this operation is not valid for an empty ll (i.e. buffer)
    // (If it is called on an empty buffer, return an emptry string "".)
    std::string getHeadElement();
    
    // returns the string in the tail node of the ll
    // this operation is not valid for an empty ll  (i.e. buffer)
    // (If it is called on an empty buffer, return an emptry string "".)
    std::string getTailElement();
    
    // creates a node containing str
    // adds the string at the head of the ll
    // (i.e. before the current head node)
    // after the operation, head node is the newly added one
    void produceAtHead(const std::string str);
    
    // creates a node containing str
    // adds the string at the end of the ll
    // (i.e. after the current tail node)
    void produceAtTail(const std::string str);
    
    // inserts Node containing "str" into the ll in front of "pos"
    // return an iterator that points to the the newly inserted elements.
    // any iterators after pos are considered invalid
    Iterator produceAtMiddle(Iterator pos, const std::string str);
    
    // buffer must not be empty before calling this
    // deletes the first element (i.e. current head node)
    void consumeAtHead();
    
    // buffer must not be empty before calling this
    // deletes the last element (i.e. current tail node)
    void consumeAtTail();
    
    // "it" is pointing to the element to be removed
    void consume(Iterator it);
    
    // erases all nodes in the range [s,t)
    // s is erased and all nodes up to but not
    // including t are erased
    void consume(Iterator s, Iterator t);
    
    // returns the number of elements in the ll
    unsigned size() const;
    
    // returns true if the ll is empty, otherwise it returns false
    bool isEmpty();
    
    // brackets operator allows indexing into the ll
    // "fakes" random access to the ith element of the ll
    // returns contents of ith element of the ll
    // if ll looks like:
    // we -> are -> family ->
    // then element 2 would be "family"
    // remember the first element is the 0th element
    std::string & operator[](int i) const;
    
    // returns the iterator pointing to the first node in the ll
    Iterator getHeadItr();
    
    // returns an iterator pointing the tail node in ll
    Iterator getTailItr();
    
    // returns an iterator of the next node pointed by it
    Iterator getNextItr(Iterator it);
    
    // returns an iterator of the previous node pointed by it
    Iterator getPrevItr(Iterator it);
    
    // prints out the ll like the following
    // contents of node, followed by a space,
    // followed by -> followed by a space
    // after list is printed, it skips a line
    // ie has 2 endls
    // if list is empty, it prints "->" followed by
    // 2 endls
    void print();
    
private:
    
    // makes a deep copy of the ll for copy constructor
    // and assignment operator
    // "other" is copied
    void copy(const Buffer & other);
    
    // clears the ll by deleting all nodes
    // calls the recursive function deleteBuffer()
    void clear();
    
    // recursively deletes the ll p
    // THIS FUNCTION MUST BE RECURSIVE
    void deleteBuffer(Node * p);
    
    // YOU MAY ADD ANY OTHER PRIVATE FUNCTIONS HERE
};

#endif // BUFFER_CLASS

// non-member function
// locates "str" in the range [first,last]
// if "str" is found in the range, return true
// if "str" is not found, return false
bool findNode(Iterator first, Iterator last, std::string str);


