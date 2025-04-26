//Esto solo es una prueba 

#include <iostream>
#include "Gota.h"
#include <vector>
#include <random>
#include <ctime>
#include "SIMULACION.hpp"
using namespace std;

int main(){
    int numGotas=1;
    double electricField=317.8; //317.8 kV m^-1
    double airDensity=1.2; //kg m^-3
    double gravity=9.803; //kg s^-2
    double airViscosity=1.820e-5; //kg m^–1 s^–1
    double b=7.88e-3; //Pa m
    double pressure=100.82; //kPa
    int steps = 0;
    int maxSteps = 100;

    gota* gotas[numGotas];
    for(int i=0;i<numGotas;i++){

        double velocity=0;
        double position=0;
        double acceleration=0;

        double velocityE=0;
        double positionE=0;
        double accelerationE=0;

        double time=0;
        double timeE=0;
        double dt=0.01;

        double fg=-4*(M_PI/3)*pow(gotas[i]->getrad(),3)*(gotas[i]->getdensity()-airDensity)*gravity;
        double fE=electricField*gotas[i]->getcharge();

        while(steps < maxSteps){
            double fA=-6*M_PI*airViscosity*gotas[i]->getrad()*velocity/(1+b/(pressure*gotas[i]->getrad()));
            acceleration=(fg+fA)/gotas[i]->getmass();
            velocity=velocity+acceleration*dt;
            position=position+velocity*dt;
            time=time+dt;
            steps++;
        }

        steps=0; 

        while(steps < maxSteps){
            double fA=-6*M_PI*airViscosity*gotas[i]->getrad()*velocity/(1+b/(pressure*gotas[i]->getrad()));
            accelerationE=(fg+fA+fE)/gotas[i]->getmass();
            velocityE=velocityE+accelerationE*dt;
            positionE=positionE+velocityE*dt;
            timeE=timeE+dt;
            steps++;
        }
        cout<<"Gota "<<i<<endl;
        cout<<"Velocidad final sin campo: "<<velocity<<endl;
        cout<<"Velocidad final con campo: "<<velocityE<<endl;
        cout<<endl;
    }
}
