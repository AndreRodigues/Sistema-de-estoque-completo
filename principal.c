#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <windows.h>

struct Cadastro
{
    char nome[50],senha[50];
};

struct Produtos{

    char nome[100],descricao[100],marca[50];
    float valor_de_compra,valor_de_venda;
    int codigo,qtd;

};


FILE *arquivo_de_cadastro;
FILE *arquivo_de_alteracao;
FILE *arquivo_de_cadastro_de_produtos;
FILE *arquivo_de_consultar_estoque;
FILE *arquivo_de_alterar_produtos;

void menu();//menu inicial do sistema
void menu_principal();//menu principal do sistema
void cadastrar_usuario();//cadastra novos usuarios
void login();//faz o login de usuarios já cadastrados
int checar_login(char user[50],char pass[16]);//chaca se o login exixte
int checar_cadastros(char user[50]);//checa se o cadastros exiete
void menu_ou_sair();//menu de opão de retornar ao menu inicial do sistema ou sair do mesmo
void alterar_senha();
void cadastro_de_produtos();
int checar_produtos(int codigo);
void consultar_estoque();
void menu_principal_ou_sair();
void alterar_produto();
void apagar_produto();
void fim_de_estoque();
void sainda_de_produtos();
void entrada_de_produtos();

    int main()
{

    setlocale(LC_ALL, "Portuguese");

    arquivo_de_cadastro = fopen("cadastros.txt", "ab");

    fclose(arquivo_de_cadastro);

    //acima cria o arquivo caso seja a primeira vez que o sistema será usado

    menu(); //chama o procedimento de menu inicia do sistema

    return 0;
}

