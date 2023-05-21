#include "Font.h"

Font::Font(std::string font_filename) {
	fontTexture = new sf::Texture();
	fontTexture->loadFromFile(font_filename);
}

void Font::drawString(SpriteBatch& batch, const std::string& text, sf::Vector2f offset)
{
	for (size_t i = 0; i < text.size(); i++) {
		int char_index = ALPHABET.find(text[i]);

		if (char_index != std::string::npos) {
			batch.draw(*fontTexture, sf::FloatRect(((i * (8 + 8)) + offset.x), offset.y, 16, 16), sf::IntRect(char_index * 8, 0, 8, 8));
		}
	}
}