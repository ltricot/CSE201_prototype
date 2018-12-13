#include <string>
#include <vector>
#include <iostream> 
using namespace std;

// Joining the strings contained in a vector<string>

void join(const vector<string>& v, char c, string& s) {

   s.clear();

   for (vector<string>::const_iterator p = v.begin();
        p != v.end(); ++p) {
      s += *p;
      if (p != v.end() - 1)
        s += c;
   }
}

/* 
int main() {

   vector<string> v;
   string s;

   v.push_back(string("truc"));
   v.push_back(string("machin"));
   v.push_back(string("blabla"));
   v.push_back(string("patate"));

   join(v, ',', s);

   cout << s << '\n';
}
*/ 