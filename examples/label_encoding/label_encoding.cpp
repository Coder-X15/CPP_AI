# include <iostream>
# include <fstream>
# include <vector>
# include <any>
// # include <<path to your lib folder>/CPP_AI/csv_read.cpp>
# include "CPP_AI\csv_read.cpp"
# include "CPP_AI\preprocessing.cpp"

// while using any, do use any_cast<type>(value) to cast values to their appropriate type
using namespace std;
int main(){
    csv::DataFrame df("C:\\Users\\samru\\CPP_AI\\","income_mgmt_data.csv");
    cout << "Dataset before label encoding \"Gender\" column:" << endl;
    df.summary();
    /* vector<any> row0 = df.getRow(0);
    vector<any> row1 = df.getRow(1);
    cout << "The first row:" << any_cast<string>(row0[0]) << "," << any_cast<int>(row0[1]) << endl;
    cout << "The second row:" << any_cast<string>(row1[0]) << "," << any_cast<int>(row1[1]) << endl; */
    LabelEncoder le;
    Column to_be_encoded = df.getColumn("Gender");
    cout << any_cast<string>(to_be_encoded.data[0]) << " is the first value in the column \"Gender\".\n";
    cout << "Encoding....\n";
    df.setColumn("Gender", le.int_encode(to_be_encoded, 1)); // label encoding with displacement in the starting integer label
    to_be_encoded = df.getColumn("Gender");
    cout << stoi(any_cast<string>(to_be_encoded.data[0])) << " is the first value in the column \"Gender\".\n";
    return(0);
}