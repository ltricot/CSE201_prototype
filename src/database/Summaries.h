#pragma once
#include <string>

using namespace std;

class Summaries{
    string directory;
    Summaries(string dir);
    void storeSummary(string id, string summary);
    string getSummary(string id);
}