#include <iostream>
#include "SerialGate.h"
#include <Winspool.h>



 bool SerialGate::Open(int port, int baud)
{
        wchar_t COM_string[20];
        swprintf(COM_string, TEXT("\\\\.\\COM%i"), port);

        m_hFile = CreateFile(COM_string, GENERIC_READ|GENERIC_WRITE, 0, NULL,
           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);


        if(m_hFile == INVALID_HANDLE_VALUE)
        {
                return false;
        }


        DCB dcb;
        GetCommState(m_hFile, &dcb);

        COMMTIMEOUTS CommTimeOuts;
        CommTimeOuts.ReadIntervalTimeout         = 30;
        CommTimeOuts.ReadTotalTimeoutMultiplier  = 2;
        CommTimeOuts.ReadTotalTimeoutConstant    = 60;
        CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
        CommTimeOuts.WriteTotalTimeoutConstant   = 0;
        CommTimeOuts.WriteTotalTimeoutMultiplier = 0;

        SetCommTimeouts(m_hFile, &CommTimeOuts);


        dcb.ByteSize = 8;
        dcb.Parity   = NOPARITY;
        dcb.StopBits = TWOSTOPBITS;
        dcb.BaudRate = baud;

        SetCommState(m_hFile, &dcb);

        this->state = true;
        return true;
}

SerialGate::SerialGate()
{
        this->state = false;
}

SerialGate::~SerialGate()
{
        this->Close();
}

void SerialGate::Close()
{
    if (this->state)
        CloseHandle(m_hFile);
    this -> state = false;
}

void SerialGate::Clean()
{
        if(!state)
                return;

        PurgeComm(m_hFile, PURGE_TXCLEAR|PURGE_RXCLEAR);
}


int SerialGate::Send(const char* buff, const int szBuff)
{
        if(!state)
                return 0;


        DWORD lpdwBytesWrittens = 0;
        WriteFile(m_hFile, buff, szBuff, &lpdwBytesWrittens, NULL);

        return lpdwBytesWrittens;
}

int SerialGate::Recv(char* buff, int numBytesToRead)
{
        if(!state)
                return 0;

        DWORD dwBytesRead = 0;
        ReadFile(m_hFile, buff, numBytesToRead, &dwBytesRead, NULL);

        return dwBytesRead;
}

void SerialGate::SetLine(OUT_LINES_NAME ln, bool state)
{
        if(!state)
                return ;

        unsigned char value;

        if(ln == DTR)
        {
                if(state)
                        value = 6;
                else
                        value = 5;
        }


        if(ln == RTS)
        {
                if(state)
                        value = 4;
                else
                        value = 3;
        }

        EscapeCommFunction(m_hFile, value);
}

 bool SerialGate::GetLine(IN_LINES_NAME ln)
{
        if(!state)
                return 0;

        unsigned long ul = 0;

        GetCommModemStatus(m_hFile, &ul);

        if(ul == 0x10 && ln == CTS)
        {
                return true;
        }

        if(ul == 0x20 && ln == DSR)
        {
                return true;
        }

        if(ul == 0x40 && ln == RING)
        {
                return true;
        }

        if(ul == 0x80 && ln == RLSD)
        {
                return true;
        }

        return false;
}

 int SerialGate::Recv(QString &str, int numBytesToRead)
 {
     char s[buffer_size];
      int rcv = Recv(s, numBytesToRead);

     if (rcv > 0){
         for (int i = 0; i < rcv; i++)
             str += s[i];
     }
     return rcv;
 }

 int SerialGate::Send(const QString &str)
 {
     return Send(str.toAscii().data(), str.size ());
 }
