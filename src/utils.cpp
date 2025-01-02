#include "utils.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

static bool readPathsFromFile(const string & filename, vector<string>& paths){
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error: could not open file " << filename << endl;
        return false;
    }
    string line;
    while (getline(file, line)){
        if (!line.empty()) paths.push_back(line);
    }
    file.close();
    return true;
}

vector<Task> validate_scripts(const string & kernels_filename){
    vector<string> paths;
    if (!readPathsFromFile(kernels_filename, paths)) {
        return {};
    }

    vector<Task> tasks;
    // Validate each path and create tasks
    for (string const& path : paths){
        struct stat fileInfo;
        // Verify if the path is valid and executable
        bool isValid = (stat(path.c_str(), &fileInfo) == 0) && (fileInfo.st_mode & S_IXUSR);
        if (!isValid){
            cerr << "Error: path " << path << " doesn't exist or is not executable" << endl;
            continue;
        }
        tasks.push_back(Task(path));
    }
    
    return tasks;
}