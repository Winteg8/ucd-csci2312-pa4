//
//  Advantage.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include "Game.h"
#include "Resource.h"
#include "Advantage.h"

namespace Gaming
{
    const char Advantage::ADVANTAGE_ID = 'D';
    
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    
    
    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    {
        __capacity = capacity;
    }
    
    Advantage::~Advantage() { }
    
    void Advantage::print(std::ostream &os) const
    {
        os << ADVANTAGE_ID << __id;
        std::cout << &os;
    }
    
    double Advantage::getCapacity() const
    {
        return (__capacity * ADVANTAGE_MULT_FACTOR);
    }
    
    double Advantage::consume()
    {
        finish();
        return getCapacity();
    }
}