void menu(){

    int opcao;

    printf("| SISTEMA DE ESTOQUE ARCLINE   |\n");
    printf("|______________________________|\n");
    printf("| DIGITE 1 PARA SE CADASTRAR   |\n");
    printf("| DIGITE 2 PARA FAZER LOGIN    |\n");
    printf("| DIGITE 3 PARA RECUPERAR CONTA|\n");
    printf("| DIGITE 4 PARA SAIR           |");
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
    case 4:
        system("cls");
        printf("SISTEMA ENCERRADO\n\n");
        exit(0);
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

    printf("| SISTEMA DE ESTOQUE ARCLINE    |\n");
    printf("|____________________________   |\n");
    printf("| DIGITE 1 CADASTRAR PRODUTOS   |\n");
    printf("| DIGITE 2 ENTRADA DE PRODUTOS  |\n");
    printf("| DIGITE 3 SAIDA DE PRODUTOS    |\n");
    printf("| DIGITE 4 CONSULTAR ESTOQUE    |\n");
    printf("| DIGITE 5 PARA SAIR DO SISTEMA |");
    printf("\n|_______________________________|\n| DIGITE AQUI: ");
    scanf("%d", &opcao);

        switch(opcao){
            
            case 1:
                cadastro_de_produtos();
                break;
            case 2:
                entrada_de_produtos();
                break;
            case 3:
                sainda_de_produtos();
                break;
                case 4:
                consultar_estoque();
                break;
            case 5:system("cls");
                printf("SISTEMA ENCERRADO\n\n");
                exit(0);
                
                break;

            default:
                system("cls");
                printf("OPÇÃO INVALIDA, DIGITE NOVAMENTE\n\n");
                menu_principal();
            break;
        }
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

void cadastro_de_produtos(){

    struct Produtos p;

        float preco_sugerido,pc,pv;
        int opcao,flag, x,cod,qtd;
        char nome[100],desc[100],marca[50];

            arquivo_de_cadastro_de_produtos = fopen("produtos.txt","ab");

            fclose(arquivo_de_cadastro_de_produtos);

        do{
            //getchar();
            system("cls");

            printf("CADASTRO DE PRODUTOS\n\n");
            printf("CASO DESEJE VOLTAR AO MENU, DIGITE 'menu' em qualque campo\n\n");
            do{

                if(x==2){
                    system("cls");

                    printf("CADASTRO DE PRODUTOS\n\n");
                    printf("CASO DESEJE VOLTAR AO MENU, DIGITE 'menu' em qualque campo\n\n");
                    printf("CODIGO JÁ PERTENCE A OUTRO PRODUTO, DIGITE NOVAMENTE ABAIXO\n\n");
                }
            printf("CODIGO DO PRODUTO: ");
            scanf("%d", &cod);
            
                
                x = checar_produtos(cod);

            }while(x == 2);

            flag = 2;

            getchar();
            printf("NOME DO PRODUTODO: ");
            scanf("%[^\n]s", nome);
            getchar();
            printf("MARCA DE %s: ", nome);
            scanf("%[^\n]s", marca);
            getchar();
            printf("DRECRIÇÃO DO %s: ", nome);
            scanf("%[^\n]s", desc);
            getchar();
            printf("VALOR DE COMPRA DE %s: ", nome);
            scanf("%f", &pc);
            getchar();
            printf("QAUNTIDADE DE %s: ",nome);
            scanf("%d", &qtd);
            getchar();

            preco_sugerido = ((pc * 2) + (pc * 0.15));

            printf("PREÇO SUGERIDO PARA %s : %.2f\n\n", nome, preco_sugerido);

            printf("PREÇO DE VENDA DE %s: ", nome);
            scanf("%f", &pv);
            getchar();

            strcpy(p.nome,nome);
            strcpy(p.marca,marca);
            strcpy(p.descricao,desc);
            p.valor_de_compra = pc;
            p.valor_de_venda = pv;
            p.qtd = qtd;
            p.codigo = cod;

            arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "ab");

            fwrite(&p, sizeof(struct Produtos),1,arquivo_de_cadastro_de_produtos);

            fclose(arquivo_de_cadastro_de_produtos);

            system("cls");
            printf("PRODUTO CADASTRADO COM SUCESSO\n\n");
            do
            {
                
                if (flag == 1)
                {
                    system("cls");
                    printf("OPÇÃO INVALIDA, DIGITE NOVAMENTE\n\n");
                }

                printf("DIGITE 1 PARA CADASTRAR OUTRO PRODUTO\nDIGITE 2 PARA VOLTAR AO MENU ANTERIOR\n\n");
                printf("DIGITE AQUI: ");
                scanf("%d", &opcao);

                flag = 1;

        }while(opcao < 1 || opcao > 2);

        }while(opcao == 1);

            

            menu_principal();
}

int checar_produtos(int codigo){

    struct Produtos p;

    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "rb");

    fread(&p, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);

    do
    {

        if (p.codigo == codigo)
        {

            fclose(arquivo_de_cadastro_de_produtos);

            return 2;
        }

        fread(&p, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
    } while (!feof(arquivo_de_cadastro_de_produtos));

    fclose(arquivo_de_cadastro_de_produtos);

    return 1;
    
    
}

