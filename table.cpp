#include "table.h"

TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent) {
    this->setStyleSheet(
                    "border: 0;"
                    "font: 14pt \"CozetteVector\";"
                    "gridline-color:black;"
                    );
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setGeometry({
        0,
        0,
        500,
        250
    });
    this->setColumnCount(2);
    this->setRowCount(2);
    this->setItem(0, 0, new QTableWidgetItem);
    this->setItem(1, 0, new QTableWidgetItem("0"));
    this->item(0, 0)->setFlags(
        this->item(0, 0)->flags() & ~Qt::ItemIsEditable
    );
    this->item(1, 0)->setFlags(
        this->item(1, 0)->flags() & ~Qt::ItemIsEditable
    );
}

QString TableWidget::command(const QString& letter, int state) {
    return this->item(state + 1, commands[letter])->text();
}

void TableWidget::addState() {
    this->insertRow(this->rowCount());
    const auto item = new QTableWidgetItem(
        QString::fromStdString(std::to_string(this->rowCount() - 2))
    );
    this->setItem(this->rowCount() - 1, 0, item);
    this->item(this->rowCount() - 1, 0)->setFlags(
        this->item(this->rowCount() - 1, 0)->flags() &
        ~Qt::ItemIsEditable
    );
}

void TableWidget::removeState() {
    if (this->rowCount() == 2) return;
    delete this->cellWidget(this->rowCount() - 1, 0);
    this->removeRow(this->rowCount() - 1);
}

void TableWidget::setAlph(const QString& ribbon, const QString& head) {
    std::set<QChar> R, H;
    for (auto letter: ribbon) {
        R.insert(letter);
    }
    for (auto letter: head) {
        H.insert(letter);
    }
    for (const auto& r: R) {
        for (auto& h: H) {
            if (r == h) {
                H.erase(h);
                break;
            }
        }
    }


}
