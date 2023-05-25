#include <random>
#include <iostream>
#include <cmath>

int randomRange(int min, int max)
{
    std::random_device rd;                                     // Obtém um dispositivo de geração de números aleatórios
    std::mt19937 gen(rd());                                    // Inicializa o gerador com o valor do dispositivo
    std::uniform_int_distribution<int> distribution(min, max); // Define a distribuição
    return distribution(gen);                                  // Gera um número aleatório dentro do intervalo e o retorna
}
double distance(double x1, double y1, double x2, double y2)
{
    double diff = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return diff;
}

class MoveDeltaTime
{
private:
    Uint32 startTime = SDL_GetTicks();
    Uint32 currentTime;
    Uint32 elapsedTime;
    float divSpeed, mov;
    int callback;

public:
    float speed;
    int move()
    {
        currentTime = SDL_GetTicks();
        if (speed != 0)
        {
            elapsedTime = currentTime - startTime;
            divSpeed = 1000 / speed;
            if (elapsedTime >= divSpeed)
            {
                if (mov >= 1.0f)
                {
                    callback = (int)mov;
                    mov = mov - 1.0f;
                    return callback;
                }
                else
                {
                    mov = mov + (speed / 1);
                }
                startTime = currentTime;
            };
            return 0;
        }
        else
            return 0;
    };
};
