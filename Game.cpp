//
//  Game.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/17/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>

#include "Food.h"
#include "Advantage.h"
#include "Simple.h"
#include "Strategic.h"
#include "Piece.h"
#include "Game.h"
#include "Gaming.h"
#include "DefaultAgentStrategy.h"
#include "Exceptions.h"

namespace Gaming
{
    
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    PositionRandomizer Game::__posRandomizer;
    
    Game::Game() : __width(3), __height(3)
    {
        __round = 0;
        __width = 4;
        __height = 5;
        
        for (int i = 0; i < __grid.size(); i++)
            __grid.push_back(nullptr);
    }
    
    Game::Game(unsigned width, unsigned height, bool manual) // note: manual population by default
    {
        
        if (width < MIN_WIDTH || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        
        
        __round = 0;
        __width = width;
        __height = height;
        
        for (int i = 0; i < __grid.size(); i++)
            __grid.push_back(nullptr);
        
        if (!manual)
            populate();
    }
    
    /*Game::Game(const Game &g)
    {
        
    }
    
    Game & Game::operator=(const Game &g)
    {
        __width = g.getWidth();
        __height = g.__height;
    }*/
    
    Game::~Game()
    {
        for (int i = 0; i < __grid.size(); i++)
        {
            delete __grid[i];
        }
    }
    
    void Game::populate()
    {
        int size = (int)__grid.size();
        std::vector<int> indexes;
        
        for (int i = 0; i < __grid.size(); i++)
            indexes.push_back(i);
        
        PositionRandomizer rand;
        
        __numInitAgents = size / NUM_INIT_AGENT_FACTOR;
        __numInitResources = size / NUM_INIT_RESOURCE_FACTOR;
        
        unsigned int food = __numInitResources * 0.75;
        unsigned int advantages = __numInitResources * 0.25;
        unsigned int simple = __numInitAgents * 0.5;
        unsigned int strategic = __numInitAgents * 0.5;
        
        while (food != 0)
        {
            addFood(rand(indexes));
            food --;
        }
        
        while (advantages != 0)
        {
            addAdvantage(rand(indexes));
            advantages --;
        }
        
        while (simple != 0)
        {
            addSimple(rand(indexes));
            simple --;
        }
        
        while (strategic != 0)
        {
            addStrategic(rand(indexes));
            strategic --;
        }
    }
    unsigned int Game::getNumPieces() const
    {
        return (int)__grid.size();
    }
    
    unsigned int Game::getNumAgents() const
    {
        unsigned int answer;
        
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                if (__grid[i]->getType() == SIMPLE || __grid[i]->getType() == STRATEGIC)
                    answer++;
            }
        }
        
