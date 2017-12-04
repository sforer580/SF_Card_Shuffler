//
//  Parameters.hpp
//  SF_Card_Shuffler_Project
//
//  Created by Scott S Forer on 1/24/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp

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


class Parameters
{
    friend class Shuffler;
    friend class Deck;
    friend class Card;
    
protected:
    
    
public:
    int num_decks = 1;          //number of decks
    int num_cards = 52;         //number of cards in deck
    int num_shuffle = 1;        //number of times deck is shuffled
    
    bool RS = false;             //false=off, true=on       Random Shuffle
    bool RSB = false;            //false=off, true=on       Random Swap Bad
    bool RSG = false;            //false=off, true=on       Random Swap Good
    bool BS = true;              //false=off, true=on       Bridge Shuffle
    
private:
};

#endif /* Parameters_hpp */
