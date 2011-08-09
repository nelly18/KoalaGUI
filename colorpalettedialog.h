#ifndef COLORPALETTEDIALOG_H
#define COLORPALETTEDIALOG_H

#include <QtGui/QDialog>

#include "defines.h"

namespace Ui {
    class ColorPaletteDialog;
}

class ColorPaletteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPaletteDialog(QWidget *parent = 0);
    ~ColorPaletteDialog();

    int palette();

private:
    Ui::ColorPaletteDialog *ui;
};

#endif // COLORPALETTEDIALOG_H
