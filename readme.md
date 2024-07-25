# AI utils in C++ (still under development)

## Aim:
I created this library to test AI stuff out using C++ (challenging yet rewarding task), basically because people consider C++ to be not so user-friendly when it comes to AI/ML applications. My target is to cross that boundary and make C++ too a useful tool for AI/ML developers.

## Functionalities Intended (status marked on the right with emojis):
* Dataframe reading / reading data from CSV files ✔️
* Data preprocessing (planned: normalisation, outlier removal, label encoding, train-test splitting) ✔️ [not exactly, need to test the normalization functions; example will be added soon]
* Simple AI / the generic stuff (i.e., those that don't require learning)❌
* Simple ML algorithms (planned: Simple Linear/Logistic Regression, Perceptron, kNN (k-Nearest Neighbours), Bayesian classifier)❌
* Simple evaluation of performance❌

## Intended Users
C++-savvy pursuers of AI/ML studies. All contributions are welcome from whosoever is interested in developing this.

## Some Silly (Probably Avoidable But I'm Not A Pro At C++) Stuff I Did
1. Instead of finding ways to directly parse CSV files without having any additional files for assistance, I made the whole setup such that the user has to have a `propeties.txt` file giving details about the table being parsed.
2. I made use of `std::ostringstream` even without understanding what it was lmao (but ofc it seemed it like it acts as a buffer to return stuff as strings when passed into the object, so I used it at some places (I may have to remove that because I didn't properly observe.
3. I'm building everything ground-up (now I'm saying this seriously, I am really trying to learn the OOP side of C++ better by oing all this (didn't get into inheritance and stuff, I did try polymorphism on the label encoding function `LabelEncoder::int_encode()` but of course I will start trying stuff soon!), sounds like a waste of time but you know what, doing so is the REAL FUN for open-source projects like these 😆.

NB: I had edited the `.hpp` and `.cpp` files assuming that you have downloaded the library in the `include` folder of the C++ compiler (I used `g++`). Do change stuff as needed so as to suit your needs.
Besides, if you're using this library as a `g++`/`cmake` based project dependancy (i.e., in the project folder itself), you may better use the absolute path. And in case you wanna try the example programs, it's hassle-free (for beginners; idk about advanced users since I'm not one myself) for you to bring the main code and the components of the example project out of the `examples\<name of the example>` folder before compiling.

