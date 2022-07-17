#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#define MAXDEP 20
#define MAXFUNC 1000

//definindo structs
typedef struct{
    int codigo;
    char nome[70];
    char sigla[10];
}cadDep;

typedef struct{
    int matricula;
    char nome[70];
    int dataNasc[3];
    int cpf[11];
    float salario;
    int codigoDep;
}cadFunc;
//fim structs

//subrotinas secundarias e pesquisas
int verificarNumerosIguais(int *cpf,int numero,int i){//fun��o para verificar se todos os n�meros do vetor CPF s�o iguais, e caso for, retorna erro
    int igual;

    igual = 0;
    for(i = 0;i<11;i++){
        if(cpf[i] == numero)
            igual++;
    }
    if(igual == 11)
        return 1;

    return -1;
}

int validarCPF(char *cpf){
    int i = 0,cpfint[11],somador=0,resultado1,resultado2,digito1,digito2;

    for(i = 0;i<11;i++){    //convertendo cpf para inteiro
        cpfint[i] = cpf[i]-48;
    }


    if(verificarNumerosIguais(cpfint,0,i)==1) //verificando se todos os n�meros s�o iguais, pois estes casos passam na verifica��o de CPF, mas s�o invalidos
        return 1;

    if(verificarNumerosIguais(cpfint,1,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,2,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,3,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,4,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,5,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,6,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,7,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,8,i)==1)
        return 1;

    if(verificarNumerosIguais(cpfint,9,i)==1)
        return 1;


    for(i=0;i<9;i++){
        somador+=cpfint[i]*(10-i); //somando o produto dos 9 primeiros numeros entre 10 a 2(1 digito * 10, 2 digito * 9...)
    }

    resultado1 = somador%11; //calculando o resto da soma por 11

    if(resultado1 == 0 || resultado1 == 1){//caso resultado seja 0 ou 1, o 1 digito verificador sera 0
        digito1 = 0;
    }
    else{
        digito1 = 11-resultado1; //caso n�o seja, o primeiro digito validador � o resultado - 11
    }

    somador = 0; //zerando o somador para calcular o 2 digito

    for(i=0;i<10;i++){
        somador+=cpfint[i]*(11-i); //somando o produto dos 9 primeiros numeros entre 11 a 3
    }

    resultado2=somador%11;   //calculando resto da soma por 11

    if(resultado2==0 || resultado2==1){ //caso o resto seja 0 ou 1, o 2 digito verificador sera 0
        digito2=0;
    }
    else{
        digito2=11-resultado2;  //caso nao seja, sera 11 - resultado
    }

    if((digito1==cpfint[9]) && (digito2==cpfint[10])){
        return -1;  //
    }

    return 1;

}

int validarDataNasc(int *dataNasc){
    if(dataNasc[1] < 1 || dataNasc[1] > 12 || dataNasc[0] < 1 || dataNasc[0] > 31 || dataNasc[2] < 1900 || dataNasc[2] > 2021){
        return 1;   //caso o mes n estiver entre 1 e 12 ou se o dia n estiver entre 1 e 31 ou se o ano for menor que 1900 e maior que 2021,retorna erro
    }

    switch(dataNasc[1]){
        case 4:;
        case 6:;
        case 9:;
        case 11:
            if(dataNasc[0] < 1 || dataNasc[0] > 30) //se o dia n estiver entre 0 ou 30 nos meses 4,6,9,11,volta erro
                return 1;
        break;
        case 2:
            if(((dataNasc[2]%4 == 0)&&(dataNasc[2]% 100 != 0)) || (dataNasc[2]% 400 == 0)){ //verificando se � ano bissexto e se o dia entrado � valido
                if(dataNasc[0] < 1 || dataNasc[0] > 29)                                     //caso seja ou n�o ano bissexto
                    return 1;
            }
            else{
                if(dataNasc[0] < 1 || dataNasc[0] > 28)
                    return 1;
            }
        break;
    }
    return -1;
}

int verificaVazio(char *s){
    if(isspace(s[0])!= 0){  //fun��o que verifica se o primeiro char de nome � um espa�o e caso seja, retorna erro
        return 1;
    }
    return -1;
}

