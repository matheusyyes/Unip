#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <locale.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#define COL 10
#define ROW 12
#define FALSE 0
#define TRUE 1

void inicializa(char matriz[ROW][COL]);
int mostrarPainelProf(char matriz[2][10]);
int mostrarPainelAluno(char matriz[8][10]);
void reservar(char matriz[ROW][COL]);
void legenda();
int reservarProfessores();
void sorteio();
int reservaAluno();
int menuOpcao();
int colunaY();
int linhaX();
int verificar_rg(int tipo);
int rgPessoa;
int cadastro();
void ticket();



int main (void) {
    setlocale(LC_ALL, "Portuguese");
    char matriz[ROW][COL];
    int rg,lugar[5],row,col;
    int opcao;
    int loopContinue=TRUE;
    int flag;
    inicializa(matriz); //Iniciliza a matriz que representa os lugares com valores (.) e (P).
    do {
        system("cls");//Limpa a tela
        opcao=menuOpcao();// chama a menu que retorna qual opção foi escolhida pelo usuario.
        system("cls");
        int tipoPessoa; // saber se o usuario é professo, convidado, aluno ou PNE.

        switch(opcao) { // determina qual ação o usuario ira realizar de acordo com a opção escolhida no menu.
        case 1:

            cadastro(); //chamando função cadastro

            break;

        case 2:

            printf("Voce deseja reservar uma cadeira para: \n \n1 - Professor \n2 - Convidado \n3 - Aluno \n4 - PNE:\n \nopcao:");
            scanf( "%i",&tipoPessoa);
            system("cls");
             if (tipoPessoa == 1 || tipoPessoa == 2 || tipoPessoa == 3 || tipoPessoa == 4){


                rg = verificar_rg(tipoPessoa); // chama função que verifica que o se o dono do rg foi registrado no sistema.



            if (tipoPessoa == 1 || tipoPessoa == 2 ) { // Exibe os lugares disponiveis para professores e convidados.
                flag = mostrarPainelProf(matriz);
                if (flag==0) { // flag conta quantos lugares disponiveis existem.
                    printf("           Nao ha lugar disponivel para professores e convidados\n \n");
                    system("pause");

                } else {

                    reservarProfessores(matriz,rg,tipoPessoa);

                }
            }
            if (tipoPessoa == 3 || tipoPessoa == 4) { // Exibe os lugares disponiveis para Alunos e Pne.

                flag = mostrarPainelAluno(matriz);
                if (flag==0) {
                    printf("           Nao ha lugar disponivel para Alunos e PNE \n \n");
                    system("pause");
                } else {
                    reservaAluno(matriz,rg);
                }

            }
            }
            else{
                        printf("Digite um valor valido !!! \n");
                        system("pause");

            }

            break;
        case 3:

            sorteio(); // Função que aleatoriamente escolhe um Aluno, professor ou pne para ganha um brinde.

            break;

        case 4:

            ticket(); // Função que mostra qual o lugar o usuario pertence.

            break;

        case 5:
            loopContinue = FALSE; //condicao para saida do programa
        }
    } while(loopContinue);
    getchar();
    return 0 ;
}

int verificar_rg(int tipoPessoa) {

    MYSQL conexao; // armazena as credenciais para ter acesso ao banco.
    MYSQL_RES *result; //  armazena o resultado de uma consulta.
    MYSQL_ROW row;
    int i, num_fields, tipo;
    int rg;
    char query[150];
    mysql_init(&conexao); // inicializa uma conexao.

    tipo = tipoPessoa; // pega via parametro qual tipo é o tipo do usuario.



    printf("Digite o seu rg:");
    scanf("%i",&rg);
    if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) { // credenciais para acessar o banco.

        if (tipo == 1 || tipo == 3 || tipo == 4) {
            sprintf(query, "select id from tb_usuarios where rg = '%i';",rg);// procura pelo id do usuario q tem X rg, sendo estes usuarios professor, aluno ou PNE.
        }
        else
        {
            sprintf(query, "select id from tb_convidado where tb_convidado_rg = '%i';",rg);// procura pelo id do usuario q tem X rg, sendo estes usuario convidado.
        }
        mysql_query(&conexao, query); //envia uma query para o banco de dados ativo no servidor da conexão informada em conexao.

        result = mysql_use_result(&conexao); //inicicia a recuperação de um resultado mas não lê realmente o resultado.


        if (mysql_fetch_row(result) == 0)//  Ele lê o resultado de uma consulta diretamente do servido, se não ouver resultado ele retornara 0.
        {
            printf("Rg nao registrado!! \n ");
            system("pause");
            main();
        }

    }

    return rg ;
}


