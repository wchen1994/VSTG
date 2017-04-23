#ifndef __RECORDER_H_
#define __RECORDER_H_

#include <SFML/Audio.hpp>
#include <iostream>

class Recorder{
private:
	std::string filename;
	sf::SoundBufferRecorder bufferRecorder;
	sf::SoundBuffer buffer;
	unsigned sampleRate;
public:
	Recorder(unsigned sampleRate);
	~Recorder();
	void SetSaveDir(std::string filename);
	bool Save();
	void Record();
	void Stop();
};

Recorder::Recorder(unsigned sampleRate = 44100){
	this->sampleRate = sampleRate;
}

Recorder::~Recorder(){
}

void Recorder::SetSaveDir(std::string filename){
	this->filename = filename;
}

bool Recorder::Save(){
	if (!filename.empty()){
		buffer = bufferRecorder.getBuffer();
		return buffer.saveToFile(filename);
	}
	return false;
}

void Recorder::Record(){
	bufferRecorder.start(sampleRate);
}

void Recorder::Stop(){
	bufferRecorder.stop();
}

#endif
