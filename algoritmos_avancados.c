// ============================================================================
//         PROJETO DETECTIVE QUEST - DESAFIO DE CÓDIGO 
// ============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estrutura para cada sala da mansão */
typedef struct Sala {
    char nome[50];
    char pista[100];  /* Pista associada à sala */
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/* Estrutura para a árvore de pistas (BST) */
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

/* === Funções da mansão === */

/* Cria dinamicamente uma sala com nome e pista */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/* === Funções da árvore de pistas === */

/* Cria um novo nó de pista */
Pista* criarPista(const char* texto) {
    Pista* nova = (Pista*) malloc(sizeof(Pista));
    if (nova == NULL) {
        printf("Erro ao alocar memória para pista!\n");
        exit(1);
    }
    strcpy(nova->texto, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/* Insere uma pista na árvore BST de forma ordenada */
Pista* inserirPista(Pista* raiz, const char* texto) {
    if (raiz == NULL) {
        return criarPista(texto);
    }
    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } else if (strcmp(texto, raiz->texto) > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    return raiz; /* Sem duplicatas */
}

/* Exibe as pistas em ordem alfabética (em-ordem) */
void listarPistas(Pista* raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        listarPistas(raiz->direita);
    }
}

/* Libera memória da BST de pistas */
void liberarPistas(Pista* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

/* === Funções de exploração === */

/* Explora a mansão e coleta pistas */
void explorarSalas(Sala* atual, Pista** arvorePistas) {
    char opcao;
    char visitadas[20][50];
    int contador = 0;
    int i;  /* compatível com C99 e C90 */

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);
        strcpy(visitadas[contador], atual->nome);
        contador++;

        /* Se a sala tem uma pista, coletar e inserir na BST */
        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: \"%s\"\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        /* Se não há caminhos, fim da exploração */
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Não há mais saídas.\n");
            break;
        }

        printf("Escolha o caminho (e = esquerda, d = direita, v = ver pistas, s = sair): ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há sala à esquerda!\n");
            }
        } else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há sala à direita!\n");
            }
        } else if (opcao == 'v') {
            printf("\n=== Pistas Coletadas ===\n");
            if (*arvorePistas == NULL) {
                printf("(Nenhuma pista coletada ainda)\n");
            } else {
                listarPistas(*arvorePistas);
            }
        } else if (opcao == 's') {
            printf("Saindo da exploração...\n");
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }

    /* Exibir histórico de salas visitadas */
    printf("\n=== Salas Visitadas ===\n");
    for (i = 0; i < contador; i++) {
        printf("- %s\n", visitadas[i]);
    }

    /* Exibir todas as pistas coletadas ao final */
    printf("\n=== Pistas Finais Coletadas ===\n");
    if (*arvorePistas == NULL) {
        printf("(Nenhuma pista coletada)\n");
    } else {
        listarPistas(*arvorePistas);
    }
}

/* Libera memória da árvore de salas */
void liberarSalas(Sala* raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

int main(void) {
    /* Construindo a árvore da mansão */
    Sala* hall = criarSala("Hall de Entrada", "Chave enferrujada");
    hall->esquerda = criarSala("Sala de Estar", "Luvas rasgadas");
    hall->direita = criarSala("Biblioteca", "Livro rasgado");

    hall->esquerda->esquerda = criarSala("Cozinha", "Copo quebrado");
    hall->esquerda->direita = criarSala("Sala de Jantar", "");
    hall->direita->esquerda = criarSala("Escritório", "Envelope aberto");
    hall->direita->direita = criarSala("Jardim de Inverno", "Pegadas na terra");

    Pista* arvorePistas = NULL;

    printf("=== Bem-vindo à Mansão Misteriosa ===\n");
    explorarSalas(hall, &arvorePistas);

    liberarSalas(hall);
    liberarPistas(arvorePistas);
    return 0;
}

// int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

//     return 0;
// }

