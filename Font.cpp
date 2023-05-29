#include "Font.h"

Font::Font(std::string font_filename, sf::Vector2i grid) {
	fontTexture = new sf::Texture();
	fontTexture->loadFromFile(font_filename);

	grid_size = grid;
}

Font::Font(sf::Texture* texture, sf::Vector2i grid)
{
	fontTexture = texture;

	grid_size = grid;
}

void Font::drawString(SpriteBatch& batch, const std::string& text, sf::Vector2f offset, int font_size, sf::Color color)
{
	sf::Color c_color = color;

	for (size_t i = 0; i < text.size(); i++) {
		int char_index = ALPHABET.find(std::tolower(text[i]));
		

		if (char_index != std::string::npos) {
			batch.draw(fontTexture, sf::FloatRect(((i * (font_size)) + offset.x), offset.y, font_size, font_size), sf::IntRect(char_index * grid_size.x, 0, grid_size.x, grid_size.y), c_color);
		}
		else {
			if (text[i] == ESPECIAL_COLOR_RED)
				c_color = sf::Color::Red;

			if (text[i] == ESPECIAL_COLOR_YELLOW)
				c_color = sf::Color::Yellow;
		}
	}
}