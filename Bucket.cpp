#include "Bucket.h"

Balde::Balde(int profundidade, int size){ //construtor da classe, parametrizado para receber uma profundidade e um tamanho
    this->profundidade = profundidade; //atribui profundidade
    this->size = size; //atribui tamanho, quantidade de elementos no Balde
}

int Balde::insert(int chave, string valor){ //metodos inserir utilizado em diretorio,
    std::map<int,string>::iterator it;
    //iterator Este é um modolo de classe base que pode ser usado para derivar as classes do iterador dele
    //map Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica
    it = valors.find(chave);
    //Retorna um iterador para o primeiro elemento no intervalo
    if(it!=valors.end())
    //Retorna um iterador para o ultimo elemento no intervalo
        return -1;
    if(estaCheio()) //metodo que verifica se esta cheio
        return 0;
    valors[chave] = valor; //atribui o valor de acordo com a chave responsavel
    return 1;
}

int Balde::remove(int chave){
    std::map<int,string>::iterator it;
    //iterator Este é um modolo de classe base que pode ser usado para derivar as classes do iterador dele
    //map Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica
    it = valors.find(chave); //Retorna um iterador para o primeiro elemento no intervalo
    if(it!=valors.end()){ //Retorna um iterador para o ultimo elemento no intervalo
        valors.erase(it); //remove um elemento unico it
        return 1;
    }
    else{
        cout<<"Nao e possivel remover pois essa chave nao existe"<<endl;
        return 0;
    }
}

void Balde::search(int chave){
    std::map<int,string>::iterator it;
     //iterator Este é um modolo de classe base que pode ser usado para derivar as classes do iterador dele
    //map Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica
    it = valors.find(chave); //Retorna um iterador para o primeiro elemento no intervalo
    if(it!=valors.end()){ //Retorna um iterador para o ultimo elemento no intervalo
        cout<<"Valor = "<<it->second<<endl; //retorna o valor pesquisado
    }
    else{
        cout<<"Essa chave nao existe"<<endl; // se nao encontrar a chave
    }
}

int Balde::estaCheio(void){ //verificar se o Balde esta cheio
    if(valors.size()==size) //verifica o tamanho para saber se esta cheio
        return 1;
    else
        return 0;
}

int Balde::estaVazio(void){ //verifica se esta vazio o Balde
    if(valors.size()==0)  //pega o size para ver se esta vazio
        return 1;
    else
        return 0;
}

int Balde::getprofundidade(void){ //pega a profundidade e retorna
    return profundidade;
}

int Balde::aumentaprofundidade(void){ //incrementa a profundidade
    profundidade++;
    return profundidade;
}

int Balde::diminuiprofundidade(void){ //decrementa a profundidade
    profundidade--;
    return profundidade;
}

std::map<int, string> Balde::copy(void){
    //map Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica
    //copia um elemento para determinado em um range especifico
    std::map<int, string> temp(valors.begin(),valors.end());
    //map Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica
    //end Retorna um iterador para o ultimo elemento no intervalo
    // begin Retorna um iterador apontando para o primeiro elemento na seqüência:
    return temp; //retorna um temporario
}

void Balde::clear(void){ //remove todos os elementos
    valors.clear();
}

void Balde::mostrar(){ //mostra tudo o que esta no Balde
    std::map<int,string>::iterator it;
     //iterator Este é um modolo de classe base que pode ser usado para derivar as classes do iterador dele
    //map Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica
    for(it=valors.begin();it!=valors.end();it++) //itera do inicio ate o fim a fim de mostrar tudo oq no Balde
        it->first;
        cout<<it->first<<" "; //mostra o elemento concatenando um espaco
    cout<<endl;
}
