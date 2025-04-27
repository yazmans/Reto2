//
//  luna.cpp
//  Reto
//
//  Created by Angel Luna on 26/04/2025.
//

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "SIMULACION.hpp"
using namespace std;

int main() {
    int dropletQ=1; //cantidad de gotas a analizar
    gota gotas[dropletQ];
    double deltaT=0.001; //definir el salto de tiempo
    double gravity=9.803;
    double airV= 1.81e-5;
    double airD=1.2;
    double b=7.88e-3;
    double platedistance=16e-3;
    double platevoltage=5e3;
    double electricF=platevoltage/platedistance; //calculo del campo electrico
    double pressure=100.82;
    
    for (int i=0;i<dropletQ;i++) {
        gotas[i].calcstuff(airD,electricF);
        int j=0;
        while (gotas[i].indexacc(j)>1e-5)
        {
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+b/pressure*gotas[i].getrad());
            gotas[i].defdrag(drag);
            double acceleration=(gotas[i].getweight()+drag-gotas[i].getbuoyant())/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            //suferencia: insertar grafica aqui
            j++;
        }
        gotas[i].defV_off((gotas[i].vecvelocity()).back());
    
        
        gotas[i].clearll();
        j=0;
        while (gotas[i].indexacc(j)>1e-5)
        {
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+b/pressure*gotas[i].getrad());
            gotas[i].defdrag(drag);
            double acceleration=(gotas[i].getweight()+drag-gotas[i].getelectricF()-gotas[i].getbuoyant())/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            //sugerencia: insertar ottra grafica aqui
            j++;
        }
        gotas[i].defV_on((gotas[i].vecvelocity()).back());
        //calcular la carga electrica de la particula
       
    }
    cout << gotas[0].getV_off() << "\n";
    double V_off=gotas[0].getV_off();
    cout << gotas[0].getV_on() << "\n";
    double V_on=gotas[0].getV_on();
    double charge=(6*M_PI*airV*(V_off+V_on))/electricF;
    cout << charge << "\n";
}

