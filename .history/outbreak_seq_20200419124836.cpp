#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open();

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
    return no_vertices;
}


vector<vector<long int>> build_graph(char* filename, long int no_vertices, vector<vector<long int>>& graph){
    long int u, node_weight;
    // vector<vector<long int>> graph;
    string data;

    // graph.resize(no_vertices);
    ifstream myfile;

    myfile.open("../../../../scratch/graph-inputs_PP/node_weights.txt");

    while(myfile>>u>>node_weight){
        graph[u].push_back(node_weight);
        // cout<<"Node weight of vertex "<<u<<" is "<<node_weight<<endl;
    }

    // return graph;
}
int main(int argc, char** argv){
    
    long int u, v, node_weight;
    vector< vector<long int> > graph, weight, node_weights;
    long int no_vertices = 0;
    string data;

    char* filename = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(filename);
    cout<<"The number of vertices are : "<<no_vertices<<endl;

    graph.resize(no_vertices);
    weight.resize(no_vertices);
    node_weights.resize(no_vertices);

    fiename = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    node_weights = 

    while(myfile>>u>>node_weight){
        node_weights[u].push_back(node_weight);
        cout<<"Node weight of vertex "<<u<<" is "<<node_weight<<endl;
    }

    myfile.close();    
}