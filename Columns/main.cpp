#include "Juego.h"


using namespace std;



int main()
{
    //cout << "LLEGO1" << endl;
    Juego* juego = Juego::getInstance();
    juego->crearVentana();
    juego->bucleJuego();

    return 0;
}
