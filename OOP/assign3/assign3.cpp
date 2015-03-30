//
//  assign3
//
//  Created by InJung Chung on 2015. 3. 24..
//  Copyright (c) 2015 InJung Chung. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// poker card type
namespace Poker {
    enum Suit {
        Club,
        Diamond,
        Heart,
        Spade
    };

    enum Value {
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    };
}

// poker card class (contains suit, value)
class Card {
private:
    Poker::Suit suit;
    Poker::Value value;
public:
    int getSuit() {
        return suit;
    }
    
    int getValue() {
        return value;
    }
    
    void set(string val) {
        // set value
        switch (val[0]) {
            case '2': value = Poker::Two; break;
            case '3': value = Poker::Three; break;
            case '4': value = Poker::Four; break;
            case '5': value = Poker::Five; break;
            case '6': value = Poker::Six; break;
            case '7': value = Poker::Seven; break;
            case '8': value = Poker::Eight; break;
            case '9': value = Poker::Nine; break;
            case 'T': value = Poker::Ten; break;
            case 'J': value = Poker::Jack; break;
            case 'Q': value = Poker::Queen; break;
            case 'K': value = Poker::King; break;
            case 'A': value = Poker::Ace; break;
        }
        // set suit
        switch (val[1]) {
            case 'C': suit = Poker::Club; break;
            case 'D': suit = Poker::Diamond; break;
            case 'H': suit = Poker::Heart; break;
            case 'S': suit = Poker::Spade; break;
        }
    }
};

// get input and return true if it is not eof and blank line
bool GetInput(string &input) {
    // if eof
    if (!getline(cin, input))
        return false;
    
    // if blank line
    if (input == "")
        return false;
    
    return true;
}

// divide text by empty space. then delete used string
void GetDividedText(string &text, string dividedText[5]) {
    int index = 0;
    int marker = 0;
    for (int i = 0; i < text.size(); i++) {
        // if empty space
        if (text[i] == ' ') {
            // slice it
            dividedText[index] = text.substr(marker, i - marker);
            // set marker
            marker = i + 1;
            index++;
            // break when make 5 divided texts
            if (index == 5) break;
        }
    }
    // delete used string
    text = text.substr(marker, text.size() - marker);
}

// align elements of array by order
void AlignArray(int *list, int size = 5) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[i]) {
                int temp = list[j];
                list[j] = list[i];
                list[i] = temp;
            }
        }
    }
}

// get hightest value
int GetHighest(Card cards[5]) {
    int highest = 0;
    for (int i = 0; i < 5; i++) {
        // put card value into highest variable if it is bigger
        if (cards[i].getValue() > highest)
            highest = cards[i].getValue();
    }
    
    return highest;
}

// check if pair
bool IsPair(Card cards[5], int &rank) {
    int count = 0;
    int values[13] = {0, };
    // add values
    for (int i = 0; i < 5; i++) {
        values[cards[i].getValue()]++;
    }
    
    for (int i = 0; i < 13; i++) {
        // if there is pair
        if (values[i] == 2) {
            rank = i;
            count++;
        }
    }
    
    return (count == 1);
}

// check if two pair
bool IsTwoPair(Card cards[5], int &rank, int &rank2, int &rank3) {
    int count = 0;
    int values[13] = {0, };
    rank2 = -1;
    // add values
    for (int i = 0; i < 5; i++) {
        values[cards[i].getValue()]++;
    }
    
    for (int i = 0; i < 13; i++) {
        // if there is pair
        if (values[i] == 2) {
            count++;
            // set rank by order
            if (rank2 != -1)
                rank = i;
            else
                rank2 = i;
        } else if (values[i] == 1)
            rank3 = i;
    }
    return (count == 2);
}

// check if triple
bool IsTriple(Card cards[5], int &rank) {
    int values[13] = {0, };
    // add values
    for (int i = 0; i < 5; i++) {
        values[cards[i].getValue()]++;
    }
    
    for (int i = 0; i < 13; i++) {
        if (values[i] == 3) {
            // if there is triple
            rank = i;
            return true;
        }
    }
    
    return false;
}

// check if straight
bool IsStraight(Card cards[5], int &rank) {
    // check if cards are consecutive
    int cardValues[5];
    // save card values
    for (int i = 0; i < 5; i++)
        cardValues[i] = cards[i].getValue();
    
    // align array by order
    AlignArray(cardValues);
    int value = -1;
    for (int i = 0; i < 5; i++) {
        value = (value == -1 ? cardValues[i] : value);
        // if not consecutive, return false
        if (cardValues[i] != value + i)
            return false;
    }
    
    // set rank
    rank = cardValues[4];
    // it is straight!
    return true;
}

// check if flush
bool IsFlush(Card cards[5], int &rank) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        // add count if two cards have same suit
        if (cards[i].getSuit() == cards[(i + 1) % 5].getSuit())
            count++;
    }
    
    // set rank
    rank = GetHighest(cards);
    // return result
    return (count == 5);
}

// check if full house
bool IsFullHouse(Card cards[5], int &rank) {
    // check triple & pair. set temp value at pair rank
    int temp;
    return (IsTriple(cards, rank) && IsPair(cards, temp));
}

// check if four card
bool IsFourCard(Card cards[5], int &rank) {
    int values[13] = {0, };
    // set value
    for (int i = 0; i < 5; i++) {
        values[cards[i].getValue()]++;
    }
    
    for (int i = 0; i < 13; i++) {
        if (values[i] == 4) {
            // if there is four card
            rank = i;
            return true;
        }
    }
    
    return false;
}

