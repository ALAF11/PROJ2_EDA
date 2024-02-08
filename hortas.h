#pragma once

using namespace std;

void cria_hortas(Plantacao** p, string* a, string alphabet, int* paT);
void mostra_hortas(Plantacao* p);
void insereplt(No** p, NoH** aux1);
void plantar(Plantacao** plantacao, Armazem** arm);
void removerplt(NoH** p, No** p2);
void colhido(Plantacao** plantacao);
void tempo_rega(Plantacao** plantacao);
void insereprg(Produto* p, Praga** lstpraga);
void pragas(Plantacao** plantacao, Praga** lstpraga);
Plantacao* lehortasfch(Plantacao* plantacao);
void gravarPraga(Praga* praga);
Praga* lerfchPraga(Praga* praga);