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
    double deltaT=1e-8; //definir el salto de tiempo
    double airV= 1.81e-5;//kg/ms
    double airD=1.2; //kg/m^3
    double b=7.88e-3;//Pa m
    double plaquedistance=16e-3;//m
    double pressure=100.82e3;//Pa
    double espesor=1e-3;//m
    double resistividad=2.65e-8;//Ohms
    double Area=4e-5;//m^2
    double epsilon_0=8.85418781762039e-12;
    double capacitancia=(Area*epsilon_0)/plaquedistance;
    double resistencia=resistividad*(espesor/Area);
    double constanteTau=resistencia*capacitancia;
    double EMF=5e3;//V
    
    
    for (int i=0;i<dropletQ;i++) {
        double plaquevoltage=0;
        //double Potentialdis=(Q/(Area*epsilon_0)*plaquedistance);
        double Potentialdis=0;
        double electricF=0;
        gotas[i].calcstuff(airD,electricF);
        gotas[i].p_P(Potentialdis);
        
        double Q=0;
        double Q_cambio=0;

        int j=0;
        
        while (abs(gotas[i].indexacc(j))>1e-6 or gotas[i].indexacc(j)==0)
        {
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+(b/pressure*gotas[i].getrad()));
            gotas[i].defdrag(drag);
            double acceleration=(gotas[i].getweight()+drag+gotas[i].getbuoyant())/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            
            j++;
        }
        /*vector<double> v_off_vec=gotas[i].vecvelocity();
        int total = v_off_vec.size();
        int last_part = total / 5;
        double sum_v = 0;
        for (int k = total - last_part; k < total; ++k) {
            sum_v += v_off_vec[k];
        }
        double avg_v_off = sum_v / last_part;
        gotas[i].defV_off(avg_v_off);*/
        gotas[i].defV_off(gotas[i].indexvelociry(j-1));
        vector<double> v_off_vec = gotas[i].vecvelocity();
        
        
        gotas[i].clearll();

        j=0;
        while (abs(gotas[i].indexacc(j))>1e-6 or gotas[i].indexacc(j)==0)
        {
            Q=capacitancia*EMF*(1.0-exp(-gotas[i].indextime(j)/constanteTau));
            plaquevoltage = EMF * (1.0 - exp(-gotas[i].indextime(j) / constanteTau));
            gotas[i].p_voltage(plaquevoltage);
            electricF=plaquevoltage/plaquedistance;
            gotas[i].p_electric(electricF);
            gotas[i].defelectricforce(electricF);
            double V_pos = -electricF * (gotas[i].indexheight(j));//checar
            gotas[i].p_P(V_pos);
            double drag=-6*M_PI*airV*gotas[i].getrad()*gotas[i].indexvelociry(j)/(1+(b/pressure*gotas[i].getrad()));
            gotas[i].defdrag(drag);
            double netforce=gotas[i].getbuoyant()+drag-(electricF*gotas[i].getcharge())+gotas[i].getweight();
            double acceleration=netforce/gotas[i].getmass();
            gotas[i].Acc(acceleration);
            double vel= gotas[i].indexvelociry(j)+gotas[i].indexacc(j)*deltaT;
            gotas[i].Vel(vel);
            double height=gotas[i].indexheight(j)-vel*deltaT;
            gotas[i].p_height(height);
            gotas[i].p_time(gotas[i].indextime(j)+deltaT);
            //grafica
            j++;
        }

        /*vector<double> v_on_vec = gotas[i].vecvelocity();
        total = v_on_vec.size();
        last_part = total / 5;
        sum_v = 0;
        for (int k = total - last_part; k < total; ++k) {
            sum_v += v_on_vec[k];
        }
        double avg_v_on = sum_v / last_part;
        
        gotas[i].defV_on(avg_v_on);
        */
        gotas[i].defV_on(gotas[i].indexvelociry(j-1));
        vector<double> v_on_vec = gotas[i].vecvelocity();
        

    }

    
    //menu interactivo
    string index_1="";
    int index_2=0;
    double E_field = gotas[0].getelectricforce() / gotas[0].getcharge();
    double rho_oil = gotas[0].getdensity(); // 919.9 kg/m^3
    double rho_air = airD; // 1.2 kg/m^3

    double buoyancy_corr = rho_oil / (rho_oil - rho_air);

    double q = ((6 * M_PI * airV * gotas[0].getrad()) /
               (1 + b / (pressure * gotas[0].getrad()))) *
               ((fabs(gotas[0].getV_off()) + gotas[0].getV_on()) / E_field) *
               buoyancy_corr;

    cout << gotas[0].getcharge()/-1.602176634e-19 << "\n";
    cout << q/1.602176634e-19 << "\n";
    cout << "Mass (kg): " << gotas[0].getmass() << endl;
    cout<< "Air Viscosity (kg/ms): " << airV << endl;
    cout<<buoyancy_corr<<endl;
    cout << "Radius (m): " << gotas[0].getrad() << endl;
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
}