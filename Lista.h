/* 
 * File:   Lista.h
 * Author: root
 *
 * Created on 14 de Junho de 2016, 10:05
 */

#ifndef LISTA_H
#define	LISTA_H
 
#include <ostream>
 
using namespace std;
 
// uma classe template para nodos da lista ...
template <class T> struct Nodo {
  T dado;
  Nodo<T> * proximo;
 
  // um construtor para criar um Nodo facilmente ...
  Nodo(const T & umDado);
};
 
// a classe template para a lista ...
template <class T> class Lista {
 private:
  // ponteiros para o primeiro e último nodos da lista
  Nodo<T> * inicio, * ultimo;
  Nodo<T> * nodoAtual;
  // a quantidade de nodos existente na lista
  int comp;
 public:
  //construtor: não precisa de parâmetros para criar uma nova lista
  Lista();
 
  // construtor de cópia
  Lista(const Lista &outra);
 
  // destrutor
  ~Lista();
 
  // adiciona "algo" no inicio da lista
  void adiciona(const T & algo);
 
  // adiciona "algo" no final da lista
  void anexa(const T & algo);
 
  // adiciona "algo" em uma posição específica da lista  
  void insere(const T & algo, int posicao);
 
  // remove o dado que está na "posicao" na lista, e retorna 
  // uma cópia desse dado
  T remove(int posicao);
 
  // remove o dado que for equivalente a "algo", e retorna 
  // uma cópia desse dado
  T retira(const T & algo);
 
  // estas duas operações são idênticas: retorna
  // uma referência ao dado que está na "posicao" na lista
  T& obtem(int posicao) const;
  T& operator[](int pos) const;
 
  // estes operadores podem ser implementados depois
  Lista& operator=(const Lista<T> & outra);
  bool operator==(const Lista<T> & outra) const;
 
 
  // Retorna uma referência a um dado que seja equivalente a "algo"
  //T& procura(const T &algo) const; 
  
  // operação de procura: procura os dados da lista igual a "algo"
  // se nenhum dado for encontrado, retorna uma lista vazia
  // esta versão compara os dados da lista com "algo" usando um comparador default.
  // o comparador default simplesmente compara os dados usando o operador ==
  // portanto, esses operadores devem estar implementados para a classe "T" 
  Lista<T> * procura(const T & algo) const;
  
  T& procura2(const T & algo);
  
 
  // Procura todos os dados equivalentes a "algo", e os
  // anexa a "lista". Retorna uma referência a "lista".
  Lista<T> & procuraMuitos(const T &algo, Lista<T> & lista) const;
 
  // retorna a quantidade de dados armazenados na lista
  int comprimento() const;
 
  // retorna true se lista estiver vazia
  bool vazia() const;
 
  // Esvazia a lista
  void esvazia();
 
  // apresenta o conteúdo da lista no stream "out"
  void escrevaSe(ostream & out) const;
  void escrevaSe(ostream & out, char delim) const;
 
  
  
  // ordena a lista
  void ordena();
  
  // Método ordenaBolha: faz o ordenamento de uma lista usando bubble sort
  void ordenaBolha();
  
  // Método ordenaSelecao: faz o ordenamento de uma lista usando bubble sort
  void ordenaSelecao();
  
  void ordenaSelecaoDecrescente();
  
  // métodos envolvidos na iteração:
  // inicia uma iteração
  void inicia();
 
  // retorna uma referência ao próximo dado da iteração
  // se não houver mais dados, gera uma exceção
  T& proximo();
 
  // retorna verdadeiro se a iteração terminou (chegou ao fim da lista)
  bool fim() const;
  
  void insereOrdenado(const T & algo);
  
  void ordenaInsercao();
  
  void mostraLista();
  
  void mostraLista(ostream & out);
  
  void inverte();
  
};

template <typename T> Nodo<T>::Nodo(const T & umDado) {
    proximo = NULL;
    dado = umDado;
}
 
template <typename T> Lista<T>::Lista() {
    inicio = NULL;
    ultimo = NULL;
    comp = 0;
}
 
template <typename T> Lista<T>::Lista(const Lista<T> & outra) {
}
 
template <typename T> Lista<T>::~Lista() {
}
 
template <typename T> void Lista<T>::adiciona(const T& algo) {
    Nodo<T> * nodo = new Nodo<T> (algo);
    
    nodo->proximo = inicio;
    inicio = nodo;
    if (ultimo == NULL) ultimo = nodo;
    comp++;
    
}
 
template <typename T> void Lista<T>::anexa(const T& algo) {
    Nodo<T> * nodo = new Nodo<T>(algo);
    
    /*if(comp == 0) adiciona(algo);
    else {
        comp++;
        ultimo->proximo = nodo;
        ultimo = nodo;
    }*/
    
    //ou assim
    if (comp == 0) {
        inicio = nodo;
    }else{
        ultimo->proximo = nodo;
    }
    ultimo = nodo;
    comp++;
}
 
