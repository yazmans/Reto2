//Esto solo es una prueba 

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "SIMULACION.hpp"
//include <>
#include <cmath>
using namespace std;



int main() {
    gota gota1;
    cout << gota1.getrad() << "\n";
    cout << gota1.indexheight(0) << "\n";
    cout << gota1.getmass() << "\n";
    for (int i=0; i<5; i++) {
        gota1.p_height(i*pow(10,-2));
    }
    cout << gota1.indexheight(3) << "\n";
    vector<double> vectorprueba = gota1.vecheight();
    
    
}

//int main(){
    // double g=9.803; estas variables ya han sido definidas en el header, probablemente no se usen.
    //double pOil=919.9;
    //double pAir=1.2;
    //cout << "This is an execution test.\n";
    //gota gota1;
    //cout << gota1.getrad() << "\n";
    //cout << gota1.getmass() << "\n";
//}
