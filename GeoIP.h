/* 
 * File:   GeoIP.h
 * Author: root
 *
 * Created on 10 de Junho de 2016, 10:08
 */

#ifndef GEOIP_H
#define	GEOIP_H

#include <sstream>
#include <ostream>
#include <string>
using std::string;

using namespace std;



// classe para representar uma faixa de endereços da base GeoIP ...
class GeoIP {
public:
    
    GeoIP(const string & linha); // construtor que cria um objeto a partir de uma linha do arquivo (formato CSV)
    GeoIP();
    GeoIP(const GeoIP& orig);
    
    // construtor que cria um objeto a partir de endereços IP e identificador de localidade
    GeoIP(const string & ip1, const string & ip2, unsigned int id);
    
    virtual ~GeoIP();
    unsigned int get_addr1();
    unsigned int get_addr2();
    unsigned int get_location();
    
    string ip2str(unsigned int addr); //Conversão de endereço IP no formato de inteiro de 32 bits para string
    unsigned int str2ip(const string & ip); //Conversão de endereço IP no formato string para o formato de 32 bits
    
    bool operator==(const GeoIP & outro); // operador de igualdade
    bool operator<(const GeoIP & outro)const;
    bool operator>(const GeoIP & outro)const; 
    friend ostream& operator<<(ostream & out, const GeoIP & outro);
    
    
private:
    unsigned int addr1, addr2;
    unsigned int locid;
};

//ostream & operator<<(ostream & out, const GeoIP & outro);

class GeoIPLocation {
public:
    GeoIPLocation(const string & linha);
    GeoIPLocation();
    GeoIPLocation(const GeoIPLocation & orig);
    virtual ~GeoIPLocation();
    
    // construtor que cria um objeto a partir do id e demais variaveis
    GeoIPLocation(unsigned int & id1);
    
    // faltam aqui os métodos para obter os valores dos atributos ...
    unsigned int get_id();
    string get_pais();
    string get_regiao();
    string get_cidade();
    string get_zipcode();
    double get_latitude();
    double get_longitude();
    unsigned int get_metro();
    unsigned int get_area();
    
    bool operator==(const GeoIPLocation & outro); // operador de igualdade
    bool operator<(const GeoIPLocation & outro)const;
    bool operator>(const GeoIPLocation & outro)const;
    friend ostream& operator<<(ostream & out, const GeoIPLocation & outro);
    
private:
    unsigned int id;
    string pais;
    string regiao;
    string cidade;
    string zipcode;
    double latitude, longitude;
    unsigned int metro, area;
};

#endif	/* GEOIP_H */