#include "colorpalettedialog.h"
#include "ui_colorpalettedialog.h"

ColorPaletteDialog::ColorPaletteDialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::ColorPaletteDialog)
{
    ui->setupUi(this);
}

ColorPaletteDialog::~ColorPaletteDialog()
{
    delete ui;
}

int ColorPaletteDialog::getPalette()
{
    return (ui->black->isChecked());
}
