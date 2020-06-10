/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on 10 de Junho de 2016, 09:59
 */

#include <iostream>
#include <fstream>
#include "GeoIP.h"
#include "Lista.h"
#include <string>
#include "Arvore.h"
#include <time.h>

using namespace std;

/*
 * 
 */

Arvore<GeoIP>* le_blocos_Arvore(const char* path){
    
     ifstream arq(path);
    
    if (not arq.is_open()) {
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
        //return;
    }
    
    string linha;
    //for(int i=0; i < 3; i++){
        getline(arq,linha);
    //}
        
    GeoIP gip1(linha); // pegando a primeira linha do arquivo e tranformando-a em objeto GeoIP
    
    Arvore<GeoIP> * arv = new Arvore<GeoIP>(gip1); //Criando a arvore com o conteudo da primeira linha do arquivo
    
    //Adicionando conteudo do arquivo na arvore
    cout << "Criando arvore dos blocos de endereços IPs" << endl;
    while (true) {
    
        try{
            getline(arq,linha);
            if (arq.eof()) break;
            GeoIP gip(linha);
            arv->adiciona(gip);
        }catch (int e){
            //cerr << "ignorando - " << e << ": " << linha << endl;
        }
     
    }
    
    //Vendo a altura da arvore e balanceando-a no maximo que der
    cout << "Altura inicial da arvore: " << arv->altura() << endl;
    cout << "balanceando arvore..." << endl;
    for(int i=0; i < 3; i++){
        
        arv = arv->balanceia();
    } 
    cout << "Altura com a arvore balanceada: " << arv->altura() << endl;
    arq.close();  
    
    return arv;
}

Arvore<GeoIPLocation>* le_blocos_Local_Arvore(const char* path){
    
    ifstream arq(path);
    
    if (not arq.is_open()) {
        cerr << "Algum erro ao abrir o arquivo ..." << endl;
        //return;
    }
    
    string linha;
    //for(int i=0; i < 3; i++){
        getline(arq,linha);
    //}
        
    GeoIPLocation gipl1(linha); // pegando a primeira linha do arquivo e tranformando-a em objeto GeoIP
    
    Arvore<GeoIPLocation> * arv = new Arvore<GeoIPLocation>(gipl1); //Criando a arvore com o conteudo da primeira linha do arquivo
    
    //Adicionando conteudo do arquivo na arvore
    cout << "Criando arvore das localidades geográficas" << endl;
    while (true) {
    
        try{
            getline(arq,linha);
            if (arq.eof()) break;
            GeoIPLocation gipl(linha);
            arv->adiciona(gipl);
        }catch (int e){
            //cerr << "ignorando - " << e << ": " << linha << endl;
        }
     
    }
    
    //Vendo a altura da arvore e balanceando-a no maximo que der
    cout << "Altura inicial da arvore: " << arv->altura() << endl;
    cout << "balanceando arvore..." << endl;
    for(int i=0; i < 3; i++){
        
        arv = arv->balanceia();
    } 
    cout << "Altura com a arvore balanceada: " << arv->altura() << endl;
    
    arq.close();  
    
    return arv;
}

unsigned int str2ip(const string & ip) { //Conversão de endereço IP no formato string para o formato de 32 bits
    istringstream inp(ip);
 
    unsigned int o1, o2, o3, o4;
 
    inp >> o1; // lê primeiro número
    inp.ignore(1); // ignora o ponto
    inp >> o2; // lê segundo número
    inp.ignore(1); // ignora o ponto
    inp >> o3; // lê terceiro número
    inp.ignore(1); // ignora o ponto
    inp >> o4; // lê quarto número
 
    if (inp.fail()) throw -1; // erro de conversão !!!
 
    return (o1<<24) + (o2<<16) + (o3<<8) + o4;
}

string ip2str(unsigned int addr) { //Conversão de endereço IP no formato de inteiro de 32 bits para string
    unsigned int o1, o2, o3, o4;
    ostringstream out;
 
    o1 = addr >> 24; // extrai o primeiro número
    o2 = (addr >> 16) & 0xff; // extrai o segundo número 
    o3 = (addr >> 8) & 0xff; // extrai o terceiro número
    o4 = addr & 0xff; // extrai o quatro número
 
    // usa um stringstream de escrita para gerar uma string contendo
    // o endereço IP em formato decimal separado por pontos
    out << o1 << '.' << o2 << '.' << o3 << '.' << o4;
 
    return out.str();
}

