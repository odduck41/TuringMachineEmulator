#pragma once
// Qt
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>

class Window;

class TableWidget final : public QTableWidget {
    Q_OBJECT
  public:
    explicit TableWidget(QWidget* = nullptr);
    [[nodiscard]] QString getCommand(const QChar&, int);
    void addState();
    void removeState();
    void updateAlph(const QString&, const QString&);
    void clearPaint() const;
    void check();
    TableWidget& operator=(const TableWidget&);
    QString style{};
  signals:
    void correct();
    void incorrect();
    void symbol();
    void not_found();
  private:
    [[nodiscard]] int getColumn(const QString&) const;
    void paint(QTableWidgetItem*);
    QWidget* prnt;
    QPushButton* btn{};
};
