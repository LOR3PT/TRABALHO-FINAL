#include <conio.h>
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")

//
//LOGINS


char sessao[200] = "";
int quantPort;
char porticos[4][3][200];

// Exemplo Porticos
// {{"Portico 1", "port1", "port2"},
//  {"Portico 2", "port2", "port2"},
//  {"Portico 3", "port3", "port4"},
//  {"Portico 4", "port5", "port5"}};

//

void criarPortico(){
    quantPort = 0;
    if(quantPort<4){
        while(quantPort < 4){
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    printf("Digite a string para matriz[%d][%d]: ", i, j);
                    scanf("%s", porticos[i][j]);
                }
            }
        }
    }
    else{
        printf("%d",quantPort);
    }
}


void menu_admin(){
    int opcao;
    clrscr();
    sessao[200] = "admin";
    printf("\n(1) Inserir os pórticos no sistema com a relativa tabela de preços");
    printf("\n(2) Listar informação de todos os pórticos");
    printf("\n(3) Saber o preço de um determinado pórtico");
    printf("\n(4) Alterar os preços de todos os pórticos");
    printf("\n(5) Listar as passagens para cada um dos pórticos");
    printf("\n(6) Contabilizar o total gasto em cada um dos pórticos");
    printf("\n(7) Saber o total gasto em cada um dos pórticos");
    printf("\n(8) Saber total gasto em cada um dos pórticos por classes");
    printf("\n(9) Saber total por pórtico e por dia");
    printf("\n(10) Saber o total de veículos que passaram em cada um dos pórticos");
    printf("\n(11) Saber qual o pórtico com mais afluência");
    printf("\n(12) Saber média de passagens para cada um dos pórticos\n");
    printf("\n\n(0) LOGOUT\n");
    scanf("%d",&opcao);

    switch (opcao)
    {
        case 0: 
            menu();
            break;
        case 1:
            criarPortico();
            break;
        case 2:
            printf("2");
            break;
        case 3: 
            printf("3");
            break;
        case 4:
            printf("4");
            break;
        case 5:
            printf("5");
            break;
        case 6: 
            printf("6");
            break;
        case 7:
            printf("7");
            break;
        case 8:
            printf("8");
            break;
        case 9: 
            printf("9");
            break;
        case 10: 
            printf("10");
             break;
        case 11: 
            printf("11");
            break;
        case 12: 
            printf("12");
            break;
        default:
            printf("Opção inválida");
            break;
    }
}

void menu_funcionario(){
    int opcao;
    clrscr();
    sessao[200] = "func";
    printf("\n(1) Preço dos pórticos por classe");
    printf("\n(2) Inserir uma passagem de um veículo num pórtico");
    printf("\n(3) Listar as passagens no seu pórtico\n");
    printf("\n\n(0) LOGOUT\n");
    scanf("%d",&opcao);

    switch (opcao)
    {
        case 0: 
            menu();
            break;
        case 1:
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3: 
            printf("Passou 3 vezes");
            break;
        default:
            printf("Opção inválida");
            break;
    }
}

void menu_utilizador(){

    int opcao;
    clrscr();
    sessao[200] = "util";
    printf("\n(1) Preço dos pórticos por classe");
    printf("\n(2) Listar passagem de um veículo nos pórticos");
    printf("\n(3) Total gasto com o veículo \n");
    printf("\n\n(4) LOGOUT\n");
    scanf("%d",&opcao);

    switch (opcao)
    {
        case 1:
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3: 
            printf("3");
            break;
        case 4: 
            menu();
            break;
        default:
            printf("Opção inválida");
            break;
    }
}

void menu(){
    int opcao;
    clrscr();
    printf("BEM VINDO AOS PÓRTICOS DA A28");
    printf("\nLOGIN");
    printf("\n(1) Administrador ");
    printf("\n(2) Funcionário ");
    printf("\n(3) Utilizador");
    printf("\nEscolha a opção: ");
    scanf("%d" ,&opcao);

    switch (opcao)
    {
        case 1:
            menu_admin();
            break;
        case 2:
            menu_funcionario();
            break;
        case 3: 
            menu_utilizador();
            break;
        default:
            printf("Opção inválida");
            break;
    }
}

void main(){
    menu();
}