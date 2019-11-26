#include "Starfield.h"


Starfield::Starfield(const int argScreenWidth, const int argScreenHeight, const int argMinStarAmount, const int argMaxStarAmount, const float argEyeDist, const float argMaxZ, const float argSpeedModifier)
	: starAmount((rand() % ((argMaxStarAmount - argMinStarAmount) + 1)) + argMinStarAmount), eyeDist(argEyeDist), maxZ(argMaxZ), speedModifier(argSpeedModifier)
{
	/// Creates new stars and applies initial on screen position
	stars = new Star[starAmount];

	for (int i = 0; i < starAmount; i++)
	{
		stars[i].RandomisePosition(argScreenWidth, argScreenHeight, argMaxZ);
		stars[i].Translate(argScreenWidth, argScreenHeight, speedModifier);

		stars[i].SetColour(starColours[rand() % 5]);

	}
}

/// Destroys stars from heap
Starfield::~Starfield()
{
	delete[] stars;
}

/// Applies Transformations to all stars
void Starfield::Update(BYTE* argScreenPointer, const int argScreenWidth, const int argScreenHeight)
{
	if (argScreenPointer == nullptr)
	{
		std::cerr << "ERROR: Trying to update starfield but screen pointer is nullptr" << std::endl;
		return;
	}

	int screenCenterX{ argScreenWidth / 2 }, screenCenterY{ argScreenHeight / 2 };
	
	for (int i = 0; i < starAmount; i++)
	{
		stars[i].Rotate(screenCenterX, screenCenterY, 0.5f, speedModifier);
		stars[i].Translate(argScreenWidth, argScreenHeight, speedModifier);

		stars[i].Draw(argScreenPointer, eyeDist, argScreenWidth, argScreenHeight);
	}
}

/// Sets Eye distance to new value (no value sets to default)
void Starfield::SetEyeDistance(const float argNewEyeDist)
{
	eyeDist = argNewEyeDist;
}

/// Sets speed modifier to new value (no value sets to default)
void Starfield::SetSpeedModifier(const float argNewSpeedModifier)
{
	speedModifier = argNewSpeedModifier;
}

/// Returns eye distance
float Starfield::GetEyeDistance() const
{
	return eyeDist;
}

/// Returns speed modifier
float Starfield::GetSpeedModifier() const
{
	return speedModifier;
}

/// Returns star amount
int Starfield::GetStarAmount() const
{
	return starAmount;
}
