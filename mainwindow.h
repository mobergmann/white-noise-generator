#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "wnwindow.h"
    class WNWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /// Reference to the UI Object of the MainWindow
    Ui::MainWindow* ui;

    /// Reference to a White Noise SDL Window Container.
    WNWindow* _wnWindow;

    /**
     * @brief Polls for an SDL_Quit Event and calls the kill_wn() Method.
     */
    void poll_exit();

    /**
     * @brief Quits/ Closes the White Noise Window.
     */
    void kill_wn();


private slots:
    void on_start_button_clicked();

    void on_fullscreen_checkBox_stateChanged(int arg1);

    void on_pause_button_clicked(bool checked);


public:
    /**
     * @brief Constructs a MainWindow
     * @param Parent, derived from QMainWindow
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructs the MainWindow
     */
    ~MainWindow();

};
#endif // MAINWINDOW_H
