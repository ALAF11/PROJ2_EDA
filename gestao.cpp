#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include "structs.h"
#include "ficheiros.h"
#include "hortas.h"
#include "registo.h"

using namespace std;

void colheitaManual(Plantacao** plantacao) {
    string colher;
    cout << "Insira o nome do produto a ser colhido:" << endl;
    cin.ignore();
    getline(cin, colher);
    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    int c = 0;
    while (aux1 != NULL) {
        aux2 = aux1->valor.cabeca;
        while (aux2 != NULL) {
            if ((aux2->valor.nome).compare(colher) == 0) {
                aux1->valor.raiz = inserirNodo(aux1->valor.raiz, aux2->valor.nome); //Inserido na arvore dos produtos colhidos
                aux1->valor.raizT++;
                cout << endl;
                cout << "Foi colhido manualmente um produto " << aux2->valor.nome << " da área " << aux2->valor.area << " da horta " << aux1->valor.nome << endl;
                removerplt(&aux1, &aux2);
                aux1->valor.produtos--;
                c++;
            }
            else {
                aux2 = aux2->seguinte;
            }
        }
        aux1 = aux1->seguinte;
    }
    cout << endl;
    if (c == 0) {
        cout << "O produto que pertende colher não se encontra plantado ou não existe no sistema" << endl;
    }
}

void atu_temporega(Plantacao** plantacao, Armazem** arm) {
    string nProd;
    int tnovo;
    cout << "Indique o nome do produto : " << endl;
    cin.ignore();
    getline(cin, nProd);
    cout << "Indique o novo tempo de rega :" << endl;
    cin >> tnovo;

    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    int c = 0;
    while (aux1 != NULL) {
        aux2 = aux1->valor.cabeca;
        while (aux2 != NULL) {
            if ((aux2->valor.nome).compare(nProd) == 0) {
                aux2->valor.rega = tnovo;
                aux2->valor.temp_para_rega = tnovo;
                cout << endl;
                cout << "Tempo de rega do produto " << nProd << " da horta " << aux1->valor.nome << " atualizado para " << tnovo << "." << endl;
                c++;
            }
            aux2 = aux2->seguinte;
        }
        aux1 = aux1->seguinte;
    }

    No* aux3 = new No;
    aux3 = (*arm)->cabeca;
    while (aux3 != NULL) {
        if ((aux3->valor.nome).compare(nProd) == 0) {
            aux3->valor.rega = tnovo;
            aux3->valor.temp_para_rega = tnovo;
            cout << endl;
            cout << "Tempo de rega do produto " << nProd << " do armazem atualizado para " << tnovo << "." << endl;
            c++;
        }
        aux3 = aux3->seguinte;
    }

    if (c == 0) {
        cout << endl;
        cout << "Produto não existe no armazem nem nas hortas, logo não foi atualizado" << endl;
    }
}

void ver_fertilizaçao(Plantacao** plantacao) {
    string area;
    int tempo_fertilizaçao;
    cout << "Insira uma área" << endl;
    cin.ignore();
    getline(cin, area);
    cout << "Insira um tempo de fertilização" << endl;
    cin >> tempo_fertilizaçao;

    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    while (aux1 != NULL) {
        if (aux1->valor.area.compare(area) == 0) {
            aux1->valor.fertilizaçao = tempo_fertilizaçao;
        }
        aux1 = aux1->seguinte;
    }
}

void fertilizacao(Plantacao** plantacao) {
    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    while (aux1 != NULL) {
        if (aux1->valor.fertilizaçao > 0) {
            aux2 = aux1->valor.cabeca;
            while (aux2 != NULL) {
                if ((aux2->valor.resistencia + 10) > 100) {
                    aux2->valor.resistencia = 100;
                }
                else {
                    aux2->valor.resistencia = aux2->valor.resistencia + 10;
                }
                aux2 = aux2->seguinte;
            }
            aux1->valor.fertilizaçao--;
        }
        aux1 = aux1->seguinte;
    }
}

void nova_area(string* a, int* paT, string* areas) {
    string na;
    string* y = new string[*paT + 1];


    cout << "Escreva o nome da nova area:" << endl;
    cin.ignore();
    getline(cin, na);

    for (int w = 0; w < *paT; w++) {
        y[w] = a[w];
    }

    y[*paT] = na;
    *paT = *paT + 1;

    for (int o = 0; o < *paT; o++) {
        areas[o] = y[o];
    }

}

void alterar_area(Plantacao** plantacao, string* a, int* paT) {
    string h;
    string ar;

    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    No* aux2 = new No;
    int c = 0;

    cout << "Indique a horta que pretende alterar: " << endl;
    cin >> h;
    cout << "Indique a nova area da horta: " << endl;
    cin.ignore();
    getline(cin, ar);
    for (int i = 0; i < *paT; i++) {
        if (ar.compare(a[i]) == 0) {
            while (aux1 != NULL) {
                aux2 = aux1->valor.cabeca;
                if (aux1->valor.nome.compare(h) == 0) {
                    c++;
                    aux1->valor.area = ar;
                    aux1->valor.produtos = 0;
                    while (aux2 != NULL) {
                        removerplt(&aux1, &aux2);
                    }
                }
                aux1 = aux1->seguinte;
            }
        }
    }

    if (c == 0) {
        cout << "A nova area não existe no sistema" << endl;
    }
}

