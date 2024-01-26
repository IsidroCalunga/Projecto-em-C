#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<locale.h> 
#include<string.h>

 FILE *basededados; //arquivo definicao

    struct conta{
    int codigo_conta, numeroconta, codigo_cliente,tipo_conta,estado;
    float saldo;
    };

    struct pessoa{
    char nome[40],morada[14],bi[14];
    int nif,telefone,codigo_pessoa,tipo;
     };

                  typedef struct conta conta;
                  conta contas[2000];                   
                  typedef struct  pessoa pessoa;
                  pessoa clientes[2000];
                  int qtcliente=0,gerarcodigo,qtcontas;
                  //prototipos 
                  void criarficheiro();
                  void backup();
                  void carregar_informacoes_do_arquivo();
           
               

bool cadastro_de_cliente(pessoa p){
        if(qtcliente<1000){
        clientes[qtcliente]=p;
        clientes[qtcliente].codigo_pessoa=p.codigo_pessoa+gerarcodigo; // 0 1
        qtcliente++;
        gerarcodigo++;
        printf("Cliente cadastrado com sucesso:%s.\n",p.nome);
        return true;
         }
        return false;
 }

pessoa* encontrar_codigo_pessoa (int codigo_cliente){ 
        int buscar;
        for(buscar=0;buscar<qtcliente;buscar++){
             if(clientes[buscar].codigo_pessoa==codigo_cliente){
               printf("Código encontrado\n");
                printf("Nome do cliente:%s\n",clientes[buscar].nome);
       return &clientes[buscar];
    }
  }
 printf("Não cadastrado\n");
 return NULL;
 }
 
bool validadrtipo(int tipopessoa,int tipoconta){
if (tipopessoa==1 && tipoconta==0){
  return true;
}
else{
  if(tipopessoa==2 && tipoconta==1){
    return true;
  }
}
printf("Dados não compativeis ou o tipo de conta não corresponde ao tipo de pessoa \n ");
return false;
}
  
bool abertura_de_conta(pessoa p,int tipo_conta){
  int buscar;
  conta abrirconta;
  abrirconta.numeroconta=1000+gerarcodigo;
  abrirconta.saldo=0.0;
  abrirconta.tipo_conta=tipo_conta;
  abrirconta.codigo_cliente=p.codigo_pessoa;
  abrirconta.estado=0;
  bool validar=validadrtipo(p.tipo,tipo_conta);
  if (validar==true){
  contas[qtcontas]=abrirconta;
  qtcontas++;
  gerarcodigo++;
  printf("Abertura de conta realizada com sucesso!\n");
  
  return true;
  }
  return false;

  }

conta *encontrar_num_da_conta(int numero_conta){
int buscar;
       for (buscar=0;buscar<qtcontas;buscar++){
             if(contas[buscar].numeroconta==numero_conta){
                return &contas[buscar];
               }
           }
             // printf("Esse numero de conta nao existe\n");
 return NULL;
 }

conta *encontrar_conta_apartir_codigo_cliente(int codigo){
    int buscar;
    for (buscar=0;buscar<qtcontas;buscar++){
     if(contas[buscar].codigo_cliente==codigo){
      return &contas[buscar];
     }
    }
  return NULL;
  }

