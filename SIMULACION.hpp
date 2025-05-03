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
    double density;
    double buoyantF;
    double volume;
    double drag;
    double weight;
    double netF;
    double electricforce;
    double charge;
    int n; // cantidad de intervalos para tomar su pocicion y movimiento (pendiente de eliminar)
    vector<double> height; //vectores de aceleracion,velocidad etcetera que (se supone) tiene que agregarse cada valor corespondiente, PENDIENTE CHECAR SI SE PUEDE USAR UNA MATRIZ
    vector<double> time;
    vector<double> velocity;
    vector<double> acceleration;
    
    //vectores para circuito RC
    vector<double> voltaje;
    vector<double> Electric;
    vector<double> PotDis;
    
    double V_off, V_on; //velocidad terminal con el campo activado y desactivado
public:
    gota() { // constructor
        vector<double> possibleR={2.780,2.781,2.782,2.783,2.784,2.785,2.786,2.787,2.788,2.789,2.790};
        vector<double> possibleN={
            10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
                50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
                70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
                80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
                90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
                100
        };
        radius=getRandomElement(possibleR)*1e-6;//m
        charge=getRandomElement(possibleN)*(-1.602176634e-19);
        density=919.9;//919.9 kg/m^3
        volume=((4.0/3.0)*M_PI*pow(radius,3));
        mass=volume*(density);
        height.push_back(16e-3);
        weight=-9.803*mass;
        acceleration.push_back(-9.803);
        velocity.push_back(0);
        time.push_back(0);
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
    double getV_off() {
        return V_off;
    }
    double getV_on() {
        return V_on;
    }
    double getcharge() {
        return charge;
    }
    double getdensity() {
        return density;
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
    void calcstuff(double airDensity, double electricfield) {
        buoyantF=airDensity*volume*9.803;
        electricforce=-electricfield*charge;
        Electric.push_back(electricfield);
    }
    double getbuoyant() {
        return buoyantF;
    }
    double getdrag() {
        return drag;
    }
    double getvolume() {
        return volume;
    }
    double getelectricF() {
        return electricforce;
    }
    double getnetF() {
        return netF;
    }
    void defdrag(double _drag) {
        drag=_drag;
    }
    double getweight() {
        return weight;
    }
    double indexP(int index) {
        return PotDis[index];
    }
    double indexelectric(int index) {
        return Electric[index];
    }
    double indexvolt(int index) {
        return voltaje[index];
    }
    void p_P(double value) {
        PotDis.push_back(value);
    }
    void p_electric(double value) {
        Electric.push_back(value);
    }
    void p_voltage(double value) {
        voltaje.push_back(value);
    }
    vector<double> getvoltage() {
        return voltaje;
    }
    vector<double> getElectric() {
        return Electric;
    }
    vector<double> getP() {
        return PotDis;
    }
    void defelectricforce(double _electricfield) {
        electricforce=_electricfield*charge;
    }
    double getelectricforce() {
        return electricforce;
    }
    void clearll() {
        acceleration.clear();
        time.clear();
        velocity.clear();
        height.clear();
        acceleration.push_back(-9.803);
        height.push_back(16e-3);
        time.push_back(0);
        velocity.push_back(0);
    }
};



#endif /* SIMULACION_hpp */
