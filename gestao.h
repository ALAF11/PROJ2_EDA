#pragma once

using namespace std;

void colheitaManual(Plantacao** plantacao);
void atu_temporega(Plantacao** plantacao, Armazem** arm);
void ver_fertilizaçao(Plantacao** plantacao);
void fertilizacao(Plantacao** plantacao);
void nova_area(string* a, int* paT,string* areas);
void alterar_area(Plantacao** plantacao, string* a, int* paT);
void imprimirprodcol(Plantacao** plantacao);
void ordem_alfabetica(Plantacao* p);
void limpar_file(string ficheiro);
void gravarh(Plantacao** plantacao);
void gravar_arm(Armazem** arm);