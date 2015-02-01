#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "include/constants.h"
#include "include/graphics.h"
#include "include/cam.h"
#include "include/tile.h"
//#include "include/world.h"

bool init();
void close();
bool load_tile_textures();
void render_map(int cam_pos_x, int cam_pos_y);
bool build_map(int level);

int main() {
	if (!init()) {
		printf("Failed to initialise!\n");
		return 1;
	}

	if (!load_tile_textures()) {
		printf("Failed to load tile textures!\n");
		return 1;
	}

	bool quit = false;
	SDL_Event e;

	if (!build_map(1)) {
		printf("Failed to build map!\n");
		return 1;
	}

	Camera::Camera cam = Camera::Camera::Camera(0,0);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_RIGHT:
						cam.set_pos_x(cam.get_pos_x() - 10);
						break;
					case SDLK_LEFT:
						cam.set_pos_x(cam.get_pos_x() + 10);
						break;
					case SDLK_UP:
						cam.set_pos_y(cam.get_pos_y() + 10);
						break;
					case SDLK_DOWN:
						cam.set_pos_y(cam.get_pos_y() - 10);
						break;
				}
			}
		}
		SDL_RenderClear(gRenderer);
		render_map(cam.get_pos_x(),cam.get_pos_y());
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}

void render_map(int cam_pos_x, int cam_pos_y) {
	for (int i = 0; i < Tiles::map.size(); ++i) {
		//if (Tiles::map.at(i).get_pos_x() >= cam_pos_x - Constants::TILE_SIZE_X && Tiles::map.at(i).get_pos_y() >= cam_pos_y - Constants::TILE_SIZE_Y) {
			Tiles::map.at(i).render(gRenderer);
		//}
	}
}

bool build_map(int level) {
	for (int i = 0; i < (Constants::WORLD_WIDTH*Constants::WORLD_HEIGHT); ++i) {
		if (map1[i] < Constants::TILE_TEXTURES_TOTAL && map1[i] > 0) {
			Tiles::map.emplace_back(Tiles::Tile(Tiles::tile_textures[map1[i]], (i * Constants::TILE_SIZE_X) % (Constants::WORLD_WIDTH*Constants::TILE_SIZE_X), (int)(i / Constants::WORLD_WIDTH)*Constants::TILE_SIZE_Y));
		} else {
			Tiles::map.emplace_back(Tiles::Tile(Tiles::tile_textures[Constants::FILL_TEXTURE], (i * Constants::TILE_SIZE_X) % (Constants::WORLD_WIDTH*Constants::TILE_SIZE_X), (int)(i / Constants::WORLD_WIDTH)*Constants::TILE_SIZE_Y));
		}
	}
	return true;
}

bool init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Lazy Reader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::VIEWPORT_WIDTH, Constants::VIEWPORT_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    
    return true;
}

void close() {
	for (int i = 0; i < Constants::TILE_TEXTURES_TOTAL; ++i) {
		SDL_DestroyTexture(Tiles::tile_textures[i]);
		Tiles::tile_textures[i] = NULL;
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	//SDL_FreeSurface(s_background);
	//s_background = NULL;
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool load_tile_textures() {
	SDL_Surface* tmp = NULL;
	tmp = IMG_Load("media/images/map_sprites/corner.png");

	Tiles::tile_textures[Constants::CORNER_TEXTURE] = SDL_CreateTextureFromSurface(gRenderer,tmp);
	if (Tiles::tile_textures[Constants::CORNER_TEXTURE] == NULL) {
		printf("Couldn't load CORNER_TEXTURE\n");
		return false;
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;
	tmp = IMG_Load("media/images/map_sprites/horisontal.png");

	Tiles::tile_textures[Constants::HORISONTAL_TEXTURE] = SDL_CreateTextureFromSurface(gRenderer,tmp);
	if (Tiles::tile_textures[Constants::HORISONTAL_TEXTURE] == NULL) {
		printf("Couldn't load HORISONTAL_TEXTURE\n");
		return false;
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;
	tmp = IMG_Load("media/images/map_sprites/vertical.png");

	Tiles::tile_textures[Constants::VERTICAL_TEXTURE] = SDL_CreateTextureFromSurface(gRenderer,tmp);
	if (Tiles::tile_textures[Constants::VERTICAL_TEXTURE] == NULL) {
		printf("Couldn't load VERTICAL_TEXTURE\n");
		return false;
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;
	tmp = IMG_Load("media/images/map_sprites/fill.png");

	Tiles::tile_textures[Constants::FILL_TEXTURE] = SDL_CreateTextureFromSurface(gRenderer,tmp);
	if (Tiles::tile_textures[Constants::FILL_TEXTURE] == NULL) {
		printf("Couldn't load FILL_TEXTURE\n");
		return false;
	}

	SDL_FreeSurface(tmp);
	tmp = NULL;

	printf("%i textures successfully loaded!\n", Constants::TILE_TEXTURES_TOTAL);

	return true;
}