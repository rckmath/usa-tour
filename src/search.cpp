/**
 * Adiciona o possivel caminho na fila
 * 
 * @param add
 * @param q Fila que guardara as N possibilidades de caminhos
 * @param x Struct que recebera a possibilidade da busca atual
 * @param min Struct que guarda o menor caminho
 * @param i Posicao do ultimo elemento do vetor de rotas da struct x
 * @param j Posicao do adjacente que conecta com o ultimo elemento da sequencia de caminhos possiveis
 */
void add_to_queue(bool *add, Stack &s, Queue &q, element *x, element *min, int i, int j, int op) {
    // Adiciona na fila caso a flag for verdadeira
    if (*add) {
        x->cost += adj_matrix[x->route[i]][j];  // Soma o custo
        x->route[i + 1] = j;                    // Concatena o vertice

        // Se o custo total for menor que o menor custo, adiciona na fila, caso contrario, poda (caminho ruim)
        if (x->cost < min->cost) {
            if (op == 2)
                push(s, *x);
            else
                q.insert(*x);
        }

        // Restaura nosso elemento
        x->cost -= adj_matrix[x->route[i]][j];
        x->route[i + 1] = -1;
    }
    *add = true;
}

/**
 * Verifica se o vertice ja foi inserido no percurso montado
 * 
 * @param x Struct que recebera a possibilidade da busca atual
 * @param j Posicao do adjacente que conecta com o ultimo elemento da sequencia de caminhos possiveis
 */
bool skip_vertex(element *x, int j) {
    // Se o indice atual da matriz existir em x.route, setar flag p/ n adicionar na fila
    for (int k = 0; x->route[k] != -1; k++) {
        if (x->route[k] == j) {
            return false;
        }
    }
    return true;
}

/**
 * Processa a busca
 * 
 * @param s Pilha que guardara as N possibilidades de caminhos
 * @param q Fila que guardara as N possibilidades de caminhos
 * @param x Struct que recebera a possibilidade da busca atual
 * @param min Struct que guarda o menor caminho
 * @param i Posicao do ultimo elemento do vetor de rotas da struct x
 * @param op Opcao de busca
 * @param sub Fator de subtracao
 */
void process_search(Stack &s, Queue &q, element *x, element *min, int i, int op, int sub) {
    int j = 0;        // Para percorrer as colunas da nossa matriz
    bool add = true;  // Flag p/ adicionar vertice + custo na fila

    for (j = 0; j < size; j++) {
        if (adj_matrix[x->route[i]][j] != 0) {
            if (op == 3) {
                add = skip_vertex(x, j);
            } else {
                if (j == x->route[0] && i >= (size - sub)) {
                    add = true;
                } else {
                    add = skip_vertex(x, j);
                }
            }
            add_to_queue(&add, s, q, x, min, i, j, op);
        }
    }
}

/**
 * Verifica se o ultimo elemento da rota eh o destino desejado, senao chama o processo de busca
 * 
 * @param x Struct que recebera a possibilidade da busca atual
 * @param min Struct que guarda o menor caminho
 * @param q Fila que guardara as N possibilidades de caminhos
 * @param s Pilha que guardara as N possibilidades de caminhos
 * @param final_vertex Vertice final/destino
 * @param op Opcao de busca
 * @param sub Fator de subtracao
 */
void verify(element *x, element *min, Queue &q, Stack &s, int final_vertex, int op, int sub) {
    int i;  // Para apontar a ultima aresta inserida na rota

    // Caminha com o contador ate a ultima posicao guardada
    for (i = 0; x->route[i] != -1; i++) {
    }
    i--;  // Se x.route[i] = -1, x.route[i-1] = ultima posicao valida guardada

    /**
    * Verifica se rota eh igual ao ponto de destino
    */
    if (x->route[i] == final_vertex && i >= (size - sub)) {
        // Se o custo atual eh menor que o menor custo guardado, guarda o custo atual e o percurso
        if (x->cost < min->cost) {
            min->cost = x->cost;
            for (int j = 0; x->route[j] != -1; j++)
                min->route[j] = x->route[j];
        }
    } else
        process_search(s, q, x, min, i, op, sub);
}

/**
 * Busca o menor custo
 * 
 * @param min Struct que guarda o menor caminho
 * @param initial_vertex Vertice inicial/inicio
 * @param final_vertex Vertice final/destino
 * @param op Opcao de busca
 */
void search_min(element *min, int initial_vertex, int final_vertex, int op) {
    Stack found_routes_s;  // Pilha de rotas possiveis (se op 1)
    Queue found_routes_q;  // Fila de rotas possiveis (se op != 1)
    element x;             // Elemento
    int sub = 42;          // Fator de subtração

    // As operacoes de busca serao feitas de acordo com a opcao do usuario
    if (op == 1) {
        size -= 1;
        sub = 7;
    } else {
        initStack(found_routes_s);
        if (op == 2)
            sub = 3;
    }

    // Inicializa todos os elementos de ambos os arrays de rota presentes nas structs com -1
    memset(x.route, -1, size * sizeof(int));
    memset(min->route, -1, size * sizeof(int));
    min->cost = 999999;

    x.cost = 0;
    x.route[0] = initial_vertex;

    cout << endl
         << "Por favor aguarde, buscando rotas..." << endl;

    if (op == 2) {
        push(found_routes_s, x);
        while (!isEmpty(found_routes_s)) {
            x = pop(found_routes_s);
            verify(&x, min, found_routes_q, found_routes_s, final_vertex, op, sub);
        }
    } else {
        found_routes_q.insert(x);
        while (!found_routes_q.is_empty()) {
            x = found_routes_q.eliminate();
            verify(&x, min, found_routes_q, found_routes_s, final_vertex, op, sub);
        }
    }
}