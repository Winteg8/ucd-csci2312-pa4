//
//  Agent.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include "Game.h"
#include "Piece.h"
#include "Agent.h"
#include "Resource.h"

namespace Gaming
{
    const double Agent::AGENT_FATIGUE_RATE = 0.3;
    
    
    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p)
    {
        setPosition(p);
        __energy = energy;
    }
    
    Agent::~Agent() {}
    
    void Agent::age()   { __energy *= AGENT_FATIGUE_RATE; }
    
    
    Piece & Agent::operator*(Piece &other)
    {
        other.interact(this);
        return *this;
    }
    
    Piece & Agent::interact(Agent * enemy)
    {
        if (__energy == enemy->getEnergy())
        {
            finish();
            enemy->finish();
        }
        else if (__energy < enemy->getEnergy())
        {
            enemy->addEnergy(-1 * __energy);
            finish();
        }
        else
        {
            __energy -= enemy->getEnergy();
            enemy->finish();
        }
        
        return *this;
    }
    
    Piece & Agent::interact(Resource * consumable)
    {
        __energy += consumable->getCapacity();
        consumable->consume();
        return *this;
    }
}


