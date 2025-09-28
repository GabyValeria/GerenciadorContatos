/* ============================================================================
 * PROJETO: Sistema de Gerenciamento de Contatos em C 
 * DESCRIÇÃO: Um programa de console para gerenciar contatos com alocação
 * dinâmica, validação, edição e ordenação.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h> // Para malloc, realloc, free, qsort, exit
#include <string.h> // Para manipulação de strings
#include <ctype.h>  // Para isdigit (validação de telefone)

#define NOME_ARQUIVO "contatos.csv"
#define CAPACIDADE_INICIAL 10 // Capacidade inicial do array dinâmico

// Definição da estrutura do contato 
struct Contato {
    char nome[100];
    char telefone[20];
    char email[100];
};

// === VARIÁVEIS GLOBAIS ===
// Agora usamos um ponteiro para a agenda, em vez de um array estático
struct Contato *agenda = NULL;
int numeroDeContatos = 0;
int capacidadeAgenda = 0;

// === PROTÓTIPOS DAS FUNÇÕES ===
void exibirMenu();
void adicionarContato();
void listarContatos();
void buscarContato();
void removerContato();
void editarContato(); 
void salvarContatos();
void carregarContatos();
void limparBufferEntrada();
void liberarMemoria(); 

// Novas funções de validação e ordenação
int validarTelefone(const char *telefone); 
int validarEmail(const char *email);     
int compararContatos(const void *a, const void *b); 

// ===================================
// FUNÇÃO PRINCIPAL
// ===================================

int main() {
    carregarContatos(); // Carrega contatos existentes e aloca memória inicial
    int opcao;

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) { // Proteção contra entrada não numérica
            opcao = -1; // Força a opção default
        }
        limparBufferEntrada(); // Essencial após um scanf

        switch (opcao) {
            case 1: adicionarContato(); break;
            case 2: listarContatos(); break;
            case 3: buscarContato(); break;
            case 4: removerContato(); break;
            case 5: editarContato(); break; 
            case 6: salvarContatos(); break;
            case 0:
                printf("Salvando contatos e saindo...\n");
                salvarContatos();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }

    } while (opcao != 0);

    liberarMemoria(); // Libera a memória alocada antes de sair
    return 0;
}

// ===================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ===================================

void exibirMenu() {
    system("clear || cls");
    printf("=================================\n");
    printf("   GERENCIADOR DE CONTATOS\n");
    printf("=================================\n");
    printf("1. Adicionar Contato\n");
    printf("2. Listar Contatos\n"); 
    printf("3. Buscar Contato\n");
    printf("4. Remover Contato\n");
    printf("5. Editar Contato\n");      
    printf("6. Salvar Contatos\n");      
    printf("0. Sair\n");
    printf("---------------------------------\n");
    printf("Contatos: %d | Capacidade: %d\n", numeroDeContatos, capacidadeAgenda);
    printf("Escolha uma opção: ");
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void liberarMemoria() {
    free(agenda);
    agenda = NULL; // Boa prática para evitar ponteiros "soltos"
}

// *** FUNÇÃO MODIFICADA PARA USAR MEMÓRIA DINÂMICA ***
void adicionarContato() {
    // Se a agenda estiver cheia, aumenta a capacidade
    if (numeroDeContatos >= capacidadeAgenda) {
        // Primeira alocação ou realocação
        int novaCapacidade = (capacidadeAgenda == 0) ? CAPACIDADE_INICIAL : capacidadeAgenda * 2;
        struct Contato *temp = realloc(agenda, novaCapacidade * sizeof(struct Contato));

        if (temp == NULL) {
            printf("Erro crítico: Falha ao alocar memória!\n");
            return; // Ou exit(1) em um caso real
        }
        agenda = temp;
        capacidadeAgenda = novaCapacidade;
        printf("(Info: Capacidade da agenda aumentada para %d)\n", capacidadeAgenda);
    }

    struct Contato novoContato;

    printf("\n--- Adicionar Novo Contato ---\n");
    printf("Nome: ");
    scanf(" %99[^\n]", novoContato.nome);
    limparBufferEntrada();

    // Validação de Telefone
    do {
        printf("Telefone: ");
        scanf(" %19[^\n]", novoContato.telefone);
        limparBufferEntrada();
        if (!validarTelefone(novoContato.telefone)) {
            printf("Telefone inválido! Use apenas números, '-', '(', ')', '+'.\n");
        }
    } while (!validarTelefone(novoContato.telefone));

    // Validação de Email
    do {
        printf("Email: ");
        scanf(" %99[^\n]", novoContato.email);
        limparBufferEntrada();
        if (!validarEmail(novoContato.email)) {
            printf("Email inválido! O email deve conter '@' e '.'.\n");
        }
    } while (!validarEmail(novoContato.email));

    agenda[numeroDeContatos] = novoContato;
    numeroDeContatos++;
    printf("\nContato adicionado com sucesso!\n");
}

// *** FUNÇÃO MODIFICADA PARA ORDENAR ANTES DE LISTAR ***
void listarContatos() {
    printf("\n--- Lista de Contatos (%d) ---\n", numeroDeContatos);
    if (numeroDeContatos == 0) {
        printf("Nenhum contato na agenda.\n");
        return;
    }

    // Ordena a agenda usando qsort antes de listar
    qsort(agenda, numeroDeContatos, sizeof(struct Contato), compararContatos);

    for (int i = 0; i < numeroDeContatos; i++) {
        printf("---------------------------------\n");
        printf("  Nome: %s\n", agenda[i].nome);
        printf("  Telefone: %s\n", agenda[i].telefone);
        printf("  Email: %s\n", agenda[i].email);
    }
}

// *** NOVA FUNÇÃO DE EDIÇÃO ***
void editarContato() {
    char nomeBusca[100];
    printf("\nDigite o nome do contato a ser editado: ");
    scanf(" %99[^\n]", nomeBusca);
    limparBufferEntrada();

    int indiceParaEditar = -1;
    for (int i = 0; i < numeroDeContatos; i++) {
        if (strcmp(agenda[i].nome, nomeBusca) == 0) {
            indiceParaEditar = i;
            break;
        }
    }

    if (indiceParaEditar == -1) {
        printf("Contato '%s' não encontrado.\n", nomeBusca);
    } else {
        printf("\n--- Editando Contato: %s ---\n", agenda[indiceParaEditar].nome);
        printf("Deixe em branco e pressione Enter para manter a informação atual.\n\n");

        char buffer[100];

        // Editar Nome
        printf("Nome atual: %s\nNovo nome: ", agenda[indiceParaEditar].nome);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove a nova linha do fgets
        if (strlen(buffer) > 0) {
            strcpy(agenda[indiceParaEditar].nome, buffer);
        }

        // Editar Telefone com validação
        do {
            printf("Telefone atual: %s\nNovo telefone: ", agenda[indiceParaEditar].telefone);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                if(validarTelefone(buffer)) {
                    strcpy(agenda[indiceParaEditar].telefone, buffer);
                    break;
                } else {
                    printf("Telefone inválido! Tente novamente.\n");
                }
            } else {
                break; 
            }
        } while(1);

        // Editar Email com validação
        do {
            printf("Email atual: %s\nNovo email: ", agenda[indiceParaEditar].email);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                if(validarEmail(buffer)) {
                    strcpy(agenda[indiceParaEditar].email, buffer);
                    break;
                } else {
                    printf("Email inválido! Tente novamente.\n");
                }
            } else {
                break; 
            }
        } while(1);

        printf("\nContato atualizado com sucesso!\n");
    }
}

// *** FUNÇÕES DE VALIDAÇÃO ***
int validarTelefone(const char *telefone) {
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (!isdigit(telefone[i]) && telefone[i] != '-' && telefone[i] != '(' &&
            telefone[i] != ')' && telefone[i] != '+' && telefone[i] != ' ') {
            return 0; // Inválido
        }
    }
    return 1; // Válido
}

int validarEmail(const char *email) {
    // Validação simples: verifica se existe um '@' e um '.' depois do '@'
    char *arroba = strchr(email, '@');
    if (arroba == NULL) return 0; // Não tem '@'

    char *ponto = strrchr(arroba, '.'); // Procura o último '.' depois do '@'
    if (ponto == NULL || ponto == arroba + 1) return 0; // Não tem '.' ou está logo após '@'

    return 1; // Válido
}

// *** FUNÇÃO DE COMPARAÇÃO PARA QSORT ***
int compararContatos(const void *a, const void *b) {
    struct Contato *contatoA = (struct Contato *)a;
    struct Contato *contatoB = (struct Contato *)b;
    return strcmp(contatoA->nome, contatoB->nome); // Compara os nomes
}

void buscarContato() {
    char nomeBusca[100];
    printf("\nDigite o nome para buscar: ");
    scanf(" %99[^\n]", nomeBusca);
    limparBufferEntrada();

    int encontrados = 0;
    qsort(agenda, numeroDeContatos, sizeof(struct Contato), compararContatos); 
    for (int i = 0; i < numeroDeContatos; i++) {
        if (strstr(agenda[i].nome, nomeBusca) != NULL) {
            if (encontrados == 0) {
                 printf("\n--- Contatos Encontrados ---\n");
            }
            printf("---------------------------------\n");
            printf("  Nome: %s\n", agenda[i].nome);
            printf("  Telefone: %s\n", agenda[i].telefone);
            printf("  Email: %s\n", agenda[i].email);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nomeBusca);
    }
}

void removerContato() {
    char nomeBusca[100];
    printf("\nDigite o nome do contato a ser removido: ");
    scanf(" %99[^\n]", nomeBusca);
    limparBufferEntrada();

    int indiceParaRemover = -1;
    for (int i = 0; i < numeroDeContatos; i++) {
        if (strcmp(agenda[i].nome, nomeBusca) == 0) {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover == -1) {
        printf("Contato '%s' não encontrado.\n", nomeBusca);
    } else {
        for (int i = indiceParaRemover; i < numeroDeContatos - 1; i++) {
            agenda[i] = agenda[i + 1];
        }
        numeroDeContatos--;
        printf("Contato removido com sucesso!\n"); 
    }
}

void salvarContatos() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    for (int i = 0; i < numeroDeContatos; i++) {
        fprintf(arquivo, "%s,%s,%s\n", agenda[i].nome, agenda[i].telefone, agenda[i].email);
    }
    fclose(arquivo);
    printf("Contatos salvos com sucesso em '%s'.\n", NOME_ARQUIVO);
}


// *** FUNÇÃO CARREGAR MODIFICADA PARA MEMÓRIA DINÂMICA ***
void carregarContatos() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Arquivo de contatos não encontrado. Começando com agenda vazia.\n");
        return;
    }

    struct Contato tempContato;
    while (fscanf(arquivo, "%99[^,],%19[^,],%99[^\n]\n",
                  tempContato.nome, tempContato.telefone, tempContato.email) != EOF) {
        
        // Garante que há espaço antes de adicionar (lógica de 'adicionarContato')
        if (numeroDeContatos >= capacidadeAgenda) {
            int novaCapacidade = (capacidadeAgenda == 0) ? CAPACIDADE_INICIAL : capacidadeAgenda * 2;
            struct Contato *temp = realloc(agenda, novaCapacidade * sizeof(struct Contato));
            if (temp == NULL) {
                printf("Erro crítico ao carregar: Falha ao alocar memória!\n");
                liberarMemoria();
                exit(1);
            }
            agenda = temp;
            capacidadeAgenda = novaCapacidade;
        }

        agenda[numeroDeContatos] = tempContato;
        numeroDeContatos++;
    }

    fclose(arquivo);
    printf("%d contatos carregados com sucesso.\n", numeroDeContatos);
}