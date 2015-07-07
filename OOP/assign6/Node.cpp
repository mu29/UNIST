#include "Node.h"

// default constructor
Node::Node() {
    word = "";
    // set next & prev to self
    next = this;
    prev = this;
}

// constructor with single argument
Node::Node(std::string _value) {
    word = _value;
    // set next & prev to self
    next = this;
    prev = this;
}

// constructor with 2 arguments
// 2nd argument is a pointer to prev node
// primary constructor
Node::Node(std::string _value, Node* _prev) {
    word = _value;
    // set next & prev
    Node* nextNode = _prev->next;
    next = nextNode;
    nextNode->prev = this;
    prev = _prev;
    _prev->next = this;
}

// accessor for word
// returns contents of word
std::string& Node::getWord() {
    return word;
}

// accessor for next
// returns pointer to node to which next is pointing
Node* Node::getNext() const {
    return next;
}

// accessor for next
// returns pointer to node to which prev is pointing
Node* Node::getPrev() const {
    return prev;
}

// mutator for word
// changes string to value passed in
void Node::setWord(std::string _value) {
    word = _value;
}

// mutator for next
// changes pointer to value passed in
void Node::setNext(Node* _next) {
    next = _next;
    if (_next != NULL)
        _next->prev = this;
}

// mutator for prev
// changes pointer to value passed in
void Node::setPrev(Node* _prev) {
    prev = _prev;
    if (_prev != NULL)
        _prev->next = this;
}
