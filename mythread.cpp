#include "QtCore/QMutex"
#include "QtCore/QWaitCondition"

#include "mythread.h"

MyThread::MyThread()
{
}

void MyThread::myMsleep(unsigned long msecs)
{
       QMutex mutex;
       mutex.lock();

       QWaitCondition waitCondition;
       waitCondition.wait(&mutex, msecs);

       mutex.unlock();
 }
