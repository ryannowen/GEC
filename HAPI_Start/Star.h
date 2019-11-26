#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

class Star
{
public:
	Star(float argX = 0, float argY = 0, float argZ = 0, HAPI_TColour argColour = HAPI_TColour::Random(), float argSpeed = 1.0f);
	
	void Draw(BYTE* argScreenPointer, const float argEyeDist, const int argScreenWidth, const int argScreenHeight);
	void RandomisePosition(const int argScreenWidth, const int argScreenHeight, const float argMaxZ = 500);
	
	/// Transforms
	void Translate(const int argScreenWidth, const int argScreenHeight, const float argSpeedModifier = 1.0f);
	void Rotate(const int argScreenCenterX, const int argScreenCenterY, const float argAngle = 0.5f, const float argSpeedModifier = 1.0f);

	void SetColour(HAPI_TColour argNewColour);

	/// Get Functions
	float GetStarSpeed() const;

private:
	float translateSpeed, x, y, z;
	int screenX{ 0 }, screenY{ 0 };
	HAPI_TColour starColour;
};

