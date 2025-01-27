#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

struct Prato {
    int prioridade;
    int tempo_preparo;
    string nome;
};

bool comparar(const Prato &a, const Prato &b) {
    if (a.prioridade != b.prioridade)
        return a.prioridade > b.prioridade;
    return a.tempo_preparo < b.tempo_preparo;
}

int particionar(Prato pratos[], int esquerda, int direita) {
    int pivo = pratos[direita].prioridade;
    int i = esquerda - 1;
    
    for (int j = esquerda; j < direita; ++j) {
        if (pratos[j].prioridade > pivo) {
            ++i;
            Prato temp = pratos[i];
            pratos[i] = pratos[j];
            pratos[j] = temp;
        } else if (pratos[j].prioridade == pivo && pratos[j].tempo_preparo < pratos[direita].tempo_preparo) {
            ++i;
            Prato temp = pratos[i];
            pratos[i] = pratos[j];
            pratos[j] = temp;
        }
    }
    Prato temp = pratos[i + 1];
    pratos[i + 1] = pratos[direita];
    pratos[direita] = temp;
    return i + 1;
}

void quicksort(Prato pratos[], int esquerda, int direita) {
    if (esquerda < direita) {
        int pi = particionar(pratos, esquerda, direita);
        quicksort(pratos, esquerda, pi - 1);
        quicksort(pratos, pi + 1, direita);
    }
}

void bubblesort(Prato pratos[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (comparar(pratos[j], pratos[j + 1])) {
                Prato temp = pratos[j];
                pratos[j] = pratos[j + 1];
                pratos[j + 1] = temp;
            }
        }
    }
}

int main() {
    ifstream arquivo("restaurante_pratos.csv");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return 1;
    }
    string linha;
    Prato pratos[300000];
    int n = 0;

    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        Prato prato;
        
        ss >> prato.prioridade >> prato.tempo_preparo;
        ss >> prato.nome;
        
        pratos[n++] = prato;
    }

    clock_t start_quick = clock();
    quicksort(pratos, 0, n - 1);
    clock_t end_quick = clock();
    double tempo_quick = double(end_quick - start_quick) / CLOCKS_PER_SEC;

    clock_t start_bubble = clock();
    bubblesort(pratos, n);
    clock_t end_bubble = clock();
    double tempo_bubble = double(end_bubble - start_bubble) / CLOCKS_PER_SEC;

    cout << "Tempo de execucoao do quicksort: " << tempo_quick << " segundos" << endl;
    cout << "Tempo de execucao do bublesort: " << tempo_bubble << " segundos" << endl;

    return 0;
}
