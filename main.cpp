#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#define TF 100
// DEFINIÇÃO DE STRUCTS
typedef struct
{
    int d, m, a;
} tpData;
typedef struct
{
    int codProd, estoque, codForn;
    char descricao[50];
    float preco;

    tpData data;
} tpProduto;
typedef struct
{
    int codForn;
    char nomeForn[50], cidadeForn[50];
} tpFornecedor;
typedef struct
{
    long long int cpfCliente, qtdeCompras;
    char nomeCliente[50];
    float valorTotalComprado;
} tpCliente;
typedef struct
{
    int codVenda;
    long int cpfCliente;
    tpData data;
    float totalVendas;
} tpVenda;
typedef struct
{
    int codVenda, codProd, qtde;
    float valorUnitario;
} tpVendasProdutos;

// DEFINIÇÃO DE "INTERFACES" DE FUNÇÕES

void executar();

// *** MENUS ***
char menuPrincipal(void);
char menuVendas(void);
char menuProdutos(void);
char menuFornecedores(void);
char menuClientes(void);

// *** AUXILIARES ***
void insercaoAutomDeDados(tpProduto produtos[TF], int &tlProdutos, tpCliente clientes[TF], int &tlClientes, tpFornecedor fornecedores[TF], int &tlFornecedores);
void moldura(int CI, int LI, int CF, int LF, int CorT, int CorF);
void exibirMoldura();
void limparMenu();
void limparTitulo();
void limparExecucao();
void limparMensagem();

// *** VENDAS ****
void efetuarVenda(tpVenda vendas[TF], int &tl, tpCliente clientes[TF], int &tlCLiente, tpProduto produtos[TF], int &tlProdutos, tpVendasProdutos vendasProdutos[TF], int &tlVendasProdutos, int &linha);
void relatorioDeVendas(tpVenda vendas[TF], int &tl);
void exclusaoDeVendas(tpVenda vendas[TF], int &tl, int &linha, tpCliente clientes[TF], int &tlCliente, tpProduto produtos[TF], int &tlProdutos, tpVendasProdutos vendasProdutos[TF], int &tlVendasProdutos);
int buscarCpfClienteVendas(tpVenda vendas[TF], int &tl, int cpf);

// *** CLIENTES ***
void cadastroCliente(tpCliente clientes[TF], int &tl, int &linha);
int buscaCliente(tpCliente clientes[TF], int tl, long int cpfCliente);
void exclusaoCliente(tpCliente clientes[TF], int &tl, int &linha);
void consultaClientes(tpCliente clientes[TF], int tl, int &linha);
void exclusaoClientes(tpCliente clientes[TF], int &tlClientes);
void alteracaoClientes(tpCliente clientes[TF], int tlClientes, int &linha);
void relatorioClientes(tpCliente fornecedores[TF], int tlFornecedores);

// *** PRODUTOS ***
void cadastroProdutos(tpProduto produtos[TF], int &tl, tpFornecedor fornecedores[TF], int &tlForn, int &linha, int veioDeCadForn);
int buscaProd(tpProduto produtos[TF], int tl, int codProduto);
int buscaProdPorFornecedor(tpProduto produtos[TF], int tl, int codForn);
void exclusaoProd(tpProduto produtos[TF], int &tl, int indice);
void exclusaoProdutos(tpProduto produtos[TF], int tlProdutos, int &Linha);
void consultaProdutos(tpProduto produtos[TF], int tlProdutos, int &linha, tpFornecedor fornecedores[TF]);
void alteracaoProdutos(tpProduto protudos[TF], int tlProdutos, int &linha);
void relatorioProdutos(tpProduto produtos[TF], int tlProdutos);

// *** FORNECEDORES ***
void cadastroForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd, int &linha, int veioDeCadProd);
int buscaForn(tpFornecedor fornecedores[TF], int tl, int codForn);
void exclusaoForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd, int &linha);
void consultaForn(tpFornecedor forncedores[TF], int tlForn, int &linha);
void alteracaoFornecedores(tpFornecedor fornecedores[TF], int tl, int &linha);
void relatorioFornecedores(tpFornecedor fornecedores[TF], int tl);
void aumentoDePreco(tpFornecedor fornecedores[TF], int tl, tpProduto produtos[TF], int tlProdutos, int &linha);

// FUNÇÕES

void insercaoAutomDeDados(tpProduto produtos[TF], int &tlProdutos, tpCliente clientes[TF], int &tlClientes, tpFornecedor fornecedores[TF], int &tlFornecedores)
{
    // add prod
    produtos[tlProdutos].codProd = 1;
    produtos[tlProdutos].estoque = 10;
    produtos[tlProdutos].preco = 12.99;
    produtos[tlProdutos].data.a = 2024;
    produtos[tlProdutos].data.d = 13;
    produtos[tlProdutos].data.m = 8;
    tlProdutos++;
    // add forn
    fornecedores[tlFornecedores].codForn = 22;
    strcpy(fornecedores[tlFornecedores].nomeForn, "mercado assai");
    strcpy(fornecedores[tlFornecedores].cidadeForn, "Prudente");
    tlFornecedores++;
    // add clientes
    strcpy(clientes[tlClientes].nomeCliente, "Daniel");
    clientes[tlClientes].cpfCliente = 23332176609;
    clientes[tlClientes].qtdeCompras = 3;
    clientes[tlClientes].valorTotalComprado = 239.49;
    tlClientes++;

    // adicionar mais feito so pra teste por enquanto
    return;
}

