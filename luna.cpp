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
    int dropletQ=1; //cantidad de gotas a analizar
    gota gotas[dropletQ];
    double deltaT=1e-6; //definir el salto de tiempo
    double airV= 1.81e-5;
    double airD=1.2;
    double b=7.88e-3;
    double plaquedistance=16e-3;
    double pressure=13438.7;
    double espesor=1e-3;
    double resistividad=2.65e-8;
    double voltaje_C;
    double Area=4e-5;
    double epsilon_0=8.85418781762039e-12;
    double capacitancia=(Area*epsilon_0)/plaquedistance;
    double resistencia=resistividad*(espesor/Area);
    double constanteTau=resistencia*capacitancia;
    int contador=0;
    
    
    for (int i=0;i<dropletQ;i++) {
        double plaquevoltage=5e3;
        double Q=0;
        double Potentialdis=(Q/(Area*epsilon_0)*plaquedistance);
        double electricF=0;
        double EMF=plaquevoltage;
        gotas[i].calcstuff(airD,electricF);
        gotas[i].p_P(Potentialdis);
        

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
        double Q_cambio=0;
        while (abs(gotas[i].indexacc(j))>1e-5 or gotas[i].indexacc(j)==0)
        {
            Q_cambio=deltaT*(1.0/resistencia)*(EMF-(Q/capacitancia));
            Q=Q+Q_cambio;
            plaquevoltage=EMF*(1.0-exp(-(gotas[i].indextime(j)/constanteTau)));
            //plaquevoltage=Q/capacitancia;
            gotas[i].p_voltage(plaquevoltage);
            electricF=plaquevoltage/plaquedistance;
            //electricF=Q/(Area*epsilon_0);
            gotas[i].p_electric(electricF);
            gotas[i].defelectricforce(electricF);
            double V_pos = plaquevoltage * (gotas[i].indexheight(j) / plaquedistance);
            gotas[i].p_P(V_pos);
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+(b/pressure*gotas[i].getrad()));
            gotas[i].defdrag(drag);
            double acceleration=(gotas[i].getweight()+drag+gotas[i].getelectricforce()-gotas[i].getbuoyant())/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            //grafica
            archivo_con_campo << gotas[i].indextime(j) << "," << gotas[i].indexheight(j) << "," << gotas[i].indexvelociry(j) << "\n";
            j++;
            int contador=j;
        }
        
        archivo_con_campo.close();
        gotas[i].defV_on((gotas[i].vecvelocity()).back());
        //calcular la carga electrica de la particula
       
    }
    
    //menu interactivo
    string index_1="";
    int index_2=0;
    double q=(6*M_PI*airV*gotas[0].getrad())/(1+(b/pressure*gotas[0].getrad()))*(gotas[0].getV_on()+gotas[0].getV_off())/gotas[0].getElectric().back();
    cout << gotas[0].getcharge()/-1.602176634e-19 << "\n";
    cout << q/-1.602176634e-19 << "\n";
    while (index_1!="")
    {
        //aun no terminado
        cout << "*******************************************\n";
        cout << "SISTEMA DE ACCESO A EXPERIMENTO SIMULADO\n";
        cout << "SELECCIONE UN INDICE PARA ACCEDER A LOS\nDATOS DE UNA GOTA O IMPRIMIR DATOS EN\nCONJUNTO\n";
        cout << "*******************************************\n";
        cout << "VER GOTA POR GOTA.......................[V]\n";
        cout << "IMPRIMIR TODOS LOS RESULTADOS...........[T]\n";
        cout << "IMPRIMIR TODAS LAS CARGAS...............[C]\n";
        cout << "TERMINAR EJECUCIÓN......................[X]\n";
        cout << "*******************************************\n";
        cin >> index_1;
    }
    cout << "Directorio actual: " << filesystem::current_path() << endl;
}

