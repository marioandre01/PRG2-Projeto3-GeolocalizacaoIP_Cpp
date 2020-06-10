/* 
 * File:   Arvore.h
 * Author: root
 *
 * Created on 18 de Julho de 2016, 18:50
 */

#ifndef ARVORE_H
#define ARVORE_H
 
#include <string>
#include <fstream>
#include "Lista.h"
 
using namespace std;
 
// Uma árvore de pesquisa binária: na verdade, um objeto da classe Arvore
// representa um nodo de uma árvore ...
 
template <class T> class Arvore {
 protected:
  T valor; // valor guardado neste nodo da árvore
  Arvore<T> * esq, * dir; // ramos esquerdo e direito
  unsigned int t = 0;
 public:
  Arvore(const T& data);
  Arvore(const Arvore<T> & outra);
  Arvore();
  ~Arvore();
 
  // adiciona um dado à árvore
  void adiciona(const T & dado);
 
  // "obtem" e "operator[]" são idênticos:
  // obtém um dado que seja igual a "algo"
  T & obtem(const T & algo) ;
  T & operator[](const T & algo);
  
 
  // remove um valor da árvore... deixemos isto por último ;-)
  T remove(const T & algo);
 
  // algo mais simples: remove os ramos esquerdo e direito
  void esvazia();
 
  // altura da folha mais profunda
  unsigned int altura() const;
  
 
  // quantidade de nodos da árvore
  unsigned int tamanho() const;
 
  void escrevaSe(ostream & out) const;
  
  void escrevaSeTop(ostream & out) const;
  
  //grava em um stream os dados da árvore em sequência pre-order
  void escrevaSePreOrder(ostream & out) const;
 
  // retorna a subárvore esquerda ou direita
  Arvore<T> * esquerda() const;
  Arvore<T> * direita() const;
 
  // grava uma cópia dos valores na lista fornecida
  void valores(Lista<T> & lista) const;
 
  // retorna uma referência ao valor da raiz
  T & obtemValor() const {return valor;}
 
  // verifica se "algo" existe na árvore
  bool existe(const T & algo) const;
  
  // A operação que calcula o fator de balanceamento
  int fatorB() const;
 
  // A operação que balanceia a árvore
  // note que ela retorna um ponteiro para a nova raiz ...
  Arvore<T> * balanceia();
 
  // os métodos protegidos da Arvore ... por enquanto são públicos
  // quando estiverem prontos, devem ficar protegidos ou privativos
 
  // rotação esquerda
  Arvore<T> * rotacionaL();
 
  // rotação direita
  Arvore<T> * rotacionaR();
  
};

template <typename T>Arvore<T>::Arvore(const T& data){
    esq = NULL;
    dir = NULL;
    valor = data;
    t++;
}



template <typename T> void Arvore<T>::adiciona(const T& dado){
    /*if(dado < valor){
        if(esq == NULL) esq = new Arvore<T>(dado);
        else esq->adiciona(dado);
    }else if(dado > valor){
        if(dir == NULL) dir =new Arvore<T>(dado);
        else dir->adiciona(dado);
    }else valor = dado;*/
    
    Arvore<T> * ptr = this;
    
    while(true){
        if(ptr->valor == dado){
            ptr->valor = dado;
            break;
        }
        if(dado < ptr->valor){
            if(ptr->esq == NULL){
                ptr->esq = new Arvore<T>(dado);
                t++;
                break;
            }
            ptr = ptr->esq;
        }else{
            if(ptr->dir == NULL){
                ptr->dir = new Arvore<T>(dado);
                t++;
                break;
            }
            ptr = ptr->dir;
        }
    }
       
    
}

template <typename T> T & Arvore<T>::obtem(const T& algo){
    
    Arvore<T> * ptr = this;
    
    /*while(true){
        if(ptr->valor == algo){
            return ptr->valor;
        }
        if(algo < ptr->valor){
            if(ptr->esq == NULL) throw -1;
            
            ptr = ptr->esq;
        }else{
            if(ptr->dir == NULL)throw -1;
      
            ptr = ptr->dir;
        }
    }*/
    
    while(ptr){
        if (ptr->valor == algo) return ptr->valor;
        if (algo < ptr->valor) ptr = ptr->esq;
        else ptr = ptr->dir;
    }
    throw -1; // nao encontrou "algo"
}

template <typename T>Arvore<T>::~Arvore(){
    
}


template <typename T> void Arvore<T>::escrevaSe(ostream & out) const{
    //Arvore<T> * ptr = this;
    if(esq) esq->escrevaSe(out);
    out << valor << endl;
    if(dir) dir->escrevaSe(out);
}

//Método escrevaSe reescrito para ajudar a visualizar a topologia da árvore
template <typename T> void Arvore<T>::escrevaSeTop(ostream& out) const {
    static int nivel = -1;
    string prefixo;
 
    nivel++;
    prefixo.append(nivel, ' ');
 
    if (dir) dir->escrevaSeTop(out);
    out << prefixo << valor << endl;
    if (esq) esq->escrevaSeTop(out);
    nivel--;
}

template <typename T> unsigned int Arvore<T>::altura() const{
    unsigned int he=0, hd=0;
    
    if(not esq and not dir) return 0;
    if (esq) he = esq->altura();
    if (dir) hd = dir->altura();
    
    if (hd > he) return hd + 1;
    return he + 1;
}

template <typename T> int Arvore<T>::fatorB() const{
    unsigned int he=0, hd=0;
    
    if(not esq and not dir) return 0;
    if (esq) he = esq->altura();
    if (dir) hd = dir->altura();
    
    return he-hd;
    
}


template <typename T> Arvore<T> * Arvore<T>::balanceia(){
    Arvore<T> * ptr = this;
    
    int fb;
    
    if (not (esq or dir)) return this;
    if (esq) esq = esq->balanceia();
    if (dir) dir = dir->balanceia();
    
    fb = fatorB();
    
    while(fb < -1){
        if (ptr->dir->fatorB() > 0) ptr->dir = ptr->dir->rotacionaR();
        ptr = ptr->rotacionaL();
        fb = ptr->fatorB();
    }
    
    while(fb > 1){
        if (ptr->esq->fatorB() < 0) ptr->esq = ptr->esq->rotacionaL();
        ptr = ptr->rotacionaR();
        fb = ptr->fatorB();
    }
    
    return ptr;
           
}

template <typename T> Arvore<T> * Arvore<T>::rotacionaL(){
    Arvore<T> * ptr1 = this;
    Arvore<T> * ptr2 = dir;
    Arvore<T> * ptr3 = ptr2->esq;
    ptr1->dir = ptr3;
    ptr2->esq = ptr1;
    return ptr2;
}

template <typename T> Arvore<T> * Arvore<T>::rotacionaR(){
    Arvore<T> * ptr1 = this;
    Arvore<T> * ptr2 = esq;
    Arvore<T> * ptr3 = ptr2->dir;
    ptr2->dir = ptr1;
    ptr1->esq = ptr3;
    
    return ptr2;
}

template <typename T> void Arvore<T>::escrevaSePreOrder(ostream & out) const{
    out << valor << endl;
    if(esq) esq->escrevaSePreOrder(out);
    if(dir) dir->escrevaSePreOrder(out);
}

template <typename T> unsigned int Arvore<T>::tamanho() const{
    return t;
}

#endif



