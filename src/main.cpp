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
#include <ctime>
#include <iostream>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::milliseconds milliseconds;

typedef struct {
    int route[42];      // 42 p/ caso max.
    unsigned int cost;  // Custo do percurso
} route;

typedef route element;
#include "..\lib\dyn_queue.h"

/**
 * /INDICES POR REGIAO /
 * 
 * NOROESTE     NORDESTE
 * [00-08]      [30-41]
 * 
 * SUDOESTE     SUDESTE
 * [09-17]      [18-29]
 */
static char locations[42][20] = {
    /*00*/ {"Boise"},
    /*01*/ {"Denver"},
    /*02*/ {"Lake Tahoe"},
    /*03*/ {"Portland"},
    /*04*/ {"Salt Lake City"},
    /*05*/ {"San Francisco"},
    /*06*/ {"Seatle"},
    /*07*/ {"Vail"},
    /*08*/ {"Yellowstone"},
    /*09*/ {"Albuquerque"},
    /*10*/ {"Aspen"},
    /*11*/ {"Colorado Springs"},
    /*12*/ {"Grand Canyon"},
    /*13*/ {"Las Vegas"},
    /*14*/ {"Los Angeles"},
    /*15*/ {"Palm Springs"},
    /*16*/ {"Phoenix"},
    /*17*/ {"San Diego"},
    /*18*/ {"Atlanta"},
    /*19*/ {"Dallas"},
    /*20*/ {"Fort Lauderdale"},
    /*21*/ {"Houston"},
    /*22*/ {"Little Rock"},
    /*23*/ {"Memphis"},
    /*24*/ {"Miami"},
    /*25*/ {"Nashville"},
    /*26*/ {"Nova Orleans"},
    /*27*/ {"Orlando"},
    /*28*/ {"San Antonio"},
    /*29*/ {"St. Louis"},
    /*30*/ {"Albany"},
    /*31*/ {"Boston"},
    /*32*/ {"Chicago"},
    /*33*/ {"Detroit"},
    /*34*/ {"Indianopolis"},
    /*35*/ {"Kansas City"},
    /*36*/ {"Milwaukee"},
    /*37*/ {"Minneapolis"},
    /*38*/ {"Nova York"},
    /*39*/ {"Ohama"},
    /*40*/ {"Richmond"},
    /*41*/ {"Washington"}};

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
void print_shortest(element s, int am[][42], int destiny, milliseconds t) {
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
    cout << endl
         << "Tempo de processamento: " << t.count() << " ms" << endl
         << "------------------------";
}

/**
 * Copia um elemento para o outro
 * 
 * @param a Elemento que sera copiado
 * @param b Elemento que recebera a copia
 */
void copy_element(element a, element *b) {
    b->cost = a.cost;
    for (int counter = 0; counter < 42; counter++)
        b->route[counter] = a.route[counter];
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
         << endl
         << "> ";
    do {
        cin >> op;
        switch (op) {
            case 1:
                break;
            case 2:
                cout << "Insira o ponto de partida" << endl
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
                cout << "Favor inserir uma opcao valida!" << endl
                     << "> ";
        }
    } while (read_again);
}

