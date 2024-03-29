#include "../include/Apparatus.h"
#include "../include/Window.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>

Apparatus::Apparatus(QWidget* parent) : QLabel(parent) {
    this->setGeometry({
        0, 280, 1024, 424
    });
    this->setObjectName("Apparatus");
    this->setStyleSheet(parent->styleSheet());
    this->CreateRibbon();
    this->CreateMario();
    auto ptr = parent;
    while (ptr->parentWidget() != nullptr) {
        ptr = ptr->parentWidget();
    }
    window = dynamic_cast<Window*>(ptr);
}

void Apparatus::CreateRibbon() {
    Ribbon = new QTableWidget(this);
    auto img = QImage("/home/lev/programming/animation_test/q.png");
    img = img.scaled(50, 50, Qt::KeepAspectRatio);
    Ribbon->setGeometry({
        12, 234 + 13, 1000, 50
    });
    Ribbon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Ribbon->horizontalHeader()->hide();
    Ribbon->verticalHeader()->hide();
    Ribbon->setStyleSheet("border-image: none;");
    Ribbon->setRowCount(1);
    Ribbon->horizontalHeader()->setDefaultSectionSize(50);
    Ribbon->verticalHeader()->setDefaultSectionSize(50);
    Ribbon->setShowGrid(false);
    for (int i = 0; i < 500; ++i) {
        Ribbon->insertColumn(Ribbon->columnCount());
        const auto block = new QLabel;
        block->setPixmap(QPixmap::fromImage(img));
        block->setScaledContents(true);
        block->setStyleSheet("border-image: none;");
        const auto txt = new QLabel("λ", block); //QChar('1' + i)
        txt->setObjectName("RibbonText");
        Ribbon->setCellWidget(0, i, block);
    }
}

void Apparatus::CreateMario() {
    Mario = new QWidget(this);
    Mario->setGeometry({
        462, 317 + 13, 50, 50
    });
    Mario->setObjectName("Mario_d");
}

void Apparatus::SetString(const QString& str) {
    Ribbon->horizontalScrollBar()->setValue(250);
    TablePos = 250 + 9;
    Mario->setGeometry({
        462, 317 + 13, 50, 50
    });
    Mario->setObjectName("Mario_d");
    for (int i = 0; i < Ribbon->columnCount(); ++i) {
        const auto cell = dynamic_cast<QLabel*>(Ribbon->cellWidget(0, i)->children()[0]);
        cell->setText("λ");
    }
    for (int i = TablePos; i - TablePos < str.size() ; ++i) {
        const auto cell = dynamic_cast<QLabel*>(Ribbon->cellWidget(0, i)->children()[0]);
        cell->setText(QString(str[i - TablePos]));
    }
    state = 0;
}


