#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "soft.h"

using std::vector;
using std::to_string;

class TableModel: public QAbstractTableModel {
private:
    vector<Soft> softs;

public:
    /*
     * Construieste un model custom pt table model
     * @param sfs: lista de soft-uri
     */
    TableModel(vector<Soft>& sfs): softs{sfs} {}

    /*
     * returneaza numarul de randuri ale modelului
     */
    int rowCount(const QModelIndex& index) const override {
        return this->softs.size();
    }

    /*
     * returneaza numarul de coloane
     */

    int columnCount(const QModelIndex& index) const override {
        return 4;
    }

    /*
     * returneaza data unui element din model
     */
    QVariant data(const QModelIndex& index, int role) const {
        if(role == Qt::DisplayRole) {
            auto soft = this->softs.at(index.row());

            if(index.column() == 0) {
                return QString::fromStdString(to_string(soft.getId()));
            } else if (index.column() == 1) {
                return QString::fromStdString(soft.getDescriere());
            } else if (index.column() == 2) {
                return QString::fromStdString(soft.getStare());
            } else if (index.column() == 3) {
                return QString::fromStdString(to_string(soft.getProgramatori().size()));
            }
        }
        return {};
    }

    /*
     * seteaza header-ul
     */

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if(role != Qt::DisplayRole) {
            return {};
        }

        if(orientation == Qt::Horizontal ) {
            if (section == 0) {
                return "Id";
            } else if (section == 1) {
                return "Descriere";
            } else if (section == 2) {
                return "Stare";
            } else if (section == 3) {
                return "Nr. programatori";
            }
        }
        return QAbstractTableModel::headerData(section, orientation, role);
    }


    /*
     * notifica modelul sa se modifice
     * @param soft: lista de soft-uri
     */
    void notify(vector<Soft>& soft) {
        this->softs = soft;
        emit layoutChanged();
    }
};