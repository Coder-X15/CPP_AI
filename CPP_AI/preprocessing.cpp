# include "csv_read.hpp"
# include "preprocessing.hpp"
# include <iostream>
# include <math.h>
# include <Sstream>

using namespace csv;

void LabelEncoder::reset(){
    for(int i = 0; i< label_count; i++){
        labels[i].clear();
    }
    label_count = 0;
}

std::string LabelEncoder::getIndex(std::string label){
    int i;
    for(i = 0; i < label_count; i++){
        if(labels[i].compare(label) == 0){
            break;
        }
    }
    if(label_count == 0 || (i == label_count && i != 0)){
        return("-1");
    } else {
        return(std::to_string(i));
    }
}

Column LabelEncoder::int_encode(Column column){
    Column answer;
    answer.column_name = column.column_name;
    answer.datatype = "int";
    for(int i = 0; i < column.item_count;i++){
        if(getIndex(column.data[i]).compare("-1") == 0){
            labels[label_count++] = column.data[i];
        }
        answer.data[i] = getIndex(column.data[i]);
    }
    reset();
    return(answer);
}

Column LabelEncoder::int_encode(Column column, int start_value){
    Column answer;
    answer.column_name = column.column_name;
    answer.datatype = "int";
    for(int i = 0; i < column.item_count;i++){
        if(getIndex(column.data[i]).compare("-1") == 0){
            labels[label_count++] = column.data[i];
        }
        std::string offset = getIndex(column.data[i]);
        int integer_label =  start_value + std::atoi(offset.c_str());
        answer.data[i] = std::to_string(integer_label);
        oss.clear();
    }
    reset();
    return(answer);
}

template <typename T> Column min_max_normalize(Column column, T min_value, T max_value){
    column.datatype = "double";
    for(int i = 0; i < column.item_count;i++){
        oss << (column.data[i] - min_value)/(max_value - min_value);
        column.data[i] = oss.str();
    }
    return(column);
}

Column decimal_scale_normalize(Column column){
    column.datatype = "double";
    for(int i = 0; i < column.item_count;i++){
        oss << std::stod(column.data[i])/(pow(10, 1 + log10(std::stod(column.data[i]))));
        column.data[i] = oss.str();
    }
    return(column);
}