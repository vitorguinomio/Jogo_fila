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

void popInventario(Item** topo){
    if(*topo == NULL){
        printf("[AVISO] O inventario esta vazio! Nao ha itens para usar.\n");
        return;
    }

    Item* itemUsado = *topo;
    printf("Voce usou o item/magia: '%s'\n", itemUsado->nome);
    *topo = itemUsado->abaixo;
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
    int primeiro = 1;

    while(atual != NULL){
        printf(primeiro ? "[TOPO] -> %s\n" : "          %s\n", atual->nome);
        primeiro = 0;
        atual = atual->abaixo;
    }
    printf("======================================\n");
}

void inserirMissao(Missao** topo, int id, const char* desc) {
    Missao* novaMissao = (Missao*)malloc(sizeof(Missao));
    if (novaMissao == NULL) {
        printf("[ERRO] Falha ao alocar memoria para a missao!\n");
        return;
    }

    novaMissao->id = id;
    strncpy(novaMissao->descricao, desc, sizeof(novaMissao->descricao) - 1);
    novaMissao->descricao[sizeof(novaMissao->descricao) - 1] = '\0';
    novaMissao->proxima = NULL;


    if (*topo == NULL) {
        *topo = novaMissao;
    } else {
        Missao* atual = *topo;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = novaMissao;
    }
    printf("Missao [%d] adicionada ao diario.\n", id);
}

void removerMissao(Missao** topo, int id) {
    Missao** cursor = topo;

    while (*cursor != NULL && (*cursor)->id != id) {
        cursor = &(*cursor)->proxima;
    }

    if (*cursor == NULL) {
        printf("Missao ID %d nao encontrada.\n", id);
        return;
    }

    Missao* removida = *cursor;
    *cursor = removida->proxima;

    printf("Missao [%d] concluida/removida!\n", id);
    free(removida);
}

void exibirMissoes(Missao* topo) {
    printf("\n=== DIARIO DE MISSOES ===\n");
    if (topo == NULL) {
        printf("Nenhuma quest ativa.\n");
        return;
    }
    Missao* atual = topo;
    while (atual != NULL) {
        printf("[ID: %d] - %s\n", atual->id, atual->descricao);
        atual = atual->proxima;
    }
}


void adicionarSala(Sala** atual, int id, const char* desc) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("[ERRO] Falha ao mapear nova sala por falta de memoria.\n");
        return;
    }

    novaSala->id_sala = id;
    strncpy(novaSala->descricao, desc, sizeof(novaSala->descricao) - 1);
    novaSala->descricao[sizeof(novaSala->descricao) - 1] = '\0';
    novaSala->anterior = NULL;
    novaSala->proxima = NULL;

    if (*atual == NULL) {
        *atual = novaSala; 
    } else {
        Sala* fim = *atual;
        while (fim->proxima != NULL) {
            fim = fim->proxima;
        }
        fim->proxima = novaSala;
        novaSala->anterior = fim;
    }
    printf("Nova sala mapeada: %s\n", desc);
}

void navegarProximaSala(Sala** atual) {
    if (*atual == NULL || (*atual)->proxima == NULL) {
        printf("Fim do caminho! Nao ha proxima sala.\n");
        return;
    }

    *atual = (*atual)->proxima;
    printf("Voce avancou para a sala: %s\n", (*atual)->descricao);
}

void navegarSalaAnterior(Sala** atual) {
    if (*atual == NULL || (*atual)->anterior == NULL) {
        printf("Esta e a entrada da masmorra. Nao ha sala anterior.\n");
        return;
    }

    *atual = (*atual)->anterior;
    printf("Voce recuou para a sala: %s\n", (*atual)->descricao);
}

void exibirSalaAtual(Sala* atual) {
    printf("\n=== SALA ATUAL ===\n");
    if (atual == NULL) {
        printf("Voce ainda nao entrou na masmorra.\n");
    } else {
        printf("ID: %d | Local: %s\n", atual->id_sala, atual->descricao);
    }
}


void inserirPatrulha(PontoPatrulha** calda, const char* local) {
    PontoPatrulha* novoPonto = (PontoPatrulha*)malloc(sizeof(PontoPatrulha));
    if (novoPonto == NULL) {
        printf("[ERRO] Falha ao criar ponto de patrulha por falta de memoria.\n");
        return;
    }

    strncpy(novoPonto->local, local, sizeof(novoPonto->local) - 1);
    novoPonto->local[sizeof(novoPonto->local) - 1] = '\0';

    if (*calda == NULL) {
        *calda = novoPonto;
        novoPonto->proximo = novoPonto;
    } else {
        novoPonto->proximo = (*calda)->proximo; 
        (*calda)->proximo = novoPonto;          
        *calda = novoPonto;                     
    }
    printf("Ponto de patrulha '%s' adicionado a rota.\n", local);
}

void exibirRotaPatrulha(PontoPatrulha* calda) {
    printf("\n=== ROTA DE PATRULHA INIMIGA ===\n");
    if (calda == NULL) {
        printf("Nenhum inimigo patrulhando.\n");
        return;
    }
    
    PontoPatrulha* atual = calda->proximo; 
    
    do {
        printf("-> %s ", atual->local);
        atual = atual->proximo;
    } while (atual != calda->proximo);
    
    printf("\n(Loop infinito)\n");
}


Habilidade* inserirHabilidade(Habilidade* raiz, int id, const char* nome) {
    if (raiz == NULL) {
        Habilidade* novaSkill = (Habilidade*)malloc(sizeof(Habilidade));
        if (novaSkill == NULL) {
            printf("[ERRO] Falha ao desbloquear habilidade por falta de memoria.\n");
            return NULL;
        }

        novaSkill->id_skill = id;
        strncpy(novaSkill->nome, nome, sizeof(novaSkill->nome) - 1);
        novaSkill->nome[sizeof(novaSkill->nome) - 1] = '\0';
        novaSkill->esquerda = NULL;
        novaSkill->direita = NULL;
        printf("Habilidade [%d - %s] desbloqueada!\n", id, nome);
        return novaSkill;
    }

    if (id < raiz->id_skill) {
        raiz->esquerda = inserirHabilidade(raiz->esquerda, id, nome);
    } else if (id > raiz->id_skill) {
        raiz->direita = inserirHabilidade(raiz->direita, id, nome);
    }
    return raiz;
}

void exibirSkillTreeInOrder(Habilidade* raiz) {
    if (raiz != NULL) {
        exibirSkillTreeInOrder(raiz->esquerda);
        printf("Skill ID: %d | Nome: %s\n", raiz->id_skill, raiz->nome);
        exibirSkillTreeInOrder(raiz->direita);
    }
}