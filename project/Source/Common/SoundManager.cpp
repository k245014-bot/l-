#include "SoundManager.h"
#include <assert.h>


namespace
{
	//同時再生数
	static const int SOUND_SAME_TIME_MAX = 10;
	//サウンドフォルダのパス
	const std::string soundfolder = "data/sound/";
}

SoundManager::SoundManager()
{
	//各シーンで使いたい物のコンストラクタで呼ぶ。
	//DontDestroyOnSceneChange();
	
	Load("REEL_STOP", (soundfolder + "stop.wav").c_str(), 500.0f);
	Load("MAXBET", (soundfolder + "MAXBET.wav").c_str(), 600.0f);
	Load("PAYOUT", (soundfolder + "Pay.wav").c_str(), 400.0f);
	Load("LEVER_ON", (soundfolder + "lever.wav").c_str(), 400.0f);

	Load("ADD_GAME_1", (soundfolder + "AddGame.wav").c_str(), 400.0f);
	Load("ADD_GAME_2", (soundfolder + "AddGame2.wav").c_str(), 400.0f);

	Load("REPLAY", (soundfolder + "replay.wav").c_str(), 400.0f);
	
	Load("BIG_JINGLE", (soundfolder + "BIG_Jingle.wav").c_str(), 400.0f);
	Load("SUPER_BIG_1", (soundfolder + "SBIG1.wav").c_str(), 400.0f);
	Load("SUPER_BIG_2", (soundfolder + "SBIG2.wav").c_str(), 400.0f);

	//Load("HEAVY_DAMAGE", (soundfolder + "heavy_damage.wav").c_str(), 70.0f);


	for (auto& s : hSounds)
		assert(s.second > 0);
}

SoundManager::~SoundManager()
{
	for (auto& s : hSounds)
		DeleteSoundMem(s.second);
	hSounds.clear();
}

void SoundManager::Update()
{
	for (auto& p : playSounds)
		p.second = 0;
}

void SoundManager::Play(const std::string& _name, const bool& _loop)
{
	if (playSounds.count(_name) == 0)
		playSounds.insert({ _name, 0 });
	else
	{
		playSounds[_name]++;
		if (playSounds[_name] > SOUND_SAME_TIME_MAX)
			return;
	}
	PlaySoundMem(hSounds[_name], _loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
}

void SoundManager::Stop(const std::string& _name)
{
	StopSoundMem(hSounds[_name]);
}

void SoundManager::Load(const std::string& _name, const std::string& _fileName, const float& _volume)
{
	hSounds.insert({ _name, LoadSoundMem(_fileName.c_str()) });
	ChangeVolumeSoundMem((int)((_volume / 100) * 255), hSounds[_name]);
}
