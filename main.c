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
int verificarNumerosIguais(int *cpf,int numero,int i){//função para verificar se todos os números do vetor CPF são iguais, e caso for, retorna erro
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


    if(verificarNumerosIguais(cpfint,0,i)==1) //verificando se todos os números são iguais, pois estes casos passam na verificação de CPF, mas são invalidos
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
        digito1 = 11-resultado1; //caso não seja, o primeiro digito validador é o resultado - 11
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
            if(((dataNasc[2]%4 == 0)&&(dataNasc[2]% 100 != 0)) || (dataNasc[2]% 400 == 0)){ //verificando se é ano bissexto e se o dia entrado é valido
                if(dataNasc[0] < 1 || dataNasc[0] > 29)                                     //caso seja ou não ano bissexto
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
    if(isspace(s[0])!= 0){  //função que verifica se o primeiro char de nome é um espaço e caso seja, retorna erro
        return 1;
    }
    return -1;
}

void retiraEnter(char *s){  //função para retirar enter dos nomes
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

int pesqDep(int cdg,int ultimaPosDep,cadDep *vetDepartamento){  //função para pesquisar em qual posição está o código que o usuário digitou
    for(int i = 0;i <= ultimaPosDep;i++){
        if(vetDepartamento[i].codigo == cdg){
            return i;
        }
    }
    return -1;
}

int pesqFunc(int matricula,int ultimaPosFunc,cadFunc *vetFuncionarios){ //função para pesquisar em qual posição está a matrícula que o usuário digitou
    for(int i = 0;i <= ultimaPosFunc;i++){
        if(vetFuncionarios[i].matricula == matricula){
            return i;
        }
    }
    return -1;
}

//fim subrotinas e pesquisas

//funçoes principais
void cadastroDep(int *ultimaPosDep,cadDep *vetDepartamento,int tamanho){
    int cdg,sair;

    if(*ultimaPosDep == tamanho-1){
        printf("\nTodos os departamentos ja foram cadastrados!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o código do departamento: ");
            scanf("%d",&cdg);
            if(pesqDep(cdg,*ultimaPosDep,vetDepartamento)== -1){
                (*ultimaPosDep)++;
                vetDepartamento[*ultimaPosDep].codigo = cdg;
                printf("\nDigite o nome do departamento: ");
                setbuf(stdin,NULL);
                fgets(vetDepartamento[*ultimaPosDep].nome,70,stdin);
                setbuf(stdin,NULL);
                while(verificaVazio(vetDepartamento[*ultimaPosDep].nome)==1){ //enquanto o nome for algo vazio não sairá do loop
                    printf("\n\nNão é permitido nome vazio ou com espaço no início!!\nDigite um nome válido: ");
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
                printf("\nCódigo já utilizado!!!\n");

            if(*ultimaPosDep < tamanho-1){
                printf("\nDeseja abandonar o Cadastro de Departamento?\n1 - Sim 2 - Não ");
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
        printf("\nTodos funcionários cadastrados!!\n\n");
        system("Pause");
        system("CLS || clear");
        return;
    }

    do{
        printf("\nDigite o número da matrícula: ");
        scanf("%d",&matricula);
        if(pesqFunc(matricula,*ultimaPosFunc,vetFuncionarios)== -1){
            (*ultimaPosFunc)++;
            vetFuncionarios[*ultimaPosFunc].matricula = matricula;
            printf("\nDigite seu nome: ");
            setbuf(stdin,NULL);
            fgets(vetFuncionarios[*ultimaPosFunc].nome,70,stdin);
            setbuf(stdin,NULL);
            while(verificaVazio(vetFuncionarios[*ultimaPosFunc].nome)==1){
                printf("\n\nNão é permitido nome vazio ou com espaço no início!!\nDigite um nome válido: ");
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
            while(validarDataNasc(vetFuncionarios[*ultimaPosFunc].dataNasc)==1){//enquanto não for uma data válida, não sairá do loop
                printf("\nData inválida!!! Digite uma data válida: dd mm yy\n");
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[0]);
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[1]);
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].dataNasc[2]);
            }
            printf("\nDigite o seu CPF: ");
            scanf("%s",cpf);
            while(validarCPF(cpf)==1){  //enquanto cpf n for valido n saira do loop
                printf("\nCPF inválido!!! Digite um CPF válido: ");
                scanf("%s",cpf);
            }
            for(int i = 0;i<11;i++){ //convertendo cpf para inteiro e atribuindo ao campo cpf da struct
                vetFuncionarios[*ultimaPosFunc].cpf[i] = cpf[i]-48;
            }

            printf("\nDigite o valor do seu salário em reais\nR$: ");
            scanf("%f",&vetFuncionarios[*ultimaPosFunc].salario);
            while(vetFuncionarios[*ultimaPosFunc].salario <= 0){    //enquanto salario for menor que zero n saira do loop
                printf("\nSalário deve ser maior que 0!!\nR$: ");
                scanf("%f",&vetFuncionarios[*ultimaPosFunc].salario);
            }
            do{
                printf("\nDepartamentos cadastrados\n");
                for(int i = 0;i<=ultimaPosDep;i++){
                    printf("\n%d - %s\n",vetDepartamento[i].codigo,vetDepartamento[i].nome);
                }
                printf("\n\nDigite o código do seu departamento: ");
                scanf("%d",&vetFuncionarios[*ultimaPosFunc].codigoDep);

                posicao = pesqDep(vetFuncionarios[*ultimaPosFunc].codigoDep,ultimaPosDep,vetDepartamento);
                if(posicao == -1){
                    printf("\nCódigo de curso inexistente!!!\n");
                }

            }while(posicao == -1);
        }
        else{
            printf("\n\nMatrícula já existente!!\n");
        }

        if(*ultimaPosFunc < tamanho -1){
            printf("\nDeseja sair do Cadastro de Funcionários?\n1 - Sim 2 - Não ");
            scanf("%d",&sair);
        }
        else{
            printf("\nTodos funcionários já cadastrados!!! Abandonando Cadastro de Funcionários...\n\n");
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
        printf("\nNenhum funcionário cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o nome que deseja procurar: ");
            setbuf(stdin,NULL);
            fgets(nome,70,stdin);
            setbuf(stdin,NULL);
            while(verificaVazio(nome)==1){
                printf("\n\nNão é permitido nome vazio ou com espaço no início!!\nDigite um nome válido: ");
                setbuf(stdin,NULL);
                fgets(nome,70,stdin);
                setbuf(stdin,NULL);
            }
            retiraEnter(nome);
            achou = 0;
            for(int i = 0;i<=ultimaPosFunc;i++){
                if(strcmp(nome,vetFuncionarios[i].nome)==0){//comparando o nome que usuario digitou com nomes de funcionarios
                    printf("\nDados do funcionário %s\n",nome);
                    printf("\nMatrícula = %d",vetFuncionarios[i].matricula);
                    printf("\nNome = %s",vetFuncionarios[i].nome);
                    printf("\nData de Nascimento = %d/%d/%d",vetFuncionarios[i].dataNasc[0],vetFuncionarios[i].dataNasc[1],vetFuncionarios[i].dataNasc[2]);
                    printf("\nCPF = ");
                    for(int s = 0;s<11;s++){
                        printf("%d",vetFuncionarios[i].cpf[s]);
                    }
                    printf("\nSalário = R$%.2f",vetFuncionarios[i].salario);
                    posicaoDep = pesqDep(vetFuncionarios[i].codigoDep,ultimaPosDep,vetDepartamento);
                    printf("\nNome e Código de Departamento = %s - %d",vetDepartamento[posicaoDep].nome,vetFuncionarios[i].codigoDep);
                    achou = 1;
                }
                else{
                    if(i == ultimaPosFunc && achou == 0){
                        printf("\nNome não encontrado!!!\n");
                    }
                }
            }

            printf("\n\nDeseja sair da Consulta de Funcionário por Nome?\n1 - Sim 2 - Não ");
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
        printf("\nNenhum funcionário cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("Digite o número de matrícula para consulta: ");
            scanf("%d",&mat);
            posFunc = pesqFunc(mat,ultimaPosFunc,vetFuncionarios);

            if(posFunc == -1){
                printf("\nMatrícula não encontrada!!!!\n");
            }
            else{
                printf("\nDados do funcionário %s\n",vetFuncionarios[posFunc].nome);
                printf("\nMatrícula = %d",vetFuncionarios[posFunc].matricula);
                printf("\nNome = %s",vetFuncionarios[posFunc].nome);
                printf("\nData de Nascimento = %d/%d/%d",vetFuncionarios[posFunc].dataNasc[0],vetFuncionarios[posFunc].dataNasc[1],vetFuncionarios[posFunc].dataNasc[2]);
                printf("\nCPF = ");
                for(int s = 0;s<11;s++){
                    printf("%d",vetFuncionarios[posFunc].cpf[s]);
                }
                printf("\nSalário = R$%.2f",vetFuncionarios[posFunc].salario);
                posicaoDep = pesqDep(vetFuncionarios[posFunc].codigoDep,ultimaPosDep,vetDepartamento);
                printf("\nNome e Código de Departamento = %s - %d",vetDepartamento[posicaoDep].nome,vetFuncionarios[posFunc].codigoDep);
            }

            printf("\n\nDeseja sair da Consulta por Matrícula?\n1 - Sim 2 - Não ");
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
        printf("\nNenhum funcionário cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite o código do departamento para listagem de funcionários: ");
            scanf("%d",&cdg);
            posDep = pesqDep(cdg,ultimaPosDep,vetDepartamento);
            if(posDep == -1){
                printf("\nCódigo de Departamento não encontrado!!!");
            }
            else{
                printf("\nFuncionários do Departamento %s",vetDepartamento[posDep].nome);
                for(int i = 0;i<=ultimaPosFunc;i++){
                    if(vetFuncionarios[i].codigoDep == cdg){ //verificando se os funcionarios tem o codigo digitado pelo usuario
                        printf("\n\nMatrícula = %d",vetFuncionarios[i].matricula);
                        printf("\nNome = %s",vetFuncionarios[i].nome);
                        printf("\nData de Nascimento = %d/%d/%d",vetFuncionarios[i].dataNasc[0],vetFuncionarios[i].dataNasc[1],vetFuncionarios[i].dataNasc[2]);
                        printf("\nCPF = ");
                        for(int s = 0;s<11;s++){
                            printf("%d",vetFuncionarios[i].cpf[s]);
                        }
                        printf("\nSalário = R$%.2f",vetFuncionarios[i].salario);
                        printf("\nNome e Código de Departamento = %s - %d",vetDepartamento[posDep].nome,vetFuncionarios[i].codigoDep);
                    }
                }
            }

            printf("\n\nDeseja sair da Consulta de Funcionários por Departamento?\n1 - Sim 2 - Não ");
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
        printf("\nNenhum funcionário cadastrado!!\n\n");
        system("Pause");
    }
    else{
        do{
            printf("\nDigite a matrícula do funcionário que deseja excluir: ");
            scanf("%d",&mat);
            posFunc = pesqFunc(mat,*ultimaPosFunc,vetFuncionarios);

            if(posFunc == -1){
                printf("\n\nMatrícula não encontrada!!\n");
            }
            else{
                if(posFunc == *ultimaPosFunc){ //caso a posição que o usuário deseja excluir for igual a ultima posição, simplesmente a ultima posição
                    (*ultimaPosFunc)--;        //é decrementada, pois não há posições sucessoras para efetuar a cópia de um campo para o outro
                }
                else{
                    vetFuncionarios[posFunc] = vetFuncionarios[*ultimaPosFunc]; //caso nao seja a ultima ou primeira posição, é copiado a ultima posição
                    (*ultimaPosFunc)--;                                         //para o campo que está sendo excluído
                }
                printf("\nFuncionário excluído com sucesso!!\n");
            }

            if(*ultimaPosFunc != -1){
                printf("\n\nDeseja sair da Exclusão de Funcionários?\n1 - Sim 2 - Não ");
                scanf("%d",&sair);
            }
            else{
                printf("\n\nNão há mais funcionários no sistema, saindo da Exclusão de Funcionários...\n\n");
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
            printf("\nDigite o código do departamento que deseja excluir: ");
            scanf("%d",&cdg);
            posDep = pesqDep(cdg,*ultimaPosDep,vetDepartamento);

            if(posDep == -1){
                printf("\nCódigo não encontrado!!\n");
            }
            else{
                if(posDep == *ultimaPosDep){    //Excluindo departamento
                    (*ultimaPosDep)--;
                }
                else{
                    vetDepartamento[posDep] = vetDepartamento[*ultimaPosDep];
                    (*ultimaPosDep)--;
                }

                for(int i = 0;i<=*ultimaPosFunc;i++){   //Excluindo Funcionário do departamento
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

                printf("\nDepartamento e funcionários desse departamento excluídos com sucesso!!\n");
            }

            if(*ultimaPosDep != -1){
                printf("\n\nDeseja sair da Exclusão de Departamento?\n1 - Sim 2 - Não ");
                scanf("%d",&sair);
            }
            else{
                printf("\n\nNão há mais departamentos registrados... Saindo da Exclusão de Departamento!!\n\n");
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
        printf("1 - Cadastro de Departamento\n2 - Cadastro de Funcionários\n3 - Consulta de Funcionários por Nome\n4 - Consulta de Funcionário por Matrícula\n");
        printf("5 - Funcionários de um Departamento\n6 - Excluir Funcionário\n7 - Excluir Departamento\n8 - Sair");
        printf("\n\nEscolha sua opção: ");
        scanf("%d",&opcao);
        while(opcao < 1 || opcao > 8){  //validando a opcao de entrada
            printf("Valor inválido!!! Insira um valor válido: ");
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
