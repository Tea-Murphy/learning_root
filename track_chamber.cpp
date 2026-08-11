#include <iostream>
#include <random>
#include <cmath>
#include <utility>

// Генерирует точку на окружности радиуса rad (равномерно по углу)
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

int main() {
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
    } else if('что-то там') { //тут должно быть какое-то условие
        q = -1;
    } else {
        q = 1;
    }
    double r2_sq = 0.25;      // x2^2 + y2^2
    double r3_sq = 1.0;       // x3^2 + y3^2
    double a = (r2_sq * y3 - y2 * r3_sq) / D;
    double b = (x2 * r3_sq - r2_sq * x3) / D;
    double R = std::sqrt(a * a + b * b);

    P = B * q * R;
    std::cout << "Радиус окружности: " << R << '\n';
    std::cout << "Заряд: " << q << '\n';
    std::cout << "Импульс частицы: " << P << std::endl;
    return 0;

    //дальше ищем инвариантную массу
}