void listarclientes(){
int buscar; 
             printf("---------------------LISTA DE CLIENTES----------------------------\n");
             for(buscar=0;buscar<qtcliente;buscar++){
            
                if (clientes[buscar].tipo==1){
                    printf("-----------------------------------------\n");
                             printf("CLIENTES PARTICULARES\n");
                    printf("Codigo Pessoal :%d.\n",clientes[buscar].codigo_pessoa);         
                    printf("Nome:%s.\n",clientes[buscar].nome);
                    printf("BI:%s.\n",clientes[buscar].bi);
                    printf("Morada:%s.\n",clientes[buscar].morada);
                    printf("Tel:%d.\n",clientes[buscar].telefone);
                    
                    conta *verificando = encontrar_conta_apartir_codigo_cliente(clientes[buscar].codigo_pessoa);
                    if(verificando!=NULL){
                     printf("Numerodeconta:%d\n",verificando->numeroconta);
                     printf("Saldo:%2.f\n",verificando->saldo);
                     printf("Codigo_cliente:%d\n",verificando->codigo_cliente);
                      printf("Tipo de conta:%d\n",verificando->tipo_conta);
                      printf("Estado da conta:%d\n",verificando->estado);
                    }
                    else{
                      printf("Att:Não existe uma conta\n");
                    }
                    printf("-----------------------------------------\n");
                }
                else{
                    if(clientes[buscar].tipo==2){
                    printf("-----------------------------------------\n");
                              printf("CLIENTES EMPRESA\n");
                     printf("Codigo Empresa :%d.\n",clientes[buscar].codigo_pessoa);              
                    printf("Nome da empresa:%s.\n",clientes[buscar].nome);
                    printf("NIF:%d.\n",clientes[buscar].nif);
                    printf("Morada:%s.\n",clientes[buscar].morada);
                    printf("Tel:%d.\n",clientes[buscar].telefone);
                    conta *verificando = encontrar_conta_apartir_codigo_cliente(clientes[buscar].codigo_pessoa);
                    if(verificando!=NULL){
                     printf("Numerodeconta:%d\n",verificando->numeroconta);
                     printf("Saldo:%2.f\n",verificando->saldo);
                     printf("Codigo_cliente:%d\n",verificando->codigo_cliente);
                      printf("Tipo de conta:%d\n",verificando->tipo_conta);
                      printf("Estado da conta:%d\n",verificando->estado);
                     printf("-----------------------------------------\n");
                    }
                    else{
                      printf("Att:Não existe uma conta\n");
                    }

                    }
                }
             }
                printf("-------------------------------------------------\n");

              }
bool depositar_dinheiro(int numero_conta,float valor){
 conta *verificando=encontrar_num_da_conta(numero_conta);
  if(verificando==NULL){
        return false;
           } 
  if(valor<=0){
  printf("Impossivel depositar devido ao valor \n");
  return false;
   }
  printf("Deposito realizado com sucesso\n");
  printf("-----Detalhes da Operação-----\n");
  printf("Deposito no valor de : %2.f.\n",valor);
  printf("Para conta:%d.\n",verificando->numeroconta);
  printf("----------------------------------\n");
  verificando->saldo=verificando->saldo+valor;
  verificando->estado=1;
  return true;
   }

bool levantar_dinheiro(int num_conta,float valor){
conta*verificando=encontrar_num_da_conta(num_conta);
if(verificando==NULL){
return false;
}
if(verificando->saldo<valor || valor<=0){
printf("Impossivel levantar dinheiro\n");
return false;   
}
  printf("Levantamento realizado com sucesso\n");
  printf("-----Detalhes da Operação-----\n");
  printf("Levantado o valor de : %2.f.\n",valor);
  printf("Da conta:%d.\n",verificando->numeroconta);
  printf("----------------------------------\n");
  verificando->saldo=verificando->saldo-valor;
                //verificando->estado=1;
  return true;
              }

float consultar_saldo(int num_conta){
conta *verificancosaldo=encontrar_num_da_conta(num_conta);
if(verificancosaldo==NULL){
return -1;
}
printf("-----Detalhes da Operação-----\n");
printf("Saldo disponivel:%2.f.\n",verificancosaldo->saldo);
printf("----------------------------------\n");
return 1;
}
              
bool trasnsferir_dinheiro(int num_conta_enviar,int num_conta_receber,float valor){
conta *verificarcontaenviar=encontrar_num_da_conta(num_conta_enviar);
if(verificarcontaenviar==NULL ){
                return false;
}
conta *verificarcontareceber=encontrar_num_da_conta(num_conta_receber);
if(verificarcontareceber==NULL){
return false;
}
if(verificarcontaenviar->saldo<valor){
printf("Não Há esse valor na conta enviar\n");
return false;
}
if(verificarcontareceber->estado==0){
  return false;
  printf("A conta a enviar ainda nao esta activa\n");
   }
 verificarcontaenviar->saldo=verificarcontaenviar->saldo-valor;
 verificarcontareceber->saldo=verificarcontareceber->saldo+valor;
printf("-----Detalhes da Operação-----\n");
printf("Valor enviado:%2.f\n",valor);
printf("Da conta:%d\n",verificarcontaenviar->numeroconta);
 printf("Para :%d\n",verificarcontareceber->numeroconta);
printf("----------------------------------\n");
return true;
  }

bool actualizar_dados(pessoa p,int codigo_pessoa){
  pessoa *verificarcodigo=encontrar_codigo_pessoa(codigo_pessoa);
  if(verificarcodigo==NULL){
    return false;
  }
  p=*verificarcodigo;
 clientes[qtcliente]=p;
 // qtcliente++;
  printf("Actualizacão de dados feita com sucesso\n");   
  return true;
}


