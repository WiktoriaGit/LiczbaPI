#include <iostream>
#include <cmath>

// Funkcja podca�kowa (�wiartka okr�gu jednostkowego)
double func(double x) {
    return std::sqrt(1 - x * x);
}

// Funkcja obliczaj�ca przybli�on� warto�� liczby PI
double calculatePI(int n) {
    double a = 0.0; // Pocz�tek przedzia�u
    double b = 1.0; // Koniec przedzia�u
    double h = (b - a) / n; // Szeroko�� przedzia�u
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return 4 * h * sum;
}

int main() {
    int n;

    std::cout << "Podaj liczb� przedzia��w: ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "Liczba przedzia��w musi by� dodatnia!" << std::endl;
        return 1;
    }

    double pi = calculatePI(n);
    std::cout << "Przybli�ona warto�� liczby PI: " << pi << std::endl;

    return 0;
}
