#include <QApplication>
#include "../include/Window.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Window window;
    window.show();

    return QApplication::exec();
}
