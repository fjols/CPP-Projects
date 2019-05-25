#include "AudioClass.h"



AudioClass::AudioClass(std::string sAudioName)
{
	if (!sfBuffer.loadFromFile(sAudioName)) {	//If it can't find the audio display an error.
		std::cout << "Error" << std::endl;
	}
	else {
		sfAudio.setBuffer(sfBuffer); //Set the sound to the buffer.
		std::cout << "AUDIO LOADED" << std::endl;
	}
}

void AudioClass::PlaySound()
{
	sfAudio.setVolume(50);	//100 is the default volume.
	sfAudio.play();			//Plays the file.
}


