#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <aluno.h>
#include <manipulararquivo.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    //explicit Dialog(QWidget *parent = nullptr);
    explicit Dialog(QWidget* parent, QString nomeDoArquivo = "");
    ~Dialog();

    void listarCursos();
    void listarDisciplinas();
    void listarTurmas();

private slots:
    void on_pushButtonFiltrar_clicked();

signals:
    void valorSelecionado(const QString& value);

private:
    Ui::Dialog *ui;
    ggs::ManipularArquivo *objAux;

    QString nomeDoArquivo;
};

#endif // DIALOG_H
