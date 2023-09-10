#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tipoFiltro("")
    , nomeArquivoNoDisco("")
{
    ui->setupUi(this);
    ui->lineEditNomeArquivoDisco->setEnabled(false);
    //Configurando a Grid
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnWidth(0, 115);
    ui->tableWidget->setColumnWidth(1, 250);
    ui->tableWidget->setColumnWidth(2, 700);
}

MainWindow::~MainWindow()
{
    delete objetoArquivo;
    delete ui;
}

void MainWindow::on_pushButtonBuscarArquivo_clicked()
{
    try {
        //Buscar o arquivo no disco
        nomeArquivoNoDisco = QFileDialog::getOpenFileName(this, "Abrir Arquivo", QDir::currentPath(), "Arquivos Textos (*.csv *.txt )");
        if(nomeArquivoNoDisco.isEmpty()) throw QString("Arquivo não foi selecionado");
        ui->lineEditNomeArquivoDisco->setText(nomeArquivoNoDisco);

        //Criar objeto da classe ManipularArquivo para tratamento dos dados do arquivo lido
        objetoArquivo = new ggs::ManipularArquivo(nomeArquivoNoDisco);
        lista = objetoArquivo->buscarDadosArquivo();
        mostrarListaAlunosNaGrid(&lista);
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}

void MainWindow::mostrarListaAlunosNaGrid(std::list<ggs::Aluno> *listaDeAlunos) {
    try {
        // Limpar a grid
        if (listaDeAlunos->empty()) return;
        ui->tableWidget->setRowCount(0);

        while (!listaDeAlunos->empty()) {
            ggs::Aluno objeto = listaDeAlunos->front();
            listaDeAlunos->pop_front();

            // Montando a grid
            QTableWidgetItem *itemMatricula = new QTableWidgetItem(objeto.getMatricula());
            QTableWidgetItem *itemNome = new QTableWidgetItem(objeto.getNomeCompleto());
            QTableWidgetItem *itemDisciplinas = new QTableWidgetItem(objeto.obterDisciplinas());
            int linha = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(linha);
            ui->tableWidget->setItem(linha, 0, itemMatricula);
            ui->tableWidget->setItem(linha, 1, itemNome);
            ui->tableWidget->setItem(linha, 2, itemDisciplinas);
        }
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    } catch (...) {
        QMessageBox::information(this, "ERRO", "ERRO NA LISTAGEM");
    }
}

void MainWindow::on_pushButtonFiltrarCurso_clicked()
{
    try {
        if (nomeArquivoNoDisco.isEmpty()) throw QString("SELECIONE O ARQUIVO!");
        QString arquivo = ui->lineEditNomeArquivoDisco->text();
        Dialog dialog(this, arquivo);
        dialog.listarCursos();
        connect(&dialog, &Dialog::valorSelecionado, this, &MainWindow::onValueSelected);
        tipoFiltro = "Listar Cursos";
        if (dialog.exec() == QDialog::Accepted) QMessageBox::about(this, "Information", "TRUE");
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}

void MainWindow::on_pushButtonFiltrarDisciplinas_clicked()
{
    try {
        if (nomeArquivoNoDisco.isEmpty()) throw QString("SELECIONE O ARQUIVO!");
        QString arquivo = ui->lineEditNomeArquivoDisco->text();
        Dialog dialog(this, arquivo);
        dialog.listarDisciplinas();
        connect(&dialog, &Dialog::valorSelecionado, this, &MainWindow::onValueSelected);
        tipoFiltro = "Listar Disciplinas";
        if (dialog.exec() == QDialog::Accepted) QMessageBox::about(this, "Information", "TRUE");
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}

void MainWindow::on_pushButtonFiltrarTurmas_clicked()
{
    try {
        if (nomeArquivoNoDisco.isEmpty()) throw QString("SELECIONE O ARQUIVO!");
        QString arquivo = ui->lineEditNomeArquivoDisco->text();
        Dialog dialog(this, arquivo);
        dialog.listarTurmas();
        connect(&dialog, &Dialog::valorSelecionado, this, &MainWindow::onValueSelected);
        tipoFiltro = "Listar Turmas";
        if (dialog.exec() == QDialog::Accepted) QMessageBox::about(this, "Information", "TRUE");
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}

void MainWindow::on_pushButtonLimparFiltros_clicked()
{
    try {
        if (nomeArquivoNoDisco.isEmpty()) return;
        // Imprimir lista completa
        lista = objetoArquivo->buscarDadosArquivo();
        mostrarListaAlunosNaGrid(&lista);
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}

void MainWindow::onValueSelected(const QString& value) {
    try {
        if (tipoFiltro == "Listar Turmas"){
            ggs::ManipularArquivo objAlunos(nomeArquivoNoDisco);
            QStringList partes = value.split("-");
            // Verificar se a string foi dividida corretamente em duas partes
            QString disciplina = ""; // XXX0000
            QString turma = ""; // X00
            if (partes.size() == 2) {
                disciplina = partes.at(0); // XXX0000
                turma = partes.at(1); // X00
            } else return;

            std::list<ggs::Aluno> listaDeAlunos = objAlunos.buscarPorDisciplinaTurma(nomeArquivoNoDisco, disciplina, turma);

            // Limpar a grid
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            mostrarListaAlunosNaGrid(&listaDeAlunos);

        } else if (tipoFiltro == "Listar Disciplinas"){
            ggs::ManipularArquivo objAlunos(nomeArquivoNoDisco);
            QString disciplina = value; // XXX0000
            std::list<ggs::Aluno> listaDeAlunos = objAlunos.buscarPorDisciplina(nomeArquivoNoDisco, disciplina);

            // Limpar a grid
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            mostrarListaAlunosNaGrid(&listaDeAlunos);

        } else if (tipoFiltro == "Listar Cursos"){
            ggs::ManipularArquivo objAlunos(nomeArquivoNoDisco);
            std::list<ggs::Aluno> listaDeAlunos = objAlunos.buscarPorCurso(nomeArquivoNoDisco, value);

            // Limpar a grid
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            mostrarListaAlunosNaGrid(&listaDeAlunos);
        }
    } catch (...) {
        QMessageBox::about(this, "Erro", "Não foi possivel concluir sua tarefa");
    }
}
