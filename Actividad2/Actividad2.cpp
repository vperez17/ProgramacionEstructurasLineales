#include <iostream>
#include <fstream>
using namespace std;

struct student{
    string date;
    string hour;
    string email;
    string name;
    string lastName;
    bool repeat;     //Si = 0 - No = 1
    int fileNumber;
    string github;
    int level;
    bool expo;      //Si = 0 - No = 1
    bool act1;      //Si = 0 - No = 1
    int month;
    int year;
    bool online; //Presencial = 0 - Online = 1

    student *next;
};

ofstream fout("../Caracteristicas.txt");

void createList(student *&list);
void emptyList(student *&list);
void olderStudent(student *list);
void birthday(student *list, int month);
void fileOdd(student *list);
void filePair(student *list);
void deliveryAct(student *list);
void assistanceClass(student *list);
void assistanceOnline(student *list);

void createList(student *&list) {
    ifstream read("../Alumnos.txt");
    try{
        while(!read.eof()){
            student *aux= new student();
            read >> aux->date >> aux->hour >> aux->email >> aux->name >> aux->lastName >> aux->repeat >> aux->fileNumber >> aux->github >>
            aux->level >> aux->expo >> aux->act1 >> aux->month >> aux->year >> aux->online;
            //una vez leido el fichero imprimimos los datos
            cout <<aux->date<<" "<<aux->hour<<" "<<aux->email<<" "<<aux->name<<" "<<aux->lastName<<" "<<aux->repeat<<" "<<aux->fileNumber<<" "<<
            aux->github<<" "<<aux->level<<" "<<aux->expo<<" "<<aux->act1<<" "<<aux->month<<" "<<aux->year<<" "<<aux->online<<endl;
            if (list==NULL){
                list = aux;
                aux->next = NULL;
            }else{
                aux->next = list;
                list = aux;
            }
        }
    }catch(...){
        read.close();
        cout<<"El archivo no se ha podido leer."<<endl;
    }
    if(list!=NULL){
        cout<<" "<<endl;
        cout<<"Se ha creado una lista con los datos anteriores. Cada alumno es un nodo de nuestra lista"<<endl;
    }
}
void emptyList(student *&list){
    student *aux = list;
    student *remove;

    if(list->next == NULL){
        delete(list);
        return;
    }

    do{
        remove = aux;
        list = aux->next;
        aux = list;
        delete(remove);
    }while(list != NULL);

    if (list ==NULL){
        cout<<"Lista vacia.";
    }
}
void olderStudent(student *list) {
    int oldYear = 2100;
    int oldMonth = 13;
    student *aux;
    do{
        if((list->year) <= oldYear){
            oldYear = list->year;
            if((list->year) == oldYear && (list->month) < oldMonth){
                oldMonth = list->month;
            }
            aux = list;
        }
        list=list->next;
    }while(list != NULL);
    fout<<"El alumno mas mayor de la clase es: "<<endl;
    fout <<"   "<<aux->email<<" "<<aux->name<<" "<<aux->lastName<<" "<<aux->repeat<<" "<<aux->fileNumber<<" "<<
         aux->github<<" "<<aux->level<<" "<<aux->expo<<" "<<aux->act1<<" "<<aux->month<<" "<<aux->year<<" "<<aux->online<<endl;
    fout<<"   "<<endl;
}
void birthday(student *list, int month) {
    fout<<"Los alumnos que cumplen anios en el mes "<<month<<" son:"<<endl;;
    do{
        if((list->month)==month){
            fout <<"   "<<list->email<<" "<<list->name<<" "<<list->lastName<<" "<<list->repeat<<" "<<list->fileNumber<<" "<<list->github<<" "
                 <<list->level<<" "<<list->expo<<" "<<list->act1<<" "<<list->month<<" "<<list->year<<" "<<list->online<<endl;
        }
        list=list->next;
    }while(list != NULL);
    fout<<"   "<<endl;
}
void fileOdd(student *list) {
    fout<<"Alumnos con expediente impar: "<<endl;
    do{
        if((list->fileNumber)%2 == 1){
            fout <<"   "<<list->email<<" "<<list->name<<" "<<list->lastName<<" "<<list->repeat<<" "<<list->fileNumber<<" "<<list->github<<" "
                 <<list->level<<" "<<list->expo<<" "<<list->act1<<" "<<list->month<<" "<<list->year<<" "<<list->online<<endl;
        }
        list = list->next;
    }while(list != NULL);
    fout<<"   "<<endl;
}
void filePair(student *list) {
    fout<<"Alumnos con expediente par: "<<endl;
    do{
        if((list->fileNumber)%2 == 0){
            fout <<"   "<<list->email<<" "<<list->name<<" "<<list->lastName<<" "<<list->repeat<<" "<<list->fileNumber<<" "<<list->github<<" "
                 <<list->level<<" "<<list->expo<<" "<<list->act1<<" "<<list->month<<" "<<list->year<<" "<<list->online<<endl;
        }
        list = list->next;
    }while(list != NULL);
    fout<<"   "<<endl;
}
void deliveryAct(student *list) {
    fout<<"Alumnos que entregaron la actividad: "<<endl;
    float sumbitAct = 0;
    float students = 0;
    do{
        if((list->act1)==false){
            fout <<"   "<<list->email<<" "<<list->name<<" "<<list->lastName<<" "<<list->repeat<<" "<<list->fileNumber<<" "<<list->github<<" "
                 <<list->level<<" "<<list->expo<<" "<<list->act1<<" "<<list->month<<" "<<list->year<<" "<<list->online<<endl;
            sumbitAct++;
        }
        list = list->next;
        students++;
    }while(list != NULL);
    float average;
    average = (sumbitAct/students)*100;
    cout<<"Han entregado la actividad el "<<average<<"% de los alumnos, es decir "<<sumbitAct<<" de "<<students<<" alumnos."<<endl;
    fout<<"  Porcentaje:"<<endl;
    fout<<"    Han entregado la actividad el "<<average<<"% de los alumnos, es decir "<<sumbitAct<<" de "<<students<<" alumnos."<<endl;
    fout<<"  "<<endl;

}
void assistanceClass(student *list){
    fout<<"Alumnos que estan en clase de forma presencial:"<<endl;
    do{
        if((list->online)==false){
            fout <<"   "<<list->email<<" "<<list->name<<" "<<list->lastName<<" "<<list->repeat<<" "<<list->fileNumber<<" "<<list->github<<" "
                 <<list->level<<" "<<list->expo<<" "<<list->act1<<" "<<list->month<<" "<<list->year<<" "<<list->online<<endl;
        }
        list=list->next;
    }while(list != NULL);
    fout<<"  "<<endl;
}
void assistanceOnline(student *list) {
    fout<<"Alumnos que estan en clase de forma online:"<<endl;
    do{
        if((list->online)==true){
            fout <<"   "<<list->email<<" "<<list->name<<" "<<list->lastName<<" "<<list->repeat<<" "<<list->fileNumber<<" "<<list->github<<" "
                 <<list->level<<" "<<list->expo<<" "<<list->act1<<" "<<list->month<<" "<<list->year<<" "<<list->online<<endl;
        }
        list=list->next;
    }while(list != NULL);
    fout<<"  "<<endl;
}