// adicionar mais dados
void exclusaoProdutos(tpProduto produtos[TF], int tlProdutos, int &linha)
{
    int codProd, aux;
    char op;
    linha = 7;
    system("cls");
    linha = 7;
    printf("__Exclusao de produtos__");

    do
    {
        clrscr();
        if (tlProdutos == 0)
        {
            gotoxy(41, linha);
            linha++;
            printf("Nao ha produtos para excluir");
            getch();
            linha = 7;
        }

        else
        {
            limparExecucao();
            linha = 7;
            gotoxy(41, linha);
            linha++;
            printf("Digite o codigo do produto a excluir");
            scanf("%d", &codProd);

            aux = buscaProd(produtos, tlProdutos, codProd);
            if (aux == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Codigo invalido ou produto inexistentedigite outro codigo");
                scanf("%d", &codProd);
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                puts(produtos[aux].descricao);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("%d", produtos[aux].codProd);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("%d", produtos[aux].estoque);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("%f", produtos[aux].preco);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("%d/%d/%d", produtos[aux].data.d, produtos[aux].data.m, produtos[aux].data.a);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;

                printf("confirma exclusao (S/N) ");
                op = toupper(getche());
                if (op == 'S')
                {
                    for (; aux < tlProdutos - 1; aux++)
                    {
                        produtos[aux] = produtos[aux + 1];
                    }
                    tlProdutos--;
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Produto excluido");
                    getch();
                }
            }
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Deseja excluir outro produto (S/N)");
            fflush(stdin);
            op = toupper(getche());
        }

    } while (op != 'S');

    return;
}

// pronto
void relatorioProdutos(tpProduto produtos[TF], int tlProdutos)
{
    system("cls");
    if (tlProdutos == 0)
    {
        printf("Nao ha produtos para exibir");
        getch();
    }
    else
    {
        for (int i = 0; i < tlProdutos; i++)
        {
            printf("*______________*");
            printf("Codigo do produto: %d", produtos[i].codProd);
            printf("Descricao do produto %s", produtos[i].descricao);
            printf("Estoque disponivel: %d", produtos[i].estoque);
            printf("Preco atual: %f", produtos[i].preco);
            printf("Data de validade do produto: %d/%d/%d", produtos[i].data.d, produtos[i].data.m, produtos[i].data.a);
            printf("*______________*");
            printf("");
        }
        printf(" [BACKSPACE] VOLTAR");
        getch();
    }
    return;
}

// sem teste feito por Daniel
void alteracaoProdutos(tpProduto produtos[TF], int tlProdutos, int &linha)
{
    int codProd, aux;
    char op;
    linha = 7;
    if (tlProdutos == 0)
    {
        gotoxy(41, linha);
        linha++;
        printf("Nao ha dados para alterar!!");
        gotoxy(41, linha);
        linha++;
        printf("Tecle algo para voltar");
        linha = 7;
        getch();
    }
    else
    {
        do
        {
            limparExecucao();
            linha = 7;
            gotoxy(41, linha);
            linha++;
            printf("Codigo do produto a ser alterado: ");
            scanf("%d", &codProd);
            aux = buscaProd(produtos, tlProdutos, codProd);
            if (aux == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Prod. nao encontrado");
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Codigo: %d", produtos[aux].codProd);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Descricao: ");
                puts(produtos[aux].descricao);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Estoque: %d", produtos[aux].estoque);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Preco: %f", produtos[aux].preco);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Data de validade: %d/%d/%d", produtos[aux].data.d, produtos[aux].data.m, produtos[aux].data.a);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Deseja alterar o produto acima: (S/N) ");
                fflush(stdin);
                op = toupper(getche());
                if (op == 'S')
                {
                    limparExecucao();
                    linha = 7;
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Nova descricao: ");
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    gets(produtos[aux].descricao);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Novo estoque: ");
                    scanf("%d", &produtos[aux].estoque);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Novo preco: ");
                    scanf("%f", &produtos[aux].preco);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Nova data de validade: ");
                    scanf("%d %d %d", &produtos[aux].data.d, &produtos[aux].data.m, &produtos[aux].data.a);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Produto alterado com sucesso!!");
                }
            }
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Continuar alteracao?: (S/N)");
            fflush(stdin);
            op = toupper(getche());
        } while (op == 'S');
    }
}

// sem teste feito por Daniel
void consultaProdutos(tpProduto produtos[TF], int tlProdutos, int &linha, tpFornecedor fornecedores[TF])
{
    int codProd, aux;
    linha = 7;
    if (tlProdutos == 0)
    {
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Nao ha produtos para consultar");
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Tecle algo para voltar");
        linha = 7;
        getch();
    }
    else
    {
        char continuar;

        do
        {

            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Codigo do produto a consultar: ");
            scanf("%d", &codProd);

            aux = buscaProd(produtos, tlProdutos, codProd);
            if (aux == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Produto não encontrado");
            }
            else
            {
                limparExecucao();
                linha = 7;
                gotoxy(41, linha);
                linha++;
                printf("Codigo: %d", produtos[aux].codProd);
                gotoxy(41, linha);
                linha++;
                printf("Descricao: %s", produtos[aux].descricao);
                gotoxy(41, linha);
                linha++;
                printf("Estoque: %d", produtos[aux].estoque);
                gotoxy(41, linha);
                linha++;
                printf("Preco: R$ %.2f", produtos[aux].preco);
                gotoxy(41, linha);
                linha++;
                printf("Data de validade: %d/%d/%d", produtos[aux].data.d, produtos[aux].data.m, produtos[aux].data.a);
                aux = buscaProdPorFornecedor(produtos, tlProdutos, produtos[aux].codForn);
                gotoxy(41, linha);
                linha++;
                printf("Fornecedor: ");
                puts(fornecedores[aux].nomeForn);
            }
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Continuar consulta? (S/N) ");
            continuar = toupper(getche());
        } while (continuar != 'N');
    }
}

