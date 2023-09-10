#include "manipulararquivo.h"

namespace ggs {
    ManipularArquivo::ManipularArquivo(QString &nomeDoArquivoNoDisco):
        nomeDoArquivoNoDisco(nomeDoArquivoNoDisco)
    {}

    std::list<Aluno> ManipularArquivo::buscarDadosArquivo() const{
        try {
            std::ifstream arquivo; //criando um arquivo de entrada
            arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str()); //abrindo um arquivo de entrada
            if(!arquivo.is_open()) throw QString("ERRO. Arquivo não pode ser aberto");

            std::string linha;
            std::list<Aluno> listaDeAluno;
            while (std::getline(arquivo, linha)) {
                std::stringstream texto(linha);
                std::string matricula, nomeAluno, turmas;

                std::getline(texto, matricula, ';');
                std::getline(texto, nomeAluno, ';');
                std::getline(texto, turmas, ';');

                std::list<std::string> turmasSeparadas;
                std::stringstream turmasStream(turmas);
                std::string turma;

                while (std::getline(turmasStream, turma, ' ')) {
                    if (!turma.empty()) turmasSeparadas.push_back(turma);
                }

                Aluno objAluno;
                objAluno.setMatricula(QString::fromStdString(matricula));
                objAluno.setNomeCompleto(QString::fromStdString(nomeAluno));

                std::list<Disciplina> listaDeDisciplinas;
                for (const auto& t : turmasSeparadas) {
                    std::string codDisciplina, numeroTurma;
                    std::stringstream turmaStream(t);

                    std::getline(turmaStream, codDisciplina, '-');
                    std::getline(turmaStream, numeroTurma);

                    if (!codDisciplina.empty() && !numeroTurma.empty()) {
                        Disciplina objDisciplina;
                        objDisciplina.setCodigo(QString::fromStdString(codDisciplina));
                        objDisciplina.setTurma(QString::fromStdString(numeroTurma));

                        listaDeDisciplinas.push_back(objDisciplina);
                    }
                }

                objAluno.setDisciplinasCursando(listaDeDisciplinas);
                listaDeAluno.push_back(objAluno);
            }

            arquivo.close(); // Fecha o arquivo após a leitura
            return listaDeAluno;
        } catch (QString &erro) {
            throw erro;
        }
    }

    std::list<std::string> ManipularArquivo::filtrarCursos(QString nomeArquivo){
        std::list<std::string> identificadoresCurso;
        std::set<std::string> auxNumeroSet;

        std::ifstream arquivo(nomeArquivo.toStdString());
        if (!arquivo) throw QString("Erro ao abrir o arquivo.");

        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::list<std::string> dados = splitString(linha, ';');
            if (dados.size() >= 3) {
                std::string matricula = dados.front();
                std::size_t primeiroPontoPos = matricula.find('.');
                std::size_t segundoPontoPos = matricula.find('.', primeiroPontoPos + 1);
                if (primeiroPontoPos != std::string::npos && segundoPontoPos != std::string::npos) {
                    std::string numerosDoMeio = matricula.substr(segundoPontoPos + 1, matricula.find('.', segundoPontoPos + 1) - segundoPontoPos - 1);
                    if (auxNumeroSet.find(numerosDoMeio) == auxNumeroSet.end()) {
                        identificadoresCurso.push_back(numerosDoMeio);
                        auxNumeroSet.insert(numerosDoMeio);
                    }
                }
            }
        }
        return identificadoresCurso;
    }

    std::list<std::string> ManipularArquivo::filtrarTurmas(QString nomeArquivo){
        std::list<std::string> turmas;
        std::set<std::string> turmasSet;

        std::ifstream arquivo(nomeArquivo.toStdString());
        if (!arquivo) throw QString("Erro ao abrir o arquivo.");

        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::list<std::string> dados = splitString(linha, ';');
            if (dados.size() >= 3) {
                std::list<std::string> turmaTokens = splitString(dados.back(), ' ');
                for (const auto& turma : turmaTokens) {
                    if (!turma.empty() && turma.find("XXX") == std::string::npos) {
                        if (turmasSet.find(turma) == turmasSet.end()) {
                            turmas.push_back(turma);
                            turmasSet.insert(turma);
                        }
                    }
                }
            }
        }
        return turmas;
    }

    std::list<std::string> ManipularArquivo::filtrarDisciplinas(QString nomeArquivo){
        std::list<std::string> disciplinas;
        std::set<std::string> disciplinasSet;

        std::ifstream arquivo(nomeArquivo.toStdString());
        if (!arquivo) throw QString("Erro ao abrir o arquivo.");

        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::list<std::string> dados = splitString(linha, ';');
            if (dados.size() >= 3) {
                std::list<std::string> disciplinaTokens = splitString(dados.back(), ' ');
                for (const auto& disciplina : disciplinaTokens) {
                    if (!disciplina.empty() && disciplina.find("XXX") == std::string::npos) {
                        std::string codigo = disciplina.substr(0, disciplina.find('-'));
                        if (disciplinasSet.find(codigo) == disciplinasSet.end()) {
                            disciplinas.push_back(codigo);
                            disciplinasSet.insert(codigo);
                        }
                    }
                }
            }
        }
        return disciplinas;
    }

    std::list<std::string> ManipularArquivo::splitString(const std::string& input, char delimiter){
        std::list<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (std::getline(iss, token, delimiter)) tokens.push_back(token);
        return tokens;
    }

    std::list<Aluno> ManipularArquivo::buscarPorCurso(QString nomeDoArquivoNoDisco, QString curso){
        try {
            std::ifstream arquivo; //criando um arquivo de entrada
            arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str()); //abrindo um arquivo de entrada
            if(!arquivo.is_open()) throw QString("ERRO. Arquivo não pode ser aberto");

            std::string linha;
            std::list<Aluno> listaDeAluno;
            while (std::getline(arquivo, linha)) {
                std::stringstream texto(linha);
                std::string matricula, nome, turmas;

                std::getline(texto, matricula, ';');
                std::getline(texto, nome, ';');
                std::getline(texto, turmas, ';');

                // Extrair o número do curso da matrícula do aluno
                size_t pos = matricula.find_last_of('.');
                std::string numeroCurso = matricula.substr(pos - 3, 3); // Considerando que o formato seja sempre "XXXX.X.####.YYYY"

                // Verificar se o número do curso extraído corresponde ao parâmetro Curso
                if (numeroCurso == curso.toStdString()) {
                    std::list<std::string> turmasSeparadas;
                    std::stringstream turmasStream(turmas);
                    std::string turma;

                    while (std::getline(turmasStream, turma, ' ')) {
                        if (!turma.empty()) turmasSeparadas.push_back(turma);
                    }

                    Aluno objAluno;
                    objAluno.setMatricula(QString::fromStdString(matricula));
                    objAluno.setNomeCompleto(QString::fromStdString(nome));

                    std::list<Disciplina> listaDeDisciplinas;
                    for (const auto& t : turmasSeparadas) {
                        std::string codigoDisciplina, numeroTurma;
                        std::stringstream turmaStream(t);

                        std::getline(turmaStream, codigoDisciplina, '-');
                        std::getline(turmaStream, numeroTurma);

                        if (!codigoDisciplina.empty() && !numeroTurma.empty()) {
                            Disciplina objDisciplina;
                            objDisciplina.setCodigo(QString::fromStdString(codigoDisciplina));
                            objDisciplina.setTurma(QString::fromStdString(numeroTurma));

                            listaDeDisciplinas.push_back(objDisciplina);
                        }
                    }

                    objAluno.setDisciplinasCursando(listaDeDisciplinas);
                    listaDeAluno.push_back(objAluno);
                }
            }

            arquivo.close();  // Fecha o arquivo após a leitura
            return listaDeAluno;
        } catch (std::bad_alloc&) { // Tratamento do erro de alocação de memória
            QString ("lista vazia");
        }
    }

    std::list<Aluno> ManipularArquivo::buscarPorDisciplina(QString nomeDoArquivoNoDisco, QString disciplina){
        try {
            std::ifstream arquivo; //criando um arquivo de entrada
            arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str()); //abrindo um arquivo de entrada
            if(!arquivo.is_open()) throw QString("ERRO. Arquivo não pode ser aberto");

            std::string linha;
            std::list<Aluno> listaDeAluno;
            while (std::getline(arquivo, linha)) {
                std::stringstream texto(linha);
                std::string matricula, nome, turmas;

                std::getline(texto, matricula, ';');
                std::getline(texto, nome, ';');
                std::getline(texto, turmas, ';');

                std::list<std::string> turmasSeparadas;
                std::stringstream turmasStream(turmas);
                std::string turma;

                while (std::getline(turmasStream, turma, ' ')) {
                    if (!turma.empty()) {
                        turmasSeparadas.push_back(turma);
                    }
                }

                Aluno objAluno;
                objAluno.setMatricula(QString::fromStdString(matricula));
                objAluno.setNomeCompleto(QString::fromStdString(nome));

                std::list<Disciplina> listaDeDisciplinas;
                for (const auto& t : turmasSeparadas) {
                    std::string codigoDisciplina, numeroTurma;
                    std::stringstream turmaStream(t);

                    std::getline(turmaStream, codigoDisciplina, '-');
                    std::getline(turmaStream, numeroTurma);

                    if (!codigoDisciplina.empty() && !numeroTurma.empty()) {
                        Disciplina objDisciplina;
                        objDisciplina.setCodigo(QString::fromStdString(codigoDisciplina));
                        objDisciplina.setTurma(QString::fromStdString(numeroTurma));

                        listaDeDisciplinas.push_back(objDisciplina);
                    }
                }

                objAluno.setDisciplinasCursando(listaDeDisciplinas);

                // Verificar se o aluno possui a disciplina e turma desejadas
                for (const auto& disciplinaTurma : objAluno.getDisciplinasCursando()) {
                    if (disciplinaTurma.getCodigo() == disciplina) {
                        listaDeAluno.push_back(objAluno);
                        break; // Não é necessário verificar as demais disciplinas do aluno
                    }
                }
            }

            arquivo.close();  // Fecha o arquivo após a leitura
            return listaDeAluno;
        } catch (std::bad_alloc&) {// Tratamento do erro de alocação de memória
            QString ("lista vazia");
        }
    }

    std::list<Aluno> ManipularArquivo::buscarPorDisciplinaTurma(QString nomeDoArquivoNoDisco, QString disciplina, QString turma){
        try {
            std::ifstream arquivo; //criando um arquivo de entrada
            arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str()); //abrindo um arquivo de entrada
            if(!arquivo.is_open()) throw QString("ERRO. Arquivo não pode ser aberto");

            std::string linha;
            std::list<Aluno> listaDeAluno;
            while (std::getline(arquivo, linha)) {
                std::stringstream texto(linha);
                std::string matricula, nome, turmas;

                std::getline(texto, matricula, ';');
                std::getline(texto, nome, ';');
                std::getline(texto, turmas, ';');

                std::list<std::string> turmasSeparadas;
                std::stringstream turmasStream(turmas);
                std::string auxTurma;

                while (std::getline(turmasStream, auxTurma, ' ')) {
                    if (!auxTurma.empty()) turmasSeparadas.push_back(auxTurma);
                }

                Aluno objAluno;
                objAluno.setMatricula(QString::fromStdString(matricula));
                objAluno.setNomeCompleto(QString::fromStdString(nome));

                std::list<Disciplina> listaDeDisciplinas;

            /*    // Aluno recebe apenas a disciplina filtrada
                Disciplina objDisciplina;
                objDisciplina.setCodigo(disciplina);
                objDisciplina.setTurma(turma);
                listaDeDisciplinas.push_back(objDisciplina);
                objAluno.setDisciplinasCursando(listaDeDisciplinas);
            */
                // Aluno recebe todas as disciplinas cursando
                for (const auto& t : turmasSeparadas) {
                    std::string codigoDisciplina, numeroTurma;
                    std::stringstream turmaStream(t);

                    std::getline(turmaStream, codigoDisciplina, '-');
                    std::getline(turmaStream, numeroTurma);

                    if (!codigoDisciplina.empty() && !numeroTurma.empty()) {
                        Disciplina objDisciplina;
                        objDisciplina.setCodigo(QString::fromStdString(codigoDisciplina));
                        objDisciplina.setTurma(QString::fromStdString(numeroTurma));

                        listaDeDisciplinas.push_back(objDisciplina);
                    }
                }
                objAluno.setDisciplinasCursando(listaDeDisciplinas);

                // Verificar se o aluno possui a disciplina e turma desejadas
                for (const auto& disciplinaTurma : objAluno.getDisciplinasCursando()) {
                    if (disciplinaTurma.getCodigo() == disciplina && disciplinaTurma.getTurma() == turma) {
                        listaDeAluno.push_back(objAluno);
                        break; // Não é necessário verificar as demais disciplinas do aluno
                    }
                }
            }

            arquivo.close();  // Fecha o arquivo após a leitura
            return listaDeAluno;
        } catch (std::bad_alloc&) {
            QString ("lista vazia");
        }
    }
}
