#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <cstdio>
#include <iostream>
#include <string>

// --------------------
// -------------------- Prototypes --------------------
// --------------------

// Starts up SDL and creates window.
bool init();
// Loads media.
bool loadMedia();
// Frees Media and shuts down SDL.
void close();
// Loads individual image.
SDL_Surface* loadSurface(std::string path);

// --------------------
// -------------------- Globals --------------------
// --------------------

// Key press surfaces constants.
enum KeyPressSurfaces {
		       KEY_PRESS_SURFACE_DEFAULT,
		       KEY_PRESS_SURFACE_UP,
		       KEY_PRESS_SURFACE_DOWN,
		       KEY_PRESS_SURFACE_LEFT,
		       KEY_PRESS_SURFACE_RIGHT,
		       KEY_PRESS_SURFACE_TOTAL,
};

// Window size.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we will render to.
SDL_Window *gWindow = NULL;
// The surface contained by the window.
SDL_Surface *gScreenSurface = NULL;
// The image we will load and show on the screen.
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// Current displayed image.
SDL_Surface *gCurrentSurface = NULL;

// --------------------
// -------------------- Main --------------------
// --------------------

int main(int argc, char **argv) {
  // Start up SDL and create window.
  if (!init()) {
    std::cout << "Failed to initialize!\n";
  }
  else {
    if (!loadMedia()) {
      std::cout << "Failed to load media!\n";
    }
    else {
      // Main loop flag.
      bool quit = false;
      // Event handler.
      SDL_Event e;
      // Set default current surface.
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
      
      // While application is running.
      while (!quit) {
	// Handle events on queue.
	while (SDL_PollEvent(&e) != 0) {
	  // User requests quit.
	  if (e.type == SDL_QUIT) {
            quit = true;
	  }
	  else if (e.type == SDL_KEYDOWN) {
	    // Select surfaces based on key press.
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
	// Apply the image.
	SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

	// Update the surface.
	SDL_UpdateWindowSurface(gWindow);
      }
 
    }
  }
  // Free resources and quit SDL.
  close();
  
  return 0;
}

// --------------------
// -------------------- Implementation --------------------
// --------------------

bool init() {
  // Initialization flag.
  bool success = true;

  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " <<
      SDL_GetError() << "\n";
    success = false;
  }
  else {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      std::cout << "Window could not be created! SDL_Error: " <<
	SDL_GetError() << "\n";
      success = false;
    }
    else {
      // Get window surface.
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

SDL_Surface* loadSurface(std::string path) {
  // Load image at specified path.
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Unable to load image: " << path << "! SDL_Error: " <<
      SDL_GetError() << "\n";
  }
  return loadedSurface;
}

bool loadMedia() {
  // Loading success flag.
  bool success = true;

  // Load default surface.
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    std::cout << "Failed to load default image!\n";
    success = false;
  }

  // Load up surface.
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_presses/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    std::cout << "Failed to load up image!\n";
    success = false;
  }

  // Load down surface.
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_presses/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    std::cout << "Failed to load down image!\n";
    success = false;
  }

  // Load left surface.
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_presses/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    std::cout << "Failed to load left image!\n";
    success = false;
  }

  // Load right surface.
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04_key_presses/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    std::cout << "Failed to load right image!\n";
    success = false;
  }
  
  return success;
}

void close() {
  // Deallocate surfaces.
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
    gKeyPressSurfaces[i] = NULL;
  }

  // Destroy window.
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL.
  SDL_Quit();	  
}
