#include "Iterator.h"

// initializes curr to currIn
Iterator::Iterator(Node *currIn) {
    curr = currIn;
}

// dereference curr, returns plaintext string
const std::string Iterator::operator*() const {
    if (curr == NULL) return "";
    return curr->getWord();
}

// pre-increment operator
Iterator& Iterator::operator++() {
    curr = curr->getNext();
    return *this;
}

// post-increment operator
Iterator Iterator::operator++(int) {
    // make temp iterator
    Iterator temp = *this;
    curr = curr->getNext();
    return temp;
}

// for iterator math
// for example it = it + 2;
Iterator Iterator::operator+(const int & _value) {
    // make temp iterator
    Iterator temp = *this;
    for (int i = 0; i < _value; i++) {
        temp.curr = temp.curr->getNext();
    }
    return temp;
}

// for iterator math
// for example it += 2;
Iterator Iterator::operator+=(const int & _value) {
    for (int i = 0; i < _value; i++) {
        curr = curr->getNext();
    }
    return *this;
}

// pre-decrement operator
Iterator& Iterator::operator--() {
    curr = curr->getPrev();
    return *this;
}

// post-decrement operator
Iterator Iterator::operator--(int) {
    // make temp iterator
    Iterator temp = *this;
    curr = curr->getPrev();
    return temp;
}

// for iterator math
// for example it = it - 2;
Iterator Iterator::operator-(const int & _value) {
    // make temp iterator
    Iterator temp = *this;
    for (int i = 0; i < _value; i++) {
        temp.curr = temp.curr->getPrev();
    }
    return temp;
}

// for iterator math
// for example it -= 2;
Iterator Iterator::operator-=(const int & _value) {
    for (int i = 0; i < _value; i++) {
        curr = curr->getPrev();
    }
    return *this;
}

// equality operator
// is true if 2 iterators are pointing to the same node
bool Iterator::operator==(const Iterator &other) {
    return (curr == other.curr);
}

// inequality operator
// is true if 2 iterators are pointing to different nodes
bool Iterator::operator!=(const Iterator &other) {
    return !(curr == other.curr);
}

// returns the node to which the iterator points
Node *& Iterator::getCurr() {
    return curr;
}
