#include <QtGui/QTextBlock>
#include <QtGui/QScrollBar>

#include "console.h"

Console::Console(QWidget *parent) :
QPlainTextEdit(parent)
{
    prompt_ = "koala> ";

    this->setFrameShape(QFrame::Panel);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::blue);
    setPalette(p);

    history_ = new QStringList;
    historyPos_ = 0;
    isLocked = true;
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
       && textCursor().positionInBlock() > prompt_.length())
            QPlainTextEdit::keyPressEvent(event);

    if(event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier)
        onEnter();

    if(event->key() == Qt::Key_Up && event->modifiers() == Qt::NoModifier)
        historyBack();

    if(event->key() == Qt::Key_Down && event->modifiers() == Qt::NoModifier)
        historyForward();

    QString cmd = textCursor().block().text().mid(prompt_.length());
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
    if(textCursor().positionInBlock() == prompt_.length())
    {
        insertPrompt(true);
        return;
    }
    QString cmd = textCursor().block().text().mid(prompt_.length());
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
    textCursor().insertText(prompt_);
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
    history_->append(cmd);
    historyPos_ = history_->length();
}

void Console::historyBack()
{
    if(!historyPos_)
return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(prompt_ + history_->at(historyPos_-1));
    setTextCursor(cursor);
    historyPos_--;
}

void Console::historyForward()
{
    if(historyPos_ == history_->length())
return;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    if(historyPos_ == history_->length() - 1)
cursor.insertText(prompt_);
    else
cursor.insertText(prompt_ + history_->at(historyPos_ + 1));
    setTextCursor(cursor);
    historyPos_++;
}
