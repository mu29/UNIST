// Node.h
// 	node for your double linked circular list

#ifndef NODE_CLASS
#define NODE_CLASS

#include <string>

class Node{
private:
    std::string word;
    Node *next;
    Node *prev;
    
public:
    // default constructor
    Node();
    
    // constructor with single argument
    Node(std::string);
    
    // constructor with 2 arguments
    // 2nd argument is a pointer to prev node
    // primary constructor
    Node(std::string, Node *);
    
    // accessor for word
    // returns contents of word
    std::string& getWord();
    
    // accessor for next
    // returns pointer to node to which next is pointing
    Node *getNext() const;
    
    // accessor for next
    // returns pointer to node to which prev is pointing
    Node *getPrev() const;
    
    // mutator for word
    // changes string to value passed in
    void setWord(std::string);
    
    // mutator for next
    // changes pointer to value passed in
    void setNext(Node *);
    
    // mutator for prev
    // changes pointer to value passed in
    void setPrev(Node *);
    
private:
    
    // YOU MAY ADD ANY OTHER PRIVATE FUNCTIONS HERE
};

#endif // NODE_CLASS
