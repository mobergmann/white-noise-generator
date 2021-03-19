#ifndef WNWINDOW_H
#define WNWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <QObject>
#include <QWidget>
#include <thread>

class WNWindow : public QWidget
{
    Q_OBJECT

private:
    bool _isInit;

    const uint  _width,
                _heigth;
    const uint  _probability,
                _genRate, _frameRate;
    const bool  _isFullscrene, _showCursor;

    bool _isPause;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    int* _pixles;

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
    WNWindow(const uint width, const uint height,
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
     * @brief Renders the White Noise
     */
    void render();

    /**
     * @brief Generates an array of Pixels
     */
    void generate();
};

#endif // WNWINDOW_H
