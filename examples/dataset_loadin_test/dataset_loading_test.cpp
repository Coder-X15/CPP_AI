# include <iostream>
# include <fstream>
# include <vector>
# include <any>
# include <C:/Users/samru/CPP_AI/CPP_AI/csv_read.cpp>

// while using any, do use any_cast<type>(value) to cast values to their appropriate type
using namespace std;
int main(){
    csv::DataFrame df("C:/Users/samru/CPP_AI/examples/dataset_loadin_test","data.csv");
    cout << "Dataset loaded successfully" << endl;
    vector<any> result = df.getRow(2);
    cout << any_cast<int>(result.back());
    result.pop_back();
    cout << any_cast<int>(result.back());
    return(0);
}