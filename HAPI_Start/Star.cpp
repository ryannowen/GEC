#include "Star.h"

//My Headers
#include "Time.h"

Star::Star(float argX, float argY, float argZ, HAPI_TColour argColour, float argSpeed)
	: x(argX), y(argY), z(argZ), starColour(argColour), translateSpeed(argSpeed)
{}

/// Converts star to 2D screen space from 3D space, then draws in on screen
void Star::Draw(BYTE* argScreenPointer, const float argEyeDist, const int argScreenWidth, const int argScreenHeight)
{
	screenX = static_cast<int>(((argEyeDist * (x - (argScreenWidth / 2))) / (z + argEyeDist)) + (argScreenWidth / 2));
	screenY = static_cast<int>(((argEyeDist * (y - (argScreenHeight / 2))) / (z + argEyeDist)) + (argScreenHeight / 2));

	if (((((screenY * argScreenWidth) + screenX) * 4) > 0) && (((screenY * argScreenWidth) + screenX) * 4) < ((argScreenWidth * argScreenHeight * 4) + 4))
	{
		memcpy(argScreenPointer + (((static_cast<size_t>(screenY) * argScreenWidth) + screenX) * 4), &starColour, 4);
	}
}

/// Gets new location in 3D world space 
void Star::RandomisePosition(const int argScreenWidth, const int argScreenHeight, const float argMaxZ)
{
	x = static_cast<float>(rand() % argScreenWidth);
	y = static_cast<float>(rand() % argScreenHeight);
	z = static_cast<float>(rand() % (static_cast<int>(argMaxZ) - 10)) + 10;
}

/// Translates to star towards camera dependant with accelaration
void Star::Translate(const int argScreenWidth, const int argScreenHeight, const float argSpeedModifier)
{
	z -= ((0.1f * translateSpeed) * argSpeedModifier) * TIME.GetDeltaTimeMiliseconds();
	translateSpeed += 0.1f;

	if (z <= 0)
	{
		RandomisePosition(argScreenWidth, argScreenHeight);
		translateSpeed = 1.0f;
	}
}

/// Rotates around given point
void Star::Rotate(const int argPointX, const int argPointY, const float argAngle, const float argSpeedModifier)
{
	float rotateAngle{ ((argAngle / z) * argSpeedModifier) * TIME.GetDeltaTimeMiliseconds() };
	float cosfAngle{ cosf(rotateAngle) }, sinfAngle{ sinf(rotateAngle) };

	x = ((cosfAngle * (x - argPointX)) - (sinfAngle * (y - argPointY))) + argPointX;
	y = ((sinfAngle * (x - argPointX)) + (cosfAngle * (y - argPointY))) + argPointY;
}

/// Sets stars new colour
void Star::SetColour(HAPI_TColour argNewColour)
{
	starColour = argNewColour;
}

/// Returns stars current movement speed ( * 0.1f to get world space speed)
float Star::GetStarSpeed() const
{
	return translateSpeed;
}
