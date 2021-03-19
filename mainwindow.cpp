#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QScreen>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _wnWindow(nullptr)
{
    ui->setupUi(this);

    // Disable Pause Button
    ui->pause_button->setDisabled(true); // TODO make default state disabed in designer

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

    // Cleanup SDL
    SDL_Quit();

    delete ui;
}


void MainWindow::on_start_button_clicked()
{
    // Delete Window, if the window already exists
    if (_wnWindow)
    {
        delete _wnWindow;
        _wnWindow = nullptr;

        // Turn Start Button into a Stop Button
        ui->start_button->setText("Start");

        // Disable Pause Button
        ui->pause_button->setDisabled(true);
        ui->pause_button->setText("Pause");

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
            _wnWindow = new WNWindow(width, height,
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

            delete _wnWindow;
            _wnWindow = nullptr;

            return; // no ui changes and stop
        }


        // Turn Stop Button into a Start Button
        ui->start_button->setText("Stop");

        // Enable Pause Button
        ui->pause_button->setDisabled(false);
        ui->pause_button->setText("Pause");


        // First Time generation and render to not start with a blank screen
        _wnWindow->generate();
        _wnWindow->render();
    }
}

void MainWindow::on_fullscreen_checkBox_stateChanged(int state)
{
    bool isFullscrene = ui->fullscreen_checkBox->isChecked();

    // Set the Screen Size as the Resolution
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    ui->width_lineEdit->setText(QString::number(width));
    ui->height_lineEdit->setText(QString::number(height));

    // disable width input
    ui->width_label->setDisabled(isFullscrene);
    ui->width_lineEdit->setDisabled(isFullscrene);
    // disable height input
    ui->height_label->setDisabled(isFullscrene);
    ui->height_lineEdit->setDisabled(isFullscrene);
}

void MainWindow::on_pause_button_clicked(bool checked)
{
    // only execute, when a window exists
    if (_wnWindow)
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

        _wnWindow->togglePause();
    }
}
