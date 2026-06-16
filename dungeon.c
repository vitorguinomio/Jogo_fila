#include "dungeon.h"

void exibirFilaTurnos(Turno* frente){
    printf("\n=== ORDEM DE TURNOS ===\n");

    if (frente == NULL ){
        printf("A fila de batalha esta vazia. Nenhum combate ativo.\n");
        printf("=======================\n");
        return;
    }
    Turno* atual = frente;
    int posicao =1;

    while(atual != NULL){
        printf("%d. %s\n", posicao, atual->personagem);
        atual = atual->proximo;
        posicao++;
    }
    printf("=======================\n");
}


void enfileirarTurno(Turno** frente, Turno** tras, const char* nome) {
    Turno* novoTurno = (Turno*)malloc(sizeof(Turno));
    
    if (novoTurno == NULL) {
        printf("[ERRO] Falha ao alocar memoria para o turno!\n");
        return;
    }

    strncpy(novoTurno->personagem, nome, sizeof(novoTurno->personagem) - 1);
    novoTurno->personagem[sizeof(novoTurno->personagem) - 1] = '\0'; // Garante o fim da string
    novoTurno->proximo = NULL; 

    // 3. Insere na estrutura
    if (*frente == NULL) {
        *frente = novoTurno;
        *tras = novoTurno;
    } else {
        (*tras)->proximo = novoTurno;
        *tras = novoTurno;
    }

    printf("Personagem '%s' entrou na fila de batalha.\n", nome);
}


void desenfileirarTurno(Turno** frente, Turno** tras) {
    if (*frente == NULL) {
        printf("[AVISO] A fila ja esta vazia! Nao ha turnos para passar.\n");
        return;
    }

    Turno* turnoRemovido = *frente;
    
    printf("O turno de '%s' acabou. Removendo da fila...\n", turnoRemovido->personagem);

    *frente = (*frente)->proximo;

    if (*frente == NULL) {
        *tras = NULL;
    }

    free(turnoRemovido);
}

void pushInventario(Item** topo, const char* nomeItem){
    Item* novoItem =  (Item*)malloc(sizeof(Item));
    if(novoItem == NULL){
        printf("[ERRO] O inventario esta cheio! Falha de memoria.\n");
        return;
    }
    strncpy(novoItem->nome, nomeItem, sizeof(novoItem->nome) - 1);
    novoItem->nome[sizeof(novoItem->nome) - 1] = '\0';

    novoItem->abaixo = *topo;
    *topo = novoItem;

    printf("Item '%s' guardado no topo do inventario.\n", nomeItem);
}

void popIventario(Item** topo){
    if(*topo == NULL){
        printf("[AVISO] O inventario esta vazio! Nao ha itens para usar.\n");
        return;
    }

    Item* itemUsado = *topo;
    printf("Voce usou o item/magia: '%s'\n", itemUsado->nome);
    *topo = (*topo)->abaixo;
    free(itemUsado);

}

void exibirInventario(Item* topo){
    printf("\n=== INVENTARIO (TOPO PARA O FUNDO) ===\n");

    if (topo == NULL) {
        printf("A mochila esta vazia.\n");
        printf("======================================\n");
        return;
    }

    Item* atual = topo;
    int posicao = 1;

    while(atual != NULL){
        if(posicao == 1){
            printf("[TOPO] -> %s\n", atual->nome);
        }else{
            printf("          %s\n", atual->nome);
        }
        atual = atual->abaixo;
        posicao++;
    }
    printf("======================================\n");
}