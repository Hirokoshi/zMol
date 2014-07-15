#include "Atoms.h"

Atoms::Atoms(std::string const& fileName) {
	std::ifstream file(fileName.c_str());

	// on essaie d'ouvrir le fichier
	try {
		if (!file) {
			throw std::string("Erreur : impossible d'ouvrir le fichier");
		}
	}
	catch (std::string const& error) {
		std::cerr << error << std::endl;
	}
	
	// lecture du fichier ligne par ligne
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);

		std::string atom;
		iss >> atom;
		double mmass;
		iss >> mmass;

		mols[atom] = mmass;
	}

	file.close();
}

double Atoms::getMmass(std::string const& atom) {
	// recherche de l'atome dans la map
	auto iterator = mols.find(atom);

	// atome trouvé
	try {
		if (iterator != mols.end()) {
			return iterator->second;
		}
		else throw std::string("Erreur : element non trouve.");
	}
	catch (std::string const& error) {
		std::cerr << error << std::endl;
	}
}