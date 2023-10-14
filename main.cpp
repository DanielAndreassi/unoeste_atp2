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
    long int cpfCliente, qtdeCompras;
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
void insercaoAutomDeDados(tpProduto produtos[TF], int &tlProdutos, tpCliente clientes[TF], int &tlClientes, tpFornecedor fornecedores[TF], int tlFornecedores);
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF);

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

void insercaoAutomDeDados(tpProduto produtos[TF], int &tlProdutos, tpCliente clientes[TF], int &tlClientes, tpFornecedor fornecedores[TF], int tlFornecedores)
{
    return;
}

void exclusaoProdutos(tpProduto produtos[TF], int tlProdutos)
{
    return;
}

void relatorioProdutos(tpProduto produtos[TF], int tlProdutos)
{
    return;
}

void alteracaoProdutos(tpProduto protudos[TF], int tlProdutos)
{
    return;
}

void consultaProdutos(tpProduto produtos[TF], int tlProdutos)
{
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
    scanf("%ld", &aux);
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
    scanf("%ld", &cpfCliente);
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

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)

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
    return;
}

void exclusaoDeVendas(tpVenda vendas[TF], int &tl)
{
    return;
}

void consultaForn(tpFornecedor forncedores[TF])
{
    // SÓ FAZER UMA BUSCA COM LOOP PARA EXIBIR QUANTOS FORNECEDORES QUISER
    return;
}

void alteracaoFornecedores(tpFornecedor fornecedores[TF], int tl)
{
    return;
}

void relatorioFornecedores(tpFornecedor fornecedores[TF], int tl)
{
    return;
}

void aumentoDePreco(tpFornecedor fornecedores[TF], int tl)
{
    return;
}

void consultaClientes(tpCliente clientes[TF], int tl)
{
    return;
}

void exclusaoClientes(tpCliente clientes[TF], int &tlClientes)
{
    return;
}

void alteracaoClientes(tpCliente clientes[TF], int tlClientes)
{
    return;
}

void relatorioClientes(tpCliente fornecedores[TF], int tlFornecedores)
{
    return;
}

char menuFornecedores(void)
{
    clrscr();
    // VER ONDE DARÁ CLEAR NA TELA
    printf("\n# # #  MENU DE FORNECEDORES  # # #\n");
    printf("\n[A] Cadastro de Fornecedores");
    printf("\n[B] Consulta de Fornecedores");
    printf("\n[C] Exclusão de Fornecedores");
    printf("\n[D] Alteração de Fornecedores");
    printf("\n[E] Relatório de Fornecedores");
    printf("\n[F] Aumento de preços de produtos");
    printf("\n[ESC] Voltar para menu principal\n");
    printf("\n\nOpcao desejada: ");
    return toupper(getche());
}

char menuProdutos(void)
{
    clrscr();
    // VER ONDE DARÁ CLEAR NA TELA
    printf("\n# # #  MENU DE PRODUTOS  # # #\n");
    printf("\n[A] Cadastro de Produtos");
    printf("\n[B] Consulta de Produtos");
    printf("\n[C] Exclusão de Produtos");
    printf("\n[D] Alteração de Produtos");
    printf("\n[E] Relatório de Produtos");
    printf("\n[ESC] Voltar para menu principal\n");
    printf("\n\nOpcao desejada: ");
    return toupper(getche());
}

char menuVendas(void)
{
    clrscr();
    // VER ONDE DARÁ CLEAR NA TELA
    printf("\n# # #  MENU DE VENDAS  # # #\n");
    printf("\n[A] Efetuar uma venda");
    printf("\n[B] Relatório de vendas");
    printf("\n[C] Exclusão de uma venda");
    printf("\n[ESC] Voltar para menu principal\n");
    printf("\n\nOpcao desejada: ");
    return toupper(getche());
}

char menuClientes(void)
{
    clrscr();
    // VER ONDE DARÁ CLEAR NA TELA
    printf("\n# # #  MENU DE CLIENTES  # # #\n");
    printf("\n[A] Cadastro de Clientes");
    printf("\n[B] Consulta de Clientes");
    printf("\n[C] Exclusão de Clientes");
    printf("\n[D] Alteração de Clientes");
    printf("\n[E] Relatório de Clientes");
    printf("\n[ESC] Voltar para menu principal\n");
    printf("\n\nOpcao desejada: ");
    return toupper(getche());
}

char menuPrincipal(void)
{
    clrscr();
    // VER ONDE DARÁ CLEAR NA TELA
    printf("\n# # #  MENU PRINCIPAL  # # #\n");
    printf("\n[A] Seção de Vendas");
    printf("\n[B] Seção de Produtos");
    printf("\n[C] Seção de Fornecedores");
    printf("\n[D] Seção de Clientes");
    printf("\n[E] Inserção de dados automáticos");
    printf("\n[ESC] Sair\n");
    printf("\n\nOpcao desejada: ");
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

    // exibicao(); MOLDURA QUANDO ESTIVER PRONTA
    getch();

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
                    consultaForn(fornecedores);
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
