# pragma once

# ifndef CSV_READ_HPP
# define CSV_READ_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <any>

# define MAX_COLS 10 // setting a limit to avoid errors
# define MAX_CAPACITY 1000 // the maximum number of elements a column can accomodate

namespace csv{

    struct Column{
        public:
            int item_count = 0;
            std::string datatype;
            std::string column_name;
            std::string data[MAX_CAPACITY];
            void add(std::string);
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
           
            std::string colnames[MAX_COLS]; // the names of the columns in the table
            std::string types[ MAX_COLS]; // list of the types corresponding to each column
            std::fstream dataset_parser; // to parse the dataset
            std::fstream properties_parser; // to parse the properties.txt file
            Column data[MAX_COLS]; // the table as an array of column
            
        public:
            
            DataFrame(std::string, std::string); // constructor
            int row_count; // no. of rows in the dataframe
            int column_count; // no. of columns in the dataframe
            Column getColumn(std::string); // returns the column indicated by the string
            void setColumn(std::string, Column); // to replace a column with a new column, if the label isn't present the column is added as a new one
            std::vector<std::any> getRow(int); // returns the row indicated by the index
            void summary(); // returns a summary about the columns in the dataframe

    };

};

# endif