#include <iostream>
#include <Clases.h>
#include <vector>
#include <string>
#include <list>
using namespace std;

router *CrearRouter(string Nombre);

int main()
{
    bool continuar = true; int seleccion; red WiFi; vector <router*> routers, red;  string RouterName;
    cout << "[ENRUTADORES Y REDES]" << endl; int Q, P, Coste; router A("");
    while (continuar)
    {

        cout << "\t [Escoga alguna de las siguiente opciones:]" << endl;
        cout << "\t [1]: Crear enrutador" << endl;
        cout << "\t  [2]: Conectar enrutadores" << endl;
        cout << "\t   [3]: Desconectar enrutadores" << endl;
        cout << "\t    [4]: Agregar enrutador a la red" << endl;
        cout << "\t     [5]: Quitar enrutador de la red" << endl;
        cout << "\t      [6]: Coste envio de paquetes" << endl;
        cout << "\t       [7]: Camino mas eficiente" << endl;
        cout << "\t        [8]: tabla de router" << endl;
        cout << "\t         [9]: Actualizar" << endl;
        cout << "\t          [10]: Salir" << endl;

        cin >> seleccion;

        switch (seleccion)
        {

        case 1:
            cout << "\t [Ingresa el I_D de tu enrutador]:" << endl; cin >> RouterName;
            routers.push_back(CrearRouter(RouterName));
            break;
        case 2:
            if (routers.empty()){
                cout << "[No hay enrutadores disponibles]" << endl;
                break;
            }
            for (int C = 0; C < routers.size(); C++)
            {
                cout << "\t\t [" << C << "]" << " " << routers[C]->getI_D() << endl;
            }
            cout << "\t [Elija los enrutadores a conectar]:" << endl;
            cin >> Q;
            cin >> P;
            cout << "\t [Ingrese el coste]:" << endl; cin >> Coste;
            routers[Q]->Conect(*routers[P], Coste);
            break;
        case 3:
            if (routers.empty()){
                cout << "[No hay enrutadores disponibles]" << endl;
                break;
            }
            for (int C = 0; C < routers.size(); C++)
            {
                cout << "\t\t [" << C << "]" << " " << routers[C]->getI_D() << endl;
            }
            cout << "\t [Elija los enrutadores a desconectar]:" << endl;
            cin >> Q;
            cin >> P;
            routers[Q]->Disconect(*routers[P]);
            break;
        case 4:
            if (routers.empty()){
                cout << "[No hay enrutadores disponibles]" << endl;
                break;
            }
            for (int C = 0; C < routers.size(); C++)
            {
                cout << "\t\t [" << C << "]" << " " << routers[C]->getI_D() << endl;
            }
            cout << "\t [Elija el enrutador para conectar a la red]:" << endl;
            cin >> Q;
            red.push_back(routers[Q]);
            WiFi.Join(routers[Q]);
            break;
        case 5:
            if (red.empty()){
                cout << "[No hay enrutadores disponibles]" << endl;
                break;
            }
            for (int C = 0; C < red.size(); C++)
            {
                cout << "\t\t [" << C << "]" << " " << red[C]->getI_D() << endl;
            }
            cout << "\t [Elija el enrutador para desconectar de la red]:" << endl;
            cin >> Q;
            WiFi.Leave(red[Q]);
            red.erase(red.begin() + Q);

            break;
        case 6:
            cout << "\t [Los costes de envio de paquetes se muestran en esta tabla]:" << endl;
            WiFi.Show();
            break;
        case 7:
            cout << "\t [A continuacion se mostraran los enrutadores los cuales estan en la red]:" << endl;
            if (red.empty()){
                cout << "[No hay enrutadores disponibles]" << endl;
                break;
            }
            for (int C = 0; C < red.size(); C++)
            {
                cout << "\t\t [" << C << "]" << " " << red[C]->getI_D() << endl;
            }
            cout << "\t [Elija los enrutadores para conocer su camino mas eficiente]:" << endl;
            cin >> Q;
            cin >> P;
            cout << WiFi.Path(red[Q], red[P]);
            break;
        case 8:
            if (routers.empty()){
                cout << "[No hay enrutadores disponibles]" << endl;
                break;
            }
            for (int C = 0; C < routers.size(); C++)
            {
                cout << "\t\t [" << C << "]" << " " << routers[C]->getI_D() << endl;
            }
            cout << "\t [Elija el enrutador]:" << endl;
            cin >> Q;
            routers[Q]->Show();
            break;
        case 9:
            WiFi.Refresh();
            break;
        case 10:
            continuar = false;
            break;
        default:
            cout << "\t [Elija un opcion valida]" << endl;
            break;
        }


    }

}

router *CrearRouter(string Nombre)
{
    return new router(Nombre);
}