void retiraEnter(char *s){  //fun��o para retirar enter dos nomes
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

int pesqDep(int cdg,int ultimaPosDep,cadDep *vetDepartamento){  //fun��o para pesquisar em qual posi��o est� o c�digo que o usu�rio digitou
    for(int i = 0;i <= ultimaPosDep;i++){
        if(vetDepartamento[i].codigo == cdg){
            return i;
        }
    }
    return -1;
}

int pesqFunc(int matricula,int ultimaPosFunc,cadFunc *vetFuncionarios){ //fun��o para pesquisar em qual posi��o est� a matr�cula que o usu�rio digitou
    for(int i = 0;i <= ultimaPosFunc;i++){
        if(vetFuncionarios[i].matricula == matricula){
            return i;
        }
    }
    return -1;
}

//fim subrotinas e pesquisas

//fun�oes principais
void cadastroDep(int *ultimaPosDep,cadDep *vetDepartamento,int tamanho){
    int cdg,sair;

    if(*ultimaPosDep == tamanho-1){
        printf("\nTodos os departamentos ja foram cadastrados!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o c�digo do departamento: ");
            scanf("%d",&cdg);
            if(pesqDep(cdg,*ultimaPosDep,vetDepartamento)== -1){
                (*ultimaPosDep)++;
                vetDepartamento[*ultimaPosDep].codigo = cdg;
                printf("\nDigite o nome do departamento: ");
                setbuf(stdin,NULL);
                fgets(vetDepartamento[*ultimaPosDep].nome,70,stdin);
                setbuf(stdin,NULL);
                while(verificaVazio(vetDepartamento[*ultimaPosDep].nome)==1){ //enquanto o nome for algo vazio n�o sair� do loop
                    printf("\n\nN�o � permitido nome vazio ou com espa�o no in�cio!!\nDigite um nome v�lido: ");
                    setbuf(stdin,NULL);
                    fgets(vetDepartamento[*ultimaPosDep].nome,70,stdin);
                    setbuf(stdin,NULL);
                }
                retiraEnter(vetDepartamento[*ultimaPosDep].nome);
                printf("\nDigite a sigla do departamento: ");
                setbuf(stdin,NULL);
                fgets(vetDepartamento[*ultimaPosDep].sigla,10,stdin);
                setbuf(stdin,NULL);
                retiraEnter(vetDepartamento[*ultimaPosDep].sigla);
            }
            else
                printf("\nC�digo j� utilizado!!!\n");

            if(*ultimaPosDep < tamanho-1){
                printf("\nDeseja abandonar o Cadastro de Departamento?\n1 - Sim 2 - N�o ");
                scanf("%d",&sair);
            }

            system("CLS || clear");

        }while(*ultimaPosDep < tamanho-1 && sair != 1);
    }
    system("CLS || clear");
    return;
}

void cadastroFunc(cadFunc *vetFuncionarios,int tamanho,int *ultimaPosFunc,int ultimaPosDep,cadDep *vetDepartamento){
    int matricula,sair,posicao;
    char cpf[11];
    if(ultimaPosDep == -1){
        printf("\nNenhum departamento cadastrado!!\n\n");
        system("Pause");
        system("ClS || clear");
        return;
    }

    if(*ultimaPosFunc == tamanho-1){
        printf("\nTodos funcion�rios cadastrados!!\n\n");
        system("Pause");
        system("CLS || clear");
        return;
    }

    do{
        printf("\nDigite o n�mero da matr�cula: ");
        scanf("%d",&matricula);
        if(pesqFunc(matricula,*ultimaPosFunc,vetFuncionarios)== -1){
            (*ultimaPosFunc)++;
            vetFuncionarios[*ultimaPosFunc].matricula = matricula;
            printf("\nDigite seu nome: ");
            setbuf(stdin,NULL);
            fgets(vetFuncionarios[*ultimaPosFunc].nome,70,stdin);
            setbuf(stdin,NULL);
            while(verificaVazio(vetFuncionarios[*ultimaPosFunc].nome)==1){
                printf("\n\nN�o � permitido nome vazio ou com espa�o no in�cio!!\nDigite um nome v�lido: ");
                setbuf(stdin,NULL);
                fgets(vetFuncionarios[*ultimaPosFunc].nome,70,stdin);
                setbuf(stdin,NULL);
            }
            retiraEnter(vetFuncionarios[*ultimaPosFunc].nome);
            setbuf(stdin,NULL);
            printf("\nDigite sua data de nascimento: dd mm yy\n");
            scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[0]);
            scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[1]);
            scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[2]);
            while(validarDataNasc(vetFuncionarios[*ultimaPosFunc].dataNasc)==1){//enquanto n�o for uma data v�lida, n�o sair� do loop
                printf("\nData inv�lida!!! Digite uma data v�lida: dd mm yy\n");
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[0]);
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[1]);
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[2]);
            }
            printf("\nDigite o seu CPF: ");
            scanf("%s",cpf);
            while(validarCPF(cpf)==1){  //enquanto cpf n for valido n saira do loop
                printf("\nCPF inv�lido!!! Digite um CPF v�lido: ");
                scanf("%s",cpf);
            }
            for(int i = 0;i<11;i++){ //convertendo cpf para inteiro e atribuindo ao campo cpf da struct
                vetFuncionarios[*ultimaPosFunc].cpf[i] = cpf[i]-48;
            }

            printf("\nDigite o valor do seu sal�rio em reais\nR$: ");
            scanf("%f",&vetFuncionarios[*ultimaPosFunc].salario);
            while(vetFuncionarios[*ultimaPosFunc].salario <= 0){    //enquanto salario for menor que zero n saira do loop
                printf("\nSal�rio deve ser maior que 0!!\nR$: ");
                scanf("%f",&vetFuncionarios[*ultimaPosFunc].salario);
            }
            do{
                printf("\nDepartamentos cadastrados\n");
                for(int i = 0;i<=ultimaPosDep;i++){
                    printf("\n%d - %s\n",vetDepartamento[i].codigo,vetDepartamento[i].nome);
                }
                printf("\n\nDigite o c�digo do seu departamento: ");
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].codigoDep);

                posicao = pesqDep(vetFuncionarios[*ultimaPosFunc].codigoDep,ultimaPosDep,vetDepartamento);
                if(posicao == -1){
                    printf("\nC�digo de curso inexistente!!!\n");
                }

            }while(posicao == -1);
        }
        else{
            printf("\n\nMatr�cula j� existente!!\n");
        }

        if(*ultimaPosFunc < tamanho -1){
            printf("\nDeseja sair do Cadastro de Funcion�rios?\n1 - Sim 2 - N�o ");
            scanf("%d",&sair);
        }
        else{
            printf("\nTodos funcion�rios j� cadastrados!!! Abandonando Cadastro de Funcion�rios...\n\n");
            system("Pause");
        }
        system("CLS || clear");

    }while(*ultimaPosFunc < tamanho -1 && sair!= 1);

    system("CLS || clear");
    return;
}

