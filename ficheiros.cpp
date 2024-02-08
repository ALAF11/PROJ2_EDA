#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int ler_linhas_ficheiro(string ficheiro) {
	ifstream file;
	file.open(ficheiro, ios::in);
	int num_linhas = 0;
	if (file.is_open()) { //Verificar se o ficheiro está aberto
		string line;
		while (getline(file, line)) { //Enquanto tem linhas somamos um valor
			num_linhas++;
		}
	}
	return num_linhas;
}

void array_ficheiros(string ficheiro, string* p) {
	ifstream file;
	file.open(ficheiro, ios::in);
	if (file.is_open()) { //Verificar se o ficheiro está aberto

		string line;
		while (getline(file, line)) { //Enquanto tem linhas adicionamos ao array
			*p = line;
			p++;
		}
	}
	file.close();
}

void limpar_file(string ficheiro) { //Limpa o ficheiro
	ofstream file(ficheiro);
	file << "";
}