

#ifndef GOTA_H
#define GOTA_H

#include <stdio.h>
# define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

class gota { // una clase que almacena todos los calculos y datos disponibles para cada gota a ser analizada
private:
    double radius, mass;
    double density; //definir la densidad PENDIENTE
    double charge;
public:
    gota(double radius, double mass, double density, double charge) { // constructor  
        this->radius=radius;
        this->charge=charge;
        this->mass=mass;
        this->density=density;
    }
    //metodos para obtener los valores de la gota
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
};


#endif 