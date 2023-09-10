#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <dialog.h>
#include <listalunos.h>
#include <manipulararquivo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onValueSelected(const QString& value);
    void mostrarListaAlunosNaGrid(std::list<ggs::Aluno> *listaDeAlunos);

private slots:
    void on_pushButtonBuscarArquivo_clicked();

    void on_pushButtonFiltrarCurso_clicked();

    void on_pushButtonFiltrarDisciplinas_clicked();

    void on_pushButtonFiltrarTurmas_clicked();

    void on_pushButtonLimparFiltros_clicked();

private:
    Ui::MainWindow *ui;
    ggs::ManipularArquivo *objetoArquivo;

    QString tipoFiltro;
    QString nomeArquivoNoDisco;
    std::list<ggs::Aluno> lista;
};
#endif // MAINWINDOW_H
