#include "../include/Window.h"
#include <QLineEdit>
#include <QTimer>

Window::Window(QWidget* parent) : QMainWindow(parent) {
    this->loadStyles();

    this->IOG();

    this->setGeometry({
        0, 0, 1024, 768
    });
    this->setStyleSheet(this->StyleSheet);
    this->setWindowFlags(Qt::FramelessWindowHint);

    title->setText("Turing Machine");
    title->setGeometry({
        6, 6, 1012, 30
    });
    title->setStyleSheet(this->StyleSheet);
    connect(title, &QPushButton::pressed,
        this, &QMainWindow::close);

    central->setGeometry({0, 42,
        this->width(), this->height() - 42});
    central->setFocusPolicy(Qt::ClickFocus);

    this->ShowFirstScreen();
    this->HideSecondScreen();
}

void Window::loadStyles(const QString& file_name){
    QFile file(file_name);
    file.open(QIODevice::ReadWrite);
    this->StyleSheet = QTextStream(&file).readAll();
    file.close();
}

void Window::IOG() {
    this->FirstScreen();
    this->SecondScreen();
}

void Window::FirstScreen() {
    const auto Ribbon = new QLineEdit(this->central);
    Ribbon->setStyleSheet(this->StyleSheet);
    Ribbon->setGeometry({
        50, 110, 210, 60
    });
    Ribbon->setPlaceholderText("Ribbon's alphabet");
    Ribbon->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    objects["RibbonInput"] = Ribbon;


    const auto Head = new QLineEdit(this->central);
    Head->setStyleSheet(this->StyleSheet);
    Head->setGeometry({
        764, 110, 210, 60
    });
    Head->setPlaceholderText("Head's alphabet");
    Head->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    objects["HeadInput"] = Head;


    const auto SetAlph = new QPushButton(this->central);
    SetAlph->setStyleSheet(this->StyleSheet);
    SetAlph->setGeometry({
        410, 95, 210, 80
    });
    SetAlph->setText("Set Alphabets!");
    objects["SetAlph"] = SetAlph;

    connect(Ribbon, &QLineEdit::returnPressed, [Head]{
            Head->setFocus();
        }
    );
    connect(Head, &QLineEdit::returnPressed, [SetAlph, this]{
            SetAlph->click();
            focusWidget()->clearFocus();
        }
    );
    connect(SetAlph, &QPushButton::pressed, [this, Ribbon, Head]{
            HideFirstScreen();
            table->updateAlph(Ribbon->text(), Head->text());
            ShowSecondScreen();
        }
    );
}

void Window::ShowFirstScreen() {
    objects["SetAlph"]->show();
    objects["RibbonInput"]->show();
    objects["HeadInput"]->show();
}

void Window::HideFirstScreen() {
    objects["SetAlph"]->hide();
    objects["RibbonInput"]->hide();
    objects["HeadInput"]->hide();
}