int main(){
    setlocale(LC_ALL,"Portuguese"); //lingua portuguesa
        pessoa p;
        int menu,buscarcodigo,encontrar_conta,encontrar_conta_deposito,consultar,contaenviar,contareceber,codigo_actualizar,editar,editar_tipo,editar_tipo_empresa,novonif,novotel;
        float valordepositar,valorlevantar,valorenviar; 
        char novonome[40],novobi[14],novamorada[40];// utilizados para actualizar os dados
        criarficheiro();
     
   
        while(menu!=9){
       
      printf("1-CADASTRAR CLIENTE\n2-LISTAR CLIENTE\n3-ABERTURA DE CONTA\n4-DEPOSITO DE DINHEIRO\n5-LEVANTAMENTO DE DINHEIRO\n6-CONSULTA DE SALDO\n7-TRANSFERENCIA\n8-ACTUALIZAR CONTA\n9-TERMINAR\n");
      scanf("%d",&menu);
      switch(menu){
      case 1:
            printf("1-PESSOA PARTICULAR\n2-PESSOA EMPRESA\n");
            scanf("%d",&p.tipo);
            
            switch (p.tipo)
             
            {
            case 1:
                printf("Nome:");
                scanf("%s",p.nome);
               
                printf("BI:");                
                scanf("%s",p.bi);
                printf("Morada:");
                scanf("%s",p.morada);
                printf("Tel:");
                scanf("%d",&p.telefone);
                system("clear");
                cadastro_de_cliente(p);
                break;
                case 2:
                  printf("Nome Empresa:");
                scanf("%s",p.nome);
                printf("NIF:");
                scanf("%d",&p.nif);
                printf("Localizacao:");
                scanf("%s",p.morada);
                printf("Tel:");
                scanf("%d",&p.telefone);
                system("clear");
                cadastro_de_cliente(p);
            default:
                break;
            }

      break;
      case 2:
      listarclientes();
      break;
      case 3:
      printf("Digite o codigo do cliente registado:");
      scanf("%d",&buscarcodigo);
     pessoa *verificar=encontrar_codigo_pessoa(buscarcodigo);
      if(verificar!=NULL){
        int tipo_de_conta;
        p=*verificar;
        printf("0-CONTA PARTICULAR ou 1-CONTA EMPRESA\n");
        scanf("%d",&tipo_de_conta);
        system("clear");
        abertura_de_conta(p,tipo_de_conta);
          
      }
      else{
        printf("Impossivel fazer abertura de conta\n");
      }
      break;

      case 4:
        printf("Digite o numero de conta :");
        scanf("%d",&encontrar_conta);
        conta *verificarconta=encontrar_num_da_conta(encontrar_conta);
        if(verificarconta==NULL){
         
          printf("Essa conta não existe\n");
        }
        else{
        printf("Valor a depositar:");
        scanf("%f",&valordepositar);
        system("clear");
       depositar_dinheiro(encontrar_conta,valordepositar);
        }
      break;
     case 5:
     printf("Digite o numero de conta:");
     scanf("%d",&encontrar_conta_deposito);
     conta *verificarencontrarconta=encontrar_num_da_conta(encontrar_conta_deposito);
     if(verificarencontrarconta==NULL){
          printf("Essa conta não existe\n");
     }
     else{
      printf("Valor a levantar:");
      scanf("%f",&valorlevantar);
      system("clear");
      levantar_dinheiro(encontrar_conta_deposito,valorlevantar);

     }
     break;
      
      case 6:
      printf("Digite o numero da conta:");
      scanf("%d",&consultar);
      conta *verificarcontaparasaldo=encontrar_num_da_conta(consultar);
      if(verificarcontaparasaldo==NULL){
        printf("Essa conta não existe\n");

      }
      else{
        system("clear");
        consultar_saldo(consultar);
      }

      break;
      case 7:
       printf("Numero da conta enviar:");
       scanf("%d",&contaenviar);
       conta *vericontarenviar=encontrar_num_da_conta(contaenviar);
       if(vericontarenviar==NULL){
        printf("Essa conta nao existe\n");
       }
       else{
         
       printf("Numero conta receber:");
       scanf("%d",&contareceber);
       conta *vericontareceber=encontrar_num_da_conta(contareceber);
       if(vericontareceber==NULL){
        printf("Não existe essa conta\n");
       }else{
         printf("Valor enviar:");
       scanf("%f",&valorenviar);
       trasnsferir_dinheiro(contaenviar,contareceber,valorenviar);
       }
       }
       
       
      break;
     case 8:
      printf("Digite o codigo da pessoa\n");
       scanf("%d",&codigo_actualizar);
       pessoa *verificarcodigoactualizar=encontrar_codigo_pessoa(codigo_actualizar);
       if(verificarcodigoactualizar==NULL){
        printf("Esse codigo no existe\n");
       }
      if(verificarcodigoactualizar->tipo==1){
        printf("ESCOLHE O CAMPO QUE DESEJA EDITAR\n");
        printf("1-Nome da pessoa\n2-BI\n3-Morada\n4-Telefone\n");
        scanf("%d",&editar_tipo);
        switch(editar_tipo){
          case 1:
       printf("Nome da pessoa:");
       scanf("%s",novonome);
       strcpy(verificarcodigoactualizar->nome,novonome);
        system("clear");
         
       actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);
       break;
        case 2:
        printf("BI:");
       scanf("%s",novobi);
       strcpy(verificarcodigoactualizar->bi,novobi);
       
       actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);
       break;
       case 3:
           printf("Morada:");
       scanf("%s",novamorada);
       strcpy(verificarcodigoactualizar->morada,novamorada);
          
       actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);
       break;
       case 4:
           printf("Tel:");
       scanf("%d",&novotel);
        verificarcodigoactualizar->telefone=novotel;
        
        actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);
     
        }

      }else{
       if(verificarcodigoactualizar->tipo==2){
          printf("ESCOLHE O CAMPO QUE DESEJA EDITAR\n");
        printf("1-Nome da Empresa\n2-NIF\n3-Morada\n4-Telefone\n");
        scanf("%d",&editar_tipo_empresa);
        switch(editar_tipo_empresa){
          case 1:
       printf("Nome da empresa:");
       scanf("%s",novonome);
       strcpy(verificarcodigoactualizar->nome,novonome);
        
       actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);
       break;

        case 2:
        printf("NIF:");
       scanf("%d",&novonif);
      verificarcodigoactualizar->nif=novonif;
       
       actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);
       break;
       case 3:
           printf("Morada:");
       scanf("%s",novamorada);
       strcpy(verificarcodigoactualizar->morada,novamorada);
      
       actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);

       break;
       case 4:
           printf("Tel:");
       scanf("%d",&novotel);
        verificarcodigoactualizar->telefone=novotel;
       
        actualizar_dados(*verificarcodigoactualizar,codigo_actualizar);

       }

      }
      } 
      break;
      case 9:
       printf("Sessão terminado!\n");
      break;
     

      }
       backup();
       
      
      }
          
}
void criarficheiro(){
 basededados=fopen("backup.txt","a");
 if (basededados!=NULL){
    printf("Existe conexão com base de dados\n");
 }
 else{
  printf("Erro de conexao\n");
 }

}
  void backup() {
    int buscar;
    basededados = fopen("backup.txt", "w");
    if (basededados == NULL) {
        printf("Impossivel fazer escrever dados\n");
    }
    for (buscar = 0; buscar < qtcliente; buscar++) {
        if (clientes[buscar].tipo == 1) {
            fprintf(basededados, "Nome:%s |BI:%s |Morada:%s |Telefone: %d.\n", clientes[buscar].nome, clientes[buscar].bi, clientes[buscar].morada, clientes[buscar].telefone);

            conta *posicao=encontrar_conta_apartir_codigo_cliente(clientes[buscar].codigo_pessoa);
            if(posicao!=NULL){
              fprintf(basededados, "Numero de conta:%d |Saldo:%2.f |Codigo_Cliente :%d |Tipo de conta :%d |Estado :%d.\n", posicao->numeroconta, posicao->saldo, posicao->codigo_cliente, posicao->tipo_conta, posicao->estado);
            }

        }else{
          if(clientes[buscar].tipo == 2){
             fprintf(basededados, "Nome:%s |NIF:%d |Morada:%s |Telefone: %d.\n", clientes[buscar].nome, clientes[buscar].nif, clientes[buscar].morada, clientes[buscar].telefone);

            conta *posicao=encontrar_conta_apartir_codigo_cliente(clientes[buscar].codigo_pessoa);
            if(posicao!=NULL){
              fprintf(basededados, "Numero de conta:%d |Saldo:%2.f |Codigo_Cliente :%d |Tipo de conta :%d |Estado :%d.\n", posicao->numeroconta, posicao->saldo, posicao->codigo_cliente, posicao->tipo_conta, posicao->estado);
            }

          }
        }
    }

 fclose(basededados);

}



   


  