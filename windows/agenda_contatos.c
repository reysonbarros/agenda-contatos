#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <windows.h> 
#include <locale.h>
#include <time.h>

enum meses_do_ano {
	Janeiro = 1, 
	Fevereiro, 
	Marco, 
	Abril, 
	Maio, 
	Junho,
	Julho, 
	Agosto, 
	Setembro, 
	Outubro, 
	Novembro, 
	Dezembro
}mes;

struct telefone {
	unsigned int ddd;
	unsigned int numero;
};

struct data {
	unsigned short dia;
	unsigned short mes;
};

struct contato {
    unsigned short id;
	unsigned char nome[128];
	struct telefone celular;
	struct data aniversario;	
};
 
int  exibirMenu(void);
void adicionarContato(void);
void consultarContato(char tipo[]);
void alterarContato(void);
void excluirContato(void);
void listarContatos(void);
void aniversariantesMes(void);
boolean existeContato(unsigned short id);
int compare(const void * a, const void * b);
int numeroLinhasArquivo(void);
void consultarContatoPorId(unsigned short id);

 
int main(void)
{
	setlocale(LC_ALL, "portuguese");	
    int opcao;    
 
    do
    {
        opcao = exibirMenu();
 
        switch (opcao)
        {
        case 1:
            adicionarContato();
            break;
        case 2:
            consultarContato("nome");
            break;
        case 3:
            alterarContato();
            break;
        case 4:
            excluirContato();
            break;
        case 5:
            listarContatos();
            break; 			
        case 6:
            consultarContato("inicial");
            break; 			    
        case 7:
            aniversariantesMes();
            break; 			        
        case 8:
        	printf("\n Encerrando...");
            break;                               
        default:
            printf("\n Opção inválida!");
        }
        Sleep(1000); 
    } while (opcao != 8);
 
    return 0;
}
 
int exibirMenu(void)
{
    int opcao;
 
    system("cls");
 
    printf("\tAGENDA DE CONTATOS \n\n");
    printf(" 1. Cadastrar Contato\n");
    printf(" 2. Consultar Contato\n");
    printf(" 3. Alterar Contato\n");
    printf(" 4. Excluir Contato\n");    
    printf(" 5. Listar Contatos\n");    
    printf(" 6. Consultar Contato por Inicial do Nome\n");
    printf(" 7. Aniversariantes do Mês\n");
    printf(" 8. Sair\n\n");    
    printf(" Digite a opção desejada: ");
    scanf("%d", &opcao);
 
    return opcao;
}
 
void adicionarContato(void)
{	
	unsigned short id;
    struct contato meuContato;
    FILE *arquivo;
 
    system("cls");
 
    printf("\tAGENDA DE CONTATOS - CADASTRAR CONTATO\n\n");
    
	printf(" Código Identificador:");    	
    scanf("%d",&meuContato.id);
	
	printf(" Nome Completo:");
    fflush(stdin);        
    gets(meuContato.nome);   
    
	printf(" Telefone/Celular\n");
	printf(" DDD:");    
    scanf("%d",&meuContato.celular.ddd);
    printf(" Número:");
    scanf("%d",&meuContato.celular.numero);
    
    printf(" Aniversário\n");    
    printf(" Dia:");        
    scanf("%d",&meuContato.aniversario.dia);        
    printf(" Mês:");    
    fflush(stdin);        
    scanf("%d",&meuContato.aniversario.mes);    
 
    arquivo = fopen("agenda.txt", "ab");
    if (!arquivo)
    {
        arquivo = fopen("agenda.txt", "wb");
    }
 	
 	if (existeContato(meuContato.id))
	{
		printf(" Contato já existente! Informar um novo código identificador.");
		
	}else{	
		
		fwrite(&meuContato, 1, sizeof(struct contato), arquivo);
		printf(" Contato cadastrado com sucesso!");	
		
	}   
 	Sleep(5000);
    fclose(arquivo);    
	    
    listarContatos();
    
}
 
