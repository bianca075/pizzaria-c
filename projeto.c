#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include "pizza.h"

struct Clientes
{
    char nome[50];
    char cpf[12];
    char nomeRua[50];
    char numeroCasa[10];
    char complemento[10];
    char telefone[14];
    int ativo;
};

bool segundoPasso(char cpf[])
{
    int soma = 0, verificador = 0, resto = 0;
    int aux = 11;

    for (int i = 0; i < 10; i++)
    {
        soma += (cpf[i] - '0') * aux;
        aux--;
    }

    resto = soma % 11;

    if (resto < 2)
    {
        verificador = 0;
    }
    else
    {
        verificador = 11 - resto;
    }

    if (verificador == (cpf[10] - '0'))
    {
        return true;
    }
    else
    {
        printf("\t\tCPF não é válido\n");
        return false;
    }
}

bool primeiroPasso(char cpf[])
{
    int soma = 0;
    int aux = 10;

    for (int i = 0; i < 9; i++)
    {
        soma += (cpf[i] - '0') * aux;
        aux--;
    }

    int verificador = 0, resto = 0;
    resto = (soma % 11);

    if (resto < 2)
    {
        verificador = 0;
    }
    else
    {
        verificador = 11 - resto;
    }

    if (verificador == (cpf[9] - '0'))
    {
        return segundoPasso(cpf);
    }
    else
    {
        printf("\t\tCPF não é valido! Por favor, digite novamente.\n");
        return false;
    }
}

bool verificaCPF(char cpf[])
{
    bool todosIguais = true;
    int soNumero = 1;

    if (strlen(cpf) != 11)
    {
        printf("\t\tCPF precisa ter 11 dígitos! Por favor, digite novamente.\n");
        return false;
    }
    else
    {
        for (int i = 0; i < 11; i++)
        {
            if (cpf[i] != cpf[0])
            {
                todosIguais = false;
                break;
            }
        }

        for (int i = 0; cpf[i] != '\0'; i++)
        {
            if (!isdigit(cpf[i]))
            {
                soNumero = 0;
                break;
            }
        }

        if (todosIguais)
        {
            printf("\t\tCPF inválido! Todos os dígitos são iguais. Por favor, digite novamente.\n");
            return false;
        }
        else if (!soNumero)
        {
            printf("\t\tCPF inválido! Contêm caracteres não numéricos. Por favor, digite novamente.\n");
            return false;
        }
        else
        {
            return primeiroPasso(cpf);
        }
    }
}

bool cpfJaCadastrado(struct Clientes *cliente, int quantidadeClientes, const char cpf[])
{
    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (strcmp(cliente[i].cpf, cpf) == 0)
        {
            return true; // CPF já existe
        }
    }
    return false; // CPF não existe
}

