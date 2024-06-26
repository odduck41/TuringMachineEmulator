#pragma once
#include <QLabel>
#include "../include/Window.h"
#include "../include/TableWidget.h"

class Window;
class Apparatus final : public QLabel {
    Q_OBJECT
  public:
    explicit Apparatus(QWidget* = nullptr);
    void CreateRibbon();
    void CreateMario();
    void SetString(const QString&);
    int State = 0;
    int steps = 0;
    void step();
    void run();
    void inc();
    void dec();
    void checker();
    QString rbn{};
  signals:
    void err();
    void finish();
    void p_started();
    void p_finished();
  private:
    bool updated = false;
    double speed = 1;
    void JumpLeft();
    void JumpRight();
    void GoLeft();
    void GoRight();
    int TablePos = 0;
    int TableScrollBar = 0;
    bool contains = false;
    TableWidget* table{};
    QTableWidget* Ribbon{};
    QWidget* Mario{};
    Window* window{};
};
