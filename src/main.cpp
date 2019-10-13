/**
 * Nomes:   Erick M. L. Pacheco             RAs:    18711630
 *          Leonardo Sanavio                        18054395
 *
 * Num. max. de cidades atendidas (time-out de 60 segundos): 
 * Opcionais funcionando:
 *          Opcional 5
 *
 * Obs:
 *
 * Valor do projeto:  1 ponto(s)
 */

#include <chrono>
#include <cstring>
#include <iostream>

#define TOTAL_LOCATIONS 41

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::milliseconds milliseconds;

#include "base.cpp"

Clock::time_point t_start;  // Guardara o inicio da contagem de tempo
Clock::time_point t_stop;   // Guardara o final da contagem de tempo

/**
 * Busca e retorna o nome do local
 *
 * @param locations Lista de locais para consulta
 * @param index ID/indice do local
 * @return Nome do local
 */
char *get_place_name(int index) {
    return locations[index];
}

/**
 * Busca e retorna o peso da aresta
 *
 * @param x Linha da matriz (cidade A)
 * @param y Coluna da matriz (cidade B)
 * @return Peso da aresta na posicao xy
 */
int get_edge_weight(int adj_matrix[][42], int x, int y) {
    return adj_matrix[x][y];
}

/**
 * Mostra a menor rota na tela (prototipo)
 *
 * @param s Elemento contendo vetor com IDs das cidades do menor caminho e o menor custo
 * @param locations Lista de locais para consulta
 * @param destiny ID do local de destino
 * @param t Guarda o tempo decorrido do processo de busca
 */
void print_shortest(element s, int am[][42], int destiny) {
    int i = 0;
    bool inverter = false;

    cout << "---- MENOR PERCURSO ----" << endl
         << "De: " << get_place_name(s.route[0]) << endl
         << "Para: " << get_place_name(destiny) << endl
         << "\nRota completa:\n\n";
    while (s.route[i++] != -1) {
        if (s.route[i] != -1) {
            cout << get_place_name(s.route[i - 1]);
            cout << " -> " << get_place_name(s.route[i]) << " (" << get_edge_weight(am, s.route[i - 1], s.route[i]) << " km)" << endl;
        } else
            break;
    }
    cout << "\nDistancia total: " << s.cost << " km";

    t_stop = Clock::now();
    milliseconds ms = chrono::duration_cast<milliseconds>(t_stop - t_start);
    cout << endl
         << "Tempo de processamento: " << ms.count() << " ms" << endl
         << "------------------------";
}

/**
 * Apresenta o menu e le as opcoes de usuario
 *
 * @param iv Vertice inicial
 * @param fv Vertice final
 */
void read(int *iv, int *fv) {
    int op;
    bool read_again = false;

    cout << "1. Fazer tour atraves dos EUA" << endl
         << "2. Buscar menor percurso entre duas cidades" << endl
         << "3. Sair" << endl
         << "> ";
    do {
        read_again = false;
        cin >> op;
        switch (op) {
            case 1:
                break;
            case 2:
                cout << "\nInsira o ponto de partida" << endl
                     << "> ";
                cin >> *iv;
                cout << "Insira o ponto de destino" << endl
                     << "> ";
                cin >> *fv;
                break;
            case 3:
                exit(1);
                break;
            default:
                read_again = true;
                cout << "Invalido!" << endl
                     << "> ";
        }
    } while (read_again);
}

void search_cut() {
}

void add_to_queue(bool *add, Queue &q, element *x, element *min, int i, int j) {
    // Adiciona na fila caso a flag for verdadeira
    if (*add) {
        x->cost += adj_matrix[x->route[i]][j];  // Soma o custo
        x->route[i + 1] = j;                    // Concatena o vertice

        // Se o custo total for menor que o menor custo, adiciona na fila, caso contrario, poda (caminho ruim)
        if (x->cost < min->cost)
            q.insert(*x);

        /* Para fins de debug (sera removido posteriormente) */
        /*int m = 0;
                        while (x.route[m++] != -1)
                            cout << x.route[m - 1] << " ";
                        cout << endl;*/

        // Restaura nosso elemento
        x->cost -= adj_matrix[x->route[i]][j];
        x->route[i + 1] = -1;
    }
    *add = true;
}

void search_min(element *shortest, int initial_vertex, int final_vertex) {
    Queue found_routes;  // Fila de rotas possiveis
    element x;           // Elemento da filas
    bool add = true;     // Flag p/ adicionar vertice + custo na fila

    // Inicializa todos os elementos de ambos os arrays de rota presentes nas structs com -1
    memset(x.route, -1, TOTAL_LOCATIONS * sizeof(int));
    memset(shortest->route, -1, TOTAL_LOCATIONS * sizeof(int));
    shortest->cost = 999999;

    x.cost = 0;
    x.route[0] = initial_vertex;

    found_routes.insert(x);

    int i = 0;               // Para apontar a ultima aresta inserida na rota
    int j = 0;               // Para percorrer as colunas da nossa matriz
    int k = 0;               // Para auxiliar
    int vertex_counter = 0;  // Para contar o numero de vertices percorridos

    while (!found_routes.is_empty()) {
        x = found_routes.eliminate();

        // Caminha com o contador ate a ultima posicao guardada
        for (i = 0; x.route[i] != -1; i++) {
        }
        i--;  // Se x.route[i] = -1, x.route[i-1] = ultima posicao valida guardada

        /**
        * Verifica se rota eh igual ao ponto de destino
        */
        if (x.route[i] == final_vertex && i > TOTAL_LOCATIONS - 8) {
            // Se o custo atual eh menor que o menor custo guardado, guarda o custo atual e o percurso
            if (x.cost < shortest->cost) {
                shortest->cost = x.cost;
                for (int counter = 0; x.route[counter] != -1; counter++)
                    shortest->route[counter] = x.route[counter];
            }
        } else {
            for (j = 0; j < TOTAL_LOCATIONS; j++) {
                if (adj_matrix[x.route[i]][j] != 0) {
                    if (j == final_vertex && i > TOTAL_LOCATIONS - 8) {
                        add = true;
                    } else {
                        // Se o indice atual da matriz existir em x.route, setar flag p/ n adicionar na fila
                        for (k = 0; x.route[k] != -1; k++) {
                            if (x.route[k] == j) {
                                add = false;
                                break;
                            }
                        }
                    }
                    add_to_queue(&add, found_routes, &x, shortest, i, j);
                }
            }
        }
    }
}

int main() {
    element shortest;    // Nosso menor caminho
    int initial_vertex;  // Vertice de partida
    int final_vertex;    // Vertice de chegada

    read(&initial_vertex, &final_vertex);

    t_start = Clock::now();

    search_min(&shortest, initial_vertex, final_vertex);
    print_shortest(shortest, adj_matrix, final_vertex);

    return 0;
}