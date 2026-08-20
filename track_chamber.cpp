#include <iostream>
#include <random>
#include <cmath>
#include <utility>
#include <limits>   // для std::numeric_limits

// Генерирует точку на окружности радиуса rad (равномерно по углу) _____________________________________________
std::pair<double, double> randomPointOnCircle(double rad) {
    static std::mt19937 gen = []{
        std::random_device rd;
        std::seed_seq seq{rd(), rd(), rd(), rd()};
        return std::mt19937(seq);
    }();
    static std::uniform_real_distribution<double> angleDist(0.0, 2.0 * 3.141592653589793);
    double angle = angleDist(gen);
    return {rad * std::cos(angle), rad * std::sin(angle)};
}

float calorimeter() {
    // Генератор инициализируется один раз при первом вызове
    static std::mt19937 gen(std::random_device{}());
    // Распределение на полуинтервале [0.0, 25.2)
    static std::uniform_int_distribution<int> dist(0, 63503);
    int distr = dist(gen);
    float q[63504];
    for(int i = 0; i<63504; i++){
        q[i]= 25.2 - std::sqrt(i)/10;
    }
    return q[distr];
}

int main() { //________________________________________________________________________________________________

    float pogr = 0.05;
    float part_gev[7] = {25.2, 0.511, 0.105, 0.139, 0.493, 0.938, 3.097};
    std::string part_names[7] = {"Too high", "Electron", "Muon", "Pion", 
                                  "Kaon", "Proton", "J/psi meson"};

    float energy = calorimeter();
    int q;
    double B = 0.1;
    double P;
    // Точка 1 – начало координат
    // Точка 2 – радиус 0.5
    auto p2 = randomPointOnCircle(0.5);
    double x2 = p2.first, y2 = p2.second;
    // Точка 3 – радиус 1.0
    auto p3 = randomPointOnCircle(1.0);
    double x3 = p3.first, y3 = p3.second;

    // Вычисление центра окружности, проходящей через (0,0), p2, p3
    double D = 2.0 * (x2 * y3 - y2 * x3);
    if (std::abs(D) < 1e-12) {
        q = 0;
        std::cout << "ОШИБКА" << std::endl;
    } else { 
        if (D > 0) {
            q = 1;      // положительный заряд
        } else {
            q = -1;     // отрицательный заряд
        }

    double r2_sq = 0.25;      // x2^2 + y2^2
    double r3_sq = 1.0;       // x3^2 + y3^2
    double a = (r2_sq * y3 - y2 * r3_sq) / D;
    double b = (x2 * r3_sq - r2_sq * x3) / D;
    double R = std::sqrt(a * a + b * b);

    P = B * std::abs(q) * R;
    //ищем инвариантную массу
    float m_inv = sqrt(energy*energy - P*P);
    int found = 0;

    if (std::isnan(m_inv) || m_inv>part_gev[0]){
        std::cout << "ОШИБКА" << std::endl;
    } else {
        std::cout << "Радиус окружности (m): " << R << '\n';
        std::cout << "Заряд: " << q << '\n';
        std::cout << "Импульс: " << P << '\n';
        std::cout << "Энергия: " << energy << '\n';
        std::cout << "Инвариантная масса: " << m_inv << std::endl;

        for (int j = 1; j < 7; j++) {
            float lower = part_gev[j] * (1 - pogr);
            float upper = part_gev[j] * (1 + pogr);
            if (m_inv >= lower && m_inv <= upper) {
                std::cout << "Нашли: " << part_names[j] << "\n";
                found = 1;
                break;
            }

        }
        if(found==0){std::cout<<"СОВПАДЕНИЙ НЕТ"<<"\n";}
    }
}



    
    return 0;
}