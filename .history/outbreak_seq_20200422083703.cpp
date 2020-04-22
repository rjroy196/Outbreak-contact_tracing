#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h> 


using namespace std;

struct graph{
    int Day;
    vector< vector<long int> > graph_for_the_day;
};


long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open(filename);

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


void get_infected(char* filename, long int no_infected, vector< vector<long int> >& infected, int day){
    long int u;
    // vector<vector<long int>> graph;
    string data;

    // graph.resize(no_vertices);
    ifstream myfile;

    myfile.open(filename);

    if(myfile){
        cout<<"File Opened"<<endl;
    }
    else{
        cout<<"File not opened"<<endl;
    }

    while(myfile>>u){
        infected.push_back(u);
    }
    myfile.close();
    // cout<<"Graph created"<<endl;
}


void build_graph(char* filename, long int no_vertices, vector< vector<long int> >& graph){
    long int u, node_weight, day;
    // vector<vector<long int>> graph;
    string data;

    // graph.resize(no_vertices);
    ifstream myfile;

    myfile.open(filename);

    if(myfile){
        cout<<"File Opened"<<endl;
    }
    else{
        cout<<"File not opened"<<endl;
    }

    while(myfile>>u>>node_weight){
        graph[u].push_back(node_weight);
    }
    myfile.close();
    // cout<<"Graph created"<<endl;
}


vector<long int> get_neighbours(vector< vector<long int> >& graph, int u){

    return graph[u];
}


int main(int argc, char** argv){
    
    int i, j, k, count=0;
    long int u, v, graph_number;

    struct graph day_graphs[10];

    vector< vector<long int> > weight, node_weights, no_of_neighbours, infected;
    long int no_vertices = 0, no_infected = 0;
    string data, file_number, txt, filename, filename1;
    char* file;

    ifstream myfile;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);
    cout<<"The number of vertices are : "<<no_vertices<<endl;

    no_of_neighbours.resize(no_vertices);
    weight.resize(no_vertices);
    node_weights.resize(no_vertices);

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    build_graph(file, no_vertices, node_weights);
    filename = "../../../../scratch/graph-inputs_PP/wiki-";
    txt = ".txt";


    for (i=1; i<=10; i++){
        day_graphs[i-1].Day = i;
        day_graphs[i-1].graph_for_the_day.resize(no_vertices);

        graph_number = i;
        file_number = to_string(graph_number);

        // filename.append(file_number);
        // filename.append(txt);
        filename1 = filename+file_number+txt;

        file = &filename1[0];
        cout<<file<<endl;
        build_graph(file, no_vertices, day_graphs[i-1].graph_for_the_day);
        cout<<"Graph "<<i<<" built"<<endl;
    }

    // filename = "../../../../scratch/graph-inputs_PP/wiki-6.txt";

    for (k=0; k<10; k++){
        count = 0;
        for (i=0; i<no_vertices; i++){
            no_of_neighbours[i].push_back(day_graphs[k].graph_for_the_day[i].size());
        }
    }
        // cout<<"The final non zero count is "<<count<<" for graph "<<k<<endl;

    for (i=0; i<no_vertices; i++){
        for (j=0; j<no_of_neighbours[i].size(); j++){
            cout<<no_of_neighbours[i][j]<<"  ";
        }
        cout<<endl;
    }
    vector<long int> infected;
    filename = "infected.txt";
    file = &filename[0];

    no_infected = get_no_lines(file);

    myfile.open(file);
    while()    


}