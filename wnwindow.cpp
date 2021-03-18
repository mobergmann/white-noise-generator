#include "wnwindow.h"

#include <iostream>
#include <QErrorMessage>
#include <QMessageBox>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

WNWindow::WNWindow()
    : WNWindow(1200, 720, 0)
{}

WNWindow::WNWindow(const uint width, const uint height, const uint buffer_size)
    : _is_init(false), _width(width), _heigth(height), _buffer_size(buffer_size)
{}

WNWindow::~WNWindow()
{
    // TODO check if renderer and windowdestruction has to be switched

    // Only if the init function has been called
    if (_is_init)
    {
        // Cleanup of renderer only if exists
        if (_renderer)
        {
            SDL_DestroyRenderer(_renderer);
            _renderer = nullptr;
        }

        // Cleanup of window only if exists
        if (_window)
        {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }
    }
}

void WNWindow::init()
{
    // Singelton
    if (_is_init)
    {
        return;
    }


    // Generate SDL main window
    _window = SDL_CreateWindow(
        "White Noise",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width,
        _heigth,
        SDL_WINDOW_SHOWN);
    if (!_window)
    {
        QMessageBox::critical(
            nullptr,
            "SDL window could not be generated: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyWindow(_window);
        _window = nullptr;

        return;
    }

    // Generate SDL renderer
    _renderer = SDL_CreateRenderer(
        _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        QMessageBox::critical(
            nullptr,
            "SDL could not generate renderer: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        return;
    }

    // Set Background Color (black)
    if (SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 0))
    {
        QMessageBox::critical(
            nullptr,
            "Could not set render draw color",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        return;
    }

    // Draw Background Color
    SDL_RenderPresent(_renderer);


    // Singleton
    _is_init = true;
}
