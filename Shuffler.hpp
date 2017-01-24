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


#include "Parameters.hpp"


using namespace std;


class Shuffler
{
    friend class Parameters;
    friend class Deck;
    friend class Card;
    
protected:
    
    
public:
    Parameters* pP;
    
    void Build_Deck();
    
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Builds population of individuals
void Shuffler::Build_Deck()
{
    cout << pP->num_cards << endl;
}



#endif /* Shuffler_hpp */
