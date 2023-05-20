#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() {
	
}

void AnimatedSprite::AddRegion(sf::IntRect region) {
	regions.push_back(region);
}

void AnimatedSprite::AddTextureImage(sf::Texture & texture) {
	setTexture(texture, true);
}

void AnimatedSprite::PlayAnimation(bool loop) {
	if (playing) {
		if (timer.getElapsedTime().asSeconds() > time) {
			if (region_index < regions.size() - 1) {
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

		if (region_index < regions.size())
		{
			setTextureRect(regions[region_index]);
			//std::cout << getTextureRect().width << "<>" << getTextureRect().left << std::endl;

			setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
		}
	}	
}