//
//  Shuffler.hpp
//  SF_Card_Shuffler_Project
//
//  Created by Scott S Forer on 1/24/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Shuffler_hpp
#define Shuffler_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <ctime>


using namespace std;


class Shuffler
{
    friend class Parameters;
    friend class Deck;
    friend class Card;
    
protected:
    
    
public:
    Parameters* pP;
    
    
    vector<Deck> stack;
    void Build_Deck();
    void Random_Shuffle();
    void Run_Shuffler();
    void Display_Deck(int s);
    
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Builds population of individuals
void Shuffler::Build_Deck()
{
    Deck D;
    stack.push_back(D);
    int i = 0;
    for (int c=1; c<pP->num_cards/4+1; c++)
    {
        //number of suites
        for (int s=0; s<4; s++)
        {
            Card C;
            stack.at(0).indv.push_back(C);
            stack.at(0).indv.at(i).card_num = c;
            stack.at(0).indv.at(i).suit = s;
            i += 1;
        }
    }
    assert(stack.at(0).indv.size() == pP->num_cards);
}


//-------------------------------------------------------------------------
//Shuffles deck
void Shuffler::Random_Shuffle()
{
    random_shuffle (stack.at(0).indv.begin(), stack.at(0).indv.end());
}


//-------------------------------------------------------------------------
//Outputs deck in order
void Shuffler::Display_Deck(int s)
{
    cout << "------------------------------------------------------" << endl;
    if (s == 0)
    {
        cout << "Intial Order" << endl;
    }
    else
    {
        cout << "Shuffle" << "\t" << s << endl;
    }
    cout << "Card" << "\t" << "Suit" << endl;
    for (int i=0; i<pP->num_cards; i++)
    {
        if (stack.at(0).indv.at(i).card_num == 1)
        {
            cout << "Ace" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num == 11)
        {
            cout << "Jack" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num == 12)
        {
            cout << "Queen" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num == 13)
        {
            cout << "King" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num !=1)
        {
            if (stack.at(0).indv.at(i).card_num != 11)
            {
                if (stack.at(0).indv.at(i).card_num != 12)
                {
                    if (stack.at(0).indv.at(i).card_num != 13)
                    {
                        cout << stack.at(0).indv.at(i).card_num << "\t";
                    }
                }
            }
        }
        if (stack.at(0).indv.at(i).suit == 0)
        {
            cout << "Heart" << "\t";
        }
        if (stack.at(0).indv.at(i).suit == 1)
        {
            cout << "Diamond" << "\t";
        }
        if (stack.at(0).indv.at(i).suit == 2)
        {
            cout << "Spade" << "\t";
        }
        if (stack.at(0).indv.at(i).suit == 3)
        {
            cout << "Club" << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


//-------------------------------------------------------------------------
//Builds population of individuals
void Shuffler::Run_Shuffler()
{
    int s = 0;
    Build_Deck();
    Display_Deck(s);
    for (int s=1; s<pP->num_shuffle+1; s++)
    {
        Random_Shuffle();
        Display_Deck(s);
    }
}


#endif /* Shuffler_hpp */
