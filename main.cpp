#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>

#include "structs.h"
#include "ficheiros.h"
#include "armazem.h"
#include "hortas.h"
#include "gestao.h"
#include "registo.h"

using namespace std;

void perguntar_responsasveis(string alphabet, Plantacao* h) {
    int k = 0;
    NoH* aux = h->cabeca;
    while (aux != NULL) {
        cout << "Qual o nome do respons�vel da horta " << alphabet[k] << "?" << endl;
        getline(cin, aux->valor.agricultor);
        aux = aux->seguinte;
        k++;
    }
}

void opcoes(Plantacao* plantacao, Armazem* arm, string* a, int* paT, string* areas, Praga* praga) {
    bool sair = false;
    do {
        int opcao;
        cout << "\n***** Bem Vindo Gestor ***** \n";
        cout << "(1). Colher Produto \n";
        cout << "(2). Atualizar tempo de rega \n";
        cout << "(3). Gravar Planta��o \n";
        cout << "(4). Carregar Planta��o \n";
        cout << "(5). Imprimir planta��o \n";
        cout << "(6). Imprimir produtos colhidos \n";
        cout << "(7). Criar nova �rea \n";
        cout << "(8). Alterar �rea \n";
        cout << "(9). Fertiliza��o \n";
        cout << "(0). Voltar \n";
        cout << "Seleccione a sua op��o:";
        cin >> opcao;
        switch (opcao) {
        case 1:
            colheitaManual(&plantacao); //Colheita Manual
            break;
        case 2:
            atu_temporega(&plantacao, &arm); //Atualizar tempo de rega
            break;
        case 3:
            gravarh(&plantacao); //Gravar as hortas (ou planta��o)
            gravar_arm(&arm); //Gravar armazem
            gravarPraga(praga); //Gravar lista dos produtos perdidos
            guardaRegisto(&plantacao); //Gravar arvores dos registos
            cout << "\nGuardado com sucesso!\n";
            break;
        case 4:
            plantacao = lehortasfch(plantacao); //Carregar as hortas (ou planta��o)
            mostra_hortas(plantacao);
            arm = lerarmfch(arm); //Carregar armazem
            mostra_arm(&arm);
            praga = lerfchPraga(praga); //Carregar lista dos produtos perdidos
            lefchReg(plantacao); //Carregar arvores dos registos
            break;
        case 5:
            ordem_alfabetica(plantacao); //Imprimir horta por ordem alfab�tica
            break;
        case 6:
            imprimirprodcol(&plantacao); //Imprimir arvore do registo por ordem alfab�tica
            break;
        case 7:
            nova_area(a, paT, areas); //Criar nova area
            break;
        case 8:
            cout << endl;
            alterar_area(&plantacao, a, paT); //Alterar area da horta
            cout << endl;
            break;
        case 9:
            ver_fertiliza�ao(&plantacao); //Fertiliza��o de areas
            break;
        case 0:
            cout << "Escolheu a opcao VOLTAR" << endl;
            sair = true;
            break;
        }
    } while (!sair);
}

int main() {
    locale::global(locale(""));

    srand(time(NULL));

    string* pa = new string[ler_linhas_ficheiro("areas.txt")]; //Criar array de areas vindas do ficheiro txt de areas
    string* pp = new string[ler_linhas_ficheiro("produtos.txt")]; //Criar array de produtos vindos do ficheiro txt de produtos
    string* pf = new string[ler_linhas_ficheiro("fornecedores.txt")]; //Criar array de fornecedores vindos do ficheiro txt de fornecedores

    int paT = ler_linhas_ficheiro("areas.txt"); //Tamanho do array de todas as areas (para utilizar em fun��es futuras)

    const string alphabet = "ABCDEFGHIJ";

    array_ficheiros("areas.txt", pa);
    array_ficheiros("fornecedores.txt", pf); //Colocar as areas, fornecedores e nome dos produtos em arrays
    array_ficheiros("produtos.txt", pp);

    Armazem* arm = new Armazem; //Inicializar o armazem
    arm->armT = 0;
    arm->cabeca = NULL;

    Plantacao* plantacao = new Plantacao; //Inicializar a plantacao
    plantacao->cabeca = NULL;
    plantacao->n_hortas = rand() % 6 + 5;

    Produto* produtos = new Produto[15]; //Criar um array auxiliar para os produtos a inserir no armazem

    Praga* lstpraga = new Praga; //Inicializar a lista dos produtos perdidos
    lstpraga->cabeca = NULL;
    lstpraga->tamanho = 0;

    criar_produto(15,&paT,pp,pa,pf,produtos); //Criar 15 novos produtos
    cria_hortas(&plantacao,pa,alphabet,&paT); //Criar as hortas

    perguntar_responsasveis(alphabet,plantacao); //Perguntar os nomes dos respons�veis das hortas

    inserirarm(&arm, 15, produtos); //Inserir os 15 novos produtos criados no armazem

    delete[] produtos;

    mostra_hortas(plantacao); //Imprimir as hortas
    mostra_arm(&arm); //Imprimir o armazem

    string* areas = new string[100]; //Criar um array auxilar identico ao das areas do ficheiro (Usaremos na fun��o de nova area)

    for (int o = 0; o < paT; o++) { //Inserindo todas as areas no array auxiliar
        areas[o] = pa[o];
    }

    bool sair = false;
    char opcao;
    do
    {
        cout << "\n(s)eguinte *********** (g)est�o\n" << endl;
        cout << "Seleccione a sua op��o:";
        cin >> opcao;
        switch (opcao) {
        case 's':

            pa = areas; //Igualando o array das areas ao array auxiliar (Por causa da fun��o nova area)

            cout << endl;

            colhido(&plantacao); //Fun��o colhido que verifica todos os produtos das hortas e tem 25% de chance de os colher

            produtos = new Produto[10]; //Criar novo array para os produtos que vamos criar

            criar_produto(10, &paT, pp, pa, pf, produtos); //Cria 10 novos produtos a inserir no armazem
            plantar(&plantacao, &arm); //Copia os produtos a inserir do armazem para as hortas correspondentes e ao mesmo tempo os elimina do pr�prio armazem
            inserirarm(&arm, 10, produtos); //Insere os 10 novos produtos criados no armazem

            cout << endl;

            pragas(&plantacao, &lstpraga);//Fun��o praga que randomiza a chance do produto ser destruido e destroi o mesmo se for o caso  //ESTE EST� SUS

            cout << endl;

            tempo_rega(&plantacao);//Atualiza os tempos de rega de produtos nas hortas

            fertilizacao(&plantacao);// Verifica cada horta para ver se s�o fertilizadas neste ciclo e se sim procede a fertilizar os seus produtos

            mostra_hortas(plantacao); //Imprimir as hortas
            mostra_arm(&arm); //Imprimir o armazem

            delete[] produtos;

            break;
        case 'g':

            opcoes(plantacao, arm, pa, &paT,areas,lstpraga); //Op��es da gest�o

            break;
        default:
            break;
        }
    } while (true);

    return 0;

}