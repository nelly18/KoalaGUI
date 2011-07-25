#ifndef SERIALGATE_H
#define SERIALGATE_H

#endif // SERIALGATE_H
//#include <Windows.h>
#define MAX_WIN_PORT 255
#include <QtCore/QString>
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
		bool Open(int port, int baud);
		int Send(QString) {}
		int Send(char* buff, int szBuff);
		int Recv(QString) {}
		int Recv(char* buff, int szBuff);
		void SetLine(OUT_LINES_NAME ln, bool state);
		bool GetLine(IN_LINES_NAME ln);
		void Close();
		void Clean();

private:
		//HANDLE m_hFile;

};
