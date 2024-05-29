#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

//recebe xo(semente), m(modulo), a(multiplicador), c(incremento), num_nums(quantid. de numeros a serem gerados)
vector<long int> linear_congruential_generator(long int xo, long int m, long int a, long int c, int num_nums) {
    //vetor para armazenar os numeros gerados
    vector<long int> random_numbers(num_nums);

    //inicializa o primeiro valor da sequencia
    random_numbers[0] = xo;
    
    for (int i = 1; i < num_nums; i++) {
        //formula do metodo de congruencia linear
        random_numbers[i] = ((random_numbers[i-1] * a) + c) % m;
    }
    // ex de saida: [1 5 25 29 17 21 9 13 1 5]
    return random_numbers;
}

int main() {
    long int xo = 1;
    long int m = 32;
    long int a = 5;
    long int c = 0;
    int num_nums = 10; //quantidade de numeros a serem gerados
    vector<long int>  numbers(num_nums);

    //inicio da medição de tempo
    auto start = high_resolution_clock::now();

    numbers = linear_congruential_generator(xo, m, a, c, num_nums);

    // fim da medição de tempo
    auto end = high_resolution_clock::now();

    //calculo da duração
    auto duration = duration_cast<microseconds>(end - start);

    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    cout << "Tempo: " << duration.count() << "mc" << endl;
    return 0;
}