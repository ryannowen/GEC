#pragma once

#include "Star.h"

class Starfield
{
public:
	Starfield(const int argScreenWidth, const int argScreenHeight, const int argMinStarAmount = 0, const int argMaxStarAmount = 1000, const float argEyeDist = 100.0f, const float argMaxZ = 500.0f, const float argSpeedModifier = 1.0f);
	~Starfield();

	void Update(BYTE* argScreenPointer, const int argScreenWidth, const int argScreenHeight);
	
	void SetEyeDistance(const float argNewEyeDist = 100.0f);
	void SetSpeedModifier(const float argNewSpeedModifier = 1.0f);

	/// Get Functions
	float GetEyeDistance() const;
	float GetSpeedModifier() const;
	int GetStarAmount() const;

private:
	float eyeDist, speedModifier, maxZ;
	const int starAmount;
	Star* stars;

	HAPI_TColour starColours[5] // Blue
	{
		HAPI_TColour(12, 0, 107),
		HAPI_TColour(29, 0, 255),
		HAPI_TColour(0, 162, 255),
		HAPI_TColour(59, 183, 255),
		HAPI_TColour(92, 241, 255),

	};

	//HAPI_TColour starColours[5] // Orange
	//{
	//	HAPI_TColour(133, 0, 0),
	//	HAPI_TColour(201, 0, 0),
	//	HAPI_TColour(255, 74, 74),
	//	HAPI_TColour(214, 114, 0),
	//	HAPI_TColour(255, 162, 56)
	//};

	//HAPI_TColour starColours[5] // Orange
	//{
	//	HAPI_TColour(0, 138, 46),
	//	HAPI_TColour(0, 222, 74),
	//	HAPI_TColour(51, 255, 119),
	//	HAPI_TColour(18, 130, 1),
	//	HAPI_TColour(142, 255, 125)
	//};


};

