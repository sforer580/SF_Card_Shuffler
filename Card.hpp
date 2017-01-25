//
//  Card.hpp
//  SF_Card_Shuffler_Project
//
//  Created by Scott S Forer on 1/24/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

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


class Card
{
    friend class Parameters;
    friend class Deck;
    friend class Shuffler;
    
protected:
    
    
public:
    int card_num;   //Ace=1, Jack=11, Queen=12, King=13
    int suit;       //Heart=0, Diamond=1, Spade=2, Club=3
    
private:
};

#endif /* Card_hpp */
