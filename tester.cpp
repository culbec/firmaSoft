#include "tester.h"

void tester::testEntity() {
    vector<string> programatori{"Marian", "Ion", "Maria"};
    Soft soft{1, "Simulare", programatori, "closed"};
    assert(soft.getId() == 1);
    assert(soft.getDescriere() == "Simulare");
    assert(soft.getProgramatori().size() == 3 && soft.getProgramatori().at(0) == "Marian");
    assert(soft.getStare() == "closed");

    soft.setStare("open");
    assert(soft.getStare() == "open");
}

void tester::testRepo() {
    string fileName = "testRepo.txt";
    std::ofstream(fileName, std::ios::trunc);

    Repository repo{fileName};
    repo.addSoft(Soft{1, "ceva", vector<string>{"Marian"}, "Open"});
    assert(repo.getSofts().size() == 1);

    Repository repository1{fileName};
    assert(repo.getSofts().size() == 1);

    repository1.setStare(0, "Closed");
    assert(repository1.getSofts().at(0).getStare() == "Closed");
}

void tester::testService() {
    string fileName = "testRepo.txt";
    std::ofstream(fileName, std::ios::trunc);

    Repository repo{fileName};
    Service service{repo};

    service.addSoft(0, "ceva", vector<string>{"Marian", "Ioana"}, "Open");
    service.addSoft(1, "altceva", vector<string>{"Ioana"}, "Closed");

    try{
        service.addSoft(0, "aa", vector<string>{}, "csa");
        assert(false);
    } catch(runtime_error& rE) {
        assert(true);
    }

    service.addSoft(2, "altcevaceva", vector<string>{"Andrei"}, "Open");
    service.sortSofts();

    assert(service.getSofts().at(1).getId() == 2);

    vector<Soft> filtered = service.filterSofts("Ioana");
    assert(filtered.size() == 2);

    service.setStare(2, "Closed");
    assert(service.getSofts().at(1).getStare() == "Closed");
}