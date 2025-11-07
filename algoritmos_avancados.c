// ============================================================================
//         PROJETO DETECTIVE QUEST - DESAFIO DE CÓDIGO 
// ============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estrutura para cada sala da mansão */
typedef struct No {
    char nome[50];
    struct No* esquerda;
    struct No* direita;
} No;

/* Cria dinamicamente uma sala com um nome */
No* criarSala(const char* valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novo->nome, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

/* Permite explorar interativamente a mansão */
void explorarSalas(No* atual) {
    char opcao;
    char visitadas[20][50];  /* Armazena até 20 salas visitadas */
    int contador = 0;
    int i; /* variável do loop declarada fora do for */

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);
        strcpy(visitadas[contador], atual->nome);
        contador++;

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Não há mais saídas.\n");
            break;
        }

        printf("Escolha o caminho (e = esquerda, d = direita, s = sair): ");
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
        } else if (opcao == 's') {
            printf("Saindo da exploração...\n");
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }

    /* Exibe todas as salas visitadas */
    printf("\n=== Salas visitadas ===\n");
    for (i = 0; i < contador; i++) {
        printf("- %s\n", visitadas[i]);
    }
}

/* Libera toda a memória da árvore */
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

int main(void) {
    /* Construção fixa da árvore (mapa da mansão) */
    No* raiz = criarSala("Hall de Entrada");
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Biblioteca");

    raiz->esquerda->esquerda = criarSala("Cozinha");
    raiz->esquerda->direita = criarSala("Sala de Jantar");

    raiz->direita->esquerda = criarSala("Escritório");
    raiz->direita->direita = criarSala("Jardim de Inverno");

    printf("=== Bem-vindo à Mansão Misteriosa ===\n");
    explorarSalas(raiz);

    liberar(raiz);
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

