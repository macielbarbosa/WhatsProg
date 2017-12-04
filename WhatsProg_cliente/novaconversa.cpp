#include "novaconversa.h"
#include "ui_novaconversa.h"

NovaConversa::NovaConversa(QWidget *parent) :
    QDialog(parent), ui(new Ui::NovaConversa)
{
    ui->setupUi(this);
}

NovaConversa::~NovaConversa()
{
    delete ui;
}

void NovaConversa::setNovaConversa()
{
    setWindowTitle("Nova conversa");
    ui->lineEditUsuario->clear();
    show();
}

void NovaConversa::on_buttonBox_accepted()
{
    string usuario = ui->lineEditUsuario->text().toStdString();

    emit iniciarNovaConversa(usuario);
}
