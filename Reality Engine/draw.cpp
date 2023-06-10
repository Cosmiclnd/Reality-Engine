#include "draw.hpp"

static inline void _drawPixel(SDL_Surface *s, int x, int y, Color color)
{
    if (x < 0 || y < 0 || x >= s->w || y >= s->h) return;
    uint32_t *buf;
    buf = (uint32_t *) s->pixels + y * s->pitch / 4 + x;
    *buf = color;
}

void drawPixel(SDL_Surface *s, int x, int y, Color color)
{
    if (SDL_MUSTLOCK(s))
        if (SDL_LockSurface(s) < 0) return;
    _drawPixel(s, x, y, color);
    if (SDL_MUSTLOCK(s))
        SDL_UnlockSurface(s);
}

void drawLine(SDL_Surface *s, int x1, int y1, int x2, int y2, Color color)
{
    if (SDL_MUSTLOCK(s))
        if (SDL_LockSurface(s) < 0) return;
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int erro = (dx > dy ? dx : -dy) / 2;
    while (x1 != x2 || y1 != y2) {
        _drawPixel(s, x1, y1, color);
        int e2 = erro;
        if (e2 > -dx) {
            erro -= dy; x1 += sx;
        }
        if (e2 < dy) {
            erro += dx; y1 += sy;
        }
    }
    if (SDL_MUSTLOCK(s))
        SDL_UnlockSurface(s);
}

void drawRect(SDL_Surface *s, int x, int y, int w, int h, Color color)
{
    if (SDL_MUSTLOCK(s))
        if (SDL_LockSurface(s) < 0) return;
    for (int i = 0; i < w; i++) {
        _drawPixel(s, x + i, y, color);
        _drawPixel(s, x + i, y + h - 1, color);
    }
    for (int i = 0; i < h; i++) {
        _drawPixel(s, x, y + i, color);
        _drawPixel(s, x + w - 1, y + i, color);
    }
    if (SDL_MUSTLOCK(s))
        SDL_UnlockSurface(s);
}

void drawFilledRect(SDL_Surface *s, int x, int y, int w, int h, Color color)
{
    if (SDL_MUSTLOCK(s))
        if (SDL_LockSurface(s) < 0) return;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            _drawPixel(s, x + i, y + j, color);
        }
    }
    if (SDL_MUSTLOCK(s))
        SDL_UnlockSurface(s);
}