void consultar_estoque(){
        
        struct Produtos p;

        int op,opcao,codigo,flag;

        system("cls");

        arquivo_de_consultar_estoque = fopen("produtos.txt","rb");

        do{

            if(flag == 1){
                system("cls");
                printf("OPÇÃO INVALDIA, DIGITE NOVAMENTE ABAIXO\n\n");
            }

        printf("DIGITE 1 PROCURAR PRODUTO ESPECIFICO\nDIGITE 2 PARA LISTAR TODOS OS PRODUTOS");
        printf("\nDIGITE 3 PARA ALTERAR PRODUTO\nDIGITE 4 PARA APAGAR ALGUM PRODUTO\nDIGITE 5 PARA VER PRODUTOS EM FIM DE ESTOQUE");
        printf("\nDIGITE 6 PARA VOLTAR AO MENU ANTERIOR");
        printf("\n\nDIGITE AQUI: ");
        scanf("%d", &op);

        flag = 1;

        }while(op < 1 || op > 6);

        if(op == 1){

            system("cls");
            printf("ESTOQUE ARCLINE\n\n");
            printf("CODIGO DO PRODUTO QUE DESEJA CONSULTAR: ");
            scanf("%d", &codigo);

            fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

            do
            {

                    if(p.codigo == codigo){
                        system("cls");
                        printf("\n\nCODIGO DO PRODUTO: %d", p.codigo);
                        printf("\nNOME DO PRODUTO: %s", p.nome);
                        printf("\nMARCA DO PRODUTO: %s", p.marca);
                        printf("\nDESCRIÇÃO DO PRODUTO: %s", p.descricao);
                        printf("\nVALOR DE COMPRA DO PRODUTO: %.2f", p.valor_de_compra);
                        printf("\nVALOR DE VENDA DO PRODUTO: %.2f", p.valor_de_venda);
                        printf("\nQUANTIDADE DISPONIVEL DO PRODUTO: %d\n\n", p.qtd);

                        fclose(arquivo_de_consultar_estoque);

                        menu_principal_ou_sair();
                    }


                fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

            } while (!feof(arquivo_de_consultar_estoque));

        }else if(op == 2){

            system("cls");

            printf("PRODUTOS CADASTRADOS NO ESTOQUE ARCLINE\n\n");

        fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

        do{

            printf("CODIGO DO PRODUTO: %d", p.codigo);
            printf("\nNOME DO PRODUTO: %s", p.nome);
            printf("\nMARCA DO PRODUTO: %s", p.marca);
            printf("\nDESCRIÇÃO DO PRODUTO: %s", p.descricao);
            printf("\nVALOR DE COMPRA DO PRODUTO: %.2f", p.valor_de_compra);
            printf("\nVALOR DE VENDA DO PRODUTO: %.2f", p.valor_de_venda);
            printf("\nQUANTIDADE DISPONIVeL DO PRODUTO: %d\n\n", p.qtd);

            fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

        }while(!feof(arquivo_de_consultar_estoque));
            
            fclose(arquivo_de_consultar_estoque);

            menu_principal_ou_sair();
        }else if(op == 3){
            alterar_produto();
        }
        else if (op == 4)
        {
            apagar_produto();
        }
        else if (op == 5)
        {
            fim_de_estoque();
        }
        else if (op == 6)
        {
            menu_principal();
        }
}

void menu_principal_ou_sair(){

        int op,flag;

        do{
            if(flag == 1){
                system("cls");
                printf("OPÇÃO INVALIDA, DIGITE NOVAMENTE ABAIXO\n\n");
            }
 
        printf("DIGITE 1 PARA VOLTAR PARA O MENU PRINCIPAL\nDIGITE 2 PARA SAIR DO SISTEMA\n\nDIGITE AQUI: ");
        scanf("%d", &op);

        if(op == 1){
            menu_principal();
        }else if(op == 2){
            system("cls");
            printf("SISTEMA ENCERRADO\n\n");
            exit(0);
        }

        flag = 1;

        }while(op < 1 || op > 2);

}

