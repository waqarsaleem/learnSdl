#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
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

// Window size.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we will render to.
SDL_Window *gWindow = NULL;
// The surface contained by the window.
SDL_Surface *gScreenSurface = NULL;
// Current displayed image.
SDL_Surface *gStretchedSurface = NULL;

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
      
      // While application is running.
      while (!quit) {
	// Handle events on queue.
	while (SDL_PollEvent(&e) != 0) {
	  // User requests quit.
	  if (e.type == SDL_QUIT) {
            quit = true;
	  }
	}
	// Apply the image.
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

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
    // Create window.
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      std::cout << "Window could not be created! SDL_Error: " <<
	SDL_GetError() << "\n";
      success = false;
    }
    else {
      // Initialize PNG loading.
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
	std::cout << "SDL_Image could not initialize! SDL_Image error: " <<
	  IMG_GetError() << "\n";
	success = false;
      }
      else {
	// Get window surface.
	gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
    }
  }
  return success;
}

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* optimizedSurface = NULL;
  
  // Load image at specified path.
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Unable to load image: " << path << "! SDL_image Error: " <<
      IMG_GetError() << "\n";
  }
  else {
    // Convert surface to screen format.
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      std::cout << "Unable to optimize image: " << path << "! SDL_Error: " <<
	SDL_GetError() << "\n";
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool loadMedia() {
  // Loading success flag.
  bool success = true;

  // Load default surface.
  gStretchedSurface = loadSurface("06_extension_libraries_and_loading_other_image_formats/loaded.png");
  if (gStretchedSurface == NULL) {
    std::cout << "Failed to load image to stretch!\n";
    success = false;
  }
  
  return success;
}

void close() {
  // Deallocate surfaces.
  SDL_FreeSurface(gStretchedSurface);
  gStretchedSurface = NULL;

  // Destroy window.
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL.
  SDL_Quit();	  
}
