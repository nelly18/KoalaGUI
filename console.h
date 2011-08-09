#ifndef CONSOLE_H
#define CONSOLE_H

#include <QtGui/QPlainTextEdit>

class Console : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    void output(QString);
    void scrollDown();
    void insertPrompt(bool insertNewBlock = true);
    bool isLocked;

signals:
    void onCommand(QString);
    void onChange(QString);

protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *);

private:
    QString prompt;
    QStringList *history;
    int historyPos;

private:
    void onEnter();
    void historyAdd(QString);
    void historyBack();
    void historyForward();
};

#endif // CONSOLE_H
