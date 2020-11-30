#include <iostream>
#include <fstream>
using namespace std;

struct pueblo{
    int cp;
    string municipio;
    int poblacion;
    int altura;
    int superficie;

    pueblo *sig;
};


void crearLista(pueblo *&list);
void crearLista(pueblo *&list) {
    ifstream read("../avila.tsv");
    try{
        while(!read.eof()){
            pueblo *aux= new pueblo();
            read >> aux->cp >> aux->municipio >> aux->poblacion >> aux->altura >> aux->superficie;
            //una vez leido el fichero imprimimos los datos
           //cout << aux->cp << aux->municipio << aux->poblacion << aux->altura << aux->superficie<<endl;
            if (list==NULL){
                list = aux;
                aux->sig = NULL;
            }else{
                aux->sig = list;
                list = aux;
            }
        }
    }catch(...){
        read.close();
        cout<<"El archivo no se ha podido leer."<<endl;
    }
}

void contarMunicipios(pueblo *list);
void contarMunicipios(pueblo *list){
    int municipios = 0;
    while(list!=NULL){
        municipios++;
        list = list->sig;
    }
    cout << "Hay " <<municipios<<" municipios"<<endl;
}

void promedioAltura(pueblo *list);
void promedioAltura(pueblo *list){
    int municipios = 0;
    float alturaTotal = 0;
    while(list!=NULL){
        municipios++;
        alturaTotal = alturaTotal + list -> altura;
        list = list->sig;
    }
    float alturaMedia = alturaTotal/municipios;
    cout<<"Altura media: "<<alturaMedia<<endl;
}

void alturaMaxima(pueblo *list);
void alturaMaxima(pueblo *list){
    int alturaMax = 0;
    while(list!=NULL){
        if(alturaMax <= list->altura){
            alturaMax = list->altura;
        }
        list = list->sig;
    }
    cout<<"La altura mayor es: "<<alturaMax<<endl;
}

void alturaMinima(pueblo *list);
void alturaMinima(pueblo *list){
    int alturaMin = 100000;
    while(list!=NULL){
        if(alturaMin >= list->altura){
            alturaMin = list->altura;
        }
        list = list->sig;
    }
    cout<<"La altura menor es: "<<alturaMin<<endl;
}

void menosPoblada(pueblo *list);
void menosPoblada(pueblo *list){
    pueblo *aux = new pueblo();
    int menosPob = 1000000;
    while(list!=NULL){
        if(menosPob >= list->poblacion){
            menosPob = list->poblacion;
            aux = list;
        }
        list = list->sig;
    }
    cout<<"Menos poblada: "<<aux->municipio<<endl;
}

void masPoblada(pueblo *list);
void masPoblada(pueblo *list){
    pueblo *aux = new pueblo();
    int menosPob = 0;
    while(list!=NULL){
        if(menosPob <= list->poblacion){
            menosPob = list->poblacion;
            aux = list;
        }
        list = list->sig;
    }
    cout<<"Mas poblada: "<<aux->municipio<<endl;
}

void masDensidad(pueblo *list);
void masDensidad(pueblo *list){
    pueblo *aux = new pueblo();
    float densiPueblo;
    float densidad = 0;
    while(list!=NULL){
        densiPueblo = list->poblacion / list->superficie;
        if(densidad <= densiPueblo){
            densidad = densiPueblo;
            aux = list;
        }
        list=list->sig;
    }
    cout <<"Mayor densidad: "<<aux->municipio<<endl;
}

void menosDensidad(pueblo *list);
void menosDensidad(pueblo *list){
    pueblo *aux = new pueblo();
    float densiPueblo;
    float densidad = 100000000000;
    while(list!=NULL){
        densiPueblo = list->poblacion / list->superficie;
        if(densidad >= densiPueblo){
            densidad = densiPueblo;
            aux = list;
        }
        list=list->sig;
    }
    cout <<"Menor densidad: "<<aux->municipio<<endl;
}

void poblacionAvila(pueblo *list);
void poblacionAvila(pueblo *list){
    float poblaTotal = 0;
    while(list!=0){
        poblaTotal = poblaTotal + list->poblacion;
        list = list->sig;
    }
    cout<<"Poblacion total de Avila: "<<poblaTotal<<endl;
    long poblaMadrid = 6507184;
    float supera = poblaMadrid / poblaTotal;
    cout<<"   Madrid supera en poblacion a Avila unas "<<supera<<" veces"<<endl;
}

void condicion(pueblo *list);
void condicion(pueblo *list){
    cout<<"10 pueblos con al menos 40 habitantes y a mas de 900 metro de altura"<<endl;
    int habitantes = 40;
    int altura = 900;
    int cont = 0;
    while(list!=NULL){
        if(habitantes <= list->poblacion && altura < list->altura && cont != 10){
            cout<<" "<<list->cp<<" "<<list->municipio<<" "<<list->poblacion<<" "<<list->altura<<" "<<list->superficie<<endl;
            cont++;
        }
        list = list->sig;
    }
}


int main() {
    pueblo *header = NULL;
    crearLista(header);

    cout<<"Examen parcial Victor Perez Perez"<<endl;

    cout<<"Mostrando numero de municipios: "<<endl;
    contarMunicipios(header);
    cout<<" "<<endl;
    cout<<"Mostrando media de altura de pueblo: "<<endl;
    promedioAltura(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipio con altura maxima: "<<endl;
    alturaMaxima(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipio con altura minima: "<<endl;
    alturaMinima(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipio menos poblado: "<<endl;
    menosPoblada(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipio mas poblado: "<<endl;
    masPoblada(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipios con mayor densidad: "<<endl;
    masDensidad(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipios con menor densidad: "<<endl;
    menosDensidad(header);
    cout<<" "<<endl;
    cout<<"Mostrando poblacion de Avila: "<<endl;
    poblacionAvila(header);
    cout<<" "<<endl;
    cout<<"Mostrando municipios que cumplen condiciones: "<<endl;
    condicion(header);


}
