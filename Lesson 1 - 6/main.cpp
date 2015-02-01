#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

// Enums and Structs
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// Global variables
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function declarations
bool init(); //Starts up SDL and creates window
bool loadMedia(); //Loads media
void close(); //Frees media and shuts down SDL
SDL_Surface* loadSurface( std::string path ); //Loads individual image

SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL; //The surface contained by the window
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]; //The images that correspond to a keypress
SDL_Surface* gCurrentSurface = NULL; //Current displayed image
//SDL_Surface* gStretchedSurface = NULL;

int main(int argc, char* args[]) {
    //Start up SDL and create window
    if(!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if(!loadMedia()){
            printf("Failed to load media!\n");
        } else {
        	
            bool quit = false; //Main loop flag
            SDL_Event e; //Event handler
			//Set default current surface
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            while (!quit) {

                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    } else if(e.type == SDL_KEYDOWN) {
                        switch(e.key.keysym.sym) {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                //Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
	            //Apply the image
	            //SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
	            //Update the surface
	            SDL_UpdateWindowSurface(gWindow);
	        }
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            } else {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("media/images/misc/press.png");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("media/images/misc/up.png");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("media/images/misc/down.png");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("media/images/misc/left.png");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("media/images/misc/right.png");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }
    return success;
}

void close() {
	//Deallocate surfaces
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {

	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    } else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0); // Last parameter was NULL in tutorial...
		if (optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}