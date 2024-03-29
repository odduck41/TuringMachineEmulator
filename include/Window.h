#pragma once
// Qt
#include <QMainWindow>
#include <QPushButton>
#include <QFile>

// std
#include <map>

// other
#include "../include/TableWidget.h"
#include "../include/Apparatus.h"

class Apparatus;
class Window final : public QMainWindow {
    Q_OBJECT
public:
    explicit Window(QWidget* = nullptr);
    void loadStyles(const QString& = "../assets/styles.qss");
    void IOG();// IOG == Initial Object Generation
    void FirstScreen();
    void SecondScreen();
    TableWidget* table{};
private:
    void ShowFirstScreen();
    void ShowSecondScreen();
    void HideFirstScreen();
    void HideSecondScreen();
    std::map<const QString, QWidget*> objects{};
    QPushButton* title = new QPushButton(this);
    QWidget* central = new QWidget(this);
    QString StyleSheet{};
    Apparatus* apparatus{};
};