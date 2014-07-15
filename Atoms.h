#ifndef ATOMS_H
#define ATOMS_H

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

class Atoms {
public:
	Atoms(std::string const& fileName);
	double getMmass(std::string const& atom);

private:
	std::map<std::string, double> mols;
};

#endif