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
    [[nodiscard]] QString getCommand(const QChar&, int) const;
    void addState();
    void removeState();
    void updateAlph(const QString&, const QString&);
    void clearPaint() const;
    TableWidget& operator=(const TableWidget&);

    QString style{};
  private:
    [[nodiscard]] int getColumn(const QString&) const;
    static void paint(QTableWidgetItem*);
    QWidget* prnt;
    QPushButton* btn{};
};
