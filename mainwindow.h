#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "wnwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_button_clicked();

    void on_fullscreen_checkBox_stateChanged(int arg1);

    void on_pause_button_clicked(bool checked);

private:
    Ui::MainWindow* ui;

    WNWindow* _wnWindow;
};
#endif // MAINWINDOW_H
