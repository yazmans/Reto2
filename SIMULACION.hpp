//
//  SIMULACION.hpp
//  
//
//  Created by Angel Luna on 22/04/2025.
//

#ifndef SIMULACION_hpp
#define SIMULACION_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class gota { // una clase que almacena todos los calculos y datos disponibles para cada gota a ser analizada
private:
    float radius, mass;
    float density=0; //definir la densidad PENDIENTE
    double charge;
    int n // cantidad de intervalos para tomar su pocicion y movimiento
    float h[n]; //position, FALTA POR DEFINIR
    float time[n]; //intervalos de tiemp de caida FALTA POR DEFINIR
    float velocity[n];
    float aceleration[n];
    float V_off, V_off; //velocidad terminal con el campo activado y desactivado
public:
    gota() {// constructor
        
    }
    void defdivision(n) {
        delta_t=_delta-t;
    }
    
    //metodos para obtener los valores de la gota
    int getdivision() {
        return delta_t;
    }
    float getrad() {
        return radius;
    }
    float getmass() {
        return mass;
    }
    float getrho() {
        return density;
    }
    float getheight(interval) {
        return height[interval];
    }
    float getvelocity(interval) {
        return velocity[interval];
    }
    float getacceleration(interval) {
        return acceleration[interval];
    }
    float getV_off() {
        return V-offf;
    }
};


#endif /* SIMULACION_hpp */
