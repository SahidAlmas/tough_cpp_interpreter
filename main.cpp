#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <sstream>
#define VERSION "0.9 built on c++"


/**
 * Coded by LittlEvil
 */

using namespace std;
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

int parse(string token,int last) {
    // (.)|(>..)|(.)\(..<)|(.>>)
    if (token == "(.)") {

        return 1;
    }
    int x = last;
    for (char word : token) {
        if (word == '.') {
            x += 1;

        }else if (word == '>') {
            x += 10;
        }else if (word == '<') {
            x -= 10;
        }else if (word == '^') {
            x += 5;
        }else if (word == '_') {
            x -= 5;
        }
    }
    return x;

}
void parse_and_print(string code){

    // (.)|(>..)|(.)\(..<)|(.>>)

    string alphas[] = {"","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

    vector<string> tokens = split(code,'|');

    if (tokens.size() == 0) {
        fputs("syntax error \n",stderr);
        return;
    }
    for (int i = 0 ; i < tokens.size() ; i++) {
        string my_token = tokens[i];
        if (my_token == "()") {
            cout << " ";
            continue;
        }

        cout << alphas[parse(my_token,0)];

    }
    cout << endl;
}
string cleanup(string basic_string) {
    string output("");
    std::vector<std::string> x = split(basic_string, '\n');
    for (string line : x) {
        std::string prefix("//");
        if (line.compare(0, prefix.size(), prefix) != 0) {

            output += line;
        }
    }
    return output;
}


string readFile(const string &fileName)
{
    ifstream f(fileName.c_str());
    return string(std::istreambuf_iterator<char>(f),
                  std::istreambuf_iterator<char>());
}

inline bool file_exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}
void copyright() {
    fputs("tough - Copyright(c) S Mahammad Almas",stderr);
}
void version() {
    fputs(VERSION,stderr);
}
void print_usage()  {
    fputs("tough by LittlEvil\n",stderr);
    fputs("written in c/c++\n",stderr);
    fputs("usage : \n",stderr);
    fputs("\ttough [file]\t\t\t\t\t To execute your tough file\n",stderr);

    fputs("\ttough --help,help\t\t\t\t To print this\n",stderr);

    fputs("\ttough --version,version\t\t\t To print this\n",stderr);

    fputs("\ttough --copyright,copyright\t\t To print copyright\n",stderr);
}

int main(int argc, char const *argv[])
{

    if (argc == 1 ) {
        print_usage();
    }else {

        char *command_z = (char *) argv[1];
        string command = command_z;
        if (command == "--help" || command == "help") {
            print_usage();
        }else if (command == "--copyright" || command == "copyright") {
            copyright();
        }else if (command == "--version" || command == "version") {
            version();
        }else {
            if (file_exists(command)) {
                string full =  (readFile(command));
                string codes = cleanup(full);

                vector<string> c_l = split(codes,'\n');

                for (string cl_code : c_l) {
                    parse_and_print(cl_code);
                }

            }else {
                fputs("tough - no such file found or directory",stderr);
            }
        }
    }
    return 0;
}

