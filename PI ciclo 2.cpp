#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_NOME 50
#define MAX_HABILIDADES 100
#define MAX_PROJETOS 50
#define MAX_VOLUNTARIOS_POR_PROJETO 100

struct Voluntario {
    char nome[MAX_NOME];
    int idade;
    char habilidades[MAX_HABILIDADES];
};

struct Ong {
    char nome[MAX_NOME];
    char causa[MAX_NOME];
    char projetos[MAX_PROJETOS][MAX_NOME];
    int numProjetos;
};

struct Empresa {
    char nome[MAX_NOME];
    char areaAtuacao[MAX_NOME];
    char projetosSociais[MAX_PROJETOS][MAX_NOME];
    int numProjetos;
};


struct Voluntariado {
    char titulo[MAX_NOME];
    char descricao[MAX_NOME];
    struct Ong *ong;
    struct Empresa *empresa;
    struct Voluntario *voluntarios[MAX_VOLUNTARIOS_POR_PROJETO];
    int numVoluntarios;
};

// Fun��es de cadastro

void cadastrarVoluntario(struct Voluntario **voluntarios, int *tamanho) {
    *voluntarios = (struct Voluntario*) realloc(*voluntarios, (*tamanho + 1) * sizeof(struct Voluntario));
    if (*voluntarios == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }

    printf("Digite o nome do volunt�rio: ");
    scanf("%s", (*voluntarios)[*tamanho].nome);
    printf("Digite a idade do volunt�rio: ");
    scanf("%d", &(*voluntarios)[*tamanho].idade);
    printf("Digite as habilidades do volunt�rio: ");
    scanf(" %[^\n]", (*voluntarios)[*tamanho].habilidades);

    (*tamanho)++;
    printf("Volunt�rio cadastrado com sucesso!\n");
}

void cadastrarOng(struct Ong **ongs, int *tamanho) {
    *ongs = (struct Ong*) realloc(*ongs, (*tamanho + 1) * sizeof(struct Ong));
    if (*ongs == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }

    printf("Digite o nome da ONG: ");
    scanf("%s", (*ongs)[*tamanho].nome);

    printf("Digite a causa da ONG: ");
    scanf(" %[^\n]", (*ongs)[*tamanho].causa);

    printf("Digite os projetos da ONG (separados por v�rgula): ");
    scanf(" %[^\n]", (*ongs)[*tamanho].projetos[0]);

    // Contar o n�mero de projetos e armazenar em numProjetos
    int i = 0, j = 0;
    while ((*ongs)[*tamanho].projetos[0][i] != '\0') {
        if ((*ongs)[*tamanho].projetos[0][i] == ',') {
            j++;
        }
        i++;
    }
    (*ongs)[*tamanho].numProjetos = j + 1;

    (*tamanho)++;
    printf("ONG cadastrada com sucesso!\n");
}

void cadastrarEmpresa(struct Empresa **empresas, int *tamanho) {
    *empresas = (struct Empresa*) realloc(*empresas, (*tamanho + 1) * sizeof(struct Empresa));
    if (*empresas == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }

    printf("Digite o nome da empresa: ");
    scanf("%s", (*empresas)[*tamanho].nome);

    printf("Digite a �rea de atua��o da empresa: ");
    scanf(" %[^\n]", (*empresas)[*tamanho].areaAtuacao);

    printf("Digite os projetos sociais da empresa (separados por v�rgula): ");
    scanf(" %[^\n]", (*empresas)[*tamanho].projetosSociais[0]);

    // Contar o n�mero de projetos e armazenar em numProjetos
    int i = 0, j = 0;
    while ((*empresas)[*tamanho].projetosSociais[0][i] != '\0') {
        if ((*empresas)[*tamanho].projetosSociais[0][i] == ',') {
            j++;
        }
        i++;
    }
    (*empresas)[*tamanho].numProjetos = j + 1;

    (*tamanho)++;
    printf("Empresa cadastrada com sucesso!\n");
}


