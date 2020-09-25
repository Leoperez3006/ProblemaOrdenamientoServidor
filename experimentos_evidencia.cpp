#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
/*
* J. Leonanardo Pérez Gonzalez
* 13 de septiembre del 2020
* Actividad integradora
*/

using namespace std;
vector <string> finalVector;

////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion que recibe un vector y lo imprime
*/
void printV(vector<string> myVector) {
    for (int i = 0; i <= myVector.size() - 1; i++) {
        cout << myVector[i] << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion que recibe un vector, dos parametros e imprime el vector entre esos dos parametros
i es el parametro menor
j es el parametro mayor
*/
void printV2(vector <string> v, int i, int j) {
    for (i; i < j; i++)
        cout << v[i] << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion que lee el archivo de "bitacora.txt" y lo convierte en un vector 
que se utilizara a lo largo del programa
*/
vector <string> createVector() {
    ifstream file;
    string line;
    file.open("bitacora.txt", ios::in);
    vector <string> vectorTemp;

    if (file.fail()) {
        cout << "No se encontró el archivo" << endl;
        exit(1);
    }
    //for (int i = 0; i < 30; i++) {
    while (!file.eof()) {
        getline(file, line);
        vectorTemp.push_back(line);
    }
    return vectorTemp;
}
////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion que recibe un vector ordenado, y lo escribe en un archivo de texto
*/
void createFile(vector <string> v) {
    ofstream file;
    file.open("BitacoraOrdenada.txt", ios::out);

    if (file.fail()) {
        cout << "Error critico" << endl << "No se puede crear el archivo" << endl;
        exit(1);
    }
    for (int i = 0; i < v.size() - 1; i++) {
        file << v[i] << endl;
    }
    file.close();
}
////////////////////////////////////////////////////////////////////////////////////////////
/*
* Funcion que recibe un vector, y ordena los segundos dentro de un dia
*/
void sortSec(vector<string> arreglo) {
    sort(arreglo.begin(), arreglo.end());
    for (int i = 0; i < arreglo.size(); i++) {
        //cout << "/// " << i << "///" << arreglo[i] << endl;
        finalVector.push_back(arreglo[i]);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion que recibe el vector, y ordena los dias dentro de un mes
*/
void sortMonthDay(vector<string> arreglo) {
    sort(arreglo.begin(), arreglo.end());
    for (int j = 0; j < 12; j++) {
        vector <string> vectorTemp;
        for (int i = 0; i < arreglo.size(); i++) {
            if (stoi(arreglo[i].substr(4, 6)) == j) {
                vectorTemp.push_back(arreglo[i]);
            }
        }
        sortSec(vectorTemp);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void sortData(vector <string> monthArray, vector <string> vectorTemp ) {
    vector <string> sortedMonths;
    for (int k = 0; k < 11; k++) {
        for (int j = 0; j < vectorTemp.size(); j++) {
            if (vectorTemp[j].substr(0, 3) == monthArray[k]) {
                sortedMonths.push_back(vectorTemp[j]);
            }
        }
    }

    for (int j = 0; j < 11; j++) {
        vector <string> vectorTemp2;
        for (int i = 0; i < sortedMonths.size(); i++) {
            if (monthArray[j] == sortedMonths[i].substr(0, 3)) {
                vectorTemp2.push_back(sortedMonths[i]);
            }
        }
        sortMonthDay(vectorTemp2);
    }

}
////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion que recibe el vector, un mes y un dia, y los ordena
*/
int indexSearch(vector <string> v, string month, int day) {
    int i = 0;
    while (i < v.size() - 1) {
        string tempMonth = v[i].substr(0, 3);
        int tempDay =stoi( v[i].substr(4, 6));
        if (month == tempMonth && day ==tempDay) {
            return i;
        }

        else {
            i++;
        }
    }
}
/*
Funcion que pide al usuario lo rangos de hora en que va a buscar 
*/
void ask(vector <string> v) {
    string month, temp;
    int day;
    int i, j;

    cout << "Escriba el primer mes en el formato adecuado" << endl;
    cin >> month;
    cout << "Escriba el primer dia" << endl;
    cin >> day;
    i = indexSearch(v, month, day);

    cout << "Escriba el segundo mes en el formato adecuado" << endl;
    cin >> month;
    cout << "Escriba el segundo dia" << endl;
    cin >> day;
    j = indexSearch(v, month, day+1);

    printV2(v,i,j);
}
////////////////////////////////////////////////////////////////////////////////////////////
/*
Funcion main
Manda a llamar a las funciones mas escenciales
*/
int main() {
    vector <string> vectorTemp;
    vector <string> months= { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
    
    vectorTemp = createVector();
    sortData(months, vectorTemp);
    createFile(finalVector);
    ask(finalVector);
    
    return 0;
}
