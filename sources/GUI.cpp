#include "../headers/GUI.h"

mainWindow::mainWindow(Service& serv) : service{serv} {
    this->initGUI();
    this->connectSigs();

    this->service.sortSofts();

    this->reloadTable(this->service.getSofts());
}

void mainWindow::initGUI() {
    this->setLayout(this->mainLay);

    this->tableModel = new TableModel{this->service.getSofts()};
    this->tblVi->setModel(this->tableModel);

    this->tblVi->verticalHeader()->setVisible(false);
    this->tblVi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->mainLay->addWidget(this->tblVi);

    this->cmdsGB->setLayout(this->cmdsLay);
    this->mainLay->addWidget(this->cmdsGB);

    // add section
    this->addGB->setLayout(this->addLay);

    this->addLay->addRow(QString{"Id"}, this->idLine);
    this->addLay->addRow(QString{"Descriere"}, this->descLine);
    this->addLay->addRow(QString{"Programatori"}, this->progsLine);
    this->addLay->addRow(QString{"Stare"}, this->stareLine);
    this->addLay->addWidget(this->btnAdd);

    this->cmdsLay->addWidget(this->addGB);

    // find section
    this->findGB->setLayout(this->findLay);

    this->findLay->addRow(QString{"Nume programator"}, this->nameLine);
    this->findLay->addWidget(this->btnFind);

    this->cmdsLay->addWidget(this->findGB);

    OpenState *openState = new OpenState{this->service};
    ProgressState *progressState = new ProgressState{this->service};
    ClosedState *closedState = new ClosedState{this->service};

    // adding the observers
    openState->addObserver(this);
    openState->addObserver(closedState);
    openState->addObserver(progressState);

    closedState->addObserver(this);
    closedState->addObserver(openState);
    closedState->addObserver(progressState);

    progressState->addObserver(this);
    progressState->addObserver(openState);
    progressState->addObserver(closedState);

    openState->show();
    closedState->show();
    progressState->show();

    openState->reloadList();
    closedState->reloadList();
    progressState->reloadList();

    this->show();
}

void mainWindow::connectSigs() {
    QObject::connect(this->btnAdd, &QPushButton::clicked, [this](){
        int _id = this->idLine->text().toInt();
        string _desc = this->descLine->text().toStdString();

        vector<string> _progs;
        auto _progsList = this->progsLine->text().split(",");
        for(const auto& _name: _progsList) {
            _progs.push_back(_name.toStdString());
        }

        string _stare = this->stareLine->text().toStdString();
        try {
            this->service.addSoft(_id, _desc, _progs, _stare);
        } catch(runtime_error& rE) {
            QMessageBox::warning(this, "Warning", rE.what());
        }
        this->service.sortSofts();
        this->reloadTable(this->service.getSofts());
    });

    QObject::connect(this->btnFind, &QPushButton::clicked, [this](){
        vector<Soft> filtered = this->service.filterSofts(this->nameLine->text().toStdString());
        this->reloadTable(filtered);
    });
}

void mainWindow::reloadTable(vector<Soft> &softs) {
    this->tableModel->notify(softs);
}



void mainWindow::update() {
    this->service.sortSofts();
    this->reloadTable(this->service.getSofts());
}