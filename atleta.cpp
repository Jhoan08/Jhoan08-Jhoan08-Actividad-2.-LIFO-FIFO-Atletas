//Librerias
#include <iostream>
#include <malloc.h> //Asigna memoria
#include <cstdlib> //Asigna numeros

using namespace std;

//Estructura del atleta - Fifo
struct atleta{
    char nombre[30];
    int numero;
    float Tvueltas[100];
    int cantidadTiempos;
    int rondas;
    double promedioT;
    atleta *sig;
};

 //Estructura Promedio - Lifo
struct promedio
{
    int numero;
    double promedioT;
    promedio *sigP;
};


//Apuntadores de las Estructuras
atleta *cab, *aux, *aux2;
promedio *cabP, *auxP;


int Natletas = 0; //Define el numeros de atletas

//Funcion Registrar - Fifo
int registrar(){
    int volver = 0;
    cout<<"Bienvenido al area de registro"<<endl;
    cout<<"\n";
    do{
        if (cab==NULL){
            //Pide memoria
            cab = (struct atleta *) malloc (sizeof(struct atleta)); //P
                
            cout<<"Ingresa el nombre del atleta: "<<endl;
            cin>>cab->nombre;
            cab-> sig = NULL;
            cout<<"\n";

            cab->numero = rand() %100;
            cout<<"El sigiente numero se le asignara al atleta "<<cab->nombre<<": "<<cab->numero<<endl;
            cab->sig = NULL;

            cab->rondas = 0;
            cab->sig = NULL;

            cab->cantidadTiempos = 0;
            cab->sig = NULL;
                
        } else{
            //Pide memoria si ya hay un atleta registrado
            aux = (struct atleta *) malloc (sizeof(struct atleta));
                
            cout<<"Ingresa el nombre del siguiente atleta: "<<endl;
            cin>>aux->nombre;
            aux->sig = NULL;
            cout<<"\n";

            aux->numero = rand() % 100;
            cout<<"El sigiente numero se le asignara al atleta "<<aux->nombre<<": "<<aux->numero<<endl;
            aux->sig = NULL;

            aux->rondas = 0;
            aux->sig = NULL;

            aux->cantidadTiempos = 0;
            aux->sig = NULL;

            aux2 = cab;
            while (aux2->sig!=NULL)    
                aux2 = aux2->sig;
                aux2->sig = aux;
                aux2 = aux = NULL;
                free(aux);
                free(aux2);
        }
        Natletas ++;
        cout<<"\n";
        cout<<"Atleta Registrado."<<endl;
        cout<<"\n";
        cout<<"Desea registrar otro atleta? (1.SI/2.NO)";
        cin>>volver;
    }while(volver!=2);
    return 0;
}

//Funcion Promedio - lifo
int PromedioT(){
    //Pide Memoria
    auxP = (struct promedio *) malloc (sizeof(struct promedio));
    auxP->promedioT = aux->promedioT;
    auxP->numero = aux->numero;
    if(cabP==NULL){
        cabP = auxP;
        cabP->sigP = NULL;
    }else{
        auxP->sigP =cabP;
        cabP = auxP;
    }
    auxP = NULL;
    free(auxP); 
    return 0;  
}

//Funcion registrar Tiempo de los atletas
int RegistrarTiempo(){
    int volver = 0;
    int buscar = 0;
    int encontrado = 0;
    double tiemposActuales = 0;
    double tiemposVueltas = 0;
    double tiempo = 0;
    int otraVuelta = 0;
    int Nvueltas = 0;
    if(cab != NULL){
        do{
            cout<<"Bienvenido al area de registro del tiempo del atleta"<<endl;
            cout<<"Digita el numero del corredor:"<<endl;
            cin>>buscar;
            aux = cab;
            while (aux!=NULL){
                if(aux->numero == buscar){
                    cout<<"Nombre: "<<aux->nombre<<", Numero: "<<aux->numero<<endl;
                    if(aux->rondas == 0){
                        do{
                            Nvueltas++;
                            cout<<"Ingresa el tiempo que duro el atleta en la vuelta #"<<Nvueltas<<endl;
                            cin>>tiempo;
                            aux->Tvueltas[aux->cantidadTiempos] = tiempo;
                            aux->cantidadTiempos++;
                            tiemposVueltas = tiemposVueltas + tiempo;
                            cout<<"Desea dar otra vuelta? (1.SI/2.NO)"<<endl;
                            cin>>otraVuelta;
                        }while(otraVuelta!=2);
                        aux->rondas = Nvueltas;
                        if(Nvueltas != 1)
                        {
                            aux->promedioT = tiemposVueltas/Nvueltas;
                            Nvueltas = 0;
                            tiemposVueltas =0;
                            PromedioT(); 
                        }
                    }else{
                        do{
                            Nvueltas++;
                            cout<<"Ingresa el tiempo que duro el atleta en esta vuelta:"<<endl;
                            cin>>tiempo;
                            aux->Tvueltas[aux->cantidadTiempos] = tiempo;
                            aux->cantidadTiempos++;
                            cout<<"Desea dar otra vuelta? (1.SI/2.NO)"<<endl;
                            cin>>otraVuelta;
                        }while(otraVuelta!=2);
                        aux->rondas = aux->rondas + Nvueltas;
                        for (int i = 0; i < aux->rondas; i++) 
                        {
                            tiemposActuales = tiemposActuales + aux->Tvueltas[i];
                        }
                        aux->promedioT = tiemposActuales/aux->rondas;
                        Nvueltas = 0;
                        tiemposActuales = 0;
                        PromedioT();
                    }            
                        cout<<"El registro ha sido exitoso"<<endl;
                        system("pause");
                    encontrado = 1;
                }
                aux = aux->sig;
            }
            if(encontrado == 0)
            {
            cout<<"No hay ningun atleta con ese numero..."<<endl;  
            }
            encontrado = 0;
            cout<<"Desea registrar el tiempo de otro atleta? (1.SI/2.NO)"<<endl;
            cin>>volver;
        }while(volver!=2);
    }else{
        cout<<"No Se han registrado atletas..."<<endl;
    }
    return 0;
}

