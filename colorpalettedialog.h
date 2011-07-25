#ifndef COLORPALETTEDIALOG_H
#define COLORPALETTEDIALOG_H
#include "defines.h"
#include <QDialog>

namespace Ui {
    class ColorPaletteDialog;
}

class ColorPaletteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPaletteDialog(QWidget *parent = 0);
    ~ColorPaletteDialog();
    int getPalette();
private:
    Ui::ColorPaletteDialog *ui;
};

#endif // COLORPALETTEDIALOG_H
