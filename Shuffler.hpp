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
    void Check_Num_Cards();
    void Test_A();
    void Test_B();
    void Run_Test_Functions();
    void Shuffle();
    void Run_Shuffler();
    void Display_Deck(int s);
    void Write_Deck_To_File(int s);
    
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Builds population of individuals
void Shuffler::Build_Deck()
{
    for (int d=0; d<pP->num_decks; d++)
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
                stack.at(d).indv.push_back(C);
                stack.at(d).indv.at(i).card_num = c;
                stack.at(d).indv.at(i).suit = s;
                stack.at(d).indv.at(i).selected = 0;
                i += 1;
            }
        }
    }
    //combines multiple decks together
    if (pP->num_decks>1)
    {
        for (int d=1; d<pP->num_decks; d++)
        {
            for (int i=0; i<pP->num_cards; i++)
            {
                stack.at(0).indv.push_back(stack.at(d).indv.at(i));
            }
        }
    }
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
    for (int i=0; i<stack.at(0).indv.size(); i++)
    {
        int r = i + rand() % (stack.at(0).indv.size() - i);
        swap(stack.at(0).indv.at(i), stack.at(0).indv.at(r));
    }
}


//-------------------------------------------------------------------------
//Randomly swaps cards in deck (same card cannot be swapped more than once)
void Shuffler::Random_Swap_Good()
{
    //better random shuffler
    for (int i=0; i<stack.at(0).indv.size()/2; i++)
    {
        int r1 = rand() % stack.at(0).indv.size();
        //cout << r1 << endl;
        while (stack.at(0).indv.at(r1).selected != 0)
        {
            //cout << r1 << endl;
            r1 = rand() % stack.at(0).indv.size();
            //cout << r1 << endl;
        }
        stack.at(0).indv.at(r1).selected = 1;
        int r2 = (int)rand() % stack.at(0).indv.size();
        while (r2 == r1)
        {
            r2 = (int)rand() % stack.at(0).indv.size();
            while (stack.at(0).indv.at(r2).selected != 0)
            {
                //cout << r2 << endl;
                r2 = rand() % stack.at(0).indv.size();
                //cout << r2 << endl;
            }
        }
        swap(stack.at(0).indv.at(r1), stack.at(0).indv.at(r2));
    }
    //resets selection identifier
    for (int i=0; i<stack.at(0).indv.size(); i++)
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
    for (int i=0; i<stack.at(0).indv.size()/2; i++)
    {
        T1.push_back(stack.at(0).indv.at(i));
        T2.push_back(stack.at(0).indv.at(i+stack.at(0).indv.size()/2));
    }
    int c= 0;
    stack.at(0).indv.clear();
    for (int i=0; i<pP->num_decks*pP->num_cards/2; i++)
    {
        if (c % 2 == 0)
        {
            stack.at(0).indv.push_back(T1.at(pP->num_decks*pP->num_cards/2-(i+1)));
        }
        c += 1;
        if (c % 2 != 0)
        {
            stack.at(0).indv.push_back(T2.at(pP->num_decks*pP->num_cards/2-(i+1)));
        }
        c += 1;
    }
    T1.clear();
    T2.clear();
}


//-------------------------------------------------------------------------
//Checks the amount of cards for each deck
void Shuffler::Check_Num_Cards()
{
    for (int d=0; d<pP->num_decks; d++)
    {
        assert(stack.at(0).indv.size() == pP->num_cards*pP->num_decks);
    }
}


//-------------------------------------------------------------------------
//Checks deck for repeated cards if only one deck
void Shuffler::Test_A()
{
    if (pP->num_decks == 1)
    {
        for (int i=0; i<stack.at(0).indv.size(); i++)
        {
            for (int j=0; j<stack.at(0).indv.size(); j++)
            {
                if (i != j)
                {
                    int c = 0;
                    if (stack.at(0).indv.at(i).card_num == stack.at(0).indv.at(j).card_num)
                    {
                        if (stack.at(0).indv.at(i).suit == stack.at(0).indv.at(j).suit)
                        {
                            c = 1;
                        }
                    }
                    assert(c == 0);     //checks if the same card exists twice in the same deck
                }
            }
        }
    }
}


