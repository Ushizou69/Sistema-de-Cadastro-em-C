#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct funcionario {
    int id_registro;
    char nome[50];
    float salario;
};
typedef struct funcionario Funcionario;

// Prototipos //
void carregar_dados(Funcionario **empresa, int *qtd);
void adicionar_funcionario(Funcionario **empresa, int *qtd);
void listar_funcionarios(Funcionario *empresa, int qtd);
void salvar_dados(Funcionario *empresa, int qtd);
void excluir_arquivo();
void limpa_memoria(Funcionario **empresa, int *qtd);
void menu();

// Implementacoes //

void carregar_dados(Funcionario **empresa, int *qtd) {
	// abre para leitura o arquivo em binario.
    FILE *file = fopen("cadastro_funcionarios.bin", "rb");
    if (file == NULL) {
        *empresa = NULL;
        *qtd = 0;
        printf("Nenhum arquivo encontrado. Iniciando com cadastro vazio.\n");
        return;
    }
	
	//	move o cursor para o final do arquivo.
    if (fseek(file, 0, SEEK_END) != 0) {
        printf("Erro ao posicionar o arquivo.\n");
        fclose(file);
        *empresa = NULL;
        *qtd = 0;
        return;
    }
	
	//	retorna a posicao atual do cursor (em bytes desde o inicio).
    long tamanho = ftell(file);
    if (tamanho < 0) {
        printf("Erro ao obter tamanho do arquivo.\n");
        fclose(file);
        *empresa = NULL;
        *qtd = 0;
        return;
    }
	
	// verifica se esta vazio.
    if (tamanho == 0) {
        printf("Arquivo existe mas esta vazio.\n");
        fclose(file);
        *empresa = NULL;
        *qtd = 0;
        return;
    }
	
	// o que isso faz? - calcula quantos registros "Funcionario" existem no arquivo:
    // tamanho (bytes do arquivo) dividido pelo tamanho em bytes de cada struct.
    int n = (int)(tamanho / sizeof(Funcionario));
    Funcionario *ptr = (Funcionario *) malloc(n * sizeof(Funcionario));
    // verifica se o ponteiro eh nulo.
    if (ptr == NULL) {
        printf("Erro: Memoria insuficiente ao carregar dados.\n");
        fclose(file);
        *empresa = NULL;
        *qtd = 0;
        return;
    }

	// o que isso faz? - rewind posiciona o cursor de leitura/escrita no início do arquivo (offset 0),
    // é equivalente a fseek(file, 0, SEEK_SET).
    rewind(file);
    // o que isso faz? - fread lê 'n' elementos do tamanho sizeof(Funcionario) do arquivo e copia
    // para a memória apontada por 'ptr'. Retorna quantos elementos foram lidos com sucesso.
    size_t lidos = fread(ptr, sizeof(Funcionario), n, file);
    // verifica se a quantidade de lidos condiz com o tamanho do arquivo.
    if (lidos != (size_t)n) {
        printf("Erro ao ler registros do arquivo. Lidos: %zu, Esperados: %d\n", lidos, n);
        free(ptr);
        fclose(file);
        *empresa = NULL;
        *qtd = 0;
        return;
    }

    fclose(file);
    *empresa = ptr;
    *qtd = n;
    printf("Carregados %d funcionarios do arquivo.\n", *qtd);
}

void adicionar_funcionario(Funcionario **empresa, int *qtd) {
	//aumenta a qtd.
    (*qtd)++;
	
	// realoca a memoria em uma variavel temporaria.
    Funcionario *temp = (Funcionario *) realloc(*empresa, (*qtd) * sizeof(Funcionario));
    if (temp == NULL) {
        printf("Erro: Memoria Insuficiente! Nao foi possivel incluir o novo funcionario.\n");
        (*qtd)--;
        return;
    }
	
	// atualiza a variavel.
    *empresa = temp;
    int ind = *qtd - 1;

    printf("Digite o id do funcionario: ");
    if (scanf("%d", &(*empresa)[ind].id_registro) != 1) {
        printf("Entrada invalida para id.\n");
        (*qtd)--;
        return;
    }
    // o que isso faz? - consome newline remanescente
    getchar();

    printf("Digite o nome do funcionario: ");
    // o que isso faz? - fgets lê uma linha de stdin (até '\n' ou até sizeof-1 caracteres) e armazena em nome.
    // Se fgets retornar NULL, houve erro ou EOF copia string vazia.
    if (fgets((*empresa)[ind].nome, sizeof((*empresa)[ind].nome), stdin) == NULL) {
        strcpy((*empresa)[ind].nome, "");
    } else {
        // remove '\n' ao final, se existir
        size_t len = strlen((*empresa)[ind].nome);
        if (len > 0 && (*empresa)[ind].nome[len-1] == '\n')
            (*empresa)[ind].nome[len-1] = '\0';
    }

    printf("Digite o salario do funcionario: ");
    if (scanf("%f", &(*empresa)[ind].salario) != 1) {
        printf("Entrada invalida para salario.\n");
        (*qtd)--;
        return;
    }

    printf("Usuario cadastrado!\n");
}