void cadastroProdutos(tpProduto produtos[TF], int &tl, tpFornecedor fornecedores[TF], int &tlForn, int &linha, int veioDeCadForn)
{
    char continuar;
    do
    {

        int pos, codProd, codFornecedor;
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Digite o codigo do produto: ");
        scanf("%d", &codProd);
        pos = buscaProd(produtos, tl, codProd);
        if (pos != -1)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Produto ja cadastrado!");
            return;
        }
        produtos[tl].codProd = codProd;
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Digite o codigo do fornecedor: ");
        scanf("%d", &codFornecedor);
        pos = buscaForn(fornecedores, tlForn, codFornecedor);
        if (pos == -1 && veioDeCadForn == 0)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Fornecedor nao cadastrado!");
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Cadastrar fornecedor? (S/N) ");
            char cadFor = toupper(getche());
            if (cadFor == 'S')
            {
                cadastroForn(fornecedores, tlForn, produtos, tl, linha, 1);
            }
        }
        while (pos == -1)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Digite o codigo do fornecedor: ");
            scanf("%d", &codFornecedor);
            pos = buscaForn(fornecedores, tlForn, codFornecedor);
        }

        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Estoque desse produto: ");
        scanf("%d", &produtos[tl].estoque);
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Descricao : ");
        fflush(stdin);
        gets(produtos[tl].descricao);
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Digite o preco do produto: ");
        scanf("%f", &produtos[tl].preco);
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Data de validade do produto: ");
        scanf("%d/%d/%d", &produtos[tl].data.d, &produtos[tl].data.m, &produtos[tl].data.a);
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Produto cadastrado com sucesso!");
        tl++;

        if (tl < TF)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Cadastrar mais produtos? (S/N) ");
            continuar = toupper(getche());
        }
        else
        {
            continuar = 'N';
        }
    } while (continuar != 'N');
}

void cadastroForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd, int &linha, int veioDeCadProd)
{
    int auxCod, buscaF;
    char continuar, cadastrarProduto;
    do
    {
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Digite o codigo do fornecedor: ");
        scanf("%d", &auxCod);
        buscaF = buscaForn(fornecedores, tl, auxCod);
        while (buscaF != -1)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Forn. encontrado, digite outro: ");
            scanf("%d", &auxCod);
            buscaF = buscaForn(fornecedores, tl, auxCod);
        }
        fornecedores[tl].codForn = auxCod;
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Digite o nome do fornecedor: ");
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        fflush(stdin);
        gets(fornecedores[tl].nomeForn);
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        fflush(stdin);
        printf("Digite a cidade do fornecedor: ");
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        gets(fornecedores[tl].cidadeForn);
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        tl++;
        if (veioDeCadProd == 0)
        {
            printf("Deseja cadastrar produto? (S/N) ");
            cadastrarProduto = toupper(getche());
            if (cadastrarProduto == 'S')
            {
                cadastroProdutos(produtos, tlProd, fornecedores, tl, linha, 1);
            }
        }
        if (tl < TF)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Cadastrar mais fornecedores? (S/N) ");
            continuar = toupper(getche());
            // FAZER SAI LIDO
        }
        else
        {
            continuar = 'N';
        }
    } while (continuar != 'N');
}

void cadastroCliente(tpCliente clientes[TF], int &tl, int &linha)
{
    int aux;
    linha = 7;
    gotoxy(41, linha);
    linha++;
    printf("Digite o CPF do cliente: ");
    scanf("%lld", &aux);
    aux = buscaCliente(clientes, tl, aux);
    if (aux != -1)
    {
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Cliente cadastrado!");
        return;
    }
    if (linha > 19)
    {
        limparExecucao();
        linha = 7;
    }
    gotoxy(41, linha);
    linha++;
    printf("Digite o nome do cliente: ");
    gets(clientes[tl].nomeCliente);

    clientes[tl].qtdeCompras = 0;
    clientes[tl].valorTotalComprado = 0;
    tl++;
    if (linha > 19)
    {
        limparExecucao();
        linha = 7;
    }
    gotoxy(41, linha);
    linha++;
    printf("cliente cadastrado com sucesso");
    getch();
}

int buscaCliente(tpCliente clientes[TF], int tl, long int cpfCliente)
{
    int i;
    for (i = 0; i < tl; i++)
    {
        if (cpfCliente == clientes[i].cpfCliente)
        {
            return i;
        }
    }
    return -1;
}

int buscaForn(tpFornecedor fornecedores[TF], int tl, int codForn)
{

    for (int i = 0; i < tl; i++)
    {
        if (codForn == fornecedores[i].codForn)
        {
            return i;
        }
    }
    return -1;
}

int buscaProd(tpProduto produtos[TF], int tl, int codProduto)
{
    int i;

    for (int i = 0; i < tl; i++)
    {
        if (produtos[i].codProd == codProduto)
        {
            return i;
        }
    }
    return -1;
}

int buscaVendas(tpVenda vendas[TF], int tl, int cod)
{
    int pos = 0;
    while (pos < tl && vendas[pos].codVenda != cod)
    {
        pos++;
    }
    if (pos == tl)
    {
        return -1;
    }
    else
    {
        return pos;
    }
}
// declarar
int buscaVendas2(tpVendasProdutos vendasProd[TF], int tl, int cod)
{
    int pos = 0;
    while (pos < tl && vendasProd[pos].codVenda != cod)
    {
        pos++;
    }
    if (pos == tl)
    {
        return -1;
    }
    else
    {
        return pos;
    }
}
// declarar funcao nova
int buscaProdPorFornecedor(tpProduto produtos[TF], int tl, int codForn)
{
    int i;

    for (int i = 0; i < tl; i++)
    {
        if (produtos[i].codForn == codForn)
        {
            return i;
        }
    }
    return -1;
}

