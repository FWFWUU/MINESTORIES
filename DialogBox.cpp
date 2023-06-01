#include "DialogBox.h"

std::vector<std::string> DialogContainer::lines;

//sf::Texture* Resources::IconsTexture;

DialogBox::DialogBox(SpriteBatch* b, Font* f)
{
	batch = b;
	font = f;

	//texture.loadFromFile("Assets/Textures/icons.png");

	sb.loadFromFile("Assets/Audio/Paper Flip.wav");
	sd.setBuffer(sb);
}

void DialogBox::showDialog(const std::string dialog_name)
{
	if (latest_dialog != dialog_name) {
		current_dialog = dialog_name;

		page = 0;

		latest_dialog = current_dialog;
	}
}

void DialogBox::loadDialog(const std::string filename)
{
	file.open(filename, std::ios::in);

	if (file) {
		std::string dialog_line;

		std::string dname;
		std::vector<std::string> lines;

		while (std::getline(file, dialog_line)) {
			dialogues.push_back(dialog_line);
		}
	}

			/*
			if (dname.size() < 1) {
				if (dialog_line[0] == '[') {
					std::string name;

					for (int i = 1; i < dialog_line.size(); i++) {
						if (dialog_line[i] != ']') {
							name += dialog_line[i];
						}
						else {
							dname = name;
							//lines.clear();

							std::cout << dname << std::endl;

							break;
						}
					}
				}
			}
			else {
				if (dialog_line[0] == '[') {
					std::string word;

					for (int i = 1; i < dialog_line.size(); i++) {
						if (dialog_line[i] != ']')
							word += dialog_line[i];
						else {
							if (word == "end") {
								DialogContainer* dc = new DialogContainer(dname);
								for (int y = 0; y < lines.size(); y++) {
									dc->lines.push_back(lines[y]);
								}
								dialogs.push_back(dc);

								//dc = NULL;

								dname = "";
								lines.clear();

								

								break;

								
							}
						}

					}
				}
				else {
					lines.push_back(dialog_line);

					//std::cout << dc->lines.size() << "=" << dc->name << std::endl;

				}
			}
		}
	}*/

	file.close();
}

void DialogBox::update()
{
	/*for (DialogContainer* d : dialogs) {
		if (d->name.compare(current_dialog) == 0) {
			sf::Vector2f book_pos = batch->getWindow()->mapPixelToCoords(sf::Vector2i(batch->getWindow()->getView().getSize().x - ((57 * 3)), (76 * 3) / 2));

			sf::FloatRect book_rect(book_pos.x, book_pos.y, 57 * 3, 76 * 3);

			batch->draw(texture, book_rect, sf::IntRect(46, 32, 57, 76));

			sf::Vector2f arrow_next_pos = sf::Vector2f(book_pos.x + (book_rect.width + 10 * 2), book_pos.y);

			sf::FloatRect arrow_next_rect(arrow_next_pos.x, arrow_next_pos.y, 10 * 3, 7 * 3);

			batch->draw(texture, arrow_next_rect, sf::IntRect(30, 32, 10, 7));

			sf::Vector2f ms = batch->getWindow()->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*batch->getWindow())));

			touchNext = false;

			if (arrow_next_rect.intersects(sf::FloatRect(ms.x, ms.y, 1, 1))) {
				touchNext = true;
			}

			//std::cout << ms.x << " - " << arrow_next_rect.left << std::endl;
			
			int correlati = 0;
			int line = 0;

			for (int j = 0; j < d->lines[page % d->lines.size()].size(); j++) {
				std::string ch(&d->lines[page % d->lines.size()][j], 1);
				
				font->drawString(*batch, ch, sf::Vector2f(20 + (8 * correlati), 20 + (8 * line)) + sf::Vector2f(book_rect.left, book_rect.top), 8, sf::Color::Black);

				if (correlati <= 14) {
					correlati++;
				} else {
					line++;
					correlati = 0;
				}
			}


		}
	}*/

	if (isOnConversation) {
		sf::Vector2f book_pos = batch->getWindow()->mapPixelToCoords(sf::Vector2i(batch->getWindow()->getView().getSize().x - ((57 * 3)), (76 * 3) / 2));

		sf::FloatRect book_rect(book_pos.x, book_pos.y, 57 * 3, 76 * 3);

		batch->draw(Resources::IconsTexture, book_rect, sf::IntRect(46, 32, 57, 76));

		sf::Vector2f arrow_next_pos = sf::Vector2f(book_pos.x + (book_rect.width + 10 * 2), book_pos.y);

		sf::FloatRect arrow_next_rect(arrow_next_pos.x, arrow_next_pos.y, 10 * 3, 9 * 3);

		batch->draw(Resources::IconsTexture, arrow_next_rect, sf::IntRect(107, 31, 10, 9));

		sf::Vector2f ms = batch->getWindow()->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*batch->getWindow())));

		touchNext = false;

		if (arrow_next_rect.intersects(sf::FloatRect(ms.x, ms.y, 1, 1))) {
			touchNext = true;
		}

		int correlati = 0;
		int line = 0;

		if (dialogueLineIndex < dialogueEndLine) {
			for (int j = 0; j < dialogues[dialogueLineIndex % dialogues.size()].size(); j++) {
				std::string ch(&dialogues[dialogueLineIndex % dialogues.size()][j], 1);

				font->drawString(*batch, ch, sf::Vector2f(20 + (8 * correlati), 20 + (8 * line)) + sf::Vector2f(book_rect.left, book_rect.top), 8, sf::Color::Black);

				if (correlati <= 14) {
					correlati++;
				}
				else {
					line++;
					correlati = 0;
				}
			}
		}
		else {
			isOnConversation = false;
		}

		
	}
}

void DialogBox::nextPage()
{
	page++;
}

void DialogBox::setCurrentDialog(int start_line, int end_line)
{
	dialogueLineIndex = start_line - 1;
	dialogueEndLine = end_line;

	isOnConversation = true;
}

void DialogBox::nextDialogue()
{
	dialogueLineIndex++;
	sd.play();
}
