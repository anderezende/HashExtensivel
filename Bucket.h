#ifndef Bucket_H_INCLUDED
#define Bucket_H_INCLUDED
#include <bits/stdc++.h>

using namespace std;
/*Assinatura das funções que seram implementadas em um arquivo cpp, todas seram comentadas la*/
class Balde {
        int profundidade,size;
        std::map<int, string> valors;
    public:
        Balde(int profundidade, int size);
        int insert(int chave,string valor);
        int remove(int chave);
        void search(int chave);
        int estaCheio(void);
        int estaVazio(void);
        int getprofundidade(void);
        int aumentaprofundidade(void);
        int diminuiprofundidade(void);
        std::map<int, string> copy(void);
        void clear(void);
        void mostrar(void);
};

#endif // Bucket_H_INCLUDED
