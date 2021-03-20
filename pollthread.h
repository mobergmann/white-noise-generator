#ifndef POLLTHREAD_H
#define POLLTHREAD_H

#include <QThread>
#include <mainwindow.h>

class PollThread : public QThread
{
    Q_OBJECT

private:
    MainWindow* _mw;

public:
    PollThread();

    PollThread(MainWindow* window);

    virtual ~PollThread();

    void run() override
    {
        SDL_Event e;
        do
        {
            SDL_PollEvent(&e);
        }
        while(e.type != SDL_QUIT);

        _mw->quit_wn();
        return;
    }
};

#endif // POLLTHREAD_H
