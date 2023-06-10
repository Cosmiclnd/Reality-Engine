#ifndef draw_hpp
#define draw_hpp

#include <SDL2/SDL.h>
#include <algorithm>

using Color = uint32_t;

void drawPixel(SDL_Surface *s, int x, int y, Color color);
void drawLine(SDL_Surface *s, int x1, int y1, int x2, int y2, Color color);
void drawRect(SDL_Surface *s, int x, int y, int w, int h, Color color);
void drawFilledRect(SDL_Surface *s, int x, int y, int w, int h, Color color);

#endif /* draw_hpp */