void alterar_produto(){

    struct Produtos l;
    struct Produtos e;
    int codigo,x = 3,qtd;
    char nome[100],descricao[100],marca[50];
    float pc,pv,ps;

    
    do
    {
        system("cls");
        printf("ALTERAÇÃO DE PRODUTOS ARCLINE\n\n");

         if(x==1){
            printf("PRODUTO NÃO ENCONTRADO\n");
        }

        printf("CASO DESEJE RETORNAR AO MENU DIGITE 'menu' CASO DESEJE SAIR, DIGITE 'sair'\n\n");

        printf("CODIGO: ");
        scanf("%d", &codigo);
        

        x = checar_produtos(codigo);

    } while (x == 1);

    getchar();
    printf("NOME DO PRODUTODO: ");
    scanf("%[^\n]s", nome);
    getchar();
    printf("MARCA DE %s: ", nome);
    scanf("%[^\n]s", marca);
    getchar();
    printf("DRECRIÇÃO DO %s: ", nome);
    scanf("%[^\n]s", descricao);
    getchar();
    printf("VALOR DE COMPRA DE %s: ", nome);
    scanf("%f", &pc);
    getchar();
    printf("QAUNTIDADE DE %s: ", nome);
    scanf("%d", &qtd);
    getchar();

    ps = ((pc * 2) + (pc * 0.15));

    printf("PREÇO SUGERIDO PARA %s : %.2f\n\n", nome, ps);

    printf("PREÇO DE VENDA DE %s: ", nome);
    scanf("%f", &pv);
    getchar();

    

    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "rb");
    arquivo_de_alterar_produtos = fopen("produtos02.txt", "wb");
    //fclose(arquivo_de_alteracao);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);

    do
    {
        // arquivo_de_alteracao = fopen("rer.txt", "ab");
        if (l.codigo == codigo)
        {

            strcpy(e.nome, nome);
            strcpy(e.marca, marca);
            strcpy(e.descricao, descricao);
            e.valor_de_compra = pc;
            e.valor_de_venda = pv;
            e.qtd = qtd;
            e.codigo = codigo;
        }
        else
        {
            strcpy(e.nome, l.nome);
            strcpy(e.marca, l.marca);
            strcpy(e.descricao, l.descricao);
            e.valor_de_compra = l.valor_de_compra;
            e.valor_de_venda = l.valor_de_compra;
            e.qtd = l.qtd;
            e.codigo = l.codigo;
        }

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        //fclose(arquivo_de_alteracao);

    } while (!feof(arquivo_de_cadastro_de_produtos));

    fclose(arquivo_de_alterar_produtos);
    fclose(arquivo_de_cadastro_de_produtos);

    arquivo_de_alterar_produtos = fopen("produtos02.txt", "rb");
    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "wb");
    // fclose(arquivo_de_cadastro);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

    do
    {
        //arquivo_de_cadastro = fopen("cadastros.txt", "ab");
        strcpy(e.nome, l.nome);
        strcpy(e.marca, l.marca);
        strcpy(e.descricao, l.descricao);
        e.valor_de_compra = l.valor_de_compra;
        e.valor_de_venda = l.valor_de_compra;
        e.qtd = l.qtd;
        e.codigo = l.codigo;

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

        //fclose(arquivo_de_cadastro);
    } while (!feof(arquivo_de_alterar_produtos));

    fclose(arquivo_de_cadastro_de_produtos);
    fclose(arquivo_de_alterar_produtos);

    system("cls");
    printf("ALTERAÇÃO DE PRODUTO REALIZADA COM SUCESSO\n\n");

    menu_principal_ou_sair();
}

