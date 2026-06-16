#include "dungeon.h"

int main() {
    int opcao = 0;

    
    Turno *frenteTurnos = NULL, *trasTurnos = NULL;
    Item* topoInventario = NULL;
    Missao* listaMissoes = NULL;
    Sala* salaAtual = NULL;
    PontoPatrulha* caldaPatrulha = NULL;
    Habilidade* raizSkills = NULL;

    do {
        exibirMenuPrincipal();
        printf("Escolha uma acao: ");
        
    
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero correspondente ao menu.\n");
            limparBuffer();
            continue;
        }

        switch(opcao) {
            case 1: {
                int opcaoFila = 0;
                char nome[50];
                do {
                    printf("\n--- GERENCIAR TURNOS (FILA) ---\n");
                    printf("1. Adicionar personagem ao combate (Enfileirar)\n");
                    printf("2. Passar o turno (Desenfileirar)\n");
                    printf("3. Exibir ordem de turnos\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Escolha: ");
                    
                    if (scanf("%d", &opcaoFila) != 1) {
                        limparBuffer();
                        continue;
                    }
                    limparBuffer(); // Limpa o \n que o scanf deixa

                    switch (opcaoFila) {
                        case 1:
                            printf("Digite o nome do personagem/monstro: ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = 0; // Remove o enter do final
                            enfileirarTurno(&frenteTurnos, &trasTurnos, nome);
                            break;
                        case 2:
                            desenfileirarTurno(&frenteTurnos, &trasTurnos);
                            break;
                        case 3:
                            exibirFilaTurnos(frenteTurnos);
                            break;
                    }
                } while (opcaoFila != 0);
                break;
            }

            case 2: {
                int opcaoPilha = 0;
                char nomeItem[50];
                do {
                    printf("\n--- GRIMORIO E INVENTARIO (PILHA) ---\n");
                    printf("1. Guardar novo item (Push)\n");
                    printf("2. Usar item do topo (Pop)\n");
                    printf("3. Inspecionar mochila (Exibir)\n");
                    printf("0. Voltar ao menu principal\n");
                    printf("Escolha: ");
                    
                    if (scanf("%d", &opcaoPilha) != 1) {
                        limparBuffer();
                        continue;
                    }
                    limparBuffer();

                    switch (opcaoPilha) {
                        case 1:
                            printf("Digite o nome do item/magia: ");
                            fgets(nomeItem, sizeof(nomeItem), stdin);
                            nomeItem[strcspn(nomeItem, "\n")] = 0;
                            pushInventario(&topoInventario, nomeItem);
                            break;
                        case 2:
                            popInventario(&topoInventario);
                            break;
                        case 3:
                            exibirInventario(topoInventario);
                            break;
                    }
                } while (opcaoPilha != 0);
                break;
            }
            case 3:
                printf("\n--- Diario de Missoes (LISTA SIMPLES) ---\n");
                // Exemplo de chamada: exibirMissoes(listaMissoes);
                break;
            case 4:
                printf("\n--- Navegacao por Salas (LISTA DUPLA) ---\n");
                // Exemplo de chamada: exibirSalaAtual(salaAtual);
                break;
            case 5:
                printf("\n--- Rota de Patrulha dos Demonios (LISTA CIRCULAR) ---\n");
                // Exemplo de chamada: exibirRotaPatrulha(caldaPatrulha);
                break;
            case 6:
                printf("\n--- Arvore de Habilidades (ARVORE BINARIA) ---\n");
                // Exemplo de chamada: exibirSkillTreeInOrder(raizSkills);
                break;
            case 0:
                printf("\nEncerrando a jornada. Ate a proxima aventura!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            limparBuffer();
            getchar();
        }

    } while (opcao != 0);

    return 0;
}

// Implementação das funções utilitárias básicas de interface
void exibirMenuPrincipal() {
    printf("\n========================================\n");
    printf("        DUNGEON ENGINE MANAGER          \n");
    printf("========================================\n");
    printf("1. Gerenciar Turnos     (Fila)\n");
    printf("2. Inventario/Grimorio  (Pilha)\n");
    printf("3. Diario de Quests     (Lista Simples)\n");
    printf("4. Explorar Salas       (Lista Dupla)\n");
    printf("5. Patrulha Inimiga     (Lista Circular)\n");
    printf("6. Skill Tree           (Arvore Binaria)\n");
    printf("0. Sair do Jogo\n");
    printf("========================================\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
