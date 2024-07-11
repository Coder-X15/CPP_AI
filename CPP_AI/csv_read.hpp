# pragma once

# ifndef CSV_READ_H
# define CSV_READ_H

# include <iostream>
# include <fstream>
# include <vector>
# include <any>


namespace csv{

    class Column{
        public:
            std::string datatype;
            std::string column_name;
            std::string *data;
            template <typename T> void getEntry(int, T*); 
    };

    class DataFrame{
        /* Used to parse the CSV file into a dataframe.
            You can use the getColumn(string column_name)
            function to get the data from a single column and getRow(int index)
            function to get the row at the given index. More functionalities will be planned 
            and implemented soon. 
            NB: the datasets must be accompanies by a properties.txt file; this file
            helps in the proper parsing of the data in the csv file to the appropriate types.*/
        private:
           
            std::string *colnames; // the names of the columns in the table
            std::string *types; // list of the types corresponding to each column
            std::ifstream dataset_parser; // to parse the dataset
            std::ifstream properties_parser; // to parse the properties.txt file
            Column *data; // the table as an array of columns
            
        public:
            
            DataFrame(std::string, std::string); // constructor
            int row_count; // no. of rows in the dataframe
            int column_count; // no. of columns in the dataframe
            Column getColumn(std::string); // returns the column indicated by the string
            std::vector<std::any> getRow(int); // returns the row indicated by the index

    };

    // some utility functions for making life easier
    void split_string(std::string[], std::string, char, int);

};

# endif