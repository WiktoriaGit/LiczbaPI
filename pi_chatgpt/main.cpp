#include <iostream>
#include <cmath>

// Funkcja podca³kowa (æwiartka okrêgu jednostkowego)
double func(double x) {
    return std::sqrt(1 - x * x);
}

// Funkcja obliczaj¹ca przybli¿on¹ wartoœæ liczby PI
double calculatePI(int n) {
    double a = 0.0; // Pocz¹tek przedzia³u
    double b = 1.0; // Koniec przedzia³u
    double h = (b - a) / n; // Szerokoœæ przedzia³u
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return 4 * h * sum;
}

int main() {
    int n;

    std::cout << "Podaj liczbê przedzia³ów: ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "Liczba przedzia³ów musi byæ dodatnia!" << std::endl;
        return 1;
    }

    double pi = calculatePI(n);
    std::cout << "Przybli¿ona wartoœæ liczby PI: " << pi << std::endl;

    return 0;
}
