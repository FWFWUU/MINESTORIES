#include "AnimatedSprite.h"

std::vector<sf::Sprite*> AnimatedSprite::sprites_list;

AnimatedSprite::AnimatedSprite() {
	sprites_list.push_back(this);
}

/*void AnimatedSprite::AddRegion(const sf::IntRect& region) {
	regions.push_back(region);
}*/

AnimationFrame* AnimatedSprite::AddAnimation(const std::string& name, sf::Texture& texture)
{
	for (AnimationFrame* frame : frames) {
		if (frame->name == name)
			return frame;
	}
	
	AnimationFrame* frame = new AnimationFrame;
	frame->name = name;
	frame->texture = &texture;
	frames.push_back(frame);

	return frames.back();
}

void AnimatedSprite::AddTextureImage(sf::Texture& texture) {
	setTexture(texture, true);
}

void AnimatedSprite::PlayAnimation(bool loop) {
	for (AnimationFrame* frame : frames) {
			if (frame->name == currentAnimation) {
				setTexture(*frame->texture, true);

				if (region_index < frame->regions.size())
				{
					setTextureRect(frame->regions[region_index]);

					setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
				}

				if (playing) {
					if (timer.getElapsedTime().asSeconds() > time) {
						if (region_index < frame->regions.size() - 1) {
							region_index++;

							timer.restart();
						}
						else {
							if (loop)
							{
								region_index = 0;
								timer.restart();
							}

						}
					}
				}
				else {
					region_index = 0;
				}
			}
		}
}

std::vector<sf::Sprite*> AnimatedSprite::getSpritesList()
{
	return sprites_list;
}
