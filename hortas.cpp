#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include "structs.h"
#include "armazem.h"
#include "registo.h"
#include "gestao.h"

using namespace std;

void cria_hortas(Plantacao** p, string* a, string alphabet, int* paT) {

    int aux = (*p)->n_hortas;
    int i = 0;
    while(aux > 0) {
        NoH *novo = new NoH;
        NoH* aux1 = NULL;

        novo->valor.area = *(a + rand() % (*paT)); //Area random do array de todas as areas criado no início
        novo->valor.capacidade = rand() % 6 + 3; //Capacidade random de 3 a 5
        novo->valor.nome = alphabet[i]; //Id da horta
        novo->valor.produtos = 0; //Número de produtos plantados na horta
        novo->valor.cabeca = NULL; //Cabeça da lista ligada de produtos
        novo->valor.raiz = NULL; //Raiz da arvore de produtos perdidos
        novo->valor.raizT = 0; //Tamanho da arvore
        novo->valor.fertilizaçao = 0;

        if ((*p)->cabeca == NULL) {
            novo->seguinte = NULL;
            (*p)->cabeca = novo;
        }
        else {
            aux1 = (*p)->cabeca;
            while (aux1->seguinte != NULL) {
                aux1 = aux1->seguinte;
            }
            novo->seguinte = aux1->seguinte;
            aux1->seguinte = novo;
        }

        aux--;
        i++;
    }
}

void mostra_hortas(Plantacao* p) {
    NoH* it_h = p->cabeca;
    while (it_h != NULL) { //Percorre as hortas
        cout << "Horta: " << it_h->valor.nome << " | " << "Responsável: " <<
            it_h->valor.agricultor << " | " << "Capacidade: " << it_h->valor.capacidade <<
            " | " << "Produtos: " << it_h->valor.produtos << " | " << "Área: "
            << it_h->valor.area << endl;

        No* it_p = it_h->valor.cabeca;
        while (it_p != NULL) { //Percorre os produtos
            cout << "Produto: " << it_p->valor.nome << " | " << "Rega: " << it_p->valor.rega << " | " << "Resistência: " << it_p->valor.resistencia << "%" << endl;
            it_p = it_p->seguinte;
        }
        cout << "----------------------------------------------------------------------------" << endl;
        it_h = it_h->seguinte;
    }
}

void insereplt(No** p, NoH** aux1) {
    No* no = new No;
    no->valor = (*p)->valor;
    no->seguinte = NULL;
    if ((*aux1)->valor.cabeca == NULL) { //Verifica se a horta esta vazia
        (*aux1)->valor.cabeca = no;
    }
    else {
        No* procura_ultimo = (*aux1)->valor.cabeca;
        while (procura_ultimo->seguinte != NULL) {
            procura_ultimo = procura_ultimo->seguinte;
        }
        procura_ultimo->seguinte = no;
    }
}

void plantar(Plantacao** plantacao, Armazem** arm) {
    No* aux2 = (*arm)->cabeca;
    NoH* aux1 = (*plantacao)->cabeca;
    int c = 0;
    while (aux2 != NULL) {
        aux1 = (*plantacao)->cabeca;
        while ((aux1->seguinte != NULL) && c<10) {
            if ((aux2 != NULL)) {
                if ((aux1->valor.area.compare(aux2->valor.area) == 0) && (*arm)->armT > 0 && (aux1->valor.produtos < aux1->valor.capacidade)) { //Se a area for igual, e o arm tiver produtos e o numero de produtos for menor que a capacidade da horta

                    insereplt(&aux2, &aux1);
                    aux1->valor.produtos++;
                    (*arm)->armT--;
                    c++;
                    removerarm(&aux2, arm);
                    aux1 = (*plantacao)->cabeca;
                }
                else {
                    aux1 = aux1->seguinte;
                }
            }
            else {
                break;
            }
        }
        if (aux2 != NULL) {
            aux2 = aux2->seguinte;
        }
    }
}

void removerplt(NoH** p,No** p2) {
    No* lixo;
    No* anterior = (*p)->valor.cabeca;
    if (anterior == (*p2)) {
        lixo = (*p2);
        (*p2) = (*p2)->seguinte;
        (*p)->valor.cabeca = (*p2);
        free(lixo);
    }
    else {
        while (anterior->seguinte != (*p2)) {
            anterior = anterior->seguinte;
        }
        lixo = (*p2);
        (*p2) = (*p2)->seguinte;
        anterior->seguinte = (*p2);
        free(lixo);
    }
}

