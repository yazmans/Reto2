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
//funciones para calcular la carga elemental
double estimate_fast_e(const std::vector<double>& charges, double est_start = 1.5e-19, double est_end = 1.7e-19, double step = 1e-21) {
    double best_e = 0.0, min_error = std::numeric_limits<double>::max();

    for (double e = est_start; e <= est_end; e += step) {
        double error = 0.0;
        for (double q : charges) {
            int n = static_cast<int>(round(q / e));
            double q_fit = n * e;
            error += pow(q - q_fit, 2);
        }
        if (error < min_error) {
            min_error = error;
            best_e = e;
        }
    }
    return best_e;
}
//esta cosa creo que no hace casi nada pero si funciona no le muevas
double estimate_fine_e(const std::vector<double>& charges, double e_center, double fine_range = 2e-21, double fine_step = 1e-23) {
    double best_e = e_center;
    double min_error = std::numeric_limits<double>::max();

    for (double e = e_center - fine_range; e <= e_center + fine_range; e += fine_step) {
        double error = 0.0;
        for (double q : charges) {
            int n = static_cast<int>(round(q / e));
            double q_fit = n * e;
            error += pow(q - q_fit, 2);
        }
        if (error < min_error) {
            min_error = error;
            best_e = e;
        }
    }
    return best_e;
}

int main() {
    int dropletQ=1000; //cantidad de gotas a analizar
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
    vector <double> charges;
    
    
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
    for (int i=0; i<dropletQ;i++) {
        double E_field = gotas[i].getelectricforce() / gotas[i].getcharge();
        double rho_oil = gotas[i].getdensity(); // 919.9 kg/m^3
        double rho_air = airD; // 1.2 kg/m^3
        
        double buoyancy_corr = rho_oil / (rho_oil - rho_air);
        
        double q = -((6 * M_PI * airV * gotas[i].getrad()) /
                    (1 + b / (pressure * gotas[i].getrad()))) *
        ((fabs(gotas[i].getV_off()) + gotas[i].getV_on()) / E_field) *
        buoyancy_corr;
        cout << "*******************************************\n";
        cout << gotas[i].getcharge()/-1.602176634e-19 << "\n";
        cout << q/1.602176634e-19 << "\n";
        cout << "Mass (kg): " << gotas[i].getmass() << endl;
        cout<< "Air Viscosity (kg/ms): " << airV << endl;
        cout<<buoyancy_corr<<endl;
        cout << "Radius (m): " << gotas[i].getrad() << endl;
        cout << "V_off: " << gotas[i].getV_off() << endl;
        cout << "V_on: " << gotas[i].getV_on() << endl;
        cout << "E_field: " << E_field << endl;
        cout << "Real q (e): " << gotas[i].getcharge() / -1.602176634e-19 << endl;
        cout << "Calc q (e): " << q / -1.602176634e-19 << endl;
        charges.push_back(q);
        cout << "*******************************************\n";
    }
    cout << "*******************************************\n";
    double rough_e = estimate_fast_e(charges);
    double fine_e = estimate_fine_e(charges, rough_e);

    std::cout << "ESTIMADO FINAL DE e" << fine_e << " C" << std::endl;
    std::cout << "ERROR PORCENTUAL" << (fine_e - 1.602176634e-19) / 1.602176634e-19 * 100.0 << "%\n";
    cout << "*******************************************\n";
    //wowowowoooo
    

    while (index_1!="") //esta cosa nunca se va a usar

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