void exclusaoProd(tpProduto produtos[TF], int &tl, int indice)
{
    for (int i = indice; i < tl; i++)
    {
        produtos[i] = produtos[i + 1];
    }
    tl--;
    // printf("produto")
}

void exclusaoForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd, int &linha)
{
    int aux, codForn;
    linha = 7;
    gotoxy(41, linha);
    linha++;
    printf("Digite o codigo do fornecedor a ser excluido: ");
    scanf("%d", &codForn);
    aux = buscaForn(fornecedores, tl, codForn);
    if (aux == -1)
    {
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Fornecedor nao cadastrado!");
    }
    for (int i = aux; i < tl; i++)
    {
        fornecedores[i] = fornecedores[i + 1];
    }
    tl--;

    aux = buscaProdPorFornecedor(produtos, tlProd, codForn);
    while (aux != -1)
    {
        exclusaoProd(produtos, tlProd, aux);
        aux = buscaProdPorFornecedor(produtos, tlProd, codForn);
    }
    if (linha > 19)
    {
        limparExecucao();
        linha = 7;
    }
    gotoxy(41, linha);
    linha++;
    printf("Fornecedor excluido com sucesso!");
}

int buscarCpfClienteVendas(tpVenda vendas[TF], int &tl, int cpf)
{
    int i;

    for (i = 0; i < tl; i++)
    {
        if (vendas[i].cpfCliente == cpf)
        {
            return i;
        }
    }
    return -1;
}

void exclusaoCliente(tpCliente clientes[TF], int &tl, int &linha)
{
    int aux;
    long int cpfCliente;
    linha = 7;
    gotoxy(41, linha);
    linha++;
    printf("Digite o CPF do cliente a ser excluido: ");
    scanf("%lld", &cpfCliente);
    aux = buscaCliente(clientes, tl, cpfCliente);
    if (aux == -1)
    {
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Cliente nao cadastrado!");
        return;
    }
    for (int i = aux; i < tl; i++)
    {
        clientes[i] = clientes[i + 1];
    }
    tl--;
    if (linha > 19)
    {
        limparExecucao();
        linha = 7;
    }
    gotoxy(41, linha);
    linha++;
    printf("Cliente excluido com sucesso!");
}

void exibirMoldura()
{
    // x de 1 a 80, 80 colunas
    // y de 1 a 25, 25 linhas
    // cor verde pra backcolor 2
    // cor light verde pra font 10

    // PARTE DE CIMA - TÍTULO
    moldura(1, 1, 80, 5, 10, 2);

    // PARTE ESQUERDA - MENUS
    moldura(1, 6, 39, 20, 10, 2);

    // ÁREA DA DIREITA - EXECUÇÕES
    moldura(40, 6, 80, 20, 10, 2);

    // PARTE DE BAIXO - MENSAGEM
    moldura(1, 21, 80, 25, 10, 2);

    gotoxy(31, 1);
    printf("* * * TITULO * * *");
    gotoxy(31, 21);
    printf("* * * MENSAGEM * * *");

    gotoxy(1, 27);
}

void limparTitulo()
{
    int linha = 3, colI = 2, colF = 79;
    for (int i = colI; i <= colF; i++)
    {
        gotoxy(i, linha);
        printf(" ");
    }
}

void limparMensagem()
{
    int linha = 23, colI = 2, colF = 79;
    for (int i = colI; i <= colF; i++)
    {
        gotoxy(i, linha);
        printf(" ");
    }
}

void limparMenu()
{
    int liI = 7, colI = 2, liF = 19, colF = 38;
    for (int i = colI; i <= colF; i++)
    {
        for (int j = liI; j <= liF; j++)
        {
            gotoxy(i, j);
            printf(" ");
        }
    }
}

void limparExecucao()
{
    int liI = 7, colI = 41, liF = 19, colF = 79;
    for (int i = colI; i <= colF; i++)
    {
        for (int j = liI; j <= liF; j++)
        {
            gotoxy(i, j);
            printf(" ");
        }
    }
}

void moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
    int i;
    textcolor(CorT);
    textbackground(CorF);
    gotoxy(CI, LI);
    printf("%c", 201);
    gotoxy(CI, LF);
    printf("%c", 200);
    gotoxy(CF, LI);
    printf("%c", 187);
    gotoxy(CF, LF);
    printf("%c", 188);
    for (i = CI + 1; i < CF; i++)
    {
        gotoxy(i, LI);
        printf("%c", 205);
        gotoxy(i, LF);
        printf("%c", 205);
    }
    for (i = LI + 1; i < LF; i++)
    {
        gotoxy(CI, i);
        printf("%c", 186);
        gotoxy(CF, i);
        printf("%c", 186);
    }

    textcolor(7);
    textbackground(0);
}

