//
//  DefaultAgentStrategy.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/15/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "DefaultAgentStrategy.h"

namespace Gaming
{
    DefaultAgentStrategy::DefaultAgentStrategy()  {}
    
    DefaultAgentStrategy::~DefaultAgentStrategy() {}
    
    
    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        
        std::vector<int> advant, food, empty, simple;
        Position moveTo;
        PositionRandomizer randomTarget;
        
        // record the surroundings
        for (int i = 0; i < 9; i++)
        {
            //skip over i = 4 so that Agent doesn't look at itself
            if (i == 4)
                i++;
            
            // add stuff to the according vector
            switch (s.array[i])
            {
                case 0: simple.push_back(i); break;
                case 1: break;
                case 2: food.push_back(i);  break;
                case 3: advant.push_back(i);break;
                case 4: break;
                // no case 5 cuz skips over i = 4
                case 6: empty.push_back(i); break;
            }
            
            
        }
        
        
        // determine course of action (determine what position to move to)
        if (!advant.empty())        moveTo = randomTarget(advant);
        
        else if (!food.empty())     moveTo = randomTarget(food);
        
        else if (!empty.empty())    moveTo = randomTarget(empty);
        
        else if (!simple.empty())   moveTo = randomTarget(simple);
        
        
        // return the direction based on PositionRandomizer position
        switch (moveTo.x)
        {
            case 0:
            {
                switch (moveTo.y)
                {
                    case 0: return NE;
                    case 1: return N;
                    case 2: return NW;
                }
            }
            case 1:
            {
                switch (moveTo.y)
                {
                    case 0: return E;
                    case 1: return STAY;
                    case 2: return W;
                }
            }
            case 2:
            {
                switch (moveTo.y)
                {
                    case 0: return SE;
                    case 1: return S;
                    case 2: return SW;
                }
            }
        }
        return STAY;
    }
}



