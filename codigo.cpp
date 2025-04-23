#include <iostream>
#include "SIMULACION.hpp"
using namespace std;

int main(){
    // double g=9.803; estas variables ya han sido definidas en el header, probablemente no se usen.
    //double pOil=919.9;
    //double pAir=1.2;
    cout << "This is an execution test.\n";
    gota gota1;
    cout << gota1.getrad() << "\n";
    cout << gota1.getmass() << "\n";
}