void efetuarVenda(tpVenda vendas[TF], int &tl, tpCliente clientes[TF], int &tlCLiente, tpProduto produtos[TF], int &tlProdutos, tpVendasProdutos vendasProdutos[TF], int &tlVendasProdutos, int &linha)
{
    long long int cpfCliente;
    int busca, codProd, qtde, buscacliente;
    float aux = 0;
    char op, son;
    // variaveis para venda
    int codVenda, D, M, A, estoque, qtdeCompras;
    long long int cpfAux;
    float totalVendas, valorTotalComprado;
    // variaveis para exibicao em tela
    linha = 7;

    do
    {
        gotoxy(41, linha);
        linha++;
        printf("Digite o CPF do cliente: ");
        scanf("%lld", &cpfCliente);

        buscacliente = buscaCliente(clientes, tlCLiente, cpfCliente);
        if (buscacliente == -1)
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Cliente Nao cadastrado\n");
            getch();
            cadastroCliente(clientes, tlCLiente, linha);
        }
        do
        {
            if (tlProdutos > 0 && op == 'S')
            {
                relatorioProdutos(produtos, tlProdutos);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Digite o codigo do produto para compra: ");
                scanf("%d", &codProd);
                busca = buscaProd(produtos, tlProdutos, codProd);
                if (busca == -1)
                {
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("codigo invalido ou inexiste\n");
                }
                else
                {
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Qual a quantidade desse produto: ");
                    scanf("%d", &qtde);
                    if (qtde > produtos[busca].estoque)
                    {
                        if (linha > 19)
                        {
                            limparExecucao();
                            linha = 7;
                        }
                        gotoxy(41, linha);
                        linha++;
                        printf("Quantidade indisponivel");
                        if (linha > 19)
                        {
                            limparExecucao();
                            linha = 7;
                        }
                        gotoxy(41, linha);
                        linha++;
                        printf("Deseja comprar outra quantidade: (S/N)");
                        fflush(stdin);
                        if (toupper(getche()) == 'S')
                        {
                            if (linha > 19)
                            {
                                limparExecucao();
                                linha = 7;
                            }
                            gotoxy(41, linha);
                            linha++;
                            printf("Qual a quantidade desse produto: ");
                            scanf("%d", &qtde);
                        }
                        else
                        {
                            if (linha > 19)
                            {
                                limparExecucao();
                                linha = 7;
                            }
                            gotoxy(41, linha);
                            linha++;
                            printf("compra cancelada!");
                        }
                    }
                    else
                    {

                        codVenda = tl + 1;
                        cpfAux = cpfCliente;
                        D = 13;
                        M = 8;
                        A = 2024;
                        totalVendas = produtos[busca].preco * qtde;
                        estoque = produtos[busca].estoque - qtde;
                        qtdeCompras = clientes[busca].qtdeCompras + qtde;
                        valorTotalComprado = clientes[busca].valorTotalComprado + produtos[busca].preco * qtde;
                        aux += qtde * produtos[busca].preco;
                        if (linha > 19)
                        {
                            limparExecucao();
                            linha = 7;
                        }
                        gotoxy(41, linha);
                        linha++;
                        printf("Venda efetuada com sucesso\n");
                        getch();
                        fflush(stdin);
                    }
                }
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Nao ha produtos cadastrados\n");
                getch();
            }

            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Deseja comprar outro produto: (S/N)");
            fflush(stdin);
            op = toupper(getche());
            if (op == 'N')
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("o cliente %s comprou %d produtos\n", clientes[busca].nomeCliente, clientes[busca].qtdeCompras);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Total da compra: %.2f", aux);
                getch();
                printf("deseja finalizar compra? (S/N)");
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                fflush(stdin);
                son = toupper(getche());
                if (son == 'N')
                {
                    op = 'N';
                }
                else
                {
                    vendas[tl].codVenda = codVenda;
                    vendas[tl].cpfCliente = cpfAux;
                    vendas[tl].data.d = D;
                    vendas[tl].data.m = M;
                    vendas[tl].data.a = A;
                    vendas[tl].totalVendas = totalVendas;
                    vendasProdutos[tl].codProd = codProd;
                    vendasProdutos[tl].qtde = qtde;
                    produtos[busca].estoque = estoque;
                    clientes[buscacliente].qtdeCompras = qtdeCompras;
                    clientes[buscacliente].valorTotalComprado = valorTotalComprado;
                    clientes[buscacliente].qtdeCompras = qtdeCompras + 1;
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("Venda efetuada com sucesso\n");
                    getch();
                    fflush(stdin);
                    system("cls");
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("cliente %s comprou %d produtos\n", clientes[buscacliente].nomeCliente, clientes[buscacliente].qtdeCompras);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("valor total comprado: %.2f", aux);
                    getch();
                }
            }
        } while (op == 'S'); // se ja foi verificado o cliente

    } while (toupper(getche()) == 'S'); // primeira entrada sem verificacao de cliente
    return;
}

void relatorioDeVendas(tpVenda vendas[TF], int &tl)
{
    system("cls");
    if (tl == 0)
    {
        printf("nao ha vendas registradas para gerar um relatorio");
        getch();
    }
    else
    {
        for (int i = 0; i < tl; i++)
        {
            printf("*__________*");
            printf("CPF do clienten: %li", vendas[i].cpfCliente);
            printf("Codigo da venda: %d", vendas[i].codVenda);
            printf("Total de vendas: %.2f", vendas[i].totalVendas);
            printf("Data da venda %d/%d/%d", vendas[i].data.d, vendas[i].data.m, vendas[i].data.a);
            printf("*__________*");
        }
    }
    return;
}
// NAO ESTA FEITO fazerrrrrrrrrrrrrrrrrrrrrr

