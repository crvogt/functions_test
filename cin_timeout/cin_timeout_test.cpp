#include <iostream>
#include <sys/select.h>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    cout<<"Before performing cin operation"<<endl;

    //Below cin operation should be executed within stipulated period of time
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(STDIN_FILENO, &readSet);
    struct timeval tv = {10, 0};  // 10 seconds, 0 microseconds;
    if (select(STDIN_FILENO+1, &readSet, NULL, NULL, &tv) < 0) perror("select");

    bool b = (FD_ISSET(STDIN_FILENO, &readSet)) ? (cin>>n) : false;

    if(b==1)
          cout<<"input is integer for n and it's correct"<<endl;
    else
          cout<<"Either n is not integer or no input for n"<<endl;

    return 0;
}
