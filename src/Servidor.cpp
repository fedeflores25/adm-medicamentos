#include <iostream>
#include <winsock2.h>

using namespace std;

class Servidor
{
public:
    //Atributos
    WSADATA wsaData;
    SOCKET servidor, cliente;//creo sockets servidor y cliente
    SOCKADDR_IN servidorDireccion, clienteDireccion; //obtengo direccion para el servidor y el cliente. SOCKADDR significa Socket Address

    char buffer[1024];
    int puerto = 5555;

    Servidor()
    {
        //CREACION DEL SERVIDOR
        WSAStartup(MAKEWORD(2,0),&wsaData);// Me parece que es para compatibilizar con la lib winsock2.h

        servidor = socket(AF_INET,SOCK_STREAM,0);//estos argumentos que le paso quieren decir que va a usar el protocolo tcp/ip


        //Le digo al servidor que escuche en cualquiera de las interfaces del sistema operativo
        servidorDireccion.sin_addr.s_addr = INADDR_ANY;
        servidorDireccion.sin_family = AF_INET;
        servidorDireccion.sin_port = htons(puerto);//le asigno el numero de puerto al servidor

        //Ahora tengo que asociar A (direccion ip y el puerto del servidor)
        //con B (el Socket que creamos con el protocolo que voy a usar TCP/IP)


        //cuando se cierra mal el servidor se puede producir un problema que cuelga el ip o el puerto
        //setea un flag que le dice al sist operativo para que le permita reutilizar la conexion
        int activado = 1;
        setsockopt(servidor, SQL_SOCKET, SO_REUSEADDR,&activado, sizeof(activado));

        //la funcion bind pide estructura (servidor, SOCKADDR, tama�o) y como usamos SOCKADDR _IN que es mas especifica la vamos a castear
        //la funcion bind puede fallar(si otro proceso ya esta usando el mismo puerto), por eso hay que validarla
        if (bind(servidor,(SOCKADDR *)&servidorDireccion,sizeof(servidorDireccion))!= 0)//asigna ip y numero de puerto con el socket servidor
        {
            perror("Fallo el bind");
            return 1;
        }
        listen(servidor, 5); //asigna el socket como servidor y maximo de conexiones acumulables

        //ESCUCHAR CONEXIONES Y ACEPTAR*****************************

        cout<<"Escuchando conexiones entrantes..."<<endl;
        int clienteDireccionLongitud = sizeof(clienteDireccion);

        //aceptar conexion
        if(accept(servidor,(SOCKADDR *)&clienteDireccion,&clienteDireccionLongitud) != INVALID_SOCKET)
        {
            cout<<"Cliente conectado"<<endl;
        }
    }//fin constructor del servidor

    //METODOS
    void recibir()
    {
        recv(cliente, buffer,sizeof(buffer),0);
        cout<<"El cliente dice: "<<buffer<<endl;
        memset(buffer,0,sizeof(buffer));
    }
    void enviar()
    {
        cout<<"Escribe el mensaje a enviar: "<<endl;
        cin>>this->buffer;
        send(servidor,buffer,sizeof(buffer),0);
        memset(buffer, 0, sizeof(buffer));
    }
    void cerrarSocket()
    {
        closesocket(cliente);
        cout<<"Cliente desconectado, socket cerrado."<<endl;
    }


};//fin clase servidor
