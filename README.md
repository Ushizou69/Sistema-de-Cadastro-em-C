# Sistema de Cadastro de Funcionários

## Descrição

Sistema desenvolvido em linguagem C  para a disciplina de Algoritmos e Programação II para a Graduação do curso de Análise Desenvolvimento de Sistemas (ADS); este sistema permite realizar o cadastro e gerenciamento de funcionários de uma empresa, o programa pode inserir, listar e armazenar dados de funcionários, utilizando alocação dinâmica de memória e persistência dos registros em um arquivo binário. Este projeto foi feito em parceria com o colaborador Matheus N..

Cada funcionário possui um identificador de registro, nome e salário. Os dados cadastrados podem ser salvos em arquivo e posteriormente carregados para continuar o gerenciamento dos registros.

## Como Instalar?
Vá em <> Code, baixe o arquivo .zip:

<img width="594" height="475" alt="image" src="https://github.com/user-attachments/assets/ae2056c3-a9dc-4c87-84d3-7749b90b6f7a" />

<img width="675" height="608" alt="image" src="https://github.com/user-attachments/assets/c12da0ae-2af6-4831-8a3b-b83e63892e11" />

e clique com botão direito e clique em extrair aqui:

entre na pasta Sistema-de-Cadastro-em-C-main e procure o arquivo projetoFinal.exe e o clique duas vezes com o botão esquerdo, ou clique com o botão direito e clique em abrir.

<img width="1115" height="628" alt="image" src="https://github.com/user-attachments/assets/c53a37cb-8101-4f0a-8d40-e9e5bc079a9a" />


## Funcionalidades

* Cadastro de funcionários com ID, nome e salário;
* Listagem de todos os funcionários cadastrados;
* Carregamento dos registros armazenados em arquivo binário;
* Salvamento dos funcionários em arquivo binário;
* Exclusão do arquivo de dados;
* Gerenciamento dinâmico da memória utilizando `malloc`, `realloc` e `free`;
* Validação básica das entradas de ID e salário;
* Liberação da memória utilizada ao encerrar o programa;
* Menu interativo para acesso às funcionalidades do sistema.

## Armazenamento de Dados

Os funcionários são armazenados no arquivo binário:

`cadastro_funcionarios.bin`

O programa utiliza as funções `fopen`, `fread`, `fwrite` e `fclose` para realizar a leitura e gravação dos registros.

Os dados são armazenados diretamente a partir da estrutura `Funcionario`, permitindo que os registros sejam recuperados posteriormente quando o programa for executado novamente.

## Estrutura do Funcionário

Cada funcionário possui os seguintes dados:

* **ID de registro:** identificador numérico do funcionário;
* **Nome:** nome do funcionário;
* **Salário:** salário do funcionário.

## Objetivo

Desenvolver um sistema simples de cadastro de funcionários, colocando em prática conceitos fundamentais da linguagem C, como estruturas (`struct`), ponteiros, ponteiros para ponteiros, alocação dinâmica de memória, manipulação de arquivos binários e gerenciamento de memória.

O projeto também tem como objetivo aprimorar o conhecimento sobre manipulação de dados e persistência de informações em programas desenvolvidos em linguagem C.
