//
//  Piece.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <ostream>

#include "Game.h"
#include "Piece.h"

namespace Gaming
{
    static unsigned int __idGen = 0;
    
    Piece::Piece(const Game &g, const Position &p) : __game(g)
    {
        __position = p;
        __finished = false;
        //__id = __idGen++;
    }
    
    Piece::~Piece()     {}
    
    void Piece::age()   {}
    
    Piece & Piece::operator*(Piece &other)  { return *this; }
    Piece & Piece::interact(Agent *)        { return *this; }
    Piece & Piece::interact(Resource *)     { return *this; }
    
    std::ostream &operator<<(std::ostream &os, const Piece &piece)
    {
        //os << Piece::__id;
        return os;
    }
}