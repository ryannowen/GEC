/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI:
	https://scm-intranet.tees.ac.uk/users/u0018197/hapi.html
*/

/// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>

/// C++ headers
#include <time.h>
#include <string.h>
#include <iostream>

/// My headers
#include "Vector2.h"
#include "World.h"
#include "Renderer.h"

/// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

/// Every HAPI program has a HAPI_Main as an entry point
/// When this function exits the program will close down
void HAPI_Main()
{
	// Debug FPS
	//HAPI.SetShowFPS(true);
	//HAPI.LimitFrameRate(5);

	/// Seeds PRNG
	std::srand(static_cast<unsigned int>(time(0)));


	/// Initial Update to begin game loop
	WORLD.Update();
}

