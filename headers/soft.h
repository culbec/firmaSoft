#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Soft{
private:
    int id;
    string descriere;
    vector<string> programatori;
    string stare;

public:
    /*
     * Initializeaza un soft.
     * @param _id: id-ul soft-ului
     * @param _descriere: descrierea
     * @param _programatori: lista de programatori
     * @param _stare: starea
     */

    Soft(int _id, const string& _descriere, const vector<string>& _programatori, const string& _stare);

    /*
     * Returneaza id-ul soft-ului
     */
    int getId() const;

    /*
     * Returneaza descrierea soft-ului
     */

    const string& getDescriere() const;

    /*
     * Returneaza lista de programatori a soft-ului
     */

    const vector<string>& getProgramatori() const;

    /*
     * Returneaza starea soft-ului
     */

    const string& getStare() const;

    /*
     * Seteaza starea unui soft
     * @param st: noua stare a soft-ului
     */

    void setStare(const string& st);
};