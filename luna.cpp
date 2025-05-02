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
#include <filesystem>
#include "SIMULACION.hpp"
using namespace std;


int main() {
    int dropletQ=1; //cantidad de gotas a analizar
    gota gotas[dropletQ];
    double deltaT=1e-7; //definir el salto de tiempo
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
    double EMF=5e3;
    
    
    for (int i=0;i<dropletQ;i++) {
        double plaquevoltage=EMF;
        double Q=0;
        double Potentialdis=(Q/(Area*epsilon_0)*plaquedistance);
        double electricF=0;
        gotas[i].calcstuff(airD,electricF);
        gotas[i].p_P(Potentialdis);
        


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
            
            j++;
        }
        vector<double> v_off_vec=gotas[i].vecvelocity();
        int total = v_off_vec.size();
        int last_part = total / 5;
        double sum_v = 0;
        for (int k = total - last_part; k < total; ++k) {
            sum_v += v_off_vec[k];
        }
        double avg_v_off = sum_v / last_part;
        gotas[i].defV_off(avg_v_off);
    
        
        gotas[i].clearll();


        j=0;
        double Q_cambio=0;
        while (abs(gotas[i].indexacc(j))>1e-1 or gotas[i].indexacc(j)==0)
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
            double acceleration = (gotas[i].getweight() + drag - gotas[i].getbuoyant() + gotas[i].getcharge() * electricF) / gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            //grafica
            j++;
            int contador=j;
        }
        vector<double> v_on_vec = gotas[i].vecvelocity();
        total = v_on_vec.size();
        last_part = total / 5;
        sum_v = 0;
        for (int k = total - last_part; k < total; ++k) {
            sum_v += v_on_vec[k];
        }
        double avg_v_on = sum_v / last_part;
        
        gotas[i].defV_on(avg_v_on);
        //calcular la carga electrica de la particula
       
    }

    
    //menu interactivo
    string index_1="";
    int index_2=0;
    double E_field = EMF / plaquedistance;
    double rho_oil = gotas[0].getdensity(); // should be ~919.9
    double rho_air = airD;

    double buoyancy_corr = rho_oil / (rho_oil - rho_air);

    double q = ((2 * 6 * M_PI * airV * gotas[0].getrad()) /
               (1 + b / (pressure * gotas[0].getrad()))) *
               ((gotas[0].getV_off() + gotas[0].getV_on()) / E_field) *
               buoyancy_corr;

    cout << gotas[0].getcharge()/-1.602176634e-19 << "\n";
    cout << q/-1.602176634e-19 << "\n";
    cout << "Radius (m): " << gotas[0].getrad() << endl;
    cout << "Mass (kg): " << gotas[0].getmass() << endl;
    cout << "V_off: " << gotas[0].getV_off() << endl;
    cout << "V_on: " << gotas[0].getV_on() << endl;
    cout << "E_field: " << E_field << endl;
    cout << "Real q (e): " << gotas[0].getcharge() / -1.602176634e-19 << endl;
    cout << "Calc q (e): " << q / -1.602176634e-19 << endl;
    
    
    while (index_1!="")

    for (int i=0;i<dropletQ;i++)

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
