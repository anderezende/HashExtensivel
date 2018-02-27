#include "Diretorio.h"

//construtor da classe parametrizado
//funcao parametrizada para receber a profundidade global e o tamanho do Balde
Diretorio::Diretorio(int profundidade, int Balde_size){
    this->global_profundidade = profundidade; //profundidade global
    this->Balde_size = Balde_size; // tamanho do Balde
    for(int i = 0 ; i < 1<<profundidade ; i++ ){
        Baldes.push_back(new Balde(profundidade,Balde_size)); //instancia um novo Balde e faz push_back, que é adicionar um novo elemento ao final depois do ultimo valor inserido
    }
}

int Diretorio::hash(int n){ //Classe de objeto de função Unary que define a função hash padrão usada pela biblioteca padrão
    return n&((1<<global_profundidade)-1); //operador de deslocamento de bit
}

int Diretorio::pardeIndice(int Balde_no, int profundidade){ //par de indice
    return Balde_no^(1<<(profundidade-1)); //retorno o Balde no e a profundidade
}

void Diretorio::crescer(void){ //metodo de crescimento com retorno vazio
    for(int i = 0 ; i < 1<<global_profundidade ; i++ ) //operador de deslocamento de bit
        Baldes.push_back(Baldes[i]); //adciona o valor no Balde na posicao i
    global_profundidade++; //retorna a posicao global, com o intuito de ver se aumentou a profundidade.
}

void Diretorio::encolher(void){ //metodo de encolhimento com retorno vazio
    int i,flag=1;
    for( i=0 ; i<Baldes.size() ; i++ ){ // percorre o Balde do inicio ate o fim
        if(Baldes[i]->getprofundidade()==global_profundidade){ //verificar se a profundidade do Balde e igual ao tamanho global do mesmo
            flag=0;
            return; //fim da funcao
        }
    }
    global_profundidade--; //diminui a profundidade global
    for(i = 0 ; i < 1<<global_profundidade ; i++ ) //deslocador de bit
        Baldes.pop_back(); //remove o ultimo elemento reduzindo o tamanho em um.
}

void Diretorio::fatiar(int Balde_no){
    int local_profundidade,pair_index,index_diff,dir_size,i;
    map<int, string> temp; //Os mapas são recipientes associativos que armazenam elementos formados por uma combinação de um valor de chave e um valor mapeado , seguindo uma ordem específica.
    map<int, string>::iterator it;

    local_profundidade = Baldes[Balde_no]->aumentaprofundidade(); //profundidade local aumenta e é retornada pelo metodo aumentaprofundidade
    if(local_profundidade>global_profundidade) //verifica se a profundidade local e maior que global, se for deve-se aumentar a global também
        crescer();
    pair_index = pardeIndice(Balde_no,local_profundidade); //atribui valor ao par
    Baldes[pair_index] = new Balde(local_profundidade,Balde_size); //aloca um novo Balde com profundidade local e o tamanho definido anteriormente
    temp = Baldes[Balde_no]->copy(); // Copia os elementos do intervalo para o intervalo que começa no resultado e atribui a uma variavel temporaria
    Baldes[Balde_no]->clear(); //Remove todos os elementos do vetor, deixando o Balde vazio
    index_diff = 1<<local_profundidade; //desloca bit e atribui a index_diff
    dir_size = 1<<global_profundidade; //desloca bit e atribui a dir_size
    for( i=pair_index-index_diff ; i>=0 ; i-=index_diff )
        Baldes[i] = Baldes[pair_index]; // realoca os Balde
    for( i=pair_index+index_diff ; i<dir_size ; i+=index_diff )
        Baldes[i] = Baldes[pair_index]; // realoca os Balde
    for(it=temp.begin();it!=temp.end();it++) //Retorna um iterador apontando para o primeiro elemento na sequência ate o final
        insert((*it).first,(*it).second,1); //O vetor é extendido, inserindo novos elementos antes do elemento na posição especificada , efetivamente aumentando o tamanho do recipiente pelo número de elementos inseridos //
}

