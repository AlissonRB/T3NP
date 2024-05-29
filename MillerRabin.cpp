#include <iostream>
#include <vector>
#include <random>

using namespace std;


// funcao para calclar ((a^b) mod m)
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

//recebe o numero para teste, k = numero de iteracoes
bool miller_rabin(long int num, int k) {
    // casos triviais
    if (num == 2 || num == 3) {
        return true;
    }
    if (num <= 1 || num % 2 == 0) {
        return false;
    }

    //escrever n-1 = 2^s * m, onde m eh impar
    //inicializar m como n - 1
    long int m = num - 1;
    // s é um contador
    int s = 0;

    //cada vez que m eh dividido por 2, incrementa o contador s
    while (m % 2 == 0) {
        m /= 2;
        s++;
    }

    // teste de primalidade
    for (int i = 0; i < k; i++) {
        //gerar um numero a aleatorio (1 < a < n-1)
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long int> dis(1, num - 1);
        long int a = dis(gen);
        long int b =  mod(a, m, num);

        //verificacao inicial de b
        // se b congruente 1 (mod n) ou b congruente -1 (mod n)
        if (b == 1 || b == num - 1) {
            continue;
        }

        // inicialmente assume b como composto
        bool composto = true;

        // itera de 0 ate s-1
        for (int j = 0; j < s - 1; j++) {
            // calcula b^2 (mod n)
            b = mod(b, 2, num);
            if (b == num - 1) {
                // o numero eh provavelmente primo
                composto = false;
                break; // sai do loop, pois encontrou evidencia de que num pode ser primo
            }
        }
        // se composto for true apos o loop anterior, retorna false indicando que é composto
        if (composto) {
            return false;
        }
    }
    // se o loop completa sem encontrar evidencia de que num é composto, retorn indicando que eh relativamente primo
    return true;
}

int main() {

    // vetor para armazenar os numeros para teste de primalidade
    vector<long long int> numbers_test = {2,3,5,7,11,13,17,101,211,307,401,359,457};
    // numero de iteracoes de teste
    int k = 4;

    for (int i = 0; i < numbers_test.size(); i++) {
        bool result = miller_rabin(numbers_test[i], k);
        if (result == true) {
            cout << "P: " << numbers_test[i] << endl;
        }
    } 
    cout << "FIM !";

    return 0;

}