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
            // ... (cases 1 e 2 já implementados) ...

            case 3: {
                int op = 0;
                int id;
                char desc[100];
                do {
                    printf("\n--- DIARIO DE MISSOES (LISTA SIMPLES) ---\n");
                    printf("1. Adicionar Missao\n2. Concluir Missao\n3. Ver Diario\n0. Voltar\nEscolha: ");
                    if (scanf("%d", &op) != 1) { limparBuffer(); continue; }
                    limparBuffer();
                    
                    if (op == 1) {
                        printf("ID da missao: ");
                        scanf("%d", &id); limparBuffer();
                        printf("Descricao: ");
                        fgets(desc, sizeof(desc), stdin); desc[strcspn(desc, "\n")] = 0;
                        inserirMissao(&listaMissoes, id, desc);
                    } else if (op == 2) {
                        printf("ID da missao concluida: ");
                        scanf("%d", &id); limparBuffer();
                        removerMissao(&listaMissoes, id);
                    } else if (op == 3) {
                        exibirMissoes(listaMissoes);
                    }
                } while (op != 0);
                break;
            }
            case 4: {
                int op = 0;
                do {
                    printf("\n--- NAVEGACAO POR SALAS (LISTA DUPLA) ---\n");
                    printf("1. Descobrir Nova Sala\n2. Avancar (Proxima)\n3. Recuar (Anterior)\n4. Olhar ao Redor\n0. Voltar\nEscolha: ");
                    if (scanf("%d", &op) != 1) { limparBuffer(); continue; }
                    limparBuffer();

                    if (op == 1) {
                        int id; char desc[100];
                        printf("Numero da sala: "); scanf("%d", &id); limparBuffer();
                        printf("Descricao do ambiente: ");
                        fgets(desc, sizeof(desc), stdin); desc[strcspn(desc, "\n")] = 0;
                        adicionarSala(&salaAtual, id, desc);
                    } else if (op == 2) {
                        navegarProximaSala(&salaAtual);
                    } else if (op == 3) {
                        navegarSalaAnterior(&salaAtual);
                    } else if (op == 4) {
                        exibirSalaAtual(salaAtual);
                    }
                } while (op != 0);
                break;
            }
            case 5: {
                int op = 0;
                do {
                    printf("\n--- PATRULHA INIMIGA (LISTA CIRCULAR) ---\n");
                    printf("1. Adicionar Ponto de Rota\n2. Observar Rota de Patrulha\n0. Voltar\nEscolha: ");
                    if (scanf("%d", &op) != 1) { limparBuffer(); continue; }
                    limparBuffer();

                    if (op == 1) {
                        char local[50];
                        printf("Nome do local da patrulha: ");
                        fgets(local, sizeof(local), stdin); local[strcspn(local, "\n")] = 0;
                        inserirPatrulha(&caldaPatrulha, local);
                    } else if (op == 2) {
                        exibirRotaPatrulha(caldaPatrulha);
                    }
                } while(op != 0);
                break;
            }
            case 6: {
                int op = 0;
                do {
                    printf("\n--- SKILL TREE (ARVORE BINARIA) ---\n");
                    printf("1. Desbloquear Habilidade\n2. Exibir Arvore de Habilidades\n0. Voltar\nEscolha: ");
                    if (scanf("%d", &op) != 1) { limparBuffer(); continue; }
                    limparBuffer();

                    if (op == 1) {
                        int id; char nome[50];
                        printf("ID (Forca da habilidade 1-100): "); scanf("%d", &id); limparBuffer();
                        printf("Nome da Magia/Habilidade: ");
                        fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
                        raizSkills = inserirHabilidade(raizSkills, id, nome);
                    } else if (op == 2) {
                        printf("\n=== ARVORE DE HABILIDADES (ORDEM CRESCENTE) ===\n");
                        exibirSkillTreeInOrder(raizSkills);
                    }
                } while(op != 0);
                break;
            }
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