void cadastrarVoluntariado(struct Voluntariado **voluntariados, int *tamanho, struct Ong *ongs, int numOngs, struct Empresa *empresas, int numEmpresas) {
    *voluntariados = (struct Voluntariado*) realloc(*voluntariados, (*tamanho + 1) * sizeof(struct Voluntariado));
    if (*voluntariados == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }

    printf("Digite o t�tulo do voluntariado: ");
    scanf("%s", (*voluntariados)[*tamanho].titulo);

    printf("Digite a descri��o do voluntariado: ");
    scanf(" %[^\n]", (*voluntariados)[*tamanho].descricao);

    // Associar o voluntariado � ONG ou empresa
    int escolha;
    printf("O voluntariado � de uma ONG (1) ou de uma empresa (2)? ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        printf("Escolha uma ONG:\n");
        for (int i = 0; i < numOngs; i++) {
            printf("%d. %s\n", i + 1, ongs[i].nome);
        }
        int ongEscolhida;
        scanf("%d", &ongEscolhida);
        
        // Validar a escolha e associar a ONG
        if (ongEscolhida >= 1 && ongEscolhida <= numOngs) {
            (*voluntariados)[*tamanho].ong = &ongs[ongEscolhida - 1];
            (*voluntariados)[*tamanho].empresa = NULL;  // Garantir que a empresa � NULL
        } else {
            printf("Op��o inv�lida.\n");
            return;
        }

    } else if (escolha == 2) {
        printf("Escolha uma empresa:\n");
        for (int i = 0; i < numEmpresas; i++) {
            printf("%d. %s\n", i + 1, empresas[i].nome);
        }
        int empresaEscolhida;
        scanf("%d", &empresaEscolhida);
        
        // Validar a escolha e associar a empresa
        if (empresaEscolhida >= 1 && empresaEscolhida <= numEmpresas) {
            (*voluntariados)[*tamanho].empresa = &empresas[empresaEscolhida - 1];
            (*voluntariados)[*tamanho].ong = NULL;  // Garantir que a ONG � NULL
        } else {
            printf("Op��o inv�lida.\n");
            return;
        }

    } else {
        printf("Op��o inv�lida.\n");
        return;
    }

    (*voluntariados)[*tamanho].numVoluntarios = 0;  // Inicializar o n�mero de volunt�rios
    (*tamanho)++;
    printf("Voluntariado cadastrado com sucesso!\n");
}


// Fun��o para inscrever um volunt�rio em um projeto
void inscreverVoluntario(struct Voluntariado *voluntariados, int numVoluntariados, struct Voluntario *voluntarios, int numVoluntarios) {
    // Primeiro, exibe todos os voluntariados para que o usu�rio escolha um
    printf("Digite o n�mero do voluntariado no qual deseja inscrever o volunt�rio:\n");
    for (int i = 0; i < numVoluntariados; i++) {
        printf("%d. %s\n", i + 1, voluntariados[i].titulo);
    }

    int voluntariadoEscolhido;
    scanf("%d", &voluntariadoEscolhido);

    // Verifica se a escolha do voluntariado � v�lida
    if (voluntariadoEscolhido < 1 || voluntariadoEscolhido > numVoluntariados) {
        printf("Op��o de voluntariado inv�lida.\n");
        return;
    }

    // Exibe todos os volunt�rios cadastrados para que o usu�rio escolha um
    printf("Digite o n�mero do volunt�rio que deseja inscrever:\n");
    for (int i = 0; i < numVoluntarios; i++) {
        printf("%d. %s\n", i + 1, voluntarios[i].nome);
    }

    int voluntarioEscolhido;
    scanf("%d", &voluntarioEscolhido);

    // Verifica se a escolha do volunt�rio � v�lida
    if (voluntarioEscolhido < 1 || voluntarioEscolhido > numVoluntarios) {
        printf("Op��o de volunt�rio inv�lida.\n");
        return;
    }

    // Verifica se h� espa�o para mais um volunt�rio no projeto
    if (voluntariados[voluntariadoEscolhido - 1].numVoluntarios >= MAX_VOLUNTARIOS_POR_PROJETO) {
        printf("O n�mero m�ximo de volunt�rios para este projeto j� foi atingido.\n");
        return;
    }

    // Inscreve o volunt�rio no projeto
    voluntariados[voluntariadoEscolhido - 1].voluntarios[voluntariados[voluntariadoEscolhido - 1].numVoluntarios] = &voluntarios[voluntarioEscolhido - 1];
    voluntariados[voluntariadoEscolhido - 1].numVoluntarios++;

    printf("Volunt�rio inscrito com sucesso no projeto '%s'!\n", voluntariados[voluntariadoEscolhido - 1].titulo);
}


// Fun��es para Listar

void listarTodosVoluntarios(struct Voluntario *voluntarios, int numVoluntarios) {
    if (numVoluntarios == 0) {
        printf("Nenhum volunt�rio cadastrado.\n");
        return;
    }

    for (int i = 0; i < numVoluntarios; i++) {
        printf("Volunt�rio %d: %s\n", i + 1, voluntarios[i].nome);
    }
}

