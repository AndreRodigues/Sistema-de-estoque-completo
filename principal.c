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
int checar_cadastros(char user);

void main(){

        setlocale(LC_ALL,"Portuguese");

        arquivo_de_cadastro = fopen("cadastros.txt","ab");
        arquivo_de_login = fopen("login.txt", "ab");

        fclose(arquivo_de_cadastro);
        fclose(arquivo_de_login);

        menu();

    system("pause");
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

        
        arquivo_de_cadastro = fopen("login.txt", "wb");

            system("cls");

            printf("CADASTRO ARCLINE\n\n");
            printf("CASO DESEJE RETORNAR AO MENU, DIGITE 'menu', PARA SAIR, DIGITE 'sair'\n\n");

            getchar();
            printf("USUARIO: ");
            scanf("%[^\n]s", usuario);
            getchar();

            arquivo_de_cadastro = fopen("cadastros.txt", "rb");

            fread(&c, sizeof(struct Cadastro),1,arquivo_de_cadastro);

            do{

                if (strcmp(c.nome,usuario) == 0)
                {
                    system("cls");
                    printf("USUARIO JÁ CADASTRADO EM NOSSO SISTEMA\nDIGITE NOVAMENTE POR FAVOR\n\n");
                    cadastrar_usuario();
                    
                }else{

                }

                    fread(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);

            }while(!feof(arquivo_de_cadastro));
           
            fclose(arquivo_de_cadastro);
            

            printf("SENHA (ATÉ 16 DIGITOS): ");
            scanf("%[^\n]s", senha);
            getchar();

            strcpy(c.nome,usuario);
            strcpy(c.senha,senha);

            arquivo_de_cadastro = fopen("cadastros.txt", "ab");

            fwrite(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);

            fclose(arquivo_de_cadastro);

            printf("CADASTRO EFETUADO COM SUCESSO");
}




