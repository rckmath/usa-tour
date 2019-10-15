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
#include <iomanip>
#include <iostream>

#pragma comment(linker, "/STACK: 2000000")
#pragma comment(linker, "/HEAP: 2000000")

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::milliseconds milliseconds;

#include "base.cpp"
#include "search.cpp"

Clock::time_point t_start;  // Guardara o inicio da contagem de tempo
Clock::time_point t_stop;   // Guardara o final da contagem de tempo

void build_matrix(char *);
char *get_place_name(int);
int get_edge_weight(int, int);
void print_shortest(element, int);
void display_places();
int read(int *, int *);

int main() {
#ifdef _WIN32
    system("Color 0A");
#endif

    element shortest;    // Nosso menor caminho
    int initial_vertex;  // Vertice de partida
    int final_vertex;    // Vertice de chegada

    int op = read(&initial_vertex, &final_vertex);

    build_matrix("..\\lib\\matrix.txt");

    t_start = Clock::now();

    int *caminho = (int *)calloc(size, sizeof(int));

    search_min(&shortest, initial_vertex, final_vertex, op);
    print_shortest(shortest, final_vertex);

    cout << endl
         << endl;
    system("pause");
    return 0;
}

/**
 * Le do arquivo e define nossa matriz
 * 
 * @param adj Caminho do arquivo que contem os elementos da matriz
 */
void build_matrix(char *adj) {
    FILE *fp = fopen(adj, "r");

    fscanf(fp, "%d\n", &size);

    adj_matrix = (int **)calloc(size, sizeof(int));

    for (int i = 0; i < size; i++) {
        adj_matrix[i] = (int *)calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            fscanf(fp, "%d ", &adj_matrix[i][j]);
        }
    }
    fclose(fp);
}

/**
 * Busca e retorna o nome do local
 *
 * @param index ID/indice do local
 * @return Nome do local
 */
char *get_place_name(int index) {
    return locations[index];
}

/**
 * Busca e retorna o peso da aresta
 *
 * @param i Linha da matriz (cidade A)
 * @param j Coluna da matriz (cidade B)
 * @return Peso da aresta na posicao xy
 */
int get_edge_weight(int i, int j) {
    return adj_matrix[i][j];
}

void display_places() {
    for (int i = 1; i <= 14; i++) {
        printf("%d. %-25s%d. %-25s%d. %-25s\n", i, get_place_name(i - 1), i + 14, get_place_name(i + 13), i + 28, get_place_name(i + 27));
    }
}

/**
 * Mostra a menor rota na tela (prototipo)
 *
 * @param s Elemento contendo vetor com IDs das cidades do menor caminho e o menor custo
 * @param destiny ID do local de destino
 */
void print_shortest(element s, int destiny) {
    system("clear || cls");
    int i = 0;

    cout << "---- MENOR PERCURSO ----" << endl
         << "\nDe: " << get_place_name(s.route[0]) << endl
         << "Para: " << get_place_name(destiny) << endl
         << "\nRota completa:\n\n";
    while (s.route[i++] != -1) {
        if (s.route[i] != -1) {
            cout << get_place_name(s.route[i - 1]);
            cout << " -> " << get_place_name(s.route[i]) << " (" << get_edge_weight(s.route[i - 1], s.route[i]) << " km)" << endl;
        } else
            break;
    }
    cout << "\nDistancia total: " << s.cost << " km";

    t_stop = Clock::now();
    milliseconds ms = chrono::duration_cast<milliseconds>(t_stop - t_start);
    cout << endl
         << "\nTempo de processamento: " << ms.count() / 1000.0 << " seg" << endl
         << "Num. de cidades percorridas: " << i - 1 << endl
         << "\n------------------------";
}

/**
 * Apresenta o menu e le as opcoes de usuario
 *
 * @param iv Vertice inicial
 * @param fv Vertice final
 * @return Retorna a opcao do usuario
 */
int read(int *iv, int *fv) {
    int op;
    bool read_again = false;

    cout << "1. Fazer tour atraves dos EUA (busca rapida, 83% das cidades, tempo < 60s)" << endl
         << "2. Fazer tour atraves dos EUA (busca lenta, 95% das cidades, tempo > 180s)" << endl
         << "3. Buscar menor percurso entre dois lugares" << endl
         << "4. Sair" << endl
         << "> ";
    do {
        read_again = false;
        cin >> op;
        cout << endl;
        if (op != 4) display_places();
        switch (op) {
            case 1:
            case 2:
                cout << "\nInsira o ponto de partida" << endl
                     << "> ";
                cin >> *iv;
                *iv -= 1;
                *fv = *iv;
                break;
            case 3:
                cout << "\nInsira o ponto de partida" << endl
                     << "> ";
                cin >> *iv;
                *iv -= 1;
                cout << "Insira o ponto de destino" << endl
                     << "> ";
                cin >> *fv;
                *fv -= 1;
                break;
            case 4:
                exit(1);
                break;
            default:
                read_again = true;
                cout << "Invalido, insira novamente!" << endl
                     << "> ";
        }
    } while (read_again);
    return op;
}