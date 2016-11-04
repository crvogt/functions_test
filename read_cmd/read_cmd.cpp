#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv){
  // check if there is more than one argument and use the second one
  //  (the first argument is the executable)
  if (argc > 1){
      std::string arg1(argv[1]);
      // do stuff with arg1
  }

  // Or, copy all arguments into a container of strings
  std::vector<std::string> allArgs(argv, argv + argc);

  for(int i = 1; i < argc; i++){
      float valx = 0, valy = 0;

      
      if(allArgs[i] == "-p")
          std::cout << "points" << std::endl;
      else if(allArgs[i] == "-h")
          std::cout << "help" << std::endl;
        else if(allArgs[i] == "-c"){
          valx = atof(allArgs[++i].c_str());
          valy = atof(allArgs[++i].c_str());
        }
        else
          std::cout << "eh" << std::endl;
      
      std::cout << "valx " << valx << " valy " << valy << std::endl;
      std::cout << "The sum: " << valx + valy << std::endl;
  }

}

/*
int main(int argc, char **argv){

   std::cout << "argc = " << argc << std::endl; 

   for(int i = 0; i < argc; i++) 
      std::cout << "argv[" << i << "] = " << argv[i] << std::endl; 

   return 0; 

}
*/
