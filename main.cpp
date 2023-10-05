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

char menu (void);
void executar ();
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF);
void cadastroCliente(tpCliente clientes[TF], int &tl);
void cadastroProduto(tpProduto produtos[TF], int &tl, tpFornecedor fornecedores[TF], int &tlForn);
void cadastroForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd);
int buscaProd(tpProduto produtos[TF], int tl, int codProduto);
int buscaForn(tpFornecedor fornecedores[TF], int tl, int codForn);
int buscaCliente(tpCliente clientes[TF], int tl, long int cpfCliente);
int buscaProdPorFornecedor(tpProduto produtos[TF], int tl, int codForn);
int buscarCpfClienteVendas(tpVenda vendas[TF], int &tl, int cpf);
void exclusaoProd(tpProduto produtos[TF], int &tl, int indice);
void exclusaoForn(tpFornecedor fornecedores[TF], int &tl, tpProduto produtos[TF], int &tlProd);
void exclusaoCliente(tpCliente clientes[TF], int &tl);


// FUNÇÕES

void cadastroProduto(tpProduto produtos[TF], int &tl, tpFornecedor fornecedores[TF], int &tlForn)
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
        cadastroForn(fornecedores, tlForn,produtos,tl);
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
    cadastroProduto(produtos, tlProd, fornecedores, tl);
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
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI); printf("%c",205);
		gotoxy(i,LF); printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	}
	
	textcolor(7);
	textbackground(0);
}

char menu (void)
{
    clrscr();
    printf("\n# # #  M E N U  # # #\n");
	printf("\n[A] ");
	printf("\n[B] ");
	printf("\n[C] ");
	printf("\n[D] ");
	printf("\n[E] ");
	printf("\n[F] ");
	printf("\n[G] ");
	printf("\n[H] ");
	printf("\n[I] ");
	printf("\n[ESC] Sair\n");
	printf("\n\nOpcao desejada: ");
    return toupper(getche());
}

void executar ()
{
    char op;
    int tl=0;
    // exibicao(); MOLDURA QUANDO ESTIVER PRONTA
    getch();

    do
    {  
        op=menu();
        switch(op)
        {
            case 'A':
                break;
            case 'B':
                break;
            case 'C':
                break;
            case 'D':
                break;
            case 'E':
                break;
            case 'F':
                break;
            case 'G':
                break;
            case 'H':
        }

    }while(op!=27);
}

void main ()
{
    executar();    
}