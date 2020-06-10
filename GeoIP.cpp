/* 
 * File:   GeoIP.cpp
 * Author: root
 * 
 * Created on 10 de Junho de 2016, 10:08
 */

#include "GeoIP.h"
#include <cstdlib>
#include <iostream>


//"16777216","16777471","17"
// addr1, addr2, locid

GeoIP::GeoIP(){
    
}

GeoIP::GeoIP(const string & linha){
    
    istringstream inp(linha);
    inp.ignore(1);
    inp >> addr1;
    inp.ignore(3);
    inp >> addr2;
    inp.ignore(3);
    inp >> locid;
    
    if (inp.fail()) throw -1;
    
}

GeoIP::~GeoIP() {
    
}

string GeoIP::ip2str(unsigned int addr) {  //Conversão de endereço IP no formato de inteiro de 32 bits para string
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

unsigned int GeoIP::str2ip(const string & ip) { //Conversão de endereço IP no formato string para o formato de 32 bits
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

bool GeoIP::operator==(const GeoIP & outro){
    // verdadeiro se a faixa de endereços do "outro" objeto GeoIP estiver dentro 
    // da faixa de endereços deste objeto GeoIP
    bool ok = (addr1 <= outro.addr1) and (addr2 >= outro.addr2);
    
    // verdadeiro se a faixa de endereços deste objeto estiver dentro 
    // da faixa de endereços do "outro" (só necessário testar se ok for false)
    if(not ok){
        ok = (addr1 >= outro.addr1) and (addr2 <= outro.addr2);
    }
    
    return ok;
}


bool GeoIP::operator<(const GeoIP & outro)const{
    return (addr2 < outro.addr2);
}

bool GeoIP::operator>(const GeoIP & outro)const{
    return (addr1 > outro.addr1);
}

ostream & operator<<(ostream & out, const GeoIP & outro){
    
    out << "\"" << outro.locid << "\",\"" << outro.addr2 << "\",\"" << outro.locid << "\"" ;
    
    return out;
}

unsigned int GeoIP::get_addr1(){ 
    return addr1;
}

unsigned int GeoIP::get_addr2(){ 
    return addr2;
}

unsigned int GeoIP::get_location(){ 
    return locid;
}

GeoIP::GeoIP(const string& ip1, const string& ip2, unsigned int id) {
    addr1 = str2ip(ip1);
    addr2 = str2ip(ip2);
    locid = id;
}

GeoIPLocation::GeoIPLocation(){
    
}

GeoIPLocation::GeoIPLocation(const string & linha){ //1,"O1","","","",0.0000,0.0000,,
   
  string tok;
  unsigned long n;
  char * ptr;
       
  //coletando dado do Id da string
  n = linha.find(',', 0);  //encontre a posição do caracter ',' apartir da posição 0 da string
  tok = linha.substr(0,n); // id
  if (tok != ""){ 
    id = strtoul(tok.c_str(), &ptr, 10); // convertendo string em unsigned int
    if (ptr == tok.c_str()) throw -1; // erro de conversão
  }else{
    id = 0;  
  }
 
  //coletando dado do pais da string
  int m = n+2;
  n = linha.find(',', m);
  pais = linha.substr(m,n-m-1); //coleta da string x caracteres com base no valor do segundo parametro, apartir da posição m, 
  
  //coletando dado da regiao da string
  m = n+2;
  n = linha.find(',', m);
  regiao = linha.substr(m,n-m-1); // regiao
  
  //coletando dado da cidade da string
  m = n+2;
  n = linha.find(',', m);
  cidade = linha.substr(m,n-m-1); //cidade
  
  //coletando dado da zipcode(CEP) da string
  m = n+2;
  n = linha.find(',', m);
  zipcode = linha.substr(m,n-m-1); //zipcode
  
  //coletando dado da latitude da string
  m = n+1;
  n = linha.find(',', m);
  tok = linha.substr(m,n-m); //latitude
  double r;
  if (tok != ""){
    istringstream stream(tok);
    stream >> r; //convertendo string em double
    latitude = r;
    if (stream.fail()) throw 1; // erro de conversão
  
  }else{
      latitude = 0;
  }
  
  //coletando dado da longitude da string
  m = n+1;
  n = linha.find(',', m);
  tok = linha.substr(m,n-m); //longitude
  if (tok != ""){  
    istringstream stream2(tok);
    stream2 >> r; //convertendo string em double
    longitude = r;
    if (stream2.fail()) throw 1; // erro de conversão
  }else{
    longitude = 0;
  }
  
  //coletando dado do metro da string
  m = n+1;
  n = linha.find(',', m);
  tok = linha.substr(m,n-m); //metro
  if (tok != ""){ 
    metro = strtoul(tok.c_str(), &ptr, 10);
    if (ptr == tok.c_str()) throw -1; // erro de conversão
  }else{
      metro = 0;
  }
  
  //coletando dado da area da string
  m = n+1;
  //n = linha.find('\0', m);
  tok = linha.substr(m); //area
  if (tok != ""){ 
    area = strtoul(tok.c_str(), &ptr, 10); //convertendo string para unsigned int
    if (ptr == tok.c_str()) throw -1; // erro de conversão
  }else{
      area = 0;
  }
  
    
}

GeoIPLocation::GeoIPLocation(unsigned int & id1){
    id = id1;
    pais = "";
    regiao = "";
    cidade = "";
    zipcode = "";
    latitude = 0;
    longitude = 0;
    metro = 0;
    area = 0;
    
}

GeoIPLocation::~GeoIPLocation() {
    
}

unsigned int GeoIPLocation::get_id(){ 
    return id;
}

string GeoIPLocation::get_pais(){ 
    return pais;
}

string GeoIPLocation::get_regiao(){ 
    return regiao;
}

string GeoIPLocation::get_cidade(){ 
    return cidade;
}

string GeoIPLocation::get_zipcode(){ 
    return zipcode;
}

double GeoIPLocation::get_latitude(){ 
    return latitude;
}

double GeoIPLocation::get_longitude(){ 
    return longitude;
}

unsigned int GeoIPLocation::get_metro(){
    return metro;
}

unsigned int GeoIPLocation::get_area(){
    return area;
}

bool GeoIPLocation::operator==(const GeoIPLocation & outro){
    return id == outro.id;
}

bool GeoIPLocation::operator<(const GeoIPLocation & outro)const{
    
    return id < outro.id;
}

bool GeoIPLocation::operator>(const GeoIPLocation & outro)const{
    
    return id > outro.id;
}

ostream & operator<<(ostream & out, const GeoIPLocation & outro){
    
    out << outro.id << ",\"" << outro.pais << "\",\"" << outro.regiao << "\",\"" << outro.cidade << "\",\"" << outro.zipcode << "\"," << outro.latitude << "," << outro.longitude << "," << outro.metro << "," << outro.area;
    
    return out;
}