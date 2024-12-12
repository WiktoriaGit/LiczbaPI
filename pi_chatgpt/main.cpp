#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono> // Biblioteka do pomiaru czasu

// Mutex do synchronizacji dostępu do sumy
std::mutex mtx;

double total_sum = 0.0; // Globalna suma

// Funkcja reprezentująca sqrt(1 - x^2)
// Jest to funkcja podcałkowa używana do obliczania liczby PI (z wzoru całki).
double func(double x) {
    return sqrt(1.0 - x * x);
}

// Funkcja obliczająca sumę dla danego przedziału wątku
void calculate_partial_sum(int start, int end, double h, double a) {
    double local_sum = 0.0;
    for (int i = start; i < end; ++i) {
        double x = a + i * h;
        local_sum += func(x);
    }

    // Dodanie lokalnej sumy do globalnej sumy w sposób bezpieczny wątkowo
    std::lock_guard<std::mutex> lock(mtx);
    total_sum += local_sum;
}

// Funkcja obliczająca przybliżoną wartość liczby PI za pomocą metody prostokątów
// z użyciem wielowątkowości
double calculate_pi(int n, int num_threads) {
    double a = 0.0; // Początek przedziału całkowania
    double b = 1.0; // Koniec przedziału całkowania
    double h = (b - a) / n; // Szerokość każdego prostokąta

    // Ustalenie zakresu dla każdego wątku
    int chunk_size = n / num_threads;
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; ++t) {
        int start = t * chunk_size;
        int end = (t == num_threads - 1) ? n : start + chunk_size;
        threads.emplace_back(calculate_partial_sum, start, end, h, a);
    }

    // Czekanie na zakończenie wszystkich wątków
    for (auto& thread : threads) {
        thread.join();
    }

    return 4 * h * total_sum; // Wynik końcowy: 4 * h * suma prostokątów
}

int main() {
    int n; // Liczba prostokątów
    int num_threads; // Liczba wątków

    std::cout << "Podaj liczbę prostokątów (im większa liczba, tym większa dokładność): ";
    std::cin >> n;

    std::cout << "Podaj liczbę wątków: ";
    std::cin >> num_threads;

    // Sprawdzenie poprawności liczby prostokątów
    if (n <= 0 || num_threads <= 0) {
        std::cerr << "Liczba prostokątów i liczba wątków muszą być większe od zera!" << std::endl;
        return 1;
    }

    // Pomiar czasu rozpoczęcia
    auto start_time = std::chrono::high_resolution_clock::now();

    double pi = calculate_pi(n, num_threads); // Obliczenie liczby PI

    // Pomiar czasu zakończenia
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Wyświetlenie wyniku z 15 miejscami po przecinku bez użycia iomanip
    std::cout << "Przybliżona wartość liczby PI: ";
    printf("%.15f\n", pi);

    // Wyświetlenie czasu obliczeń
    std::cout << "Czas obliczeń: " << duration.count() << " ms" << std::endl;

    return 0;
}
