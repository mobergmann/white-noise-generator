#include "pollthread.h"

PollThread::PollThread()
{}

PollThread::PollThread(MainWindow* window)
    : QThread(), _mw(window)
{}

PollThread::~PollThread()
{}
