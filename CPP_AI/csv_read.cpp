# include "C:/Users/samru/CPP_AI/CPP_AI/csv_read.hpp"
# include <iostream>
# include <fstream>

template <typename T> void csv::Column::getEntry(int index, T *addr){
    // returns the entry at index 0 in the correct type as specified in the column
    if(datatype.compare("int") == 0){
        *addr = std::atoi(data[index].c_str());
    } else if(datatype.compare("float") == 0){
        *addr = std::stof(data[index].c_str());
    } else if(datatype.compare("double") == 0){
        *addr = std::stod(data[index].c_str());
    } else {
        *addr = data[index];
    }
}

void csv::split_string(std::string list[], std::string line, char delimiter, int count){
    int start_pos = 0;
    int end_pos = 0;
    for(int i = 0; i < count; i++){
        end_pos = line.find(delimiter);
        if(end_pos == std::string::npos){
            end_pos = line.length();
        }
        list[i] = line.substr(start_pos, end_pos);
        start_pos = end_pos + 1;
    }
}
csv::DataFrame::DataFrame(std::string fpath, std::string fname){
    // fpath is the path to the dataset and its properties.txt file
    std::string dataset = fpath.append(fname);
    std::string properties_file = fpath.append("/properties.txt");

    // step 1: parsing the properties.txt file
    /* syntax of the file: 
    no. of columns
    no. of rows
    for each column, write <column name>:<type> 
    (supported: int, float, double, string), each in a single line*/
    
    properties_parser.open(properties_file);
    std::string val;
    properties_parser.seekg(0);
    std::getline(properties_parser, val);
    column_count = std::atoi(val.c_str());
    std::cout << "Column count:" << column_count << "Pointer position:"<< properties_parser.tellg() << std::endl;
    std::getline(properties_parser, val);
    row_count = std::atoi(val.c_str());
    std::cout << "Row count:" << row_count << "Pointer position:"<< properties_parser.tellg() << std::endl;

    std::string line;
    std::cout << "Reading properties.txt..."<< std::endl; // DEBUG LINE 1
    for(int i = 0; i < column_count; i++){
        // continues till no more data can be read
        std::getline(properties_parser, line);
        colnames[i] = line.substr(0, line.find(':',0));
        types[i] = line.substr(line.find(':',0), line.length() - line.find(':',0)-1);
        std::cout << "FOUND COLUMNS: (" << i + 1 << ")" + colnames[i]<< std::endl; // DEBUG LINE 2
    }

    std::cout << ">>>>Read all columns!" << std::endl; // DEBUG LINE 3
    properties_parser.close();


    // step 2: parsing the CSV file
    dataset_parser.open(dataset);
    std::cout << "Reading the csv dataset..."<< std::endl; // DEBUG LINE 4
    // 2.a : we make the columns in the table
    for(int i  = 0; i < column_count; i++){
        data[i].datatype = types[i];
        data[i].column_name = colnames[i];
    }

    // 2.b : we start off parsing the data
    std::string row;
    std::string values[column_count];
    for(int i = 0; i < row_count;i++){
        std::getline(dataset_parser, row);
        split_string(values, row, ',', column_count);
        for(int j = 0; j < column_count; j++){
            data[j].data[i] = values[j];
        }
    }
    std::cout << ">>>>Read all rows!" << std::endl; // DEBUG LINE 5
    dataset_parser.close();
    std::cout << "Table dimensions:" << row_count << "x" << column_count << std::endl; //DEBUG LINE 6
}

std::vector<std::any> csv::DataFrame::getRow(int index){
    if(index >= row_count || index < 0){
        throw std::runtime_error("The given row index is out of range:" + std::to_string(index));
    }
    std::vector<std::any> return_vector; 
    // the use of std::any with vectors is something that might just give us a bit of trouble if not noted
    for(int i = 0; i < column_count; i++){
        return_vector.push_back(data[i].data[index]);
    }

    return return_vector;
}

csv::Column csv::DataFrame::getColumn(std::string column_name){
    int i;
    for(i = 0; i < this->column_count; i++){
        if(colnames[i].compare(column_name)){
            break;
        }
    }

    if(i == column_count){throw std::runtime_error("Column not found:"+column_name);}

    return data[i];
}