#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Air density — exponential atmosphere model
double airDensity(double h) {
    return 1.225 * exp(-h / 8500.0);
}

// Drag force
double dragForce(double v, double h, double Cd, double A) {
    double rho = airDensity(h);
    return 0.5 * rho * Cd * A * v * v;
}

int main() {
    // Rocket parameters
    double mass    = 500.0;  // kg (dry mass)
    double thrust  = 15000.0;// N
    double Cd     = 0.3;    // drag coefficient
    double A      = 0.5;    // cross-section area (m^2)
    double g      = 9.81;   // gravity (m/s^2)
    double dt     = 0.05;   // timestep (s)
    double t_end  = 120.0;  // simulate 2 minutes

    // Initial conditions
    double h = 0.0, v = 0.0, t = 0.0;

    // Storage
    vector<double> t_vec, h_vec, v_vec, a_vec;

    // Simulation loop
    while (t <= t_end && h >= 0.0) {
        double D = dragForce(v, h, Cd, A);
        double F_net = thrust - D - mass * g;
        double a = F_net / mass;

        t_vec.push_back(t);
        h_vec.push_back(h);
        v_vec.push_back(v);
        a_vec.push_back(a);

        // Euler step for both ODEs
        h = h + v * dt;
        v = v + a * dt;
        t = t + dt;
    }

    // Terminal output — every 10 seconds
    cout << "Time(s)  Height(m)  Velocity(m/s)  Accel(m/s^2)" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < (int)t_vec.size(); i += (int)(10.0/dt)) {
        printf("%-8.1f %-10.1f %-14.2f %.2f", t_vec[i], h_vec[i], v_vec[i], a_vec[i]);
    }

    cout << "Max altitude: " << *max_element(h_vec.begin(), h_vec.end())
         << " m" << endl;

    // Write CSV
    ofstream f("ascent.csv");
    f << "time_s,height_m,velocity_ms,accel_ms2" << endl;
    for (int i = 0; i < (int)t_vec.size(); i++)
        f << t_vec[i] << "," << h_vec[i] << ","
          << v_vec[i] << "," << a_vec[i] << endl;
    f.close();
    cout << "Written: ascent.csv" << endl;

    return 0;
}