void colhido(Plantacao** plantacao) {
    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    while (aux1 != NULL) {
        aux2 = aux1->valor.cabeca;
        while (aux2 != NULL) {
            if ((rand() % 100 + 1) < 26) { //Tem 25% de chance de ser colhido
                cout << "Foi colhido um produto " << aux2->valor.nome << " da área " << aux2->valor.area << " da horta " << aux1->valor.nome << endl;
                aux1->valor.raiz = inserirNodo(aux1->valor.raiz, aux2->valor.nome);
                aux1->valor.raizT++;
                aux1->valor.produtos--;
                removerplt(&aux1, &aux2);
            }
            else {
                aux2 = aux2->seguinte;
            }
        }
        aux1 = aux1->seguinte;
    }
}

void tempo_rega(Plantacao** plantacao) {
    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    while (aux1 != NULL) {
        aux2 = aux1->valor.cabeca;
        while (aux2 != NULL) {
            if (aux2->valor.temp_para_rega == 0) { //Verifica se o tempo para a rega chegou a 0 e volta ao tempo original
                aux2->valor.temp_para_rega == aux2->valor.rega;
            }
            else {
                aux2->valor.temp_para_rega--;
            }
            aux2 = aux2->seguinte;
        }
        aux1 = aux1->seguinte;
    }
}

void insereprg(Produto* p, Praga** lstpraga) {
    No* no = new No;
    no->valor = *p;
    no->seguinte = NULL;
    if ((*lstpraga)->cabeca == NULL) {
        (*lstpraga)->cabeca = no;
    }
    else {
        No* procura_ultimo = (*lstpraga)->cabeca;
        while (procura_ultimo->seguinte != NULL) {
            procura_ultimo = procura_ultimo->seguinte;
        }
        procura_ultimo->seguinte = no;
    }
}

void pragas(Plantacao** plantacao, Praga** lstpraga) {
    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    while (aux1 != NULL) {
        aux2 = aux1->valor.cabeca;
        while (aux2 != NULL) {
            if (aux2->valor.temp_para_rega == 1) {
                if (rand() % 100 + 1 < (101 - aux2->valor.resistencia)) { //Tem (100-resistência)% de chance de ser perdido
                    cout << "Foi perdido um produto " << aux2->valor.nome << " da área " << aux2->valor.area << " da horta " << aux1->valor.nome << endl;
                    aux1->valor.produtos--;
                    insereprg(&aux2->valor, lstpraga); //Inserido na lista de produtos perdidos
                    (*lstpraga)->tamanho++;
                    removerplt(&aux1, &aux2);
                }
                else {
                    aux2 = aux2->seguinte;
                }
            }
            else {
                aux2 = aux2->seguinte;
            }
        }
        aux1 = aux1->seguinte;
    }
}

Plantacao* inserehorta(Plantacao* plantacao, Horta* h) {
    if (plantacao->cabeca == NULL) {
        plantacao->cabeca = new NoH;
        plantacao->cabeca->valor = *h;
        plantacao->cabeca->seguinte = NULL;
    }
    else {
        NoH* aux = plantacao->cabeca;
        NoH* novo = new NoH;
        novo->valor = *h;
        novo->seguinte = NULL;
        while (aux->seguinte != NULL)
            aux = aux->seguinte;
        aux->seguinte = novo;
    }
    return plantacao;
}

Horta* insereproduto(Horta* h, Produto* p) {
    if (h->cabeca == NULL) {
        h->cabeca = new No;
        h->cabeca->valor = *p;
        h->cabeca->seguinte = NULL;
    }
    else {
        No* aux = h->cabeca;
        No* novo = new No;
        novo->valor = *p;
        novo->seguinte = NULL;
        while (aux->seguinte != NULL)
            aux = aux->seguinte;
        aux->seguinte = novo;
    }
    return h;
}

