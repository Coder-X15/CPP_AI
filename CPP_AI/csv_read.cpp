# include "C:/Users/samru/CPP_AI/CPP_AI/csv_read.hpp"
# include <iostream>
# include <fstream>
# include <vector>
# include <any>
# include <cstring>

void csv::Column::add(std::string value){
    data[item_count++] = value;
}

void csv::split_string(std::string list[], std::string line, char delimiter, int count){
    int pos_pointer = 0;
    int length = line.length();
    for(int i = 0; i < count; i++){
        std::string temp;
        while(line.at(pos_pointer) != delimiter && pos_pointer < length-1){
            temp = temp + line.at(pos_pointer);
            pos_pointer++;
        }
        list[i] = temp;
        pos_pointer++;
    }
}
csv::DataFrame::DataFrame(std::string fpath, std::string fname){
    // fpath is the path to the dataset and its properties.txt file
    std::string dataset = fpath + fname;
    std::string properties_file = fpath + "properties.txt";

    // step 1: parsing the properties.txt file
    /* syntax of the file: 
    no. of columns
    no. of rows
    for each column, write <column name>:<type> 
    (supported: int, float, double, string), each in a single line*/
    
    properties_parser.open(properties_file, std::ios::in);
    std::string val;
    std::cout << "<msg>------ > Reading properties.txt..."<< std::endl;
    std::getline(properties_parser, val);
    this->column_count = std::atoi(val.c_str());
    std::cout << "Column count:" << column_count << std::endl;
    std::getline(properties_parser, val);
    this->row_count = std::atoi(val.c_str());
    std::cout << "Row count:" << row_count << std::endl;

    std::string line;
    for(int i = 0; i < this->column_count; i++){
        // continues till no more data can be read
        std::getline(properties_parser, line);
        int pos = line.find(":");
        int length = line.length();
        for(int counter = 0; counter < pos; counter++){
            colnames[i] = colnames[i] + line.at(counter);
        }
        for(int counter = pos + 1; counter < length; counter++){
            types[i] = types[i] + line.at(counter);
        }
    }

    std::cout << "<msg>------ > Read all columns!" << std::endl;
    properties_parser.close();


    // step 2: parsing the CSV file
    dataset_parser.open(dataset);
    std::cout << "Reading the csv dataset..."<< std::endl; // DEBUG LINE 4
    // 2.a : we make the columns in the table
    for(int i  = 0; i < this->column_count; i++){
        data[i].datatype = types[i];
        data[i].column_name = colnames[i];
    }

    // 2.b : we start off parsing the data
    std::string row;
    for(int i = 0; i < this->row_count;i++){
        std::string values[this->column_count];
        std::getline(dataset_parser, row);
        /* split_string(values, row, ',', this->column_count); */
        // splitting the row around the commas
        int char_count = 0;
        int value_count = 0;
        while(char_count < row.length()){
            if(row.at(char_count) == ','){
                value_count++;
            } else {
                values[value_count] += row.at(char_count);
            }
            char_count++;
        }
        for(int j = 0; j < this->column_count; j++){
           (this-> data[j]).add(values[j]);
        }
    }
    std::cout << "<msg>------ > Read all rows!" << std::endl; // DEBUG LINE 5
    dataset_parser.close();
    std::cout << "<msg>------ > Table dimensions:" << this->row_count << "x" << this->column_count << std::endl; //DEBUG LINE 6
}

std::vector<std::any> csv::DataFrame::getRow(int index){
    if(index >= row_count || index < 0){
        throw std::runtime_error("The given row index is out of range:" + std::to_string(index));
    }
    std::vector<std::any> return_vector; 
    // the use of std::any with vectors is something that might just give us a bit of trouble if not noted
    for(int i = 0; i < column_count; i++){
        if(data[i].datatype.compare("int") == 0){
            return_vector.push_back(std::atoi(data[i].data[index].c_str()));
        } else if(data[i].datatype.compare("int") == 0){
            return_vector.push_back(std::atof(data[i].data[index].c_str()));
        } else {
            return_vector.push_back(data[i].data[index]);
        }
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