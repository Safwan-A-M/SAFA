#include <iostream>
#include <cmath>
using namespace std;

//Isentropic temperature after compression/expansion
double isentropicTemp(double T_in, double pressureRatio, double gamma) {
double exp = (gamma - 1.0)/gamma;
return T_in * pow(pressureRatio, exp);
}

// thermal efficiency of ideal brayton cycle
double thermalEfficiency(double pressureRatio, double gamma) {
double exp = (gamma - 1)/gamma;
return 1.0 - 1.0/ pow(pressureRatio, exp);
}

int main() {
//cycle parameters
    double gamma = 1.4;
    double T1 = 288.15;
    double T3 = 1400.0;
    double pr = 15.0;
//static calcualtions
double T2 = isentropicTemp(T1, pr, gamma);
double T4 =  T3/pow(pr, (gamma -1)/gamma);
double eta = thermalEfficiency(pr, gamma);

//work calculations
double cp = 1.005;
double W_comp = cp * (T3-T1);
double W_turb = cp * (T3-T4);
double W_net = W_turb - W_comp;

// out put state table
cout << "===================================" << endl;
cout << " BRAYTON CYCLE ANALYSIS" << endl;
cout << " =================================" << endl;
cout << "Pressure ratio:  " << pr << endl;
cout << " ---------------------------------" << endl;
cout << "State 1 (inlet): " << T1 << "K" << endl;
cout << "Stat 2 (post-c): " << T2 << "K" << endl;
cout << "State 3 (TIT) : " << T3 << "K" << endl;
cout << "State 4 (post-T): " << T4 << "K" << endl;
cout << "----------------------------------------" <<endl;
cout << "W_compressor: " << W_comp << "kj/kg" << endl;
cout << "W_turbine: " << W_turb << "kj/kg" << endl;
cout << "W_net: " << W_net << "kj/kg" << endl;
cout << "Efficiency: " << eta * 100 << "%" << endl;

return 0;
}
