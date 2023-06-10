#include "window.hpp"
#include "draw.hpp"

Window::Window()
    : __state(State::MAIN), __progress(0), __dragging(false)
{
    __raw = SDL_CreateWindow("Reality Engine", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    __screen = SDL_GetWindowSurface(__raw);
    __updateProgRect();
}

Window::~Window()
{
    SDL_FreeSurface(__screen);
    SDL_DestroyWindow(__raw);
}

void Window::update()
{
    if (__state == State::MAIN)
        __updateMain();
}

void Window::draw()
{
    if (__state == State::MAIN)
        __drawMain();
    SDL_UpdateWindowSurface(__raw);
}

void Window::handle(SDL_Event *event)
{
    if (__state == State::MAIN)
        __handleMain(event);
}

void Window::__updateMain()
{
    __player.update();
    __updateProgRect();
}

void Window::__drawMain()
{
    SDL_FillRect(__screen, nullptr, 0xff000000);
    drawFilledRect(__screen, 100, 550, 600, 10, 0xff3f3f3f);
    drawRect(__screen, 100, 550, 600, 10, 0xffc0c0c0);
    drawFilledRect(__screen,
        __progRect.x, __progRect.y, __progRect.w, __progRect.h, 0xff707070);
    drawRect(__screen,
        __progRect.x, __progRect.y, __progRect.w, __progRect.h, 0xffd0d0d0);
}

void Window::__handleMain(SDL_Event *event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point p { event->button.x, event->button.y };
        if (event->button.button == SDL_BUTTON_LEFT &&
            SDL_PointInRect(&p, &__progRect))
            __dragging = true;
    }
    else if (event->type == SDL_MOUSEBUTTONUP) {
        if (event->button.button == SDL_BUTTON_LEFT)
            __dragging = false;
    }
    else if (event->type == SDL_MOUSEMOTION) {
        if (__player.paused && __dragging) {
            __progress += event->motion.xrel * (1 / 600.0);
            __player.tick = __player.maxTicks * __progress;
            __updateProgRect();
        }
    }
    else if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_p)
            __player.paused = !__player.paused;
        else if (event->key.keysym.sym == SDLK_LEFT) {
            __progress -= 0.1;
            __player.tick = __player.maxTicks * __progress;
            __updateProgRect();
        }
        else if (event->key.keysym.sym == SDLK_RIGHT) {
            __progress += 0.1;
            __player.tick = __player.maxTicks * __progress;
            __updateProgRect();
        }
    }
}

void Window::__updateProgRect()
{
    if (__player.tick >= __player.maxTicks)
        __player.tick = __player.maxTicks - 1;
    else if (__player.tick < 0)
        __player.tick = 0;
    __progress = __player.getProgress();
    __progRect.x = 92 + __progress * 600;
    __progRect.y = 540;
    __progRect.w = 16;
    __progRect.h = 30;
}
