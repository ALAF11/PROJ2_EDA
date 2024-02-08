#pragma once
#include <string>

using namespace std;

struct Produto 
{
    string nome;
    string area;
    string fornecedor;
    int rega;
    int temp_para_rega; //Tempo para a rega
    int resistencia;
};

struct No //N� de uma lista ligada de produtos
{
    Produto valor;
    No* seguinte;
};

struct NoArvore //N� de uma arvore de strings
{
    string nome;
    NoArvore* esquerda;
    NoArvore* direita;
};

struct Horta
{
    string nome;
    string area;
    string agricultor;
    int capacidade;
    int produtos;
    NoArvore* raiz;
    int raizT;
    int fertiliza�ao;
    No* cabeca;
};

struct NoH //N� de uma lista ligada de hortas
{
    Horta valor;
    NoH* seguinte;
};


struct Armazem
{
    int armT;
    No* cabeca;
};

struct Plantacao 
{
    int n_hortas;
    NoH* cabeca;
};

struct Praga { //Lista ligada de produtos perdidos
    int tamanho;
    No* cabeca;
};

