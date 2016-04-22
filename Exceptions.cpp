//
//  Game.cpp
//  pa4
//
//  Created by Maxim Anaya on 4/18/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include<iostream>
#include<ostream>
#include<string>
#include"Exceptions.h"

namespace Gaming
{
	void GamingException::setName(std::string name)
	{
		__name = name;
	}
    
	std::ostream & operator<<(std::ostream & os, const GamingException & ex)
	{
		os << ex.__name;
		return os;
	}
    
	DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
	{
        __width = width;
        __height = height;
		__exp_width = expWidth;
		__exp_height = expHeight;
		__name = "DimensionEx";
	}
    
	unsigned DimensionEx::getExpWidth() const
	{
		return __exp_width;
	}
    
	unsigned DimensionEx::getExpHeight() const
	{
		return __exp_height;
	}
    
	unsigned DimensionEx::getWidth() const
	{
		return __width;
	}
    
	unsigned DimensionEx::getHeight() const
	{
		return __height;
	}
    
	void InsufficientDimensionsEx::__print_args(std::ostream & os) const
	{
		os << getExpHeight() << getExpWidth() << getWidth() << getHeight();
	}
    
	InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) : DimensionEx(minWidth, minHeight, width, height)
	{
		setName("InsufficientDimensionsEx");
	}
    
	void OutOfBoundsEx::__print_args(std::ostream & os) const
	{
		os << getExpHeight() << getExpWidth() << getWidth() << getHeight();
	}
    
	OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height)
	{
		__name = "OutofBoundsEx";
	}
    
	void PositionEx::__print_args(std::ostream & os) const
	{
		os << __x << __y;
	}
    
	PositionEx::PositionEx(unsigned x, unsigned y)
	{
		__x = x;
		__y = y;
		__name = "PositionEx";
	}
    
	PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y)
	{
		__name = "PositionNonemptyEx";
	}
    
	PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y)
	{
		__name = "PositionEmptyEx";
	}
    
	void PosVectorEmptyEx::__print_args(std::ostream & os) const
	{
		os << __name;
	}
    
	PosVectorEmptyEx::PosVectorEmptyEx()
	{
		__name = "PosVectorEmptyEx";
	}
}