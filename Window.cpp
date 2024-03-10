#include "Window.h"
#include "table.h"

Window::Window(QWidget* parent): QMainWindow(parent) {
    this->setGeometry({0, 0,
        1024, 512 + 256});
    central->setGeometry({0, 42,
        this->width(), this->height() - 42});
    this->setStyleSheet("QMainWindow {"
                        "background-color: rgb(53, 53, 53);"
                        "}");
    this->setWindowFlags(Qt::FramelessWindowHint);
    title->setGeometry({6, 6, 1012, 30});
    title->setStyleSheet("QPushButton {"
                         "background-color:rgba(0, 0, 0, 80);"
                         "color:white;"
                         "border-radius: 10px;"
                         "font: 14pt \"CozetteVector\";"
                         "}"
                         "QPushButton:hover {"
                         "background-color:rgba(0, 0, 0, 100);"
                         "color:white;"
                         "border-radius: 10px;"
                         "font: 14pt \"CozetteVector\";"
                         "}"
                         );
    title->setText("Turing Machine");
    connect(title, &QPushButton::pressed, [this]() {
        this->close();
        exit(0);
    });
    App = new Apparatus(central);
    App->hide();
    central->setFocusPolicy(Qt::ClickFocus);
    Load();
    title->show();
}

void Window::Load() {
    const auto Ribbon = new QLineEdit(this->central);
    const auto Head = new QLineEdit(this->central);
    Ribbon->setStyleSheet(
        "QLineEdit {"
        "border-radius: 15px;"
        "background-color:rgb(255, 255, 255);"
        "color:rgb(0, 0, 0);"
        "font: 14pt \"CozetteVector\";"
        "}"
    );
    Head->setStyleSheet(Ribbon->styleSheet());
    Ribbon->setGeometry({50, 110, 210, 60});
    Head->setGeometry({
        1024 - 50 - 210,
        110,
        210,
        60
    });
    Ribbon->setPlaceholderText("Ribbon's alphabet");
    Head->setPlaceholderText("Head's alphabet");
    Ribbon->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    Head->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    connect(Ribbon, &QLineEdit::returnPressed, [Head](){
        Head->setFocus();
    });
    connect(Head, &QLineEdit::returnPressed, [this](){
        focusWidget()->clearFocus();
    });
    objects["RibbonInput"] = Ribbon;
    objects["HeadInput"] = Head;
    const auto SetAlph = new QPushButton(this->central);
    SetAlph->setStyleSheet(
            "QPushButton {"
            "border-radius: 20px;"
            "background-color:rgba(0, 0, 0, 70);"
            "color:rgb(255, 255, 255);"
            "outline: none;"
            "font: 14pt \"CozetteVector\";"
            "}"
            "QPushButton:hover {"
            "border-radius: 20px;"
            "background-color:rgba(0, 0, 0, 100);"
            "color:rgb(255, 255, 255);"
            "outline: none;"
            "font: 12pt \"CozetteVector\";"
            "}"
    );

    SetAlph->setGeometry({
        static_cast<int>(
            (Head->pos().x() + 105 - Ribbon->pos().x()) / 2),
        110 - 15,
        210,
        80
    });

    SetAlph->setText("Set Alphabets!");

    connect(SetAlph, &QPushButton::pressed,
        this, &Window::Run);

    objects["SetAlph"] = SetAlph;
    objects["SetAlph"]->show();
    objects["RibbonInput"]->show();
    objects["HeadInput"]->show();
}

void Window::Run() {
    objects["SetAlph"]->hide();
    objects["RibbonInput"]->hide();
    objects["HeadInput"]->hide();
    if (objects["Table"] == nullptr) {
        objects["Table"] = new TableWidget(central);
        GenerateButtons();
    }
    else {
        ;
    }
    objects["SetStr"]->show();
    objects["Reset"]->show();
    objects["Add"]->show();
    objects["Rm"]->show();
    objects["Table"]->show();
    objects["play"]->show();
    objects["pause"]->show();
    objects["step"]->show();
    objects["resetA"]->show();
    objects["inc"]->show();
    objects["dec"]->show();
    App->show();
}

/*void Window::CreateTable() {
    const auto table = new TableWidget(central);
    objects["Table"] = table;
}*/

