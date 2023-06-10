#include "window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Window *window = new Window;
    FPSmanager fps;
    SDL_initFramerate(&fps);
    SDL_setFramerate(&fps, 30);
    SDL_Event event;
    bool done = false;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            }
            else
                window->handle(&event);
        }
        window->update();
        window->draw();
        SDL_framerateDelay(&fps);
    }
    delete window;
    SDL_Quit();
    return 0;
}
