//
//  SIMULACION.hpp
//  
//
//  Created by Angel Luna on 22/04/2025.
//

#ifndef SIMULACION_hpp
#define SIMULACION_hpp

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
//srand (static_cast <unsigned> (time(0)));
using namespace std;

template<typename T>
T getRandomElement(const std::vector<T>& vec) {
    if (vec.empty()) throw std::runtime_error("Vector is empty!");

    // Seed with a real random value, if available
    static std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<std::size_t> dist(0, vec.size() - 1);
    return vec[dist(rng)];
}



class gota { // una clase que almacena todos los calculos y datos disponibles para cada gota a ser analizada
private:
    double radius, mass;
    float density; //definir la densidad PENDIENTE
    double charge;
    int n; // cantidad de intervalos para tomar su pocicion y movimiento
    vector<double> height; //position, FALTA POR DEFINIR
    vector<double> time; //intervalos de tiemp de caida FALTA POR DEFINIR
    vector<double> velocity;
    vector<double> acceleration;
    double V_off, V_on; //velocidad terminal con el campo activado y desactivado
public:
    gota() { // constructor
        vector<double> possibleR={2.780,2,781,2.782,2.783,2.784,2.785,2.786,2.787,2.788,2.789,2.790};
        radius=getRandomElement(possibleR)*pow(10,-6);
        density=919.9;
        mass=(4/3*M_PI*pow(radius,3))*density;
        height[1]=(16*pow(10,-3));
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
