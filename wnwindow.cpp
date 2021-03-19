#include "wnwindow.h"

#include <iostream>
#include <QErrorMessage>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


WNWindow::WNWindow()
    : WNWindow(1200, 720, 45, 17, 17, false, true)
{}

WNWindow::WNWindow(const uint width, const uint height,
                   const uint probability,
                   const uint genRate, const uint frameRate,
                   const bool isFullscrene, const bool showCursor)
    : _width(width), _heigth(height),
      _probability(probability), _genRate(genRate), _frameRate(frameRate),
      _isFullscrene(isFullscrene), _showCursor(showCursor),
      _isPause(false),
      _pixles(new int[_width * _heigth])
{
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
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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


    // Set Fullscrene
    SDL_SetWindowFullscreen(_window, _isFullscrene);

    // Set if Cursor should be shown
    SDL_ShowCursor(_showCursor);


    // Set Background Color (black)
    if (SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0))
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

    // Clear the Screen
    SDL_RenderClear(_renderer);


    // Draw Background Color
    SDL_RenderPresent(_renderer);

    // only create one timer, if the rates are equal,
    // to prevent update-losses
    if (_genRate == _frameRate)
    {
        // Sedule Generation every x seconds
        QTimer *genTimer = new QTimer(this);
        connect(genTimer, SIGNAL(timeout()), this, SLOT(generate_and_render()));
        genTimer->start(_genRate);
    }
    else
    {
        // Sedule Generation every x seconds
        QTimer *genTimer = new QTimer(this);
        connect(genTimer, SIGNAL(timeout()), this, SLOT(generate()));
        genTimer->start(_genRate);

        // Sedule Renering every x seconds
        QTimer *renderTimer = new QTimer(this);
        connect(renderTimer, SIGNAL(timeout()), this, SLOT(render()));
        renderTimer->start(_frameRate);
    }
}

WNWindow::~WNWindow()
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


bool WNWindow::isPaused() const
{
    return _isPause;
}

void WNWindow::togglePause()
{
    _isPause = !_isPause;
}


void WNWindow::generate()
{
    if (_isPause)
    {
        return;
    }

    if (_probability == 0)
    {
        return;
    }

    for (uint i = 0; i < _width * _heigth; i++)
    {
        // Check if Pixel is noised // TODO better comment :(
        if (rand() > (float)RAND_MAX * ((float)_probability) / 100)
        {
            _pixles[i] = 1;
        }
        else
        {
            _pixles[i] = 0;
        }
    }
}

void WNWindow::render()
{
    if (_isPause)
    {
        return;
    }

    // Draw Background (black)
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);

    // Set Star Color (white)
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

    // Check all Pixels, if they should be drawn
    for (uint i = 0; i < _width * _heigth; i++)
    {
        if (_pixles[i] == 1)
        {
            SDL_RenderDrawPoint(_renderer, i % _width, (int)((float)i / _width));
        }
    }

    // Draw Everything
    SDL_RenderPresent(_renderer);
}
