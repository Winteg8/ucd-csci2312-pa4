//
//  Simple.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include "Gaming.h"
#include "Simple.h"

namespace Gaming
{
    const char Simple::SIMPLE_ID = 'S';
    
    
    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy)
    {
        __energy = energy;
    }
    
    Simple::~Simple()   {}
    
    void Simple::print(std::ostream &os) const
    {
        os << SIMPLE_ID << __id;
        std::cout << &os;
    }
    
    
    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        Position moveTo;
        Position ownPos(1, 1);
        PositionRandomizer randomTarget;
        std::vector<int> resources, empty;
        
        // record the surroundings
        for (int i = 0; i < 9; i++)
        {
            //skip over i = 4 so that Agent doesn't look at itself
            if (i == 4)
                i++;
            
            
            if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)      resources.push_back(i);
            
            else if (s.array[i] == EMPTY)                           empty.push_back(i);
        }
        
        // determine the course of action
        if (!resources.empty())     return __game.reachSurroundings(ownPos, randomTarget(resources));
        
        else if (!empty.empty())    return __game.reachSurroundings(ownPos, randomTarget(empty));
        
        else
            return STAY;
    }
}






