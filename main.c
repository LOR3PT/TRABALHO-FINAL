#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#define clrscr() printf("\e[1;1H\e[2J")

// FUNCOES (tirar aviso amarelo)

void menu_admin();
void menu_funcionario();
void menu_utilizador();
void menu();

// VARIAVEIS GLOBAIS

static int logado = 0;
static int quantPort = 0;
char porticos[4][2][200];
time_t rawtime;






void mostrarPorticos()
{
    int flag = 1;
    clrscr();
    printf("PÓRTICOS\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Pórtico %d    ", i+1);
        for (int j = 0; j < 2; j++)
        {
            if(strlen(porticos[i][j]) == 0)
                flag = 0;
            else
                printf("%s\t", porticos[i][j]);
        }
        if(flag == 0)
            printf("NOT CREATED");
        printf("\n");
    }
    sleep(7);
    menu_admin();
}
void criarPorticos()
{
    clrscr();
    if (quantPort < 4)
    {
        while (quantPort < 4)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if ((j == 0 && i == 0) || (j == 0 && i == 1) || (j == 0 && i == 2) || (j == 0 && i == 3))
                    {
                        printf("Utilizador do Pórtico %d: ", i + 1);
                        scanf("%s", porticos[i][j]);
                    }
                    else
                    {
                        if ((j == 1 && i == 0) || (j == 1 && i == 1) || (j == 1 && i == 2) || (j == 1 && i == 3))
                        {
                            printf("Senha do Pórtico %d: ", i + 1);
                            scanf("%s", porticos[i][j]);
                        }
                    }
                    quantPort++;
                }
            }
        }
        printf("Pórticos criados com sucesso!");
        sleep(2);
        menu_admin();
    }
    else
    {
        printf("Máximo de pórticos já criados!");
    }
}

void menu_admin()
{
    int opcao;
    clrscr();
    printf("\n(1) Inserir os pórticos no sistema");
    printf("\n(2) Listar informação dos pórticos");
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
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 0:
        menu();
        break;
    case 1:
        criarPorticos();
        break;
    case 2:
        mostrarPorticos();
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

void menu_funcionario()
{

    clrscr();
    int opcao;
    if (logado == 0)
    {
        char idfuncionario[200];
        char password[200];

        printf("Introduza o username do funcionario do portico: ");
        scanf("%s", &idfuncionario);
        printf("\nIntroduza a password: ");
        scanf("%s", &password);
        if (strcmp(idfuncionario, "funcionario") == 0 && strcmp(password, "funcionario99") == 0)
        {
            int opcao;
            clrscr();
            printf("\n(1) Preço dos pórticos por classe");
            printf("\n(2) Inserir uma passagem de um veículo num pórtico");
            printf("\n(3) Listar as passagens no seu pórtico\n");
            printf("\n\n(0) LOGOUT\n");
            scanf("%d", &opcao);

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
        else
        {
            printf("\nUtilizador ou senhas incorretas!\n");
            sleep(2);
            menu_funcionario();
        }
    }
    else
    {
        int opcao;
        clrscr();
        printf("\n(1) Preço dos pórticos por classe");
        printf("\n(2) Inserir uma passagem de um veículo num pórtico");
        printf("\n(3) Listar as passagens no seu pórtico\n");
        printf("\n\n(0) LOGOUT\n");
        scanf("%d\n", &opcao);

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
}

void menu_utilizador()
{
    clrscr();
    int opcao;
    if (logado == 0)
    {
        char utilizador[200];
        char password[200];

        printf("Introduza o utilizador: ");
        scanf("%s", &utilizador);
        printf("\nIntroduza a password: ");
        scanf("%s", &password);

        if (strcmp(utilizador, "utilizador") == 0 && strcmp(password, "utilizador99") == 0)
        {
            clrscr();
            logado = 1;
            printf("\n(1) Preço dos pórticos por classe");
            printf("\n(2) Listar passagem de um veículo nos pórticos");
            printf("\n(3) Total gasto com o veículo \n");
            printf("\n\n(4) LOGOUT\n");
            scanf("%d", &opcao);

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
                    logado = 0;
                    menu();
                    break;
                default:
                    printf("Opção inválida");
                    break;
            }
        }
        else
        {
            printf("\nUtilizador ou senhas incorretas!\n");
            sleep(2);
            menu_utilizador();
        }
    }
    else
    {
        printf("\n(1) Preço dos pórticos por classe");
        printf("\n(2) Listar passagem de um veículo nos pórticos");
        printf("\n(3) Total gasto com o veículo \n");
        printf("\n\n(4) LOGOUT\n");
        scanf("%d\n", &opcao);
        time(&rawtime);


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
            logado = 0;
            menu();
            break;
        default:
            printf("Opção inválida");
            break;
        }
    }
}

void menu()
{
    int opcao;
    clrscr();
    printf("BEM VINDO AOS PÓRTICOS DA A28");
    printf("\nLOGIN");
    printf("\n(1) Administrador ");
    printf("\n(2) Funcionário ");
    printf("\n(3) Utilizador\n\n");
    time(&rawtime);
    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    printf("Data e hora atuais: %s\n", buffer);
    printf("\nEscolha a opção: ");
    scanf("%d", &opcao);

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

void main()
{
    menu();
}