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
void efetuarVenda(tpVenda vendas[TF], int &tl);
void relatorioDeVendas(tpVenda vendas[TF], int &tl);
void exclusaoDeVendas(tpVenda vendas[TF], int &tl);
int buscarCpfClienteVendas(tpVenda vendas[TF], int &tl, int cpf);

// *** CLIENTES ***
void cadastroCliente(tpCliente clientes[TF], int &tl);
int buscaCliente(tpCliente clientes[TF], int tl, long int cpfCliente);
void exclusaoCliente(tpCliente clientes[TF], int &tl);
void consultaClientes(tpCliente clientes[TF], int tl);
void exclusaoClientes(tpCliente clientes[TF], int &tlClientes);
void alteracaoClientes(tpCliente clientes[TF], int tlClientes);
void relatorioClientes(tpCliente fornecedores[TF], int tlFornecedores);

// *** PRODUTOS ***
void cadastroProdutos(tpProduto produtos[TF], int &tl, tpFornecedor fornecedores[TF], int &tlForn);
int buscaProd(tpProduto produtos[TF], int tl, int codProduto);
int buscaProdPorFornecedor(tpProduto produtos[TF], int tl, int codForn);
void exclusaoProd(tpProduto produtos[TF], int &tl, int indice);
void exclusaoProdutos(tpProduto produtos[TF], int tlProdutos);
void consultaProdutos(tpProduto produtos[TF], int tlProdutos);
void alteracaoProdutos(tpProduto protudos[TF], int tlProdutos);
void relatorioProdutos(tpProduto produtos[TF], int tlProdutos);

// *** FORNECEDORES ***
void cadastroForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd);
int buscaForn(tpFornecedor fornecedores[TF], int tl, int codForn);
void exclusaoForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd);
void consultaForn(tpFornecedor forncedores[TF]);
void alteracaoFornecedores(tpFornecedor fornecedores[TF], int tl);
void relatorioFornecedores(tpFornecedor fornecedores[TF], int tl);
void aumentoDePreco(tpFornecedor fornecedores[TF], int tl);

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

// sem teste feito por Daniel
void exclusaoProdutos(tpProduto produtos[TF], int tlProdutos)
{
    int codProd, aux;
    char op;

    system("cls");
    printf("\n__Exclusao de produtos__\n");

    do
    {
        clrscr();
        if (tlProdutos == 0)
        {
            printf("Nao ha produtos para excluir\n");
            getch();
        }

        else
        {
            printf("\nDigite o codigo do produto a excluir\n");
            scanf("%d", &codProd);

            aux = buscaProd(produtos, tlProdutos, codProd);
            if (aux == -1)
            {
                printf("\nCodigo invalido ou produto inexistente\ndigite outro codigo\n");
                scanf("%d", &codProd);
            }
            else
            {
                puts(produtos[aux].descricao);
                printf("%d\n", produtos[aux].codProd);
                printf("%d\n", produtos[aux].estoque);
                printf("%f\n", produtos[aux].preco);
                printf("%d/%d/%d", produtos[aux].data.d, produtos[aux].data.m, produtos[aux].data.a);

                printf("\nconfirma exclusao (S/N) ");
                op = toupper(getche());
                if (op == 'S')
                {
                    for (; aux < tlProdutos - 1; aux++)
                    {
                        produtos[aux] = produtos[aux + 1];
                    }
                    tlProdutos--;

                    printf("\nProduto excluido");
                    getch();
                }
            }
            printf("\nDeseja excluir outro produto (S/N)");
            fflush(stdin);
            op = toupper(getche());
        }

    } while (op != 'S');

    return;
}

// sem teste feito por Daniel
void relatorioProdutos(tpProduto produtos[TF], int tlProdutos)
{
    system("cls");
    if (tlProdutos == 0)
    {
        printf("\nNao ha produtos para exibir");
        getch();
    }
    else
    {
        for (int i = 0; i < tlProdutos; i++)
        {
            printf("\n*______________*");
            printf("Codigo do produto: %d\n", produtos[i].codProd);
            printf("Descricao do produto %s\n", produtos[i].descricao);
            printf("Estoque disponivel: %d\n", produtos[i].estoque);
            printf("Preco atual: %f\n", produtos[i].preco);
            printf("Data de validade do produto: %d/%d/%d\n", produtos[i].data.d, produtos[i].data.m, produtos[i].data.a);
            printf("\n*______________*");
            printf("\n\n");
        }
        printf("\n\n [BACKSPACE] VOLTAR");
        getch();
    }
    return;
}

