#ifndef NOVACONVERSA_H
#define NOVACONVERSA_H

#include <iostream>
#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class NovaConversa;
}

class NovaConversa : public QDialog
{
    Q_OBJECT

public:
    explicit NovaConversa(QWidget *parent = 0);
    ~NovaConversa();
    void setNovaConversa();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NovaConversa *ui;

signals:
    void iniciarNovaConversa(const string &usuario);
};

#endif // NOVACONVERSA_H