void listarTodasOngs(struct Ong *ongs, int numOngs) {
    for (int i = 0; i < numOngs; i++) {
        printf("\nONG: %s\n", ongs[i].nome);
        printf("Causa: %s\n", ongs[i].causa);
        
        printf("Projetos:\n");
        for (int j = 0; j < ongs[i].numProjetos; j++) {
            printf("  - %s\n", ongs[i].projetos[j]);
        }
    }
}

void listarTodosProjetos(struct Voluntariado *projetos, int numProjetos) {
    for (int i = 0; i < numProjetos; i++) {
        printf("\nProjeto: %s\n", projetos[i].titulo);
        printf("Descri��o: %s\n", projetos[i].descricao);

        // Exibir informa��es sobre a ONG ou empresa respons�vel
        if (projetos[i].ong != NULL) {
            printf("ONG: %s\n", projetos[i].ong->nome);
        } else if (projetos[i].empresa != NULL) {
            printf("Empresa: %s\n", projetos[i].empresa->nome);
        }

        printf("N�mero de volunt�rios: %d\n", projetos[i].numVoluntarios);
       
    }
}

void listarTodasEmpresas(struct Empresa *empresas, int numEmpresas) {
    for (int i = 0; i < numEmpresas; i++) {
        printf("\nEmpresa: %s\n", empresas[i].nome);
        printf("�rea de Atua��o: %s\n", empresas[i].areaAtuacao);

        printf("Projetos Sociais:\n");
        for (int j = 0; j < empresas[i].numProjetos; j++) {
            printf("  - %s\n", empresas[i].projetosSociais[j]);
        }
    }
}

void listarTodosVoluntariados(struct Voluntariado *voluntariados, int numVoluntariados) {
    if (numVoluntariados == 0) {
        printf("Nenhum voluntariado cadastrado.\n");
        return;
    }

    for (int i = 0; i < numVoluntariados; i++) {
        printf("Voluntariado: %s\n", voluntariados[i].titulo);
        if (voluntariados[i].ong != NULL) {
            printf("   ONG: %s\n", voluntariados[i].ong->nome);
        } else if (voluntariados[i].empresa != NULL) {
            printf("   Empresa: %s\n", voluntariados[i].empresa->nome);
        }
        printf("   Descri��o: %s\n", voluntariados[i].descricao);
    }
}


int main() {
	setlocale(LC_ALL, "Portuguese");
    struct Voluntario *voluntarios = NULL;
    int numVoluntarios = 0;
    struct Ong *ongs = NULL;
    int numOngs = 0;
    struct Empresa *empresas = NULL;
    int numEmpresas = 0;
    struct Voluntariado *voluntariados = NULL;
    int numVoluntariados = 0;
    

    int opcao, subOpcao;
    do {
        printf("\nMenu Principal:\n");
        printf("1. Cadastrar\n");
        printf("2. Listar\n");
        printf("3. Increver Volunt�rio\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("O que deseja cadastrar?\n");
                printf("1. Volunt�rio\n");
                printf("2. ONG\n");
                printf("3. Empresa\n");
                printf("4. Voluntariado\n");
                scanf("%d", &subOpcao);
                if (subOpcao == 1) cadastrarVoluntario(&voluntarios, &numVoluntarios);
                else if (subOpcao == 2) cadastrarOng(&ongs, &numOngs);
                else if (subOpcao == 3) cadastrarEmpresa(&empresas, &numEmpresas);
                else if (subOpcao == 4) cadastrarVoluntariado(&voluntariados, &numVoluntariados, ongs, numOngs, empresas, numEmpresas);
                break;
            case 2:
                printf("O que deseja listar?\n");
                printf("1. Volunt�rios\n");
                printf("2. ONGs\n");
                printf("3. Empresas\n");
                printf("4. Voluntariados\n");
                scanf("%d", &subOpcao);

                if (subOpcao == 1) listarTodosVoluntarios(voluntarios, numVoluntarios);
                else if (subOpcao == 2) listarTodasOngs(ongs, numOngs);
               	else if (subOpcao == 3) listarTodasEmpresas(empresas, numEmpresas);
               	else if (subOpcao == 4) listarTodosVoluntariados(voluntariados, numVoluntariados);
                else printf("Op��o inv�lida.\n");
                break;
            case 3:
    			inscreverVoluntario(voluntariados, numVoluntariados, voluntarios, numVoluntarios);
    			break;   
            case 0:
                break;
            default:
                printf("Op��o inv�lida.\n");
        }
    } while (opcao != 0);

    free(voluntarios);
    free(ongs);
    free(empresas);
    free(voluntariados);
    
    return 0;
}
