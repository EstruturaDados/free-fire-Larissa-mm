#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato (Busca Sequencial)
// Sistema de inventário com Structs e Vetores
 
#define MAX_ITENS 10

// 1. Definição da struct (Requisito funcional)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções obrigatórias
void inserirItem(Item mochila[], int *contador); 
void removerItem(Item mochila[], int *contador);
void listarItens(Item mochila[], int contador);
void buscarItem(Item mochila[], int contador);   
void limparBuffer();
void aguardarEnter();

int main() {
    Item mochila[MAX_ITENS]; // Vetor de structs
    int totalItens = 0;
    int opcao;

    do {
        // Menu de Usabilidade 
        printf("\n====================================================\n");
        printf("     MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("====================================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, MAX_ITENS);

        printf("1. Inserir Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n"); 
        printf("0. Sair\n");
        printf("----------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens); 
                aguardarEnter();
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                aguardarEnter();
                break;
            case 3:
                listarItens(mochila, totalItens);
                aguardarEnter();
                break;
            case 4:
                buscarItem(mochila, totalItens); 
                aguardarEnter();
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                aguardarEnter();
        }

    } while (opcao != 0);

    return 0;
}

// Função 1: Inserir (Cadastro de itens)
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel carregar mais loot.\n");
        return;
    }

    printf("\n--- Inserir Novo Loot ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[*contador].nome, 30, stdin);
    mochila[*contador].nome[strcspn(mochila[*contador].nome, "\n")] = 0;

    printf("Tipo do item (arma, municao, cura): ");
    fgets(mochila[*contador].tipo, 20, stdin);
    mochila[*contador].tipo[strcspn(mochila[*contador].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[*contador].quantidade);
    limparBuffer();

    printf("\nItem '%s' inserido com sucesso!\n", mochila[*contador].nome);
    
    (*contador)++;
}

// Função 2: Remover (Exclusão com deslocamento de vetor)
void removerItem(Item mochila[], int *contador) {
    char nomeBusca[30];
    int encontrado = 0;

    if (*contador == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Remover Item ---\n");
    printf("Nome do item para remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Busca sequencial para encontrar e remover
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Realoca os itens para não deixar buraco no vetor
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*contador)--;
            encontrado = 1;
            printf("\nItem '%s' removido da mochila.\n", nomeBusca);
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila!\n");
    }
}

// Função 3: Listar (Exibição formatada)
void listarItens(Item mochila[], int contador) {
    printf("\n--- CONTEUDO DA MOCHILA (%d/%d) ---\n", contador, MAX_ITENS);
    printf("----------------------------------------------------\n");
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QTD");
    
    if (contador == 0) {
        printf("     Mochila Vazia\n");
    } else {
        for (int i = 0; i < contador; i++) {
            printf("%-20s | %-15s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("----------------------------------------------------\n");
}

// Função 4: Buscar (Busca Sequencial )
void buscarItem(Item mochila[], int contador) {
    char nomeBusca[30];
    int encontrado = 0;

    if (contador == 0) {
        printf("\nMochila vazia. Nada para buscar.\n");
        return;
    }

    printf("\n--- Buscar Item ---\n");
    printf("Digite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Laço de repetição para percorrer o vetor ( Busca sequencial)
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[ITEM LOCALIZADO]\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break; // Encerra o loop ao encontrar
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

// Funções auxiliares
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void aguardarEnter() {
    printf("\nPressione Enter para continuar...");
    getchar();
}