int main() {
    
    clock_t tInicio, tFim, tDecorrido; 
    
    cout << "Carregando programa..." << endl;
    
    const char* path = "GeoLiteCity-Blocks2.csv"; //GeoLiteCity-Blocks2.csv é o arquivo com o conteudo do GeoLiteCity-Blocks.csv ja embaralhado
    
    tInicio = clock();
    Arvore<GeoIP> * arv1 = le_blocos_Arvore(path);
    tFim = clock();
    
    tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));
    cout << "Tempo para a criação da arvore: " << tDecorrido/1000 << " segundos" << endl;
    
    cout << endl;
    
    path = "GeoLiteCity-Location2.csv"; //GeoLiteCity-Location2.csv é o arquivo com o conteudo do GeoLiteCity-Location.csv ja embaralhado
    
    tInicio = clock();
    Arvore<GeoIPLocation> * arv2 = le_blocos_Local_Arvore(path);
    tFim = clock();
    
    tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));
    cout << "Tempo para a criação da arvore: " << tDecorrido/1000 << " segundos" << endl;
    
    string ip;
    string palavra;
    unsigned int addr;
    unsigned int id;
    int n;
 
    while(palavra != "sair"){
        cout << endl;
        cout << "##################################################################################" << endl;
        cout << "############################ Geolocalizador IP ###################################" << endl;
        cout << "##################################################################################" << endl;
        cout << " 1 - Pesquisar endereço IP" << endl;
        cout << " 2 - Pesquisar faixa de IPs por Países " << endl;
        cout << " 3 - Salvar conteudo da arvore em um arquivo" << endl;
        cout << " 4 - Sair" << endl;
        cout << "##################################################################################" << endl;
        
        cout << "Escolha uma opção: ";
        cin >> n;
        cout << endl;
       
        if (n == 1){
            cout << "Digite o IP a ser pesquisado: ";
            cin >> ip;
            cout << endl;
            cout << "****** Resultado da pesquisa ******" << endl;
            cout << "------------------------------------------" << endl;
            
              
            tInicio = clock();
            
            unsigned int a1, a2; 
            
            GeoIP aux(ip, ip, 0);
           
             try {
                // se "aux" não for encontrado, uma exceção será disparada ...
                GeoIP & gip = arv1->obtem(aux);
                a1 = gip.get_addr1();
                a2 = gip.get_addr2();
   
                cout << "Faixa de Ip: " << ip2str(a1) << " - " << ip2str(a2) << endl;
                id = gip.get_location();
            
                GeoIPLocation aux2(id);
            
                try {
                    // se "aux2" não for encontrado, uma exceção será disparada ...
                    GeoIPLocation & giploc = arv2->obtem(aux2);
                    cout << "Id de localidade: " << giploc.get_id() << endl;
                    cout << "País: " << giploc.get_pais() << endl;
                    cout << "Região: " << giploc.get_regiao() << endl;
                    cout << "Cidade: " << giploc.get_cidade() << endl;
                    cout << "Cep: " << giploc.get_zipcode() << endl;
                    cout << "Latitude: " << giploc.get_latitude() << endl;
                    cout << "Longitude: " << giploc.get_longitude() << endl;
                    cout << "Metro: " << giploc.get_metro() << endl;
                    cout << "Area: " << giploc.get_area() << endl;
                } catch (...) {
                    //cout << "Ops .. ID não encontrado" << endl;
                }
            
            } catch (...) {
                cout << "Ops .. IP não encontrado" << endl;
            }
            
            cout << "------------------------------------------" << endl;
            
            tFim = clock();
            
            tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));
            cout << "Tempo que durou para a pesquisa ser feita: " << tDecorrido << " milisegundos" << endl;
            
        }else if(n == 2){
            string pa;
            
            cout << "Digite a sigla do país a ser pesquisado(Sigla em letra maiuscula): ";
            cin >> pa;
            cout << endl;
            cout << "****** Resultado da pesquisa ******" << endl;
            cout << "------------------------------------------" << endl;
            
            int x = arv2->tamanho();
            
            for(unsigned int i=1; i < x;i++){
                
                GeoIPLocation aux3(i);
                try {
                
                    GeoIPLocation & giploc2 = arv2->obtem(aux3);
                    
                    if(pa == giploc2.get_pais()){
                        //cout << "País: " << giploc2.get_pais() << endl;
                    }
                     
                }catch(...){
                    //cout << "erro" << endl;
                }
                    
            }
            cout << "------------------------------------------" << endl;
            
        }else if(n == 3){
            cout << "Salvando conteudo das arvores em arquivos..." << endl;
            
            ofstream arq("teste.txt");
            arq << "Copyright (c) 2016 MaxMind Inc.  All Rights Reserved." << endl;
            arq << "startIpNum,endIpNum,locId" << endl;
            arv1->escrevaSePreOrder(arq);
            
            ofstream arq2("teste2.txt");
            arq2 << "Copyright (c) 2012 MaxMind LLC.  All Rights Reserved." << endl;
            arq2 << "locId,country,region,city,postalCode,latitude,longitude,metroCode,areaCode" << endl;
            arv2->escrevaSePreOrder(arq2);
            
            
            cout << "Processo concluido com sucesso!" << endl;
            
            
        }else if(n == 4){
            palavra = "sair";
            
        }else{
                
        }    
    }
     
}




