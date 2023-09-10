#include "disciplina.h"

namespace ggs {
    QString Disciplina::getCodigo() const
    {
        return codigo;
    }

    void Disciplina::setCodigo(const QString &newCodigo)
    {
        codigo = newCodigo;
    }

    QString Disciplina::getTurma() const
    {
        return turma;
    }

    void Disciplina::setTurma(const QString &newTurma)
    {
        turma = newTurma;
    }

    Disciplina::Disciplina():
        codigo(""), turma("")
    {}

    Disciplina::Disciplina(QString codigo, QString turma):
        codigo(codigo), turma(turma)
    {}
}
