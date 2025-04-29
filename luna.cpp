///
//  luna.cpp
//  Reto
//
//  Created by Angel Luna on 26/04/2025.
//

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <filesystem>
#include "SIMULACION.hpp"
using namespace std;


int main() {
    int dropletQ=5; //cantidad de gotas a analizar
    gota gotas[dropletQ];
    double deltaT=1e-6; //definir el salto de tiempo
    double airV= 1.81e-5;
    double airD=1.2;
    double b=7.88e-3;
    double platedistance=16e-3;
    double platevoltage=5e3;
    double electricF=platevoltage/platedistance; //calculo del campo electrico
    double pressure=13438.7;
    double capacitancia=2.2125e-13;
    vector<double> tiempo;
    vector<double> voltaje;
    double voltaje_C;
    double deltaV_C;
    double Q=capacitancia*platevoltage;
    double constanteTau=5.8631e-21;
    double Area=4e-4;
    double epsilon_0=8.85418781762039e-12;
    
    
    
    
    for (int i=0;i<dropletQ;i++) {
        gotas[i].calcstuff(airD,electricF);

        ofstream archivo_sin_campo("gota" + to_string(i) + "_sin_campo.csv");
        if (!archivo_sin_campo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo 'gota" << i << "_sin_campo.csv' para escritura.\n";
            continue; // Salta al siguiente ciclo si no se puede abrir el archivo
        }
        archivo_sin_campo << "Tiempo,Altura,Velocidad\n";

        int j=0;
        
        while (abs(gotas[i].indexacc(j))>1e-5 or gotas[i].indexacc(j)==0)
        {
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+(b/pressure*gotas[i].getrad()));
            gotas[i].defdrag(drag);
            double acceleration=(gotas[i].getweight()+drag-gotas[i].getbuoyant())/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            archivo_sin_campo << gotas[i].indextime(j) << "," << gotas[i].indexheight(j) << "," << gotas[i].indexvelociry(j) << "\n";
            j++;
        }
        
        archivo_sin_campo.close();
        gotas[i].defV_off((gotas[i].vecvelocity()).back());
    
        
        gotas[i].clearll();

        ofstream archivo_con_campo("gota" + to_string(i) + "_con_campo.csv");
        if (!archivo_con_campo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo 'gota" << i << "_con_campo.csv' para escritura.\n";
            continue; // Salta al siguiente ciclo si no se puede abrir el archivo
        }
        archivo_con_campo << "Tiempo,Altura,Velocidad\n";

        j=0;
        while (abs(gotas[i].indexacc(j))>1e-5 or gotas[i].indexacc(j)==0)
        {
            deltaV_C=(Q/capacitancia)*platevoltage*(1-exp(-deltaT/constanteTau));
            voltaje_C=platevoltage+deltaV_C;
            voltaje.push_back(voltaje_C);
            Q= capacitancia*platevoltage*(1-exp(-deltaT/constanteTau));
            electricF=Q/(Area*epsilon_0);
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+(b/pressure*gotas[i].getrad()));
            gotas[i].defdrag(drag);
            double acceleration=(gotas[i].getweight()+drag-gotas[i].getelectricF()-gotas[i].getbuoyant())/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            //grafica
            archivo_con_campo << gotas[i].indextime(j) << "," << gotas[i].indexheight(j) << "," << gotas[i].indexvelociry(j) << "\n";
            j++;
        }
        
        archivo_con_campo.close();
        gotas[i].defV_on((gotas[i].vecvelocity()).back());
        //calcular la carga electrica de la particula
       
    }
    
    for (int i=0;i<dropletQ;i++)
    {
        cout << "GOTA " << i << "\n";
        cout << "****************************************************\n";
        cout << "VELOCIDAD SIN CAMPO: " <<gotas[i].getV_off() << "ms^-1\n";
        double V_off=gotas[i].getV_off();
        cout << "VELOCIDAD CON CAMPO: " << gotas[i].getV_on() << "ms^-1\n";
        cout << "****************************************************\n";
        cout << "CARGA DE LA GOTA: \n";
        double V_on=gotas[i].getV_on();
        double charge=(6*M_PI*airV*gotas[i].getrad()*(V_on+V_off))/(electricF*(1+(b/(pressure*gotas[i].getrad()))));
        cout << charge << "C\n";
        cout << "****************************************************\n";
    }
    cout << "Directorio actual: " << filesystem::current_path() << endl;
}

