#ifndef SERIALGATE_H
#define SERIALGATE_H

#include <QtCore/QString>

#ifdef Q_WS_WIN
#include <qt_windows.h>
#endif //Q_WS_WIN

#include "defines.h"

#define MAX_WIN_PORT 255

class SerialGate
{

public:
    enum IN_LINES_NAME {CTS, DSR, RING, RLSD};
    enum OUT_LINES_NAME {DTR, RTS};

public:
    static SerialGate* instance();
    ~SerialGate();
    bool state;
    bool open(const int port, const int baud);
    int send(const char* buff, const int szBuff);
    int send(const QString &str);
    int recv(char* buff, int numBytesToRead);
    QString recv(int numBytesToRead);
    void setLine(OUT_LINES_NAME ln, bool state);
    bool line(IN_LINES_NAME ln);
    void close();
    void clean();

protected:
    SerialGate();

private:
    static SerialGate* instance_;
#ifdef Q_WS_WIN
        HANDLE hFile_;
#endif //Q_WS_WIN
};

#endif // SERIALGATE_H

