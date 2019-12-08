#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Cadastro
{
    char nome[50],senha[50];
};


FILE *arquivo_de_cadastro;
FILE *arquivo_de_alteracao;

void menu();//menu inicial do sistema
void menu_principal();//menu principal do sistema
void cadastrar_usuario();//cadastra novos usuarios
void login();//faz o login de usuarios já cadastrados
int checar_login(char user[50],char pass[16]);//chaca se o login exixte
int checar_cadastros(char user[50]);//checa se o cadastros exiete
void menu_ou_sair();//menu de opão de retornar ao menu inicial do sistema ou sair do mesmo
void alterar_senha();

int main(){

        setlocale(LC_ALL,"Portuguese");

        arquivo_de_cadastro = fopen("cadastros.txt","ab");
        

        fclose(arquivo_de_cadastro);
        
        //acima cria o arquivo caso seja a primeira vez que o sistema será usado

        menu();//chama o procedimento de menu inicia do sistema

    return 0;
}

void menu(){

    int opcao;

    printf("| SISTEMA DE ESTOQUE ARCLINE   |\n");
    printf("|______________________________|\n");
    printf("| DIGITE 1 PARA SE CADASTRAR   |\n");
    printf("| DIGITE 2 PARA FAZER LOGIN    |\n");
    printf("| DIGITE 3 PARA RECUPERAR CONTA|");
    printf("\n|______________________________|\n| DIGITE AQUI: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        cadastrar_usuario();
        break;
    case 2:
        login();
        break;
    case 3:
        alterar_senha();
        break;

    default:
        system("cls");
        printf("|OPÇÃO INVALIDA,DIGITE NOVAMENTE|\n|                            |\n");
        menu();
        break;
        }

        //menu inicial do sistema
}

void cadastrar_usuario(){

    struct Cadastro c;

    char usuario[50],senha[16];
    int x;
                
            
                do{//irá repetir esse laço enquanto o usuario digitar um cadastro ja utilizado
                    system("cls");
                    printf("CADASTRO ARCLINE\n\n");
                    if(x == 1){
                        /*caso ele digite um usuario já cadastrado, o 'x' irá retornar o valor de 1
                        e aparecerá a mensagem abaixo*/
                        printf("USUARIO JA CADASTRADO, DIGITE NOVAMENTE\n");
                    }
                printf("CASO DESEJE RETORNAR AO MENU, DIGITE 'menu', PARA SAIR, DIGITE 'sair'\n\n");

                getchar();
                printf("USUARIO: ");
                scanf("%[^\n]s", usuario);
                /*os dois 'if' abaixo irá comparar se o usuario quer voltar ao menu ou 
                sair do sistema*/
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

                /*aqui se chama a função aonde checa se o usuario digitado já está
                cadastrado no sistema*/
                x = checar_cadastros(usuario);

                }while(x == 1);
              
                getchar();
                printf("SENHA: ");
                scanf("%[^\n]s", senha);
                getchar();

                /*os dois 'if' abaixo irá comparar se o usuario quer voltar ao menu ou 
                sair do sistema*/
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
                    /*atricui o usuario e a senha a ser cadastrada, já que foi permitido chegar
                    até aqui, checando os cadasrtros no arquico cadastros.txt*/
                strcpy(c.nome,usuario);
                strcpy(c.senha,senha);

                arquivo_de_cadastro = fopen("cadastros.txt", "ab");

                fwrite(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);

                fclose(arquivo_de_cadastro);

                system("cls");
                printf("CADASTRO EFETUADO COM SUCESSO\n\n");

                menu_ou_sair();
}

int checar_cadastros(char user[50]){


    /*nessa função ele checa se o usuario já esta cadastrado, caso esteja, a função
    retormnará o valor 1 caso contrario retorna o valor 2*/
    arquivo_de_cadastro = fopen("cadastros.txt", "rb");

    struct Cadastro c;

    fread(&c, sizeof(struct Cadastro),1,arquivo_de_cadastro);

    do{
        
        if(strcmp(c.nome,user)==0){

            fclose(arquivo_de_cadastro);

            return 1;
        }
        

        fread(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);
    }while(!feof(arquivo_de_cadastro));

    fclose(arquivo_de_cadastro);

    return 2;
}

