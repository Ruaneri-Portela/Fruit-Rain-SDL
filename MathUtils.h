#include <random>
#include <iostream>
#include <cmath>

int randomRange(int min, int max) {
    std::random_device rd;  // Obtém um dispositivo de geração de números aleatórios
    std::mt19937 gen(rd()); // Inicializa o gerador com o valor do dispositivo
    std::uniform_int_distribution<int> distribution(min, max); // Define a distribuição
    return distribution(gen); // Gera um número aleatório dentro do intervalo e o retorna
}
double distance(double x1, double y1, double x2, double y2) {
    double diff = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return diff;
}