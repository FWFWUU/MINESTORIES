#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "SpriteBatch.h"
#include "Font.h"
#include "Resources.h"

struct DialogContainer {
public:
	std::string name;
	static std::vector<std::string> lines;

	DialogContainer(std::string name) : name(name) {};
};

class DialogBox
{
public:
	bool isOnConversation = false;
	bool touchNext = false;
	bool touchPrevious = false;

	std::string current_dialog;

	DialogBox(SpriteBatch* b, Font* f);

	void showDialog(const std::string dialog_name);
	void loadDialog(const std::string filename);
	void update();
	void nextPage();
	void setCurrentDialog(int start_line, int end_line);
	void nextDialogue();

private:
	std::vector<DialogContainer*> dialogs;
	std::vector<std::string> dialogues;
	SpriteBatch* batch;
	Font* font;
	sf::Texture texture;
	
	std::fstream file;

	int page = 0;

	std::string latest_dialog;

	int dialogueEndLine = 0;
	int dialogueLineIndex = 0;

	sf::SoundBuffer sb;
	sf::Sound sd;
};