template <typename T> int Lista<T>::comprimento() const {
    return comp;
}
 
template <typename T> void Lista<T>::esvazia() {
    int posicao = comprimento();
    Nodo<T> * ptr = inicio;
    Nodo<T> * aux;
    
    while (posicao > 0) {
        aux = ptr;
        ptr = ptr->proximo;
        delete aux;
        if(ptr == NULL){
            //cout << "entrei aqui" << endl;
            inicio = NULL;
            ultimo = NULL;
            comp=0;
        }
        
        posicao--;
    }
}
 
template <typename T> void Lista<T>::insere(const T& algo, int posicao) {
    if (posicao >= comp) throw -1;
    
    if (posicao == 0){
        adiciona(algo);
    }else{
        Nodo<T> * nodo = new Nodo<T>(algo);
        Nodo<T> * ptr = inicio;
        posicao--;
        for (; posicao > 0; posicao--, ptr = ptr->proximo);
        nodo->proximo = ptr->proximo;
        ptr->proximo = nodo;
        comp++; 
   }
    
    
}
 
template <typename T> T& Lista<T>::obtem(int posicao) const {
    if (posicao >= comp) throw -1;
    
    Nodo<T> * ptr = inicio;
    for (; posicao > 0; posicao--, ptr = ptr->proximo);
    
    //com while
    /*while (posicao > 0){
        posicao--;
        ptr = ptr->proximo;
    }*/
    
    return ptr->dado;
}
 
template <typename T> T& Lista<T>::operator[](int pos) const {
    return obtem(pos);
 
}
 
template <typename T> void Lista<T>::escrevaSe(ostream& out) const {
    for (Nodo<T> * ptr = inicio; ptr != NULL; ptr = ptr->proximo){
        out << ptr->dado << endl;
    }
    
    //ou assim
    //escrevaSe(out, '\n');
}
 
template <typename T> void Lista<T>::escrevaSe(ostream& out, char delim) const {
    for (Nodo<T> * ptr = inicio; ptr != NULL; ptr = ptr->proximo){
        out << ptr->dado << delim;
    }
}
 
template <typename T> T Lista<T>::remove(int posicao) {
    T dado;
    Nodo<T> * ptr = inicio;
    Nodo<T> * aux;
    
    
    
    
    if (vazia() == true) throw 'e';
    
    if (posicao >= comp) throw -1;
    
    if (posicao == 0){
        
        dado = ptr->dado;
        inicio = ptr->proximo;
        
        if(inicio == NULL){
            ultimo = ptr->proximo;
        }
        delete ptr;
        comp--;
        
    }else{
       
        posicao--;
       
        while (posicao > 0 ){
          
          ptr = ptr->proximo;
          posicao--;
        }
        
        //for (; posicao > 0; posicao--, ptr = ptr->proximo);
        
        aux = ptr->proximo->proximo;
        dado = ptr->proximo->dado;
        delete ptr->proximo;
        ptr->proximo = aux;
        comp--;
        if(ptr->proximo == NULL){
            ultimo = ptr;
        }
        
    }
  return dado;  
}
 
template <typename T> T Lista<T>::retira(const T& algo) {
        
        T dado2;
        int posicao = comprimento();
        
        Nodo<T> * ptr2 = inicio;
        Nodo<T> * aux;
        Nodo<T> * aux2;
        
        
            
            if (vazia() == true) throw 'e';
        
            while (posicao > 0) {
            
                if (ptr2->dado == algo){
                    if (ptr2 == inicio){
                        ptr2 = ptr2->proximo;
                        dado2 = remove(0);
                        
                    
                    }else{
                    
                        dado2 = ptr2->dado;
                        aux->proximo = ptr2->proximo;
                        aux2 = ptr2;
                        ptr2 = ptr2->proximo;
                        delete aux2;
                        if(aux->proximo == NULL){
                            ultimo = aux;
                        }
                        comp--;
                        
                    }
                
                }else{ 
                    aux = ptr2;
                    ptr2 = ptr2->proximo;
                }
            
                posicao--;
            }
        return dado2;
              
}
 
template <typename T> bool Lista<T>::vazia() const {
    return comp == 0; 
}
 
 
template <typename T> void Lista<T>::ordena() {
 
}
 
 
template <typename T> Lista<T>* Lista<T>::procura(const T& algo) const {
    
    int posicao = comprimento();
    Nodo<T> * ptr = inicio;
    
    Lista<T> * iguais = new Lista<T>;
    //procura todos os dados iguais
    for(int k=0; k < posicao; k++){
        if(ptr->dado == algo){
            iguais->adiciona(ptr->dado);
        }
        ptr = ptr->proximo;
    }
    return iguais;
 
}

