//
//  assign2
//
//  Created by InJung Chung on 2015. 3. 11..
//  Copyright (c) 2015 InJung Chung. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
const string plainText = "the quick brown fox jumps over the lazy dog";

int getCases(string*);
bool isMatchWithPlain(string);
void findKeys(char*, string);

int main() {
    // get number of files
    int fileNum;
    cin >> fileNum;
    
    for (int n = -1; n < fileNum + 1; n++) {
        char keys[26];
        string encryptedText[100];
        bool keyEnable = false;
        
        // get all cases divided by blank line and its count
        int count = getCases(encryptedText);
        if (count == 0) continue;
        
        // find match case and keys
        for (int k = 0; k < count; k++) {
            if (isMatchWithPlain(encryptedText[k])) {
                findKeys(keys, encryptedText[k]);
                keyEnable = true;
                break;
            }
        }
        
        // decrypt text
        if (keyEnable) {
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < encryptedText[i].size(); j++) {
                    if (encryptedText[i][j] == ' ')
                        continue;
                    
                    encryptedText[i][j] = keys[encryptedText[i][j] - 97];
                }
                cout << encryptedText[i] << endl;
            }
        } else {
            // if there is no solution
            cout << "No Solution." << endl;
        }
        if (n < fileNum) cout << endl;
    }
    
    return 0;
}

// get all cases
int getCases(string* cryptos) {
    string input;
    int index = 0;
    do {
        getline(cin, input);
        cryptos[index] = input;
        index++;
    } while (input != "");
    index--;
    
    return index;
}

// check if encrypted text is match with plain text
bool isMatchWithPlain(string encryptedText) {
    string shortText = encryptedText.size() > plainText.size() ? plainText : encryptedText;
    for (int i = 0; i < shortText.size(); i++) {
        if (encryptedText[i] == ' ' && plainText[i] != ' ')
            return false;
        if (plainText[i] == ' ' && encryptedText[i] != ' ')
            return false;
    }
    
    if (encryptedText.size() != plainText.size())
        return false;
    
    return true;
}

// find keys by comparing encrypted text and plain text
void findKeys(char *keys, string encryptedText) {
    for (int i = 0; i < encryptedText.size(); i++) {
        if (encryptedText[i] == ' ')
            continue;
        
        keys[encryptedText[i] - 97] = plainText[i];
    }
}