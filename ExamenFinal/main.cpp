#include <iostream>
#include <fstream>
using namespace std;

//Estructura que almacena en memoria dinámica el contenido de cada una de las líneas del CSV
struct nodo{
    string provincia;
    string municipio;
    string localidad;
    int codigoPostal;
    string direccion;
    string margen;
    float longitud;
    float latitud;
    float precio95E5;
    float precio95E10;
    float precio95E5Premium;
    float precio98E5;
    float precio98E10;
    float precioGasoleoA;
    float precioGasoleoPremium;
    float precioGasoleoB;
    float precioGasoleoC;
    float precioBioetanol;
    float bioalcohol;
    float precioBiodiesel;
    float estermetilico;
    float precioGasesLicuados;
    float precioGasNaturalComprimido;
    float precioGasNaturalLicuado;
    float precioHidrogeno;
    string rotulo;
    string tipoVenta;
    string rem;
    string horario;
    string tipoServicio;

    nodo *next;
};

//Función para crear la lista con los datos del archivo
void crearLista(nodo *&lista, nodo *&final);
void crearLista(nodo *&lista, nodo *&final){
    //Indicamos al programa la dirección del archivo que tiene que leer
    ifstream read("../hoja_modificada_UK.tsv");
    try{
        //Mientras el archivo no esté vacío
        while(!read.eof()){
            nodo *actual= new nodo();
            //Creamos un nodo para indicar al programa los datos que se van a encontrar en el archivo y su orden respectivo
            read >>actual->provincia>>actual->municipio>> actual->localidad>> actual->codigoPostal>> actual->direccion>> actual->margen>> actual->longitud>> actual->latitud>> actual->precio95E5>>
                 actual->precio95E10>> actual->precio95E5Premium>> actual->precio98E5>> actual->precio98E10>> actual->precioGasoleoA>> actual->precioGasoleoPremium>>
                 actual->precioGasoleoB>> actual->precioGasoleoC>> actual->precioBioetanol>> actual->bioalcohol>> actual->precioBiodiesel>> actual->estermetilico>>
                 actual->precioGasesLicuados>> actual->precioGasNaturalComprimido>> actual->precioGasNaturalLicuado>> actual->precioHidrogeno>> actual->rotulo>>
                 actual->tipoVenta>> actual->rem>> actual->horario>> actual->tipoServicio;
            //Una vez leído el fichero añadimos el nodo a la lista
            if (lista==NULL){
                actual->next = NULL;
                lista = actual;
                final = actual;
            }else{
                final->next = actual;
                final = actual;
            }
        }
        //Si el archivo no se puede leer, salta la excepción
    }catch(...){
        read.close();
        cout<<"El archivo no se ha podido leer."<<endl;
    }
}