// sem teste feito por Daniel
void alteracaoProdutos(tpProduto produtos[TF], int tlProdutos)
{
    int codProd, aux;
    char op;
    system("cls");
    do
    {
        if (tlProdutos == 0)
        {
            printf("\nNao ha produtos para serem alterados\n");
            getch();
        }
        else
        {
            printf("digite o codigo do produto a ser alterado: \n");
            scanf("%d", &codProd);
            aux = buscaProd(produtos, tlProdutos, codProd);
            if (aux == -1)
            {
                printf("codigo invalido ou inexistente");
                getch();
            }
            else
            {
                printf("Codigo do produto: %d\n", produtos[aux].codProd);
                printf("Descricao do produto %s\n", produtos[aux].descricao);
                printf("Estoque disponivel: %d\n", produtos[aux].estoque);
                printf("Preco atual: %f\n", produtos[aux].preco);
                printf("Data de validade do produto: %d/%d/%d\n", produtos[aux].data.d, produtos[aux].data.m, produtos[aux].data.a);

                printf("\nDeseja alterar o produto a cima: (S/N)");
                fflush(stdin);
                op = toupper(getche());
                if (op == 'S')
                {
                    printf("\ndigite a nova descricao desse produto: \n");
                    gets(produtos[aux].descricao);
                    printf("\nQual o novo estoque desse produto: \n");
                    scanf("%d", &produtos[aux].estoque);
                    printf("\nDigite o novo preco desse produto: \n");
                    scanf("%f", &produtos[aux].preco);
                    printf("\ndigite a nova data de validade desse produto: \n");
                    scanf("%d %d %d", &produtos[aux].data.d, &produtos[aux].data.m, &produtos[aux].data.a);

                    printf("\n\nProduto alterado com sucesso!!\n\n");
                    getch();
                }
            }
        }
        printf("\n\nDeseja alterar outro produto: (S/N)");
        fflush(stdin);
        op = toupper(getche());
    } while (op == 'S');
    return;
}

// sem teste feito por Daniel
void consultaProdutos(tpProduto produtos[TF], int tlProdutos)
{
    int codProd, aux;
    system("cls");
    printf("Consulta de Produtos\n\n");

    if (tlProdutos == 0)
    {
        printf("Nao ha produtos para consultar");
        getch();
    }
    else
    {
        printf("\ndigite o codigo do produto a consultar\n");
        scanf("%d", codProd);

        aux = buscaProd(produtos, tlProdutos, codProd);
        if (aux == -1)
        {
            printf("\ncodigo inexistente ou invalido\n");
            getch();
        }
        else
        {
            printf("Codigo do produto: %d\n", produtos[aux].codProd);
            printf("Descricao do produto %s\n", produtos[aux].descricao);
            printf("Estoque disponivel: %d\n", produtos[aux].estoque);
            printf("Preco atual: %f\n", produtos[aux].preco);
            printf("Data de validade do produto: %d/%d/%d\n", produtos[aux].data.d, produtos[aux].data.m, produtos[aux].data.a);

            getch();
        }
    }
    return;
}

void cadastroProdutos(tpProduto produtos[TF], int &tl, tpFornecedor fornecedores[TF], int &tlForn)
{
    int pos, codProd, codFornecedor;
    printf("\nDigite o codigo do produto a cadastrar: \n");
    scanf("%d", &codProd);
    pos = buscaProd(produtos, tl, codProd);
    if (pos == -1)
    {
        printf("\nProduto ja cadastrado!\n");
        return;
    }
    produtos[tl].codProd = codProd;
    printf("\nDigite o codigo do fornecedor: \n");
    scanf("%d", &codFornecedor);
    pos = buscaForn(fornecedores, tlForn, codFornecedor);
    if (pos == -1)
    {
        printf("\nFornecedor nao cadastrado!\n");
        cadastroForn(fornecedores, tlForn, produtos, tl);
    }
    printf("\nA quantidade em estoque desse produto: \n");
    scanf("%d", &produtos[tl].estoque);
    printf("\nDigite a descricao do produto: \n");
    gets(produtos[tl].descricao);
    printf("\nDigite o preco do produto: \n");
    scanf("%f", &produtos[tl].preco);
    printf("\nDigite a data de validade do produto: \n");
    scanf("%d/%d/%d", &produtos[tl].data.d, &produtos[tl].data.m, &produtos[tl].data.a);
    printf("\nProduto cadastrado com sucesso!\n");
    tl++;
    getch();
}

void cadastroForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd)
{
    printf("\nDigite o codigo do fornecedor: \n");
    scanf("%d", &fornecedores[tl].codForn);
    printf("Digite o nome do fornecedor: \n");
    gets(fornecedores[tl].nomeForn);
    printf("Digite a cidade do fornecedor: \n");
    gets(fornecedores[tl].cidadeForn);
    cadastroProdutos(produtos, tlProd, fornecedores, tl);
    tl++;
}

