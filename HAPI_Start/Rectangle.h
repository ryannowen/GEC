#pragma once
class Rectangle
{
public:
	int right, bottom, left, top;
	Rectangle(int argRight = 0, int argLeft = 0, int argBottom = 0,  int argTop = 0);

	void UpdateDimensions(int argWidth, int argHeight);
	void Translate(const int argPosX, const int argPosY);

	int Width() const { return right - left; };
	int Height() const { return bottom - top; };

	void ClipTo(const Rectangle& argSourceRect);
	bool CompletelyContains(const Rectangle& argRect) const;
	bool CompletelyOutside(const Rectangle& argRect) const;
	bool Contains(const Rectangle& argRect) const;
};