void Window::SecondScreen() {
    table = new TableWidget(central);
    apparatus = new Apparatus(central);
    apparatus->SetString("");
    table->style = this->StyleSheet;

    auto *first = new QLabel(central), *second = new QLabel(central);
    auto *third = new QLabel(central);
    first->setText("Table hasn't got !, so program never finish");
    first->setGeometry({
       530, 190, 160, 60
    });
    first->setWordWrap(true);
    first->setObjectName("Err");
    first->setStyleSheet(central->styleSheet());
    connect(table, &TableWidget::correct, first, &QLabel::hide);
    connect(table, &TableWidget::incorrect, first, &QLabel::show);
    objects["firstErr"] = first;

    second->setText("Cell is empty");
    second->setGeometry({
           530, 190, 160, 60
    });
    second->setWordWrap(true);
    second->setObjectName("Err");
    second->setStyleSheet(central->styleSheet());
    connect(table, &TableWidget::not_found, second, &QLabel::show);
    objects["secondErr"] = second;

    const auto reset = new QPushButton(central);
    objects["Reset"] = reset;
    reset->setText("Reset Alphabets!");
    reset->setGeometry({
        530, 90, 160, 60
    });
    reset->setStyleSheet(this->StyleSheet);
    connect(reset, &QPushButton::pressed, [this]{
        HideSecondScreen();
        ShowFirstScreen();
    });

    const auto addState = new QPushButton(central);
    objects["AddState"] = addState;
    addState->setText("+");
    addState->setGeometry({
       530, 0, 60, 60
    });
    addState->setStyleSheet(this->StyleSheet);
    connect(addState, &QPushButton::pressed, table, &TableWidget::addState);

    const auto removeState = new QPushButton(central);
    objects["RemoveState"] = removeState;
    removeState->setText("-");
    removeState->setGeometry({
       630, 0, 60, 60
    });
    removeState->setStyleSheet(this->StyleSheet);
    connect(removeState, &QPushButton::pressed, table, &TableWidget::removeState);

    const auto Step = new QPushButton(central);
    objects["Step"] = Step;
    Step->setText("⏯");
    Step->setGeometry({
        750, 0, 60, 60
    });
    Step->setStyleSheet(this->StyleSheet);
    connect(Step, &QPushButton::pressed, [this] {
        objects["secondErr"]->hide();
        if (apparatus->steps == 0) {
            const auto timer = new QTimer;
            connect(timer, &QTimer::timeout, apparatus, &Apparatus::step);
            connect(apparatus, &Apparatus::finish, timer, &QTimer::stop);
            timer->start();
        }
        ++apparatus->steps;
    });

    const auto Pause = new QPushButton(central);
    objects["Pause"] = Pause;
    Pause->setText("⏸");
    Pause->setGeometry({
    950, 0, 60, 60
    });
    Pause->setStyleSheet(this->StyleSheet);

    const auto Run = new QPushButton(central);
    Run->setObjectName("Run");
    objects["Run"] = Run;
    Run->setText("⏵");
    Run->setGeometry({
        850, 0, 60, 60
    });
    Run->setStyleSheet(this->StyleSheet);
    connect(Run, &QPushButton::pressed, [this, Pause]{
        objects["secondErr"]->hide();
        const auto timer = new QTimer;
        connect(timer, &QTimer::timeout, apparatus, &Apparatus::run);

        connect(apparatus, &Apparatus::finish, [this, timer] {
            timer->stop();
            emit apparatus->p_finished();
        });
        connect(Pause, &QPushButton::pressed,  [this, timer] {
           timer->stop();
           emit apparatus->p_finished();
        });
        timer->start();
    });


    const auto SpeedDec = new QPushButton(central);
    objects["SpeedDec"] = SpeedDec;
    SpeedDec->setText("⏪");
    SpeedDec->setGeometry({
        750, 90, 60, 60
    });
    SpeedDec->setStyleSheet(this->StyleSheet);
    connect(SpeedDec, &QPushButton::pressed, apparatus, &Apparatus::dec);

    const auto ResetProgram = new QPushButton(central);
    objects["ResetProgram"] = ResetProgram;
    ResetProgram->setObjectName("Stop");
    ResetProgram->setText("⏹");
    ResetProgram->setGeometry({
        850, 90, 60, 60
    });
    ResetProgram->setStyleSheet(this->StyleSheet);

    const auto SpeedInc = new QPushButton(central);
    objects["SpeedInc"] = SpeedInc;
    SpeedInc->setText("⏩");
    SpeedInc->setGeometry({
        950, 90, 60, 60
    });
    SpeedInc->setStyleSheet(this->StyleSheet);
    connect(SpeedInc, &QPushButton::pressed, apparatus, &Apparatus::inc);

    const auto RibbonStr = new QLineEdit(central);
    objects["RibbonStr"] = RibbonStr;
    RibbonStr->setPlaceholderText("Set a string!");
    RibbonStr->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    RibbonStr->setGeometry({
       750, 190, 260, 60
    });
    connect(RibbonStr, &QLineEdit::textChanged, [this, RibbonStr] {
        RibbonStr->setObjectName("");
        RibbonStr->setStyleSheet(this->StyleSheet);
        for (const auto& letter: RibbonStr->text()) {
            if (!dynamic_cast<QLineEdit*>(this->objects["RibbonInput"])->text().contains(letter)) {
                RibbonStr->setObjectName("Incorrect");
                RibbonStr->setStyleSheet(this->StyleSheet);
                break;
            }
        }
    });

    connect(apparatus, &Apparatus::p_started, [this] {
        objects["Reset"]->setEnabled(false);
        objects["AddState"]->setEnabled(false);
        objects["RemoveState"]->setEnabled(false);
        objects["Step"]->setEnabled(false);
        objects["Run"]->setEnabled(false);
        objects["ResetProgram"]->setEnabled(false);
        objects["RibbonStr"]->setEnabled(false);

    });
    connect(apparatus, &Apparatus::p_finished, [this] {
        objects["Reset"]->setEnabled(true);
        objects["AddState"]->setEnabled(true);
        objects["RemoveState"]->setEnabled(true);
        objects["Step"]->setEnabled(true);
        objects["Run"]->setEnabled(true);
        objects["ResetProgram"]->setEnabled(true);
        objects["RibbonStr"]->setEnabled(true);
    });
    connect(RibbonStr, &QLineEdit::returnPressed, [this, RibbonStr]{
        if (RibbonStr->objectName() == "") apparatus->SetString(RibbonStr->text());
    });
    connect(ResetProgram, &QPushButton::pressed, [second, RibbonStr] {
        second->hide();
        emit RibbonStr->returnPressed();
    });

    connect(table, &TableWidget::correct, [this]{
        objects["Step"]->setEnabled(true);
        objects["Run"]->setEnabled(true);
    });

    connect(table, &TableWidget::incorrect, [this]{
        objects["Step"]->setEnabled(false);
        objects["Run"]->setEnabled(false);
    });
}

void Window::ShowSecondScreen() {
    table->show();
    objects["Reset"]->show();
    objects["AddState"]->show();
    objects["RemoveState"]->show();
    objects["Step"]->show();
    objects["Run"]->show();
    objects["Pause"]->show();
    objects["SpeedDec"]->show();
    objects["ResetProgram"]->show();
    objects["SpeedInc"]->show();
    objects["RibbonStr"]->show();
    apparatus->show();
    table->check();
}

void Window::HideSecondScreen() {
    table->hide();
    objects["Reset"]->hide();
    objects["AddState"]->hide();
    objects["RemoveState"]->hide();
    objects["Step"]->hide();
    objects["Run"]->hide();
    objects["Pause"]->hide();
    objects["SpeedDec"]->hide();
    objects["ResetProgram"]->hide();
    objects["SpeedInc"]->hide();
    objects["RibbonStr"]->hide();
    objects["firstErr"]->hide();
    objects["secondErr"]->hide();
    apparatus->hide();
}
