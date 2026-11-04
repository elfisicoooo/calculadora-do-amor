#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <algorithm>

void exibe_menu() {
    std::cout << "====================================================================================================\n";
    std::cout << "Seja bem vindo(a) a CALCULADORA DO AMOR!\n\n";
    std::cout << "Você está gostando de uma pessoa e quer verificar suas chances de terminar ao lado dela?\n";
    std::cout << "Se sim, então você está no lugar certo! Basta inserir os nomes que o resultado será exibido na hora!\n\n";
    std::cout << "Opções: \n";
    std::cout << "1. Calcular a porcentagem do amor\n";
    std::cout << "2. Sair do programa\n";
    std::cout << "====================================================================================================\n";
    std::cout << "Insira a opção: ";
}
void verifica_opcao(char& opcao)  {
    bool verificado = false;
    std::string tentativa;
    std::getline(std::cin, tentativa);

    while (!verificado) {
        if (tentativa.size() != 1 || (tentativa[0] != '1' && tentativa[0] != '2')) {
            std::cout << "Opção inválida. Tente novamente (1 ou 2): ";
            std::getline(std::cin, tentativa);
        } else {
            opcao = tentativa[0];
            std::cout << "====================================================================================================\n";
            verificado = true;
        }
    }
}
void definir_nomes(std::string& nome1, std::string& nome2) {
    bool def1 = false, def2 = false;
    // define nome1
    std::string tentativa;
    std::cout << "Insira o nome da primeira pessoa. Esse nome não pode ter letras minúsculas, nem acentos e não pode começar com espaços: ";
    std::getline(std::cin, tentativa);

    while (!def1) {
        if (tentativa.size() < 1 || tentativa[0] == ' ') {
            std::cout << "\nOpção inválida. O primeiro caractere do nome não pode ser um espaço/o nome deve haver 1 ou mais caractere.\n";
            std::cout << "Tente novamente: ";
            std::getline(std::cin, tentativa);
        } else {
            bool caracteres_validos = true;
            for (char c : tentativa) {
                if (c != ' ' && (c < 'A' || c > 'Z')) {
                    std::cout << "\nOpção inválida. O nome precisa ser formado por letras maiúsculas do alfabeto latino e por espaços, mas sem acentos.\n";
                    std::cout << "Tente novamente: ";
                    std::getline(std::cin, tentativa);
                    caracteres_validos = false;
                    break;
                }
            }

            if (caracteres_validos) {
                nome1 = tentativa;
                def1 = true;
            }
        }
    }
    // define nome2
    std::cout << "Insira o nome da segunda pessoa. Esse nome não pode ter letras minúsculas, nem acentos e não pode começar com espaços: ";
    std::getline(std::cin, tentativa);

    while (!def2) {
        if (tentativa.size() < 1 || tentativa[0] == ' ') {
            std::cout << "\nOpção inválida. O primeiro caractere do nome não pode ser um espaço/o nome deve haver 1 ou mais caractere.\n";
            std::cout << "Tente novamente: ";
            std::getline(std::cin, tentativa);
        } else {
            bool caracteres_validos = true;
            for (char c : tentativa) {
                if (c != ' ' && (c < 'A' || c > 'Z')) {
                    std::cout << "\nOpção inválida. O nome precisa ser formado por letras maiúsculas do alfabeto latino e por espaços, mas sem acentos.\n";
                    std::cout << "Tente novamente: ";
                    std::getline(std::cin, tentativa);
                    caracteres_validos = false;
                    break;
                }
            }

            if (caracteres_validos) {
                nome2 = tentativa;
                std::cout << "====================================================================================================\n";
                def2 = true;
            }
        }
    }
}
int reduz(int num) {
    while (num > 9) {num = num % 10 + num / 10;}
    return num;
}
int calcular_amor(std::string nome1, std::string nome2) {
    std::deque <int> d; std::set <char> ja_usados;

    for (char c : nome1 + nome2) {
        if (c != ' ' && ja_usados.count(c)) continue;
        int k = std::count(nome1.begin(), nome1.end(), c) +
                std::count(nome2.begin(), nome2.end(), c); 
        d.push_back(reduz(k));
        ja_usados.insert(c);
    }

    while (d.size() > 2) {
        std::deque<int> novo;
        while (d.size() > 1) {
            novo.push_back(reduz(d.front() + d.back())); 
            d.pop_front(); d.pop_back();
        }
        if (!d.empty()) novo.push_back(d.front());
        d = novo;
    }

    int resultado = 0;
    for (int x : d) resultado = resultado*10 + x;
    return resultado;
}

int main() {
    char opcao; std::string nome1, nome2;
    exibe_menu(); verifica_opcao(opcao);

    while (opcao == '1') {
        definir_nomes(nome1, nome2); 
        std::cout << "RESULTADO: A possibilidade de " << nome1 << " e " << nome2 << " ficarem juntos é de " << std::max(calcular_amor(nome1, nome2), calcular_amor(nome2, nome1)) << "%.\n";
        std::cout << "Você quer continuar? (1 para continuar e 2 para sair) ";
        verifica_opcao(opcao);
    }
}