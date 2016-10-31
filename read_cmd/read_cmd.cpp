#include <string>
#include <vector>
#include <iostream>

int main(int argc, char **argv){
  // check if there is more than one argument and use the second one
  //  (the first argument is the executable)
  if (argc > 1){
    std::string arg1(argv[1]);
    // do stuff with arg1
  }

  // Or, copy all arguments into a container of strings
  std::cout << argv + argc << std::endl;
  std::vector<std::string> allArgs(argv, argv + argc);

  for(int i = 1; i < argc; i++){
  	std::cout << allArgs[i] << std::endl;
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