void apagar_produto(){
   
    struct Produtos l;
    struct Produtos e;
    int codigo, x = 3, qtd,a,b,opp;
   
    
    do
    {
        system("cls");
        printf("APAGAR PRODUTOS ARCLINE\n\n");

        if (x == 1)
        {
            printf("PRODUTO NÃO ENCONTRADO\n");
        }

        printf("CASO DESEJE RETORNAR AO MENU DIGITE 'menu' CASO DESEJE SAIR, DIGITE 'sair'\n\n");

        printf("CODIGO: ");
        scanf("%d", &codigo);

        x = checar_produtos(codigo);

    } while (x == 1);

    
    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "rb");
    arquivo_de_alterar_produtos = fopen("produtos02.txt", "wb");
    //fclose(arquivo_de_alteracao);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);

    do
    {
        // arquivo_de_alteracao = fopen("rer.txt", "ab");
        if (l.codigo == codigo)
        {

            
           
        }
        else
        {
            strcpy(e.nome, l.nome);
            strcpy(e.marca, l.marca);
            strcpy(e.descricao, l.descricao);
            e.valor_de_compra = l.valor_de_compra;
            e.valor_de_venda = l.valor_de_compra;
            e.qtd = l.qtd;
            e.codigo = l.codigo;

            fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);
        }

        
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        //fclose(arquivo_de_alteracao);


    } while (!feof(arquivo_de_cadastro_de_produtos));

    fclose(arquivo_de_alterar_produtos);
    fclose(arquivo_de_cadastro_de_produtos);

    arquivo_de_alterar_produtos = fopen("produtos02.txt", "rb");
    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "wb");
    // fclose(arquivo_de_cadastro);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

    do
    {
        //arquivo_de_cadastro = fopen("cadastros.txt", "ab");
        strcpy(e.nome, l.nome);
        strcpy(e.marca, l.marca);
        strcpy(e.descricao, l.descricao);
        e.valor_de_compra = l.valor_de_compra;
        e.valor_de_venda = l.valor_de_compra;
        e.qtd = l.qtd;
        e.codigo = l.codigo;

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

        //fclose(arquivo_de_cadastro);
    } while (!feof(arquivo_de_alterar_produtos));

    fclose(arquivo_de_cadastro_de_produtos);
    fclose(arquivo_de_alterar_produtos);

    system("cls");
    printf("PRODUTO APAGADO COM SUCESSO REALIZADA COM SUCESSO\n\n");

    menu_principal_ou_sair();
}

void fim_de_estoque(){

    struct Produtos p;

    system("cls");
    printf("PRODUTOS EM FIM DE ESTOQUE\n\n");

    arquivo_de_consultar_estoque = fopen("produtos.txt","rb");

    fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

    do
    {

        if (p.qtd <= 10)
        {
            
            printf("\nCODIGO DO PRODUTO: %d", p.codigo);
            printf("\nNOME DO PRODUTO: %s", p.nome);
            printf("\nMARCA DO PRODUTO: %s", p.marca);
            printf("\nDESCRIÇÃO DO PRODUTO: %s", p.descricao);
            printf("\nVALOR DE COMPRA DO PRODUTO: %.2f", p.valor_de_compra);
            printf("\nVALOR DE VENDA DO PRODUTO: %.2f", p.valor_de_venda);
            printf("\nQUANTIDADE DISPONIVEL DO PRODUTO: %d\n\n", p.qtd);

            
        }

        fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

    } while (!feof(arquivo_de_consultar_estoque));
    
        fclose(arquivo_de_consultar_estoque);

            menu_principal_ou_sair();
}

