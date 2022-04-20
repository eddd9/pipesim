#include <iostream>
#include "unistd.h"
#include "pipeline.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * DO NOT MODIFY THIS FILE!
 */

using namespace std;

int main(int argc, char *argv[]) {

	int opt;
	bool forwarding = false;
	string fileName;
	while ((opt = getopt(argc,argv,"fi:")) != EOF)
        switch(opt)
        {
            case 'f': forwarding = true; break;
            case 'i': fileName.assign(optarg); break;
            case '?': fprintf(stderr, "usage is \n -i fileName : to run input file fileName \n -f : for enabling forwarding ");
            default: cout<<endl; abort();
        }
	
	if(fileName.empty()) 
	{
            fprintf(stderr, "No input file specified \nusage is \n -i fileName : to run input file fileName \n -f : for enabling forwarding ");
	    abort();
	}

	cout << "Loading application..." << fileName << endl;
	Application application;
	application.loadApplication(fileName);
	cout << "Initializing pipeline..." << endl;
	Pipeline pipeline(&application);
	pipeline.forwarding = forwarding;

	do {
		pipeline.cycle();
		pipeline.printPipeline();

	} while(!pipeline.done());

	cout << "Completed in " << pipeline.cycleTime - 1 << " cycles" << endl;
	return 0;
}
