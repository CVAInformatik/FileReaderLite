#pragma once 

#include <cmath>
#include <ctype.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

class FileReaderDouble
{
	
public: 
	
	/*
	    lines beginning with a number (surrounded by optional whitespace) will have it converted to double and appended to an array 
	    (and the rest of the line will be ignored)
	    lines beginning with '.' will be stored - in order - internally, numbered 0,1,2,.... 
	    a line not conforming to the above is understood as <end of input>
	*/
	FileReaderDouble(std::string _fname , unsigned int _ChunkSize = 10000)
		 { 
		        DoubleData = NULL;
		        DoubleSize = 0;
		        AllocationSize = 0;
						ChunkSize = _ChunkSize ;
						ReadFile(_fname) ;
					  }; 
	
	~FileReaderDouble(){ if (DoubleData != NULL) free(DoubleData) ; } ;
		
	double* data() { return DoubleData ;}
	size_t  size() { return DoubleSize ; }
	
	/* 
	    lines beginning with '.' will be cached in order internally, numbered 0,1,2,3,4,.... 
	    A copy will be returned,  if available, or an empty line.
	*/
	std::string line(unsigned int index) {  
		std::string val("");
		if (index < strings.size() ) val = strings[index];
		return val ;
	};
  	
private: 	
	
	std::vector<std::string>  strings ;
	double *DoubleData;
	size_t DoubleSize ;
	size_t AllocationSize; 
	size_t ChunkSize ;
	
	int ReadFile(const std::string &fn)
	{
		std::fstream fs;

		fs.open(fn, std::ios_base::in);

		if (fs.is_open())
		{
    	std::string buffer ;
     
			while (!fs.eof())
			{
				getline(fs, buffer);

        if( buffer[0] == '.') strings.push_back(buffer);
        else {
					size_t row = 0;
					double n1;
					n1= std::nan("1") ;
					std::stringstream(buffer) >> n1;
					if (!std::isnan(n1)) { //NaN check
						if (AllocationSize == DoubleSize) {
							AllocationSize += ChunkSize ;
							DoubleData = (double *) realloc( DoubleData, AllocationSize * sizeof(double));
							if( DoubleData == NULL){
							 	fprintf(stderr, "Out of Memory\n");
								return 0	;
							}
						}
						DoubleData[DoubleSize++] = n1;
					}
					else {
					if(DoubleSize > 0) DoubleData =(double *)  realloc( DoubleData, DoubleSize * sizeof(double));
					break ;  // bail out
					}
				}
			}
			fs.close();
			return 1;
		}
	  return 0;
  };
};