void exclusaoDeVendas(tpVenda vendas[TF], int &tl, int &linha, tpCliente clientes[TF], int &tlCliente, tpProduto produtos[TF], int &tlProdutos, tpVendasProdutos vendasProdutos[TF], int &tlVendasProdutos)
{
    int aux, codVenda, pos1;
    char op;
    linha = 7;
    if (tl == 0)
    {
        gotoxy(41, linha);
        linha++;
        printf("Vendas nao registradas");
        getch();
    }
    else
    {
        printf("digite o codigo da venda que deseja apagar: ");
        scanf("%d", &codVenda);
        while (tl > 0 && codVenda > 0)
        {
            aux = buscaVendas(vendas, tl, codVenda);
            if (aux == -1)
            {
                printf("venda nao cadastrada");
                getch();
            }
            else
            {
                printf("CPF do cliente: %li", vendas[aux].cpfCliente);
                printf("data da venda: %d/%d/%d", vendas[aux].data.d, vendas[aux].data.m, vendas[aux].data.a);
                printf("total da venda: %.2f", vendas[aux].totalVendas);
                printf("confirmar exclusao? (S/N)");
                op = toupper(getche());
                if (op == 'S')
                {
                    pos1 = buscaCliente(clientes, tlCliente, vendas[aux].cpfCliente);
                    clientes[pos1].qtdeCompras--;
                    clientes[pos1].valorTotalComprado -= vendas[aux].totalVendas;
                    for (; aux < tl; aux++)
                    {
                        vendas[aux] = vendas[aux + 1];
                        vendas[aux].codVenda--;
                    }
                    tl--;
                    aux = buscaVendas2(vendasProdutos, tlVendasProdutos, codVenda);
                    while (aux < tlVendasProdutos)
                    {
                        pos1 = buscaProd(produtos, tlProdutos, vendasProdutos[aux].codProd);
                        produtos[pos1].estoque += vendasProdutos[pos1].qtde;
                        for (int i = aux; i < tlVendasProdutos - 1; i++)
                        {
                            vendasProdutos[i] = vendasProdutos[i + 1];
                        }
                        tlVendasProdutos--;
                        aux = buscaVendas2(vendasProdutos, tlVendasProdutos, codVenda);
                    }
                    aux = buscaVendas2(vendasProdutos, tlVendasProdutos, codVenda + 1);
                    for (int i = 0; i < tlVendasProdutos; i++)
                    {
                        vendasProdutos[i].codVenda--;
                    }
                    printf("venda excluida com sucesso");
                }
                else
                {
                    printf("exclusao cancelada");
                }
            }
        }
    }
    return;
}

void consultaForn(tpFornecedor forncedores[TF], int tlForn, int &linha)
{

    int codForn, aux;
    linha = 7;
    if (tlForn == 0)
    {
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Nao ha fronecedores para consultar");
        gotoxy(41, linha);
        linha++;
        printf("Tecle algo para voltar");
        linha = 7;
        getch();
    }
    else
    {
        char continuar;

        do
        {

            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Codigo do fornecedor a consultar: ");
            scanf("%d", &codForn);

            aux = buscaForn(forncedores, tlForn, codForn);
            if (aux == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Fornecedor nao encontrado");
            }
            else
            {
                limparExecucao();
                linha = 7;
                gotoxy(41, linha);
                linha++;
                printf("Codigo: %d", forncedores[aux].codForn);
                gotoxy(41, linha);
                linha++;
                printf("Nome: ");
                puts(forncedores[aux].nomeForn);
                gotoxy(41, linha);
                linha++;
                printf("Cidade: ");
                puts(forncedores[aux].cidadeForn);
            }
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Continuar consulta? (S/N) ");
            continuar = toupper(getche());
        } while (continuar != 'N');
    }
}

void alteracaoFornecedores(tpFornecedor fornecedores[TF], int tl, int &linha)
{
    int codForn, busca;
    char op;
    linha = 7;
    if (tl == 0)
    {
        gotoxy(41, linha);
        linha++;
        printf("Nao ha dados para alterar!!");
        gotoxy(41, linha);
        linha++;
        printf("Tecle algo para voltar");
        linha = 7;
        getch();
    }
    else
    {
        do
        {
            limparExecucao();
            linha = 7;
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Codigo do forn. a ser alterado: ");
            scanf("%d", &codForn);

            busca = buscaForn(fornecedores, tl, codForn);

            if (busca == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Forn. nao encontrado");
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Digite o novo nome do forncedor:");
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                fflush(stdin);
                gets(fornecedores[busca].nomeForn);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Digite a nova cidade do fornecedor:");
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                fflush(stdin);
                gets(fornecedores[busca].cidadeForn);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Alteracoes feitas com sucesso!!");
            }
            fflush(stdin);
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Continuar alteracoes?: (S/N)");
            op = toupper(getche());
        } while (op == 'S');
    }
}

void relatorioFornecedores(tpFornecedor fornecedores[TF], int tl)
{
    system("cls");

    if (tl == 0)
    {
        printf("Nao ha dados para fazer um relarotio");
        getch();
    }
    else
    {
        for (int i = 0; i < tl; i++)
        {
            printf("*__________*");
            printf("Codigo do fornecedor: %d", fornecedores[i].codForn);
            printf("Nome do fornecedor: %s", fornecedores[i].nomeForn);
            printf("Cidade do Fornecedor: %s", fornecedores[i].cidadeForn);
            printf("*__________*");
        }
    }
    return;
}

void aumentoDePreco(tpFornecedor fornecedores[TF], int tl, tpProduto produtos[TF], int tlProdutos, int &linha)
{
    int codForn, busca, porcentagem;
    linha = 7;
    do
    {
        if (tl == 0)
        {
            gotoxy(41, linha);
            linha++;
            linha = 7;
            printf("Nao ha dados para fazer um aumento de preco");
            getch();
        }
        else
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("Digite o coidigo do fornecedor para aumentar o preco dos produtos: ");
            scanf("%d", &codForn);

            busca = buscaForn(fornecedores, tl, codForn);
            if (busca == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Codigo invalido ou inexistente");
                getch();
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Qual o percentual de aumento: ");
                scanf("%d", &porcentagem);

                for (int i = 0; i < tlProdutos; i++)
                {
                    if (produtos[i].codForn == codForn)
                    {
                        produtos[i].preco = produtos[i].preco + (produtos[i].preco * porcentagem / 100);
                    }
                }
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Aumento de preco feito com sucesso!!");
            }
        }
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Deseja fazer outro aumento de preco: (S/N)");
        fflush(stdin);
    } while (toupper(getche()) == 'S');
    return;
}

