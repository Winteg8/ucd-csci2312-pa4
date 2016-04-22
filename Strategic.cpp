//
//  Strategic.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"
#include "Strategic.h"

namespace Gaming
{
    const char Strategic::STRATEGIC_ID = 'T';
    
    
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy)
    {
        __energy = energy;
        __strategy = s;
    }
    
    Strategic::~Strategic()
    {
        
    }
    
    void Strategic::print(std::ostream &os) const
    {
        os << STRATEGIC_ID << __id;
        std::cout << &os;
    }
    
    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }
    
}