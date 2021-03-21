#include "mainwindow.h"
#include "ui_mainwindow.h"

// QT
#include <QMessageBox>
#include <QScreen>
#include <QTimer>

// STD
#include <iostream>
#include <thread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _wn(nullptr)
{
    ui->setupUi(this);

    // Disable Pause Button
    ui->pause_button->setDisabled(true); // TODO make default state disabed in designer

    // Init SDL with video
    SDL_Init(SDL_INIT_VIDEO);



    // Starts a Thread, that polls for an SDL_Quit
    _pollThread = new std::thread(&MainWindow::poll_exit, this);
}

MainWindow::~MainWindow()
{
    // Terminate and Delete Polling Thread
    if (_pollThread)
    {
        delete _pollThread;
        _pollThread = nullptr;
    }

    // Cleanup window (to prevent possible segfault)
    if (_wn)
    {
        delete _wn;
        _wn = nullptr;
    }

    // Cleanup SDL
    SDL_Quit();

    delete ui;
}


/**
 * @brief Polls as long as the white noise window exists
 * and as long as the SDL_QUIT event hasen't been send
 */
void MainWindow::poll_exit()
{
    SDL_Event e;

    while (true)
    {
        SDL_PollEvent(&e);

        if (e.type == SDL_QUIT)
        {
            std::cout << "Print Kill" << std::endl;

            // kill the white noise window
            kill_wn();

            std::cout << "Print Killed" << std::endl;
        }
    }
}

/**
 * @brief Kills/ quits/ closes the White Noise Window.
 */
void MainWindow::kill_wn()
{
    std::cout << "Start kill" << std::endl;

    // If Window already deleted, then skip,
    // to prevent segfault
    if (!_wn)
    {
        std::cout << "Already killed" << std::endl;
        return;
    }

    std::cout << "Delete White Noise Pointer" << std::endl;
    delete _wn;
    _wn = nullptr;

    std::cout << "Canging UI" << std::endl;

    // Turn Start Button into a Stop Button
    ui->start_button->setText("Start");

    // Disable Pause Button
    ui->pause_button->setDisabled(true);
    ui->pause_button->setText("Pause");


    std::cout << "Finished Killing" << std::endl;
}


void MainWindow::on_start_button_clicked()
{
    // Delete Window, if it exists
    if (_wn)
    {
        kill_wn();
        return;
    }
    // Generate Window with the input values
    else
    {
        // Convert to unsigned integer (if not a valid int, default is 0)
        uint width          = ui->width_lineEdit->text().toUInt(),
             height         = ui->height_lineEdit->text().toUInt(),
             probability    = ui->probability_lineEdit->text().toUInt(),
             gen_rate       = ui->gen_lineEdit->text().toUInt(),
             frame_rate     = ui->frameRate_lineEdit->text().toUInt();

        bool isFullscrene   = ui->fullscreen_checkBox->isChecked(),
             showCursor     = ui->showCursor_checkBox->isChecked();


        try
        {
            // Create SDL Window and initialize it
            _wn = new WhiteNoise(this,
                                 width, height,
                                 probability, gen_rate, frame_rate,
                                 isFullscrene, showCursor);
        }
        catch (...)
        {
            // shows an error message
            QMessageBox::critical(
                nullptr,
                "Critical Error:",
                "SDL Could not be initalized. Please restart the application and try again.",
                QMessageBox::Ok);

            delete _wn;
            _wn = nullptr;

            return; // no ui changes and stop
        }


        // Turn Stop Button into a Start Button
        ui->start_button->setText("Stop");

        // Enable Pause Button
        ui->pause_button->setDisabled(false);
        ui->pause_button->setText("Pause");


        // First Time generation and rendering to not start with a blank Screen
        _wn->generate();
        _wn->render();


//        // delete pollThread, if its already exists
//        // shouldn't happen, only to be sure
//        if (_pollThread)
//        {
//            delete _pollThread;
//            _pollThread = nullptr;
//        }
    }
}

void MainWindow::on_fullscreen_checkBox_stateChanged(int state)
{
    // Get Screensize (Resolution)
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int screenHeight = screenGeometry.height();
    int screenWidth = screenGeometry.width();


    // Set Fullscrene to Screene Resulotion
    ui->height_lineEdit->setText(QString::number(screenHeight));
    ui->width_lineEdit->setText(QString::number(screenWidth));

    // Disable Width Input
    ui->width_label->setDisabled(state);
    ui->width_lineEdit->setDisabled(state);

    // Disable Height Input
    ui->height_label->setDisabled(state);
    ui->height_lineEdit->setDisabled(state);
}

void MainWindow::on_pause_button_clicked(bool checked)
{
    // only execute, when a window exists
    if (_wn)
    {
        // Change Text of Button
        if (checked)
        {
            ui->pause_button->setText("Play");
        }
        else
        {
            ui->pause_button->setText("Pause");
        }

        _wn->togglePause();
    }
}
