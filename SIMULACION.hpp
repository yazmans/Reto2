//
//  SIMULACION.hpp
//  
//
//  Created by Angel Luna on 22/04/2025.
//

#ifndef SIMULACION_hpp
#define SIMULACION_hpp
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

class gota { // una clase que almacena todos los calculos y datos disponibles para cada gota a ser analizada
private:
    double radius, mass;
    double density; //definir la densidad PENDIENTE
    double charge;
    //double velocity;
    //double acceleration;
    int n; // cantidad de intervalos para tomar su pocision y movimiento
    float h(); //position, FALTA POR DEFINIR
    //float time(); intervalos de tiemp de caida FALTA POR DEFINIR
    //float velocity();
    //float V_off, V_off; //velocidad terminal con el campo activado y desactivado
public:

    /*double changeAceleration(double gravity, double airDensity,double pressure, double airViscosity, double electricField){
        double b=7.88e-3;
        double F=-4*(M_PI/3)*pow(radius,3)*(density-airDensity)*gravity
        -6*M_PI*airViscosity*radius*velocity/(1+b/(pressure*radius))+
        charge*electricField;
        acceleration=mass*F;
        return acceleration;
    }*/

    //Constructor, getters, setters
    gota() {// constructor
    }

    /*void defdivision(n) {
        delta_t=_delta-t;
    }*/
    
    //metodos para obtener los valores de la gota
    /*int getdivision() {
        return delta_t;
    }*/
    double getrad() {
        return radius;
    }
    double getmass() {
        return mass;
    }
    double getdensity() {
        return density;
    }
    double getcharge(){
        return charge;
    }
    /*float getheight(interval) {
        return height[interval];
    }
    float getvelocity(interval) {
        return velocity[interval];
    }
    float getacceleration(interval) {
        return acceleration[interval];
    }
    float getV_off() {
        return V-off;
    }*/

};


#endif /* SIMULACION_hpp */