void sainda_de_produtos(){

    struct Produtos l;
    struct Produtos e;
    struct Produtos p;
    int codigo,x = 3,qtd,quant,opp;
    char nome[100],descricao[100],marca[50];
    float pc,pv,ps;

    do{
    
    do
    {
        system("cls");
        printf("SAIDA DE PRODUTOS ARCLINE\n\n");

         if(x==1){
            printf("PRODUTO NÃO ENCONTRADO\n");
        }

        printf("CASO DESEJE RETORNAR AO MENU DIGITE 'menu' CASO DESEJE SAIR, DIGITE 'sair'\n\n");

        printf("CODIGO: ");
        scanf("%d", &codigo);
        

        x = checar_produtos(codigo);

    } while (x == 1);

    arquivo_de_consultar_estoque = fopen("produtos.txt","r");

    fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

    do
    {

        if (p.codigo == codigo)
        {
            
            printf("\nCODIGO DO PRODUTO: %d", p.codigo);
            printf("\nNOME DO PRODUTO: %s", p.nome);
            printf("\nMARCA DO PRODUTO: %s", p.marca);
            printf("\nDESCRIÇÃO DO PRODUTO: %s", p.descricao);
            printf("\nVALOR DE COMPRA DO PRODUTO: %.2f", p.valor_de_compra);
            printf("\nVALOR DE VENDA DO PRODUTO: %.2f", p.valor_de_venda);
            printf("\nQUANTIDADE DISPONIVEL DO PRODUTO: %d\n\n", p.qtd);

            
        }

        fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

    } while (!feof(arquivo_de_consultar_estoque));
    
        fclose(arquivo_de_consultar_estoque);


    printf("\n\nDIGITE A QUANTIDADE DE RETIRADA DESSE PRODUTO: "); 
    scanf("%d",&quant);

    

    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "rb");
    arquivo_de_alterar_produtos = fopen("produtos02.txt", "wb");
    //fclose(arquivo_de_alteracao);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);

    do
    {
        // arquivo_de_alteracao = fopen("rer.txt", "ab");
        if (l.codigo == codigo)
        {

            strcpy(e.nome, l.nome);
            strcpy(e.marca, l.marca);
            strcpy(e.descricao, l.descricao);
            e.valor_de_compra = l.valor_de_compra;
            e.valor_de_venda = l.valor_de_venda;
            e.qtd = l.qtd - quant;
            e.codigo = codigo;

            if(e.qtd < 0){
                printf("QUANTIDADE DE PRODUTO INDISPONIVAL NO ESTOQUE\nDIGITE NOVAMENTE EM INSTANTES");
                Sleep(3000);
                sainda_de_produtos();
            }
        }
        else
        {
            strcpy(e.nome, l.nome);
            strcpy(e.marca, l.marca);
            strcpy(e.descricao, l.descricao);
            e.valor_de_compra = l.valor_de_compra;
            e.valor_de_venda = l.valor_de_compra;
            e.qtd = l.qtd;
            e.codigo = l.codigo;
        }

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        //fclose(arquivo_de_alteracao);

    } while (!feof(arquivo_de_cadastro_de_produtos));

    fclose(arquivo_de_alterar_produtos);
    fclose(arquivo_de_cadastro_de_produtos);

    arquivo_de_alterar_produtos = fopen("produtos02.txt", "rb");
    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "wb");
    // fclose(arquivo_de_cadastro);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

    do
    {
        //arquivo_de_cadastro = fopen("cadastros.txt", "ab");
        strcpy(e.nome, l.nome);
        strcpy(e.marca, l.marca);
        strcpy(e.descricao, l.descricao);
        e.valor_de_compra = l.valor_de_compra;
        e.valor_de_venda = l.valor_de_compra;
        e.qtd = l.qtd;
        e.codigo = l.codigo;

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

        //fclose(arquivo_de_cadastro);
    } while (!feof(arquivo_de_alterar_produtos));

    fclose(arquivo_de_cadastro_de_produtos);
    fclose(arquivo_de_alterar_produtos);

    system("cls");
    printf("RETIRADA EFETUADA COM SUCESSO\n\n");

    printf("DIGITE 1 PARA RETIRAR OUTRO PRODUTO\nDIGITE 2 PARA VOLTAR AO MENU\n\nDIGITE AQUI: ");
    scanf("%d", &opp);

    }while(opp == 1);

    menu_principal();


}

