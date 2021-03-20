#ifndef WNWINDOW_H
#define WNWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <QObject>
#include <QWidget>
#include <QThread>

#include "mainwindow.h"
    class MainWindow;

class WNWindow : public QWidget
{
    Q_OBJECT

private:
    MainWindow* _mw;
    bool _isPause;

    const uint  _width,
                _heigth;

    const uint  _probability,
                _genRate, _frameRate;

    const bool  _isFullscrene, _showCursor;


    int* _pixles;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    QThread pollThread;


public:

    /**
     * @brief Construct a new WNWindow object
     */
    WNWindow();

    /**
     * @brief Construct a new WNWindow object
     * 
     * @param width width of the SDL Window
     * @param height height of the SDL Window
     * @param buffer_size size of the buffer
     */
    WNWindow(MainWindow* window,
             const uint width, const uint height,
             const uint probability,
             const uint genRate, const uint _frameRate,
             const bool isFullscrene, const bool showCursor);

    /**
     * @brief Destroy the WNWindow object
     */
    virtual ~WNWindow();

    /**
     * @brief returns, if the stream is paused.
     * @return …
     */
    bool isPaused() const;

    /**
     * @brief inverts the pause statement.
     */
    void togglePause();

public slots:

    /**
     * @brief polls for an sdl exit event
     */
    void poll_exit();

    // TODO remove
    inline void generate_and_render()
    {
        generate();
        render();
    }

    /**
     * @brief Generates an array of Pixels
     */
    void generate();

    /**
     * @brief Renders the White Noise
     */
    void render();
};

#endif // WNWINDOW_H