void consultaClientes(tpCliente clientes[TF], int tl, int &linha)
{
    long int cpf;
    int busca;
    char op;
    linha = 7;
    system("cls");
    do
    {
        if (tl == 0)
        {
            gotoxy(41, linha);
            linha++;
            printf("Nao ha clientes para consulta");
            getch();
        }
        else
        {
            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("digite o cpf sem tracos e pontos para consulta: ");
            scanf("%lld", &cpf);
            busca = buscaCliente(clientes, tl, cpf);
            if (busca == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("CPF invalido ou inexistente");
                getch();
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("CPF do cliente: %lld", clientes[busca].cpfCliente);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Nome do cliente: %s", clientes[busca].nomeCliente);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Quantidade de compras feito: %d", clientes[busca].qtdeCompras);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("Total comprado pelo cliente: %.2f", clientes[busca].valorTotalComprado);
            }
        }

        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("Deseja consultar outro cliente: (S/N)");
        fflush(stdin);
        op = toupper(getche());
    } while (op == 'S');
    return;
}

void exclusaoClientes(tpCliente clientes[TF], int &tlClientes)
{

    return;
}
// falta exclusao de clientes  
void alteracaoClientes(tpCliente clientes[TF], int tlClientes, int &linha)
{
    int busca;
    long long int cpf;
    char op;
    linha = 7;
    do
    {
        if (tlClientes == 0)
        {
            gotoxy(41, linha);
            linha++;
            printf("\nNao ha clientes para alterar\n\n");
        }
        else
        {

            if (linha > 19)
            {
                limparExecucao();
                linha = 7;
            }
            gotoxy(41, linha);
            linha++;
            printf("\nDigite o CPF do cliente a ser alterado: \n");
            scanf("%lld", &cpf);

            busca = buscaCliente(clientes, tlClientes, cpf);
            if (busca == -1)
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("\nCPF invalido ou inexistente\n\n");
            }
            else
            {
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("\nCPF do cliente: %lld\n", clientes[busca].cpfCliente);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("\nNome do cliente: %s\n", clientes[busca].nomeCliente);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("\nQuantidade de compras feito: %d\n", clientes[busca].qtdeCompras);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("\nTotal comprado pelo cliente: %.2f\n", clientes[busca].valorTotalComprado);
                if (linha > 19)
                {
                    limparExecucao();
                    linha = 7;
                }
                gotoxy(41, linha);
                linha++;
                printf("\n\nDeseja alterar esse cliente: (S/N)\n");
                fflush(stdin);
                op = toupper(getche());
                if (op == 'S')
                {
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("\nDigite o novo nome do cliente: \n");
                    gets(clientes[busca].nomeCliente);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("\nDigite o novo CPF do cliente: \n");
                    scanf("%lld", &clientes[busca].cpfCliente);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("\nDigite a nova quantidade de compras feita pelo cliente: \n");
                    scanf("%d", &clientes[busca].qtdeCompras);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("\nDigite o novo valor total comprado pelo cliente: \n");
                    scanf("%f", &clientes[busca].valorTotalComprado);
                    if (linha > 19)
                    {
                        limparExecucao();
                        linha = 7;
                    }
                    gotoxy(41, linha);
                    linha++;
                    printf("\n\nAlteracoes feitas com sucesso!!\n\n");
                    getch();
                }
            }
        }
        if (linha > 19)
        {
            limparExecucao();
            linha = 7;
        }
        gotoxy(41, linha);
        linha++;
        printf("\n\nDeseja alterar outro cliente: (S/N)\n");
        fflush(stdin);
        op = toupper(getche());
    } while (op == 'S');
    return;
}

void relatorioClientes(tpCliente clientes[TF], int tlClientes)
{
    system("cls");
    if (tlClientes == 0)
    {
        printf("Nao ha dados para gerar relatorio");
        getch();
    }
    else
    {
        for (int i = 0; i < tlClientes; i++)
        {
            printf("*__________*");
            printf("CPF do cliente: %lld", clientes[i].cpfCliente);
            printf("Nome do cliente: %s", clientes[i].nomeCliente);
            printf("Quantidade de compras feito: %d", clientes[i].qtdeCompras);
            printf("Total comprado pelo cliente: %.2f", clientes[i].valorTotalComprado);
            printf("*__________*");
        }
        getch();
    }
    return;
}

