#include "Animation.h"

/*
|animation|
	|tracks|
		track 0 | [1v 2v 3v 4v]
		track 1 | [1v 2v 3v 4v]
		track 2 | [1v 2v 3v 4v]
	|index 2|

animation:name {
	tracks: [
		track:name1 = [v1, v2, v3]
		track:name2 = [v1, v2, v3]
		track:name3 = [v1]
	]

	index: {v2} of track:name1 and track:name2; track:name3 is out of range size
}
*/

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

Animation::Animation()
{
}

void Animation::addAnimation(AnimationResource* res)
{
	animations.push_back(res);
}

void Animation::playAnimation(float dt, bool loop)
{
	for (int i = 0; i < animations.size(); i++) {
		if (animations[i]->name == currentAnimation) {
			if (playing) {
				if (index < animations[i]->length + 0.5) {
					if (clock.getElapsedTime().asMilliseconds() > speed) {
						for (int t_index = 0; t_index < animations[i]->tracks.size(); t_index++) {
							Track* currentTrack = animations[i]->tracks[t_index];

							for (int f_index = 0; f_index < currentTrack->frames.size(); f_index++) {
								Frame* currentFrame = currentTrack->frames[f_index];

								if (index >= currentFrame->at) {
									int diff = (currentTrack->frames[(f_index + 1) % currentTrack->frames.size()]->value - currentTrack->frameValue);

									if (currentTrack->frameValue)
										currentTrack->frameValue = lerp(currentTrack->frameValue, currentFrame->value, diff);
									else
										currentTrack->frameValue = currentFrame->value;

								}
								else {
									continue;
								}
							}
							
							index += speed;

							clock.restart();
							

							//std::cout << index;
						}
					}
				}
				else {
					if (loop) {
						index = 0.f;
						clock.restart();
					}
					else {
						playing = false;
					}
				}
			}
		}
	}
}

int AnimationResource::addTrack()
{
	Track* track = new Track;
	
	tracks.push_back(track);

	return tracks.size() - 1;
}

size_t AnimationResource::getTrackValue(int track)
{
	if (track < tracks.size()) {
		return tracks[track]->frameValue;
	}

	return NULL;
}
