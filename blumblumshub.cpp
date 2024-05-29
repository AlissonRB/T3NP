#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

// funcao para calcular ((a^b) mod m)
long int mod(long int a, long int b, long int m) {
    long int res = 1;
    a = a % m;
    while (b > 0) {
        if(b % 2 == 1)
            res = (res * a) % m;
        b = b / 2;
        a = (a * a) % m;
    }
    return res;
}

// voce deve fornecer os valores de entrada p,q,s,num_bits
//bits e x sao vetores para armazenar o numero gerado e a variavel X, respectivamente
vector<long int> BlumBlumShub(long int p, long int q, long int s, int num_bits, vector<long int> bits, vector<long int> x) {
    // n = p x q
    long int n = p * q;

    //o primeiro bit nao vai ser considerado, entao somar mais 1 para fechar o tamanho correto
    //num_bits vai o tamanho do vetor de bits(ex: 32, 64, 1024)
    num_bits += 1;

    //inicializa x[0]
    x[0] = mod (s, 2, n); //calcula ((s^2) mod n)
    bits[0]= x[0] % 2;

    //o algoritmo produz uma sequencia de bits nesse laço
    for (int i = 1; i < num_bits; i++) {
        //calcula a variavel atual usando a anterior
        x[i] = ((x[i-1]) * (x[i-1]) ) % n;
        //obtem o bit menos significativo em cada iteração
        bits[i]= x[i] % 2;
    }
    //retorna o numero gerado
    return bits;
}

int main() {
    // p e q, dois numeros primos grandes, ambos p e q congruente a 3 (mod 4)
    // s: numero aleatorio, relativamente primo de n(p e q nao sao fatores de s)
    long int p = 383;
    long int q = 503;
    long int s = 101355;
    int num_bits; //numero de bits a serem gerados

    // cout << "Digite p: ";
    // cin >> p;

    // cout << "Digite q: ";
    // cin >> q;

    // cout << "Digite s: ";
    // cin >> s;

    cout << "Digite o número de bits: ";
    cin >> num_bits;

    // vetor para armazenar o bits (numero)
    vector<long int> bits(num_bits);

    // vetor para armazenar a variavel X
    vector<long int> x(num_bits);
    //inicio da medição de tempo
    auto start = high_resolution_clock::now();

    vector<long int> random_number = BlumBlumShub(p, q, s, num_bits, bits, x);

    // fim da medição de tempo
    auto end = high_resolution_clock::now();

    //calculo da duração
    auto duration = duration_cast<microseconds>(end - start);

    //printa vetor
    cout << "bits: " << endl;
    for (int i = 1 ; i < num_bits; i++) {
        cout << random_number[i];
    }
    cout << endl;

    cout << "Tempo: " << duration.count() << "microsegundos" << endl;
    return 0;
}