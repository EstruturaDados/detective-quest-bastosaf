// ============================================================================
//         PROJETO DETECTIVE QUEST - DESAFIO DE CÓDIGO 
// ============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_HASH 10

// ESTRUTURAS

// Estrutura da sala (nó da árvore da mansão)
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Estrutura para a árvore de pistas (BST)
typedef struct Pista {
    char texto[100];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

// Estrutura para itens da hash (lista encadeada)
typedef struct ItemHash {
    char pista[100];
    char suspeito[50];
    struct ItemHash *prox;
} ItemHash;

// Tabela hash
typedef struct {
    ItemHash *tabela[TAM_HASH];
} HashTable;

// DECLARAÇÕES DE FUNÇÕES

// --- Funções de utilidade ---
int funcaoHash(const char *chave);

// --- Árvores de salas ---
Sala *criarSala(const char *nome, const char *pista);
void explorarSalas(Sala *sala, Pista **raizPistas, HashTable *ht);

// --- Árvores de pistas (BST) ---
Pista *inserirPista(Pista *raiz, const char *texto);
void listarPistas(Pista *raiz);

// --- Tabela hash ---
void inicializarHash(HashTable *ht);
void inserirNaHash(HashTable *ht, const char *pista, const char *suspeito);
const char *buscarSuspeito(HashTable *ht, const char *pista);
void listarAssociacoes(HashTable *ht);

// --- Fase final ---
void verificarSuspeitoFinal(Pista *raiz, HashTable *ht);

// IMPLEMENTAÇÃO DAS FUNÇÕES

// --- Funções auxiliares ---
int funcaoHash(const char *chave) {
    int soma = 0;
    int i;
    for (i = 0; chave[i] != '\0'; i++)
        soma += tolower(chave[i]);
    return soma % TAM_HASH;
}

// --- Criação de sala ---
Sala *criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala *) malloc(sizeof(Sala));
    if (!nova) {
        printf("Erro de memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// --- Inserir pista na BST ---
Pista *inserirPista(Pista *raiz, const char *texto) {
    if (raiz == NULL) {
        Pista *nova = (Pista *) malloc(sizeof(Pista));
        strcpy(nova->texto, texto);
        nova->esq = nova->dir = NULL;
        return nova;
    }
    if (strcmp(texto, raiz->texto) < 0)
        raiz->esq = inserirPista(raiz->esq, texto);
    else if (strcmp(texto, raiz->texto) > 0)
        raiz->dir = inserirPista(raiz->dir, texto);
    return raiz;
}

// --- Exibir pistas em ordem alfabética ---
void listarPistas(Pista *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esq);
        printf("%s\n", raiz->texto);
        listarPistas(raiz->dir);
    }
}

// --- Inicializar tabela hash ---
void inicializarHash(HashTable *ht) {
    int i;
    for (i = 0; i < TAM_HASH; i++)
        ht->tabela[i] = NULL;
}

// --- Inserir par pista e suspeito na hash ---
void inserirNaHash(HashTable *ht, const char *pista, const char *suspeito) {
    int indice = funcaoHash(pista);
    ItemHash *novo = (ItemHash *) malloc(sizeof(ItemHash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = ht->tabela[indice];
    ht->tabela[indice] = novo;
}

// --- Buscar suspeito a partir da pista ---
const char *buscarSuspeito(HashTable *ht, const char *pista) {
    int indice = funcaoHash(pista);
    ItemHash *atual = ht->tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

// --- Listar todas as associações ---
void listarAssociacoes(HashTable *ht) {
    printf("\n===== Associações de Pistas e Suspeitos =====\n");
    int i;
    for (i = 0; i < TAM_HASH; i++) {
        ItemHash *atual = ht->tabela[i];
        while (atual != NULL) {
            printf("Pista: %-30s | Suspeito: %s\n", atual->pista, atual->suspeito);
            atual = atual->prox;
        }
    }
}

// --- Explorar as salas ---
void explorarSalas(Sala *sala, Pista **raizPistas, HashTable *ht) {
    if (sala == NULL) return;

    printf("\n Você entrou na sala: %s\n", sala->nome);
    if (strlen(sala->pista) > 0) {
        printf("Encontrou uma pista: %s\n", sala->pista);
        *raizPistas = inserirPista(*raizPistas, sala->pista);
    }

    char escolha;
    printf("\nDeseja ir para (e) esquerda, (d) direita ou (s) sair? ");
    scanf(" %c", &escolha);

    if (escolha == 'e')
        explorarSalas(sala->esquerda, raizPistas, ht);
    else if (escolha == 'd')
        explorarSalas(sala->direita, raizPistas, ht);
    else
        printf("\nEncerrando exploração...\n");
}

// --- Julgamento final ---
void verificarSuspeitoFinal(Pista *raiz, HashTable *ht) {
    char acusacao[50];
    printf("\nDigite o nome do suspeito que deseja acusar: ");
    scanf(" %[^\n]", acusacao);

    int contador = 0;

    if (raiz == NULL)
        return;

    // Busca nas pistas da BST
    if (buscarSuspeito(ht, raiz->texto) &&
        strcmp(buscarSuspeito(ht, raiz->texto), acusacao) == 0)
        contador++;

    if (raiz->esq)
        verificarSuspeitoFinal(raiz->esq, ht);
    if (raiz->dir)
        verificarSuspeitoFinal(raiz->dir, ht);

    // Resultado final (só exibe na raiz principal)
    if (strcmp(raiz->texto, "Pegadas sujas no tapete") == 0) {
        if (contador >= 2)
            printf("\n Acusação correta! %s é o culpado!\n", acusacao);
        else
            printf("\n Acusação incorreta. %s parece inocente.\n", acusacao);
    }
}

int main() {
    // --- Criar mapa da mansão ---
    Sala *hall = criarSala("Hall de Entrada", "Pegadas sujas no tapete");
    hall->esquerda = criarSala("Biblioteca", "Livro rasgado com iniciais");
    hall->direita = criarSala("Cozinha", "Faca com marcas de sangue");
    hall->esquerda->esquerda = criarSala("Jardim", "Luvas molhadas");
    hall->esquerda->direita = criarSala("Escritório", "Documento rasgado");
    hall->direita->esquerda = criarSala("Sala de Jantar", "Copo quebrado");
    hall->direita->direita = criarSala("Porão", "Chave antiga");

    // --- Inicializar estruturas ---
    Pista *raizPistas = NULL;
    HashTable ht;
    inicializarHash(&ht);

    // --- Inserir associações pista ? suspeito ---
    inserirNaHash(&ht, "Pegadas sujas no tapete", "Jardineiro");
    inserirNaHash(&ht, "Livro rasgado com iniciais", "Bibliotecário");
    inserirNaHash(&ht, "Faca com marcas de sangue", "Cozinheiro");
    inserirNaHash(&ht, "Luvas molhadas", "Jardineiro");
    inserirNaHash(&ht, "Documento rasgado", "Secretária");
    inserirNaHash(&ht, "Copo quebrado", "Empregada");
    inserirNaHash(&ht, "Chave antiga", "Zelador");

    printf("=== Bem-vindo à Mansão Misteriosa ===\n");
    explorarSalas(hall, &raizPistas, &ht);

    printf("\n=== Pistas coletadas ===\n");
    listarPistas(raizPistas);

    listarAssociacoes(&ht);

    verificarSuspeitoFinal(raizPistas, &ht);

    return 0;
}

