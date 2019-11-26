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
	if (left > argRect.left && right < argRect.right && top > argRect.top && bottom < argRect.bottom)
		return true;

	return false;
}

bool Rectangle::CompletelyOutside(const Rectangle& argRect) const
{
	if (left < argRect.left && right > argRect.right && top < argRect.top && bottom > argRect.bottom)
		return true;

	return false;
}

bool Rectangle::Contains(const Rectangle& argRect) const
{
	if (bottom < argRect.bottom && bottom > argRect.top)
		return true;
	else if (left > argRect.left && left < argRect.right)
		return true;
	else if (right < argRect.right && right > argRect.left)
		return true;
	else if (top > argRect.top && top < argRect.bottom)
		return true;

	return false;
}