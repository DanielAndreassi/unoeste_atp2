#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>

#define TF 100

typedef struct{
    int d,m,a;
} tpData;
typedef struct{
    int codProd,estoque,codForn;
    char descricao[50];
    float preco;
    
    tpData data;
} tpProduto;




