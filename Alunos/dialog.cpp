#include "dialog.h"
#include "ui_dialog.h"
#include "QRegularExpression"

Dialog::Dialog(QWidget *parent, QString nomeDoArquivo) :
    QDialog(parent),
    ui(new Ui::Dialog),
    nomeDoArquivo(nomeDoArquivo)
{
    ui->setupUi(this);
    objAux = new ggs::ManipularArquivo(nomeDoArquivo);
}

Dialog::~Dialog()
{
    delete objAux;
    delete ui;
}

void Dialog::on_pushButtonFiltrar_clicked()
{
    QString selectedValue = ui->comboBox->currentText();
    emit valorSelecionado(selectedValue); // Emitir o sinal personalizado com o valor selecionado
    close(); // Fechar a janela DialogComboBox
}

void Dialog::listarCursos(){
    ui->labelTexto->setText("Selecione o curso:");
    std::list<std::string> cursos = objAux->filtrarCursos(nomeDoArquivo);
    for (const auto& curso : cursos) ui->comboBox->addItem(QString::fromStdString(curso));
}

void Dialog::listarDisciplinas(){
    ui->labelTexto->setText("Selecione a Disciplina:");
    std::list<std::string> disciplinas = objAux->filtrarDisciplinas(nomeDoArquivo);
    for (const auto& disciplina : disciplinas) ui->comboBox->addItem(QString::fromStdString(disciplina));
}

void Dialog::listarTurmas(){
    ui->labelTexto->setText("Selecione a Turma:");
    std::list<std::string> turmas = objAux->filtrarTurmas(nomeDoArquivo);
    for (const auto& turma : turmas) ui->comboBox->addItem(QString::fromStdString(turma));
}
