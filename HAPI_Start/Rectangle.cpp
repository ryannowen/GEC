#include "Rectangle.h"

#include <algorithm>

Rectangle::Rectangle(int argRight, int argLeft, int argBottom, int argTop)
	: right(argRight), left(argLeft), bottom(argBottom), top(argTop)
{
}

void Rectangle::UpdateDimensions(int argWidth, int argHeight)
{
	left = 0;
	top = 0;
	right = argWidth;
	bottom = argHeight;
}

void Rectangle::Translate(const int argPosX, const int argPosY)
{
	left += argPosX;
	right += argPosX;

	bottom += argPosY;
	top += argPosY;
}

void Rectangle::ClipTo(const Rectangle& argRect)
{
	left = std::max(left, argRect.left);
	top = std::max(top, argRect.top);
	right = std::min(right, argRect.right);
	bottom = std::min(bottom, argRect.bottom);
}

bool Rectangle::CompletelyContains(const Rectangle& argRect) const
{
	if ((left > argRect.left && right < argRect.right) && (top > argRect.top && bottom < argRect.bottom))
		return true;

	return false;
}

bool Rectangle::CompletelyOutside(const Rectangle& argRect) const
{
	if ((left < argRect.left && right > argRect.right) && (top < argRect.top && bottom > argRect.bottom))
		return true;

	return false;
}

bool Rectangle::Contains(const Rectangle& argRect) const
{	
	if ((right < argRect.left || left > argRect.right) || (bottom < argRect.top || top > argRect.bottom))
		return false;
	else
		return true;
}