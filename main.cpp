//
//  main.cpp
//  SF_Card_Shuffler_Project
//
//  Created by Scott S Forer on 1/24/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
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

#include "Parameters.hpp"
#include "Card.hpp"
#include "Deck.hpp"
#include "Shuffler.hpp"


int main()
{
    Parameters P;
    Shuffler S;
    S.pP = &P;
    S.Run_Shuffler();
}
