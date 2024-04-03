#include "../include/TableWidget.h"

#include <QPushButton>
#include <set>
#include <QHBoxLayout>


TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent) {
    prnt = parent;

    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setGeometry({
        0, 0, 500, 280
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

    this->setSelectionMode(QAbstractItemView::NoSelection);

    connect(this, &QTableWidget::cellChanged, this, &TableWidget::check);
}

void TableWidget::check() {
    if (!checking) return;
    bool flag = false;
    for (int row = 1; row < this->rowCount(); ++row) {
        for (int column = 1; column < this->columnCount(); ++column) {
            if (this->item(row, column) != nullptr) {
                if (this->item(row, column)->text().contains('!')) {
                    flag = true;
                }
                const auto txt = this->item(row, column)->text();
                QString skip = "1234567890!><\\";
                for (auto& letter: txt) {
                    if (skip.contains(letter)) continue;
                    bool is = false;
                    for (int ch = 1; ch < this->columnCount(); ++ch) {
                        if (letter == this->item(0, ch)->text()) {
                            is = true;
                        }
                    }
                    if (!is) {
                        emit symbol();
                        return;
                    }
                }

            }
        }
    }
    if (!flag) {
        emit incorrect();
    } else {
        emit correct();
    }
}

void TableWidget::addState() {
    this->insertRow(this->rowCount());
    this->setItem(this->rowCount() - 1, 0,
        new QTableWidgetItem(
            QString::number(this->rowCount() - 2)
        )
    );
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

void TableWidget::updateAlph(const QString& ribbon, const QString& head) {
    std::set<QChar> Ribbon, Head;

    for (const auto& letter: ribbon) Ribbon.insert(letter);
    for (const auto& letter: head) Head.insert(letter);
    for (const auto& r: Ribbon) Head.erase(r);

    const auto other = new TableWidget(dynamic_cast<QWidget*>(this->parent()));
    other->setColumnCount(static_cast<int>(Head.size() + Ribbon.size() + 2));
    for (int state = 0; state < this->rowCount() - 2; ++state) {
        other->addState();
    }

    int column = 1;
    for (const auto& letter: Ribbon) {
        other->setItem(0, column, new QTableWidgetItem(letter));
        other->item(0, column)->setFlags(other->item(0, 0)->flags());
        ++column;
    }
    other->setItem(0, column, new QTableWidgetItem("λ"));
    other->item(0, column)->setFlags(other->item(0, 0)->flags());
    ++column;
    for (const auto& letter: Head) {
        other->setItem(0, column, new QTableWidgetItem(letter));
        other->item(0, column)->setFlags(other->item(0, 0)->flags());
        ++column;
    }
    for (int c = 1; c < other->columnCount(); ++c) {
        if (const auto& f = this->getColumn(other->item(0, c)->text()); f != -1) {
            for (int i = 1; i < this->rowCount(); ++i) {
                if (this->item(i, f) != nullptr) {
                    other->setItem(i, c,
                        new QTableWidgetItem(this->item(i, f)->text()));
                }
            }
        }
    }
    *this = *other;
    delete other;
}

TableWidget& TableWidget::operator=(const TableWidget& other) {
    this->clear();
    this->setColumnCount(other.columnCount());
    this->setRowCount(other.rowCount());
    for (int r = 0; r < other.rowCount(); ++r) {
        for (int c = 0; c < other.columnCount(); ++c) {
            if (other.item(r, c) != nullptr) {
                const auto& item = new QTableWidgetItem();
                *item = *other.item(r, c);
                this->setItem(r, c, item);
                this->item(r, c)->setFlags(other.item(r, c)->flags());
            }
        }
    }
    this->prnt = other.prnt;
    btn = new QPushButton(this);
    btn->setObjectName("table");
    connect(btn, &QPushButton::pressed, [this] {
        if (this->parent() == prnt) {
            this->setParent(nullptr);
            this->setStyleSheet(style);
        } else {
            this->setParent(prnt);
            this->setGeometry({
                0, 0, 500, 280
            });
        }
        this->show();
    });
    this->setCellWidget(0, 0, btn);

    return *this;
}

int TableWidget::getColumn(const QString& s) const {
    for (int i = 0; i < this->columnCount(); ++i) {
        if (this->item(0, i) != nullptr && this->item(0, i)->text() == s) {
            return i;
        }
    }
    return -1;
}

QString TableWidget::getCommand(const QChar& letter, const int state) {
    const auto cell = this->item(state + 1, getColumn(letter));
    clearPaint();
    paint(cell);
    if (cell == nullptr) {
        return "FUCK";
    }
    return cell->text();
}

void TableWidget::clearPaint() const {
    for (int row = 1; row < this->rowCount(); ++row) {
        for (int column = 1; column < this->columnCount(); ++column) {
            if (this->item(row, column) != nullptr) {
                this->item(row, column)->setBackground(QColor(Qt::white));
            }
        }
    }
}

void TableWidget::paint(QTableWidgetItem* a) {
    if (a != nullptr) {
        a->setBackground(QColor(Qt::green));
    } else {
        emit not_found();
    }
}
