#include <QCoreApplication>
#include <iostream>
#include <math.h>

#define SDL_MAIN_HANDLED
#include <gameLib.h>


using namespace std;




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    init();


    return a.exec();
}