//-------------------------------------------------------------------------
//Checks that card multiplicity is equal to the number of decks
void Shuffler::Test_B()
{
    if (pP->num_decks>1)
    {
        for (int i=0; i<pP->num_cards; i++)
        {
            if (stack.at(0).indv.at(i).selected == 0)
            {
                stack.at(0).indv.at(i).selected = 1;
                int c = 1;
                for (int j=0; j<pP->num_decks*pP->num_cards; j++)
                {
                    if (i != j)
                    {
                        if (stack.at(0).indv.at(i).card_num == stack.at(0).indv.at(j).card_num)
                        {
                            if (stack.at(0).indv.at(i).suit == stack.at(0).indv.at(j).suit)
                            {
                                if (stack.at(0).indv.at(j).selected == 0)
                                {
                                    //cout << c << endl;
                                    c = c+1;
                                    //cout << c << endl;
                                    stack.at(0).indv.at(j).selected = 1;
                                }
                            }
                        }
                    }
                }
                assert (c == pP->num_decks);
            }
        }
        //resets selection identifier
        for (int i=0; i<stack.at(0).indv.size(); i++)
        {
            stack.at(0).indv.at(i).selected = 0;
        }
    }
}



//-------------------------------------------------------------------------
//Runs all the test functions
void Shuffler::Run_Test_Functions()
{
    Check_Num_Cards();
    Test_A();
    Test_B();
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
}


//-------------------------------------------------------------------------
//writes the deck to a txt file
void Shuffler::Write_Deck_To_File(int s)
{
    ofstream File1;
    File1.open("Deck.txt", ios_base::app);
    if (s == 0)
    {
        File1 << "Number of Decks" << "\t" << "\t" <<pP->num_decks << endl;
        File1 << "Number of Shuffles" << "\t" << pP->num_shuffle << endl;
        File1 << "Type of Shuffle:" << "\t";
        if (pP->RS ==1)
        {
            File1 << "Random Shuffle Fucntion" << endl;
        }
        if (pP->RSB ==1)
        {
            File1 << "Bad Random Shuffle" << endl;
        }
        if (pP->RSG ==1)
        {
            File1 << "Good Random Shuffle" << endl;
        }
        if (pP->BS ==1)
        {
            File1 << "Bridge Shuffle" << endl;
        }
        File1 << endl;
        File1 << "------------------------------------------------------" << endl;
        File1 << "Initial Order" << endl;
    }
    else
    {
        File1 << "------------------------------------------------------" << endl;
        File1 << "Shuffle" << "\t" << s << endl;
    }
    File1 << "Card" << "\t" << "Suit" << endl;
    for (int i=0; i<pP->num_decks*pP->num_cards; i++)
    {
        if (stack.at(0).indv.at(i).card_num == 1)
        {
            File1 << "Ace" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num == 11)
        {
            File1 << "Jack" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num == 12)
        {
            File1 << "Queen" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num == 13)
        {
            File1 << "King" << "\t";
        }
        if (stack.at(0).indv.at(i).card_num !=1)
        {
            if (stack.at(0).indv.at(i).card_num != 11)
            {
                if (stack.at(0).indv.at(i).card_num != 12)
                {
                    if (stack.at(0).indv.at(i).card_num != 13)
                    {
                        File1 << stack.at(0).indv.at(i).card_num << "\t";
                    }
                }
            }
        }
        if (stack.at(0).indv.at(i).suit == 0)
        {
            File1 << "Heart" << "\t";
        }
        if (stack.at(0).indv.at(i).suit == 1)
        {
            File1 << "Diamond" << "\t";
        }
        if (stack.at(0).indv.at(i).suit == 2)
        {
            File1 << "Spade" << "\t";
        }
        if (stack.at(0).indv.at(i).suit == 3)
        {
            File1 << "Club" << "\t";
        }
        File1 << endl;
    }
    File1 << endl;
    File1.close();
}


//-------------------------------------------------------------------------
//Outputs deck in order that the cards appear in the vector
void Shuffler::Display_Deck(int s)
{
    cout << "------------------------------------------------------" << endl;
    if (s == 0)
    {
        cout << "Number of Decks" << "\t" << "\t" <<pP->num_decks << endl;
        cout << "Number of Shuffles" << "\t" << pP->num_shuffle << endl;
        cout << "Type of Shuffle:" << "\t";
        if (pP->RS ==1)
        {
            cout << "Random Shuffle Fucntion" << endl;
        }
        if (pP->RSB ==1)
        {
            cout << "Bad Random Shuffle" << endl;
        }
        if (pP->RSG ==1)
        {
            cout << "Good Random Shuffle" << endl;
        }
        if (pP->BS ==1)
        {
            cout << "Bridge Shuffle" << endl;
        }
        cout << endl;
        cout << "Initial Order" << endl;
    }
    else
    {
        cout << "Shuffle" << "\t" << s << endl;
    }
    cout << "Card" << "\t" << "Suit" << endl;
    for (int i=0; i<pP->num_decks*pP->num_cards; i++)
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
    Run_Test_Functions();
    Display_Deck(s);
    Write_Deck_To_File(s);
    for (int s=1; s<pP->num_shuffle+1; s++)
    {
        Shuffle();
        Run_Test_Functions();
        Display_Deck(s);
        Write_Deck_To_File(s);
    }
}


#endif /* Shuffler_hpp */
