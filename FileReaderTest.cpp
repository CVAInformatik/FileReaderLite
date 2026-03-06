

#include "FileReader.h"

int main(int argc, char** argv ){
	
	std::cout << "argc " << argc << std::endl;
		
	if(argc == 2) {
		  std::string name(argv[1]);		  	
	  	std::cout << "name " << name << std::endl;
			FileReaderDouble  testObject(name, 100)  ;
			std::cout << " testObject.Size()  " <<  testObject.size() << std::endl ;
			double *ptr = testObject.data();	
			if (ptr) for ( int i = 0 ; i < testObject.size() ; i++)	
				 printf("%d :  %e \n",i, ptr[i]);
		  
		  int index = 0;
			do 
			   std::cout << index << "   " << testObject.line(index) << std::endl;
			while ( testObject.line(index++).length() > 0);
	}
	
	return 0;
}