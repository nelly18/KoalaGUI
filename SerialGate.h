#ifndef SERIALGATE_H
#define SERIALGATE_H

#endif // SERIALGATE_H
#include <Windows.h>
#define MAX_WIN_PORT 255
#include <QString>
#include "defines.h"
struct Port
{
        unsigned char Id;
        bool Availbl;
};


class SerialGate
{
public:

        enum IN_LINES_NAME {CTS, DSR, RING, RLSD};
        enum OUT_LINES_NAME {DTR, RTS};

        SerialGate();
        ~SerialGate();

        bool state;
        bool Open(const int port, const int baud);
        int Send(const char* buff, const int szBuff);
        int Send(const QString &str);
        int Recv(char* buff, int numBytesToRead);
        int Recv(QString &str, int numBytesToRead);
        void SetLine(OUT_LINES_NAME ln, bool state);
        bool GetLine(IN_LINES_NAME ln);
        void Close();
        void Clean();

private:
        HANDLE m_hFile;

};
