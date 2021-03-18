#ifndef WNWINDOW_H
#define WNWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class WNWindow
{
private:
    bool _is_init;

    const uint _width, _heigth;
    const uint _buffer_size;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

public:
    WNWindow();
    WNWindow(const uint width, const uint height, const uint buffer_size);
    ~WNWindow();

    void init();
};

#endif // WNWINDOW_H
