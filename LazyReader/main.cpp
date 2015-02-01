//#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "include/constants.h"
#include "include/graphics.h"

bool loadGUI();
bool loadMedia();
bool init();
void close();
void switch_background(int index);
void render_splash();
void events_splash();
void render_run();
void events_run();

bool quit = false;
int game_state = STATE_SPLASH;
SDL_Event e;

// Button buttons[BUTTONS_TOTAL] = {};

int main() {
	if (!init()) {
		printf("Failed to initialise!\n");
		return 1;
	}
	if (!loadMedia()) {
		printf("Failed to load media!\n");
		return 1;
	}
	if (!loadGUI()) {
		printf("Failed to load UI!\n");
		return 1;
	}
	
    while (!quit) {
        switch (game_state) {
        	/*
			* GAME STATE IS SPLASH SCREEN/MAIN MENU
        	*/
        	case STATE_SPLASH:
        		render_splash();
        		events_splash();
        		break;
        	/*
			* GAME STATE IS RUN PROGRAM
        	*/
    		case STATE_RUN:
    			render_run();
    			events_run();
    			break;
        }
    }
    close();
	return 0;
}

void render_splash() {
	SDL_RenderClear(gRenderer);

	switch_background(SURFACES_SPLASH);

    SDL_Rect q_background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(gRenderer, t_background, NULL, &q_background);

	s_header_font = surfaces[SURFACES_HEADER_FONT];
	t_header_font = SDL_CreateTextureFromSurface(gRenderer, s_header_font);
	SDL_Rect q_header_font = {SCREEN_WIDTH/2-s_header_font->w/2, 0, s_header_font->w, s_header_font->h};
	SDL_RenderCopy(gRenderer, t_header_font, NULL, &q_header_font);


	buttons.at(SPLASH_OPEN_PDF).show(gRenderer);

	SDL_RenderPresent(gRenderer);
}

void events_splash() {
	while (SDL_PollEvent(&e) != 0) {

		buttons.back().handle_event(e);

		if (e.type == SDL_QUIT) {
    		quit = true;
		} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			printf("mouse click\n");
		} else if (e.type == SDL_MOUSEMOTION) {
    		int x,y;
    		SDL_GetMouseState(&x,&y);
            printf("x,y: %d, %d \n", x, y);
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_r:
					game_state = STATE_RUN;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
			}
		} 
	}
}

void render_run() {
	SDL_RenderClear(gRenderer);

	switch_background(SURFACES_RUN);

	SDL_Rect q_background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(gRenderer, t_background, NULL, &q_background);

	SDL_RenderPresent(gRenderer);
}

void events_run() {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
    		quit = true;
		} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			printf("mouse click\n");
		} else if (e.type == SDL_MOUSEMOTION) {
    		int x,y;
    		SDL_GetMouseState(&x,&y);
            printf("x,y: %d, %d \n", x, y);
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					game_state = STATE_SPLASH;
					break;
				default:
					break;
			}
		} 
	}
}

void switch_background(int index) {
	s_background = surfaces[index];
	t_background = SDL_CreateTextureFromSurface(gRenderer, s_background);
}

bool loadGUI() {
	int number_of_buttons = 0;

	buttons.emplace_back(Button(102, 29, gRenderer, button_images[SPLASH_OPEN_PDF]));
	buttons.back().set_position(100,100);
	++number_of_buttons;

	if (buttons.size() != number_of_buttons) {
		return false;
	}

	return true;
}

bool loadMedia() {

	// IMAGES
	surfaces[SURFACES_SPLASH] = IMG_Load("media/images/misc/splash_bg.png");
	if (surfaces[SURFACES_SPLASH] == NULL) {
		printf("Couldn't load SURFACES_SPLASH\n");
		return false;
	}

	surfaces[SURFACES_RUN] = IMG_Load("media/images/misc/background.png");
	if (surfaces[SURFACES_RUN] == NULL) {
		printf("Couldn't load SURFACES_RUN\n");
		return false;
	}

	// ICONS
	button_images[SPLASH_OPEN_PDF] = IMG_Load("media/images/buttons/load_pdf.png");
	if (button_images[SPLASH_OPEN_PDF] == NULL) {
		printf("Couldn't load OPEN_PDF button for splash screen!\n");
		return false;
	}

	// FONTS & FONT SURFACES
	TTF_Font* header_font = TTF_OpenFont("media/fonts/Georgia Italic.ttf", 70);
	if (header_font == NULL) {
		printf("Couldn't load font!\n");
		return false;
	}

	surfaces[SURFACES_HEADER_FONT] = TTF_RenderText_Blended(header_font, "lazy reader", c_dark_grey);
	if (surfaces[SURFACES_HEADER_FONT] == NULL) {
		printf("Couldn't generate SURFACES_HEADER_FONT\n");
		return false;
	}
	
	return true;
}

bool init() {
    // Init SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create Window
    gWindow = SDL_CreateWindow("Lazy Reader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Init image support
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    } else {
        s_background = SDL_GetWindowSurface(gWindow);
    }

    // Init TTF support
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void close() {
	for (int i = 0; i < SURFACES_TOTAL; ++i) {
		SDL_FreeSurface(surfaces[i]);
		surfaces[i] = NULL;
	}

	for (int i = 0; i < BUTTONS_TOTAL; ++i) {
		SDL_FreeSurface(button_images[i]);
		button_images[i] = NULL;
		delete(buttons.at(i).get_rect());
		delete(buttons.at(i).get_clip());
		SDL_DestroyTexture(buttons.at(i).get_tex());
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}