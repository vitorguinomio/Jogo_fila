#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Turno {
    char personagem[50];
    struct Turno* proximo;
} Turno;

// Protótipos da Fila
Turno* criarFila();
void enfileirarTurno(Turno** frente, Turno** tras, const char* nome);
void desenfileirarTurno(Turno** frente, Turno** tras);
void exibirFilaTurnos(Turno* frente);

typedef struct Item {
    char nome[50];
    struct Item* abaixo;
} Item;

// Protótipos da Pilha
void pushInventario(Item** topo, const char* nomeItem);
void popInventario(Item** topo);
void exibirInventario(Item* topo);


typedef struct Missao {
    int id;
    char descricao[100];
    struct Missao* proxima;
} Missao;


void inserirMissao(Missao** topo, int id, const char* desc);
void removerMissao(Missao** topo, int id);
void exibirMissoes(Missao* topo);


typedef struct Sala {
    int id_sala;
    char descricao[100];
    struct Sala* anterior;
    struct Sala* proxima;
} Sala;

// Protótipos da Lista Dupla
void adicionarSala(Sala** atual, int id, const char* desc);
void navegarProximaSala(Sala** atual);
void navegarSalaAnterior(Sala** atual);
void exibirSalaAtual(Sala* atual);


typedef struct PontoPatrulha {
    char local[50];
    struct PontoPatrulha* proximo;
} PontoPatrulha;


void inserirPatrulha(PontoPatrulha** calda, const char* local);
void avancarPatrulha(PontoPatrulha** atual);
void exibirRotaPatrulha(PontoPatrulha* calda);


typedef struct Habilidade {
    int id_skill;
    char nome[50];
    struct Habilidade* esquerda;
    struct Habilidade* direita;
} Habilidade;


Habilidade* inserirHabilidade(Habilidade* raiz, int id, const char* nome);
Habilidade* buscarHabilidade(Habilidade* raiz, int id);
void exibirSkillTreeInOrder(Habilidade* raiz);

void exibirMenuPrincipal();
void limparBuffer();

#endif
