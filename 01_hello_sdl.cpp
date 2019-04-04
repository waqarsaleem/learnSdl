#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <cstdio>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv) {
  // The window we will render to.
  SDL_Window *window = NULL;

  // The surface contained by the window.
  SDL_Surface *screenSurface = NULL;

  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " <<
      SDL_GetError() << "\n";
  }
  else {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN);
    if (window == NULL) {
      std::cout << "Window could not be created! SDL_Error: " <<
	SDL_GetError() << "\n";
    }
    else {
      // Get window surface.
      screenSurface = SDL_GetWindowSurface(window);

      // Fill the surface white.
      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      // Update the surface.
      SDL_UpdateWindowSurface(window);

      // Wait 2 seconds.
      SDL_Delay(50000);
    }
  }
  // Destroy window.
  SDL_DestroyWindow(window);

  // Quit SDL.
  SDL_Quit();
  
  return 0;
}
