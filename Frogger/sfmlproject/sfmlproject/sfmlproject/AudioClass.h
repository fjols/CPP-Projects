#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
class AudioClass
{
public:
	AudioClass(std::string sAudioName);
	void PlaySound();	//Plays the sound
private:
	sf::SoundBuffer sfBuffer;
	sf::Sound sfAudio;
};

