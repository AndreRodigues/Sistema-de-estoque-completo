#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Cadastro
{
    char nome[50],senha[50];
};


FILE *arquivo_de_cadastro;
FILE *arquivo_de_login;

void menu();
void cadastrar_usuario();
int checar_cadastros(char user[50]);
void menu_ou_sair();

int main(){

        setlocale(LC_ALL,"Portuguese");

        arquivo_de_cadastro = fopen("cadastros.txt","ab");
        arquivo_de_login = fopen("login.txt", "ab");

        fclose(arquivo_de_cadastro);
        fclose(arquivo_de_login);

        menu();

    return 0;
}

void menu(){

    int opcao;

    printf("| SISTEMA DE ESTOQUE ARCLINE |\n");
    printf("|____________________________|\n");
    printf("| DIGITE 1 PARA SE CADASTRAR |");
    printf("\n|____________________________|\n| DIGITE AQUI: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        cadastrar_usuario();
        break;

    default:
        system("cls");
        printf("|OPÇÃO INVALIDA,DIGITE NOVAMENTE|\n|                            |\n");
        menu();
        break;
        }
}

void cadastrar_usuario(){

    struct Cadastro c;

    char usuario[50],senha[16];
    int x;
                
      
                do{
                    system("cls");
                    printf("CADASTRO ARCLINE\n\n");
                    if(x == 1){
                        printf("USUARIO JA CADASTRADO, DIGITE NOVAMENTE\n");
                    }
                printf("CASO DESEJE RETORNAR AO MENU, DIGITE 'menu', PARA SAIR, DIGITE 'sair'\n\n");

                getchar();
                printf("USUARIO: ");
                scanf("%[^\n]s", usuario);

                if(strcmp(usuario,"menu")== 0){
                    system("cls");
                    menu();
                }

                if (strcmp(usuario, "sair") == 0)
                {
                    system("cls");
                    printf("SISTEMA ENCERRADO\n\n");
                    exit(0);
                }

                x = checar_cadastros(usuario);

                }while(x == 1);
              
                getchar();
                printf("SENHA: ");
                scanf("%[^\n]s", senha);
                getchar();

                if (strcmp(senha, "menu") == 0)
                {
                    system("cls");
                    menu();
                }

                if (strcmp(senha, "sair") == 0)
                {
                    system("cls");
                    printf("SISTEMA ENCERRADO\n\n");
                    exit(0);
                }

                strcpy(c.nome,usuario);
                strcpy(c.senha,senha);

                arquivo_de_cadastro = fopen("cadastros.txt", "ab");

                fwrite(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);

                fclose(arquivo_de_cadastro);

                printf("CADASTRO EFETUADO COM SUCESSO\n\n");

                menu_ou_sair();
}

int checar_cadastros(char user[50]){

    arquivo_de_cadastro = fopen("cadastros.txt", "rb");

    struct Cadastro c;

    fread(&c, sizeof(struct Cadastro),1,arquivo_de_cadastro);

    do{
        
        if(strcmp(c.nome,user)==0){
            return 1;
        }

        fread(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);
    }while(!feof(arquivo_de_cadastro));

    fclose(arquivo_de_cadastro);

    return 2;
}

void menu_ou_sair(){

    int op;

        printf("DIGITE 1 PARA VOLTAR AO MENU\nDIGITE 2 PARA SAIR\n\nDIGITE AQUI: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                system("cls");
                menu();
            break;

            case 2:
                system("cls");
                printf("SISTEMA ENCERRADO\n\n");
                exit(0);
            break;
            

            default:
                system("cls");
                printf("OPÇÃO INVALIDA, DIGITE NOVAMENTE ABAIXO\n\n");
                menu_ou_sair();
                
                break;
        }

}