#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <QString>

namespace ggs {
    class Disciplina
    {
    private:
        QString codigo;
        QString turma;
    public:
        Disciplina();
        Disciplina(QString codigo, QString turma);

        QString getCodigo() const;
        void setCodigo(const QString &newCodigo);
        QString getTurma() const;
        void setTurma(const QString &newTurma);
    };
}

#endif // DISCIPLINA_H
