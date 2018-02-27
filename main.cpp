/*
Disciplina: Banco de dados II

*/

#include <bits/stdc++.h>

#include "Bucket.h"
#include "Diretorio.h"

using namespace std;

void menu();

  vector<string> fatiar(string str, char delimitador) { //funcao para esplodir em delimitador especifico  com o objetivo de inserir e remover
  vector<string> internal;
  stringstream ss(str); //Transforme a cadeia em um fluxo.
  string tok;

  while(getline(ss, tok, delimitador)) { //pega a linha do arquivo de acordo com o delimitador
    internal.push_back(tok);
    //Adiciona um novo elemento ao final do vetor , depois do último elemento atual. O conteúdo de val é copiado (ou movido) para o novo elemento
  }

  return internal;
}

void menu(){ //menu com as opções
    cout<<"--------------------"<<endl;
    cout<<"Digite uma das opcoes abaixo:"<<endl;
    cout<<"1 - Pesquisar Chave."<<endl;
    cout<<"2 - Mostrar Tabela Completa."<<endl;
    cout<<"0 - Sair."<<endl;
    cout<<"--------------------"<<endl;
}

int main(){
    bool mostra_dup_Baldes; //parametro que ativa se vai mostrar os Balde duplicado, ou seja quando aumentar de nivel se uma funcao hash de nivel superior podera ter um Balde apontando para uma de nivel inferior
    int Balde_size, inicializacao_global_profundidade; //tamanho do Balde e profundidade global
    int chave, modo;
    int opcao;
    string valor;
    string line;
    string table;
    bool quit = false;
    ifstream fileReader ("output.csv"); //variavel de arquivo
    vector<string> sep; //variavel para funcao fatiar
    int tamanhocoluna =10;
    //mudar a variavel para 1 para ver todas as instancias de ponteiros
    mostra_dup_Baldes = 0;

    cout<<"Insira o tamanho do Balde: ";
    cin>>Balde_size;
    Balde_size = 5;
    cout<<"Insira a profundidade Global Inicial: ";
    cin>>inicializacao_global_profundidade;
    inicializacao_global_profundidade =1;

    Diretorio d(inicializacao_global_profundidade,Balde_size); //inicializa o diretorio (construtor)

    if(fileReader.is_open()){//Se o arquivo foi aberto com sucesso
        while (getline(fileReader,line)){//Vai pegando as linhas do arquivo
            cout <<line <<'\n';//Imprime cada linha
            sep=fatiar(line, ','); // explode as linhas na virgula
            if(sep[0]=="+"){ //delimitador para insercao
                chave = atoi(sep[1].c_str()); //converte a string em um inteiro
                table = "";
                for(int i=2;i<=tamanhocoluna;i++){
                    table = table + " | "+sep[i]; //insere o resto da string associado a um chave
                }
                valor = table;
                d.insert(chave,valor,0); //insere a chave e string montada restante
                cout<<endl;
            }

            if(sep[0]=="-"){ //delimitador para deletar
                cout<<"Selecionou deletar" <<endl;
                chave = atoi(sep[1].c_str()); //conveter uma string para um inteiro
                modo = 2; //modo fixado para deletar (flag), essa flag é usada para testar se vai diminuir o grau ou se vai permanecer ja que a tendencia é sempre crescer e diminuir pode nao ser vantagem
                d.remove(chave,modo); //remover a chave
                cout<<endl;
            }
        }
    }

    fileReader.close(); // fim do arquivo
/*Menu com todas as opções apos insercao e delecao dos dados extraidos do arquivo*/
    while (!quit){
        menu();
        cout << ">>> Insira a Opcao: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
                cout<<"Insira a chave a ser pesquisada: "<<endl;
                cin>>chave;
                cout<<endl;
                d.search(chave); //funcao de pesquisar uma chave determinada, deverá retornar o restante dos dados referente a chave
                cout<<endl;
                break;
            case 2:
                cout<<endl;
                d.mostrar(mostra_dup_Baldes); //mostra uma visao mais geral, mostra a estrutura completa
                cout<<endl;
                break;
            case 0:
                cout<<endl;
                cout<<"Saindo."<<endl;
                quit=true; //sai do menu e finaliza a aplicacao
                break;
            default:
                cout<<"Opcao Invalida."<<endl; //caso digite uma opcao invalida
                break;
        }
    }

    return 0;
}
