#pragma once
#include <QLabel>
#include "../include/Window.h"

class Window;
class Apparatus final : public QLabel {
    Q_OBJECT
public:
    explicit Apparatus(QWidget* = nullptr);
    void CreateRibbon();
    void CreateMario();
    void SetString(const QString&);
    QChar GetChar();
    int state = 0;
private:
    int TablePos;
    QTableWidget* Ribbon{};
    QWidget* Mario{};
    Window* window{};
};
