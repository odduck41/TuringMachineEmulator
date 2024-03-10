#pragma once
#include <QTableWidgetItem>
#include <QHeaderView>

#include <set>

class TableWidget final : public QTableWidget {
    Q_OBJECT
public:
    explicit TableWidget(QWidget* = nullptr);
    QString command(const QString&, int);
    void addState();
    void removeState();
    void setAlph(const QString&, const QString&);
private:
    std::map<const QString, int> commands;
};
