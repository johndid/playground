//
//  main.cpp
//  how_many_triangles
//
//  Created by John Dideriksen on 4/3/13.
//  Copyright (c) 2013 John Dideriksen. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, const char * argv[])
{
    int n = 0;
    cout << "Input the magic number for your triangles: (count the ones following the height)" << endl;
    cin >> n;
    
    unsigned int number_of_triangles = floor(n*(n+2)*(2*n+1)/8);
 
    if(1 == number_of_triangles) {
        cout << "There is: " << number_of_triangles << " triangle" << endl;
    }
    else {
        cout << "There are: " << number_of_triangles << " triangles" << endl;
    }
    
    string triangles;
    for(int i=0;i<number_of_triangles;i++) {
        triangles.insert(0,"*");
        cout << triangles.c_str() << endl;
    }
    
    return 0;
}