void consultaNome(cadFunc *vetFuncionarios,int ultimaPosFunc,cadDep *vetDepartamento,int ultimaPosDep){
    int sair,posicaoDep,achou;
    char nome[70];
    if(ultimaPosFunc == -1){
        printf("\nNenhum funcion�rio cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o nome que deseja procurar: ");
            setbuf(stdin,NULL);
            fgets(nome,70,stdin);
            setbuf(stdin,NULL);
            while(verificaVazio(nome)==1){
                printf("\n\nN�o � permitido nome vazio ou com espa�o no in�cio!!\nDigite um nome v�lido: ");
                setbuf(stdin,NULL);
                fgets(nome,70,stdin);
                setbuf(stdin,NULL);
            }
            retiraEnter(nome);
            achou = 0;
            for(int i = 0;i<=ultimaPosFunc;i++){
                if(strcmp(nome,vetFuncionarios[i].nome)==0){//comparando o nome que usuario digitou com nomes de funcionarios
                    printf("\nDados do funcion�rio %s\n",nome);
                    printf("\nMatr�cula = %d",vetFuncionarios[i].matricula);
                    printf("\nNome = %s",vetFuncionarios[i].nome);
                    printf("\nData de Nascimento = %d/%d/%d",vetFuncionarios[i].dataNasc[0],vetFuncionarios[i].dataNasc[1],vetFuncionarios[i].dataNasc[2]);
                    printf("\nCPF = ");
                    for(int s = 0;s<11;s++){
                        printf("%d",vetFuncionarios[i].cpf[s]);
                    }
                    printf("\nSal�rio = R$%.2f",vetFuncionarios[i].salario);
                    posicaoDep = pesqDep(vetFuncionarios[i].codigoDep,ultimaPosDep,vetDepartamento);
                    printf("\nNome e C�digo de Departamento = %s - %d",vetDepartamento[posicaoDep].nome,vetFuncionarios[i].codigoDep);
                    achou = 1;
                }
                else{
                    if(i == ultimaPosFunc && achou == 0){
                        printf("\nNome n�o encontrado!!!\n");
                    }
                }
            }

            printf("\n\nDeseja sair da Consulta de Funcion�rio por Nome?\n1 - Sim 2 - N�o ");
            scanf("%d",&sair);

            system("CLS || clear");

        }while(sair != 1);
    }
    system("CLS || clear");
    return;
}

