//
//  assign1
//
//  Created by InJung Chung on 2015. 3. 8..
//  Copyright (c) 2015 InJung Chung. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// Fragment class
class Fragment {
private:
    int mNumZeros;
    unsigned long mSize;
    string mContent;
public:
    Fragment();
    void init(unsigned long, string);
    int getNumZeros();
    unsigned long getSize();
    string getContent();
};

bool canSwap(Fragment, Fragment);
void doSwap(Fragment &, Fragment &);

int main() {
    int uniqueFileNum;
    
    // get number of file trays
    cin >> uniqueFileNum;
    for (int n = -1; n < uniqueFileNum + 1; n++) {
        int index = 0;
        string input;
        Fragment* fragment = new Fragment[288];
        
        // get all file fragments
        do {
            getline(cin, input);
            fragment[index].init(input.length(), input);
            index++;
        } while (input != "");
        index--;
        
        // skip procedure when there is no input
        if (index == 0)
            continue;
        
        // align by length
        for (int i = 0; i < index; i++)
            for (int j = 0; j < i; j++)
                if (canSwap(fragment[j], fragment[i]))
                    doSwap(fragment[j], fragment[i]);
        
        // calculate total size
        int totalZeros = 0;
        if (fragment[0].getNumZeros() == fragment[1].getNumZeros()) {
            totalZeros = (fragment[0].getNumZeros() + fragment[index - 1].getNumZeros() +
                          fragment[1].getNumZeros() + fragment[index - 2].getNumZeros()) / 2;
        } else {
            totalZeros = fragment[0].getNumZeros() + fragment[index - 1].getNumZeros();
        }

        // swap fragments to match right case
        for (int i = 0; i < index / 2; i++) {
            if (fragment[i].getNumZeros() + fragment[index - i - 1].getNumZeros() != totalZeros) {
                if (fragment[i].getSize() == fragment[i + 1].getSize())
                    doSwap(fragment[i], fragment[i + 1]);
                else if (fragment[i].getSize() == fragment[i - 1].getSize())
                    doSwap(fragment[i], fragment[i - 1]);
            }
        }
        
        int answer = 0;
        // able answers
        string output[2] = {fragment[0].getContent() + fragment[index - 1].getContent(),
            fragment[index - 1].getContent() + fragment[0].getContent()};
        
        // find answers
        for (int i = 0; i < index / 2; i++) {
            if (fragment[i].getContent() + fragment[index - i - 1].getContent() == output[1])
                answer++;
            else if (fragment[index - i - 1].getContent() + fragment[i].getContent() == output[1])
                answer++;
            else
                answer--;
        }
        
        // print output
        cout << output[answer > 0 ? 1 : 0] << endl;
        cout << (n == uniqueFileNum ? "" : "\n");
    }
    
    return 0;
}


//  implements of Fragment class
Fragment::Fragment() {
    mNumZeros = 0;
    mSize = 0;
    mContent = "";
}

void Fragment::init(unsigned long _size, string _content) {
    mSize = _size;
    mContent = _content;
    for (int i = 0; i < mContent.size(); i++)
        mNumZeros += mContent[i] == '0' ? 1 : 0;
}

int Fragment::getNumZeros() {
    return mNumZeros;
}

unsigned long Fragment::getSize() {
    return mSize;
}

string Fragment::getContent(){
    return mContent;
}


// check whether can swap or not
bool canSwap(Fragment forward, Fragment backward) {
    return forward.getSize() > backward.getSize();
}

// swap function
void doSwap(Fragment &forward, Fragment &backward) {
    Fragment temp;
    temp = backward;
    backward = forward;
    forward = temp;
}