void imprimirprodcol(Plantacao** plantacao) {
    string n;
    cout << "Qual o nome da horta que quer ver o registo:" << endl;
    cin >> n;

    NoH* aux1 = new NoH;
    aux1 = (*plantacao)->cabeca;
    while (aux1 != NULL && aux1->valor.nome.compare(n) != 0) {
        aux1 = aux1->seguinte;
    }
    cout << endl;
    imprimirres(aux1->valor.raiz); //Função recursiva que imprime uma arvore infixamente
    cout << endl;
}

void ordem_alfabetica(Plantacao* p) {
    int num_prod = 0;
    int i = 0;
    NoH* aux1 = new NoH;
    aux1 = p->cabeca;
    while (aux1 != NULL) {
        num_prod += aux1->valor.produtos;
        aux1 = aux1->seguinte;
    }
    aux1 = p->cabeca;
    No* aux2 = new No;
    aux2 = aux1->valor.cabeca;
    string* lst_prod = new string[num_prod];
    while (aux1 != NULL) {
        while (aux2 != NULL) {
            lst_prod[i] = aux2->valor.nome;
            aux2 = aux2->seguinte;
            i++;
        }
        aux1 = aux1->seguinte;
        if (aux1 != NULL) {
            aux2 = aux1->valor.cabeca;
        }
    }
    int primeiro = 0;
    for (int i = 0; i < num_prod - 1; i++) {
        primeiro = i;
        for (int j = i + 1; j < num_prod; j++) {
            if (lst_prod[j].compare(lst_prod[primeiro]) < 0) primeiro = j;
        }
        if (primeiro != i) swap(lst_prod[i], lst_prod[primeiro]);
    }
    cout << endl;
    for (int i = 0; i < num_prod; i++) {
        cout << i+1 <<"º: " << lst_prod[i] << endl;
    }
}

void swap(int& a, int& b)
{
    int aux = a;
    a = b;
    b = aux;
}

void gravarh(Plantacao** plantacao) {
    string gravarplant("gravarplantacoes.txt");
    fstream file_out;
    file_out.open(gravarplant, fstream::in | fstream::out);
    if (!file_out.is_open()) {
        cout << "Erro ao abrir " << gravarplant << endl;
        cout << endl;
    }
    else if (file_out.is_open()) {
        limpar_file("gravarplantacoes.txt");
        NoH* aux1 = new NoH;
        aux1 = (*plantacao)->cabeca;
        while (aux1 != NULL) {
            file_out << aux1->valor.nome << endl;                          // Primeira linha imprime nome da hortaa
            file_out << aux1->valor.agricultor << endl;                   //segunda linha agricultor
            file_out << aux1->valor.area << endl;                        //terceira linha area
            file_out << aux1->valor.capacidade << endl;                 //quarta linha capacidade
            file_out << aux1->valor.produtos << endl;                  //Quinta linha nºde produtos
            int prod = aux1->valor.produtos;
            if (prod > 0) {
                No* aux2 = new No;
                aux2 = aux1->valor.cabeca;
                while (aux2 != NULL) {
                    file_out << aux2->valor.nome << endl;                //Sexta linha nome do primeiro produto
                    file_out << aux2->valor.fornecedor << endl;          //Setima linha fornecedor do produto
                    file_out << aux2->valor.rega << endl;                //Oitava linha rega do produto
                    file_out << aux2->valor.resistencia << endl;         //Nona linha resistencia do produto
                    file_out << aux2->valor.temp_para_rega << endl;      //Decima linha tempo para rega do produto
                    aux2 = aux2->seguinte;                               //REPETE PARA TODOS OS PRODUTOS DA HORTA
                }
            }
            aux1 = aux1->seguinte;
        }
    }
    file_out.close();
}

void gravar_arm(Armazem** arm) {
    string gravarArma("gravarArmazem.txt");
    fstream file_out;
    file_out.open(gravarArma, fstream::in | fstream::out);
    if (!file_out.is_open()) {
        cout << "Erro ao abrir " << gravarArma << endl;
        cout << endl;
    }
    else {
        limpar_file("gravarArmazem.txt");
        No* aux1 = new No;
        aux1 = (*arm)->cabeca;
        file_out << (*arm)->armT << endl;
        while (aux1 != NULL) {
            file_out << aux1->valor.area << endl;                              //PRIMEIRA LINHA AREA
            file_out << aux1->valor.nome << endl;                              //SEGUNDA LINHA NOME
            file_out << aux1->valor.fornecedor << endl;                        //TERCEIRA LINHA FORNECEDOR
            file_out << aux1->valor.rega << endl;                              //QUINTA LINHA REGA
            file_out << aux1->valor.temp_para_rega << endl;                    //SEXTA LINHA TEMP PARA REGA
            file_out << aux1->valor.resistencia << endl;                       //SÉTIMA LINHA RESISTENCIA    
            aux1 = aux1->seguinte;
        }
    }
    file_out.close();
}