#pragma once
#include "soft.h"
#include <fstream>
#include <exception>

using std::ofstream;
using std::ifstream;
using std::runtime_error;
using std::getline;
using std::stoi;

class Repository {
private:
    vector<Soft> softs;
    const string& fileName;
    void loadFromFile();
    void writeToFile(const Soft& soft);

public:
    /*
     * Initializeaza un repository
     * @param f: numele fisierului care contine soft-urile
     */
    Repository(const string& f);

    /*
     * Returneaza lista de soft-uri
     */
    vector<Soft>& getSofts();

    /*
     * Seteaza starea unui soft
     * @param pos: pozitia in lista a soft-ului
     * @param _stare: starea de setat
     */
    void setStare(const int& pos, const string& _stare);

    /*
     * Adauga un soft in lista
     * @param soft: soft-ul de adaugat in lista
     */
    void addSoft(const Soft& soft);
};