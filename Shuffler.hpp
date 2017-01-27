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
#include <random>


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
    void Random_Swap_Bad();
    void Random_Swap_Good();
    void Bridge_Shuffle();
    void Shuffle();
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
            stack.at(0).indv.at(i).selected = 0;
            i += 1;
        }
    }
    assert(stack.at(0).indv.size() == pP->num_cards);
}


//-------------------------------------------------------------------------
//Randomly shuffles deck
void Shuffler::Random_Shuffle()
{
    //bad random shuffler
    random_shuffle (stack.at(0).indv.begin(), stack.at(0).indv.end());
}

//-------------------------------------------------------------------------
//Randomly swaps cards in deck (same card can be swapped multiple times)
void Shuffler::Random_Swap_Bad()
{
    //more random shuffler
    for (int i=0; i<pP->num_cards; i++) {
        int r = i + rand() % (pP->num_cards - i); // careful here!
        swap(stack.at(0).indv.at(i), stack.at(0).indv.at(r));
    }
}


//-------------------------------------------------------------------------
//Randomly swaps cards in deck (same card cannot be swapped more than once)
void Shuffler::Random_Swap_Good()
{
    //better random shuffler
    for (int i=0; i<pP->num_cards/2; i++)
    {
        int r1 = rand() % pP->num_cards;
        //cout << r1 << endl;
        while (stack.at(0).indv.at(r1).selected != 0)
        {
            //cout << r1 << endl;
            r1 = rand() % pP->num_cards;
            //cout << r1 << endl;
        }
        stack.at(0).indv.at(r1).selected = 1;
        int r2 = (int)rand() % pP->num_cards;
        while (r2 == r1)
        {
            r2 = (int)rand() % pP->num_cards;
            while (stack.at(0).indv.at(r2).selected != 0)
            {
                //cout << r2 << endl;
                r2 = rand() % pP->num_cards;
                //cout << r2 << endl;
            }
        }
        swap(stack.at(0).indv.at(r1), stack.at(0).indv.at(r2));
    }
    for (int i=0; i<pP->num_cards; i++)
    {
        stack.at(0).indv.at(i).selected = 0;
    }
}


//-------------------------------------------------------------------------
//Performs a true perfect bridge shuffle
void Shuffler::Bridge_Shuffle()
{
    vector<Card> T1;
    vector<Card> T2;
    for (int i=0; i<pP->num_cards/2; i++)
    {
        T1.push_back(stack.at(0).indv.at(i));
        T2.push_back(stack.at(0).indv.at(i+pP->num_cards/2));
    }
    int c= 0;
    stack.at(0).indv.clear();
    for (int i=0; i<pP->num_cards/2; i++)
    {
        if (c % 2 == 0)
        {
            stack.at(0).indv.push_back(T1.at(pP->num_cards/2-(i+1)));
        }
        c += 1;
        if (c % 2 != 0)
        {
            stack.at(0).indv.push_back(T2.at(pP->num_cards/2-(i+1)));
        }
        c += 1;
    }
}


//-------------------------------------------------------------------------
//Shuffles deck
void Shuffler::Shuffle()
{
    if (pP->RS == 1)
    {
        Random_Shuffle();
    }
    if (pP->RSB == 1)
    {
        Random_Swap_Bad();
    }
    if (pP->RSG == 1)
    {
        Random_Swap_Good();
    }
    if (pP->BS == 1)
    {
        Bridge_Shuffle();
    }
    assert(stack.at(0).indv.size() == pP->num_cards);
}


//-------------------------------------------------------------------------
//Outputs deck in order that the cards appear in the vector
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
//Runs the entire card shuffler program
void Shuffler::Run_Shuffler()
{
    int s = 0;
    Build_Deck();
    Display_Deck(s);
    for (int s=1; s<pP->num_shuffle+1; s++)
    {
        Shuffle();
        Display_Deck(s);
    }
}


#endif /* Shuffler_hpp */
