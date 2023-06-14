#pragma once

#include "repo.h"
#include <algorithm>

class Service{
private:
    Repository& repository;

public:
    /*
     * Initializeaza un service
     * @param repo: repository-ul service-ului
     */
    Service(Repository& repo);

    /*
     * Valideaza un soft
     * @return true: soft-ul este valid
     * @return false: soft-ul este invalid
     */
    bool validateSoft(const Soft& soft);

    /*
     * Adauga un soft in lista
     * @param _id: id-ul soft-ului
     * @param _descriere: descrierea soft-ului
     * @param _programatori: lista de programatori a soft-ului
     * @param _stare: starea soft-ului
     */
    void addSoft(int _id, const string& _descriere, const vector<string>& _programatori, const string& _stare);

    /*
     * Returneaza lista de soft-uri
     */
    vector<Soft>& getSofts();

    /*
     * Seteaza starea unui soft
     * @param id: id-ul soft-ului de modificat strea
     * @param _stare: starea noua
     */
    void setStare(const int& id, const string& _stare);

    /*
     * Sorteaza soft-urile
     */
    void sortSofts();

    /*
     * Filtreaza soft-urile care au macar un programator cu numele name
     * @param name: numele prog
     */
    vector<Soft> filterSofts(const string& name);
};