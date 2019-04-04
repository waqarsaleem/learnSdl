#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <cstdio>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window.
bool init();
// Loads media.
bool loadMedia();
// Frees Media and shuts down SDL.
void close();

// The window we will render to.
SDL_Window *gWindow = NULL;
// The surface contained by the window.
SDL_Surface *gScreenSurface = NULL;
// The image we will load and show on the screen.
SDL_Surface *gHelloWorld = NULL;

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
      // Apply the image.
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

      // Update the surface.
      SDL_UpdateWindowSurface(gWindow);

      // // Wait 2 seconds.
      // SDL_Delay(50000);

      // Start event loop.
      bool quit = false;
      SDL_Event event;
      while (!quit) {
	if (SDL_PollEvent( & event)) {
	  if (event.type == SDL_QUIT) {
            quit = true;
	  }
	}
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

bool loadMedia() {
  // Loading success flag.
  bool success = true;

  // Load splash image.
  gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
  if (gHelloWorld == NULL) {
    std::cout << "Unable to load image: 02_getting_an_image_on_the_screen/hello_world.bmp! SDL_Error: " <<
      SDL_GetError() << "\n";
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surface.
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  // Destroy window.
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL.
  SDL_Quit();	  
}
