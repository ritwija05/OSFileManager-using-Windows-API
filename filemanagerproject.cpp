// filemanagerproject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FileManager.h"

int main()
{
         std::string filename = "C:\\Users\\21146\\OneDrive\\Desktop\\first.txt";
   		if ( FileManager::createFile(filename) ) 
   		{
   			std::cout << "Created file: " << filename << std::endl;
   		}
    std::cout << "Hello World!\n";
}

