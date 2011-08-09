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

signals:
    void onCommand(QString);
    void onChange(QString);

protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *);

private:
    void onEnter();
    void historyAdd(const QString &cmd);
    void historyBack();
    void historyForward();

public:
    bool isLocked;

private:
    QString prompt_;
    QStringList *history_;
    int historyPos_;
};

#endif // CONSOLE_H