int validarNome(const char *nome)
{
    for (int i = 0; nome[i] != '\0'; i++)
    {
        if (!isalpha(nome[i]) && nome[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int validarNumero(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

void cadastrarCliente(struct Clientes *cliente, int *quantidadeClientes, FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);

    int quantidade;
    printf("\t\t==> Quantos clientes deseja cadastrar? ");
    while (scanf("%d", &quantidade) != 1) {
            printf("\t\tEntrada inválida. Por favor, digite um número inteiro.");
            printf("\n\t\t==> Quantos clientes deseja cadastrar? ");
            while (getchar() != '\n');
    }

    for (int i = 0; i < quantidade; i++)
    {
        char cpf[12];
        while (true)
        {
            printf("\t\t==> Digite o CPF do cliente (somente números): ");
            scanf("%11s", cpf);

            if (cpfJaCadastrado(cliente, *quantidadeClientes, cpf))
            {
                printf("\t\tCPF já cadastrado. Tente novamente.\n");
            }
            else
            {
                if (verificaCPF(cpf))
                {
                    strcpy(cliente[*quantidadeClientes].cpf, cpf);
                    cliente[*quantidadeClientes].ativo = 1;
                    (*quantidadeClientes)++; // Incrementa a quantidade de clientes
                    break;
                }
            }
        }

        do
        {
            printf("\t\t==> Digite o nome do cliente: ");
            scanf(" %[^\n]", cliente[*quantidadeClientes - 1].nome);

            if (!validarNome(cliente[*quantidadeClientes - 1].nome))
            {
                printf("\t\tNome inválido! Por favor, insira apenas letras.\n");
            }
        } while (!validarNome(cliente[*quantidadeClientes - 1].nome));

        // Coleta informações do cliente
        do
        {
            printf("\t\t==> Digite o nome da rua do cliente %d: ", i + 1);
            fflush(stdin);
            fgets(cliente[*quantidadeClientes - 1].nomeRua, sizeof(cliente[*quantidadeClientes - 1].nomeRua), stdin);
            cliente[*quantidadeClientes - 1].nomeRua[strcspn(cliente[*quantidadeClientes - 1].nomeRua, "\n")] = '\0';

            if (!validarNome(cliente[*quantidadeClientes - 1].nomeRua))
            {
                printf("\t\tNome inválido! Por favor, insira apenas letras.\n");
            }
        } while (!validarNome(cliente[*quantidadeClientes - 1].nomeRua));

        do
        {
            printf("\t\t==> Digite o número da casa do cliente %d: ", i + 1);
            fflush(stdin);
            fgets(cliente[*quantidadeClientes - 1].numeroCasa, sizeof(cliente[*quantidadeClientes - 1].numeroCasa), stdin);
            cliente[*quantidadeClientes - 1].numeroCasa[strcspn(cliente[*quantidadeClientes - 1].numeroCasa, "\n")] = '\0';

            if (!validarNumero(cliente[*quantidadeClientes - 1].numeroCasa))
            {
                printf("\t\tEntrada inválida! Por favor, insira apenas números.\n");
            }
        } while (!validarNumero(cliente[*quantidadeClientes - 1].numeroCasa));

        do
        {
            printf("\t\t==> Digite o complemento (número da casa/apartamento) do cliente %d: ", i + 1);
            fflush(stdin);
            fgets(cliente[*quantidadeClientes - 1].complemento, sizeof(cliente[*quantidadeClientes - 1].complemento), stdin);
            cliente[*quantidadeClientes - 1].complemento[strcspn(cliente[*quantidadeClientes - 1].complemento, "\n")] = '\0';

            if (!validarNumero(cliente[*quantidadeClientes - 1].complemento))
            {
                printf("\t\tEntrada inválida! Por favor, insira apenas números.\n");
            }
        } while (!validarNumero(cliente[*quantidadeClientes - 1].complemento));

        do
        {
            printf("\t\t==> Digite seu telefone (somente os números) do cliente %d: ", i + 1);
            fflush(stdin);
            fgets(cliente[*quantidadeClientes - 1].telefone, sizeof(cliente[*quantidadeClientes - 1].telefone), stdin);
            cliente[*quantidadeClientes - 1].telefone[strcspn(cliente[*quantidadeClientes - 1].telefone, "\n")] = '\0';

            if (!validarNumero(cliente[*quantidadeClientes - 1].telefone))
            {
                printf("\t\tEntrada inválida! Por favor, insira apenas números.\n");
            }
        } while (!validarNumero(cliente[*quantidadeClientes - 1].telefone));

        fprintf(arquivo, "Nome: %s\nCPF: %s\nNome da rua: %s\nNumero da rua: %s\nComplemento: %s\nTelefone: %s\nAtivo: %d\n",
                cliente[*quantidadeClientes - 1].nome, cliente[*quantidadeClientes - 1].cpf,
                cliente[*quantidadeClientes - 1].nomeRua, cliente[*quantidadeClientes - 1].numeroCasa,
                cliente[*quantidadeClientes - 1].complemento, cliente[*quantidadeClientes - 1].telefone,
                cliente[*quantidadeClientes - 1].ativo);

        printf("\n\t\tCliente cadastrado com sucesso!\n");
    }
}

void lerClientesDoArquivo(struct Clientes *cliente, int *quantidadeClientes, FILE *arquivo)
{
    rewind(arquivo);
    *quantidadeClientes = 0;

    while (fscanf(arquivo, "Nome: %s\nCPF: %s\nNome da rua: %s\nNumero da rua: %s\nComplemento: %s\nTelefone: %s\nAtivo: %d\n",
                  cliente[*quantidadeClientes].nome, cliente[*quantidadeClientes].cpf, cliente[*quantidadeClientes].nomeRua, cliente[*quantidadeClientes].numeroCasa,
                  cliente[*quantidadeClientes].complemento, cliente[*quantidadeClientes].telefone, &cliente[*quantidadeClientes].ativo) == 7)
    {

        if (cliente[*quantidadeClientes].ativo == 1 || cliente[*quantidadeClientes].ativo == 0)
        {
            (*quantidadeClientes)++;
        }
    }
}

void quickSortAlfabetica(struct Clientes *cliente, int inicio, int fim)
{
    if (inicio < fim)
    {
        int pivo = inicio;
        int i = inicio;
        int j = fim;
        struct Clientes temp;

        while (i < j)
        {
            while (strcmp(cliente[i].nome, cliente[pivo].nome) <= 0 && i < fim)
            {
                i++;
            }

            while (strcmp(cliente[j].nome, cliente[pivo].nome) > 0)
            {
                j--;
            }

            if (i < j)
            {
                temp = cliente[i];
                cliente[i] = cliente[j];
                cliente[j] = temp;
            }
        }

        temp = cliente[inicio];
        cliente[inicio] = cliente[j];
        cliente[j] = temp;

        quickSortAlfabetica(cliente, inicio, j - 1);
        quickSortAlfabetica(cliente, j + 1, fim);
    }
}

// troca para ordenação de acordo com o cpf
void quickSortNumerica(struct Clientes *cliente, int inicio, int fim)
{
    if (inicio < fim)
    {
        int i = inicio;
        int j = fim;
        struct Clientes temp;
        int pivotIndex = (inicio + fim) / 2;
        struct Clientes pivotElement = cliente[pivotIndex];

        while (i <= j)
        {
            // substituido atoi para strcmp, fazendo funcionar
            while (cliente[i].ativo == 1 && strcmp(cliente[i].cpf, pivotElement.cpf) < 0)
            {
                i++;
            }
            while (cliente[j].ativo == 1 && strcmp(cliente[j].cpf, pivotElement.cpf) > 0)
            {
                j--;
            }

            if (i <= j)
            {
                temp = cliente[i];
                cliente[i] = cliente[j];
                cliente[j] = temp;
                i++;
                j--;
            }
        }

        if (inicio < j)
        {
            quickSortNumerica(cliente, inicio, j);
        }

        if (i < fim)
        {
            quickSortNumerica(cliente, i, fim);
        }
    }
}

void desativarCliente(struct Clientes *cliente, int quantidadeClientes, const char *cpfDesativar, FILE *arquivo)
{
    int encontrado = 0;

    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (strcmp(cliente[i].cpf, cpfDesativar) == 0)
        {
            cliente[i].ativo = 0;
            encontrado = 1;

            fclose(arquivo);
            arquivo = fopen("clientes.txt", "w");
            if (arquivo == NULL)
            {
                printf("\t\tErro ao abrir o arquivo para escrita.\n");
                return;
            }

            for (int j = 0; j < quantidadeClientes; j++)
            {
                fprintf(arquivo, "Nome: %s\nCPF: %s\nNome da rua: %s\nNumero da rua: %s\nComplemento: %s\nTelefone: %s\nAtivo: %d\n",
                        cliente[j].nome, cliente[j].cpf, cliente[j].nomeRua, cliente[j].numeroCasa, cliente[j].complemento, cliente[j].telefone,
                        cliente[j].ativo);
            }

            break;
        }
    }

    if (!encontrado)
    {
        printf("\t\tCliente com CPF %s não encontrado.\n", cpfDesativar);
    }
}


void listarCliente(struct Clientes *cliente, int quantidadeClientes, int opcaoOrdenacao)
{
    if (quantidadeClientes == 0)
    {
        printf("\n\t\tNenhum cliente cadastrado.\n");
        return;
    }

    if (opcaoOrdenacao == 1)
    {
        quickSortAlfabetica(cliente, 0, quantidadeClientes - 1);
    }
    else if (opcaoOrdenacao == 2)
    {
        quickSortNumerica(cliente, 0, quantidadeClientes - 1);
    }
    else
    {
        printf("\n\t\tOpção inválida.\n");
        return;
    }

    printf("\n\t\tLista de clientes:\n");
    printf("\t\t************************************************\n");

    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (cliente[i].ativo == 1)
        {
            printf("\t\tCliente %d\n", i + 1);
            printf("\t\tNome: %s\n", cliente[i].nome);
            printf("\t\tCPF: %s\n", cliente[i].cpf);
            printf("\t\tNome da rua: %s\n", cliente[i].nomeRua);
            printf("\t\tNúmero da rua: %s\n", cliente[i].numeroCasa);
            printf("\t\tComplemento: %s\n", cliente[i].complemento);
            printf("\t\tTelefone: %s\n", cliente[i].telefone);
            printf("\t\t************************************************\n");
        }
    }
}

int compareClientes(const void *a, const void *b)
{
    return strcmp(((struct Clientes *)a)->cpf, ((struct Clientes *)b)->cpf);
}

void consultarCliente(struct Clientes *cliente, int quantidadeClientes, char cpfConsultar[])
{
    qsort(cliente, quantidadeClientes, sizeof(struct Clientes), compareClientes);

    int encontrado = 0;
    int inicio = 0, fim = quantidadeClientes - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int comparar = strcmp(cpfConsultar, cliente[meio].cpf);

        if (comparar == 0)
        {
            printf("\n\t\t************************************************\n");
            printf("\t\tNome: %s\n", cliente[meio].nome);
            printf("\t\tCPF: %s\n", cliente[meio].cpf);
            printf("\t\tEndereço: %s\n", cliente[meio].nomeRua);
            printf("\t\tNúmero da rua: %s\n", cliente[meio].numeroCasa);
            printf("\t\tComplemento: %s\n", cliente[meio].complemento);
            printf("\t\tTelefone: %s\n", cliente[meio].telefone);

            encontrado = 1;
            break;
        }
        else if (comparar < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    if (!encontrado)
    {
        printf("\t\tCPF não cadastrado.\n");
    }
}

void excluirCliente(struct Clientes *cliente, int *quantidadeClientes, const char *cpfExcluir, FILE *arquivo)
{
    int encontrado = 0;

    for (int i = 0; i < *quantidadeClientes; i++)
    {
        if (strcmp(cliente[i].cpf, cpfExcluir) == 0)
        {
            cliente[i].ativo = 2;
            encontrado = 1;

            // Desloca todos os elementos após o cliente excluído uma posição para trás
            for (int j = i; j < *quantidadeClientes - 1; j++)
            {
                cliente[j] = cliente[j + 1];
            }
            (*quantidadeClientes)--; // Diminui a quantidade de clientes
            
            // Atualizar o arquivo com a nova situação dos clientes
            fclose(arquivo);
            arquivo = fopen("clientes.txt", "w");
            if (arquivo == NULL)
            {
                printf("\t\tErro ao abrir o arquivo para escrita.\n");
                return;
            }
            
            break;
        }
    }

    if (!encontrado)
    {
        printf("\t\tCliente com CPF %s não encontrado.\n", cpfExcluir);
    }
    else
    {
        printf("\t\tCliente com CPF %s excluído com sucesso.\n", cpfExcluir);
    }
}

void salvarClientes(struct Clientes *cliente, int quantidadeClientes, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("\t\tErro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (cliente[i].ativo != 2)  // Ignora clientes com ativo == 2 (excluídos)
        {
            fprintf(arquivo, "Nome: %s\nCPF: %s\nNome da rua: %s\nNumero da rua: %s\nComplemento: %s\nTelefone: %s\nAtivo: %d\n",
                    cliente[i].nome, cliente[i].cpf, cliente[i].nomeRua, cliente[i].numeroCasa, cliente[i].complemento, cliente[i].telefone, cliente[i].ativo);
        }
    }

    fclose(arquivo);
}

struct Clientes *buscarCliente(struct Clientes *clientes, int quantidadeClientes, const char *cpf)
{
    for (int i = 0; i < quantidadeClientes; i++)
    {
        if (clientes[i].ativo && strcmp(clientes[i].cpf, cpf) == 0)
        {
            return &clientes[i];
        }
    }
    return NULL; // null se o cliente não for encontrado
}

void realizarPedido(struct Clientes *clientes, int quantidadeClientes)
{
    static int idPedido = 1;
    int sabor, tamanho, quantidade;
    float preco = 0.0, totalPedido = 0.0;
    int totalQuantidade = 0;
    char adicionarOutroSabor, novoCliente;
    char cpf[12];

    char *saborEscolhido;
    saborEscolhido = (char*)malloc(21*sizeof(char));

    FILE *arquivoPedidos;

    do
    {
        printf("\t\t==> Digite o CPF do cliente para realizar o pedido (somente números): ");
        scanf("%s", &cpf);

        while(verificaCPF(cpf) == false){
            printf("\t\t==> Digite o CPF do cliente para realizar o pedido (somente números): ");
            scanf("%s", &cpf);
        }

        struct Clientes *cliente = buscarCliente(clientes, quantidadeClientes, cpf);
        if (cliente == NULL)
        {
            printf("\t\tCliente não encontrado ou inativo.\n");
            return;
        }

        arquivoPedidos = fopen("pedidos.txt", "a");

        if (arquivoPedidos == NULL)
        {
            printf("Erro ao abrir o arquivo de pedidos.\n");
            return;
        }

        fprintf(arquivoPedidos, "Pedido %d:\n", idPedido);

        do
        {
            printf("\n");
            printf("\t\t************************************************\n");
            printf("\t\t*                    Menu                      *\n");
            printf("\t\t************************************************\n");
            printf("\t\t*     Escolha o sabor:                         *\n");
            printf("\t\t*     1 - Calabresa                            *\n");
            printf("\t\t*     2 - Quatro Queijos                       *\n");
            printf("\t\t*     3 - Frango com Catupiry                  *\n");
            printf("\t\t************************************************\n");
            printf("\n\t\t==> Digite o número do sabor desejado: ");

            while(scanf("%d", &sabor) != 1){
                printf("\t\tEntrada inválida. Por favor, digite um número inteiro.\n");
                printf("\t\t==> Digite o número do sabor desejado: ");
                while (getchar() != '\n');
            };

            switch (sabor)
            {
                case 1:
                    strcpy(saborEscolhido, "Calabresa");
                    printf("\n");
                    printf("\t\t************************************************\n");
                    printf("\t\t*            Você escolheu Calabresa.          *\n");
                    printf("\t\t************************************************\n");
                    printf("\t\t*            Escolha o tamanho:                *\n");
                    printf("\t\t*        1 - Pequena (4 fatias) - R$20.00      *\n");
                    printf("\t\t*        2 - Média (8 fatias) - R$30.00        *\n");
                    printf("\t\t*        3 - Grande (12 fatias) - R$40.00      *\n");
                    printf("\t\t************************************************\n");
                    printf("\n\t\t==> Digite o número do tamanho desejado: ");
                    fflush(stdin);

                    while(scanf("%d", &tamanho) != 1){
                        printf("\t\tEntrada inválida. Por favor, digite um número inteiro.\n");
                        printf("\t\t==> Digite o número do tamanho desejado: ");
                        while (getchar() != '\n');
                    };

                    if (tamanho == 1)
                        preco = 20.0;
                    else if (tamanho == 2)
                        preco = 30.0;
                    else if (tamanho == 3)
                        preco = 40.0;
                    else
                        printf("Tamanho inválido.\n");
                    break;
                case 2:
                    strcpy(saborEscolhido, "Quatro Queijos");
                    printf("\n");
                    printf("\t\t************************************************\n");
                    printf("\t\t*         Você escolheu Quatro Queijos.        *\n");
                    printf("\t\t************************************************\n");
                    printf("\t\t*            Escolha o tamanho:                *\n");
                    printf("\t\t*         1 - Pequena (4 fatias) - R$25.00     *\n");
                    printf("\t\t*         2 - Média (8 fatias) - R$35.00       *\n");
                    printf("\t\t*         3 - Grande (12 fatias) - R$45.00     *\n");
                    printf("\t\t************************************************\n");
                    printf("\n\t\t==> Digite o número do tamanho desejado: ");
                    
                    while(scanf("%d", &tamanho) != 1){
                        printf("\t\tEntrada inválida. Por favor, digite um número inteiro.\n");
                        printf("\t\t==> Digite o número do tamanho desejado: ");
                        while (getchar() != '\n');
                    };
                    
                    if (tamanho == 1)
                        preco = 25.0;
                    else if (tamanho == 2)
                        preco = 35.0;
                    else if (tamanho == 3)
                        preco = 45.0;
                    else
                        printf("Tamanho inválido.\n");
                    break;
                case 3:
                    strcpy(saborEscolhido, "Frango com Catupiry");
                    printf("\n");
                    printf("\t\t************************************************\n");
                    printf("\t\t*       Você escolheu Frango com Catupiry.     *\n");
                    printf("\t\t************************************************\n");
                    printf("\t\t*            Escolha o tamanho:                *\n");
                    printf("\t\t*       1 - Pequena (4 fatias) - R$22.00       *\n");
                    printf("\t\t*       2 - Média (8 fatias) - R$32.00         *\n");
                    printf("\t\t*       3 - Grande (12 fatias) - R$42.00       *\n");
                    printf("\t\t************************************************\n");
                    printf("\n\t\t==> Digite o número do tamanho desejado: ");
                    
                    while(scanf("%d", &tamanho) != 1){
                        printf("\t\tEntrada inválida. Por favor, digite um número inteiro.\n");
                        printf("\t\t==> Digite o número do tamanho desejado: ");
                        while (getchar() != '\n');
                    };

                    if (tamanho == 1)
                        preco = 22.0;
                    else if (tamanho == 2)
                        preco = 32.0;
                    else if (tamanho == 3)
                        preco = 42.0;
                    else
                        printf("\t\tTamanho inválido.\n");
                    break;
                    default:
                        printf("\n\t\tSabor inválido.\n");
                        fclose(arquivoPedidos);
                        return;
            }

            if (preco > 0)
            {
                printf("\t\t==> Quantas pizzas deste tipo você deseja? ");

                while(scanf("%d", &quantidade) != 1){
                    printf("\t\tEntrada inválida. Por favor, digite um número inteiro.\n");
                    printf("\t\t==> Quantas pizzas deste tipo você deseja? ");
                    while (getchar() != '\n');
                };

                totalPedido += preco * quantidade;
                totalQuantidade += quantidade;

                fprintf(arquivoPedidos, "%d pizza %s %s\n", quantidade, saborEscolhido, (tamanho == 1) ? "pequena" : (tamanho == 2) ? "media"
                                                                                                                                    : "grande");
            }

            printf("\t\t==> Deseja adicionar outra pizza ao pedido? (s/n): ");
            
            while (1) {
                scanf(" %c", &adicionarOutroSabor);

                if (adicionarOutroSabor == 's' || adicionarOutroSabor == 'S' ||
                    adicionarOutroSabor == 'n' || adicionarOutroSabor == 'N') {
                    break; 
                } else {
                    printf("\t\tEntrada inválida. Por favor, digite 's' ou 'n'.\n");
                    printf("\t\t==> Deseja adicionar outra pizza ao pedido? (s/n): ");
                    while (getchar() != '\n');
                }
            }

        } while (adicionarOutroSabor == 's' || adicionarOutroSabor == 'S');

        printf("\n");
        printf("    ****************************************************************************\n");
        printf("              Resumo do Pedido #%d:\n", idPedido);
        printf("              Cliente: %s\n", cliente->nome);
        printf("              CPF: %s\n", cliente->cpf);
        printf("              Endereço de Entrega: Rua %s, Nº %s, Complemento: %s\n",
               cliente->nomeRua, cliente->numeroCasa, cliente->complemento);
        printf("              Quantidade Total de Pizzas: %d\n", totalQuantidade);
        printf("              Total do Pedido: R$%.2f\n", totalPedido);
        printf("    ****************************************************************************\n");
        printf("\n");

        fprintf(arquivoPedidos, "Endereco: Rua %s, Nº %s, Complemento: %s\n\n",
                cliente->nomeRua, cliente->numeroCasa, cliente->complemento);

        fclose(arquivoPedidos);

        idPedido++;
        totalPedido = 0.0;
        totalQuantidade = 0;

        printf("\t\t==> Deseja realizar um novo pedido para outro cliente? (s/n): ");
        
        while (1) {
            scanf(" %c", &novoCliente);

            if (novoCliente == 's' || novoCliente == 'S' ||
                novoCliente == 'n' || novoCliente == 'N') {
                break; 
            } else {
                printf("\t\tEntrada inválida. Por favor, digite 's' ou 'n'.\n");
                printf("\t\t==> Deseja realizar um novo pedido para outro cliente? (s/n): ");
                while (getchar() != '\n');
            }
        }

    } while (novoCliente == 's' || novoCliente == 'S');

    free(saborEscolhido);
}

int main()
{
    //setlocale(LC_ALL, "Portuguese"); 
    system("chcp 65001"); // para os caracteres especiais
    system("cls");

    FILE *arquivo;
    int opcao, quantidadeClientes = 0, idDesativar, opcaoOrdenacao, idExcluir;
    char cpfConsultar[12], cpfPedido[12];
    int capacidadeClientes = 10;

    arquivo = fopen("clientes.txt", "a+");
    if (arquivo == NULL)
    {
        printf("\t\tProblema ao abrir o arquivo");
        return 1;
    }

    struct Clientes *cliente = malloc(capacidadeClientes * sizeof(struct Clientes));
    if (cliente == NULL)
    {
        printf("\n\t\tErro na alocação de memória.");
        return 1;
    }

    // se a quantidade de clientes ultrapassar a capacidade alocada fazemos um realloc com o dobro de capacidade
    if (quantidadeClientes >= capacidadeClientes) {
        capacidadeClientes *= 2;
        cliente = realloc(cliente, capacidadeClientes * sizeof(struct Clientes));
        if (cliente == NULL) {
            printf("\n\t\tErro ao realocar memória.");
            return 1;
        }
    }   

    lerClientesDoArquivo(cliente, &quantidadeClientes, arquivo);

    pizza();

    do
    {
        printf("\n");
        printf("\t\t************************************************\n");
        printf("\t\t*           Bem-vindo à Pizzada Certa!         *\n");
        printf("\t\t************************************************\n");
        printf("\t\t*    1 - Cadastrar um cliente                  *\n");
        printf("\t\t*    2 - Listar cliente                        *\n");
        printf("\t\t*    3 - Consultar um cliente a partir do CPF  *\n");
        printf("\t\t*    4 - Desativar um cliente                  *\n");
        printf("\t\t*    5 - Excluir um cliente                    *\n");
        printf("\t\t*    6 - Realizar um pedido                    *\n");
        printf("\t\t*    7 - Sair                                  *\n");
        printf("\t\t************************************************\n");
        printf("\n\t\t==> Escolha uma opção: ");
       
        while (scanf("%d", &opcao) != 1) {
            printf("\t\tEntrada inválida. Por favor, digite um número inteiro.");
            printf("\n\t\t==> Escolha uma opção: ");
            while (getchar() != '\n');
        }

        switch (opcao)
        {
            case 1:
                cadastrarCliente(cliente, &quantidadeClientes, arquivo);
                break;
            case 2:
                printf("\t\t==> Deseja listar os clientes em ordem alfabética (1) ou númerica (2)? ");
               
                while (scanf("%d", &opcaoOrdenacao) != 1) {
                    printf("\t\tEntrada inválida. Por favor, digite um número inteiro.");
                    printf("\n\t\t==> Deseja listar os clientes em ordem alfabética (1) ou númerica (2)? ");
                    while (getchar() != '\n');
                }

                listarCliente(cliente, quantidadeClientes, opcaoOrdenacao);
                break;
            case 3:
                printf("\t\t==> Informe o CPF do cliente que você deseja consultar: ");
                scanf("%s", &cpfConsultar);

                while(verificaCPF(cpfConsultar) == false){
                    printf("\t\t==> Informe o CPF do cliente que você deseja consultar: ");
                    scanf("%s", &cpfConsultar);
                }

                consultarCliente(cliente, quantidadeClientes, cpfConsultar);
                break;
            case 4: {
            char cpfDesativar[12];
            printf("\t\t==> Informe o CPF do cliente que deseja desativar: ");
    
            while (scanf("%11s", cpfDesativar) != 1 || strlen(cpfDesativar) != 11) {
                printf("\t\tEntrada inválida. Por favor, digite um CPF com 11 dígitos.\n");
                printf("\t\t==> Informe o CPF do cliente que deseja desativar: ");
            while (getchar() != '\n');
            }
    
            desativarCliente(cliente, quantidadeClientes, cpfDesativar, arquivo);
            printf("\t\tCliente com CPF %s foi desativado com sucesso.\n", cpfDesativar);
            break;
            }

            case 5: {
            char cpfExcluir[12];
            int encontrado = 0;

            while (!encontrado) {
                printf("\t\t==> Informe o CPF do cliente que deseja excluir: ");
                scanf("%11s", cpfExcluir);

                for (int i = 0; i < quantidadeClientes; i++) {
                    if (strcmp(cliente[i].cpf, cpfExcluir) == 0 && cliente[i].ativo != 2) {
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("\t\tCPF não encontrado ou cliente já excluído. Tente novamente.\n");
                }
            }

            excluirCliente(cliente, &quantidadeClientes, cpfExcluir, arquivo);
            salvarClientes(cliente, quantidadeClientes, "clientes.txt");
            break;
        }
            case 6:
                realizarPedido(cliente, quantidadeClientes);
                break;
            case 7:
                printf("\t\tSaindo do programa.\n");
                break;
            default:
                printf("\t\tOpção inválida. Por favor, digite um dos números do menu.\n");
                break;
        }
    } while (opcao != 7);

    free(cliente);

    if (fclose(arquivo) == 0)
    {
        printf("\n\t\tArquivo fechado corretamente.");
        return 0;
    }
    else
    {
        printf("\n\t\tProblema ao fechar o arquivo.");
        return 1;
    }
    return 0;
}