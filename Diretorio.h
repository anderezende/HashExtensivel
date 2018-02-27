#ifndef Diretorio_H_INCLUDED
#define Diretorio_H_INCLUDED

#include <bits/stdc++.h>
#include "Bucket.h"

using namespace std;
/*Assinatura das funções que seram implementadas em um arquivo cpp, todas seram comentadas la*/
class Diretorio {
        int global_profundidade, Balde_size;
        std::vector<Balde*> Baldes;
        int hash(int n);
        int pardeIndice(int Balde_no, int profundidade);
        void crescer(void);
        void encolher(void);
        void fatiar(int Balde_no);
        void merge(int Balde_no);
        string Balde_id(int n);
    public:
        Diretorio(int profundidade, int Balde_size);
        void insert(int chave,string valor,bool reinsercao);
        void remove(int chave,int modo);
        void search(int chave);
        void mostrar(bool duplicados);
};

#endif // Diretorio_H_INCLUDED
