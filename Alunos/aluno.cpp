#include "aluno.h"

namespace ggs {
    QString Aluno::getMatricula() const
    {
        return matricula;
    }

    QString Aluno::getNomeCompleto() const
    {
        return nomeCompleto;
    }

    std::list<Disciplina> Aluno::getDisciplinasCursando() const
    {
        return disciplinasCursando;
    }

    void Aluno::setMatricula(const QString &newMatricula)
    {
        matricula = newMatricula;
    }

    void Aluno::setNomeCompleto(const QString &newNomeCompleto)
    {
        nomeCompleto = newNomeCompleto;
    }

    void Aluno::setDisciplinasCursando(const std::list<Disciplina> &newDisciplinasCursando)
    {
        disciplinasCursando = newDisciplinasCursando;
    }

    Aluno::Aluno():
        matricula(""), nomeCompleto(""), disciplinasCursando(0)
    {}

    Aluno::Aluno(QString matricula, QString nomeCompleto, std::list<Disciplina> disciplinasCursando):
        matricula(matricula), nomeCompleto(nomeCompleto), disciplinasCursando(disciplinasCursando)
    {}

    QString Aluno::obterDisciplinas() const{
        QString listaDisciplinas; // QString para armazenar a lista de disciplinas do aluno
        for (const auto& disciplina : disciplinasCursando) {
            listaDisciplinas += disciplina.getCodigo() + "-" + disciplina.getTurma() + " | ";
        }
        return listaDisciplinas;
    }
}
