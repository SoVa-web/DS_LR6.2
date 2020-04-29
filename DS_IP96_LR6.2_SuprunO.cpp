#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

class Graph {
  public:
    void init(int lines, int stones, int**& A);
    void reading();
    void adjencency();
    void outputMatrix(int a1, int a2, int**& A);
    void initArrColor(int*&C);
    void glueing(int glue1, int glue2, int**&A);
    void algorithm(int*&C, int**& A);
    void coloring(int glue1, int glue2,int*&C);
    void clearing();
//varieties
    int versh, rebra;
    int** listRibs;
    int** adjMatrix;
    int* colors;
    int* tempColor;
    int** tempAdj;
};

bool check(int**A, int v) {
    for(int i = 0; i< v; i ++) {
        for(int j = 0; j <v; j++) {
            if(A[i][j] == 0)
                return false;
        }
    }
    return true;
}

void outputResult(int*C, int versh) {
    int chromNumber = 0;
    for(int i = 0; i<versh; i++) {
        cout<<" the top of the graph "<<i+1<<" have color "<<C[i]<<endl;
        if(C[i] > chromNumber)
            chromNumber = C[i];
    }
    cout<<" Chromatic number is : "<<chromNumber+1;
}

void Graph::glueing(int glue1, int glue2, int**&A) {
    if(glue1 != -1) {
        for(int i = 0; i < versh; i++) {//склеюЇмо вершини, розставл€ючи 1 в матриц≥ сум≥жност≥
            if(A[glue1][i] == 1)
                tempAdj[i][glue2] = tempAdj[glue2][i]=1;
            if(A[glue2][i] == 1)
                tempAdj[i][glue1] = tempAdj[glue1][i]=1;
        }
    }
}

void Graph::coloring(int glue1, int glue2,int*&C) {
    if(glue1<glue2) //присвоюЇмо вершинам один кол≥р
        tempColor[glue2] = C[glue1];//за принципом меншого ≥ндекca
    else
        tempColor[glue1] = C[glue2];
}

void Graph::algorithm(int*&C, int**& A) {
    tempAdj = A;
    tempColor = C;
    if(check(A, versh) == false) {
        int glue1 = -1;//вершини €к≥ будемо склеювати
        int glue2 = -1;
        for(int i = 0; i< versh; i ++) {//шукаЇмо вершини , що будемо склеювати
            for(int j = 0; j <versh; j++) {
                if(A[i][j] == 0) {
                    glue1 = i;
                    glue2 = j;
                    tempAdj[i][j] = 1;
                    coloring(glue1, glue2,C);
                    break;
                }
            }
            if(glue1 != -1)
                break;
        }
        glueing(glue1, glue2,A);
        algorithm(tempColor, tempAdj);
    } else {
        outputResult(C, this->versh);
    }
}

void Graph::initArrColor(int*&C) {
    C = new int[this->versh];
    for(int i = 0; i < this->versh; i++) {
        C[i] = i;
    }
}

void Graph:: init(int lines, int stones, int**& A) {
    A = new int*[lines];
    for(int i = 0; i < lines; i++) {
        A[i] = new int[stones];
    }
}

void Graph::reading() { //читаЇмо дан≥ з файлу
    ifstream inn;
    inn.open("list.txt");
    inn>>versh;
    cout<<" Number nodes :"<<versh<<endl;
    inn>>rebra;
    cout<<" Number of ribs : "<<rebra<<endl;
    init(this->rebra, 2, this->listRibs);
    for(int i = 0; i < this->rebra; i++) {
        for(int j = 0; j < 2; j++) {
            inn>>listRibs[i][j];
        }
    }
    cout<< " List of ribs : "<<endl;
    outputMatrix(this->rebra, 2, this->listRibs);
    cout<<"============================================"<<endl;
    adjencency();
    cout<<"============================================"<<endl;
    initArrColor(this->colors);
    initArrColor(tempColor);
    init(versh, versh, tempAdj);
    inn.close();
}

void Graph::adjencency() {
    init(this->versh, this->versh, this->adjMatrix);
    for(int i = 0 ; i < this->versh; i++) {
        for(int j = 0 ; j < this->versh; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    for(int i = 0; i < this->rebra; i++) {
        int a, b;
        a = listRibs[i][0];
        b = listRibs[i][1];
        adjMatrix[a-1][b-1] = 1;
        adjMatrix[b-1][a-1] = 1;
        adjMatrix[i][i] = 1;//заповнимо головну д≥агональ "1"дл€ спрощенн€ пошуку не сум≥жних вершин
    }
    outputMatrix(this->versh, this->versh, this->adjMatrix);
}

void Graph::outputMatrix(int a1, int a2, int**& A) {//виводимо матрицю
    for(int i = 0; i < a1; i++) {
        for(int j = 0; j < a2; j++) {
            cout<<setw(8)<<A[i][j];
        }
        cout<<endl;
    }
}

void Graph::clearing() {
    delete[] colors;
    delete[] tempColor;
    delete[] adjMatrix;
    delete[] tempAdj;
    delete[] listRibs;
}

int main() {
    Graph graf  ;
    graf.reading();
    graf.algorithm(graf.colors, graf.adjMatrix);
    graf.clearing();

}
