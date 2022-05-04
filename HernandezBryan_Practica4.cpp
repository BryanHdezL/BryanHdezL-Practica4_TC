/********************************************************************************************************
    Descripcion:
        Creacion de un programa que realice el conteo de cada uno de los TOKENS
        establecidos como OPERADORES, PUNTUACION e IDENTIFICADORES.
    Autores:
        Hernandez Lopez Bryan
        Martinez Islas Armando Samir
    Fecha de creacion:
        03/05/2022
    Version: 1.0
********************************************************************************************************/

//Librerias
#include<bits/stdc++.h> //Libreria de cabecera.
using namespace std;

//Prototipos de las funciones.
void leer();
int comprobar(int,int);
void contador(string);
void mostrar();
void nombre(string a, int i, string &variable);
unordered_map<string, int> caracteres;
unordered_map<string, string> tipo = {{"<<","Operador"}, {">>","Operador"}, {"++","Operador"}, {"--","Operador"}, {"-=","Operador"}, {"+=","Operador"},{"*=","Operador"},{"/=","Operador"},
                                        {"::","Operador"},{"!","Operador"},{"+","Operador"},{"=","Operador"},{"-","Operador"},{"/","Operador"},{"*","Operador"},{"//","Operador"},{"{","Operador"},{"}","Operador"},
                                        {"()","Puntuacion"}, {",","Puntuacion"}, {";","Puntuacion"}, {":","Puntuacion"},  {".","Puntuacion"},{"(","Puntuacion"},{")","Puntuacion"},{"[","Puntuacion"},{"]","Puntuacion"}, 
                                        {"<","Comparador"}, {">","Comparador"}, {"==","Comparador"}, {"<=","Comparador"}, {">=","Comparador"}, {"!=","Comparador"}};
unordered_set<string> operadores = {"<<", ">>", "++", "--", "-=", "+=","*=","/=", "::", "!","()",",",";",".", "<", ">", "==", "<=", ">=", "!=", "+", "=", "-", "/", "//", "", "*", ":","(", ")", "[", "]", "{", "}"};
unordered_set<string> variables = {"int","long","double","float","boolean","char","string","auto","void"};
unordered_set<string> digitos = {"0","1","2","3","4","5","6","7","8","9"};

//Funcion principal.
int main(){
    leer();
    return 0;
}

//Funcion de lectura del archivo .txt que contiene las cadenas de caracteres.
void leer(){
    ifstream archivo;
    string contenido;
    archivo.open("caracteres.txt",ios::in);  //Abrimos el archivo en lectura.
    if(archivo.fail()){
        cout<<"\t NO SE PUDO ABRIR EL ARCHIVO."<<endl;  //Mensaje en caso de no lograr encontrar o abrir el .txt
        exit(1);
    }
    cout<<"\n   -> Contenido del archivo de texto: \n"<<endl;
    cout<<"===================================================================================================================================================================================\n"<<endl;
    while(!archivo.eof()){  //Recorremos el archivo hasta llegar al final.
        getline(archivo,contenido); //Copiamos el contenido del archivo .txt a una variable tipo string.
        cout<<"\t"<<contenido<<endl;    //Mostramos en pantalla el contenido del archivo .txt.
        contador(contenido);  //Recorremos la cadena y contamos los caracteres buscados.
    }
    cout<<"\n===================================================================================================================================================================================\n"<<endl;
    archivo.close();    //Cerramos el archivo.
    mostrar(); //Mostramos los resultaos obtenidos.
}

