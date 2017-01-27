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
    int num_cards = 52;         //number of cards in deck
    int num_shuffle = 1;        //number of times deck is shuffled
    
    int RS = 0;             //0=off, 1=on       Random Shuffle
    int RSB = 0;            //0=off, 1=on       Random Swap Bad
    int RSG = 0;            //0=off, 1=on       Random Swap Good
    int BS = 1;             //0=off, 1=on       Bridge Shuffle
    
private:
};

#endif /* Parameters_hpp */
