#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente
{
    char nomeCliente [50];
    char sexo;
    int idade;
};

typedef struct Cliente cliente;

struct Venda
{
    char nomeCliente [50];
    int qtdVendas;
    int qtdAdicionais;
    char nomeModelo [50];
    float precoModelo;
    float valorAdicionais;
    float valorTotal;
};

typedef struct Venda venda;

void cadastro_clientes (cliente *clientes, int qtdClientes);
void cadastrar_vendas (venda *vendas, int qtdVendas, cliente *clientes, int qtdClientes);
void salvar_vendas (venda venda);
void buscarCliente ();
void ver_todas_vendas();

int opcao;

int main() {

    int qtdVendas, qtdClientes;

    cliente *clientes = NULL;
    venda *vendas = NULL;

    do{
        printf("Menu principal:\n\n");

        printf("1- Cadastrar novas vendas\n");
        printf("2- Ver informações de uma venda especifica (nome do cliente)\n");
        printf("3- Ver informações de todas as vendas\n");
        printf("4- Encerrar o programa\n\n");

        printf("Digite um numero para acessar o menu: ");
        scanf("%d", &opcao);
        getchar();


        printf("\n");

        switch (opcao)
        {
            case 1:

                printf("Quantos clientes deseja cadastrar?: ");
                scanf("%d", &qtdClientes);
                getchar();

                clientes = malloc (qtdClientes * sizeof(cliente));

                if (clientes == NULL)
                {
                    printf("Erro ao alocar na memória para clientes!\n");
                    return 1;
                }

                cadastro_clientes (clientes, qtdClientes);

                printf("\n");

                printf("Qual é a quantidade de vendas que serão cadastradas?: ");
                scanf("%d", &qtdVendas);
                getchar();

                printf("\n");

                vendas = malloc (qtdVendas * sizeof (venda));

                if (vendas == NULL)
                {
                    printf("Erro ao alocar na memória!\n");
                    return 1;
                }

                cadastrar_vendas (vendas, qtdVendas, clientes, qtdClientes);

                break;

            case 2:

                buscarCliente();

                break;

            case 3:

                ver_todas_vendas();


                break;


            case 4:
                printf("Programa encerrado!\n");
                    free (clientes);
                    free (vendas);
                break;

            default:
                printf("Opção inválida!\n\n");
        }
    } while (opcao != 4);

    return 0;
}



