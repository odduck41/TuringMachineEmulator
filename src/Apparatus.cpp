#include "../include/Apparatus.h"

#include <qeventloop.h>

#include <QTableWidget>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QTimer>
#include <iostream>

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
    table = window->table;
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
    emit finish();
    State = 0;
    steps = 0;
    Ribbon->horizontalScrollBar()->setValue(250);
    TableScrollBar = 250;
    TablePos = 250 + 9;
    for (int i = 0; i < Ribbon->columnCount(); ++i) {
        const auto cell = dynamic_cast<QLabel*>(Ribbon->cellWidget(0, i)->children()[0]);
        cell->setText("λ");
    }
    for (int i = TablePos; i - TablePos < str.size() ; ++i) {
        const auto cell = dynamic_cast<QLabel*>(Ribbon->cellWidget(0, i)->children()[0]);
        cell->setText(QString(str[i - TablePos]));
    }
    Mario->setGeometry({
    462, 317 + 13, 50, 50
    });
    Mario->setObjectName("Mario_d");
    updated = true;
}

void Apparatus::inc() {
    if (speed < 2) {
        speed += 0.1;
    }
}
void Apparatus::dec() {
    if (speed > 0.2) {
        speed -= 0.1;
    }
}



void Apparatus::step() {
    updated = false;
    // command := {((symbol & ![<, >]) |& [<, >] |& state) | (!)}, 1 <= size <= 3
    const auto cell = dynamic_cast<QLabel*>(Ribbon->cellWidget(0, TablePos)->children()[0]);
    QString command = table->getCommand(cell->text()[0], State);
    if (command == "!") {
        steps = 0;
        emit finish();
        return;
    }
    if (command[0] == '>' || command[0] == '<') {
        if (command[0] == '>') GoRight();
        // else GoLeft();
        if (command.size() >= 2) {
            State = command.sliced(1).toInt();
        }
    } else {
        cell->setText(command[0]);
        if (command[1] == '>') {
            // JumpRight();
            GoRight();
        } else {
            // JumpLeft();
            // GoLeft();
        }
        if (command.size() >= 3) {
            State = command.sliced(2).toInt();
        }
    }
    if (updated) {
        Mario->setGeometry({
        462, 317 + 13, 50, 50
        });
        Mario->setObjectName("Mario_d");
        updated = false;
    }
    --steps;
    if (steps < 0) {
        steps = 0;
        return;
    }
    if (steps == 0) {
        emit finish();
    }
}

void Apparatus::GoRight() {
    ++TablePos;
    if (Mario->pos() == QPoint{962, 330}) {
        const auto mario = new QPropertyAnimation(Mario, "pos");
        mario->setEndValue(QPoint{712, 330});
        mario->setDuration((int)(1000 / speed));
        mario->setEasingCurve(QEasingCurve::InOutExpo);

        const auto ribbon = new QPropertyAnimation(Ribbon, "pos");
        ribbon->setTargetObject(Ribbon->horizontalScrollBar());
        ribbon->setPropertyName("value");
        ribbon->setEndValue(TableScrollBar += 6);
        ribbon->setDuration((int)(900 / speed));
        ribbon->setEasingCurve(QEasingCurve::InOutExpo);

        mario->start();
        ribbon->start();

        QEventLoop loop;
        connect(ribbon, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        loop.exec();

        return;
    }
    const auto mario = new QPropertyAnimation(Mario, "pos");
    mario->setEndValue(Mario->pos() + QPoint{50, 0});
    mario->setDuration((int)(300 / speed));

    const auto changer = new QTimer;
    changer->setInterval((int)(50 / speed));

    changer->start();
    QEventLoop loop;
    connect(changer, &QTimer::destroyed, &loop, &QEventLoop::quit);
    connect(mario, &QPropertyAnimation::finished, [this, changer] {
        Mario->setObjectName("Mario_d");
        changer->stop();
        delete changer;
    });
    mario->start();
    loop.exec();
}

