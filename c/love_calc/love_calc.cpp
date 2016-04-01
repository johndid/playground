// Author: john@dideriksen.org
// File: love_calc.cpp
// Date: 040220014
// Purpose: codegolf -> http://codegolf.stackexchange.com/questions/19649/love-calculation
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

void scan(std::string &target, std::string &matches)
{
    for(unsigned int i=0;i<target.length();i++) {
	for(unsigned int j=0;j<matches.length();j++) {
	    if(target[i] == matches[j]) {
		target[i] = '2';
		matches[j] = '.';
		break;
	    }
	}
	if(target[i] != '2') target[i] = '1';
    }
}

std::string trim(std::string target, char match)
{
    for(unsigned int i=0;i<target.length();i++) {
	if(target[i] == match) target.erase(i,1);
    }
    return target;
}

void set(std::string &target, char replacement)
{
    for(unsigned int i=0;i<target.length();i++) target[i] = replacement;
}

int main (int argc, char **argv)
{
    if(3 == argc) {
	
	std::string john(argv[1]) , loves("Loves") ,jane(argv[2]);

	// scan john first for Jane then Loves
	std::string janeloves(jane + loves);
	scan(john,janeloves);

	// scan loves for Jane 
	jane = janeloves.substr(0,jane.length());
	loves = janeloves.substr(jane.length(),loves.length());
	jane = trim(jane,'.');
	loves = trim(loves,'.');
	scan(loves,jane);

	// replace all remaining characters in jane with 1
	jane = trim(jane,'.');
	set(jane,'1');

        // ready to perform calculation
//	std::cout << john.c_str() << loves.c_str() << jane.c_str() << std::endl;
	std::string johnlovesjane(john+loves+jane);

	for(unsigned int i = 0;i<johnlovesjane.length();i++)
	{
	    if(i == johnlovesjane.length()/2)
	    {
		int cutter = johnlovesjane.find('.');
		johnlovesjane.erase(cutter,johnlovesjane.length() - cutter);
//		std::cout << johnlovesjane.c_str() << std::endl;
		i = 0;
	    }

	    if(johnlovesjane.length()==2)break;

	    int a = johnlovesjane[i] - 0x30, b = (johnlovesjane[johnlovesjane.length()-i-1] - 0x30),r=a+b;

	    if(9<r) {
		johnlovesjane[i] = (char)(r/10)+0x30;
		johnlovesjane.insert(i,1,(char)(r%10)+0x30);
	    }
	    else {
		johnlovesjane[i] = (char)(r + 0x30);
		johnlovesjane[johnlovesjane.length()-i-1] = '.';
	    }
//	    std::cout << a << "+" << b << "=" << a+b << std::endl;
	}

	std::cout << argv[1] << " Loves " << argv[2] << " has a: " << johnlovesjane.c_str() << "% chance" << std::endl;
		
    }
    else {
	std::cout << "Usage: " << (const char*)(argv[0]+2) << " [name1] [name2]" << std::endl;
	return 1;
    }
    return 0;
}