void listar_funcionarios(Funcionario *empresa, int qtd) {
	int i = 0;
	
	// verifica se ha um funcionario cadastrado.
    if (qtd == 0) {
        printf("Nenhum funcionario cadastrado!\n");
        return;
    }
	
	// mostra todos os funcionarios cadastrados.
    for (i = 0; i < qtd; i++) {
        printf("\nFuncionario %d:\n", i + 1);
        printf("ID: %d\n", empresa[i].id_registro);
        printf("Nome: %s\n", empresa[i].nome);
        printf("Salario: %.2f\n", empresa[i].salario);
    }
}

void salvar_dados(Funcionario *empresa, int qtd) {
	// abre o arquivo para escrita em binario e o cria se nao existir.
    FILE *file = fopen("cadastro_funcionarios.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }
	
	// verifica se o arquivo esta vazio.
    if (qtd == 0) {
        printf("Nenhum registro para salvar. Arquivo vazio.\n");
        fclose(file);
        return;
    }
	
	// o que isso faz? - fwrite grava 'qtd' elementos de tamanho sizeof(Funcionario)
    // a partir de 'empresa' no arquivo, retorna quantos elementos foram efetivamente gravados.
    size_t escritos = fwrite(empresa, sizeof(Funcionario), qtd, file);
    if (escritos != (size_t)qtd) {
        printf("Erro ao gravar dados no arquivo. Gravados: %zu, Esperados: %d\n", escritos, qtd);
    } else {
        printf("Dados salvos com sucesso. %d registros gravados.\n", qtd);
    }

    fclose(file);
}

void excluir_arquivo() {
	// caso a funcao remove retorne zero, remove o arquivo cadastro_funcionarios.bin.
    if (remove("cadastro_funcionarios.bin") == 0) {
        printf("Arquivo 'cadastro_funcionarios.bin' excluido com sucesso.\n");
    } else {
        printf("Falha ao excluir arquivo. Verifique se o arquivo existe ou permissao.\n");
    }
}

void limpa_memoria(Funcionario **empresa, int *qtd) {
	// verifica se o ponteiro para ponteiro nao eh vazio para liberar a sua mem�ria.
    if (*empresa != NULL) {
        free(*empresa);
        *empresa = NULL;
    }
    *qtd = 0;
    printf("Memoria liberada e ponteiro definido para NULL.\n");
}

void menu() {
    int op = 0, contador_de_funcionario = 0;
    Funcionario *empresa = NULL;

    printf("-----CADASTRO DE FUNCIONARIOS-----\n");
    do {
        printf("\nDigite a opcao que voce deseja:\n");
        printf("1. Inicializar/Carregar Cadastro\n");
        printf("2. Adicionar Novo Funcionario\n");
        printf("3. Exibir Registros \n");
        printf("4. Persistir/Salvar Cadastro\n");
        printf("5. Excluir Arquivo de Dados\n");
        printf("6. Encerrar Programa\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) {
            // limpar entrada invalida
            printf("Entrada invalida. Tente novamente.\n");
            int c;
            // o que isso faz? - Este loop consome caracteres até o fim da linha (ou EOF),
            // descartando a entrada inválida deixada no buffer de stdin.
            while ((c = getchar()) != '\n' && c != EOF) {}
            op = 0;
            continue;
        }
        // o que isso faz? - limpar \n remanescente antes de possiveis fgets
        int c; while ((c = getchar()) != '\n' && c != EOF) {}

        switch (op) {
            case 1:
                carregar_dados(&empresa, &contador_de_funcionario);
                break;
            case 2:
                adicionar_funcionario(&empresa, &contador_de_funcionario);
                break;
            case 3:
                listar_funcionarios(empresa, contador_de_funcionario);
                break;
            case 4:
                salvar_dados(empresa, contador_de_funcionario);
                break;
            case 5:
                excluir_arquivo();
                break;
            case 6:
                limpa_memoria(&empresa, &contador_de_funcionario);
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Nenhuma das opcoes selecionadas! Tente novamente.\n");
                break;
        }
    } while (op != 6);
}

int main() {
    menu();
    return 0;
}
