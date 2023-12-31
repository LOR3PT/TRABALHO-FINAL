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
static int isCreatedPort = 0;
static int portEscolhido = 0;
static int quantPassagensPortico = 0;
static int quantPassagensPorticoMatr = 0;

char porticos[4][2][200];

float precario[4][4] = {
    {0.55, 1.00, 1.25, 1.40},
    {0.70, 1.30, 1.65, 1.80},
    {0.70, 1.20, 1.50, 1.70},
    {0.40, 0.75, 1.00, 1.10},
};

int colunas = 5;
int linhas = 0;

char ***matriz = NULL;

time_t rawtime;

void mostrarPorticos()
{
    clrscr();
    printf("PÓRTICOS\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Pórtico %d    ", i + 1);
        for (int j = 0; j < 2; j++)
        {
            if (strlen(porticos[i][j]) > 0)
            {
                printf("%s\t", porticos[i][j]);
                isCreatedPort = 1;
            }
        }
        if (isCreatedPort == 0)
            printf("NOT CREATED");
        printf("\n");
    }
    sleep(7);
    menu_admin();
}

void mostrarPrecario()
{
    clrscr();
    printf("PREÇÁRIO\n\n");
    printf("Classe  \t  1  \t  2  \t  3  \t  4\n");
    for (int i = 0; i < 4; i++)
    {

        if (i == 0)
            printf("Angeiras\t");
        else if (i == 1)
            printf("Póvoa    \t");
        else if (i == 2)
            printf("Esposende\t");
        else if (i == 3)
            printf("Neiva    \t");
        for (int j = 0; j < 4; j++)
        {
            if (precario[i][j] > 0)
            {
                printf("%.2f\t", precario[i][j]);
            }
        }
        printf("\n");
    }
    sleep(7);
    return;
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
        isCreatedPort = 1;
        sleep(2);
        menu_admin();
    }
    else
    {
        printf("Máximo de pórticos já criados!");
        sleep(2);
        menu_admin();
    }
}

void alterarPrecario(){
    clrscr();
    int classe;
    int destinofinal;
    float novopreco = 0;
    int opcao;
    printf("CLASSE DO VEÍCULO\n\n");
    printf("0 - VOLTAR");
    printf("\n\n1 - CLASSE 1 (Ligeiro de Passageiros [até 5 lugares]) *");
    printf("\n2 - CLASSE 2 (Pesado de Passageiros  [+ de 5 lugares]) *");
    printf("\n3 - CLASSE 3 (Ligeiro de Mercadorias [até 3 eixos]) *");
    printf("\n4 - CLASSE 4 (Pesado de Mercadorias  [+ de 3 eixos]) *");
    printf("\n*com ou sem reboque");
    printf("\nEscolha a opção: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 0:
        menu_admin();
        break;
    case 1:
        classe = 0;
        break;
    case 2:
        classe = 1;
        break;
    case 3:
        classe = 2;
        break;
    case 4:
        classe = 3;
        break;
    default:
        printf("Opção inválida!");
        sleep(1);
        alterarPrecario();
        break;
    }
    clrscr();
    printf("DESTINO FINAL\n\n");
    printf("0 - VOLTAR");
    printf("\n\n1 - Angeiras");
    printf("\n\n2 - Póvoa");
    printf("\n\n3 - Esposende");
    printf("\n\n4 - Neiva");
    printf("\nEscolha a opção: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 0:
        menu_admin();
        break;
    case 1:
        destinofinal = 0;
        break;
    case 2:
        destinofinal = 1;
        break;
    case 3:
        destinofinal = 2;
        break;
    case 4:
        destinofinal = 3;
        break;
    default:
        printf("Opção inválida!");
        sleep(1);
        alterarPrecario();
        break;
    }
    clrscr();
    printf("Indique o novo preço desta passagem: ");
    scanf("%f", &novopreco);
    if(novopreco != 0){
        precario[destinofinal][classe] = novopreco;
        printf("Preço atualizado com sucesso!");
        sleep(1);
        menu_admin();
    }
    else{
        printf("A passagem não pode ser gratuita!");
        sleep(1);
        alterarPrecario();
    }
}

