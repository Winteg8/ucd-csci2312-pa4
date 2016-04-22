//
//  Resource.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include "Game.h"
#include "Piece.h"
#include "Resource.h"

namespace Gaming
{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;
    
    
    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p)
    {
        __capacity = capacity;
    }
    
    Resource::~Resource()
    {}
    
    double consume() { return 0; }
    
    void Resource::age()    { __capacity = __capacity / RESOURCE_SPOIL_FACTOR; }
    
    ActionType Resource::takeTurn(Surroundings const &s) const { return STAY; }
    
    Piece & Resource::operator*(Gaming::Piece &other)   { return *this; }
    
    Piece & Resource::interact(Gaming::Agent *)         { return *this; }
    
    Piece & Resource::interact(Gaming::Resource *)      { return *this; }
    
}