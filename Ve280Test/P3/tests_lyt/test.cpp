#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <dirent.h>  // For getting world file names
using namespace std;
// #include "world_type.h"
// #include "simulation.h"
// CAUTION: "using namespace std;" has already been used in world_type.h.

void p3_test();
// Effects: get the names of all the files under directory dir_name
// (like ls), and store it into a vector of strings. Since ISO C++
// forbids conversion from string literal to char*, we use C++ string
// instead of char* here.
void get_world_file_ls(vector<string> &ls, string dir_name);
// Requires: num_rounds has the same size as ls.
void get_num_rounds(vector<int> &num_rounds, const vector<string> &ls,
    string file_name);
void test_world_file_dir(string dir_name, bool is_verbose);

int main()
{
    p3_test();
    return 0;
}

void p3_test()
{
    // Since it uses the system() function, it is only valid for POSIX
    // compatible OSes.

    // Test for input error 1 to 6.
    system("cp ../p3 .");
    system("./p3 aaa bbb > outfile");
    system("diff -s outfile error1.answer");
    system("./p3 aaa bbb -1 > outfile");
    system("diff -s outfile error2.answer");
    system("./p3 specie world-tests/world1 1 > outfile");
    system("diff -s outfile error3_1.answer");
    system("./p3 species world-tests/world 1 > outfile");
    system("diff -s outfile error3_2.answer");
    system("./p3 species_not_exist world-tests/world1 1 > outfile");
    system("diff -s outfile error3_3.answer");
    system("./p3 species_too_many world-tests/world1 1 > outfile");
    system("diff -s outfile error4.answer");
    system("./p3 species_long_program world-tests/world1 1 > outfile");
    system("diff -s outfile error5.answer");
    system("./p3 species_invalid_instr world-tests/world1 1 > outfile");
    system("diff -s outfile error6.answer");

    // Test for other input errors.
    test_world_file_dir("world-tests/error_worlds", false);
    // Test for world1 to world3. The answer for world4 may not be
    // correct.
    test_world_file_dir("world-tests", false);
    test_world_file_dir("world-tests", true);

    cout << "Test complete." << endl;
}

void test_world_file_dir(string dir_name, bool is_verbose)
{
    vector<string> file_ls;
    string str_temp;

    // Test for other input errors.
    get_world_file_ls(file_ls, dir_name);
    vector<int> num_rounds(file_ls.size(), 0);
    get_num_rounds(num_rounds, file_ls, dir_name+"/rounds");
    for (unsigned i = 0; i != file_ls.size(); ++i) {
        str_temp = "./p3 species " + dir_name + "/" + file_ls[i] + " "
            + to_string(num_rounds[i]) + " > outfile";
        if (is_verbose) {
            str_temp += " v";
        }
        // cout << str_temp << endl;
        system(str_temp.c_str());
        str_temp = "diff -s outfile " + dir_name + "/"
            + file_ls[i] + ".answer";
        if (is_verbose) {
            str_temp += "-verbose";
        }
        // cout << str_temp << endl;
        system(str_temp.c_str());
    }
}

void get_world_file_ls(vector<string> &ls, string dir_name)
{
    DIR *dir;
    dirent *ent;
    string str_temp;
    ls.clear();

    dir = opendir(dir_name.c_str());
    if (dir != nullptr) {
        while ((ent=readdir(dir)) != nullptr) {
            str_temp = ent->d_name;
            // If the return value of find() is npos, it means "answer"
            // does not occur in the file name.
            if (ent->d_type == DT_REG && str_temp[0] != '.'
                    && str_temp.find("answer") == str_temp.npos
                    && str_temp != "rounds") {
                ls.push_back(str_temp);
            }
        }
    }
    closedir(dir);
}

void get_num_rounds(vector<int> &num_rounds, const vector<string> &ls,
    string file_name)
{
    ifstream infile(file_name);
    // If no rounds file is provided, do nothing and let num_rounds be
    // all zero.
    if (infile.fail()) {
        return;
    }
    string str;

    while (getline(infile, str) && !str.empty()) {
        for (unsigned i = 0; i != ls.size(); ++i) {
            if (str == ls[i]) {
                getline(infile, str);
                num_rounds[i] = stoi(str);
                break;
            }
        }
    }
}