Plantacao* lehortasfch(Plantacao* plantacao) {
    ifstream file_pla;
    file_pla.open("gravarplantacoes.txt", ios::in);
    plantacao->cabeca = NULL;
    plantacao->n_hortas = 0;
    if (!file_pla.is_open()) {
        cout << "Erro ao abrir o ficheiro das plantações" << endl;
        cout << endl;
    }
    else {
        int linha = 1;
        string line;
        while (getline(file_pla, line)) {

            string id;
            string agr;
            string area;
            int cap;
            int n_prod;

            id = line;
            getline(file_pla, agr);
            getline(file_pla, area);
            getline(file_pla, line);
            cap = stoi(line);
            getline(file_pla, line);
            n_prod = stoi(line);

            Horta* h = new Horta;

            h->nome = id;
            h->agricultor = agr;
            h->area = area;
            h->capacidade = cap;
            h->produtos = n_prod;
            h->cabeca = NULL;

            int contador = 0;

            string nome_prod;
            string forn;
            int reg = 0;
            int resist = 0;
            int temp_reg = 0;

            while (contador < (h->produtos) && getline(file_pla, line)) {

                nome_prod = line;
                getline(file_pla, forn);
                getline(file_pla, line);
                reg = stoi(line);
                getline(file_pla, line);
                resist = stoi(line);
                getline(file_pla, line);
                temp_reg = stoi(line);

                Produto* p = new Produto;

                p->nome = nome_prod;
                p->fornecedor = forn;
                p->rega = reg;
                p->resistencia = resist;
                p->temp_para_rega = temp_reg;

                h = insereproduto(h, p);

                contador++;
            }
            plantacao = inserehorta(plantacao, h);
            plantacao->n_hortas++;
        }
    }
    file_pla.close();
    cout << endl;
    return plantacao;
}

void gravarPraga(Praga* praga) {
    string gravaPraga("pragas.txt");
    fstream file_out;
    file_out.open(gravaPraga, fstream::in | fstream::out);
    if (!file_out.is_open()) {
        cout << "Erro ao abrir " << gravarPraga << endl;
        cout << endl;
    }
    else {
        limpar_file("pragas.txt");
        No* aux1 = new No;
        aux1 = praga->cabeca;
        file_out << praga->tamanho << endl;
        while (aux1 != NULL) {
            file_out << aux1->valor.area << endl;
            file_out << aux1->valor.nome << endl;
            file_out << aux1->valor.fornecedor << endl;
            file_out << aux1->valor.rega << endl;
            file_out << aux1->valor.temp_para_rega << endl;
            file_out << aux1->valor.resistencia << endl;
            aux1 = aux1->seguinte;
        }
    }
    file_out.close();
}

Praga* insereprodutoPraga(Praga* h, Produto* p) {
    if (h->cabeca == NULL) {
        h->cabeca = new No;
        h->cabeca->valor = *p;
        h->cabeca->seguinte = NULL;
    }
    else {
        No* aux = h->cabeca;
        No* novo = new No;
        novo->valor = *p;
        novo->seguinte = NULL;
        while (aux->seguinte != NULL)
            aux = aux->seguinte;
        aux->seguinte = novo;
    }
    return h;
}

Praga* lerfchPraga(Praga* praga) {
    ifstream file_prag;
    file_prag.open("pragas.txt", ios::in);
    praga->cabeca = NULL;
    praga->tamanho = 0;
    if (!file_prag.is_open()) {
        cout << "Erro ao abrir o ficheiro das pragas" << endl;
        cout << endl;
    }
    else {
        string line;
        int contador = 0; 
        getline(file_prag, line);
        praga->tamanho = stoi(line);
        while (contador < praga->tamanho) {
            while (getline(file_prag, line)) {

                string area;
                string nome;
                string forn;
                int rega = 0;
                int temp_reg = 0;
                int resist = 0;

                area = line;
                getline(file_prag, nome);
                getline(file_prag, forn);
                getline(file_prag, line);
                rega = stoi(line);
                getline(file_prag, line);
                temp_reg = stoi(line);
                getline(file_prag, line);
                resist = stoi(line);

                Produto* p = new Produto;

                p->area = area;
                p->fornecedor = forn;
                p->nome = nome;
                p->rega = rega;
                p->resistencia = resist;
                p->temp_para_rega = temp_reg;

                praga = insereprodutoPraga(praga, p);
                contador++;
                break;
            }
        }

    }
    file_prag.close();
    return praga;
}
