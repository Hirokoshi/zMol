#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Atoms.h"

int chartoint(char character);
double result(std::string const& molec, Atoms &atoms);

int main() {
	// Lecture du fichier
	std::string const fileName("mols.txt");
	Atoms atoms(fileName);

	// Stockage de la molécule entrée par l'utilisateur
	std::cout << "Entrez une molecule" << std::endl;
	std::string mol;
	std::cin >> mol;

	double mmass(0);

	// si la molécule contient une parenthèse fermante
	if (mol.find(')') != std::string::npos) {
		// récupération de la position de la parenthèse fermante
		std::size_t ferm_pos = mol.find(')');
		std::size_t ouvr_pos = mol.find('(');

		// récupération du contenu des parenthèses
		std::string content = mol.substr(ouvr_pos + 1, ferm_pos - 1);

		// récupération du coef
		int coef = chartoint('A');

		for (int x(0); x < coef; x++) {
			mmass += result(content, atoms);
		}

		std::string test = mol.substr(ferm_pos + 2, mol.size());

		if (test.size() != 0)
			mmass += result(test, atoms);
	}
	else {
		mmass = result(mol, atoms);
	}

	std::cout << mmass << std::endl;

	system("pause");
	return 0;
}

int chartoint(char character) {
	try {
		if (isdigit(character)) {
			std::stringstream sstream;
			sstream << character;

			int integer;
			sstream >> integer;

			return integer;
		}
		else {
			throw std::string("Erreur : caractere non digital.");
		}
	}
	catch (std::string const& error) {
		std::cerr << error << std::endl;
	}

}

double result(std::string const& molec, Atoms &atoms) {
	double final_result(0);

	for (int i(0); i < molec.size(); i++) {
			// 1er cas : 2 lettres + coef
			if (isupper(molec[i]) && islower(molec[i + 1]) && isdigit(molec[i + 2])) {
				std::string atom{ molec[i] };
				atom += molec[i + 1];

				// récupération du coef
				int coef = chartoint(molec[i + 2]);

				final_result += atoms.getMmass(atom) * coef;
				i += 2;
			}
			// 2e cas : 1 lettre + coef
			else if (isupper(molec[i]) && isdigit(molec[i + 1])) {
				std::string atom{ molec[i] };

				// coef
				int coef = chartoint(molec[i + 1]);

				final_result += atoms.getMmass(atom) * coef;
				i++;
			}
			// 3e cas : 2 lettres
			else if (isupper(molec[i]) && islower(molec[i + 1])) {
				std::string atom{ molec[i] };
				atom += molec[i + 1];

				final_result += atoms.getMmass(atom);
				i++;
			}
			// 4e cas : 1 seul lettre
			else {
				std::string atom{ molec[i] };
				final_result += atoms.getMmass(atom);
			}
	}

	return final_result;
}