template <typename T> T& Lista<T>::procura2(const T& algo){
    
    int posicao = comprimento();
    Nodo<T> * ptr = inicio;
    
    T *dado;
    //procura todos os dados iguais
    for(int k=0; k < posicao; k++){
        if(ptr->dado == algo){
            dado = &ptr->dado;
            
        }
        ptr = ptr->proximo;
    }
    return *dado;
 
}


 
template <typename T> Lista<T>& Lista<T>::procuraMuitos(const T& algo, Lista<T>& lista) const {
    
}
 
template <typename T> Lista<T>& Lista<T>::operator=(const Lista<T>& outra) {
    inicio = outra.inicio;
    ultimo = outra.ultimo;
    comp = outra.comp;
}
 
template <typename T> bool Lista<T>::operator==(const Lista<T>& outra) const {
}


template <typename T> void Lista<T>::ordenaBolha() {
    T dado;
    int posicao = comprimento();
    posicao--;
    Nodo<T> * ptr = inicio;
    Nodo<T> * aux;
    
    for(; posicao > 0; posicao--){
        aux = ptr;
        for(int k=0; k < posicao; k++){
            if(aux->dado > aux->proximo->dado){
                dado = aux->dado;
                aux->dado = aux->proximo->dado;
                aux->proximo->dado = dado;
            } 
            aux = aux->proximo;
        }
    }    
}
    
template <typename T> void Lista<T>::ordenaSelecao() {
    T dado;
    int posicao = comprimento();
    posicao--;
    int posicao2 = comprimento();
    Nodo<T> * ptr = inicio;
    Nodo<T> * aux;
    
    for(int j=0; j < posicao; j++){
        aux = ptr;
        for(int k=j+1; k < posicao2; k++){
            if(aux->proximo->dado < ptr->dado ){
                dado = ptr->dado;
                ptr->dado = aux->proximo->dado;
                aux->proximo->dado = dado;
            }
            aux = aux->proximo;
        }
        ptr = ptr->proximo;
    }   

}  

template <typename T> void Lista<T>::ordenaSelecaoDecrescente() {
    T dado;
    int posicao = comprimento();
    posicao--;
    int posicao2 = comprimento();
    Nodo<T> * ptr = inicio;
    Nodo<T> * aux;
    
    for(int j=0; j < posicao; j++){
        aux = ptr;
        for(int k=j+1; k < posicao2; k++){
            if( ptr->dado < aux->proximo->dado){
                dado = ptr->dado;
                ptr->dado = aux->proximo->dado;
                aux->proximo->dado = dado;
            }
            aux = aux->proximo;
        }
        ptr = ptr->proximo;
    }   

} 

template <typename T> void Lista<T>::inicia(){
    nodoAtual = inicio;
}

template <typename T> T& Lista<T>::proximo(){
    T * dado;
    
    if (nodoAtual == NULL) throw 1;
    
        dado = &nodoAtual->dado;
        nodoAtual = nodoAtual->proximo;
    
    return *dado;
}

template <typename T> bool Lista<T>::fim() const{
 return nodoAtual == NULL;    
}

template <typename T> void Lista<T>::insereOrdenado(const T & algo){
    
    if (vazia() == true){
        adiciona(algo);
    }else{
        
        Nodo<T> * ptr = inicio;
    
        //se dado < valor do primeiro nodo então
        if(algo < ptr->dado){
            //insere dado no inicio da lista
            insere(algo, 0);
        }else{
            ptr = ptr->proximo;
            //para nodo do inicio ao fim da lista
            for(int i=1; i < comprimento(); i++){
                //se dado do nodo > dado entao
                if(ptr->dado > algo){
                    //insere dado antes do nodo
                    //retorna
                    insere(algo, i);
                    return;
                }
                ptr = ptr->proximo;
            }
            //anexa o dado ao final da lista
            anexa(algo);
        }
    }
}

template <typename T> void Lista<T>::ordenaInsercao(){
    Lista<T> lista2;
    T dado;
    
    while(vazia() != true){
        dado = remove(0);
        lista2.insereOrdenado(dado);
    }
    
    *this = lista2;
    
}

/*template <typename T> void Lista<T>::mostraLista(){
    cout << "Comprimento: " << comp << endl;
    
    int pos = 0;  
    while (pos < comp) {
        T algo = remove(0);
        anexa(algo);
        cout << "Posicao " << pos;
        cout << ": " << algo << endl;    
        pos++;
    }
    cout << endl;
    
}*/

template <typename T> void Lista<T>::mostraLista(ostream & out){
    inicia();
    while (not fim()) {
        string & dado = proximo();
        out << dado << endl;
    } 
}

template <typename T> void Lista<T>::inverte(){
    T dado;
    int posicao = comprimento();
    posicao--;
    Nodo<T> * ptr = inicio;
    Nodo<T> * aux;
    
    for(; posicao > 0; posicao--){
        aux = ptr;
        for(int k=0; k < posicao; k++){
            dado = aux->dado;
            aux->dado = aux->proximo->dado;
            aux->proximo->dado = dado;
            aux = aux->proximo;
        }
    }      
}

#endif	/* LISTA_H */





