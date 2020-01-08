#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

class Sound
{
private:
	HAPI_TSoundOptions soundOptions;

	int instanceID{ 0 };

public:
	Sound(const HAPI_TSoundOptions& argOptions)
		: soundOptions(argOptions)
	{}


	void SetVolume(const float argVolume) { soundOptions.volume = argVolume; };
	void SetLooping(const bool argLoop) { soundOptions.loop = argLoop; };

	bool Play(const std::string& argSoundPath) { return HAPI.PlaySound(argSoundPath, soundOptions, instanceID); };
	int GetInstanceID() const { return instanceID; };
};