void inicializa(char matriz[ROW][COL]) { // preenche a matriz com valores "." e "p"
    int i,j,flag=0;
    for(i=1; i<=ROW; i++)
        for(j=1; j<=COL; j++)
            matriz[i][j] = '.';
    matriz [6][9] = 'p';
    matriz [7][9] = 'p';
    matriz [8][9] = 'p';
    matriz [6][10] = 'p';
    matriz [7][10] = 'p';


}

int mostrarPainelProf(char matriz[2][10]) { // Mostra os lugares disponiveis para professores e convidados

    int i,j,flag=0;
    printf("\n\n         %c   PAINEL DE LUGARES   %c\n\n",16,17);
    printf("          ");
    for(i=1; i<=10; i++)
        printf("%d     ",i);
    for(i=9; i<=10; i++) {
        printf("\n\n     %d",i);
        for(j=1; j<=10; j++) {
            printf("   (%c)",matriz[i][j]);

            if (matriz[i][j]=='.') //conta quantos lugares tem disponiveis, quando flag valer 0, significa que não ha mais lugares disponiveis e sera exibido uma msg.
            {
                flag++;
            }
        }

    }


    legenda(); //apresenta quais os significados do "R", ".", "p"
    return(flag);
}

int mostrarPainelAluno(char matriz[8][10]) { // Mostra os lugares disponiveis para Alunos e Pne
    int i,j,flag=0;
    printf("\n\n         %c   PAINEL DE OCUPACOES   %c\n\n",16,17);
    printf("          ");
    for(i=1; i<=10; i++)
        printf("%d     ",i);
    for(i=1; i<=8; i++) {
        printf("\n\n     %d",i);
        for(j=1; j<=10; j++) {
            printf("   (%c)",matriz[i][j]);
            if (matriz[i][j]=='.' || matriz[i][j]=='p' ) //conta quantos lugares tem disponiveis, quando flag valer 0, significa que não ha mais lugares disponiveis e sera exibido uma msg.
            {
                flag++;
            }
        }
    }

    legenda(); //apresenta quais os significados do "R", ".", "p"
    return(flag);

}

int menuOpcao() { //Mostra as opções da aplicação.

    int opcao=4;
    do {
        system("cls");
        printf("\n\n                    %c  MENU  %c\n\n",16,17);

        printf("                %c  1- Cadastro          %c\n",16,17);

        printf("                %c  2- Reservar          %c\n",16,17);

        printf("                %c  3- Sorteio           %c\n",16,17);

        printf("                %c  4- Consultar Lugar   %c\n\n",16,17);

        printf("                   opcao: ");
        scanf("%d",&opcao);
        fflush(stdin);



        if(opcao <= 0 || opcao > 4) {
            printf("\n\n\n    DIGITE APENAS VALORES CORESPONDENTES AO MENU !!");
            getch();
        }

    } while(opcao <= 0 || opcao > 4);

    return opcao;
}

void legenda() { // apresenta uma legenda
    printf("\n\n\n        .-Livre  P-PNE  R-Reservado\n\n");

}

void sorteio() {
    int i, j, x;


    x =1+(rand()%14); //dá a X um valor aleatório de 1 a 14;
    printf("VENCEDOR DO SORTEIO ....\n ");
    printf("                            ");
    printf(" \n \n                      ID = %i\n",x);

    MYSQL conexao;
    MYSQL_RES *result;
    MYSQL_ROW rows;
    int num_fields;
    char query[150];
    mysql_init(&conexao);
    if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) )
    {


        sprintf(query, "select nome  from tb_usuarios where id = '%i';",x); // busca o usuario no qual o id é igual a x



        mysql_query(&conexao, query);


        result = mysql_use_result(&conexao);


        num_fields = mysql_num_fields(result);


        while ((rows = mysql_fetch_row(result))) {
            for( i = 0; i < num_fields; i++) {

                printf("                      NOME: %s \n \n", rows[i] ); // imprime o nome do usuario.
            }
        }


        mysql_close(&conexao); // finaliza a conexao com o banco


    }
    system(" \n \n pause");
}

