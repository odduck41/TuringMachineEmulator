#include "mario.h"

#include <qcoreapplication.h>

Apparatus::Apparatus (QWidget* parent){
    str = new QString;
    background = new QWidget(parent);
    background->setGeometry({
        0,
        parent->height() - ((512 + 256) / 2 + 32),
        parent->width(),
        (512 + 256) / 2
        }
    );
    background->setStyleSheet(
        "border-image:url(\"/home/lev/programming/animation_test/bg.jpg\");"
        );
    CreateRibbon();
    CreateMario();
}

void Apparatus::CreateRibbon() {
    auto img =
        QImage("/home/lev/programming/animation_test/q.png");
    img = img.scaled(50, 50, Qt::KeepAspectRatio);
    Ribbon = new QTableWidget(background);
    Ribbon->setGeometry({
        (background->width() - 50 * 20) / 2,
        (256 + 128) / 2 + 32,
        50 * 20,
        50
    });
    Ribbon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Ribbon->horizontalHeader()->hide();
    Ribbon->verticalHeader()->hide();
    Ribbon->setStyleSheet("border-image: none;");
    Ribbon->setRowCount(1);
    Ribbon->horizontalHeader()->setDefaultSectionSize(50);
    Ribbon->verticalHeader()->setDefaultSectionSize(50);
    for (int i = 0; i < 500; ++i) {
        Ribbon->insertColumn(Ribbon->columnCount());
        const auto block = new QLabel;
        block->setStyleSheet("");
        block->setPixmap(QPixmap::fromImage(img));
        block->setScaledContents(true);
        block->setStyleSheet("border-image: none;");
        const auto txt = new QLabel("λ", block); // QChar('A' + i)
        txt->setStyleSheet(
                    "font: 30pt \"CozetteVector\";"
                    "color: black;"
                    "margin-left: 7px;"
                    "margin-top: 7px;"
                    "border-image: none;"
                    );
        Ribbon->setCellWidget(0, i, block);
    }
    ActualTablePos = Ribbon->horizontalScrollBar()->value();
}

void Apparatus::CreateMario() {
    Mario = new QWidget(background);
    Mario->setGeometry(
        (background->width() - 50 * 20) / 2,
        (256 + 128) / 2 + 32 + 50 + 22,
        50,
        50
        );
    Mario->setStyleSheet(
        "border-image:"
        "url(/home/lev/programming/animation_test/mario_default.png);"
    );

}

void Apparatus::upd(const QString & s) {
    *str = s;
    int i = 250 + 8;
    Ribbon->horizontalScrollBar()->setValue(250);
    for (int c = 0; c < Ribbon->columnCount(); ++c) {
        dynamic_cast<QLabel*>(Ribbon->cellWidget(0, c)->children()[0])
        ->setText("λ");
    }
    Mario->setGeometry({
        (background->width() - 50 * 20) / 2 + (i - 250) * 50,
        (256 + 128) / 2 + 32 + 50 + 22 ,
        50,
        50
    });
    smb = i;
    for (const auto& letter: *str) {
        // Ribbon->Widgeitem(0, i)->
        dynamic_cast<QLabel*>(Ribbon->cellWidget(0, i)->children()[0])
        ->setText(letter);
        ++i;
    }
}