int main() {
    // Matriz de adjacencia p/ 42 cidades
    int adj_matrix[][42] = {/*00*/ {0, 0, 420, 420, 0, 0, 500, 0, 670, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*01*/ {0, 0, 0, 0, 530, 0, 0, 160, 930, 0, 170, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 540, 0, 0},
                            /*02*/ {420, 0, 0, 580, 520, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 780, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*03*/ {420, 0, 580, 0, 0, 640, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*04*/ {0, 530, 520, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 420, 0, 0, 660, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*05*/ {0, 0, 300, 640, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 380, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*06*/ {500, 0, 0, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*07*/ {0, 160, 0, 0, 0, 0, 0, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1340, 0, 0, 0, 0},
                            /*08*/ {670, 930, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*09*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*10*/ {0, 170, 0, 0, 0, 0, 0, 800, 0, 0, 0, 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*11*/ {0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 180, 0, 0, 0, 0, 0, 0, 0, 0, 730, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*12*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 470, 0, 440, 360, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*13*/ {0, 0, 0, 0, 420, 0, 0, 0, 0, 0, 0, 0, 470, 0, 270, 290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*14*/ {0, 0, 0, 0, 0, 380, 0, 0, 0, 0, 0, 0, 0, 270, 0, 160, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*15*/ {0, 0, 780, 0, 0, 0, 0, 0, 0, 0, 0, 0, 440, 290, 160, 0, 0, 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*16*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 350, 0, 0, 360, 0, 0, 0, 0, 350, 0, 1070, 0, 0, 0, 0, 0, 0, 0, 0, 990, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*17*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 140, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*18*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 790, 0, 0, 0, 210, 0, 240, 470, 440, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 560, 0},
                            /*19*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 730, 1070, 0, 790, 0, 0, 250, 320, 0, 0, 0, 0, 0, 280, 0, 0, 0, 0, 0, 0, 550, 0, 0, 0, 0, 0, 0},
                            /*20*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 0, 0, 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*21*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250, 0, 0, 0, 0, 0, 0, 530, 0, 310, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*22*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320, 0, 0, 0, 140, 0, 0, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*23*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 390, 0, 0, 0, 140, 0, 0, 210, 0, 0, 0, 290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*24*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 0, 0, 0, 0, 0, 860, 230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*25*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0, 210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 290, 0, 0, 0, 0, 0, 710, 0},
                            /*26*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 470, 0, 0, 530, 0, 0, 860, 0, 0, 640, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*27*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 440, 0, 180, 0, 0, 0, 230, 0, 640, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*28*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 990, 0, 0, 280, 0, 310, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            /*29*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 400, 290, 0, 0, 0, 0, 0, 0, 0, 0, 300, 0, 250, 250, 0, 0, 0, 0, 0, 0},
                            /*30*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 170, 0, 650, 0, 0, 0, 0, 150, 0, 0, 0},
                            /*31*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 170, 0, 0, 0, 0, 0, 0, 0, 210, 0, 0, 0},
                            /*32*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 300, 0, 0, 0, 280, 180, 0, 90, 410, 0, 470, 0, 700},
                            /*33*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 650, 0, 280, 0, 0, 0, 0, 0, 640, 0, 0, 530},
                            /*34*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 290, 0, 0, 0, 250, 0, 0, 180, 0, 0, 0, 0, 0, 0, 0, 0, 590},
                            /*35*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 550, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 190, 0, 0},
                            /*36*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 0, 0, 0, 340, 0, 0, 0, 0},
                            /*37*/ {0, 0, 0, 0, 0, 0, 0, 0, 1340, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 410, 0, 0, 0, 340, 0, 0, 380, 0, 0},
                            /*38*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150, 210, 0, 640, 0, 0, 0, 0, 0, 0, 0, 240},
                            /*39*/ {0, 540, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 470, 0, 0, 190, 0, 380, 0, 0, 0, 0},
                            /*40*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 560, 0, 0, 0, 0, 0, 0, 710, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200},
                            /*41*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 700, 530, 590, 0, 0, 0, 240, 0, 200, 0}};

    Queue found_routes;         // Fila de rotas possiveis
    element x;                  // Elemento da fila
    element shortest;           // Nosso menor caminho
    int initial_vertex;         // Vertice de partida
    int final_vertex;           // Vertice de chegada
    bool add_to_queue = true;   // Flag p/ adicionar vertice + custo na fila
    Clock::time_point t_start;  // Guardara o inicio da contagem de tempo
    Clock::time_point t_stop;   // Guardara o inicio da contagem de tempo

    /* -------------------- */

    // Inicializa todos os elementos de ambas os arrays de rota presentes nas structs com -1
    memset(x.route, -1, 42 * sizeof(int));
    memset(shortest.route, -1, 42 * sizeof(int));
    shortest.cost = 999999;

    read(&initial_vertex, &final_vertex);
    x.cost = 0;
    x.route[0] = initial_vertex;

    found_routes.insert(x);

    int i = 0;               // Para apontar a ultima aresta inserida na rota
    int j = 0;               // Para percorrer as colunas da nossa matriz
    int k = 0;               // Para auxiliar
    int vertex_counter = 0;  // Para contar o numero de vertices percorridos

    t_start = Clock::now();
    while (!found_routes.is_empty()) {
        vertex_counter++;
        x = found_routes.eliminate();

        // Caminha com o contador ate a ultima posicao guardada
        for (i = 0; x.route[i] != -1; i++) {
        }
        i--;  // Se x.route[i] = -1, x.route[i-1] = ultima posicao valida guardada

        /**
        * Verifica se rota eh igual ao ponto de destino
        */
        if (x.route[i] == final_vertex) {
            // Se o custo atual eh menor que o menor custo guardado, guarda o custo atual e o percurso
            if (x.cost < shortest.cost) {
                shortest.cost = x.cost;
                for (int counter = 0; x.route[counter] != -1; counter++)
                    shortest.route[counter] = x.route[counter];
            }
        } else {
            for (j = 0; j < 42; j++) {
                if (adj_matrix[x.route[i]][j] != 0) {
                    // Se o indice atual da matriz existir em x.route, setar flag p/ n adicionar na fila
                    for (k = 0; x.route[k] != -1; k++) {
                        if (x.route[k] == j)
                            add_to_queue = false;
                    }
                    // Adiciona na fila caso a flag for verdadeira
                    if (add_to_queue) {
                        element temp;

                        // Copia nosso elemento atual
                        copy_element(x, &temp);
                        x.cost += adj_matrix[x.route[i]][j];  // Soma o custo
                        x.route[i + 1] = j;                   // Concatena o vertice

                        // Se o custo total atal for menor que o menor custo, adiciona na fila
                        if (x.cost < shortest.cost)
                            found_routes.insert(x);

                        /* Para fins de debug (sera removido posteriormente) */
                        /*int m = -1;
                        while (x.route[m++] != -1)
                            cout << x.route[m] << " ";
                        cout << endl;*/

                        // Restaura nosso elemento atual
                        copy_element(temp, &x);
                    }

                    add_to_queue = true;
                }
            }
        }
    }
    t_stop = Clock::now();
    milliseconds ms = chrono::duration_cast<milliseconds>(t_stop - t_start);

    print_shortest(shortest, adj_matrix, final_vertex, ms);
    return 0;
}