int cadastro () {

    int tipoPessoa, esco = 2;
    printf("Voce e: \n 1 - Professor \n 2 - Aluno \n 3 - Convidado \n 4 - Portador de necessidade especial \n \n opcao: ");
    scanf("%i", &tipoPessoa);
    system("cls");
    switch(tipoPessoa) {
    case 1: { // Cadastra professor
        MYSQL conexao;
        int res;
        char query[100];
        char nomeProfessor[31], rgProfessor[12], emailProfessor[65], carteirinhaProfessor[16], telefoneProfessor[21];

        do { // repete estas etapas caso o usuario diga que as informações não estão corretas.
            printf("Informe seu nome completo: ");
            scanf(" %[^\n]s", &nomeProfessor);
            fflush(stdin);

            printf("Informe seu RG: ");
            scanf(" %s", &rgProfessor);
            fflush(stdin);

            printf("Informe seu telefone com DDD: ");
            scanf(" %s", &telefoneProfessor);
            fflush(stdin);

            printf("Informe seu E-mail: ");
            scanf(" %s", &emailProfessor);
            fflush(stdin);

            system("cls");

            printf("\n Nome: %s", &nomeProfessor);
            printf("\n RG: %s", &rgProfessor);
            printf("\n Telefone:%s", &telefoneProfessor);
            printf("\n Email: %s", &emailProfessor);

            printf(" \n As Informacoes acima estao corretas? \n \n 1 - sim\n 2 - nao \n");
            scanf("%i",&esco);
            system("cls");

        } while (esco == 2);

        //Inserir dados no banco//
        mysql_init(&conexao);

        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
            sprintf(query,"call cadas_usu ('%s','%s','%s','%s');", nomeProfessor, telefoneProfessor, emailProfessor, rgProfessor);
            res = mysql_query(&conexao,query);
            if (!res)
                printf("Cadastrado com sucesso!! \n");
            else
                printf("Erro na inser��o %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            mysql_close(&conexao);
        } else {
            printf("Falha de conexao\n");
            printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
        }

        system("pause");


        break;
    }
    case 2: {
        MYSQL conexao;
        int res;
        int esco = 2;
        char query[100];
        char nomeAluno[31], rgAluno[12], emailAluno[65], ra[16], telefoneAluno[21];
        do {
            printf("Informe seu nome completo: ");
            scanf(" %[^\n]s", &nomeAluno);
            fflush(stdin);

            printf("Informe seu RG: ");
            scanf(" %s", &rgAluno);
            fflush(stdin);

            printf("Informe seu telefone com DDD: ");
            scanf(" %s", &telefoneAluno);
            fflush(stdin);

            printf("Informe seu E-mail: ");
            scanf(" %s", &emailAluno);
            fflush(stdin);
            system("cls");

            printf("\n Nome: %s", &nomeAluno);
            printf("\n RG: %s", &rgAluno);
            printf("\n Telefone:%s", &telefoneAluno);
            printf("\n Email: %s", &emailAluno);


            printf(" \n As Informacoes acima estao corretas? \n \n 1 - sim\n 2 - nao \n ");
            scanf("%i",&esco);
            system("cls");
        } while(esco == 2);
        //conexao com o banco //
        mysql_init(&conexao);
        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
            sprintf(query,"call cadas_usu ('%s','%s','%s','%s');", nomeAluno, telefoneAluno, emailAluno, rgAluno);
            res = mysql_query(&conexao,query);
            if (!res)
                printf("Cadastrado com Sucesso!! \n");
            else
                printf("Erro na insersao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            mysql_close(&conexao);
        } else {
            printf("Falha de conexao\n");
            printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
        }
        system("pause");
        menuOpcao();

        break;
    }
    case 3: {
        MYSQL conexao;
        int res, esco = 2;
        char query[100];
        char nomeConvidado[31], rgConvidado[12], emailConvidado[65], numeroConvite[16], telefoneConvidado[21];
        do {
            printf("Informe seu nome completo: ");
            scanf(" %[^\n]s", &nomeConvidado);
            fflush(stdin);

            printf("Informe seu RG: ");
            scanf(" %s", &rgConvidado);
            fflush(stdin);

            printf("Informe seu telefone com DDD: ");
            scanf(" %s", &telefoneConvidado);
            fflush(stdin);

            printf("Informe seu E-mail: ");
            scanf(" %s", &emailConvidado);
            fflush(stdin);
            system("cls");

            printf("\n Nome: %s", &nomeConvidado);
            printf("\n RG: %s", &rgConvidado);
            printf("\n Telefone:%s", &telefoneConvidado);
            printf("\n Email: %s", &emailConvidado);

            printf(" \n As Informacoes acima estao corretas? \n \n 1 - sim\n 2 - nao \n ");
            scanf("%i",&esco);
            system("cls");
        } while(esco == 2);
        //conexao com o banco //
        mysql_init(&conexao);
        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
            sprintf(query,"call cadas_convidado ('%s','%s','%s','%s');", nomeConvidado, rgConvidado, emailConvidado, telefoneConvidado);
            res = mysql_query(&conexao,query);
            if (!res)
                printf("Cadastrado com Sucesso!! \n");
            else
                printf("Erro na insersao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            mysql_close(&conexao);
        } else {
            printf("Falha de conexao\n");
            printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
        }
        system("pause");


        break;
        break;
    }
    case 4: {
        MYSQL conexao;
        int res, esco = 2;
        char query[100];
        char nomePessoa[31], rgPessoa[12], emailPessoa[65], numeroPd[16], telefonePessoa[21];
        do {
            printf("Informe seu nome completo: ");
            scanf(" %[^\n]s", &nomePessoa);
            fflush(stdin);

            printf("Informe seu RG: ");
            scanf(" %s", &rgPessoa);
            fflush(stdin);

            printf("Informe seu telefone com DDD: ");
            scanf(" %s", &telefonePessoa);
            fflush(stdin);

            printf("Informe seu E-mail: ");
            scanf(" %s", &emailPessoa);
            fflush(stdin);
            system("cls");

            printf("\n Nome: %s", &nomePessoa);
            printf("\n RG: %s", &rgPessoa);
            printf("\n Telefone:%s", &telefonePessoa);
            printf("\n Email: %s", &emailPessoa);
            printf(" \n As Informacoes acima estao corretas? \n \n 1 - sim\n 2 - nao \n");
            scanf("%i",&esco);
            system("cls");
        } while(esco == 2);
        // -------- Conexao -------- //
        mysql_init(&conexao);
        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
            sprintf(query,"call cadas_usu ('%s','%s','%s','%s');", nomePessoa, telefonePessoa, emailPessoa, rgPessoa);
            res = mysql_query(&conexao,query);
            if (!res)
                printf("Cadastrado com Sucesso!! \n");
            else
                printf("Erro na insercao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            mysql_close(&conexao);
        } else {
            printf("Falha de conexao\n");
            printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
        }
        system("pause");

        break;
    }
    default:
        printf("Digite uma opcao valida \n \n");
        system("pause");
        break;
    }




    return (0);
}

