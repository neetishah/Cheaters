#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <vector>

using namespace std;


int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));

    }
    closedir(dp);
    return 0;
}


int main() {

    //    char fName[strlen(argv[1])];
    //    strcpy(fName,argv[1]);
    //    int nWord = argv[1];

    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir, files);

    for (unsigned int i = 0; i < files.size(); i++) {
        cout << i << files[i] << endl;
    }

    int nWord = 10;


    for (int index = 0; index < files.size(); index++) {

        string fName = files[index];

        if (fName == ".") {
            index++;
            fName = files[index];
        }

        if (fName == "..") {
            index++;
            fName = files[index];
        }

        if (fName == "abf0704.txt___jb_old___") {
            index++;
            fName = files[index];
        }

        string folder = "sm_doc_set/";
        fName = folder + fName;


        FILE *fptr = fopen(fName.c_str(), "r");



        if (fptr != NULL){

            char queue[nWord];
            char *queueTop = queue;
            char *queueBottom = &queue[nWord - 1];
            char *first = queue;
            char *incr = queue;
            char *incrnext;


            cout << feof(fptr)<< endl;

            while (!feof(fptr)) {
                char c = fgetc(fptr);
                if ((c != '.') && (c != '\r')) {
                    if ((c <= 'Z') && (c >= 'A') || (c <= 'z') && (c >= 'a')) {
                        if (incr == queueBottom) {
                            incrnext = queueTop;
                        } else incrnext = incr + 1;

                        if (incrnext != first) {            //there is space in queue
                            incr = incrnext;
                            *incr = c;
                        } else {
                            //cout
                            char *dummy = first;
                            for (int i = 0; i < nWord; i++) {
                                cout << *dummy;
                                if (dummy == queueBottom) {
                                    dummy = queueTop;
                                } else dummy++;
                            }

                            //incr first + wrap around
                            if (first == queueBottom) {
                                first = queueTop;
                            } else {
                                first++;
                            }

                        }
                    }
                }
            }









//
//            while (!feof(fptr)) {
//                for (int i = 0; i <= nWord; i++) {
//                    char c = fgetc(fptr);
//                    if ((c != '.') && (c != '\r')) {
//                        if ((c <= 'Z') && (c >= 'A') || (c <= 'z') && (c >= 'a')) {
//                            queue[i] = c;
//                            cout << c;
//                        }
//                        else {
//                            i--;
//                        }
//                    }
//                    if (feof(fptr))
//                        break;
//                }
//                cout << endl;
//            }
//        }

        }

        else {
            cout << "error in opening" << endl;
            exit(-1);
        }

    }
}