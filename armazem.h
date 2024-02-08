#pragma once

using namespace std;

void criar_produto(int n_produtos, int* paT, string* p, string* a, string* f, Produto* s);
void mostra_arm(Armazem** arm);
void inserirarm(Armazem** arm, int n_produtos, Produto* produtos);
void removerarm(No** p, Armazem** arm);
Armazem* insereArmazem(Armazem* arm, Produto* p);
Armazem* lerarmfch(Armazem* arm);