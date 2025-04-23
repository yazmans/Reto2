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
    int n; // cantidad de intervalos para tomar su pocicion y movimiento
    float height; //position, FALTA POR DEFINIR
    float time; //intervalos de tiemp de caida FALTA POR DEFINIR
    float velocity;
    float aceleration;
    float V_off, V_on; //velocidad terminal con el campo activado y desactivado
public:
    gota() {// constructor
        
    }
    void defdivision(int _n) {
        n=_n;
    }
    
    //metodos para obtener los valores de la gota
    //al parecer no se pueden usar no-estaticos en los arreglos de las propiedades, por lo que esta variable [n] es inutil, por ahora, pero hay que ver como se puede modificar el tamaño del arreglo para dejarlo a discrecion del usuario.
    int getdivision() {
        return n;
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
    float getheight(int interval) {
        int height[interval];
        return height[interval];
    }
    float getvelocity(int interval) {
        int velocity[interval];
        return velocity[interval];
    }
    float getacceleration(int interval) {
        int acceleration[interval];
        return acceleration[interval];
    }
    float getV_off() {
        return V_off;
    }
    float getV_on() {
        return V_on;
    }
};


#endif /* SIMULACION_hpp */
