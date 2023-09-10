#ifndef LISTALUNOS_H
#define LISTALUNOS_H

#include <aluno.h>

namespace ggs {
    class ListAlunos
    {
    private:
        std::list<Aluno> listaAlunos;
    public:
        ListAlunos(std::list<Aluno> listaAlunos);
    };
}

#endif // LISTALUNOS_H
