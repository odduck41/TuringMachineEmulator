#pragma once
#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QLineEdit>
#include <QTableWidget>
#include <QScrollBar>
#include <QThread>
#include <QPushButton>
#include <QString>
#include <QTableWidgetItem>

#include <map>

#include "mario.h"

class Window final : public QMainWindow {
    Q_OBJECT
public:
    explicit Window(QWidget* = nullptr);
    void Load();
    void Run();
    //void CreateTable();
    //void UpdateTable();
    //void GenerateTable();
    void Reset();
    void GenerateButtons();
    ~Window() override;
private:
    QWidget* central = new QWidget(this);
    QPushButton* title = new QPushButton(this);
    std::map<const QString, QWidget*> objects;
    std::map<const QString, int> cell;
    Apparatus* App{};
};