void Diretorio::merge(int Balde_no){ //combinacao de elementos
    int local_profundidade,pair_index,index_diff,dir_size,i;

    local_profundidade = Baldes[Balde_no]->getprofundidade(); //atribui o valor de profundidade local
    pair_index = pardeIndice(Balde_no,local_profundidade); //atribui o retorno de pardeIndice definida anteriormente
    index_diff = 1<<local_profundidade; // atribui a profundidade local com bit deslocado
    dir_size = 1<<global_profundidade; // atribui a profundidade global com bit deslocado

    if( Baldes[pair_index]->getprofundidade() == local_profundidade ){ //testa se o Balde estao na mesma profundidade
        Baldes[pair_index]->diminuiprofundidade(); //decrementa a profundidade
        delete(Baldes[Balde_no]); //deleta o elemento do Balde
        Baldes[Balde_no] = Baldes[pair_index];
        for( i=Balde_no-index_diff ; i>=0 ; i-=index_diff )
            Baldes[i] = Baldes[pair_index]; //vai preenchendo o Balde
        for( i=Balde_no+index_diff ; i<dir_size ; i+=index_diff )
            Baldes[i] = Baldes[pair_index]; //vai preenchendo o Balde
    }
}

string Diretorio::Balde_id(int n){
    int d;
    string s;
    d = Baldes[n]->getprofundidade(); //pega profundidade
    s = "";
    while(n>0 && d>0){
        s = (n%2==0?"0":"1")+s; //atribui o resto ta divisao usando operador ternario
        n/=2; //simplificacao de expressao n = n/2
        d--; //decrementa a fim de sair do while
    }
    while(d>0){
        s = "0"+s;
        d--;
    }
    return s;
}

void Diretorio::insert(int chave,string valor,bool reinsercao){
    int Balde_no = hash(chave); //calcula o hash da chave e atribui uma posicao para colocar no Balde
    int status = Baldes[Balde_no]->insert(chave,valor); //insere no Balde na posicao correta a chave e um valor, isso retornará um status que sera de sucesso ou falha
    if(status==1){ //caso de sucesso
      //  if(!reinsercao)
       //     cout<<"Chave " << chave << " inserida no Balde "<<Balde_id(Balde_no)<<endl; //insere a chave no Balde e mostra onde foi inserida
       // else
         //   cout<<"Moveu chave "<<chave<<" para o Balde "<<Balde_id(Balde_no)<<endl; //move a chave e mostra para onde foi
    }
   // else
        if(status==0){ //caso de falha
        fatiar(Balde_no); //fatia na posicao
        insert(chave,valor,reinsercao); // insere
    }
    else{
     //   cout<<"Chave "<<chave<<" ja existe no Balde "<<Balde_id(Balde_no)<<endl; //chave ja existente no Balde, para reeinsercao deve-se parametrizar o reinsercao
    }
}
/* os modos aqui usados, seram como um teste para saber se tera uma recombinacao ou uma delecao de um bucket null, porém a intencao desta estrutura é crescer, julgando somente o modo para teste*/
void Diretorio::remove(int chave,int modo){
    int Balde_no = hash(chave); //calcula o hash para saber em qual diretorio estara a chave
    if(Baldes[Balde_no]->remove(chave)) //se removeu a chave aparecera a mensagem abaixo
        cout<<"Deletou chave "<<chave<<" do Balde "<<Balde_id(Balde_no)<<endl;
    if(modo>0){
        if(Baldes[Balde_no]->estaVazio() && Baldes[Balde_no]->getprofundidade()>1)
            merge(Balde_no);
    }
    if(modo>1){
        encolher();
    }
}

void Diretorio::search(int chave){
    int Balde_no = hash(chave); //calcula o hash e atribui a uma posicao
    cout<<"Procurando chave "<<chave<<" no Balde "<<Balde_id(Balde_no)<<endl; //mostra a chave se encontrar
    Baldes[Balde_no]->search(chave); //itera sobre os Baldes para pesquisar o elemento

}

void Diretorio::mostrar(bool duplicados){ //mostra toda estrutura
    int i,j,d;
    string s;
    std::set<string> shown; //Os conjuntos são recipientes que armazenam elementos exclusivos seguindo uma ordem específica
    cout<<"Profundidade Global: "<<global_profundidade<<endl; //mostra profundidade global
    for(i=0;i<Baldes.size();i++) // anda de inicio ate tamanho fim
    {
        d = Baldes[i]->getprofundidade(); //pega profundidade e atribui a d
        s = Balde_id(i);   //pega o elemento no Balde(i) e atribui para s
        if(duplicados || shown.find(s)==shown.end()) //duplicados vem com o intuito de mostrar valores repetidos, é parametrizavel na main,
        {
            shown.insert(s); //elementos inseridos numa ordem definida
            for(j=d;j<=global_profundidade;j++) //mostra da profundidade pega ate a global
                cout<<" ";
            cout<<s<<" => "; //mostra o elemento
            Baldes[i]->mostrar(); //itera sobre o elemento
        }
    }
}
