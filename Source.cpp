#include "Graph.h"

using std::cout;
using std::cin;
using std::string;
using std::list;
using std::fstream;
using std::ios;
using std::endl;


void runAllOptions();
void connetedGraphRun();
void diameterGraphRun();
void isolatedVertexInGraphRun();
void generateGraphsToCSV(string str, float *arr, int n);
void createGraphAndWriteToCSV(string str, float p, int operation);
float getThreashold1_3();
float getThreashold2();
float* buildPArray(float p);
void putArrayToCSV(string str, float* arr);
string fileNameCSV();

int main() {
    srand((unsigned int)time(NULL));

    int select = 0;

    cout << "The program will calculate: " << N * 10 << " graphs, every graph has: " << V << " vertexes\n\n";
    cout << "the results will be saved in: " << fileNameCSV() << "\n";

    do
    {
        cout << "\n\nPress:\n" <<
            "1 to run connectivity solution\n" <<
            "2 to run diameter solution\n" <<
            "3 to run isolated vertex solution\n" <<
            "4 to run all solutions\n" <<
            "0 to EXIT\n\n";

        do {
            select = 0;
            cin >> select;
        } while ((select < 0) || (select > 5));
        switch (select)
        {
        case 1: connetedGraphRun(); break;
        case 2: diameterGraphRun(); break;
        case 3: isolatedVertexInGraphRun(); break;
        case 4: runAllOptions(); break;
        }
    } while (select);

    return 0;
}


void runAllOptions() {
    cout << "\n---- Running runAllOptions()----\n\n";
    connetedGraphRun();
    diameterGraphRun();
    isolatedVertexInGraphRun();
}

void connetedGraphRun() {   
    cout << "\nRunning connetedGraphRun()\n";
 
    float* pArray1_3 = buildPArray(getThreashold1_3());

    fstream fs;
    fs.open(fileNameCSV(), ios::out | ios::app);
    fs << "P for concectivity: " << endl;
    putArrayToCSV(fileNameCSV(), pArray1_3);
    fs << endl;

    generateGraphsToCSV(fileNameCSV(), pArray1_3, 1);
    cout << "\n";

    fs.close();
}

void diameterGraphRun() {
    cout << "\nRunning diameterGraphRun()\n";

    float* pArray2 = buildPArray(getThreashold2());

    fstream fs;
    fs.open(fileNameCSV(), ios::out | ios::app);
    fs << "P for diameter: " << endl;
    putArrayToCSV(fileNameCSV(), pArray2);
    fs << endl;

    generateGraphsToCSV(fileNameCSV(), pArray2, 2);
    cout << "\n";

    fs.close();
}

void isolatedVertexInGraphRun() {
    cout << "\nRunning isolatedVertexInGraphRun()\n";

    float* pArray1_3 = buildPArray(getThreashold1_3());

    fstream fs;
    fs.open(fileNameCSV(), ios::out | ios::app);
    fs << "P for isolated vertex: " << endl;
    putArrayToCSV(fileNameCSV(), pArray1_3);
    fs << endl;

    generateGraphsToCSV(fileNameCSV(), pArray1_3, 3);
    cout << "\n";

    fs.close();
}

void generateGraphsToCSV(string str, float* arr, int n) {
    
    int printValue = 1;

    fstream fs;
    fs.open(str, ios::out | ios::app);
    cout << "Number of graphs builded and calculated:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 10; j++) {
            createGraphAndWriteToCSV(str, arr[j], n);
        }
        cout << 10 * printValue++ << " ";
        fs << endl;
    }
   
    fs.close();
}

//number of operation: 1 connection, 2 diameter, 3 isolated
void createGraphAndWriteToCSV(string str, float p, int operation) {
    
    Graph g(V);
    list<int> adj[V];
    int* arr = new int[10];

    g.buildRandomGraph(adj, V, p);

    if (operation == 1) {
        g.BFS(0);
        writeToCSV(str, g.getIsConnected());
    }

    if (operation == 2) {     
        g.setDiameter(g);
        writeToCSV(str, g.getDiameter());
    }

    if (operation == 3) {
        g.isIsolatedVertex(g);
        writeToCSV(str, g.getIsIsolatedVertex());
    }
}

float* buildPArray(float p) {

    float* arr = new float[10];
    float sizeOfJumpAroundP = p / 7; // as this number smaller, the results will be corrected. big number -> more the number will close to threshold
    float currentPToJump = p - (float)6.5 * (sizeOfJumpAroundP); // constant number is very important to final results. its the size of surrounding threshold values.

    for (int i = 0; i < 10; i++) {
        arr[i] = currentPToJump;
        currentPToJump += sizeOfJumpAroundP;
        if (i == 4) { currentPToJump = p + (sizeOfJumpAroundP); } //to avoid p eqauls to the threshold
    }

    return arr;
}

void putArrayToCSV(string str, float* arr) {
    fstream fs;
    fs.open(str, ios::out | ios::app);
    for (int i = 0; i < 10; i++) {
        writeToCSV(str, arr[i]);
    }
    fs.close();
}

float getThreashold1_3() { return (float)log(V) / V; }

float getThreashold2() { return (float)sqrt(2 * (log(V) / V)); }

string fileNameCSV() { return "Test.csv"; }
