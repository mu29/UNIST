#include "Buffer.h"

// default constructor
// creates empty linked list of count = 0
Buffer::Buffer() {
    count = 0;
    head = NULL;
}

// copy constructor for buffer
// creates a deep copy, of the ll,
// and stores it in other
// calls copy()
Buffer::Buffer(const Buffer & other) {
    copy(other);
}

// destructor
// calls clear();
Buffer::~Buffer() {
    clear();
}

// overloaded assignment operator
// calls copy()
Buffer& Buffer::operator=(const Buffer & original) {
    copy(original);
    return *this;
}

// accessor
// returns the head
Node* Buffer::getHead() {
    return head;
}

// accessor
// returns the tail node
Node* Buffer::getTail() {
    // find tail at front of head
    if (head == NULL) return NULL;
    return head->getPrev();
}

// returns the string in the head node of the ll
// this operation is not valid for an empty ll (i.e. buffer)
// (If it is called on an empty buffer, return an emptry string "".)
std::string Buffer::getHeadElement() {
    if (count == 0) return "";
    return head->getWord();
}

// returns the string in the tail node of the ll
// this operation is not valid for an empty ll  (i.e. buffer)
// (If it is called on an empty buffer, return an emptry string "".)
std::string Buffer::getTailElement() {
    if (count == 0) return "";
    // find tail at front of head
    return head->getPrev()->getWord();
}

// creates a node containing str
// adds the string at the head of the ll
// (i.e. before the current head node)
// after the operation, head node is the newly added one
void Buffer::produceAtHead(const std::string str) {
    // make head node
    head = (head == NULL ? new Node(str) : new Node(str, head->getPrev()));
    count++;
}

// creates a node containing str
// adds the string at the end of the ll
// (i.e. after the current tail node)
void Buffer::produceAtTail(const std::string str) {
    // make tail node
    if (head == NULL) return;
    new Node(str, head->getPrev());
    count++;
}

// inserts Node containing "str" into the ll in front of "pos"
// return an iterator that points to the the newly inserted elements.
// any iterators after pos are considered invalid
Iterator Buffer::produceAtMiddle(Iterator pos, const std::string str) {
    // make node at middle
    Node* node = new Node(str, pos.getCurr()->getPrev());
    Iterator iter(node);
    count++;
    return iter;
}

// buffer must not be empty before calling this
// deletes the first element (i.e. current head node)
void Buffer::consumeAtHead() {
    if (count == 0) return;
    // find next head
    Node* nextHead = head->getNext();
    
    // delete head
    Iterator it(head);
    consume(it);
    head = NULL;
    
    // if not empty, set head
    if (count > 0) head = nextHead;
}

// buffer must not be empty before calling this
// deletes the last element (i.e. current tail node)
void Buffer::consumeAtTail() {
    if (count == 0) return;
    
    // delete tail
    Iterator it(head->getPrev());
    consume(it);
}

// "it" is pointing to the element to be removed
void Buffer::consume(Iterator it) {
    Node* prevNode = it.getCurr()->getPrev();
    Node* nextNode = it.getCurr()->getNext();
    // cut link
    prevNode->setNext(nextNode);
    
    // set prev & next null
    it.getCurr()->setPrev(NULL);
    it.getCurr()->setNext(NULL);
    // delete node
    delete it.getCurr();
    it.getCurr() = NULL;
    
    count--;
    if (count == 0) head = NULL;
}

// erases all nodes in the range [s,t)
// s is erased and all nodes up to but not
// including t are erased
void Buffer::consume(Iterator s, Iterator t) {
    // loop do if s is not equal to t
    while (s.getCurr() != t.getCurr()) {
        // free memory
        consume(s++);
    }
}

// returns the number of elements in the ll
unsigned Buffer::size() const {
    return count;
}

// returns true if the ll is empty, otherwise it returns false
bool Buffer::isEmpty() {
    return (count == 0);
}

// brackets operator allows indexing into the ll
// "fakes" random access to the ith element of the ll
// returns contents of ith element of the ll
// if ll looks like:
// we -> are -> family ->
// then element 2 would be "family"
// remember the first element is the 0th element
std::string& Buffer::operator[](int i) const {
    // make iterator
    Iterator iter(head);
    iter += i;
    return iter.getCurr()->getWord();
}

// returns the iterator pointing to the first node in the ll
Iterator Buffer::getHeadItr() {
    // make head iterator
    Iterator iter(head);
    return iter;
}

// returns an iterator pointing the tail node in ll
Iterator Buffer::getTailItr() {
    // make tail iterator
    Iterator iter(head->getPrev());
    return iter;
}

// returns an iterator of the next node pointed by it
Iterator Buffer::getNextItr(Iterator it) {
    // make next iterator
    Iterator iter(it.getCurr()->getNext());
    return iter;
}

// returns an iterator of the previous node pointed by it
Iterator Buffer::getPrevItr(Iterator it) {
    // make prev iterator
    Iterator iter(it.getCurr()->getPrev());
    return iter;
}

// prints out the ll like the following
// contents of node, followed by a space,
// followed by -> followed by a space
// after list is printed, it skips a line
// ie has 2 endls
// if list is empty, it prints "->" followed by
// 2 endls
void Buffer::print() {
    Iterator iter(head);
    // print head
    std::cout << getHeadElement() << " -> ";
    // print all nodes
    for (int i = 1; i < (count == 0 ? 0 : count - 1); i++) {
        std::cout << (++iter).getCurr()->getWord() << " -> ";
    }
    // if head is not equal to tail
    if (getHead() != getTail())
        std::cout << getTailElement();
    std::cout << std::endl << std::endl;
}


// makes a deep copy of the ll for copy constructor
// and assignment operator
// "other" is copied
void Buffer::copy(const Buffer & other) {
    // copy count
    count = other.count;
    // make iterator
    Iterator iter(other.head);
    // make head
    head = new Node(iter.getCurr()->getWord());
    // copy all nodes
    for (int i = 1; i < count; i++) {
        // add node at tail
        Node* node = new Node((iter + i).getCurr()->getWord(), head->getPrev());
        head->setPrev(node);
    }
}

// clears the ll by deleting all nodes
// calls the recursive function deleteBuffer()
void Buffer::clear() {
    // if there are some nodes, start delete
    if (count > 0)
        deleteBuffer(head->getNext());
}

// recursively deletes the ll p
// THIS FUNCTION MUST BE RECURSIVE
void Buffer::deleteBuffer(Node* p) {
    // if p is equal to head
    if (p == head) {
        // delete head
        Iterator it(p);
        consume(it);
        // finish recursive function
        return;
    }
    
    // delete next node
    deleteBuffer(p->getNext());
    
    // delete self
    Iterator it(p);
    consume(it);
}


// non-member function
// locates "str" in the range [first,last]
// if "str" is found in the range, return true
// if "str" is not found, return false
bool findNode(Iterator first, Iterator last, std::string str) {
    // loop do if first is not equal to last
    while (first.getCurr() != last.getCurr()) {
        if (first.getCurr()->getWord() == str)
            return true;
        first++;
    }
    // check last node
    if (last.getCurr()->getWord() == str)
        return true;
    
    // if there is no match, return false
    return false;
}
