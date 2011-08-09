#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
public:
    MyThread();
    void myMsleep(unsigned long msecs);
};

#endif // MYTHREAD_H