void consultaMat(cadFunc *vetFuncionarios,int ultimaPosFunc,cadDep *vetDepartamento,int ultimaPosDep){
    int mat,sair,posicaoDep,posFunc;
    if(ultimaPosFunc == -1){
        printf("\nNenhum funcion�rio cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("Digite o n�mero de matr�cula para consulta: ");
            scanf("%d",&mat);
            posFunc = pesqFunc(mat,ultimaPosFunc,vetFuncionarios);

            if(posFunc == -1){
                printf("\nMatr�cula n�o encontrada!!!!\n");
            }
            else{
                printf("\nDados do funcion�rio %s\n",vetFuncionarios[posFunc].nome);
                printf("\nMatr�cula = %d",vetFuncionarios[posFunc].matricula);
                printf("\nNome = %s",vetFuncionarios[posFunc].nome);
                printf("\nData de Nascimento = %d/%d/%d",vetFuncionarios[posFunc].dataNasc[0],vetFuncionarios[posFunc].dataNasc[1],vetFuncionarios[posFunc].dataNasc[2]);
                printf("\nCPF = ");
                for(int s = 0;s<11;s++){
                    printf("%d",vetFuncionarios[posFunc].cpf[s]);
                }
                printf("\nSal�rio = R$%.2f",vetFuncionarios[posFunc].salario);
                posicaoDep = pesqDep(vetFuncionarios[posFunc].codigoDep,ultimaPosDep,vetDepartamento);
                printf("\nNome e C�digo de Departamento = %s - %d",vetDepartamento[posicaoDep].nome,vetFuncionarios[posFunc].codigoDep);
            }

            printf("\n\nDeseja sair da Consulta por Matr�cula?\n1 - Sim 2 - N�o ");
            scanf("%d",&sair);

            system("CLS || clear");

        }while(sair != 1);


    }
    system("CLS || clear");
    return;
}

void funcionariosDep(cadDep *vetDepartamento,cadFunc *vetFuncionarios,int ultimaPosFunc,int ultimaPosDep){
    int cdg,sair,posDep;

    if(ultimaPosDep == -1){
        printf("\nNenhum departamento cadastrado!!\n\n");
        system("Pause");
    }
    if(ultimaPosFunc == -1){
        printf("\nNenhum funcion�rio cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o c�digo do departamento para listagem de funcion�rios: ");
            scanf("%d",&cdg);
            posDep = pesqDep(cdg,ultimaPosDep,vetDepartamento);
            if(posDep == -1){
                printf("\nC�digo de Departamento n�o encontrado!!!");
            }
            else{
                printf("\nFuncion�rios do Departamento %s",vetDepartamento[posDep].nome);
                for(int i = 0;i<=ultimaPosFunc;i++){
                    if(vetFuncionarios[i].codigoDep == cdg){ //verificando se os funcionarios tem o codigo digitado pelo usuario
                        printf("\n\nMatr�cula = %d",vetFuncionarios[i].matricula);
                        printf("\nNome = %s",vetFuncionarios[i].nome);
                        printf("\nData de Nascimento = %d/%d/%d",vetFuncionarios[i].dataNasc[0],vetFuncionarios[i].dataNasc[1],vetFuncionarios[i].dataNasc[2]);
                        printf("\nCPF = ");
                        for(int s = 0;s<11;s++){
                            printf("%d",vetFuncionarios[i].cpf[s]);
                        }
                        printf("\nSal�rio = R$%.2f",vetFuncionarios[i].salario);
                        printf("\nNome e C�digo de Departamento = %s - %d",vetDepartamento[posDep].nome,vetFuncionarios[i].codigoDep);
                    }
                }
            }

            printf("\n\nDeseja sair da Consulta de Funcion�rios por Departamento?\n1 - Sim 2 - N�o ");
            scanf("%d",&sair);

            system("CLS || clear");

        }while(sair != 1);
    }
    system("CLS || clear");
    return;
}

void excluirFunc(cadFunc *vetFuncionarios,int *ultimaPosFunc){
    int mat,posFunc,sair;
    if(*ultimaPosFunc == -1){
        printf("\nNenhum funcion�rio cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite a matr�cula do funcion�rio que deseja excluir: ");
            scanf("%d",&mat);
            posFunc = pesqFunc(mat,*ultimaPosFunc,vetFuncionarios);

            if(posFunc == -1){
                printf("\n\nMatr�cula n�o encontrada!!\n");
            }
            else{
                if(posFunc == *ultimaPosFunc){ //caso a posi��o que o usu�rio deseja excluir for igual a ultima posi��o, simplesmente a ultima posi��o
                    (*ultimaPosFunc)--;        //� decrementada, pois n�o h� posi��es sucessoras para efetuar a c�pia de um campo para o outro
                }
                else{
                    vetFuncionarios[posFunc] = vetFuncionarios[*ultimaPosFunc]; //caso nao seja a ultima ou primeira posi��o, � copiado a ultima posi��o
                    (*ultimaPosFunc)--;                                         //para o campo que est� sendo exclu�do
                }
                printf("\nFuncion�rio exclu�do com sucesso!!\n");
            }

            if(*ultimaPosFunc != -1){
                printf("\n\nDeseja sair da Exclus�o de Funcion�rios?\n1 - Sim 2 - N�o ");
                scanf("%d",&sair);
            }
            else{
                printf("\n\nN�o h� mais funcion�rios no sistema, saindo da Exclus�o de Funcion�rios...\n\n");
                system("Pause");
            }

            system("ClS || clear");
        }while(sair != 1 && *ultimaPosFunc != -1);
    }
    system("ClS || clear");
    return;
}

