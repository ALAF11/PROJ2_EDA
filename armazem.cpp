#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include "structs.h"
#include "ficheiros.h"

using namespace std;

void criar_produto(int n_produtos, int* paT, string* p, string* a, string* f, Produto* s) {
    for (int i = 0; i < n_produtos; i++) { //Utilizamos um for, que enquanto i < n_produtos, cria produto para o array de produtos s
        s[i].nome = *(p + rand() % ler_linhas_ficheiro("produtos.txt")); //Nome de produto random do array de todos os nomes de produtos criado no início
        s[i].fornecedor = *(f + rand() % ler_linhas_ficheiro("fornecedores.txt")); //Fornecedor random do array de todos os fornecedores criado no início
        s[i].area = *(a + rand() % ( * paT)); //Area random do array de todas as areas criado no início
        s[i].rega = rand() % 5 + 1; //Rega do produto que vai de 1 a 5
        s[i].resistencia =rand() % 61 + 20; //Resistencia do produto que vai de 20% a 80%
        s[i].temp_para_rega = s[i].rega; //Tempo para a rega do produto que no início é igual á rega
    }
}

void mostra_arm(Armazem** arm) {
    cout << "Armazem: " << endl;
    No* no = new No;
    if ((*arm)->cabeca == NULL) { //Verificar se o armazem esta vazio
        cout << "O armazem está vazio!" << endl;
    }
    else {
        no = (*arm)->cabeca;
        while (no != NULL) { //Percorrer todos os produtos do aramazem
            cout << "Nome: " << no->valor.nome << " | " << "Resistência: " << no->valor.resistencia << "%" << " | " << "Area: " << no->valor.area << endl;
            no = no->seguinte;
        }
    }
}

void inserirarm(Armazem** arm, int n_produtos, Produto* produtos) {
    for (int i = 0; i < n_produtos; i++) {
        No* aux, * novo = new No; //Criamos dois apontadores auxiliares

        if (novo) {
            novo->valor = produtos[i]; //Um apontador novo que terá o valor do produto a inserir
            if ((*arm)->cabeca == NULL) { //Se a cabeça do armazem for NULL adicionamos o produto nela (isto é no ínício)
                novo->seguinte = NULL;
                (*arm)->cabeca = novo;
            }
            else {
                aux = (*arm)->cabeca; // Um apontador auxiliar que só serve para chegra á ultima possição do armazem
                while ((aux->valor.area != produtos[i].area) && (aux->seguinte)) { //Enquanto a area não é igual e equanto não chegou ao fim, passa para o seguinte
                    aux = aux->seguinte;
                }
                novo->seguinte = aux->seguinte;
                aux->seguinte = novo;
            }
        }
    }
    (*arm)->armT = (*arm)->armT + n_produtos; //Adicionamos ao tamanho do armazem o numero de produtos introduzidos
}

void removerarm(No** p, Armazem** arm){
    No* lixo; //Criamos um apontador que vamos usar para o produto que iremos remover
    No* anterior = (*arm)->cabeca; //Criamos um apontador para o anterior do produto que queremos remover
    if (anterior == *p) { //Se esse anterior for igual ao que queremos remover (isto é se o que queremos remover é a cabeça do armazem)
        lixo = (*p);
        (*p) = (*p)->seguinte;
        (*arm)->cabeca = (*p);
        free(lixo); //Libertar a memória do produto a remover
    }
    else {
        while (anterior->seguinte != (*p)) {
            anterior = anterior->seguinte;
        }
        lixo = (*p);
        (*p) = (*p)->seguinte;
        anterior->seguinte = (*p);
        free(lixo); //Libertar a memória do produto a remover
    }
}

Armazem* insereArmazem(Armazem* arm, Produto* p) {
    if (arm->cabeca == NULL) { //Verificar se o armazem esta vazio e se sim inserir á cabeça
        arm->cabeca = new No;
        arm->cabeca->valor = *p;
        arm->cabeca->seguinte = NULL;
    }
    else {
        No* aux = arm->cabeca;
        No* novo = new No;
        novo->valor = *p;
        novo->seguinte = NULL;
        while (aux->seguinte != NULL) //Percorrer o armazem até o final para inserir o produto
            aux = aux->seguinte;
        aux->seguinte = novo;
    }
    return arm;
}

Armazem* lerarmfch(Armazem* arm) {
    ifstream file_arm;
    file_arm.open("gravarArmazem.txt", ios::in);
    arm->cabeca = NULL;
    arm->armT = 0;
    if (!file_arm.is_open()) {
        cout << "Erro ao abrir o ficheiro do armazem" << endl;
        cout << endl;
    }
    else {
        string line;
        int contador = 0;
        getline(file_arm, line);
        arm->armT = stoi(line);
        while (contador < arm->armT) {
            while (getline(file_arm, line)) {

                string area;
                string nome;
                string forn;
                int rega = 0;
                int temp_reg = 0;
                int resist = 0;

                area = line;
                getline(file_arm, nome);
                getline(file_arm, forn);
                getline(file_arm, line);
                rega = stoi(line);
                getline(file_arm, line);
                temp_reg = stoi(line);
                getline(file_arm, line);
                resist = stoi(line);

                Produto* p = new Produto;

                p->area = area;
                p->fornecedor = forn;
                p->nome = nome;
                p->rega = rega;
                p->resistencia = resist;
                p->temp_para_rega = temp_reg;

                arm = insereArmazem(arm, p);
                contador++;
                break;
            }
        }

    }
    file_arm.close();
    return arm;
}