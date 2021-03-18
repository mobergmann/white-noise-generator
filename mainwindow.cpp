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

    connect(ui->probability_lineEdit, SIGNAL(textEdited(QString)),
            ui->probability_slider,
            SLOT(rag_valuechanged()));

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

        // Change Text of Button
        ui->start_button->setText("Start");

        return;
    }
    // Generate Window with the input values
    else
    {
        // Convert to unsigned integer (if not a valid int, default is 0)
        uint width          = ui->width_lineEdit->text().toUInt(),
             height         = ui->height_lineEdit->text().toUInt(),
             probability    = ui->probability_lineEdit->text().toUInt(),
             gen_rate       = ui->fps_lineEdit->text().toUInt(),
             buffer_size    = ui->buffer_lineEdit->text().toUInt();
        bool isFullscrene   = ui->fullscreen_checkBox->isChecked(),
             showCursor     = ui->showCursor_checkBox->isChecked();


        // Create SDL Window and initialize it
        _wnWindow = new WNWindow(width, height,
                                 probability, gen_rate, buffer_size,
                                 isFullscrene, showCursor);
        _wnWindow->init();
        if (!_wnWindow->isInit())
        {
            QMessageBox::critical(
                nullptr,
                "Critical Error:",
                "SDL Could not be initalized. Please restart the application and try again.",
                QMessageBox::Ok);

            delete _wnWindow;
            _wnWindow = nullptr;

            return;
        }

        // Change Text of Button
        ui->start_button->setText("Stop");


        // First Time generation and render
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

    // disable width and height input
    ui->width_label->setDisabled(isFullscrene);
    ui->width_lineEdit->setDisabled(isFullscrene);
    ui->height_label->setDisabled(isFullscrene);
    ui->height_lineEdit->setDisabled(isFullscrene);
}
