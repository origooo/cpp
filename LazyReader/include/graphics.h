#include <SDL2/SDL.h>

enum Surfaces {
	SURFACES_SPLASH,
	SURFACES_RUN,
	SURFACES_HEADER_FONT,
	SURFACES_TOTAL
};

enum Button_images {
	SPLASH_OPEN_PDF,
	BUTTONS_TOTAL
};

class Button;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Surface* button_images[BUTTONS_TOTAL];
std::vector<Button> buttons;

SDL_Surface* surfaces[SURFACES_TOTAL];
SDL_Surface* s_background = NULL;
SDL_Texture* t_background = NULL;
SDL_Surface* s_header_font = NULL;
SDL_Texture* t_header_font = NULL;
SDL_Surface* s_button_splash_open_pdf = NULL;
SDL_Texture* t_button_splash_open_pdf = NULL;

SDL_Color c_dark_grey = {34,34,34,1};


class Button {
	private:
		SDL_Rect* rect;
		SDL_Rect* clip;
		SDL_Texture* tex;

	public:
		Button(const int w, const int h, SDL_Renderer* r, SDL_Surface* s);
		// ~Button();

		void show(SDL_Renderer* r);
		void set_position(const int x, const int y);
		void handle_event(SDL_Event e);
		SDL_Rect* get_rect();
		SDL_Rect* get_clip();
		SDL_Texture* get_tex();
};


Button::Button(const int w, const int h, SDL_Renderer* r, SDL_Surface* s) {
	tex = SDL_CreateTextureFromSurface(r,s);
	rect = new SDL_Rect{0,0,w,h};
	clip = new SDL_Rect{0,0,w,h};
	printf("CONSTRUCTOR\n");
}

void Button::show(SDL_Renderer* r) {
	SDL_RenderCopy(r,tex,clip,rect);
}

void Button::set_position(const int x, const int y) {
	rect->x = x;
	rect->y = y;
}

SDL_Rect* Button::get_rect() {
	return rect;
}

SDL_Rect* Button::get_clip() {
	return clip;
}

SDL_Texture* Button::get_tex() {
	return tex;
}

void Button::handle_event(SDL_Event e) {
	int x,y;
	SDL_GetMouseState(&x,&y);
	bool inside = false;

	if ((x > rect->x) && (x < rect->x + rect->w) && (y > rect->y) && (y < rect->y + rect->h)) {
		inside = true;
	} else {
		inside = false;
	}

	if (inside) {
        clip->x = 102;
        if (e.type == SDL_MOUSEBUTTONDOWN) {
        	clip->x = 204;
        } else {
        	clip->x = 102;
        }
	} else {
		clip->x = 0;
	}
}