void excluirDep(cadDep *vetDepartamento,cadFunc *vetFuncionarios,int *ultimaPosDep,int *ultimaPosFunc){
    int sair,cdg,posDep;

    if(*ultimaPosDep == -1){
        printf("\nNenhum Departamento Cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o c�digo do departamento que deseja excluir: ");
            scanf("%d",&cdg);
            posDep = pesqDep(cdg,*ultimaPosDep,vetDepartamento);

            if(posDep == -1){
                printf("\nC�digo n�o encontrado!!\n");
            }
            else{
                if(posDep == *ultimaPosDep){    //Excluindo departamento
                    (*ultimaPosDep)--;
                }
                else{
                    vetDepartamento[posDep] = vetDepartamento[*ultimaPosDep];
                    (*ultimaPosDep)--;
                }

                for(int i = 0;i<=*ultimaPosFunc;i++){   //Excluindo Funcion�rio do departamento
                    if(vetFuncionarios[i].codigoDep == cdg){
                        if(i == *ultimaPosFunc){
                            (*ultimaPosFunc)--;
                        }
                        else{
                            vetFuncionarios[i] = vetFuncionarios[*ultimaPosFunc];
                            (*ultimaPosFunc)--;
                        }
                    }
                }

                printf("\nDepartamento e funcion�rios desse departamento exclu�dos com sucesso!!\n");
            }

            if(*ultimaPosDep != -1){
                printf("\n\nDeseja sair da Exclus�o de Departamento?\n1 - Sim 2 - N�o ");
                scanf("%d",&sair);
            }
            else{
                printf("\n\nN�o h� mais departamentos registrados... Saindo da Exclus�o de Departamento!!\n\n");
                system("Pause");
            }

            system("CLS || clear");
        }while(sair != 1 && *ultimaPosDep != -1);
    }

    system("CLS || clear");
    return;
}


int main(){
    int opcao,ultimaPosDep = -1,ultimaPosFunc = -1;
    cadDep vetDepartamento[MAXDEP];
    cadFunc vetFuncionarios[MAXFUNC];
    setlocale(LC_ALL,"");

    do{
        printf("1 - Cadastro de Departamento\n2 - Cadastro de Funcion�rios\n3 - Consulta de Funcion�rios por Nome\n4 - Consulta de Funcion�rio por Matr�cula\n");
        printf("5 - Funcion�rios de um Departamento\n6 - Excluir Funcion�rio\n7 - Excluir Departamento\n8 - Sair");
        printf("\n\nEscolha sua op��o: ");
        scanf("%d",&opcao);
        while(opcao < 1 || opcao > 8){  //validando a opcao de entrada
            printf("Valor inv�lido!!! Insira um valor v�lido: ");
            scanf("%d",&opcao);
        }

        system("CLS || clear");

        switch(opcao){
            case 1:
                cadastroDep(&ultimaPosDep,vetDepartamento,MAXDEP);
            break;

            case 2:
                cadastroFunc(vetFuncionarios,MAXFUNC,&ultimaPosFunc,ultimaPosDep,vetDepartamento);
            break;

            case 3:
                consultaNome(vetFuncionarios,ultimaPosFunc,vetDepartamento,ultimaPosDep);
            break;

            case 4:
                consultaMat(vetFuncionarios,ultimaPosFunc,vetDepartamento,ultimaPosDep);
            break;

            case 5:
                funcionariosDep(vetDepartamento,vetFuncionarios,ultimaPosFunc,ultimaPosDep);
            break;

            case 6:
                excluirFunc(vetFuncionarios,&ultimaPosFunc);
            break;

            case 7:
                excluirDep(vetDepartamento,vetFuncionarios,&ultimaPosDep,&ultimaPosFunc);
            break;
        }

    }while(opcao != 8);

    return 0;
}
