//
// Created by culbec on 14.06.2023.
//
#include "../headers/soft.h"

Soft::Soft(int _id, const string& _descriere, const vector<string>& _programatori, const string& _stare): id{_id}, descriere{_descriere}, programatori{_programatori}, stare{_stare} {}

int Soft::getId() const {
    return this->id;
}

const string& Soft::getDescriere() const {
    return this->descriere;
}

const vector<string>& Soft::getProgramatori() const {
    return this->programatori;
}

const string& Soft::getStare() const {
    return this->stare;
}

void Soft::setStare(const std::string &st) {
    this->stare = st;
}