        return answer;
    }
    unsigned int Game::getNumSimple() const
    {
        unsigned int answer;
        
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                if (__grid[i]->getType() == SIMPLE)
                    answer++;
            }
        }
        
        return answer;
    }
    unsigned int Game::getNumStrategic() const
    {
        unsigned int answer;
        
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                if (__grid[i]->getType() == STRATEGIC)
                    answer++;
            }
        }
        
        return answer;
    }
    unsigned int Game::getNumResources() const
    {
        unsigned int answer;
        
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                if (__grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE)
                    answer++;
            }
        }
        
        return answer;
    }
    
    const Piece * Game::getPiece(unsigned int x, unsigned int y) const
    {
        if (x < __height && y < __width)
        {
            for (int i = 0; i < getNumPieces(); i++)
            {
                if (__grid[i] != nullptr)
                {
                    if (__grid[i]->getPosition().x == x && __grid[i]->getPosition().y == y)
                        return __grid[i];
                }
            }
            //std::cout << "~~~~~~~~~~EXCEPTION THROWN~~~~~~~~~~~" << std::endl;
            throw PositionEmptyEx(x, y);
        }
        else
            throw OutOfBoundsEx(__width, __height, y, x);
    }
    
    void Game::addSimple(const Position &position)
    {
        try
        {
            if (getPiece(position.x, position.y)->getType() == EMPTY)
                __grid.push_back(new Simple(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR));
            else
                throw PositionNonemptyEx(position.x, position.y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Simple(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR)); }
    }
    
    
    
    void Game::addSimple(const Position &position, double energy) // used for testing only
    {
        try
        {
            if (getPiece(position.x, position.y)->getType() == EMPTY)
                __grid.push_back(new Simple(*this, *new Position(position.x, position.y), energy));
            else
                throw PositionNonemptyEx(position.x, position.y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Simple(*this, *new Position(position.x, position.y), energy)); }
    }
    
    
    
    void Game::addSimple(unsigned x, unsigned y)
    {
        try
        {
            if (getPiece(x, y)->getType() == EMPTY)
                __grid.push_back(new Simple(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR));
            else
                throw PositionNonemptyEx(x, y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Simple(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR)); }
    }
    
    
    
    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        try
        {
            if (getPiece(x, y)->getType() == EMPTY)
                __grid.push_back(new Simple(*this, *new Position(x, y), energy));
            else
                throw PositionNonemptyEx(x, y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Simple(*this, *new Position(x, y), energy)); }
    }
    
    
    
    void Game::addStrategic(const Position &position, Strategy *s)
    {
        try
        {
            if (getPiece(position.x, position.y)->getType() == EMPTY)
                __grid.push_back(new Strategic(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR, s));
            else
                throw PositionNonemptyEx(position.x, position.y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Strategic(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR, s)); }
    }
    
    
    
    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        try
        {
            if (getPiece(x, y)->getType() == EMPTY)
                __grid.push_back(new Strategic(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR, s));
            else
                throw PositionNonemptyEx(x, y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Strategic(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR, s)); }
    }
    
    
    
    void Game::addFood(const Position &position)
    {
        try
        {
            if (getPiece(position.x, position.y)->getType() == EMPTY)
                __grid.push_back(new Food(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR));
            else
                throw PositionNonemptyEx(position.x, position.y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Food(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR)); }
    }
    
    
    
    void Game::addFood(unsigned x, unsigned y)
    {
        try
        {
            if (getPiece(x, y)->getType() == EMPTY)
                __grid.push_back(new Food(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR));
            else
                throw PositionNonemptyEx(x, y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Food(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR)); }
    }
    
    
    
    void Game::addAdvantage(const Position &position)
    {
        try
        {
            if (getPiece(position.x, position.y)->getType() == EMPTY)
                __grid.push_back(new Advantage(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR));
            else
                throw PositionNonemptyEx(position.x, position.y);
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Advantage(*this, *new Position(position.x, position.y), NUM_INIT_AGENT_FACTOR)); }
    }
    
    
    
    void Game::addAdvantage(unsigned x, unsigned y)
    {
        try
        {
            if (getPiece(x, y)->getType() == EMPTY)
                __grid.push_back(new Advantage(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR));
            else
                throw PositionNonemptyEx(x, y);
            
        }
        catch (PositionEmptyEx &ex)
        { __grid.push_back(new Advantage(*this, *new Position(x, y), NUM_INIT_AGENT_FACTOR)); }
    }
    
    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings s;
        
        if (isLegal(STAY, pos))
        {
            if (isLegal(N, pos))
            {
                // record top slot of the 3x3 grid
                try
                { s.array[1] = getPiece(pos.x-1, pos.y)->getType(); }
                catch (PositionEmptyEx &ex)
                { s.array[1] = EMPTY; }
                catch (OutOfBoundsEx &ex)
                { s.array[1] = INACCESSIBLE; }
                
                
                if (isLegal(W, pos))
                {
                    // record top left and left slots in the 3x3 grid
                    
                    try
                    { s.array[3] = getPiece(pos.x, pos.y-1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[3] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[3] = INACCESSIBLE; }
                    
                    try
                    { s.array[0] = getPiece(pos.x-1, pos.y-1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[0] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[0] = INACCESSIBLE; }
                    
                }
                if (isLegal(E, pos))
                {
                    // record top right and right slots in the 3x3 grid
                    try
                    { s.array[5] = getPiece(pos.x, pos.y+1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[5] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[5] = INACCESSIBLE; }
                
                    try
                    { s.array[2] = getPiece(pos.x-1, pos.y+1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[3] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[3] = INACCESSIBLE; }
            
                }
            }
            if (isLegal(S, pos))
            {
                // record bottom slot of the 3x3 grid
                try
                { s.array[7] = getPiece(pos.x+1, pos.y)->getType(); }
                catch (PositionEmptyEx &ex)
                { s.array[7] = EMPTY; }
                catch (OutOfBoundsEx &ex)
                { s.array[7] = INACCESSIBLE; }
                
                
                
                if (isLegal(W, pos))
                {
                    // record bottom left and left slots in the 3x3 grid
                    
                    try
                    { s.array[3] = getPiece(pos.x, pos.y-1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[3] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[3] = INACCESSIBLE; }
                    
                    
                    try
                    { s.array[6] = getPiece(pos.x+1, pos.y-1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[6] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[6] = INACCESSIBLE; }
                    
                }
                
                if (isLegal(E, pos))
                {
                    // record bottom right and right slots in the 3x3 grid
                    
                    try
                    { s.array[5] = getPiece(pos.x, pos.y+1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[5] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[5] = INACCESSIBLE; }
                    
                    
                    try
                    { s.array[8] = getPiece(pos.x+1, pos.y+1)->getType(); }
                    catch (PositionEmptyEx &ex)
                    { s.array[3] = EMPTY; }
                    catch (OutOfBoundsEx &ex)
                    { s.array[3] = INACCESSIBLE; }
                    
                }

            }
        }
        
        return s;
    }
    
    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        int x = to.x - from.x + 1, y = to.y - from.y + 1;
        
        unsigned int i = y + (3 * x);
        
        switch (i)
        {
            case 0: return NW;
            case 1: return N;
            case 2: return NE;
            case 3: return W;
            case 4: return STAY;
            case 5: return E;
            case 6: return SW;
            case 7: return S;
            case 8: return SE;
        }
        return STAY;
    }
    
    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        // return true if can move in desired direction from specified position
        switch(ac)
        {
            case NW:    // if 1+ away from top left corner of the board
            {
                if (pos.x > 0 && pos.y > 0) return true;
                else return false;
            }
            case N:     // if 1+ away from top edge of the board
            {
                if (pos.x > 0) return true;
                else return false;
            }
            case NE:    // if 1+ away from top right corner of the board
            {
                if (pos.x > 0 && pos.y < __width-1) return true;
                else return false;
            }
            case W:     // if 1+ away from right edge of the board
            {
                if (pos.y > 0) return true;
                else return false;
            }
            case E:     // if 1+ away from left edge of the board
            {
                if (pos.y < __width-1) return true;
                else return false;
            }
            case SW:    // if 1+ away from bottom left corner of the board
            {
                if (pos.x < __height-1 && pos.y > 0) return true;
                else return false;
            }
            case S:     // if 1+ away from bottom edge of the board
            {
                if (pos.x < __height-1) return true;
                else return false;
            }
            case SE:    // if 1+ away from bottom right corner of the board
            {
                if (pos.x < __height-1 && pos.y < __width-1) return true;
                else return false;
            }
            case STAY:  // if within the grid of the board
            {
                if (pos.x < __height && pos.y < __width) return true;
                else return false;
            }
        }
    }
    
    const Position Game::move(const Position &pos, const ActionType &ac) const // note: assumes legal, use with isLegal()
    {
        if (isLegal(ac, pos))
        {
            switch (ac)
            {
                case NW:    return *new Position(pos.x-1,pos.y-1);
                case N:     return *new Position(pos.x-1,pos.y);
                case NE:    return *new Position(pos.x-1,pos.y+1);
                case W:     return *new Position(pos.x,pos.y-1);
                case E:     return *new Position(pos.x,pos.y+1);
                case SW:    return *new Position(pos.x+1,pos.y-1);
                case S:     return *new Position(pos.x+1,pos.y);
                case SE:    return *new Position(pos.x+1,pos.y+1);
                case STAY:  return pos;
            }
        }
        return pos;
    }
    
    void Game::round()   // play a single round
    {
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                if (__grid[i]->getTurned() == false)
                {
                    Surroundings s = getSurroundings(__grid[i]->getPosition());
                    Position movingTo = move(__grid[i]->getPosition(), __grid[i]->takeTurn(s));
                    
                    if (__grid[i]->getType() == STRATEGIC || __grid[i]->getType() == SIMPLE)
                    {
                        Piece * acted = nullptr;
                        for (int i = 0; i < __grid.size(); i++)
                        {
                            if (__grid[i]->getPosition().x == movingTo.x && __grid[i]->getPosition().y == movingTo.y)
                                acted = __grid[i];
                        }
                        
                        // interact
                        //(*__grid[i])*(*acted);
                    }
                        
                    __grid[i]->setTurned(true);
                }
            }

        }
            
            // remove all Pieces that are finished, and if 8th round, reset __turned
            for (int i = 0; i < __grid.size(); i++)
            {
                if (__grid[i] != nullptr)
                {
                    try
                    {
                        if (__grid[i]->isViable())
                        {
                            __grid[i]->age();
                            //std::cout << "INDEX " << i << " IS AGING" << std::endl;
                        }
                        else
                        {
                            __grid.erase(__grid.begin()+i);
                        }
                    }
                    catch (PositionEmptyEx &ex)
                    { }
                    
                }
            }
        
        if (__round == 8)
        {
            for (int i = 0; i < __grid.size(); i++)
            {
                if (__grid[i] != nullptr)
                    __grid[i]->setTurned(false);
            }
        }
        
        __round++;
    }
    
    void Game::play(bool verbose)
    {
        
    }
    
    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        return os;
    }
}






