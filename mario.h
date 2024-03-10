#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QString>
#include <QImage>
#include <QHeaderView>
#include <QScrollBar>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTimer>

class Apparatus {
public:
    Apparatus(QWidget* = nullptr);
    void step(const QString&);
    // void startCircle(map<QString*, map<long long, QString*>>);
    // void stopCircle();
    // void reset();
    int speed = 0;
    void upd(const QString&);
    void show() const{
        background->show();
        Ribbon->show();
        Mario->show();
    }
    void hide() const {
        background->hide();
        Ribbon->hide();
        Mario->hide();
    }
    void setSmb(const QChar&) const;
    int state = 0;
    unsigned long long smb{};
    QTableWidget* Ribbon{};
private:
    void GoLeft();
    void GoRight();
    void JumpLeft(bool = false);
    void JumpRight(bool = false);
    QString* str{};
    void CreateRibbon();
    void CreateMario();
    unsigned long long ActualTablePos{};
    QWidget* background{};
    QWidget* Mario{};
};