int main() {
    student *header = NULL;

    int month, opt;

    cout<<"Lista de alumnos de clase con sus caracteristicas."<<endl;
    cout<<" "<<endl;
    createList(header);
    cout<<" "<<endl;

    cout<<"   UNIVERSIDAD EUROPEA DE MADRID"<<endl;
    cout<<"           Victor Perez "<<endl;
    cout<<"      *** MENU PRINCIPAL ***"<<endl;
    cout<<" 1/ Persona mas mayor de la clase"<<endl;
    cout<<" 2/ Personas que cumplen anios un mes indicado"<<endl;
    cout<<" 3/ Personas con expediente impar"<<endl;
    cout<<" 4/ Personas con expediente par"<<endl;
    cout<<" 5/ Porcentaje de alumn@s que entregaron la Actividad1"<<endl;
    cout<<" 6/ Listado de asistencia a clase (presencial/virtual)"<<endl;

    do{
        cout<<"Introduzca una opcion.";
        cin>>opt;
        switch (opt) {
            case 1:
                cout<<"Buscando a la persona mayor de la clase..."<<endl;
                olderStudent(header);
                cout<<"Se ha anadido correctamente al fichero Caracteristicas.txt"<<endl;
                break;
            case 2:
                cout<<"Introduzca el mes que desee."<<endl;
                cin>>month;
                cout<<"Buscando personas que cumplen anios este mes..."<<endl;
                birthday(header,month);
                cout<<"Se ha anadido correctamente al fichero Caracteristicas.txt"<<endl;
                break;
            case 3:
                cout<<"Buscando personas con expediente impar..."<<endl;
                fileOdd(header);
                cout<<"Se ha anadido correctamente al fichero Caracteristicas.txt"<<endl;
                break;
            case 4:
                cout<<"Buscando personas con expediente par..."<<endl;
                filePair(header);
                cout<<"Se ha anadido correctamente al fichero Caracteristicas.txt"<<endl;
                break;
            case 5:
                cout<<"Buscando personas que entregaron la Actividad1..."<<endl;
                deliveryAct(header);
                cout<<"Se ha anadido correctamente al fichero Caracteristicas.txt"<<endl;
                break;
            case 6:
                cout<<"Asistencia a clase (presencial/virtual)."<<endl;
                cout<<"Buscando personas que estan en presencial..."<<endl;
                assistanceClass(header);
                cout<<"Buscando personas que estan en online..."<<endl;
                assistanceOnline(header);
                cout<<"Se ha anadido correctamente al fichero Caracteristicas.txt"<<endl;
                break;
            case 0:
                emptyList(header);
                cout<<"Ha salido del programa."<<endl;
                break;
        }
    }while(opt!=0);
}
