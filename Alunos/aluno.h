#ifndef ALUNO_H
#define ALUNO_H

#include <list>
#include <QString>
#include <disciplina.h>

namespace ggs {
    class Aluno
    {
    private:
        QString matricula;
        QString nomeCompleto;
        std::list<Disciplina> disciplinasCursando;
    public:
        Aluno();
        Aluno(QString matricula, QString nomeCompleto, std::list<Disciplina> disciplinasCursando);

        QString getMatricula() const;
        QString getNomeCompleto() const;
        std::list<Disciplina> getDisciplinasCursando() const;
        void setMatricula(const QString &newMatricula);
        void setNomeCompleto(const QString &newNomeCompleto);
        void setDisciplinasCursando(const std::list<Disciplina> &newDisciplinasCursando);

        QString obterDisciplinas() const;
    };
}

#endif // ALUNO_H
