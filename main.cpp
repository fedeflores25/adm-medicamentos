#include <iostream>
#include "src/Cliente.cpp"

using namespace std;

int main()
{
   Cliente *cliente = new Cliente();
    cout<<"enviando"<<endl;

    while(true)
    {
        cliente->enviar();

    }
    return 0;
}
