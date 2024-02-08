#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include "structs.h"
#include "ficheiros.h"

using namespace std;

NoArvore* novoNo(string nome) {
	NoArvore* novo = new NoArvore;
	novo->nome = nome;
	novo->esquerda = NULL;
	novo->direita = NULL;
	return novo;
}

int compara(string s1, string s2) {
	int i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) { 
		if (s1[i] < s2[i]) {
			return -1; //Significa que s1 vem primeiro (alfabéticamente) que s2
		}
		else {
			if (s1[i] > s2[i]) {
				return 1; //Significa que s2 vem primeiro (alfabéticamente) que s1
			}
		}
	}
	return 0; // Significa que são iguais
}

NoArvore* inserirNodo(NoArvore* raiz, string nome) {
	if (raiz == NULL) {
		raiz = novoNo(nome);
	}
	else {
		if (compara(raiz->nome, nome) >= 0) { //Compara a string com a raiz para saber se vai para a esquerda ou direita
			raiz->esquerda = inserirNodo(raiz->esquerda, nome);
		}
		else {
			raiz->direita = inserirNodo(raiz->direita, nome);
		}
	}
	return raiz;
}

void imprimirres(NoArvore* raiz){

	if (raiz == NULL)return;
	imprimirres(raiz->esquerda);
	cout << "|" << raiz->nome << "|";
	imprimirres(raiz->direita);
}

void addlista(string* conteudo, string value) {
	int i = 0;
	while (conteudo[i] != "") {
		i++;
	}
	conteudo[i] = value;
}

void restoarray(NoArvore* raiz, string* conteudo) { //Função recursiva que insere o nome dos produtos perdidos (que estão na arvore) num array
	if (raiz == NULL)return;
	restoarray(raiz->esquerda,conteudo);
	addlista(conteudo, raiz->nome);
	restoarray(raiz->direita,conteudo);
}

void cria_array(NoH** aux1, string* arrayres) { 

	for (int i = 0; i < (*aux1)->valor.raizT; i++)
		(arrayres)[i] = "";

	restoarray((*aux1)->valor.raiz, arrayres);
}

void guardaRegisto(Plantacao** plantacao) {
	string gravarReg("Registo.txt");
	fstream file_out;
	file_out.open(gravarReg, fstream::in | fstream::out);
	if (!file_out.is_open()) {
		cout << "Erro ao abrir " << gravarReg << endl;
		cout << endl;
	}
	else {
		limpar_file("Registo.txt");
		NoH* aux1 = new NoH;
		aux1 = (*plantacao)->cabeca;
		while (aux1 != NULL) {

			string* arrayres = new string[(aux1)->valor.raizT];

			cria_array(&aux1, arrayres);

			file_out << aux1->valor.nome << endl;
			file_out << aux1->valor.raizT << endl;
			for (int i = 0; i < aux1->valor.raizT; i++){
				file_out << arrayres[i] << endl;
			}
			aux1 = aux1->seguinte;

		}

	}
	file_out.close();
}

void lefchReg(Plantacao* plantacao) {
	ifstream file_reg;
	file_reg.open("Registo.txt", ios::in);
	NoH* aux1 = new NoH;
	aux1 = plantacao->cabeca;
	if (!file_reg.is_open()) {
		cout << "Erro ao abrir o ficheiro do registo" << endl;
		cout << endl;
	}
	else {
		string line;
		while (getline(file_reg, line)) {
			aux1->valor.raiz = NULL;
			aux1->valor.raizT = 0;
			getline(file_reg, line);
			aux1->valor.raizT = stoi(line);
			for (int i = 0; i < aux1->valor.raizT; i++) {
				getline(file_reg, line);
				aux1->valor.raiz=inserirNodo(aux1->valor.raiz, line);
			}
			aux1 = aux1->seguinte;
		}
	}
	file_reg.close();
}