void criarPassagem(){
    clrscr();
    int opcao;
    for (int passagem = 1; passagem <= 1; passagem++) {
        // Aumentando o número de linhas
        linhas++;
        matriz = (char ***)realloc(matriz, linhas * sizeof(char **));
        matriz[linhas - 1] = (char **)malloc(colunas * sizeof(char *));
        char matricula[200];
        int classe;
        char str_classe[20];
        int destinofinal;
        char str_destinofinal[20];
        char str_data[200];
        char str_portEscolhido[20];

        printf("Indique a matrícula: ");
        scanf("%s", &matricula);
        clrscr();
        printf("CLASSE DO VEÍCULO\n\n");
        printf("\n\n1 - CLASSE 1 (Ligeiro de Passageiros [até 5 lugares]) *");
        printf("\n2 - CLASSE 2 (Pesado de Passageiros  [+ de 5 lugares]) *");
        printf("\n3 - CLASSE 3 (Ligeiro de Mercadorias [até 3 eixos]) *");
        printf("\n4 - CLASSE 4 (Pesado de Mercadorias  [+ de 3 eixos]) *");
        printf("\n*com ou sem reboque");
        printf("\n\nEscolha a opção: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            classe = 0;
            break;
        case 2:
            classe = 1;
            break;
        case 3:
            classe = 2;
            break;
        case 4:
            classe = 3;
            break;
        default:
            printf("Opção inválida!");
            sleep(1);
            criarPassagem();
            break;
        }
        clrscr();
        printf("DESTINO FINAL\n\n");
        printf("\n1 - Angeiras");
        printf("\n2 - Póvoa");
        printf("\n3 - Esposende");
        printf("\n4 - Neiva");
        printf("\n\nEscolha a opção: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            destinofinal = 0;
            break;
        case 2:
            destinofinal = 1;
            break;
        case 3:
            destinofinal = 2;
            break;
        case 4:
            destinofinal = 3;
            break;
        default:
            printf("Opção inválida!");
            sleep(1);
            criarPassagem();
            break;
        }
        clrscr();
        time(&rawtime);
        struct tm *timeinfo;
        timeinfo = localtime(&rawtime);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        snprintf(str_classe, sizeof(str_classe), "%d", classe);
        snprintf(str_destinofinal, sizeof(str_destinofinal), "%d", destinofinal);
        snprintf(str_portEscolhido, sizeof(str_portEscolhido), "%d", portEscolhido);
        matriz[linhas - 1][0] = matricula;
        matriz[linhas - 1][1] = str_classe;
        matriz[linhas - 1][2] = str_destinofinal;
        matriz[linhas - 1][3] = buffer;
        matriz[linhas - 1][4] = str_portEscolhido;

        printf("Matriz resultante:\n");
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    sleep(2);
    menu_funcionario();
}

void listarPassagensPortico(){
    clrscr();
    char str_portEscolhido[20];
    snprintf(str_portEscolhido, sizeof(str_portEscolhido), "%d", portEscolhido);
    printf("Pórtico %s - PASSAGENS REGISTADAS :\n",str_portEscolhido);
    for (int i = 0; i < linhas; i++) {
        if(strcmp(matriz[i][4], str_portEscolhido) == 0){
            quantPassagensPortico++;
            for (int j = 0; j < colunas; j++) {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    printf("\nForam registadas %d passagens no pórtico %s\n", quantPassagensPortico, str_portEscolhido);
    sleep(2);
    menu_funcionario();
}

void listarPassagensPorticoMatricula(){
    clrscr();
    char matricula[200];
    printf("Indique a matrícula: ");
    scanf("%s",&matricula);

    printf("Matrícula %s - PASSAGENS REGISTADAS :\n", matricula);
    for (int i = 0; i < linhas; i++) {
        if(strcmp(matriz[i][0], matricula) == 0){
            quantPassagensPorticoMatr++;
            for (int j = 0; j < colunas; j++) {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    printf("\nForam registadas %d passagens com a matricula %s\n", quantPassagensPorticoMatr, matricula);
    sleep(2);
    menu_utilizador();
}

void menu_admin()
{
    int opcao;
    clrscr();
    if (logado == 0)
    {
        char utilizador[200];
        char password[200];

        printf("0 - VOLTAR\n");
        printf("Introduza o utilizador: ");
        scanf("%s", &utilizador);
        if (strcmp(utilizador, "0") == 0)
            menu();
        printf("Introduza a password: ");
        scanf("%s", &password);
        if (strcmp(utilizador, "admin99") == 0 && strcmp(password, "admin99") == 0)
        {
            clrscr();
            logado = 1;
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
            printf("\n(12) Saber média de passagens para cada um dos pórticos");
            printf("\n(0) LOGOUT");
            printf("\nEscolha a opção: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 0:
                menu();
                logado = 0;
                break;
            case 1:
                criarPorticos();
                break;
            case 2:
                mostrarPorticos();
                break;
            case 3:
                mostrarPrecario();
                break;
            case 4:
                alterarPrecario();
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
        else
        {
            printf("\nUtilizador ou senha incorreta!\n");
            sleep(2);
            menu_admin();
        }
    }
    else
    {
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
        printf("\n(12) Saber média de passagens para cada um dos pórticos");
        printf("\n(0) LOGOUT");
        printf("\nEscolha a opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            logado = 0;
            menu();
            break;
        case 1:
            criarPorticos();
            break;
        case 2:
            mostrarPorticos();
            break;
        case 3:
            mostrarPrecario();
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
}

void menu_funcionario()
{
    clrscr();
    int opcao;
    char utport[200];
    char pwport[200];
    if (logado == 0)
    {
        if (isCreatedPort == 0)
        {
            printf("Crie os pórticos primeiro!");
            sleep(2);
            menu();
        }
        else
        {
            printf("1 - Pórtico 1");
            printf("\n2 - Pórtico 2");
            printf("\n3 - Pórtico 3");
            printf("\n4 - Pórtico 4");
            printf("\nEscolha o Pórtico: ");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 1:
                strcpy(utport, porticos[0, 0]);
                strcpy(pwport, porticos[1, 0]);
                portEscolhido = 1;
                break;
            case 2:
                strcpy(utport, porticos[1, 0]);
                strcpy(pwport, porticos[1, 1]);
                portEscolhido = 2;
                break;
            case 3:
                strcpy(utport, porticos[2, 0]);
                strcpy(pwport, porticos[1, 2]);
                portEscolhido = 3;
                break;
            case 4:
                strcpy(utport, porticos[3, 0]);
                strcpy(pwport, porticos[1, 3]);
                portEscolhido = 4;
                break;

            default:
                printf("Opcao inválida!");
                sleep(2);
                menu_funcionario();
                break;
            }
            char idfuncionario[200];
            char password[200];

            printf("Introduza o username do funcionario do portico: ");
            scanf("%s", &idfuncionario);
            printf("\nIntroduza a password: ");
            scanf("%s", &password);

            if (strcmp(idfuncionario, utport) == 0 && strcmp(password, pwport) == 0)
            {
                int opcao;
                logado = 1;
                clrscr();
                printf("Posto de Trabalho: Pórtico %d", portEscolhido);
                printf("\n(1) Consultar preços por classe");
                printf("\n(2) Inserir uma passagem de um veículo num pórtico");
                printf("\n(3) Listar as passagens no seu pórtico\n");
                printf("\n\n(0) LOGOUT\n");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 0:
                    logado = 0;
                    menu();
                    break;
                case 1:
                    mostrarPrecario();
                    break;
                case 2:
                    criarPassagem();
                    break;
                case 3:
                    listarPassagensPortico();
                    break;
                default:
                    printf("Opção inválida");
                    menu_funcionario();
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
    }
    else
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
            logado = 0;
            menu();
            break;
        case 1:
            mostrarPrecario();
            break;
        case 2:
            criarPassagem();
            break;
        case 3:
            listarPassagensPortico();
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
    printf("\n(1) Preço dos pórticos por classe");
    printf("\n(2) Listar passagem de um veículo nos pórticos");
    printf("\n(3) Total gasto com o veículo \n");
    printf("\n\n(4) LOGOUT\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
            mostrarPrecario();
            break;
        case 2:
            listarPassagensPorticoMatricula();
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