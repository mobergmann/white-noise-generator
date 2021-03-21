#ifndef WHITENOISE_H
#define WHITENOISE_H

// QT
#include <QWidget>
#include <QObject>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Forward declaration
#include "mainwindow.h"
    class MainWindow;


class WhiteNoise : public QWidget
{
    Q_OBJECT


private:
    /// Reference to the SDL_Window, on which is drawn
    SDL_Window* _window;
    /// Reference to the SDL_Renderer, which draws
    SDL_Renderer* _renderer;
    /// Reference to a Mainwindow
    MainWindow* _parent;

    /// If the White Noise is currently paused (no rendering and generation)
    bool _isPause;
    /// Array, which resembels each Pixel, which is drawn
    int* _pixles;

    /* Parameter from the constructor */
    const uint  _width,
                _heigth;
    const uint  _probability,
                _genRate,
                _frameRate;
    const bool  _isFullscrene,
                _showCursor;


public:
    explicit WhiteNoise(MainWindow *parent = nullptr);

    /**
     * @brief Construct a new WNWindow Object
     * @param parent: Reference to the Parent (MainWindow)
     * @param width: Width of the SDL Window
     * @param height: Height of the SDL Window
     * @param probability: Probability, that a Pixel is noised
     * @param genRate: Rate at which a new Noise should be generated
     * @param frameRate: Rate at which the SDL_Window should redraw
     * @param isFullscrene: Bool, if the Window should be displayed
     * @param showCursor: If the Cursor should be displayed
     */
    WhiteNoise(MainWindow* parent,
             const uint width, const uint height,
             const uint probability,
             const uint genRate, const uint frameRate,
             const bool isFullscrene, const bool showCursor);

    /**
     * @brief Destroys the WNWindow Object
     */
    virtual ~WhiteNoise();

    /**
     * @brief Returns, if the Nosie Generation is Paused
     */
    bool isPaused() const;

    /**
     * @brief Inverts the Pause Statement
     */
    void togglePause();


public slots:

    /**
     * @brief Generates an White Noised array
     */
    void generate();

    /**
     * @brief Renders the White Noise
     */
    void render();

};

#endif // WHITENOISE_H
