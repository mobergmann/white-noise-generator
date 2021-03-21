#include "whitenoise.h"

// QT
#include <QErrorMessage>
#include <QMessageBox>
#include <QTimer>
#include <QObject>
#include <QException>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// STD
#include <thread>


WhiteNoise::WhiteNoise(MainWindow *parent)
    : WhiteNoise(parent, 1200, 720, 45, 17, 17, false, true)
{
    // TODO message box
}

WhiteNoise::WhiteNoise(MainWindow* parent,
                       const uint width, const uint height,
                       const uint probability,
                       const uint genRate, const uint frameRate,
                       const bool isFullscrene, const bool showCursor)
    : QWidget(nullptr)
    , _parent(parent)
    , _isPause(false), _pixles(new bool[width * height])
    , _width(width), _heigth(height)
    , _probability(probability), _genRate(genRate), _frameRate(frameRate)
    , _isFullscrene(isFullscrene), _showCursor(showCursor)
{
    // Generate SDL main window
    _window = SDL_CreateWindow("White Noise",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _width, _heigth,
                               SDL_WINDOW_SHOWN);
    if (!_window)
    {
        QMessageBox::critical(
            _parent,
            "SDL could not generate the window: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyWindow(_window);
        _window = nullptr;

        throw QException();
        return;
    }

    // Generate SDL renderer
    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        QMessageBox::critical(
            _parent,
            "SDL could not generate the renderer: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        throw QException();
        return;
    }


    // Set Fullscrene
    if (SDL_SetWindowFullscreen(_window, _isFullscrene))
    {
        QMessageBox::critical(
            _parent,
            "SDL could not set fullscreen: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        throw QException();
        return;
    }

    // Set if Cursor should be shown
    if (SDL_ShowCursor(_showCursor) < 0)
    {
        QMessageBox::critical(
            _parent,
            "SDL could not set cursor state: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        throw QException();
        return;
    }


    // Check Setting a Color (Black)
    if (SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0))
    {
        QMessageBox::critical(
            _parent,
            "Could not set Renders Drawcolor: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        throw QException();
        return;
    }

    // Check SDL_RenderClear
    if (SDL_RenderClear(_renderer))
    {
        QMessageBox::critical(
            _parent,
            "Could not clear the Screen: ",
            SDL_GetError(),
            QMessageBox::Ok);

        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
        SDL_DestroyWindow(_window);
        _window = nullptr;

        throw QException();
        return;
    }


    // First Time generation and rendering to not start with a blank Screen
    generate();
    render();


    /* Start Timer(s), which generates a White Noise and then renders the White Noise. */

    // Only create one Timer, if the rates are equal,
    // to prevent update-losses due to timer inperfection
    if (_genRate == _frameRate)
    {
        // Schedule Generation and Rendering every _genRate or _frameRate milliseconds
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &WhiteNoise::generate);
        connect(timer, &QTimer::timeout, this, &WhiteNoise::render);
        timer->start(_genRate);
    }
    else
    {
        // Schedule Generation every _genRate milliseconds
        QTimer *genTimer = new QTimer(this);
        connect(genTimer, &QTimer::timeout, this, &WhiteNoise::generate);
        genTimer->start(_genRate);

        // Schedule Renering every _fooRate milliseconds
        QTimer *renderTimer = new QTimer(this);
        connect(renderTimer, &QTimer::timeout, this, &WhiteNoise::render);
        renderTimer->start(_frameRate);
    }
}

WhiteNoise::~WhiteNoise()
{
    // Cleanup the renderer only if it exists
    if (_renderer)
    {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    // Cleanup the window only if it exists
    if (_window)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}


bool WhiteNoise::isPaused() const
{
    return _isPause;
}

void WhiteNoise::togglePause()
{
    _isPause = !_isPause;
}


void WhiteNoise::generate()
{
    if (_isPause)
    {
        return;
    }


    /* Special Cases, to Speed thinks up */

    if (_probability == 0)          // No Noises => do Nothing
    {
        for (uint i = 0; i < _width * _heigth; i++)
        {
            _pixles[i] = 0;
        }
    }
    else if (_probability == 100)   // Only Noises => everything Noised
    {
        for (uint i = 0; i < _width * _heigth; i++)
        {
            _pixles[i] = 1;
        }
    }
    else                            // Radom Number of Noises
    {

        for (uint i = 0; i < _width * _heigth; i++)
        {
            // Calculate if Pixel is noised // TODO better explaination
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
}

void WhiteNoise::render()
{
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
