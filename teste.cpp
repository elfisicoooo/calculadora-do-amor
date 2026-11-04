#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <algorithm>
#include <cmath>

void reduz(int& num) {
    while (num > 9) {num = num % 10 + num / 10;}
}

int calcular_amor(std::string nome1, std::string nome2) {
    std::deque <int> novo; std::set <char> ja_usados;
    // formacao do deque inicial (novo)
    for (char c : nome1) {
        if (c != ' ' && ja_usados.count(c) == 0) {
            int k = std::count(nome1.begin(), nome1.end(), c) +
                    std::count(nome2.begin(), nome2.end(), c); reduz(k);
            novo.push_back(k);
            ja_usados.insert(c);
        }
    }

    for (char c : nome2) {
        if (c != ' ' && ja_usados.count(c) == 0) {
            int p = std::count(nome2.begin(), nome2.end(), c); reduz(p);
            novo.push_back(p);
            ja_usados.insert(c);
        }
    }

    // vai e volta dos deques
    std::deque<int> definitivo = novo, aux;
    while (definitivo.size() > 2) {
        aux = novo; novo.clear();
        int frente = aux.front();
        if (aux.size() == 1) {
            reduz(frente);
            novo.push_back(frente);
            aux.pop_front();
        } else {
            int tras = aux.back(), p = frente + tras; reduz(p);
            novo.push_back(p); aux.pop_back(); aux.pop_front();
        }

        definitivo = novo;
    }

    if (definitivo.size() == 2) {
        return 10 * definitivo.front() + definitivo.back();
    } else {
        return definitivo.back();
    }
}

int main() {
    
}