/*void Window::UpdateTable() {
    const auto table = dynamic_cast<QTableWidget*>(objects["Table"]);
    const auto Ribbon =
        dynamic_cast<QLineEdit *>(objects["RibbonInput"])->text();
    const auto Head =
        dynamic_cast<QLineEdit *>(objects["HeadInput"])->text();
    for (auto&[fst, snd]: cell) {
        if (fst == "λ") continue;
        if (snd != 0 &&
            std::ranges::count(Head.begin(), Head.end(), fst)
            == 0
            && std::ranges::count(Ribbon.begin(),
                Ribbon.end(), fst)
            == 0) {
            int rowCount = table->rowCount();
            int columnCount = table->columnCount();

            for (int i = 0; i < rowCount; i++) {
                for (int j = 0; j < columnCount; j++) {
                    if (table->cellWidget(i, j)) {
                        delete table->cellWidget(i, j);
                    }
                }
            }
            table->setRowCount(0);
            table->setColumnCount(0);
            cell.clear();
        } else {
            if (snd != 0 &&
            ((std::ranges::count(Head.begin(), Head.end(), fst) != 0
            && snd < cell["λ"]) || (
            std::ranges::count(Ribbon.begin(), Ribbon.end(), fst) != 0
                        && snd > cell["λ"]
            ))) {
                for (int row = 0; row < table->rowCount(); ++row) {
                    const auto item = table->takeItem(row,
                        static_cast<int>(snd));
                    delete item;
                }
                table->removeColumn(static_cast<int>(snd));
                // ReSharper disable once CppUseElementsView
                for (auto&[fst1, snd1]: cell) {
                    if (snd1 > snd) {
                        --snd1;
                    }
                }
                snd = 0;
            }
        }
    }
    {
        table->setRowCount(2);
        table->setColumnCount(2);
        const auto item = new QTableWidgetItem(QString("λ"));
        table->setItem(0, 1, item);
        cell["λ"] = 1;
        table
        ->item(0, 1)
        ->setFlags(table
            ->item(0, 1)->flags()
             & ~Qt::ItemIsEditable);
    }
    for (auto& letter: Ribbon) {
        if (cell[letter] != 0) continue;
        const auto item = new QTableWidgetItem(QString(letter));
        const int column = static_cast<int>(cell["λ"]);
        table->insertColumn(column);
        table
        ->setItem(0, column, item);
        table
        ->item(0, column)
        ->setFlags(table
            ->item(0, column)->flags()
             & ~Qt::ItemIsEditable);
        cell[letter] = column;
        ++cell["λ"];
        for (auto& sl: Head) {
            if (cell[sl] != 0) ++cell[sl];
        }
    }
    for (auto& letter: Head) {
        if (cell[letter] != 0) continue;
        const auto item = new QTableWidgetItem(QString(letter));
        const int column = static_cast<int>(cell["λ"] + 1);
        table->insertColumn(column);
        table
        ->setItem(0, column, item);
        table
        ->item(0, column)
        ->setFlags(table
            ->item(0, column)->flags()
             & ~Qt::ItemIsEditable);
        for (auto& sl: Head) {
            if (cell[sl] >= column) ++cell[sl];
        }
        cell[letter] = column;
    }
}*/

/*void Window::GenerateTable() {
    const auto table = dynamic_cast<QTableWidget*>(objects["Table"]);
    const auto Ribbon =
        dynamic_cast<QLineEdit *>(objects["RibbonInput"])->text();
    const auto Head =
        dynamic_cast<QLineEdit *>(objects["HeadInput"])->text();
    for (auto& letter: Ribbon) {
        if (cell[letter] != 0) continue;
        const auto item = new QTableWidgetItem(QString(letter));
        table->insertColumn(table->columnCount());
        table
        ->setItem(0, table->columnCount() - 1, item);
        table
        ->item(0, table->columnCount() - 1)
        ->setFlags(table
            ->item(0, table->columnCount() - 1)->flags()
             & ~Qt::ItemIsEditable);
        cell[letter] = table->columnCount() - 1;
    }

    {
        const auto item = new QTableWidgetItem(QString("λ"));
        table->insertColumn(table->columnCount());
        table
        ->setItem(0, table->columnCount() - 1, item);
        table
        ->item(0, table->columnCount() - 1)
        ->setFlags(table
            ->item(0, table->columnCount() - 1)->flags()
             & ~Qt::ItemIsEditable);
        cell["λ"] = table->columnCount() - 1;
    }

    for (auto& letter: Head) {
        if (cell[letter] != 0) continue;
        const auto item = new QTableWidgetItem(QString(letter));
        table->insertColumn(table->columnCount());
        table
        ->setItem(0, table->columnCount() - 1, item);
        table
        ->item(0, table->columnCount() - 1)
        ->setFlags(table
            ->item(0, table->columnCount() - 1)->flags()
             & ~Qt::ItemIsEditable);
        cell[letter] = table->columnCount() - 1;
    }
}
*/

