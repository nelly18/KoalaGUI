#include <iostream>

#ifdef Q_WS_WIN
#include <Winspool.h>
#endif //Q_WS_WIN32

#include "serialgate.h"
SerialGate *SerialGate::instance_ = 0;
SerialGate *SerialGate::instance()
{
    if (instance_ == 0) {
        instance_ = new SerialGate;
    }

    return instance_;
}

SerialGate::~SerialGate()
{
    if (instance_ == this) {
        close();
        instance_ = 0;
    }
}

bool SerialGate::open (int port, int baud)
{
#ifdef Q_WS_WIN
    wchar_t COM_string[20];
    swprintf (COM_string, TEXT ("\\\\.\\COM%i"), port);

    hFile_ = CreateFile (COM_string, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


    if (hFile_ == INVALID_HANDLE_VALUE) {
        return false;
    }

    DCB dcb;
    GetCommState (hFile_, &dcb);

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout         = 30;
    CommTimeOuts.ReadTotalTimeoutMultiplier  = 2;
    CommTimeOuts.ReadTotalTimeoutConstant    = 60;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant   = 0;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;

    SetCommTimeouts (hFile_, &CommTimeOuts);


    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = TWOSTOPBITS;
    dcb.BaudRate = baud;

    SetCommState (hFile_, &dcb);

    this->state = true;
#endif //Q_WS_WIN32
    return true;
}

SerialGate::SerialGate()
{
    this->state = false;
}

void SerialGate::close()
{
#ifdef Q_WS_WIN

    if (this->state)
        CloseHandle (hFile_);

    this -> state = false;
#endif //Q_WS_WIN32
}

void SerialGate::clean()
{
#ifdef Q_WS_WIN

    if (!state)
        return;

    PurgeComm (hFile_, PURGE_TXCLEAR | PURGE_RXCLEAR);
#endif //Q_WS_WIN32
}


int SerialGate::send (const char *buff, const int szBuff)
{
#ifdef Q_WS_WIN

    if (!state)
        return 0;

    DWORD lpdwBytesWrittens = 0;
    WriteFile (hFile_, buff, szBuff, &lpdwBytesWrittens, NULL);

    return lpdwBytesWrittens;
#else //Q_WS_WIN32
    return 0;
#endif //Q_WS_WIN32
}

int SerialGate::recv (char *buff, int numBytesToRead)
{
#ifdef Q_WS_WIN

    if (!state)
        return 0;

    DWORD dwBytesRead = 0;
    ReadFile (hFile_, buff, numBytesToRead, &dwBytesRead, NULL);

    return dwBytesRead;
#else //Q_WS_WIN32
    return 0;
#endif //Q_WS_WIN32
}

void SerialGate::setLine (OUT_LINES_NAME ln, bool state)
{
#ifdef Q_WS_WIN

    if (!state)
        return ;

    unsigned char value;

    if (ln == DTR) {
        if (state)
            value = 6;
        else
            value = 5;
    }


    if (ln == RTS) {
        if (state)
            value = 4;
        else
            value = 3;
    }

    EscapeCommFunction (hFile_, value);
#endif //Q_WS_WIN32
}

bool SerialGate::line (IN_LINES_NAME ln)
{
#ifdef Q_WS_WIN

    if (!state)
        return 0;

    unsigned long ul = 0;

    GetCommModemStatus (hFile_, &ul);

    if (ul == 0x10 && ln == CTS) {
        return true;
    }

    if (ul == 0x20 && ln == DSR) {
        return true;
    }

    if (ul == 0x40 && ln == RING) {
        return true;
    }

    if (ul == 0x80 && ln == RLSD) {
        return true;
    }

#endif //Q_WS_WIN32
    return false;
}

QString SerialGate::recv (int numBytesToRead)
{
    char s[numBytesToRead + 1];
    int rcv = recv (s, numBytesToRead);
    s [rcv] = '\0';
    return QString (s);
}

int SerialGate::send (const QString &str)
{
    return send (str.toAscii().data(), str.size ());
}