//Función para comparar las gasolineras y sacar las 10 más baratas
void gasolinera(nodo *list, string provincia, string municipio, string localidad);
void gasolinera(nodo *list, string provincia, string municipio, string localidad){
    //Creamos punteros y variables necesarias e inicializamos las necesarias
    nodo *comprobar = list;
    nodo *header1 = list;
    nodo *peque1;
    nodo *peque2;
    nodo *peque3;
    nodo *peque4;
    nodo *peque5;
    nodo *peque6;
    nodo *peque7;
    nodo *peque8;
    nodo *peque9;
    nodo *peque10;
    float barato = 10000000;
    float gasolinaActual;
    float precioFinal = 0;
    int contprovincia = 0;
    int contmunicipio = 0;
    int contlocalidad = 0;

    //Recorremos la lista y cada valor que introduzca el usuario y coincida con alguno de la lista, aumentará el contador
    do{
        if(comprobar->provincia == provincia){
            contprovincia++;
        }
        if(comprobar->municipio == municipio){
            contmunicipio++;
        }
        if(comprobar->localidad == localidad){
            contlocalidad++;
        }
        comprobar = comprobar->next;
    }while(comprobar != NULL);

    //Si todos los contadores son distintos de 0, el programa habrá encontrado la localización introducida por el usuario
    if(contprovincia != 0 && contmunicipio != 0 && contlocalidad != 0) {
        cout<<"Buscando gasolineras localizacion indicada..."<<endl;
        //Si algunos de los contadores es 0 significa que no todos los datos están en el fichero y volvemos al menú principal
    }else if(contprovincia == 0 || contmunicipio == 0 || contlocalidad == 0){
        cout<<"Estos datos no se encuentran, asegurese de que estan correctamente escritos (Mayusculas)"<<endl;
        return;
    }

    //Buscamos la primera gasolinera más barata
    header1 = list;
    do{
        //Recorremos la lista, y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0) {
                peque1=header1;
                precioFinal = peque1->precio95E5; barato = peque1->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Ninguna gasolinera tiene este tipo de gasolina."<<endl;
        cout<<" "<<endl;
        return;
    }
    //Mostramos los datos de la gasolinera más barata
    cout<<"Gasolineras mas baratas: "<<endl;
    cout<<"1/    Calle: "<< peque1->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque1->codigoPostal<<endl;
    cout<<" "<<endl;
    //Si se cumple esta condición, mostramos el mensaje correspondiente y volvemos al menú principal
    if(contlocalidad == 1){
        cout<<"En "<<localidad<<" solo existe una gasolinera."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la segunda gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad) {
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1) {
                peque2=header1;
                precioFinal = peque2->precio95E5; barato = peque2->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
//Si el valor precioFinal es igual a 0, mostramos el mensaje correspondiente y volvemos al menú principal
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina una vez."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"2/    Calle: "<< peque2->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque2->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 2){
        cout<<"En "<<localidad<<" solo existen dos gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la tercera gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2) {
                peque3=header1;
                precioFinal = peque3->precio95E5; barato = peque3->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina dos veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"3/    Calle: "<< peque3->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque3->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 3){
        cout<<"En "<<localidad<<" solo existen tres gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la cuarta gasolinera más barata
    //Actualizamos el valor de las variables necesarias

    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3) {
                peque4=header1;
                precioFinal = peque4->precio95E5; barato = peque4->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina tres veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"4/    Calle: "<< peque4->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque4->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 4){
        cout<<"En "<<localidad<<" solo existen cuatro gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la quinta gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3 && header1!=peque4) {
                peque5=header1;
                precioFinal = peque5->precio95E5; barato = peque5->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina cuatro veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"5/    Calle: "<< peque5->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque5->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 5){
        cout<<"En "<<localidad<<" solo existen cinco gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la sexta gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3
            && header1!=peque4 && header1!=peque5) {
                peque6=header1;
                precioFinal = peque6->precio95E5; barato = peque6->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina cuatro veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"6/    Calle: "<< peque6->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque6->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 6){
        cout<<"En "<<localidad<<" solo existen seis gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la quinta gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3
            && header1!=peque4 && header1!=peque5 && header1!=peque6) {
                peque7=header1;
                precioFinal = peque7->precio95E5; barato = peque7->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina seis veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"7/    Calle: "<< peque7->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque7->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 7){
        cout<<"En "<<localidad<<" solo existen siete gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la quinta gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3
            && header1!=peque4 && header1!=peque5 && header1!=peque6 && header1!=peque7) {
                peque8=header1;
                precioFinal = peque8->precio95E5; barato = peque8->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina siete veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"8/    Calle: "<< peque8->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque8->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 8){
        cout<<"En "<<localidad<<" solo existen ocho gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la quinta gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3 && header1!=peque4
            && header1!=peque5&& header1!=peque6 && header1!=peque7 &&header1!=peque8) {
                peque9=header1;
                precioFinal = peque9->precio95E5; barato = peque9->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina ocho veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"9/    Calle: "<< peque9->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque9->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 9){
        cout<<"En "<<localidad<<" solo existen nueve gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

    //Buscamos la quinta gasolinera más barata
    //Actualizamos el valor de las variables necesarias
    barato = 10000000;
    precioFinal = 0;
    header1 = list;
    do{
        //Recorremos la lista y cuando coincidan los datos inicializaremos la variable gasolinaActual con su precio correspondiente
        if((header1->provincia)==provincia && (header1->municipio)==municipio && (header1->localidad)==localidad){
            gasolinaActual = header1->precio95E5;
            if (gasolinaActual<= barato && gasolinaActual!=0 && header1!=peque1 && header1!=peque2 && header1!=peque3
            && header1!=peque4 && header1!=peque5 && header1!=peque6 && header1!=peque7 &&header1!=peque8 &&header1!= peque9) {
                peque10=header1;
                precioFinal = peque10->precio95E5; barato = peque10->precio95E5;
            }
        }
        header1 = header1->next;
    }while(header1!=NULL);
    if(precioFinal == 0){
        cout<<" "<<endl;
        cout<<"Esta localidad solo tiene este tipo de gasolina nueve veces."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"10/    Calle: "<< peque10->direccion<<"   Precio: "<<precioFinal<<"   Codigo Postal: "<< peque10->codigoPostal<<endl;
    cout<<" "<<endl;
    if(contlocalidad == 10){
        cout<<"En "<<localidad<<" solo existen diez gasolineras."<<endl;
        cout<<" "<<endl;
        return;
    }

}

//Gasolineras mas cercanas a la calle Toledo
void gasolineraToledo(nodo *lista);
void gasolineraToledo(nodo *lista){
    int contadorGasolineras = 0;
    do{
        if(lista->codigoPostal == 28005){
            contadorGasolineras++;
        }
        lista = lista->next;
    }while(lista!=NULL);
    cout<<"En el mismo codigo postal que la calle Toledo hay "<<contadorGasolineras<<" gasolineras"<<endl;
    cout<<" "<<endl;
}

//Gasolinera mas barata de madrid
void baratadeMadrid(nodo *lista);
void baratadeMadrid(nodo *lista){
    float barato = 10000000;
    nodo *aux;
    do{
        if (lista->provincia == "MADRID"){
            if(lista->precio95E5 <= barato && lista->precio95E5 != 0){
                barato = lista->precio95E5;
                aux = lista;
            }
        }
        lista = lista->next;
    }while (lista != NULL);
    cout<<"La estacion de servicio mas barata de Madrid esta en: "<<aux->direccion<<" con codigo postal: "<<aux->codigoPostal
    <<" con el precio de: "<<aux->precio95E5<<endl;
    cout<<" "<<endl;
}

//Gasolineras mas barata con Gasoleo A
void barataGasoleoA(nodo *lista);
void barataGasoleoA(nodo *lista){
    float barato = 10000000;
    nodo *aux;
    do{
        if (lista->precioGasoleoA <= barato && lista->precioGasoleoA!=0){
                barato = lista->precioGasoleoA;
                aux = lista;
        }
        lista = lista->next;
    }while (lista != NULL);
    cout<<"La gasolinera con GasoleoA mas barata esta en: "<<aux->municipio<<"("<<aux->provincia<<")"<<endl;
    cout<<" "<<endl;
}

//Gasolineras low-cost
void lowcost(nodo *lista);
void lowcost(nodo *lista){
    int contador = 0;
    int contadorNormal = 0;
    do{
        if(lista->municipio == "BARCELONA"){
            if(lista->rotulo == "REPSOL" ||lista->rotulo == "GALP" ||lista->rotulo == "CEPSA" ||lista->rotulo == "SHELL"){
                contadorNormal++;
            }
            contador++;
        }
        lista = lista->next;
    }while(lista!=NULL);
    int lowcost = contador - contadorNormal;
    cout<<"De las "<<contador<<" gasolineras que hay en el municipio de Barcelona: "<<endl;
    cout<<"   Gasolineras comunes (no lowcost) -> "<<contadorNormal<<endl;
    cout<<"   Gasolineras lowcost -> "<<lowcost<<endl;
    cout<<" "<<endl;

}

int main() {
    //Creamos una lista vacía
    nodo *header = NULL;
    nodo *final =NULL;
    crearLista(header, final);
    //creamos las variables necesarias
    string provinciaPedida, municipioPedido, localidadPedida;
    int opt;

    cout<<"EXAMEN FINAL PEL VICTOR PEREZ 21923658"<<endl;
    cout << "-------------------------------------------------" << endl;
    cout << "      Bienvenido al buscador de gasolineras" << endl;
    cout << "-------------------------------------------------" << endl;

    do{
        cout<<"1/ Gasolineras afectadas cerca de la calle Toledo (Madrid)"<<endl;
        cout<<"2/ 10 Gasolineras mas baratas"<<endl;
        cout<<"3/ Gasolinera mas barata de Madrid"<<endl;
        cout<<"4/ GasoleoA mas barato de Espana"<<endl;
        cout<<"5/ Gasolineras lowcost en Barcelona"<<endl;

        cout<<"Ingrese una opcion: "<<endl;
        cin>>opt;

        switch(opt){
            case 1:
                cout<<"Mostrando gasolineras afectadas por la explosion cerca de la calle Toledo..."<<endl;
                gasolineraToledo(header);
                break;

            case 2:
                cout<<"Ingrese la provincia: "<<endl;
                cin>>provinciaPedida;
                cout<<"Ingrese el municipio: "<<endl;
                cin>>municipioPedido;
                cout<<"Ingrese la localidad: "<<endl;
                cin>>localidadPedida;
                cout<<"Buscando 10 gasolineras mas baratas..."<<endl;
                gasolinera(header, provinciaPedida, municipioPedido, localidadPedida);
                break;
            case 3:
                cout<<"Calculando estacion mas barata de Madrid..."<<endl;
                baratadeMadrid(header);
                break;
            case 4:
                cout<<"Buscando gasolinera con GasoleoA mas barato en Espana..."<<endl;
                barataGasoleoA(header);
                break;
            case 5:
                cout<<"Buscando gasolineras low cost..."<<endl;
                lowcost(header);
                break;
        }

    }while(opt!=0);

}
