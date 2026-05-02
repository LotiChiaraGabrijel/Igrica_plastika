#include "win_screen.h"
#include <fstream>
#include <cstring>
using namespace std;
WinScreen::WinScreen(SDL_Renderer* renderer) {
	background = IMG_LoadTexture(renderer, "slike/win.png");
	font_tex = load_font(renderer);

}
void WinScreen::render(SDL_Renderer* renderer) {
	destRect.w = 1024;
	destRect.h = 900;
	destRect.x = 0;
	destRect.y = 0;
	SDL_RenderCopy(renderer, background, nullptr, &destRect);
	display_score(renderer);
}
struct player_info {
	char name_player[30];
	int score_player;
};

bool WinScreen::handleEvents(SDL_Event& e) {
	if (e.type == SDL_QUIT) return 0;
	return 1;
}
void WinScreen::update(float deltaTime) {
}

bool WinScreen::is_in_vector(char name[30], vector<const char*> vec) {
	for (int i = 0; i < vec.size(); i++) {
		if (strcmp(vec[i], name) == 0) return 1;
	}
	return 0;
}


void WinScreen::display_score(SDL_Renderer* renderer) {
	ifstream file("scores.dat", ios::binary);

	player_info s;
	draw_text(renderer, font_tex, "Leaderboard:", 410, 40, 2);
	vector<player_info> vec;
	if (file.is_open()) {
		while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
			vec.push_back(s);
		}
		file.close();
	}

	//sort the scores
	player_info temp;
	for (int i = 0; i < vec.size(); i++) 
		for (int j = 0; j < vec.size() - i - 1; j++) {
			if (vec[j].score_player < vec[j + 1].score_player) {
				strcpy_s(temp.name_player, vec[j].name_player);
				temp.score_player = vec[j].score_player;

				strcpy_s(vec[j].name_player, vec[j+1].name_player);
				vec[j].score_player = vec[j+1].score_player;

				strcpy_s(vec[j+1].name_player, temp.name_player);
				vec[j + 1].score_player = temp.score_player;

			}
		}
	//remove duplicate names
	vector<const char*> seen;
	vector<player_info> final_list;

	for (int i = 0; i < vec.size(); i++) {
		if (!(is_in_vector(vec[i].name_player, seen))) {
			seen.push_back(vec[i].name_player);
			final_list.push_back(vec[i]);
		}
	}
	//show the scores
	int y = 70;
	string text;
	for (int i = 0; i < final_list.size(); i++) {
		text = string(final_list[i].name_player) + " " + to_string(final_list[i].score_player);
		draw_text(renderer, font_tex,text , 410, y, 2);
		y += 30;
	}



}

WinScreen::~WinScreen() {
	if (background)
		SDL_DestroyTexture(background);
	if (font_tex)
		SDL_DestroyTexture(font_tex);
} 