void Apparatus::GoLeft() {
    if(Mario->pos().x() == (background->width() - 50 * 20) / 2) {
        if (Ribbon->horizontalScrollBar()->value() == 0) {
            return;
        }
        const auto animation
        = new QPropertyAnimation(Mario, "pos");
        animation->setDuration(1000 - speed);
        animation->setStartValue(Mario->pos());
        animation->setEndValue(QPoint({
            (background->width() - 50 * 20) / 2 + 5 * 50,
        (256 + 128) / 2 + 32 + 50 + 22}));
        animation->setEasingCurve(QEasingCurve::InOutExpo);
        const auto sa
        = new QPropertyAnimation(Ribbon, "pos");
        sa->setDuration(1000 - speed);
        sa->setStartValue(Mario->pos());
        sa->setTargetObject(Ribbon->horizontalScrollBar());
        sa->setPropertyName("value");
        sa->setStartValue(Ribbon->horizontalScrollBar()->value());
        sa->setEasingCurve(QEasingCurve::InOutExpo);
        sa->setEndValue(std::max(Ribbon->horizontalScrollBar()->value() - 6, 0));
        ActualTablePos = Ribbon->horizontalScrollBar()->value() - 6;
        sa->start();
        animation->start();
        return;
    }
    --smb;
    const auto animation =
        new QPropertyAnimation(Mario, "pos");
    animation->setDuration(300 - speed);
    animation->setStartValue(Mario->pos());
    animation->setEndValue(Mario->pos() - QPoint(50, 0));
    Mario->setStyleSheet(
        "border-image: "
        "url(/home/lev/programming/animation_test/mario_run1_r.png);");
    const auto timer = new QTimer;
    timer->setInterval((300 - speed) / 6);
    QObject::connect(timer, &QTimer::timeout, [this](){
        if (Mario->styleSheet()
            ==
            "border-image: "
            "url(/home/lev/programming/animation_test/mario_run1_r.png);") {
            Mario->setStyleSheet("border-image: "
            "url(/home/lev/programming/animation_test/mario_run2_r.png);");
        } else if (Mario->styleSheet()
            == "border-image: "
               "url(/home/lev/programming/animation_test/mario_run2_r.png);") {
            Mario->setStyleSheet(
                "border-image: "
                "url(/home/lev/programming/animation_test/mario_run3_r.png);");
        } else if (Mario->styleSheet()
            == "border-image: "
               "url(/home/lev/programming/animation_test/mario_run3_r.png);") {
            Mario->setStyleSheet(
                "border-image: "
                "url(/home/lev/programming/animation_test/mario_run1_r.png);");
        }
    });
    timer->start();
    QObject::connect(animation,
        &QPropertyAnimation::finished, [this, timer](){
        Mario->setStyleSheet("border-image: "
            "url(/home/lev/programming/animation_test/mario_default_r.png);");
        timer->stop();
        delete timer;
    });
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void Apparatus::GoRight() {
    if(Mario->pos().x() == 962) {
        const auto animation
        = new QPropertyAnimation(Mario, "pos");
        animation->setDuration(1000 - speed);
        animation->setStartValue(Mario->pos());
        animation->setEndValue(QPoint({
            (background->width() - (background->width() - 20*50) / 2 - 6 * 50),
        (256 + 128) / 2 + 32 + 50 + 22}));
        animation->setEasingCurve(QEasingCurve::InOutExpo);
        const auto sa
        = new QPropertyAnimation(Ribbon, "pos");
        sa->setDuration(1000 - speed);
        sa->setStartValue(Mario->pos());
        sa->setTargetObject(Ribbon->horizontalScrollBar());
        sa->setPropertyName("value");
        sa->setStartValue(Ribbon->horizontalScrollBar()->value());
        sa->setEasingCurve(QEasingCurve::InOutExpo);
        sa->setEndValue(Ribbon->horizontalScrollBar()->value() + 6);
        ActualTablePos = Ribbon->horizontalScrollBar()->value() + 6;
        sa->start();
        animation->start();
        return;
    }
    ++smb;
    const auto animation =
        new QPropertyAnimation(Mario, "pos");
    animation->setDuration(300 - speed);
    animation->setStartValue(Mario->pos());
    animation->setEndValue(Mario->pos() + QPoint(50, 0));
    Mario->setStyleSheet(
        "border-image: "
        "url(/home/lev/programming/animation_test/mario_run1.png);");
    const auto timer = new QTimer;
    timer->setInterval((300 - speed) / 6);
    QObject::connect(timer, &QTimer::timeout, [this](){
        if (Mario->styleSheet()
            ==
            "border-image: "
            "url(/home/lev/programming/animation_test/mario_run1.png);") {
            Mario->setStyleSheet("border-image: "
            "url(/home/lev/programming/animation_test/mario_run2.png);");
        } else if (Mario->styleSheet()
            == "border-image: "
               "url(/home/lev/programming/animation_test/mario_run2.png);") {
            Mario->setStyleSheet(
                "border-image: "
                "url(/home/lev/programming/animation_test/mario_run3.png);");
        } else if (Mario->styleSheet()
            == "border-image: "
               "url(/home/lev/programming/animation_test/mario_run3.png);") {
            Mario->setStyleSheet(
                "border-image: "
                "url(/home/lev/programming/animation_test/mario_run1.png);");
        }
    });
    timer->start();
    QObject::connect(animation,
        &QPropertyAnimation::finished, [this, timer](){
        Mario->setStyleSheet("border-image: "
            "url(/home/lev/programming/animation_test/mario_default.png);");
        timer->stop();
        delete timer;
    });
    animation->start(QPropertyAnimation::DeleteWhenStopped);

}

void Apparatus::JumpLeft(bool flag) {
    const auto animation =
        new QPropertyAnimation(Mario, "pos");
    animation->setStartValue(Mario->pos());
    animation->setEndValue(Mario->pos() - QPoint(0, 35));
    Mario->setStyleSheet("border-image: "
                    "url(/home/lev/programming/animation_test/mario_jump_r.png);");
    QObject::connect(animation, &QPropertyAnimation::finished,
        [this, flag](){
        const auto animatio_ =
            new QPropertyAnimation(Mario, "pos");
        animatio_->setStartValue(Mario->pos());
        animatio_->setEndValue(Mario->pos() + QPoint(0, 35));
        QObject::connect(animatio_, &QPropertyAnimation::finished, [=](){
            Mario->setStyleSheet("border-image:"
                "url(/home/lev/programming/animation_test/mario_default_r.png);");
            if (flag) {
                GoLeft();
            }
        });
        animatio_->start(QPropertyAnimation::DeleteWhenStopped);
    });
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void Apparatus::JumpRight(bool flag) {
    const auto animation =
        new QPropertyAnimation(Mario, "pos");
    animation->setStartValue(Mario->pos());
    animation->setEndValue(Mario->pos() - QPoint(0, 35));
    Mario->setStyleSheet("border-image: "
                    "url(/home/lev/programming/animation_test/mario_jump.png);");
    QObject::connect(animation, &QPropertyAnimation::finished,
        [this, flag]() {
            const auto animatio_ =
                new QPropertyAnimation(Mario, "pos");
            animatio_->setStartValue(Mario->pos());
            animatio_->setEndValue(Mario->pos() + QPoint(0, 35));
            QObject::connect(animatio_, &QPropertyAnimation::finished, [=](){
                Mario->setStyleSheet("border-image:"
                    "url(/home/lev/programming/animation_test/mario_default.png);");
                if (flag) {
                    GoRight();
                }
            });
            animatio_->start(QPropertyAnimation::DeleteWhenStopped);

        });
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void Apparatus::step(const QString& command) {
    if (command == "!") {
        return;
    }
    if (command.size() == 1) {
        if (command == "L") {
            GoLeft();
        } else if (command == "R") {
            GoRight();
        } else {
            state = command.toInt();
        }
    } else if (command.size() == 2) {
        setSmb(command[0]);
        if (command[1] == 'L') {
            JumpLeft(true);
        } else if (command[1] == 'R') {
            JumpRight();
            GoRight();
        } else {
            state = QString(command[1]).toInt();
        }
    } else {
        setSmb(command[0]);
        if (command[1] == 'L') {
            GoLeft();
        } else {
            GoRight();
        }
        state = QString(command[1]).toInt();
    }
}

void Apparatus::setSmb(const QChar& t) const {
    dynamic_cast<QLabel*>(Ribbon->cellWidget(0, static_cast<int>(smb))
    ->children()[0])
    ->setText(t);
}
