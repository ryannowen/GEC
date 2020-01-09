#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <unordered_map>

/// My Headers
#include "Sound.h"

class Audio
{
private:
	Audio();

	static std::shared_ptr<Audio> audio;

	std::unordered_map<std::string, std::shared_ptr<Sound>> soundMap;
	std::unordered_map<std::string, std::shared_ptr<Sound>> musicMap;

	std::string currentMusic{ std::string() };

public:
	static Audio& GetInstance()
	{
		if (!audio)
		{
			audio.reset(new Audio());
		}

		return *audio;
	}

	void Update();

	// Loads sound returns true if sound is loaded, otherwise somehow failed
	bool LoadSound(const std::string& argSoundPath, const HAPI_TSoundOptions& argOptions);

	// Loads music returns true if music is loaded, otherwise somehow failed
	bool LoadMusic(const std::string& argMusicPath, const HAPI_TSoundOptions& argOptions);


	// Plays sound if loaded
	void PlaySound(const std::string& argSoundPath);

	// Plays a randomly selected music
	void PlayMusic();

};

#define AUDIO Audio::GetInstance()

