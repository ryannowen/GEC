#pragma once
class Rectangle
{
public:
	int right, bottom, left, top;
	Rectangle(int argRight = 0, int argLeft = 0, int argBottom = 0,  int argTop = 0);

	// Changes dimensions of rectangle;
	void UpdateDimensions(int argWidth, int argHeight);
	// Moves rectangle by position (Translate back afterwards)
	void Translate(const int argPosX, const int argPosY);

	// Returns width
	int Width() const { return right - left; };
	// Returns height
	int Height() const { return bottom - top; };

	// Clips rectangle to source
	void ClipTo(const Rectangle& argSourceRect);
	// Checks if rectangle fully overlaps other
	bool CompletelyContains(const Rectangle& argRect) const;
	// Checks if rectangle fully outside other
	bool CompletelyOutside(const Rectangle& argRect) const;
	// Checks if rectangle has part of other
	bool Contains(const Rectangle& argRect) const;
};