void salvar_vendas (venda venda)
{
    FILE *arquivo;

    arquivo = fopen ("vendas.txt", "a");

    if(arquivo == NULL)
    {
        printf("Erro ao salvar o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%s\n", venda.nomeCliente);
    fprintf(arquivo, "%d\n", venda.qtdAdicionais);
    fprintf(arquivo, "%s\n", venda.nomeModelo);
    fprintf(arquivo, "%.2f\n", venda.precoModelo);
    fprintf(arquivo, "%.2f\n", venda.valorAdicionais);
    fprintf(arquivo, "%.2f\n", venda.valorTotal);

    fclose(arquivo);

}


void buscarCliente()
{
    FILE *arquivo;
    char buscarNome [50];
    char nomeArquivo [50];
    char nomeModelo[50];
    int qtdAdicionais;
    float precoModelo , valorAdicionais, total;

    int desejaPesquisarNovamente = 1;
    char opcao_pesquisa;

    do
    {
        arquivo = fopen ("vendas.txt", "r");

        if(arquivo == NULL)
        {
            printf("\nErro ao abrir o arquivo. Nenhuma venda registrada.\n");
            return;
        }

        printf("Digite o nome do cliente a ser pesquisado: ");

        fgets(buscarNome, sizeof(buscarNome), stdin);
        buscarNome[strcspn(buscarNome, "\n")] = 0;

        int clienteEncontrado = 0;
        int numCompras = 0;
        float somaTotal = 0.0;

        rewind(arquivo);

        while (fgets(nomeArquivo, sizeof(nomeArquivo),arquivo)!= NULL)
        {
            nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;

            fscanf(arquivo, "%d", &qtdAdicionais);

            fgetc(arquivo);

            fgets(nomeModelo, sizeof(nomeModelo), arquivo);
            nomeModelo[strcspn(nomeModelo, "\n")] = 0;

            fscanf(arquivo, "%f", &precoModelo);
            fscanf(arquivo, "%f", &valorAdicionais);
            fscanf(arquivo, "%f", &total);

            char c;
            while ((c = fgetc(arquivo)) != '\n' && c != EOF);

            if(strcmp(buscarNome, nomeArquivo) == 0)
            {
                printf("\n--- Venda Encontrada ---\n");
                printf("Modelo: %s\n", nomeModelo);
                printf("Adicionais: %d\n", qtdAdicionais);
                printf("Valor adicionais: R$%.2f\n", valorAdicionais);
                printf("Valor total: R$%.2f\n", total);
                printf("------------------------\n");

                clienteEncontrado = 1;
                numCompras++;
                somaTotal += total;
            }
        }

        fclose(arquivo);

        if (clienteEncontrado)
        {
            float media = somaTotal / numCompras;
            printf("\nClientes: %s\n", buscarNome);
            printf("Total de compras encontradas: %d\n", numCompras);
            printf("Valor médio das compras: R$%.2f\n", media);
        }
        else
        {
            printf("\nNão há compras registradas para o cliente: %s\n", buscarNome);
        }

        printf("\nDeseja pesquisar outro cliente? (S/N): ");
        scanf(" %c", &opcao_pesquisa);
        getchar();
        if (opcao_pesquisa == 'N' || opcao_pesquisa == 'n') {
            desejaPesquisarNovamente = 0;
        }

    } while (desejaPesquisarNovamente);
}

void ver_todas_vendas()
{
    FILE *arquivo;
    char nomeArquivo [50];
    char nomeModelo[50];
    int qtdAdicionais;
    float precoModelo , valorAdicionais, total;

    int totalVendas = 0;
    float somaTotalVendas = 0.0;

    float valorLimite;

    int qtdVendasAcimaDoValor = 0;
    int qtdSomenteDoisAdicionais = 0;
    int totalAdicionaisVendidos = 0;

    char opcao_retorno;

    printf("\nDigite um valor limite para o filtro de vendas (R$): ");
    scanf("%f", &valorLimite);
    getchar();

    arquivo = fopen ("vendas.txt", "r");

    if(arquivo == NULL)
    {
        printf("\nNenhuma venda registrada.\n");
        return;
    }

    while (fgets(nomeArquivo, sizeof(nomeArquivo),arquivo)!= NULL)
    {

        nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;

        fscanf(arquivo, "%d", &qtdAdicionais);

        fgetc(arquivo);

        fgets(nomeModelo, sizeof(nomeModelo), arquivo);
        nomeModelo[strcspn(nomeModelo, "\n")] = 0;

        fscanf(arquivo, "%f", &precoModelo);
        fscanf(arquivo, "%f", &valorAdicionais);
        fscanf(arquivo, "%f", &total);

        char c;
        while ((c = fgetc(arquivo)) != '\n' && c != EOF);

        totalVendas++;
        somaTotalVendas += total;
        totalAdicionaisVendidos += qtdAdicionais;

        if (total > valorLimite) {
            qtdVendasAcimaDoValor++;
        }

        if (qtdAdicionais == 2) {
            qtdSomenteDoisAdicionais++;
        }

    }

    fclose(arquivo);

    printf("\n========== RELATÓRIO GERAL DE VENDAS ==========\n");
    printf("Total de Vendas Processadas: %d\n", totalVendas);
    printf("-----------------------------------------------\n");

    printf("Vendas acima de R$%.2f: %d\n", valorLimite, qtdVendasAcimaDoValor);
    printf("Vendas com exatamente 2 itens adicionais: %d\n", qtdSomenteDoisAdicionais);

    printf("Total de itens adicionais vendidos: %d\n", totalAdicionaisVendidos);
    printf("Valor total das vendas: R$%.2f\n", somaTotalVendas);
    printf("Valor médio de uma venda: R$%.2f\n", totalVendas > 0 ? somaTotalVendas / totalVendas : 0.0);

    printf("-----------------------------------------------\n");
    printf("\nRelatório concluído!\n");
    printf("Deseja retornar ao menu principal? (S/N para encerrar): ");
    scanf(" %c", &opcao_retorno);

    if (opcao_retorno == 'N' || opcao_retorno == 'n') {
        opcao = 4;
    }
}


void cadastro_clientes (cliente *clientes, int qtdClientes)
{
    for(int i = 0; i<qtdClientes; i++)
    {

        do{

            printf("\nNome do cliente: ");
            fgets(clientes[i].nomeCliente, sizeof(clientes[i].nomeCliente), stdin);

            if (strlen(clientes[i].nomeCliente) < 4)
            {
                printf("\nO nome deve ter 3 ou mais letras!\n");
            }

        } while (strlen(clientes[i].nomeCliente) < 4);

        do{

            printf("Sexo (m,f ou n): ");
            scanf(" %c", &clientes[i].sexo);

            if (clientes[i].sexo != 'm' && clientes[i].sexo != 'f' && clientes[i].sexo != 'n')
            {
                printf("\nSexo invalido\n");
            }

        } while (clientes[i].sexo != 'm' && clientes[i].sexo != 'f' && clientes[i].sexo != 'n');

        printf("Idade: ");
        scanf("%d", &clientes[i].idade);
        getchar();
    }

    printf("\nTodos os clientes foram cadastrados com sucesso!\n");
}

void cadastrar_vendas (venda *vendas, int qtdVendas, cliente *clientes, int qtdClientes)
{
    for (int i = 0; i< qtdVendas; i++)
    {
        char confirmacao;
        float valorUnitarioAdicional;

        do{


            do{

                printf("Nome do modelo: ");
                fgets (vendas[i].nomeModelo, sizeof(vendas[i].nomeModelo), stdin);

                printf("Preço base do modelo escolhido (em R$): ");
                scanf("%f", &vendas[i].precoModelo);

                getchar();

                if (vendas[i].precoModelo < 0)
                {
                    printf("\nO valor não pode ser negativo. Tente novamente!\n");
                }

            } while (vendas[i].precoModelo < 0);

            do{

                printf("Numero de itens adicionais: ");
                scanf("%d", &vendas[i].qtdAdicionais);

                if (vendas[i].qtdAdicionais < 0)
                {
                    printf("\nO valor não pode ser negativo. Tente novamente!\n");
                }

                else if (vendas[i].qtdAdicionais > 3)
                {
                    printf("Só é permitido até 3 adicionais!\n");
                }

            } while (vendas[i].qtdAdicionais < 0 || vendas[i].qtdAdicionais > 3);

            do{

                printf("Digite o valor do adicional (em R$): ");
                scanf("%f", &valorUnitarioAdicional);

                if (valorUnitarioAdicional < 0)
                {
                    printf("\nO valor não pode ser negativo. Tente novamente!\n");
                }

            } while (valorUnitarioAdicional < 0);

            vendas[i].valorAdicionais = vendas[i].qtdAdicionais * valorUnitarioAdicional;

            printf("\nRESUMO DA VENDA:\n");

            vendas[i].nomeModelo[strcspn(vendas[i].nomeModelo, "\n")] = 0;

            printf("Modelo: %s\n", vendas[i].nomeModelo);

            printf("Preço base: R$%.2f\n", vendas[i].precoModelo);

            printf("Adicionais: %d x R$%.2f = R$%.2f\n",
                vendas[i].qtdAdicionais, valorUnitarioAdicional, vendas[i].valorAdicionais);

            vendas[i].valorTotal = vendas[i].precoModelo + vendas[i].valorAdicionais;

            printf("Valor total: R$%.2f\n", vendas[i].valorTotal);

            strcpy(vendas[i].nomeCliente, clientes[i % qtdClientes].nomeCliente);

            vendas[i].nomeCliente[strcspn(vendas[i].nomeCliente, "\n")] = 0;



            printf("\nOs dados estão corretos? (S/N): ");
            scanf(" %c", &confirmacao);
            getchar();


        } while (confirmacao == 'N' || confirmacao == 'n');

        salvar_vendas(vendas[i]);

        printf("\nVenda %d cadastrada com sucesso!\n", i + 1);

        printf("\n");

    }
}