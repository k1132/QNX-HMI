#ifndef DEMO_H
#define DEMO_H
#include <vector>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;
static vector<string> file_video_path_vector ;
static vector<string> file_music_path_vector ;
void readFileList( char *basePath,vector<string>& filePathVector);
#endif //DEMO_H
