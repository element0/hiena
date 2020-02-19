

#include <string>
#include <iostream>

using namespace std;

struct cosmos;

class dcel {
  private:
    static struct cosmos cosmos;

  public:
    string service;
    string address;
    string type;
};
