#include "console.h"

Console::Console(QWidget *parent) :
QPlainTextEdit(parent)
{
    prompt = "koala> ";

    this->setFrameShape(QFrame::Panel);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::blue);
    setPalette(p);

    history = new QStringList;
    historyPos = 0;
}

void Console::keyPressEvent(QKeyEvent *event)
{
    if (isLocked) return;

    if(((event->key() >= 0x20 && event->key() <= 0x7e) || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
       && (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::ShiftModifier))
            QPlainTextEdit::keyPressEvent(event);

     if (event->modifiers() == Qt::KeypadModifier)
         QPlainTextEdit ::keyPressEvent(event);

    if(event->key() == Qt::Key_Backspace
       && event->modifiers() == Qt::NoModifier
       && textCursor().positionInBlock() > prompt.length())
            QPlainTextEdit::keyPressEvent(event);

    if(event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier)
        onEnter();

    if(event->key() == Qt::Key_Up && event->modifiers() == Qt::NoModifier)
        historyBack();

    if(event->key() == Qt::Key_Down && event->modifiers() == Qt::NoModifier)
        historyForward();

    QString cmd = textCursor().block().text().mid(prompt.length());
    emit onChange(cmd);
}

void Console::mousePressEvent(QMouseEvent *)
{
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *){}

void Console::contextMenuEvent(QContextMenuEvent *){}

void Console::onEnter()
{
    if(textCursor().positionInBlock() == prompt.length())
    {
        insertPrompt(true);
        return;
    }
    QString cmd = textCursor().block().text().mid(prompt.length());
    historyAdd(cmd);
    emit onCommand(cmd);
}

void Console::output(QString s)
{
    textCursor().insertBlock();
    QTextCharFormat format;
    format.setForeground(QColor(0, 153, 0));
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(s);
    insertPrompt();
}

void Console::insertPrompt(bool insertNewBlock)
{
    if(insertNewBlock)
        textCursor().insertBlock();
    QTextCharFormat format;
    format.setForeground(Qt::blue);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(prompt);
    scrollDown();
    setFocus();
}

void Console::scrollDown()
{
    QScrollBar *vbar = verticalScrollBar();
    vbar->setValue(vbar->maximum());
}

void Console::historyAdd(QString cmd)
{
    history->append(cmd);
    historyPos = history->length();
}

void Console::historyBack()
{
    if(!historyPos)
return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(prompt + history->at(historyPos-1));
    setTextCursor(cursor);
    historyPos--;
}

void Console::historyForward()
{
    if(historyPos == history->length())
return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    if(historyPos == history->length() - 1)
cursor.insertText(prompt);
    else
cursor.insertText(prompt + history->at(historyPos + 1));
    setTextCursor(cursor);
    historyPos++;
}
