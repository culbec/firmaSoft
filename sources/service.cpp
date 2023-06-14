#include "../headers/service.h"

Service::Service(Repository &repo): repository{repo} {}

bool Service::validateSoft(const Soft &soft) {
    if(soft.getDescriere().empty()) {
        return false;
    }

    if(soft.getProgramatori().size() > 4 && soft.getProgramatori().empty()) {
        return false;
    }

    if(soft.getStare() != "Open" && soft.getStare() != "In progress" && soft.getStare() != "Closed") {
        return false;
    }

    for(const auto& _soft: this->repository.getSofts()) {
        if(soft.getId() == _soft.getId()) {
            return false;
        }
    }

    return true;
}

void Service::addSoft(int _id, const std::string &_descriere, const vector<std::string> &_programatori,
                      const std::string &_stare) {
    Soft soft{_id, _descriere, _programatori, _stare};

    if(!validateSoft(soft)) {
        throw runtime_error("Soft-ul nu este valid!\n");
    }

    this->repository.addSoft(soft);
}

void Service::setStare(const int &id, const std::string &_stare) {
    for(auto i = 0; i < this->repository.getSofts().size(); i++) {
        if(this->repository.getSofts().at(i).getId() == id) {
            this->repository.setStare(i, _stare);
            break;
        }
    }
}

vector<Soft>& Service::getSofts() {
    return this->repository.getSofts();
}

void Service::sortSofts() {
    sort(this->repository.getSofts().begin(), this->repository.getSofts().end(), [](const Soft& soft1, const Soft& soft2){
        return soft1.getStare() > soft2.getStare();
    });
}

vector<Soft> Service::filterSofts(const std::string &name) {
    vector<Soft> filtered;

    for(const auto& _soft: this->repository.getSofts()) {
        for(const auto& _programator: _soft.getProgramatori()) {
            if(name == _programator) {
                filtered.push_back(_soft);
                break;
            }
        }
    }

    return filtered;
}