//Funcion Tabla Promedio
int tablaP(){
    int i,j,Cambiar2;
    float Cambiar;
    double Promedio[Natletas];
    int NumeroA[Natletas];
    int indicador = 0;
    if(cab!= NULL){
        //Almacena todos los promedios en una variable
        for(aux=cab; aux != NULL; aux = aux->sig){
            Promedio[indicador] = aux->promedioT;
            NumeroA[indicador] = aux->numero;
            indicador++;
        }
        indicador = 0;
        //Se utiliza el metodo burbuja
        for(i=0;i<Natletas;i++){
            for(j=0;j<Natletas;j++){
                if(Promedio[j] > Promedio[j+1]){
                    Cambiar = Promedio[j];
                    Cambiar2 = NumeroA[j];

                    Promedio[j] = Promedio[j+1];
                    NumeroA[j] = NumeroA[j+1];
                    
                    Promedio[j+1] = Cambiar;
                    NumeroA[j+1] =Cambiar2;
                }
            }
        }
        cout<<"Tabla"<<endl;
        cout<<"---------------------------"<<endl;
        for(i=Natletas;i>=1;i--){
            cout<<"-> Atleta Numero: "<<NumeroA[i]<<" - promedio: "<<Promedio[i]<<endl;
        }
        system("pause");
    }else{
        cout<<"Vacio..."<<endl;
        cout<<"No ha comenzado la competencia."<<endl;
        system("pause");
    }
    return 0;
}

//Funcion Mostrar datos
int mostrar(){
    int Nvueltas = 0;
    if(cab!=NULL){
        cout<<"Bienvenido"<<endl;
        for (aux=cab; aux!=NULL; aux = aux->sig)
        {
            cout<<"Nombre: "<<aux->nombre<<endl;
            cout<<"Numero: "<<aux->numero<<endl;
            if(aux->rondas != 0){
                cout<<"Tiempo: "<<endl;
                for (int i = 0; i < aux->rondas; i++) {
                    Nvueltas++;
                    cout<<"Vuelta #" << Nvueltas << ": " << aux->Tvueltas[i] << endl;
                }
                if(aux->rondas != 1)
                {
                    cout<<"El promedio de sus tiempo es: "<<aux->promedioT<<endl;
                }else{
                    cout<<"Este atleta no tiene promedio, ya que solo hizo una vuelta..."<<endl;
                }
            }else{
                cout<<"Este atleta no ha hecho vueltas..."<<endl;
            }
            
            cout<<"\n";
            Nvueltas = 0;
        }
        system("pause");
    }else{
        cout<<"Vacio..."<<endl;
        cout<<"No Se han registrado atletas..."<<endl;
        system("pause");
    }
    return 0;
}

//Funcion Eliminar Estructura atleta y promedio
int eliminarA(){
    aux = cab;
    cab = cab->sig;
    free(aux);
    auxP = cabP;
    cabP = cabP->sigP;
    free(auxP);  
    if(cab!=NULL){
        eliminarA();
    }
}

//Funcion Terminar o no la competencia
int Estado(){
    if(cab != NULL){
        int borrar = 0;
        cout<<"La competencia a terminado?"<<endl;
        cout<<"1.Si --> Eliminar atletas."<<endl;
        cout<<"2.No --> Se conserva atletas."<<endl;
        cin>>borrar;
        if (borrar == 1)
        {
            eliminarA();
            cout<<"Atletas eliminados..."<<endl;
            system("pause");
        }else{
            cout<<"Datos Conservados..."<<endl;
            system("pause");
        }
    }else{
        cout<<"No se han registrado atletas..."<<endl;
    }
    return 0;
}

//Menu
int main(){
    int opc = 0;
    do{
        cout<<"\nMenu"<<endl;
        cout<<"1. Registrar atleta"<<endl;
        cout<<"2. Registrar tiempo de los atletas"<<endl;
        cout<<"3. Tabla del promedio de cada atleta"<<endl;
        cout<<"4. Mostrar datos"<<endl;
        cout<<"5. Estado de la competencia (Eliminar atleta)"<<endl;
        cout<<"6. Salir"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: registrar(); break;
            case 2: RegistrarTiempo(); break;
            case 3: tablaP(); break;
            case 4: mostrar(); break;
            case 5: Estado(); break;
            case 6: cout<<"Adios"; break;
            default:cout<<"Opcion Invalidad."; break;
        }
    }while(opc!=6);

}