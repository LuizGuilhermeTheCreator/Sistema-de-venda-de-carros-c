# Sistema de Venda de Carros em C

Sistema desenvolvido em linguagem C para gerenciamento de clientes e vendas de veículos.

O projeto foi desenvolvido como prática dos fundamentos da linguagem C, trabalhando com estruturas de dados, alocação dinâmica de memória, manipulação de arquivos e organização do código em funções.

## Funcionalidades

* Cadastro de clientes
* Cadastro de vendas de veículos
* Registro do modelo e preço do veículo
* Cadastro de itens adicionais
* Cálculo do valor dos adicionais
* Cálculo do valor total da venda
* Busca de vendas pelo nome do cliente
* Consulta de todas as vendas registradas
* Geração de relatório geral de vendas
* Cálculo do valor médio das vendas
* Filtro de vendas acima de determinado valor
* Contagem de vendas com exatamente 2 adicionais
* Persistência das vendas em arquivo de texto

## Conceitos utilizados

* Structs para organização dos dados de clientes e vendas
* Ponteiros
* Alocação dinâmica de memória com `malloc()` e `free()`
* Manipulação de strings com funções da biblioteca `string.h`
* Manipulação de arquivos com `fopen()`, `fprintf()`, `fgets()`, `fscanf()` e `fclose()`
* Funções para organização e divisão das responsabilidades do programa
* Estruturas condicionais
* Estruturas de repetição
* Validação de dados de entrada
* Cálculos e geração de relatórios

## Persistência de dados

As informações das vendas são armazenadas no arquivo:

```text
vendas.txt
```

O arquivo é utilizado para registrar os dados das vendas e permitir consultas posteriores durante a execução do programa.

## Relatório de vendas

O sistema permite consultar informações gerais das vendas, incluindo:

* Quantidade total de vendas
* Vendas acima de um valor determinado
* Vendas com exatamente 2 adicionais
* Total de adicionais vendidos
* Valor total das vendas
* Valor médio das vendas

## Busca por cliente

Também é possível pesquisar as vendas de um cliente pelo nome.

O sistema apresenta as vendas encontradas e calcula:

* Quantidade de compras realizadas
* Valor médio das compras

## Como executar

### Pré-requisito

É necessário possuir um compilador C, como o GCC.

### Compilação

No terminal, execute:

```bash
gcc main.c -o sistema-vendas
```

### Execução

No Windows:

```bash
sistema-vendas.exe
```

No Linux:

```bash
./sistema-vendas
```

## Estrutura do projeto

```text
Sistema-de-venda-de-carros-c/
│
├── main.c
└── README.md
```

O arquivo `vendas.txt` é criado pelo próprio programa para armazenar os registros das vendas.

## Objetivo acadêmico

Projeto desenvolvido durante a graduação em **Sistemas de Informação**, com o objetivo de praticar conceitos fundamentais de programação em C e desenvolvimento de aplicações utilizando persistência de dados em arquivos.

---

**Tecnologia principal:** C
**Compilador utilizado:** GCC