//Funcion que realiza el conteo de cada caracter
void contador(string a){
    string temp, temp2, variable="";
    int aux;
    for(int i=0;i<a.length();i++){  //Recorremos y contamos cada caracter.
        string c;
        c.push_back(a[i]); //convertimos el caracter leido a string
        temp=c; //le concatenamos el caracter a temp
        if(operadores.count(c)){ //si el caracter esta en nuestro set incrementaremos ese caracter 
            string cad;
            cad.push_back(a[i+1]);  //convertimos el siguiente caracter a string
            temp.append(cad);   //lo concatenamos a temp
            
            if(operadores.count(temp)){ // verificamos si es un operador o comparador de dos caracteres
                caracteres[temp]+=1;//incrementamos en uno ese operador o comparador
            }else{ //se accede cuando el primer caracter es valido, pero el segundo no. Ejemplo:  1+1    solo se tomaria el + y no +1
                string d;
                d.push_back(temp[0]); //convertimos a string unicamente el primer caracter
                caracteres[d]+=1; // incrementamos e
            }
            i++; //incrementamos el i ya que ya verificamos el segundo operador
            temp="";//limpiamos el valor de temp
        }
        /*
        if(digitos.count(c)){
            aux=i; 
            string numero="", cadena="";
            cadena.push_back(a[aux]);
            while(digitos.count(cadena)){
                numero+=a[aux];
                aux++;
                cadena="";
                cadena.push_back(a[aux]);
            }
            caracteres[numero]+=1;
            tipo[numero]="Numero";
        }*/
    }

    //Funcion para buscar identificadores
    temp2="";
    for(int i=0;i<a.length();i++){  //Recorremos cada renglon del documento
        if(a[i]==' '){  //si es un espacio en blanco dejamos de concatenar
            if(variables.count(temp2)){ //comprobamos si la cadena es un tipo de variable
                if(a[i+1]==' ')
                    i++;    
                nombre(a, i, variable); //obtenemos el nombre del variable
                i+=variable.size(); //avanzamos hasta el final del nombre de la variable
                caracteres[variable]+=1;//incrementamos el contador del nombre del variable
                tipo[variable]= "Identificador";
                variable="";
                int l=i+1;
                while(a[l]!=';'){ //verificamos si hay mas variables del mismo tipo declaradas en la misma linea
                    while(a[l]!=','){ //avanzamos hasta el nombre de la variable
                        if(l>=a.length()-1 or a[l]==';')
                            break;
                        l++;
                    }
                    if(a[l]==';'){
                        break;
                    }else if(a[l+1]==' '){
                        l++;
                        
                    }
                    variable="";
                    nombre(a, l, variable);
                    if(variables.count(variable)){
                        l++;
                        l+=variable.size(); //avanzamos hasta el final del nombre de la variable
                        variable="";
                        nombre(a,l,variable);    
                    }
                    if(l!=a.length()-1){
                        l+=variable.size(); //avanzamos hasta el final del nombre de la variable
                        caracteres[variable]+=1;//incrementamos el contador del nombre del variable
                        tipo[variable]= "Identificador";//asignamos el tipo a identificador
                    }
                    variable=" "; //limpiamos
                    if(l>=a.length()-1 or a[l+1]==';')
                        break;
                    l++;
                } 
                i=l;
            }
            temp2="";//limpiamos
        }else{ //concatenamos cada caracter
            //comparamos si es un identificador 
            temp2.push_back(a[i]);
            string g="", h="";
            if(i+1<=a.length()-1)
                g.push_back(a[i+1]);
            if(i+2<=a.length()-1)   
                h.push_back(a[i+2]);
            if(caracteres.count(temp2) and tipo[temp2] == "Identificador" and (operadores.count(g) or operadores.count(h))){ //verificamos si ese conjunto de caracteres es un identificador 
                caracteres[temp2]+=1;
            }
        }
    }
    
}

//Funcion para conocer el nombre de la variable
void nombre(string a, int i, string &variable){
    int j=i+1;
        while((a[j]!= ' ') and (a[j]!= ';') and (a[j]!=',') and (a[j]!='=')){       //concatenamos hasta un espacio, un punto y coma o una coma
            variable.push_back(a[j]);
            j++;
            if(j>=a.length())
                break;
        }
}

//Funcion que muestra los resultados obtenidos por el programa
void mostrar(){
    for(auto x: caracteres){
        cout<<"\t ->    "<<x.first<<"    tiene "<<x.second<<" y es de tipo: "<< tipo[x.first]<<"."<<endl;
    }
    cout<<"\n";
}