// check if straight flush
bool IsStraightFlush(Card cards[5], int &rank) {
    // check straight & flush. set temp value at flush rank
    int temp;
    return (IsFlush(cards, temp) && IsStraight(cards, rank));
}

// check hand
int Check(Card cards[5], int &rank, int &rank2, int &rank3) {
    if (IsStraightFlush(cards, rank))
        return 8;
    else if (IsFourCard(cards, rank))
        return 7;
    else if (IsFullHouse(cards, rank))
        return 6;
    else if (IsFlush(cards, rank))
        return 5;
    else if (IsStraight(cards, rank))
        return 4;
    else if (IsTriple(cards, rank))
        return 3;
    else if (IsTwoPair(cards, rank, rank2, rank3))
        return 2;
    else if (IsPair(cards, rank))
        return 1;
    
    rank = GetHighest(cards);
    return 0;
}

int main() {
    string input;
    
    // do loop
    while (GetInput(input)) {
        input += " ";
        // black and white card
        Card blackCards[5];
        Card whiteCards[5];
        string blackCardList[5];
        string whiteCardList[5];
        // get divided text (black first)
        GetDividedText(input, blackCardList);
        GetDividedText(input, whiteCardList);
        // set card values
        for (int i = 0; i < 5; i++) {
            blackCards[i].set(blackCardList[i]);
            whiteCards[i].set(whiteCardList[i]);
        }
        
        // rank variables. 2 and 3 is for two pair
        int blackRank = 0;
        int blackRank2 = 0;
        int blackRank3 = 0;
        int whiteRank = 0;
        int whiteRank2 = 0;
        int whiteRank3 = 0;
        // check hand
        int blackHand = Check(blackCards, blackRank, blackRank2, blackRank3);
        int whiteHand = Check(whiteCards, whiteRank, whiteRank2, whiteRank3);
         
        if (blackHand > whiteHand)
            cout << "Black wins." << endl;
        else if (whiteHand > blackHand)
            cout << "White wins." << endl;
        else {
            // if hands are same, check rank
            if (blackRank > whiteRank)
                cout << "Black wins." << endl;
            else if (whiteRank > blackRank)
                cout << "White wins." << endl;
            else if (blackHand == 5) {
                // if flush, check like high card
                bool isTie = true;
                int blackHighValues[5];
                int whiteHighValues[5];
                // save card values
                for (int i = 0; i < 5; i++) {
                    blackHighValues[i] = blackCards[i].getValue();
                    whiteHighValues[i] = whiteCards[i].getValue();
                }
                // align array by order
                AlignArray(blackHighValues);
                AlignArray(whiteHighValues);
                for (int i = 4; i >= 0; i--) {
                    if (blackHighValues[i] > whiteHighValues[i]) {
                        cout << "Black wins." << endl;
                        isTie = false;
                        break;
                    }
                    else if (whiteHighValues[i] > blackHighValues[i]) {
                        cout << "White wins." << endl;
                        isTie = false;
                        break;
                    }
                }
                if (isTie)
                    cout << "Tie." << endl;
            } else if (blackHand == 2) {
                // if two pair, check rank 2 and 3
                if (blackRank2 > whiteRank2)
                    cout << "Black wins." << endl;
                else if (whiteRank2 > blackRank2)
                    cout << "White wins." << endl;
                else {
                    if (blackRank3 > whiteRank3)
                        cout << "Black wins." << endl;
                    else if (whiteRank3 > blackRank3)
                        cout << "White wins." << endl;
                    else
                        cout << "Tie." << endl;
                }
            } else if (blackHand == 1) {
                // if pair, check like high card except pair value
                bool isTie = true;
                int blackHighValues[3];
                int whiteHighValues[3];
                // save card values
                int n = 0;
                for (int i = 0; i < 5; i++) {
                    if (blackCards[i].getValue() != blackRank) {
                        blackHighValues[n] = blackCards[i].getValue();
                        n++;
                    }
                }
                n = 0;
                for (int i = 0; i < 5; i++) {
                    if (whiteCards[i].getValue() != whiteRank) {
                        whiteHighValues[n] = whiteCards[i].getValue();
                        n++;
                    }
                }
                
                // align array by order
                AlignArray(blackHighValues, 3);
                AlignArray(whiteHighValues, 3);
                for (int i = 2; i >= 0; i--) {
                    if (blackHighValues[i] > whiteHighValues[i]) {
                        cout << "Black wins." << endl;
                        isTie = false;
                        break;
                    }
                    else if (whiteHighValues[i] > blackHighValues[i]) {
                        cout << "White wins." << endl;
                        isTie = false;
                        break;
                    }
                }
                if (isTie)
                    cout << "Tie." << endl;
            }
            else if (blackHand == 0) {
                // if high card and rank is same, check other cards
                bool isTie = true;
                int blackHighValues[5];
                int whiteHighValues[5];
                // save card values
                for (int i = 0; i < 5; i++) {
                    blackHighValues[i] = blackCards[i].getValue();
                    whiteHighValues[i] = whiteCards[i].getValue();
                }
                // align array
                AlignArray(blackHighValues);
                AlignArray(whiteHighValues);
                for (int i = 4; i >= 0; i--) {
                    if (blackHighValues[i] > whiteHighValues[i]) {
                        cout << "Black wins." << endl;
                        isTie = false;
                        break;
                    }
                    else if (whiteHighValues[i] > blackHighValues[i]) {
                        cout << "White wins." << endl;
                        isTie = false;
                        break;
                    }
                }
                if (isTie)
                    cout << "Tie." << endl;
            }
            else
                cout << "Tie." << endl;
        }
    }
    
    return 0;
}