char menuFornecedores(void)
{
    limparMenu();
    limparExecucao();
    gotoxy(2, 8);
    // VER ONDE DARÁ CLEAR NA TELA
    printf("# # #  MENU DE FORNECEDORES  # # #");
    gotoxy(2, 9);
    printf("[A] Cadastro de Fornecedores");
    gotoxy(2, 10);
    printf("[B] Consulta de Fornecedores");
    gotoxy(2, 11);
    printf("[C] Exclusao de Fornecedores");
    gotoxy(2, 12);
    printf("[D] Alteracao de Fornecedores");
    gotoxy(2, 13);
    printf("[E] Relatorio de Fornecedores");
    gotoxy(2, 14);
    printf("[F] Aumento de precos de produtos");
    gotoxy(2, 15);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 16);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuProdutos(void)
{
    limparMenu();
    limparExecucao();
    gotoxy(2, 8);
    // VER ONDE DARÁ CLEAR NA TELA
    printf("# # #  MENU DE PRODUTOS  # # #");
    gotoxy(2, 9);
    printf("[A] Cadastro de Produtos");
    gotoxy(2, 10);
    printf("[B] Consulta de Produtos");
    gotoxy(2, 11);
    printf("[C] Exclusao de Produtos");
    gotoxy(2, 12);
    printf("[D] Alteracao de Produtos");
    gotoxy(2, 13);
    printf("[E] Relatorio de Produtos");
    gotoxy(2, 14);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 15);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuVendas(void)
{
    limparMenu();
    limparExecucao();
    gotoxy(2, 8);
    // VER ONDE DARÁ CLEAR NA TELA
    printf("# # #  MENU DE VENDAS  # # #");
    gotoxy(2, 9);
    printf("[A] Efetuar uma venda");
    gotoxy(2, 10);
    printf("[B] Relatorio de vendas");
    gotoxy(2, 11);
    printf("[C] Exclusao de uma venda");
    gotoxy(2, 12);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 13);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuClientes(void)
{
    limparMenu();
    limparExecucao();
    gotoxy(2, 8);
    // VER ONDE DARÁ CLEAR NA TELA
    printf("# # #  MENU DE CLIENTES  # # #");
    gotoxy(2, 9);
    printf("[A] Cadastro de Clientes");
    gotoxy(2, 10);
    printf("[B] Consulta de Clientes");
    gotoxy(2, 11);
    printf("[C] Exclusao de Clientes");
    gotoxy(2, 12);
    printf("[D] Alteracao de Clientes");
    gotoxy(2, 13);
    printf("[E] Relatorio de Clientes");
    gotoxy(2, 14);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 15);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuPrincipal(void)
{
    limparMenu();
    limparExecucao();
    // VER ONDE DARÁ CLEAR NA TELA
    gotoxy(2, 8);
    printf("# # #  MENU PRINCIPAL  # # #");
    gotoxy(2, 9);
    printf("[A] Secao de Vendas");
    gotoxy(2, 10);
    printf("[B] Secao de Produtos");
    gotoxy(2, 11);
    printf("[C] Secao de Fornecedores");
    gotoxy(2, 12);
    printf("[D] Secao de Clientes");
    gotoxy(2, 13);
    printf("[E] Insercao de dados automaticos");
    gotoxy(2, 14);
    printf("[ESC] Sair");
    gotoxy(2, 15);
    printf("Opcao desejada: ");
    return toupper(getche());
}

void executar()
{
    // CRIAR TODAS AS INSTÂNCIAS DOS VETORES
    char opMenuPrincipal;
    tpVenda vendas[TF];
    int tlVendas = 0;
    tpCliente clientes[TF];
    int tlClientes = 0;
    tpFornecedor fornecedores[TF];
    int tlFornecedores = 0;
    tpProduto produtos[TF];
    int tlProdutos = 0;
    tpVendasProdutos vendas_produtos[TF];
    int tlVendasProdutos = 0;
    int linha = 7;

    exibirMoldura();
    //    getch();

    do
    {
        opMenuPrincipal = menuPrincipal();
        switch (opMenuPrincipal)
        {
        case 'A':
            char opMenuVendas;
            do
            {
                opMenuVendas = menuVendas();
                switch (opMenuVendas)
                {
                case 'A':
                    efetuarVenda(vendas, tlVendas, clientes, tlClientes, produtos, tlProdutos, vendas_produtos, tlVendasProdutos, linha);
                    break;
                case 'B':
                    relatorioDeVendas(vendas, tlVendas);
                    break;
                case 'C':
                    exclusaoDeVendas(vendas, tlVendas, linha, clientes, tlClientes, produtos, tlProdutos, vendas_produtos, tlVendasProdutos);
                    break;
                }
            } while (opMenuVendas != 27);
            break;
        case 'B':
            char opMenuProdutos;
            do
            {
                opMenuProdutos = menuProdutos();
                switch (opMenuProdutos)
                {
                case 'A':
                    cadastroProdutos(produtos, tlProdutos, fornecedores, tlFornecedores, linha, 0);
                    break;
                case 'B':
                    consultaProdutos(produtos, tlProdutos, linha, fornecedores);
                    break;
                case 'C':
                    exclusaoProdutos(produtos, tlProdutos, linha);
                    break;
                case 'D':
                    alteracaoProdutos(produtos, tlProdutos, linha);
                    break;
                case 'E':
                    relatorioProdutos(produtos, tlProdutos);
                    break;
                }
            } while (opMenuProdutos != 27);
            break;
        case 'C':
            char opMenuFornecedores;
            do
            {
                opMenuFornecedores = menuFornecedores();
                switch (opMenuFornecedores)
                {
                case 'A':
                    cadastroForn(fornecedores, tlFornecedores, produtos, tlProdutos, linha, 0);
                    break;
                case 'B':
                    consultaForn(fornecedores, tlFornecedores, linha);
                    break;
                case 'C':
                    exclusaoForn(fornecedores, tlFornecedores, produtos, tlProdutos, linha);
                    break;
                case 'D':
                    alteracaoFornecedores(fornecedores, tlFornecedores, linha);
                    break;
                case 'E':
                    relatorioFornecedores(fornecedores, tlFornecedores);
                    break;
                case 'F':
                    aumentoDePreco(fornecedores, tlFornecedores, produtos, tlProdutos, linha);
                    break;
                }
            } while (opMenuFornecedores != 27);
            break;
        case 'D':
            char opMenuClientes;
            do
            {
                opMenuClientes = menuClientes();
                switch (opMenuClientes)
                {
                case 'A':
                    cadastroCliente(clientes, tlClientes, linha);
                    break;
                case 'B':
                    consultaClientes(clientes, tlClientes, linha);
                    break;
                case 'C':
                    exclusaoClientes(clientes, tlClientes);
                    break;
                case 'D':
                    alteracaoClientes(clientes, tlClientes, linha);
                    break;
                case 'E':
                    relatorioClientes(clientes, tlClientes);
                    break;
                }
            } while (opMenuClientes != 27);
            break;
        case 'E':
            insercaoAutomDeDados(produtos, tlProdutos, clientes, tlClientes, fornecedores, tlFornecedores);
            break;
        }
    } while (opMenuPrincipal != 27);
}

int main()
{
    executar();
    return 0;
}
