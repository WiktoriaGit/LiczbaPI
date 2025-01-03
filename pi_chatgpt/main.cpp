﻿#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono> // Biblioteka do pomiaru czasu

/**
 * @file main.cpp
 * @brief Program obliczający wartość liczby PI metodą prostokątów z użyciem wielowątkowości.
 */

 // Mutex do synchronizacji dostępu do sumy
std::mutex mtx;

double total_sum = 0.0; // Globalna suma

/**
 * @brief Funkcja reprezentująca sqrt(1 - x^2).
 *
 * Funkcja podcałkowa używana do obliczania liczby PI na podstawie całki oznaczonej.
 * @param x Wartość wejściowa.
 * @return Wartość funkcji sqrt(1 - x^2).
 */
double func(double x) {
    return sqrt(1.0 - x * x);
}

/**
 * @brief Funkcja obliczająca sumę dla danego przedziału wątku.
 *
 * Każdy wątek oblicza część sumy całkowej dla zadanego przedziału iteracji.
 * @param start Indeks początkowy.
 * @param end Indeks końcowy.
 * @param h Szerokość każdego prostokąta.
 * @param a Początek przedziału całkowania.
 */
void calculate_partial_sum(long long start, long long end, double h, double a) {
    double local_sum = 0.0;
    for (long long i = start; i < end; ++i) {
        double x = a + i * h;
        local_sum += func(x);
    }

    // Dodanie lokalnej sumy do globalnej sumy w sposób bezpieczny wątkowo
    std::lock_guard<std::mutex> lock(mtx);
    total_sum += local_sum;
}

/**
 * @brief Funkcja obliczająca wartość liczby PI za pomocą metody prostokątów z wielowątkowością.
 *
 * Funkcja dzieli obliczenia na wiele wątków, aby przyspieszyć proces.
 * @param n Liczba prostokątów (dokładność obliczeń).
 * @param num_threads Liczba wątków używanych do obliczeń.
 * @return Przybliżona wartość liczby PI.
 */
double calculate_pi(long long n, int num_threads) {
    double a = 0.0; // Początek przedziału całkowania
    double b = 1.0; // Koniec przedziału całkowania
    double h = (b - a) / n; // Szerokość każdego prostokąta

    // Ustalenie zakresu dla każdego wątku
    long long chunk_size = n / num_threads;
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; ++t) {
        long long start = t * chunk_size;
        long long end = (t == num_threads - 1) ? n : start + chunk_size;
        threads.emplace_back(calculate_partial_sum, start, end, h, a);
    }

    // Czekanie na zakończenie wszystkich wątków
    for (auto& thread : threads) {
        thread.join();
    }

    return 4 * h * total_sum; // Wynik końcowy: 4 * h * suma prostokątów
}

/**
 * @brief Funkcja główna programu.
 *
 * Pobiera dane od użytkownika, wykonuje obliczenia liczby PI i wyświetla wyniki.
 * @return Kod zakończenia programu.
 */
int main() {
    long long n; // Liczba prostokątów
    int num_threads; // Liczba wątków

    std::cout << "Podaj liczbe prostokatow (im wieksza liczba, tym wieksza dokladnosc): ";
    std::cin >> n;

    std::cout << "Podaj liczbę wątków: ";
    std::cin >> num_threads;

    // Sprawdzenie poprawności liczby prostokątów
    if (n <= 0 || num_threads <= 0) {
        std::cerr << "Liczba prostokatow i liczba watkow musza byc wieksze od zera!" << std::endl;
        return 1;
    }

    // Pomiar czasu rozpoczęcia
    auto start_time = std::chrono::high_resolution_clock::now();

    double pi = calculate_pi(n, num_threads); // Obliczenie liczby PI

    // Pomiar czasu zakończenia
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Wyświetlenie wyniku z 15 miejscami po przecinku bez użycia iomanip
    std::cout << "Przyblizona wartosc liczby PI: ";
    printf("%.15f\n", pi);

    // Wyświetlenie czasu obliczeń
    std::cout << "Czas obliczen: " << duration.count() << " ms" << std::endl;

    return 0;
}
