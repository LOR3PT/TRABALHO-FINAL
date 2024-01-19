#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
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
static int quantPassagensPorticoAdm = 0;
static int quantPassagensPorticoAdmMatreData = 0;
static int quantPassagensPorticoData = 0;

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

void mostrarPrecario(char *path)
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
    sleep(2);
    if (strcmp(path, "utl") == 0)
        menu_utilizador();
    else if (strcmp(path, "func") == 0)
        menu_funcionario();
    else if (strcmp(path, "adm") == 0)
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

void alterarPrecario()
{
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
    if (novopreco != 0)
    {
        precario[destinofinal][classe] = novopreco;
        printf("Preço atualizado com sucesso!");
        sleep(1);
        menu_admin();
    }
    else
    {
        printf("A passagem não pode ser gratuita!");
        sleep(1);
        alterarPrecario();
    }
}

void criarPassagem()
{
    clrscr();
    int opcao;
    for (int passagem = 1; passagem <= 1; passagem++)
    {
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
        printf("1 - CLASSE 1 (Ligeiro de Passageiros [até 5 lugares]) *");
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
        printf("1 - Angeiras");
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
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
        snprintf(str_classe, sizeof(str_classe), "%d", classe);
        snprintf(str_destinofinal, sizeof(str_destinofinal), "%d", destinofinal);
        snprintf(str_portEscolhido, sizeof(str_portEscolhido), "%d", portEscolhido);
        matriz[linhas - 1][0] = matricula;
        matriz[linhas - 1][1] = str_classe;
        matriz[linhas - 1][2] = str_destinofinal;
        matriz[linhas - 1][3] = buffer;
        matriz[linhas - 1][4] = str_portEscolhido;

        printf("Matriz resultante:\n");
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    sleep(2);
    menu_funcionario();
}

void listarPassagensPortico()
{
    clrscr();
    char str_portEscolhido[20];
    snprintf(str_portEscolhido, sizeof(str_portEscolhido), "%d", portEscolhido);
    printf("Pórtico %s - PASSAGENS REGISTADAS :\n", str_portEscolhido);
    for (int i = 0; i < linhas; i++)
    {
        if (strcmp(matriz[i][4], str_portEscolhido) == 0)
        {
            quantPassagensPortico++;
            for (int j = 0; j < colunas; j++)
            {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    printf("Foram registadas %d passagens no pórtico %s.", quantPassagensPortico, str_portEscolhido);
    sleep(2);
    menu_funcionario();
}

void listarPassagensPorticoAdmin()
{
    clrscr();
    int nport;
    int opcao;
    printf("1 - Pórtico 1");
    printf("\n2 - Pórtico 2");
    printf("\n3 - Pórtico 3");
    printf("\n4 - Pórtico 4");
    printf("\nEscolha o Pórtico: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        nport = 1;
        break;
    case 2:
        nport = 2;
        break;
    case 3:
        nport = 3;
        break;
    case 4:
        nport = 4;
        break;
    default:
        printf("Opcao inválida!");
        sleep(2);
        menu_funcionario();
        break;
    }
    clrscr();
    char str_portEscolhido[20];
    snprintf(str_portEscolhido, sizeof(str_portEscolhido), "%d", nport);
    printf("Pórtico %s - PASSAGENS REGISTADAS :\n", str_portEscolhido);
    for (int i = 0; i < linhas; i++)
    {
        if (strcmp(matriz[i][4], str_portEscolhido) == 0)
        {
            quantPassagensPortico++;
            for (int j = 0; j < colunas; j++)
            {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    printf("Foram registadas %d passagens no pórtico %s.", quantPassagensPortico, str_portEscolhido);
    sleep(2);
    menu_admin();
}

void listarPassagensPorticoMatricula()
{
    quantPassagensPorticoMatr = 0;
    clrscr();
    char matricula[200];
    printf("Indique a matrícula: ");
    scanf("%s", &matricula);
    clrscr();
    printf("Matrícula %s - PASSAGENS REGISTADAS :", matricula);
    for (int i = 0; i < linhas; i++)
    {
        if (strcmp(matriz[i][0], matricula) == 0)
        {
            quantPassagensPorticoMatr++;
            for (int j = 0; j < colunas; j++)
            {
                printf("%s\t", matriz[i][j]);
            }
            printf("\n");
        }
    }
    printf("\nForam registadas %d passagens com a matricula %s.", quantPassagensPorticoMatr, matricula);
    sleep(2);
    menu_utilizador();
}

void listarTotalMatricula()
{
    quantPassagensPorticoMatr = 0;
    int classe;
    int destinofinal;
    float soma = 0;
    clrscr();
    char matricula[200];
    printf("Indique a matrícula: ");
    scanf("%s", &matricula);

    printf("Matrícula %s - Total Gasto\n", matricula);
    for (int i = 0; i < linhas; i++)
    {
        if (strcmp(matriz[i][0], matricula) == 0)
        {
            quantPassagensPorticoMatr++;
            classe = atoi(&matriz[i][1]);
            destinofinal = atoi(&matriz[i][2]);
            soma = soma + precario[destinofinal][classe];
        }
    }
    printf("Foram registadas %d passagens com a matricula %s somando um total de %.2f€\n", quantPassagensPorticoMatr, matricula, soma);
    sleep(3);
    menu_utilizador();
}

void listarTotalPorticos()
{
    clrscr();
    quantPassagensPorticoAdm = 0;
    int classe;
    int destinofinal;
    float soma = 0;
    clrscr();
    for (int a = 0; a < 4; a++)
    {
        printf("Pórtico %d - Total Gasto\n", (a + 1));
        for (int i = 0; i < linhas; i++)
        {
            if (strcmp(matriz[i][4], (a + 1)) == 0)
            {
                quantPassagensPorticoAdm++;
                classe = atoi(&matriz[i][1]);
                destinofinal = atoi(&matriz[i][2]);
                soma = soma + precario[destinofinal][classe];
            }
        }
        printf("Foram registadas %d passagens no pórtico %d somando um total de %.2f€\n\n", quantPassagensPorticoAdm, (a + 1), soma);
    }
    sleep(3);
    menu_admin();
}

void listarTotalPorticosMatr()
{
    clrscr();
    quantPassagensPorticoAdmMatreData = 0;
    int classe;
    int destinofinal;
    float soma = 0;
    char matricula[200];
    int flag = 0;
    printf("Indique a matrícula: ");
    scanf("%s", &matricula);
    clrscr();
    char data[200];
    printf("Indique a data: ");
    scanf("%s", &data);
    clrscr();
    if (linhas == 0)
    {
        printf("Não existe nenhuma passagem nas Portagens A28!");
    }
    else
    {
        clrscr();
        for (int a = 0; a < 4; a++)
        {

            printf("Pórtico %d - Total Gasto pela Matrícula %s\n", (a + 1), matricula);
            quantPassagensPorticoAdmMatreData = 0;
            flag = 0;
            for (int i = 0; i < linhas; i++)
            {
                char charValue[200];
                snprintf(charValue, sizeof(charValue), "%d", (a + 1));
                if (strcmp(matriz[i][0], matricula) == 0 && strcmp(matriz[i][3], data) == 0 && strcmp(matriz[i][4], charValue) == 0)
                {
                    quantPassagensPorticoAdmMatreData++;
                    classe = atoi(&matriz[i][1]);
                    destinofinal = atoi(&matriz[i][2]);
                    soma = soma + precario[destinofinal][classe];
                    flag = 1;
                    printf("Foram registadas %d passagens no pórtico %d pela matrícula %s no dia %s somando um total de %.2f€\n\n", quantPassagensPorticoAdmMatreData, (a + 1), matricula, data, soma);
                }

                if (flag == 0)
                {
                    printf("Não foram registadas passagens!\n\n");
                }
            }
        }
    }
    sleep(3);
    menu_admin();
}

void listarTotalPorticosData()
{
    clrscr();
    quantPassagensPorticoData = 0;
    int classe;
    int destinofinal;
    float soma = 0;
    int flag = 0;
    char data[200];
    printf("Indique a data: ");
    scanf("%s", &data);
    clrscr();
    if (linhas == 0)
    {
        printf("Não existe nenhuma passagem nas Portagens A28!");
    }
    else
    {
        clrscr();
        for (int a = 0; a < 4; a++)
        {

            printf("Pórtico %d - Total Gasto no dia %s\n", (a + 1), data);
            quantPassagensPorticoData = 0;
            flag = 0;
            for (int i = 0; i < linhas; i++)
            {
                char charValue[200];
                snprintf(charValue, sizeof(charValue), "%d", (a + 1));
                if (strcmp(matriz[i][3], data) == 0 && strcmp(matriz[i][4], charValue) == 0)
                {
                    quantPassagensPorticoData++;
                    classe = atoi(&matriz[i][1]);
                    destinofinal = atoi(&matriz[i][2]);
                    soma = soma + precario[destinofinal][classe];
                    flag = 1;
                    printf("Foram registadas %d passagens no pórtico %d no dia %s somando um total de %.2f€\n\n", quantPassagensPorticoData, (a + 1), data, soma);
                }

                if (flag == 0)
                {
                    printf("Não foram registadas passagens!\n\n");
                }
            }
        }
    }
    sleep(3);
    menu_admin();
}

void listarTotalPorticosClasses()
{
    int opcao;
    int classe;
    int destinofinal;
    int soma = 0;
    int quantPassagensPorticoAdmClasse = 0;
    clrscr();
    printf("CLASSE DO VEÍCULO\n\n");
    printf("1 - CLASSE 1 (Ligeiro de Passageiros [até 5 lugares]) *");
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
        menu_admin();
        break;
    }
    clrscr();
    char charPortico[200];
    char charClasse[200];
    int flag = 0;
    if (linhas == 0)
    {
        printf("Não existe nenhuma passagem nas Portagens A28!");
    }
    else
    {

        for (int a = 0; a < 4; a++)
        {
            printf("Pórtico %d - Total Gasto pela Classe %d\n", (a + 1), classe);
            quantPassagensPorticoAdmClasse = 0;
            flag = 0;
            for (int i = 0; i < linhas; i++)
            {
                snprintf(charPortico, sizeof(charPortico), "%d", (a + 1));
                snprintf(charClasse, sizeof(charPortico), "%d", classe);
                if (strcmp(matriz[i][4], charPortico) == 0 && strcmp(matriz[i][1], charClasse) == 0)
                {
                    quantPassagensPorticoAdmClasse++;
                    classe = atoi(&matriz[i][1]);
                    destinofinal = atoi(&matriz[i][2]);
                    soma = soma + precario[destinofinal][classe];
                    printf("Foram registadas %d passagens no pórtico %d pela classe %s somando um total de %.2f€\n\n", quantPassagensPorticoAdmClasse, (a + 1), charClasse, soma);
                    flag = 1;
                }

                if (flag == 0)
                {
                    printf("Não foram registadas passagens!\n\n");
                }
            }
        }
    }
    sleep(3);
    menu_admin();
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
            printf("0 - LOGOUT");
            printf("\n1 - Inserir os pórticos no sistema");
            printf("\n2 - Listar informação dos pórticos");
            printf("\n3 - Saber o preço de um determinado pórtico");
            printf("\n4 - Alterar os preços de todos os pórticos");
            printf("\n5 - Listar as passagens de um pórtico");
            printf("\n6 - Contabilizar o total gasto em cada um dos pórticos");
            printf("\n7 - Saber o total gasto em cada um dos pórticos por veiculo num dia;");
            printf("\n8 - Saber total gasto em cada um dos pórticos por classes");
            printf("\n9 - Saber total por pórtico e por dia");
            printf("\n10 - Saber o total de veículos que passaram em cada um dos pórticos");
            printf("\n11 - Saber qual o pórtico com mais afluência");
            printf("\n12 - Saber média de passagens para cada um dos pórticos\n");
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
                mostrarPrecario("adm");
                break;
            case 4:
                alterarPrecario();
                break;
            case 5:
                listarPassagensPorticoAdmin();
                break;
            case 6:
                listarTotalPorticos();
                break;
            case 7:
                listarTotalPorticosMatr();
                break;
            case 8:
                listarTotalPorticosClasses();
                break;
            case 9:
                listarTotalPorticosData();
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
                sleep(2);
                menu_admin();
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
        clrscr();
        printf("0 - LOGOUT");
        printf("\n1 - Inserir os pórticos no sistema");
        printf("\n2 - Listar informação dos pórticos");
        printf("\n3 - Saber o preço de um determinado pórtico");
        printf("\n4 - Alterar os preços de todos os pórticos");
        printf("\n5 - Listar as passagens de um pórtico");
        printf("\n6 - Contabilizar o total gasto em cada um dos pórticos");
        printf("\n7 - Saber o total gasto em cada um dos pórticos por veiculo num dia;");
        printf("\n8 - Saber total gasto em cada um dos pórticos por classes");
        printf("\n9 - Saber total por pórtico e por dia");
        printf("\n10 - Saber o total de veículos que passaram em cada um dos pórticos");
        printf("\n11 - Saber qual o pórtico com mais afluência");
        printf("\n12 - Saber média de passagens para cada um dos pórticos\n");
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
            mostrarPrecario("adm");
            break;
        case 4:
            alterarPrecario();
            break;
        case 5:
            listarPassagensPorticoAdmin();
            break;
        case 6:
            listarTotalPorticos();
            break;
        case 7:
            listarTotalPorticosMatr();
            break;
        case 8:
            listarTotalPorticosClasses();
            break;
        case 9:
            listarTotalPorticosData();
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
            sleep(2);
            menu_admin();
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

            printf("Introduza o utilizador: ");
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
                    mostrarPrecario("func");
                    break;
                case 2:
                    criarPassagem();
                    break;
                case 3:
                    listarPassagensPortico();
                    break;
                default:
                    printf("Opção inválida");
                    sleep(2);
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
            mostrarPrecario("func");
            break;
        case 2:
            criarPassagem();
            break;
        case 3:
            listarPassagensPortico();
            break;
        default:
            printf("Opção inválida");
            sleep(2);
            menu_funcionario();
            break;
        }
    }
}

void menu_utilizador()
{
    clrscr();
    int opcao;
    printf("\n0 - VOLTAR");
    printf("\n1 - Preço dos pórticos por classe");
    printf("\n2 - Listar passagem de um veículo nos pórticos");
    printf("\n3 - Total gasto com o veículo\n");
    printf("\nEscolha a opção: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        mostrarPrecario("utl");
        break;
    case 2:
        listarPassagensPorticoMatricula();
        break;
    case 3:
        listarTotalMatricula();
        break;
    case 0:
        menu();
        logado = 0;
        break;
    default:
        printf("Opção inválida");
        sleep(2);
        menu_utilizador();
        break;
    }
}

void menu()
{
    int opcao;
    clrscr();
    printf("BEM VINDO AOS PÓRTICOS DA A28");
    printf("\nLOGIN\n");
    printf("\n0 - SAIR");
    printf("\n1 - Administrador ");
    printf("\n2 - Funcionário ");
    printf("\n3 - Utilizador\n\n");
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
    case 0:
        break;
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
    clrscr();
}