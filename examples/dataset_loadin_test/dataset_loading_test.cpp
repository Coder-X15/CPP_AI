# include <iostream>
# include <fstream>
# include <vector>
# include <any>
// # include <<path to your lib folder>/CPP_AI/csv_read.cpp>
# include <CPP_AI/csv_read.cpp>

// while using any, do use any_cast<type>(value) to cast values to their appropriate type
using namespace std;
int main(){
    csv::DataFrame df("C:\\Users\\samru\\CPP_AI\\examples\\dataset_loadin_test\\","data.csv");
    cout << "Dataset loaded successfully; use df.summary() to get a quick view about the columns." << endl;
    df.summary();
    vector<any> row0 = df.getRow(0);
    vector<any> row1 = df.getRow(1);
    cout << "The first row:" << any_cast<int>(row0[0]) << "," << any_cast<int>(row0[1]) << endl;
    cout << "The second row:" << any_cast<int>(row1[0]) << "," << any_cast<int>(row1[1]) << endl;
    return(0);
}