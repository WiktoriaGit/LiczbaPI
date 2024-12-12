#include <iostream>
#include <cmath>

// Funkcja reprezentująca sqrt(1 - x^2)
// Jest to funkcja podcałkowa używana do obliczania liczby PI (z wzoru całki).
double func(double x) {
    return sqrt(1.0 - x * x);
}

// Funkcja obliczająca przybliżoną wartość liczby PI za pomocą metody prostokątów
// Przedziały całkowania są ustalone wewnątrz tej funkcji
double calculate_pi(int n) {
    double a = 0.0; // Początek przedziału całkowania
    double b = 1.0; // Koniec przedziału całkowania
    double h = (b - a) / n; // Szerokość każdego prostokąta
    double sum = 0.0;       // Suma obszarów prostokątów

    for (int i = 0; i < n; ++i) {
        double x = a + i * h; // Współrzędna x dolnego lewego rogu prostokąta
        sum += func(x);          // Wartość funkcji podcałkowej dodana do sumy
    }

    return 4 * h * sum; // Wynik końcowy: 4 * h * suma prostokątów
}

int main() {
    int n; // Liczba prostokątów

    std::cout << "Podaj liczbę prostokątów (im większa liczba, tym większa dokładność): ";
    std::cin >> n;

    // Sprawdzenie poprawności liczby prostokątów
    if (n <= 0) {
        std::cerr << "Liczba prostokątów musi być większa od zera!" << std::endl;
        return 1;
    }

    double pi = calculate_pi(n); // Obliczenie liczby PI

    // Wyświetlenie wyniku z 15 miejscami po przecinku bez użycia iomanip
    std::cout << "Przybliżona wartość liczby PI: ";
    printf("%.15f\n", pi_approx);

    return 0;
}
