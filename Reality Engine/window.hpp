#ifndef window_hpp
#define window_hpp

#include <SDL2/SDL.h>

#include "play.hpp"

enum class State {
    MAIN
};

class Window {
    SDL_Window *__raw;
    SDL_Surface *__screen;
    State __state;
    Player __player;
    double __progress;
    SDL_Rect __progRect;
    bool __dragging;

public:
    Window();
    ~Window();
    
    void update();
    void draw();
    void handle(SDL_Event *event);
    
private:
    void __updateMain();
    void __drawMain();
    void __handleMain(SDL_Event *event);
    void __updateProgRect();
};

#endif /* window_hpp */
