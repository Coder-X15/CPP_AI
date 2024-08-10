# pragma once

# ifndef PREPROCESSING_HPP
# define PREPROCESSING_HPP

# include "csv_read.hpp"
# include <iostream>
# include <math.h>
# include <sstream>

# define MAX_LABELS 100 // idk why but putting these relieves my trouble of having to deal with a lot of pointers
using namespace csv;

std::ostringstream oss;

class LabelEncoder{
    // a class to do the label encoding task for us
    private:
        std::string labels[MAX_LABELS];
        void reset(); // just resetting the object so as to prepare for the next label encoding task
        std::string getIndex(std::string);
    public:
        int label_count = 0;
        Column int_encode(Column); //  the main function, to do the encoding task starting from 0
        Column int_encode(Column, int);  // an overload so as to enable displacement of the label (not yet implemented)
};

template <typename T> Column min_max_normalize(Column, T, T); 
Column decimal_scale_normalize(Column);
// Column z_score_normalize(Column); works for a normal distribution (not yet implemneted)

# endif