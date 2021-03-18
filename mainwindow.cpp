#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _wnWindow(nullptr)
{
    ui->setupUi(this);

    // Init SDL with video
    SDL_Init(SDL_INIT_VIDEO);
}

MainWindow::~MainWindow()
{
    // Cleanup window, if it exists
    if (_wnWindow)
    {
        delete _wnWindow;
        _wnWindow = nullptr;
    }

    SDL_Quit(); // Cleanup SDL

    delete ui;
}


void MainWindow::on_start_button_clicked()
{
    // Delete Window, if the window exists
    if (_wnWindow)
    {
        delete _wnWindow;
        _wnWindow = nullptr;
        return;
    }
    // Generate Window with the input values
    else
    {
        // Convert to uinteger (if not a valid int, then 0)
        uint width = ui->width_lineEdit->text().toUInt();
        uint height = ui->height_lineEdit->text().toUInt();
        uint buffer_size = ui->buffer_slider->value();

        _wnWindow = new WNWindow(width, height, buffer_size);
        _wnWindow->init();
    }
}
