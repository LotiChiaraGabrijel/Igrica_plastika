#include "font.h"

SDL_Texture* load_font(SDL_Renderer* renderer) {
	
	SDL_Surface* surf = SDL_CreateRGBSurface(0, FONT_WIDTH, FONT_HEIGHT,
		32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	Uint32 white = SDL_MapRGB(surf->format, 255, 255, 255);
	Uint32 black = SDL_MapRGBA(surf->format, 0, 0, 0, 0);

	for (int y = 0; y < FONT_HEIGHT; ++y) {
		for (int x = 0; x < FONT_WIDTH; ++x) {
			Uint32 color = font_bitmap[y][x] ? white : black;
			((Uint32*)surf->pixels)[y * FONT_WIDTH + x] = color;
		}
	}

	SDL_Texture* tx = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_SetTextureScaleMode(tx, SDL_ScaleModeNearest);
	SDL_FreeSurface(surf);

	return tx;
}
void draw_char(SDL_Renderer* renderer, SDL_Texture* font_tex, unsigned char character, int cx, int cy, int scale) {

	SDL_Point cell = {
		(character - 32) % (FONT_WIDTH / GLYPH_WIDTH),
		(character - 32) / (FONT_WIDTH / GLYPH_WIDTH) };

	SDL_Rect srcrect = {
		cell.x * GLYPH_WIDTH,
		cell.y * GLYPH_HEIGHT,
		GLYPH_WIDTH,
		GLYPH_HEIGHT };
	SDL_Rect dstrect = {
		cx,
		cy,
		GLYPH_WIDTH * scale,
		GLYPH_HEIGHT * scale
	};
	SDL_RenderCopy(renderer, font_tex, &srcrect, &dstrect);

}
void draw_text(SDL_Renderer* renderer, SDL_Texture* font_tex,std::string text, int x, int y, int scale) {
	for (size_t i = 0; text[i] != '\0'; i++) {
		draw_char(renderer, font_tex,  text[i], x + i * GLYPH_WIDTH * scale, y, scale);
	}
}