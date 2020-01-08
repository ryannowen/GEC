#include "Audio.h"

std::shared_ptr<Audio> Audio::audio{ nullptr };

Audio::Audio()
{
	LoadMusic("Data//Sounds//Music//ATimeForgotten.wav", HAPI_TSoundOptions(0.1f));
	LoadMusic("Data//Sounds//Music//DreamingUnderTheStars.wav", HAPI_TSoundOptions(0.1f));
	LoadMusic("Data//Sounds//Music//HavenoftheFaeries.wav", HAPI_TSoundOptions(0.1f));
	LoadMusic("Data//Sounds//Music//IllusoryRealm.wav", HAPI_TSoundOptions(0.1f));

	PlayMusic();
}

void Audio::Update()
{
	float playbackPosition;
	const HAPI_MediaStatus& musicStatus{ HAPI.GetSoundStatus(musicMap.at(currentMusic)->GetInstanceID(), playbackPosition) };

	if (musicStatus != HAPI_MediaStatus::ePlaying)
		PlayMusic();
}

bool Audio::LoadSound(const std::string& argSoundPath, const HAPI_TSoundOptions& argOptions)
{
	if (argSoundPath == std::string())
		return false;

	/// Checks if space is available in map for sound, and creates sound if there is
	if (soundMap.find(argSoundPath) == soundMap.end())
	{
		if (HAPI.LoadSound(argSoundPath))
			soundMap[argSoundPath] = std::make_shared<Sound>(argOptions);
		else
		{
			std::cerr << "ERROR: Trying to load sound and failed, soundPath=" << argSoundPath << std::endl;
			return false;
		}
	}

	return true;
}

bool Audio::LoadMusic(const std::string& argMusicPath, const HAPI_TSoundOptions& argOptions)
{
	if (argMusicPath == std::string())
		return false;

	/// Checks if space is available in map for sound, and creates sound if there is
	if (musicMap.find(argMusicPath) == musicMap.end())
	{
		if (HAPI.LoadSound(argMusicPath))
			musicMap[argMusicPath] = std::make_shared<Sound>(argOptions);
		else
		{
			std::cerr << "ERROR: Trying to load music and failed, soundPath=" << argMusicPath << std::endl;
			return false;
		}
	}

	return true;
}

void Audio::PlaySound(const std::string& argSoundPath)
{
	if (argSoundPath == std::string())
		return;

	/// Checks if sound is loaded, if it is play it, otherwise output error
	if (soundMap.find(argSoundPath) != soundMap.end())
		soundMap.find(argSoundPath)->second->Play(argSoundPath);
	else
		std::cerr << "ERROR: Trying to play sound but isn't loaded, soundPath=" << argSoundPath << std::endl;
}

void Audio::PlayMusic()
{
	if (musicMap.size() > 0)
	{
		auto it{ musicMap.begin() };

		std::advance(it, rand() % musicMap.size());

		it->second->Play(it->first);
		currentMusic = it->first;
	}
	else
		std::cerr << "ERROR: No loaded music to play" << std::endl;
}