void ticket() {
    int rg, tipoPessoa;
    MYSQL_RES *result;
    MYSQL_ROW rows;
    int num_fields;
    char query[150];
    MYSQL conexao;

    printf("voce e: \n \n1 - Professor \n2 - Convidado \n3 - Aluno \n4 - PNE:\n");
    scanf("%i",&tipoPessoa);
    system("cls");

    switch (tipoPessoa) {

    case 1:
    case 3:
    case 4:

        printf("Digite o seu rg:");
        scanf("%i",&rg);
        system("cls");



        mysql_init(&conexao);
        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) )
        {


            sprintf(query, "select nome,lugar_x,lugar_y from tb_usuarios where rg = '%i';",rg);// busca nome e o lugar do usuario atraves do rg.



            mysql_query(&conexao, query);


            result = mysql_use_result(&conexao);


            num_fields = mysql_num_fields(result);

            printf("\n|     NOME     |    Linha    |   Coluna    |  \n");
            while ((rows = mysql_fetch_row(result))) { // Imprime  nome e o lugar do usuario.
                for( int i = 0; i < num_fields; i++) {

                    printf(" %s        ", rows[i] ? rows[i] : NULL );
                }
            }


            mysql_close(&conexao);
            printf(" \n \nData:12/12/18  Hora: 14:30 \n \n");
            system("pause");
        }

        break;

    case 2:
        printf("Digite o seu rg:");
        scanf("%i",&rg);
        system("cls");



        mysql_init(&conexao);
        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) )
        {


            sprintf(query, "select tb_convidado_nome,lugar_x,lugar_y from tb_convidado where tb_convidado_rg = '%i';",rg);



            mysql_query(&conexao, query);


            result = mysql_use_result(&conexao);


            num_fields = mysql_num_fields(result);

            printf("\n|     NOME     |    Linha    |   Coluna    |  \n");
            while ((rows = mysql_fetch_row(result))) {
                for( int i = 0; i < num_fields; i++) {

                    printf(" %s        ", rows[i] ? rows[i] : NULL );
                }
            }


            mysql_close(&conexao);
            printf(" \n \nData:12/12/18  Hora: 14:30 \n \n");
            system("pause");
        }

        break;
    default:
        printf("Digite uma opcao valida \n \n");
        system("pause");
        break;
    }

}