void entrada_de_produtos(){

    struct Produtos l;
    struct Produtos e;
    struct Produtos p;
    int codigo,x = 3,qtd,quant,opp;
    char nome[100],descricao[100],marca[50];
    float pc,pv,ps;

    do{
    
    do
    {
        system("cls");
        printf("ENTRADA DE PRODUTOS ARCLINE\n\n");

         if(x==1){
            printf("PRODUTO NÃO ENCONTRADO\n");
        }

        printf("CASO DESEJE RETORNAR AO MENU DIGITE 'menu' CASO DESEJE SAIR, DIGITE 'sair'\n\n");

        printf("CODIGO: ");
        scanf("%d", &codigo);
        

        x = checar_produtos(codigo);

    } while (x == 1);

    arquivo_de_consultar_estoque = fopen("produtos.txt","r");

    fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

    do
    {

        if (p.codigo == codigo)
        {
            
            printf("\nCODIGO DO PRODUTO: %d", p.codigo);
            printf("\nNOME DO PRODUTO: %s", p.nome);
            printf("\nMARCA DO PRODUTO: %s", p.marca);
            printf("\nDESCRIÇÃO DO PRODUTO: %s", p.descricao);
            printf("\nVALOR DE COMPRA DO PRODUTO: %.2f", p.valor_de_compra);
            printf("\nVALOR DE VENDA DO PRODUTO: %.2f", p.valor_de_venda);
            printf("\nQUANTIDADE DISPONIVEL DO PRODUTO: %d\n\n", p.qtd);

            
        }

        fread(&p, sizeof(struct Produtos), 1, arquivo_de_consultar_estoque);

    } while (!feof(arquivo_de_consultar_estoque));
    
        fclose(arquivo_de_consultar_estoque);

    printf("\n\nDIGITE A QUANTIDADE A SER ADICIONADA DESSE PRODUTO: "); 
    scanf("%d",&quant);

    

    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "rb");
    arquivo_de_alterar_produtos = fopen("produtos02.txt", "wb");
    //fclose(arquivo_de_alteracao);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);

    do
    {
        // arquivo_de_alteracao = fopen("rer.txt", "ab");
        if (l.codigo == codigo)
        {

            strcpy(e.nome, l.nome);
            strcpy(e.marca, l.marca);
            strcpy(e.descricao, l.descricao);
            e.valor_de_compra = l.valor_de_compra;
            e.valor_de_venda = l.valor_de_venda;
            e.qtd = l.qtd + quant;
            e.codigo = codigo;

            if(e.qtd < 0){
                printf("QUANTIDADE DE PRODUTO INDISPONIVAL NO ESTOQUE\nDIGITE NOVAMENTE EM INSTANTES");
                Sleep(3000);
                sainda_de_produtos();
            }
        }
        else
        {
            strcpy(e.nome, l.nome);
            strcpy(e.marca, l.marca);
            strcpy(e.descricao, l.descricao);
            e.valor_de_compra = l.valor_de_compra;
            e.valor_de_venda = l.valor_de_compra;
            e.qtd = l.qtd;
            e.codigo = l.codigo;
        }

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        //fclose(arquivo_de_alteracao);

    } while (!feof(arquivo_de_cadastro_de_produtos));

    fclose(arquivo_de_alterar_produtos);
    fclose(arquivo_de_cadastro_de_produtos);

    arquivo_de_alterar_produtos = fopen("produtos02.txt", "rb");
    arquivo_de_cadastro_de_produtos = fopen("produtos.txt", "wb");
    // fclose(arquivo_de_cadastro);

    fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

    do
    {
        //arquivo_de_cadastro = fopen("cadastros.txt", "ab");
        strcpy(e.nome, l.nome);
        strcpy(e.marca, l.marca);
        strcpy(e.descricao, l.descricao);
        e.valor_de_compra = l.valor_de_compra;
        e.valor_de_venda = l.valor_de_compra;
        e.qtd = l.qtd;
        e.codigo = l.codigo;

        fwrite(&e, sizeof(struct Produtos), 1, arquivo_de_cadastro_de_produtos);
        fread(&l, sizeof(struct Produtos), 1, arquivo_de_alterar_produtos);

        //fclose(arquivo_de_cadastro);
    } while (!feof(arquivo_de_alterar_produtos));

    fclose(arquivo_de_cadastro_de_produtos);
    fclose(arquivo_de_alterar_produtos);

    system("cls");
    printf("ADIÇÃO EFETUADA COM SUCESSO\n\n");

    printf("DIGITE 1 PARA RETIRAR OUTRO PRODUTO\nDIGITE 2 PARA VOLTAR AO MENU\n\nDIGITE AQUI: ");
    scanf("%d", &opp);

    }while(opp == 1);

    menu_principal();


}