void consultarContato(char tipo[])
{
    int encontrado = 0;
    char busca[128];
    char *text;
    struct contato meuContato;
    FILE *arquivo;	
 
    system("cls"); 
 
    printf("\tAGENDA DE CONTATOS - BUSCAR CONTATO\n\n"); 
    
    if (strcmp(tipo, "nome") == 0){    
    	printf(" Nome do contato: ");
	}else{
		printf(" Letra Inicial do contato: ");
	}
    
    fflush(stdin);
    gets(busca);
 
    arquivo = fopen("agenda.txt", "rb");
 
    if (arquivo)
    {
        fread(&meuContato, 1, sizeof(struct contato), arquivo);
        while (!feof(arquivo))
        {
            
			text = strstr(meuContato.nome, busca);           
            if (text != NULL){          
                
                printf("\n Código Identificador: %d\n", meuContato.id);
				printf(" Nome: %s\n", meuContato.nome);
				printf(" Telefone/Celular:%d %d\n", meuContato.celular.ddd, meuContato.celular.numero);
                printf(" Aniversário: %d/%d\n", meuContato.aniversario.dia, meuContato.aniversario.mes);
                encontrado = 1;                
            }
            fread(&meuContato, 1, sizeof(struct contato), arquivo);
        }		
 		
 
        if (!encontrado)
        {
            printf("\n Contato não encontrado!\n");
            
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Nenhum registro encontrado no arquivo!\n");
        
    }
    
    
    
    system("PAUSE");
}


boolean existeContato(unsigned short id)
{    
    boolean flag;
	struct contato meuContato;
    FILE *arquivo;   
 
    arquivo = fopen("agenda.txt", "rb");
 
    if (arquivo)
    {
        fread(&meuContato, 1, sizeof(struct contato), arquivo);
        while (!feof(arquivo))
        {
            
                
                if(meuContato.id == id){
                	flag = 1;	
                }else{
                	flag = 0;
                }				
				            
            fread(&meuContato, 1, sizeof(struct contato), arquivo);
        }
        
        fclose(arquivo);
        
        
    }
    return flag;
}

void consultarContatoPorId(unsigned short id){ 
    
    int encontrado=0;
	struct contato meuContato;	
    FILE *arquivo;   
 
    arquivo = fopen("agenda.txt", "rb");
 
    if (arquivo)
    {
        fread(&meuContato, 1, sizeof(struct contato), arquivo);
        while (!feof(arquivo))
        {
            
                
                if(meuContato.id == id){
                	printf("\n Código Identificador: %d\n", meuContato.id);
					printf(" Nome: %s\n", meuContato.nome);
					printf(" Telefone/Celular:%d %d\n", meuContato.celular.ddd, meuContato.celular.numero);
		            printf(" Aniversário: %d/%d\n", meuContato.aniversario.dia, meuContato.aniversario.mes);	              	
		            encontrado = 1;
		            break;
            	}
				            
            fread(&meuContato, 1, sizeof(struct contato), arquivo);
        }      
        
        fclose(arquivo);
        
        
        
        if(!encontrado){        	        
        	printf(" Contato não encontrado.");
        }
        
    }else{
    	printf(" Nenhum registro de contato na agenda.");
    }    
}

void alterarContato(void)
{
    int encontrado = 0;
    int id;
    char nome[128];
    int ddd;
    int numero;
    int dia;
    int mes;
    
    struct contato contatoTemporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;
 
 	listarContatos();
 	
    system("cls");
 
    printf("\tAGENDA DE CONTATOS - ATUALIZAR CONTATO\n\n");
    printf(" Código Identificador: ");    
    scanf("%d",&id);
    printf(" Novo Nome: ");
    fflush(stdin);
    gets(nome);    
	printf(" Novo DDD: ");    
    scanf("%d",&ddd);
    printf(" Novo Número: ");    
    scanf("%d",&numero);
    printf(" Novo Dia: ");    
    scanf("%d",&dia);
    printf(" Novo Mês: ");    
    scanf("%d",&mes);   
 
    arquivoAntigo = fopen("agenda.txt", "rb");
    
    if (arquivoAntigo)    	
    {
    	
        arquivoAtualizado = fopen("temp.txt", "wb");
        
        if (!arquivoAtualizado)
        {
        	
            printf("\n Falha na atualizacao da agenda!");
            Sleep(5000); 
            return;
        }
 		
        fread(&contatoTemporario, 1, sizeof(struct contato), arquivoAntigo);
        
        while (!feof(arquivoAntigo))
        {
        	
            if (contatoTemporario.id == id)
            {		
                
                strcpy(contatoTemporario.nome, nome);			
				contatoTemporario.celular.ddd = ddd;			
				contatoTemporario.celular.numero = numero;                				
				contatoTemporario.aniversario.dia = dia;
                contatoTemporario.aniversario.mes = mes;                 
                
                encontrado = 1;
            }
            fwrite(&contatoTemporario, 1, sizeof(struct contato), arquivoAtualizado);
            fread(&contatoTemporario, 1, sizeof(struct contato), arquivoAntigo);
        }
 
        fclose(arquivoAntigo);
        fclose(arquivoAtualizado);
 
        remove("agenda.txt");
        rename("temp.txt", "agenda.txt");       
 
        if (!encontrado)
        {
            printf("\n Não foi possível encontrar o contato...");
        }
        else
        {
            printf("\n Atualização realizada com sucesso!");
        }
 
        Sleep(5000);
    }
    else
    {
        printf("\n Nenhum contato encontrado!");
        Sleep(5000);
    }
}
 
void excluirContato(void)
{
    int encontrado = 0;    
    unsigned short id;
    int decisao;        
    struct contato contatoTemporario;
    FILE *arquivoAntigo = NULL, *arquivoAtualizado = NULL;
 	
    system("cls"); 
 
    printf("\tAGENDA DE CONTATOS - EXCLUIR CONTATO\n\n");
    printf(" Código Identificador do Contato: ");    
    scanf("%d",&id);
 
 	printf(" Tem certeza que deseja excluir o contato?\n");
 	printf(" 1->SIM\n");
 	printf(" 0->NÃO\n");
	printf(" Escolha sua opção:\n");
 	scanf("%d",&decisao);
 	
 		
 	if (decisao == 1){
	    arquivoAntigo = fopen("agenda.txt", "rb");
	    if (arquivoAntigo)
	    {
	        arquivoAtualizado = fopen("temp.txt", "wb");
	        if (!arquivoAtualizado)
	        {
	            printf("\n Falha na exclusão da obra!");
	            fclose(arquivoAntigo);
	            Sleep(5000); 
	            return;
	        }
	 
	        fread(&contatoTemporario, 1, sizeof(struct contato), arquivoAntigo);
	        while (!feof(arquivoAntigo))
	        {
	            if (contatoTemporario.id == id)
	            {
	                encontrado = 1;
	            }
	            else
	            {
	                fwrite(&contatoTemporario, 1, sizeof(struct contato), arquivoAtualizado);
	            }
	            fread(&contatoTemporario, 1, sizeof(struct contato), arquivoAntigo);
	        }
	 
	        fclose(arquivoAntigo);
	        fclose(arquivoAtualizado);
	 
	        remove("agenda.txt");
	        rename("temp.txt", "agenda.txt");
	        
	        
	 
	        if (!encontrado)
	        {
	            printf("\n Não foi possível encontrar o contato...");
	        }
	        else
	        {
	            printf("\n Exclusão realizada com sucesso!");
	        }
	 
	        Sleep(5000); 
	    }
	    else
	    {
	        printf("\n Nenhum contato encontrado!");
	        Sleep(5000); 
	    }
	}
}

void listarContatos(void)
{   
	int *id; 
	int n=0;
	int linhas=0;
	int contador=0;
    struct contato meuContato;
    FILE *arquivo;
 
    system("cls"); 
 
    printf("\tAGENDA DE CONTATOS - LISTAGEM GERAL \n\n");    
 
    arquivo = fopen("agenda.txt", "rb");
    
    linhas = numeroLinhasArquivo();   
 	
    if (arquivo)
    {
        fread(&meuContato, 1, sizeof(struct contato), arquivo);
        id = (int*) malloc(linhas*sizeof(int));
        while (!feof(arquivo))
        {               
                
				id[contador] = meuContato.id;								
				contador++;				
				            
            fread(&meuContato, 1, sizeof(struct contato), arquivo);
        }
        
        fclose(arquivo);
        
        
        
        
        qsort(id, linhas, sizeof(int), compare);
        for(n=0; n<linhas; n++){        	
        	consultarContatoPorId(id[n]);
		}     	
		
		free(id);
        
    }
    else
    {
        printf("\n Nenhum registro encontrado no arquivo!\n");
        
    } 
    
    system("PAUSE");
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int numeroLinhasArquivo(void){    
    
    int totalLinhas=0;
	struct contato meuContato;
    FILE *arquivo;   
 
    arquivo = fopen("agenda.txt", "rb");
 
    if (arquivo)
    {
        fread(&meuContato, 1, sizeof(struct contato), arquivo);
        while (!feof(arquivo))
        {                   
				++totalLinhas;				
				            
            fread(&meuContato, 1, sizeof(struct contato), arquivo);
        }
        
        fclose(arquivo);
        
        
    }   
    
    return totalLinhas;
}

void aniversariantesMes(void){   
	
	struct tm *data;          
  	time_t segundos;	
	int encontrado = 0;    
    struct contato meuContato;
    FILE *arquivo;	
 
    system("cls"); 
 
    printf("\tAGENDA DE CONTATOS - ANIVERSARIANTES DO MÊS\n\n");
    
    time(&segundos);    
  	data = localtime(&segundos);       	
	mes = data->tm_mon+1;		
	
	printf(" Mês ");
	switch(mes)
    {
	    case Janeiro:
	    printf("%d - Janeiro",mes);
	    break;
	    
	    case Fevereiro:
	    printf(" %d - Fevereiro",mes);
	    break;
	    
	    case Marco:
	    printf(" %d - Marco",mes);
	    break;
	    
	    case Abril:
	    printf(" %d - Abril",mes);
	    break;
	    
	    case Maio:
	    printf(" %d - Maio",mes);
	    break;
	    
	    case Junho:
	    printf(" %d - Junho",mes);
	    break;
	    
	    case Julho:
	    printf(" %d - Julho",mes);
	    break;
	    
	    case Agosto:
	    printf(" %d - Agosto",mes);
	    break;
	    
	    case Setembro:
	    printf(" %d - Setembro",mes);
	    break;
	    
	    case Outubro:
	    printf(" %d - Outubro",mes);
	    break;
	    
	    case Novembro:
	    printf(" %d - Novembro",mes);
	    break;
	    
	    case Dezembro:
	    printf(" %d - Dezembro",mes);
	    break;
	    
    }	    
 
    arquivo = fopen("agenda.txt", "rb");
 
    if (arquivo)
    {
        fread(&meuContato, 1, sizeof(struct contato), arquivo);
        while (!feof(arquivo))
        {        
			
            if (meuContato.aniversario.mes == mes){          
                
                printf("\n Código Identificador: %d\n", meuContato.id);
				printf(" Nome: %s\n", meuContato.nome);
				printf(" Telefone/Celular:%d %d\n", meuContato.celular.ddd, meuContato.celular.numero);
                printf(" Aniversário: %d/%d\n", meuContato.aniversario.dia, meuContato.aniversario.mes);
                encontrado = 1;                
            }
            fread(&meuContato, 1, sizeof(struct contato), arquivo);
        }		
 		
 
        if (!encontrado)
        {
            printf("\n Nenhum aniversariante no mês!\n");
            
        }
        fclose(arquivo);
        
        
    }
    else
    {
        printf("\n Nenhum registro encontrado no arquivo!\n");
        
    }
    
    
    system("PAUSE");
	
	
}

