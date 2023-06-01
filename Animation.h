#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

struct Frame {
	size_t value = 0; //frame attribute value
	float at = 0.0; //time of frame on length
};

struct Track {
	std::vector<Frame*> frames; //array of frames
	size_t frameValue = 0; //current frame attribute value
};

struct AnimationResource {
	const char* name; //animation name
	std::vector<Track*> tracks; //tracks of frames
	float length = 1.f; //length of animation

	int addTrack();
	template<typename T> void insertFrame(int track, T value, float time);
	size_t getTrackValue(int track);
};

class Animation
{
private:
	std::vector<AnimationResource*> animations;
	sf::Clock clock;

public:
	std::string currentAnimation = "DEFAULT";

	bool playing = true;

	float index = 0.f;
	float speed = 0.5f;

	Animation();
	
	void addAnimation(AnimationResource* res);
	void playAnimation(float dt, bool loop = true);
};


template<typename T>
inline void AnimationResource::insertFrame(int track, T value, float time)
{
	if (track < tracks.size()) {
		Frame* frame = new Frame;
		frame->at = time;
		frame->value = value;

		tracks[track]->frames.push_back(frame);
	}
}