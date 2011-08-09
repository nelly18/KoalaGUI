#include "mythread.h"
#include "QMutex"
#include "QWaitCondition"

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