void menu_ou_sair(){

    /*menu que pode ser chamado em varios momentos no sistema, no qual tem as opções
    de retornar ao menu ou sair do sistema*/

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

void login(){

    char usuario[50],senha[16];
    int x;
    getchar();
    do{
    system("cls");
    printf("TELA DE LOGIN ARCLINE\n\n");
    if(x==1){
        printf("USUARIO OU SENHA INCORRETOS\n\n");
    }
    
    printf("USUARIO: ");
    scanf("%[^\n]s", usuario);
    getchar();
    printf("\nSENHA: ");
    scanf("%[^\n]s", senha);
    getchar();

    /*chama a função que checa se a senha ou usuarios estão cadastrados e correpondem um ao outro
    e permite ou não o acesso ao menu proncipal do sistema*/

    x = checar_login(usuario,senha);

    }while(x == 1);

    menu_principal();
}

int checar_login(char user[50], char pass[16]){
    

    /*
    Essa função checa se o usuario e a senha digitada pelo usuario correspondem de forma correta,
    se sim retorna o valor 2, caso contrariom retorna o valor 1
    */

    struct Cadastro c;

    arquivo_de_cadastro = fopen("cadastros.txt", "rb");
    
    fread(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);

    do
    {

        if (strcmp(c.nome, user) == 0 && strcmp(c.senha, pass) == 0)
        {
            return 2;
        }

        fread(&c, sizeof(struct Cadastro), 1, arquivo_de_cadastro);
    } while (!feof(arquivo_de_cadastro));

        return 1;
}

void menu_principal(){

    /*procedimento aonde fica o menu principal do sistema, e chama as funcionalidades do mesmo*/

    int opcao;

    system("cls");

    printf("| SISTEMA DE ESTOQUE ARCLINE |\n");
    printf("|____________________________|\n");
    printf("| DIGITE 1 CADASTRAR PRODUTOS|\n");
    printf("| DIGITE 2 SAIDA DE PRODUTOS |");
    printf("\n|____________________________|\n| DIGITE AQUI: ");
    scanf("%d", &opcao);
}

void alterar_senha(){

    struct Cadastro l;
    struct Cadastro e;
    char usuario[50],senha[16];
    int x;

    
   
            getchar();
        do{
        system("cls");
        printf("ALTERAÇÃO DE SENHA ARCLINE\n\n");

       /* if(x==2){
            printf("USUARIO NÃO ENCONTRADO\n");
        }*/

        printf("CASO DESEJE RETORNAR AO MENU DIGITE 'menu' CASO DESEJE SAIR, DIGITE 'sair'\n\n");

        printf("USUARIO: ");
        scanf("%[^\n]s", usuario);
        getchar();

        x = checar_cadastros(usuario);

        }while(x == 2);

        printf("SENHA: ");
        scanf("%[^\n]s", senha);
        getchar();

            arquivo_de_cadastro = fopen("cadastros.txt","rb");
            arquivo_de_alteracao = fopen("rer.txt","wb");
            //fclose(arquivo_de_alteracao);

            fread(&l, sizeof(struct Cadastro),1,arquivo_de_cadastro);

            do{
               // arquivo_de_alteracao = fopen("rer.txt", "ab");
                if(strcmp(l.nome,usuario)==0){
                    
                    strcpy(e.nome,l.nome);
                    strcpy(e.senha,senha);

                    
                }else{
                    strcpy(e.nome, l.nome);
                    strcpy(e.senha, l.senha);
                }

                fwrite(&e, sizeof(struct Cadastro),1,arquivo_de_alteracao);
                fread(&l, sizeof(struct Cadastro), 1, arquivo_de_cadastro);
                //fclose(arquivo_de_alteracao);

            }while(!feof(arquivo_de_cadastro));

            fclose(arquivo_de_alteracao);
            fclose(arquivo_de_cadastro);

            arquivo_de_alteracao = fopen("rer.txt","rb");
            arquivo_de_cadastro = fopen("cadastros.txt","wb");
           // fclose(arquivo_de_cadastro);

            fread(&l,sizeof(struct Cadastro),1,arquivo_de_alteracao);

            do{
                //arquivo_de_cadastro = fopen("cadastros.txt", "ab");
                strcpy(e.nome,l.nome);
                strcpy(e.senha,l.senha);

                fwrite(&e, sizeof(struct Cadastro),1,arquivo_de_cadastro);
                fread(&l, sizeof(struct Cadastro), 1, arquivo_de_alteracao);

                //fclose(arquivo_de_cadastro);
            }while(!feof(arquivo_de_alteracao));            

                fclose(arquivo_de_cadastro);
                fclose(arquivo_de_alteracao);
       
            system("cls");
            printf("ALTERAÇÃO DE SENHA REALIZADA COM SUCESSO\n\n");

            menu_ou_sair();
}
