#include "../headers/repo.h"

Repository::Repository(const std::string &f): fileName{f} {
    this->loadFromFile();
}

void Repository::loadFromFile() {
    ifstream fin(this->fileName);

    if(!fin.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul!\n");
    }

    while(!fin.eof()) {
        string _id;
        getline(fin, _id, '\n');

        if(fin.eof()) {
            break;
        }

        string _descriere, _programator;
        vector<string> _programatori;

        getline(fin, _descriere, '\n');
        getline(fin, _programator, '\n');
        while(_programator != "Open" && _programator != "In progress" && _programator != "Closed") {
            _programatori.push_back(_programator);
            getline(fin, _programator, '\n');
        }
        string _stare = _programator;

        this->softs.emplace_back(stoi(_id), _descriere, _programatori, _stare);
    }
    fin.close();
}

void Repository::writeToFile(const Soft& soft) {
    ofstream fout(this->fileName, std::ios::app);

    if(!fout.is_open()) {
        throw runtime_error("Nu se poate deschide fisierul!\n");
    }

    fout << soft.getId() << "\n";
    fout << soft.getDescriere() << "\n";
    for(const auto& programator: soft.getProgramatori()) {
        fout << programator << "\n";
    }
    fout << soft.getStare() << "\n";

    fout.close();
}

vector<Soft>& Repository::getSofts() {
    return this->softs;
}

void Repository::setStare(const int &pos, const std::string &_stare) {
    this->softs.at(pos).setStare(_stare);
    ofstream(this->fileName, std::ios::trunc);

    for(const auto& _soft: this->softs) {
        this->writeToFile(_soft);
    }
}

void Repository::addSoft(const Soft &soft) {
    this->softs.push_back(soft);
    this->writeToFile(soft);
}

