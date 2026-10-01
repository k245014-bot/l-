#pragma once
#include "../Library/gameObject.h"
#include <unordered_map>
#include <string>
//#include "Other.h"

class SoundManager : public GameObject
{
public:

	SoundManager();
	~SoundManager();

	void Update()override;
	void Draw() {}

	void Play(const std::string& _name, const bool& _loop = false);
	void Stop(const std::string& _name);

	bool IsPlay(const std::string& _name) { return CheckSoundMem(hSounds[_name]) == TRUE; }

private:
	void Load(const std::string& _name, const std::string& _fileName, const float& _volume);

	std::unordered_map<std::string, int> hSounds;
	std::unordered_map<std::string, int> playSounds;
};