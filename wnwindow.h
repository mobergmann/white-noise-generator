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

    /**
     * @brief Construct a new WNWindow Object
     */
    WNWindow();

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
    WNWindow(MainWindow* parent,
             const uint width, const uint height,
             const uint probability,
             const uint genRate, const uint frameRate,
             const bool isFullscrene, const bool showCursor);

    /**
     * @brief Destroys the WNWindow Object
     */
    virtual ~WNWindow();

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
     * @brief Generates an Array of Pixels
     */
    void generate();

    /**
     * @brief Renders the White Noise
     */
    void render();
};

#endif // WNWINDOW_H
