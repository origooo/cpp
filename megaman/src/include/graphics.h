#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

namespace Graphics {
	static SDL_Window* gWindow = NULL;
	static SDL_Renderer* gRenderer = NULL;
	struct Float_Rect {
		float x;
		float y;
		int w;
		int h;
	};
}
#endif //GRAPHICS_H_