void cadastroCliente(tpCliente clientes[TF], int &tl)
{
    int aux;
    printf("\nDigite o CPF do cliente: \n");
    scanf("%lld", &aux);
    aux = buscaCliente(clientes, tl, aux);
    if (aux != -1)
    {
        printf("\nCliente cadastrado!\n");
        return;
    }
    printf("\nDigite o nome do cliente: \n");
    gets(clientes[tl].nomeCliente);

    clientes[tl].qtdeCompras = 0;
    clientes[tl].valorTotalComprado = 0;
    tl++;
    printf("\ncliente cadastrado com sucesso\n");
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

void exclusaoForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd)
{
    int aux, codForn;
    printf("Digite o codigo do fornecedor a ser excluido: \n");
    scanf("%d", &codForn);
    aux = buscaForn(fornecedores, tl, codForn);
    if (aux == -1)
    {
        printf("\nFornecedor nao cadastrado!\n");
        return;
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
    printf("\nFornecedor excluido com sucesso!\n");
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

void exclusaoCliente(tpCliente clientes[TF], int &tl)
{
    int aux;
    long int cpfCliente;
    printf("\nDigite o CPF do cliente a ser excluido: \n");
    scanf("%lld", &cpfCliente);
    aux = buscaCliente(clientes, tl, cpfCliente);
    if (aux == -1)
    {
        printf("\nCliente nao cadastrado!\n");
        return;
    }
    for (int i = aux; i < tl; i++)
    {
        clientes[i] = clientes[i + 1];
    }
    tl--;
    printf("\nCliente excluido com sucesso!\n");
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
    int liI = 8, colI = 2, liF = 19, colF = 38;
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
    int liI = 8, colI = 41, liF = 19, colF = 79;
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

void efetuarVenda(tpVenda vendas[TF], int &tl)
{
    return;
}

void relatorioDeVendas(tpVenda vendas[TF], int &tl)
{
    system("cls");
    if (tl == 0)
    {
        printf("nao ha vendas registradas para gerar um relatorio\n\n");
        getch();
    }
    else
    {
        for (int i = 0; i < tl; i++)
        {
            printf("\n*__________*\n");
            printf("\nCPF do clienten: %li\n", vendas[i].cpfCliente);
            printf("\nCodigo da venda: %d\n", vendas[i].codVenda);
            printf("\nTotal de vendas: %.2f\n", vendas[i].totalVendas);
            printf("\nData da venda %d/%d/%d\n", vendas[i].data.d, vendas[i].data.m, vendas[i].data.a);
            printf("\n*__________*\n");
        }
    }
    return;
}
// sem teste feito por Daniel

void exclusaoDeVendas(tpVenda vendas[TF], int &tl)
{
    return;
}

void consultaForn(tpFornecedor forncedores[TF], int tlForn)
{
    // SÓ FAZER UMA BUSCA COM LOOP PARA EXIBIR QUANTOS FORNECEDORES QUISER
    int codForn, busca;
    char op;
    system("cls");
    printf("\n\nConsulta de fornecedores\n\n");
    do
    {
        if (tlForn == 0)
        {
            printf("nao ha dados para consulta\n");
            getch();
        }
        else
        {
            printf("digite o codigo do fornecedor a ser consultado: \n\n");
            scanf("%d", &codForn);

            busca = buscaForn(forncedores, tlForn, codForn);
            if (busca == -1)
            {
                printf("\nCodigo invalido ou inexistente");
                getch();
            }
            else
            {
                printf("\nCodigo do fornecedor: %d\n", forncedores[busca].codForn);
                printf("\nNome do fornecedor: %s\n", forncedores[busca].nomeForn);
                printf("\nCidade do Fornecedor: %s\n", forncedores[busca].cidadeForn);
            }
        }
        fflush(stdin);
        printf("Deseja consultar outro fornecedor: (S/N)\n");
        op = toupper(getche());
    } while (op == 'S');
    return;
}
// sem teste feito por Daniel
void alteracaoFornecedores(tpFornecedor fornecedores[TF], int tl)
{
    int codForn, busca;
    char op;
    do
    {
        if (tl == 0)
        {
            printf("\nNao ha dados para alterar!!\n");
            getch();
        }
        else
        {
            printf("digite o codigo do fornecedor a ser alterado: \n");
            scanf("%d", &codForn);

            busca = buscaForn(fornecedores, tl, codForn);

            if (busca == -1)
            {
                printf("\nCodigo inexistente ou codigo invalido\n\n");
                getch();
            }
            else
            {
                printf("\ndigite o novo nome do forncedor: \n");
                puts(fornecedores[busca].nomeForn);
                printf("\nDigite a nova cidade do fornecedor: \n");
                puts(fornecedores[busca].cidadeForn);

                printf("\n\nAlteracoes feitas com sucesso!!\n\n");
                getch();
            }
            fflush(stdin);
            printf("\nDeseja alterar outro fornecedor: (S/N)");
            op = toupper(getche());
        }
    } while (op == 'S');
    return;
}
// sem teste feito por Daniel
void relatorioFornecedores(tpFornecedor fornecedores[TF], int tl)
{
    system("cls");

    if (tl == 0)
    {
        printf("Nao ha dados para fazer um relarotio\n\n");
        getch();
    }
    else
    {
        for (int i = 0; i < tl; i++)
        {
            printf("\n*__________*\n");
            printf("\nCodigo do fornecedor: %d", fornecedores[i].codForn);
            printf("\nNome do fornecedor: %s", fornecedores[i].nomeForn);
            printf("\nCidade do Fornecedor: %s", fornecedores[i].cidadeForn);
            printf("\n*__________*\n");
        }
    }
    return;
}
// sem teste feito por Daniel
void aumentoDePreco(tpFornecedor fornecedores[TF], int tl)
{
    return;
}

void consultaClientes(tpCliente clientes[TF], int tl)
{
    long int cpf;
    int busca;
    char op;
    system("cls");
    do
    {
        if (tl == 0)
        {
            printf("\n\nNao ha clientes para consulta\n\n");
            getch();
        }
        else
        {
            printf("\ndigite o cpf sem tracos e pontos para consulta: \n");
            scanf("%lld", &cpf);
            busca = buscaCliente(clientes, tl, cpf);
            if (busca == -1)
            {
                printf("\nCPF invalido ou inexistente\n");
                getch();
            }
            else
            {
                printf("\nCPF do cliente: %lld\n", clientes[busca].cpfCliente);
                printf("\nNome do cliente: %s\n", clientes[busca].nomeCliente);
                printf("\nQuantidade de compras feito: %d\n", clientes[busca].qtdeCompras);
                printf("\nTotal comprado pelo cliente: %.2f\n", clientes[busca].valorTotalComprado);
            }
        }
        printf("\n\nDeseja consultar outro cliente: (S/N)\n");
        fflush(stdin);
        op = toupper(getche());
    } while (op == 'S');
    return;
}

// sem teste feito por Daniel
void exclusaoClientes(tpCliente clientes[TF], int &tlClientes)
{
    return;
}

void alteracaoClientes(tpCliente clientes[TF], int tlClientes)
{
    return;
}

void relatorioClientes(tpCliente clientes[TF], int tlClientes)
{
    system("cls");
    if (tlClientes == 0)
    {
        printf("\n\nNao ha dados para gerar relatorio\n\n");
        getch();
    }
    else
    {
        for (int i = 0; i < tlClientes; i++)
        {
            printf("\n*__________*\n");
            printf("\nCPF do cliente: %lld\n", clientes[i].cpfCliente);
            printf("\nNome do cliente: %s\n", clientes[i].nomeCliente);
            printf("\nQuantidade de compras feito: %d\n", clientes[i].qtdeCompras);
            printf("\nTotal comprado pelo cliente: %.2f\n", clientes[i].valorTotalComprado);
            printf("\n*__________*\n");
        }
        getch();
    }
    return;
}
// sem teste feito por Daniel
char menuFornecedores(void)
{
    limparMenu();
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
                    efetuarVenda(vendas, tlVendas);
                    break;
                case 'B':
                    relatorioDeVendas(vendas, tlVendas);
                    break;
                case 'C':
                    exclusaoDeVendas(vendas, tlVendas);
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
                    cadastroProdutos(produtos, tlProdutos, fornecedores, tlFornecedores);
                    break;
                case 'B':
                    consultaProdutos(produtos, tlProdutos);
                    break;
                case 'C':
                    exclusaoProdutos(produtos, tlProdutos);
                    break;
                case 'D':
                    alteracaoProdutos(produtos, tlProdutos);
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
                    cadastroForn(fornecedores, tlFornecedores, produtos, tlProdutos);
                    break;
                case 'B':
                    consultaForn(fornecedores, tlFornecedores);
                    break;
                case 'C':
                    exclusaoForn(fornecedores, tlFornecedores, produtos, tlProdutos);
                    break;
                case 'D':
                    alteracaoFornecedores(fornecedores, tlFornecedores);
                    break;
                case 'E':
                    relatorioFornecedores(fornecedores, tlFornecedores);
                    break;
                case 'F':
                    aumentoDePreco(fornecedores, tlFornecedores);
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
                    cadastroCliente(clientes, tlClientes);
                    break;
                case 'B':
                    consultaClientes(clientes, tlClientes);
                    break;
                case 'C':
                    exclusaoClientes(clientes, tlClientes);
                    break;
                case 'D':
                    alteracaoClientes(clientes, tlClientes);
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
