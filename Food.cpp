//
//  Food.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include "Game.h"
#include "Resource.h"
#include "Food.h"

namespace Gaming
{
    const char Food::FOOD_ID = 'F';
    
    
    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    {
        __capacity = capacity;
    }
    
    Food::~Food()   { }
    
    void Food::print(std::ostream &os) const
    {
        os << FOOD_ID << __id;
        std::cout << &os;
    }
    
    double Resource::consume()
    {
        finish();
        return __capacity;
    }
}