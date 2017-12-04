//
//  main.cpp
//  Card_Shuffler
//
//  Created by Scott S Forer on 12/3/17.
//  Copyright © 2017 Card_Shuffler. All rights reserved.
//

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

#include "Parameters.hpp"
#include "Card.hpp"
#include "Deck.hpp"
#include "Shuffler.hpp"


int main()
{
    srand(time(NULL));
    Parameters P;
    Shuffler S;
    S.pP = &P;
    S.Run_Shuffler();
}
