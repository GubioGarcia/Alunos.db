#ifndef MANIPULARARQUIVO_H
#define MANIPULARARQUIVO_H

#include <aluno.h>
#include <fstream>
#include <sstream>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <set>

namespace ggs {
    class ManipularArquivo
    {
    private:
        QString nomeDoArquivoNoDisco = "";
    public:
        ManipularArquivo(QString &nomeDoArquivoNoDisco);

        std::list<Aluno> buscarDadosArquivo() const;

        std::list<std::string> filtrarCursos(QString nomeArquivo);
        std::list<std::string> filtrarTurmas(QString nomeArquivo);
        std::list<std::string> filtrarDisciplinas(QString nomeArquivo);

        std::list<std::string> splitString(const std::string& input, char delimiter);

        std::list<Aluno> buscarPorDisciplinaTurma(QString nomeDoArquivoNoDisco, QString disciplina, QString turma);
        std::list<Aluno> buscarPorDisciplina(QString nomeDoArquivoNoDisco, QString disciplina);
        std::list<Aluno> buscarPorCurso(QString nomeDoArquivoNoDisco, QString curso);

    };
}

#endif // MANIPULARARQUIVO_H
