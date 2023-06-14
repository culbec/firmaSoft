#pragma once

#include <QTableView>
#include <QListWidget>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>

#include "service.h"
#include "Observer.h"
#include "Observable.h"
#include "TableModel.h"

class StateWnd: public Observer, public Observable, public QWidget{
protected:
    Service& service;

    QLayout *openLay = new QVBoxLayout;

    QListWidget *softLst = new QListWidget;

    QLayout *btnLay = new QHBoxLayout;
    QGroupBox *btns = new QGroupBox("Buttons");
    QPushButton *btnOpen = new QPushButton("&Open");
    QPushButton *btnProgress = new QPushButton("&In progress");
    QPushButton *btnClosed = new QPushButton("&Closed");

public:
    /*
     * Construieste o clasa stateWnd care va fi baza pt. celelalte clase
     */
    StateWnd(Service& serv): service{serv} {
        this->setLayout(openLay);
        this->openLay->addWidget(this->softLst);

        this->btns->setLayout(this->btnLay);
        this->btnLay->addWidget(this->btnOpen);
        this->btnLay->addWidget(this->btnProgress);
        this->btnLay->addWidget(this->btnClosed);

        this->openLay->addWidget(this->btns);

        QObject::connect(this->btnOpen, &QPushButton::clicked, [this](){
            this->setState("Open");
        });

        QObject::connect(this->btnProgress, &QPushButton::clicked, [this](){
            this->setState("In progress");
        });

        QObject::connect(this->btnClosed, &QPushButton::clicked, [this](){
            this->setState("Closed");
        });
    }

    virtual void reloadList() = 0;

    virtual void setState(const string& State){
        auto ind = this->softLst->currentIndex();
        if(ind.row() < 0 || ind.row() > this->service.getSofts().size()) {
            return;
        }
        this->service.setStare(this->service.getSofts().at(ind.row()).getId(), State);
        this->reloadList();
        this->notify();
    };

    void update() override {
        this->reloadList();
    }
};

/*
 * open state wnd
 */
class OpenState: public StateWnd{
public:
    OpenState(Service& serv): StateWnd{serv} {}

    void reloadList() override {
        this->softLst->clear();

        for(const auto& _soft: this->service.getSofts()) {
            if(_soft.getStare() == "Open") {
                auto _id = QString::fromStdString(to_string(_soft.getId()));
                auto _desc = QString::fromStdString(_soft.getDescriere());
                auto _stare = QString::fromStdString(_soft.getStare());
                auto _progs = QString::fromStdString(to_string(_soft.getProgramatori().size()));

                auto item = QString{_id + "\t" + _desc + "\t" + _stare + "\t" + _progs};

                this->softLst->addItem(item);
            }
        }
    }
};

/*
 * progress state wnd
 */
class ProgressState: public StateWnd{
public:
    ProgressState(Service& serv): StateWnd{serv} {}

    void reloadList() override {
        this->softLst->clear();

        for(const auto& _soft: this->service.getSofts()) {
            if(_soft.getStare() == "In progress") {
                auto _id = QString::fromStdString(to_string(_soft.getId()));
                auto _desc = QString::fromStdString(_soft.getDescriere());
                auto _stare = QString::fromStdString(_soft.getStare());
                auto _progs = QString::fromStdString(to_string(_soft.getProgramatori().size()));

                auto item = QString{_id + "\t" + _desc + "\t" + _stare + "\t" + _progs};

                this->softLst->addItem(item);
            }
        }
    }
};

/*
 * closed state wnd
 */
class ClosedState: public StateWnd{
public:
    ClosedState(Service& serv): StateWnd{serv} {}

    void reloadList() override {
        this->softLst->clear();

        for(const auto& _soft: this->service.getSofts()) {
            if(_soft.getStare() == "Closed") {
                auto _id = QString::fromStdString(to_string(_soft.getId()));
                auto _desc = QString::fromStdString(_soft.getDescriere());
                auto _stare = QString::fromStdString(_soft.getStare());
                auto _progs = QString::fromStdString(to_string(_soft.getProgramatori().size()));

                auto item = QString{_id + "\t" + _desc + "\t" + _stare + "\t" + _progs};

                this->softLst->addItem(item);
            }
        }
    }
};

class mainWindow: public Observer, public QWidget {
private:
    Service& service;

    QLayout* mainLay = new QHBoxLayout;

    TableModel *tableModel;
    QTableView *tblVi = new QTableView;

    QLayout* cmdsLay = new QVBoxLayout;
    QGroupBox *cmdsGB = new QGroupBox{"Commands"};

    QFormLayout *addLay = new QFormLayout;
    QGroupBox *addGB = new QGroupBox{"Add"};
    QLineEdit *idLine = new QLineEdit;
    QLineEdit *descLine = new QLineEdit;
    QLineEdit *progsLine = new QLineEdit;
    QLineEdit *stareLine = new QLineEdit;
    QPushButton *btnAdd = new QPushButton{"&Add"};

    QFormLayout* findLay = new QFormLayout;
    QGroupBox *findGB = new QGroupBox;
    QLineEdit *nameLine = new QLineEdit;
    QPushButton *btnFind = new QPushButton{"&Find"};

    /*
     * initializeaza gui-ul
     */
    void initGUI();

    /*
     * conecteaza semnalele
     */
    void connectSigs();

    /*
     * reincarca tabelul
     * @param softs: lista de soft-uri pentru reincarcare
     */
    void reloadTable(vector<Soft>& softs);

public:
    /*
     * initializeaza un obiect de tip mainWindow
     * @param serv: service-ul de care este dependent
     */
    mainWindow(Service& serv);

    void update() override;
};