//reserva a cadeira no teatro
int reservarProfessores(char matriz[2][10], int rg,int tipoPessoa) {
    MYSQL conexao;
    MYSQL_RES *result;
    MYSQL_ROW rows;
    int i, num_fields, res;
    char query[150];
    int row, col;
    int iden, tipo;

    iden = rg;
    tipo = tipoPessoa;

    printf("\n\n         RESERVA DE CADEIRAS\n\n");
    row =linhaX();
    col = colunaY();


    if(matriz[row][col]=='.' ) {// Muda o valor do vetor que esta "." para "R"
        matriz[row][col] = 'R';
        system("cls");

        system("cls");

        if (tipo == 2) { // se for convidado os dados seram armazenados na tabela convidado

            mysql_init(&conexao);

            if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
                sprintf(query,"UPDATE tb_convidado SET lugar_x='%i', lugar_y='%i' where tb_convidado_rg = '%i';",row,col,rg); // armazena no cadastro do usuario o lugar q ele escolheu
                res = mysql_query(&conexao,query);
                if (!res)
                    printf("\n\n      RESERVA EFETIVADA COM SUCESSO !!\n \n");
                else
                    printf("Erro na insersao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
                mysql_close(&conexao);
            } else {
                printf("Falha de conexao\n");
                printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            }

            system("pause");
        }

        else {

            mysql_init(&conexao); // se for pne, aluno ou professor os dados seram armazenados na tabela usuarios.

            if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
                sprintf(query,"UPDATE tb_usuarios SET lugar_x='%i', lugar_y='%i' where rg = '%i';",row,col,rg);
                res = mysql_query(&conexao,query);
                if (!res)
                    printf("\n\n      RESERVA EFETIVADA COM SUCESSO !!\n \n");
                else
                    printf("Erro na insersao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
                mysql_close(&conexao);
            } else {
                printf("Falha de conexao\n");
                printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            }

            system("pause");
        }


    }

    else if(matriz[row][col]=='R') { // se o valor da matriz foir "R" sera exibido a seguinte menssagem.
        printf("\n\n      CADEIRA JA RESERVADA !! ESCOLHA OUTRA !!\n\n");
    }



    return 0 ;
}
int reservaAluno(char matriz[8][10], int rg) {
    int iden;
    int row, col;
    printf("\n\n         RESERVA DE CADEIRAS\n\n");
    row =linhaX();
    col = colunaY();;

    iden = rg;

    if(matriz[row][col]=='.' || matriz[row][col]=='p') { // Muda o valor do vetor que esta "." ou "p" para "R"
        matriz[row][col] = 'R';
        system("cls");

        printf("\n\n      RESERVA EFETIVADA COM SUCESSO !! \n \n");
        system("cls");
        MYSQL conexao;
        MYSQL_RES *result;
        MYSQL_ROW rows;
        int i, num_fields, res;
        char query[150];
        mysql_init(&conexao);

        if ( mysql_real_connect(&conexao, "localhost", "root", "", "teatro", 0, NULL, 0) ) {
            sprintf(query,"UPDATE tb_usuarios SET lugar_x='%i', lugar_y='%i' where rg = '%i';",row,col,rg); // armazena no cadastro do usuario o lugar q ele escolheu
            res = mysql_query(&conexao,query);
            if (!res)
                printf("\n\n      RESERVA EFETIVADA COM SUCESSO !!\n \n");
            else
                printf("Erro na insersao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            mysql_close(&conexao);
        } else {
            printf("Falha de conexao\n");
            printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
        }


    }

    else if(matriz[row][col]=='R')
        printf("\n\n      CADEIRA JA RESERVADA !! ESCOLHA OUTRA !!\n\n");
    system("pause");

}
//ler a linha oferecida pelo usuario
int linhaX() {
    int row;
    printf("          Linha: ");
    scanf("%i",&row);
    if(row>10)
    {
        printf("\t\n Esta cadeira nao existe!!! ");
    }
    return row;
}
//ler  coluna oferecida pelo usuario
int colunaY() {
    int col;
    printf("          Coluna: ");
    scanf("%i",&col);
    if(col>10)
    {
        printf("\t\n Esta cadeira nao existe!!! ");
    }
    return col;
}
