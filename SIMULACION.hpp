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
    else {
        // Seed with a real random value, if available
        static std::mt19937 rng(std::random_device{}());
        
        std::uniform_int_distribution<std::size_t> dist(0, vec.size() - 1);
        return vec[dist(rng)];
    }
}

//Esto es un mugrero pero sirve

class gota { // una clase que almacena todos los calculos y datos disponibles para cada gota a ser analizada
private:
    double radius, mass;
    float density;
    double charge;
    int n; // cantidad de intervalos para tomar su pocicion y movimiento (pendiente de eliminar)
    vector<double> height; //vectores de aceleracion,velocidad etcetera que (se supone) tiene que agregarse cada valor corespondiente, PENDIENTE CHECAR SI SE PUEDE USAR UNA MATRIZ
    vector<double> time;
    vector<double> velocity;
    vector<double> acceleration;
    double V_off, V_on; //velocidad terminal con el campo activado y desactivado
public:
    gota() { // constructor
        vector<double> possibleR={2.780,2.781,2.782,2.783,2.784,2.785,2.786,2.787,2.788,2.789,2.790};
        radius=getRandomElement(possibleR)*pow(10,-6);
        density=919.9;
        mass=(4/3*M_PI*pow(radius,3))*density;
        height.push_back(16*pow(10,-3));
    }
    void defdivision(int _n) {
        n=_n;
    }
    
    //metodos para obtener los valores de la gota
    //al parecer no se pueden usar no-estaticos en los arreglos de las propiedades, por lo que esta variable [n] es inutil, por ahora, pero hay que ver como se puede modificar el tamaño del arreglo para dejarlo a discrecion del usuario.
    int getdivision() {
        return n;
    }
    double getrad() {
        return radius;
    }
    double getmass() {
        return mass;
    }
    double getrho() {
        return density;
    }
    double getheight(int interval) {
        int height[interval];
        return height[interval];
    }
    double getvelocity(int interval) {
        int velocity[interval];
        return velocity[interval];
    }
    double getacceleration(int interval) {
        int acceleration[interval];
        return acceleration[interval];
    }
    double getV_off() {
        return V_off;
    }
    double getV_on() {
        return V_on;
    }
    //instalacion de valores
    void defV_on(double _V_on) {
        V_on=_V_on;
    }
    void defV_off(double _V_off) {
        V_off=_V_off;
    }
    void defrad(double _radius) {
        radius=_radius;
    }
    void defmass(double _mass) {
        density=_mass;
    }
    void defrho(float _density) {
        density=_density;
    }
    void defcharge(double _charge) {
        charge=_charge;
    }
    void p_height(double _height) {
        height.push_back(_height);
    }
    void p_time(double _time) {
        time.push_back(_time);
    }
    void Vel(double _velocity) {
        velocity.push_back(_velocity);
    }
    void Acc(double _acceleration) {
        acceleration.push_back(_acceleration);
    }
    //regresar los valores de los vectores
    double indexheight(int i) {
        return height[i];
    }
    double indexvelociry(int i) {
        return velocity[i];
    }
    double indextime(int i) {
        return time[i];
    }
    double indexacc(int i) {
        return acceleration[i];
    }
    vector<double> vecheight() {
        return height;
    }
    vector<double> vecvelocity() {
        return velocity;
    }
    vector<double> vectime() {
        return time;
    }
    vector<double> vecacc() {
        return acceleration;
    }
};


#endif /* SIMULACION_hpp */