void Window::Reset() {
    objects["play"]->hide();
    objects["pause"]->hide();
    objects["step"]->hide();
    objects["resetA"]->hide();
    objects["inc"]->hide();
    objects["dec"]->hide();
    objects["Table"]->hide();
    objects["Rm"]->hide();
    objects["Reset"]->hide();
    objects["Add"]->hide();
    objects["SetStr"]->hide();
    objects["RibbonInput"]->show();
    objects["HeadInput"]->show();
    objects["SetAlph"]->show();
    App->hide();
}

void Window::GenerateButtons() {
        const auto add = new QPushButton(central);
        add->setText("+");
        objects["Add"] = add;
        add->setGeometry(QRect({530, 20, 60, 60}));
        add->setStyleSheet("QPushButton {"
                     "background-color:rgba(0, 0, 0, 80);"
                     "color:white;"
                     "border-radius: 10px;"
                     "font: 14pt \"CozetteVector\";"
                     "}"
                     "QPushButton:hover {"
                     "background-color:rgba(0, 0, 0, 100);"
                     "color:white;"
                     "border-radius: 10px;"
                     "font: 10pt \"CozetteVector\";"
                     "}"
                     );
        connect(add, &QPushButton::pressed,
            dynamic_cast<TableWidget*>(objects["Table"]),
            &TableWidget::addState
        );
        const auto rm = new QPushButton(central);
        objects["Rm"] = rm;
        rm->setText("-");
        rm->setGeometry(QRect({610, 20, 60, 60}));
        rm->setStyleSheet("QPushButton {"
                     "background-color:rgba(0, 0, 0, 80);"
                     "color:white;"
                     "border-radius: 10px;"
                     "font: 14pt \"CozetteVector\";"
                     "}"
                     "QPushButton:hover {"
                     "background-color:rgba(0, 0, 0, 100);"
                     "color:white;"
                     "border-radius: 10px;"
                     "font: 10pt \"CozetteVector\";"
                     "}"

                           );
        connect(rm, &QPushButton::pressed,
            dynamic_cast<TableWidget*>(objects["Table"]),
            &TableWidget::removeState
        );
        const auto reset = new QPushButton(central);
        objects["Reset"] = reset;
        reset->setText("Reset Alphabets!");
        reset->setGeometry(QRect({530, 100, 140, 60}));
        reset->setStyleSheet("QPushButton {"
                     "background-color:rgba(0, 0, 0, 80);"
                     "color:white;"
                     "border-radius: 10px;"
                     "font: 13pt \"CozetteVector\";"
                     "}"
                     "QPushButton:hover {"
                     "background-color:rgba(0, 0, 0, 100);"
                     "color:white;"
                     "border-radius: 10px;"
                     "font: 11pt \"CozetteVector\";"
                     "}"

                           );
        connect(reset, &QPushButton::pressed, [this]() {
            dynamic_cast<QTableWidget*>(objects["Table"])->hide();
            Reset();
        });
        const auto SetStr = new QLineEdit(this->central);
        SetStr->setStyleSheet(
            "QLineEdit {"
            "border-radius: 15px;"
            "background-color:rgb(255, 255, 255);"
            "color:rgb(0, 0, 0);"
            "font: 14pt \"CozetteVector\";"
            "}"
        );
        SetStr->setGeometry({
            1024 - 50 - 210,
            240,
            210,
            60
        });
        SetStr->setPlaceholderText("Set string!");
        SetStr->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        objects["SetStr"] = SetStr;
        connect(SetStr, &QLineEdit::textChanged, [this]() {
            objects["SetStr"]->setStyleSheet(
                    "QLineEdit {"
                    "border-radius: 15px;"
                    "background-color:rgb(255, 255, 255);"
                    "color:rgb(0, 0, 0);"
                    "font: 14pt \"CozetteVector\";"
                    "}");
            const auto Ribbon =
                    dynamic_cast<QLineEdit*>(objects["RibbonInput"])->text();
            for (const auto& letter:
                dynamic_cast<QLineEdit*>(objects["SetStr"]) ->text()) {
                if (!Ribbon.contains(letter)) {
                    objects["SetStr"]->setStyleSheet(
                    "QLineEdit {"
                    "border-radius: 15px;"
                    "background-color:rgb(255, 255, 255);"
                    "color:rgb(255, 0, 0);"
                    "font: 14pt \"CozetteVector\";"
                    "}"
                    );
                    return;
                }
            }
        });
        connect(SetStr, &QLineEdit::returnPressed, [this]() {
            if (objects["SetStr"]->styleSheet() == ("QLineEdit {"
                    "border-radius: 15px;"
                    "background-color:rgb(255, 255, 255);"
                    "color:rgb(0, 0, 0);"
                    "font: 14pt \"CozetteVector\";"
                    "}")) {
                App->upd(dynamic_cast<QLineEdit*>(objects["SetStr"])->text());
            }
        });
        const auto start = new QPushButton(central);
        const auto step = new QPushButton(central);
        const auto pause = new QPushButton(central);
        const auto resetA = new QPushButton(central);
        start->setStyleSheet(add->styleSheet());
        step->setStyleSheet(start->styleSheet());
        pause->setStyleSheet(step->styleSheet());
        resetA->setStyleSheet(pause->styleSheet());
        start->setText("▶");
        start->setGeometry({
            1024 - 50 - 210,
            20,
            60,
            60
        });
        objects["play"] = start;
        pause->setText("⏸");
        pause->setGeometry({
            1024 - 50 - 210 + 80,
            20,
            60,
            60
        });
        objects["pause"] = pause;
        step->setText("⏯");
        step->setGeometry({
            1024 - 50 - 210,
            20 + 80,
            60,
            60
        });
        objects["step"] = step;
        resetA->setText("⏹");
        resetA->setGeometry({
            1024 - 50 - 210 + 80,
            20 + 80,
            60,
            60
        });
        QObject::connect(step, &QPushButton::pressed, [this]() {
            // const int row = App->state + 1;
            // const int column = cell[dynamic_cast<QLabel*>(App->Ribbon->cellWidget(0, static_cast<int>(App->smb))
            // ->children()[0])
            // ->text()];
            // const auto table = dynamic_cast<TableWidget*>(objects["Table"]);
            // App->step(table->command());
        });
        objects["resetA"] = resetA;
        const auto speed_inc = new QPushButton(central);
        const auto speed_dec = new QPushButton(central);
        speed_dec->setText("-");
        speed_dec->setStyleSheet(
                "QPushButton {"
                 "background-color:rgba(0, 0, 0, 80);"
                 "color:white;"
                 "border-top-left-radius: 10px;"
                 "border-bottom-left-radius: 10px;"
                 "font: 13pt \"CozetteVector\";"
                 "}"
                 "QPushButton:hover {"
                 "background-color:rgba(0, 0, 0, 100);"
                 "color:white;"
                 "border-top-left-radius: 10px;"
                 "border-bottom-left-radius: 10px;"
                 "font: 11pt \"CozetteVector\";"
                 "}"
                 );
        speed_dec->setGeometry(QRect({530, 240, 70, 60}));
        speed_inc->setGeometry(QRect({600, 240, 70, 60}));
        speed_inc->setText("+");
        speed_inc->setStyleSheet(
            "QPushButton {"
             "background-color:rgba(0, 0, 0, 80);"
             "color:white;"
             "border-top-right-radius: 10px;"
             "border-bottom-right-radius: 10px;"
             "font: 13pt \"CozetteVector\";"
             "}"
             "QPushButton:hover {"
             "background-color:rgba(0, 0, 0, 100);"
             "color:white;"
             "border-top-right-radius: 10px;"
             "border-bottom-right-radius: 10px;"
             "font: 11pt \"CozetteVector\";"
             "}"
             );
        QObject::connect(speed_dec,
            &QPushButton::pressed, [this]() {
            ++App->speed;
        });
        QObject::connect(speed_inc,
            &QPushButton::pressed, [this]() {
            // --App->speed;
                App->step("aR");
        });
        objects["inc"] = speed_inc;
        objects["dec"] = speed_dec;
}

Window::~Window() {
    delete this;
}