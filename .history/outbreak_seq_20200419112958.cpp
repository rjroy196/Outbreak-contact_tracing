#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv){
    
    vector< vector<long int> > graph, weight, node_weights;
    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open("../../../../scratch/graph-inputs_PP/node_weights.txt");
    if(myfile){
        cout<<"File Opened"<<endl;
    }
    else{
        cout<<"File not opened"<<endl;
    }
    while(getline(myfile, data)){
        no_vertices++;
    }
    myfile.close();
    
    cout<<"The number of vertices are : "<<no_vertices<<endl;

    graph.resize(no_vertices);
    weight.resize(no_vertices);
    node_weights.resize(no_vertices);


}