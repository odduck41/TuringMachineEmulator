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
    double speed = 1;
    void step();
signals:
    void finish();
private:
    // void JumpLeft();
    // void JumpRight();
    // void GoLeft();
    void GoRight();
    int TablePos;
    int TableScrollBar;
    TableWidget* table{};
    QTableWidget* Ribbon{};
    QWidget* Mario{};
    Window* window{};
};
