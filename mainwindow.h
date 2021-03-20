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
    bool _is_wnKilled;
    Ui::MainWindow* ui;
    WNWindow* _wnWindow;

private slots:
    void on_start_button_clicked();

    void on_fullscreen_checkBox_stateChanged(int arg1);

    void on_pause_button_clicked(bool checked);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief returns if the white noise window has been killed
     * @return …
     */
    inline bool is_wnKilled() { return _is_wnKilled; }

    /**
     * @brief Quits/ closes the White-Noise Window.
     */
    void quit_wn();
};
#endif // MAINWINDOW_H
