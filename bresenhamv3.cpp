/*

Scotty Fulton                 
Feb 8, 2019 
Bresenham's Line Algorithm Implementation

This application was designed and compiled with a unix terminal 
in Visual Studio Code IDE's integrated bash terminal with:
$g++ bresenhamv3.cpp
$./a.out < indata.txt > outdata.txt

This application takes input of an initial and final 
vertex and uses them to calculate the intermediate
verticies by implementing Bresenham's Line algorithm.
This application takes integer inputs and produces 
integer (x,y) coordinates between the initial and final
verticies; as per the lab instructions.

The algorithm outline was provided by Dr. Rabieh at SHSU
but left the implementation to me.  

The main() initializes the retrieval for the initial and 
final verticies, and assigns them to a vector of struct 
"vertices" data type.  This vector is then passed to 
bresenhamIt() for calculating and populating the 
intermediate verticies.  Which then calls displayVector() 
to print out a formatted table of (Xi, Yi) points. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
indata.txt contains:

20
10
30
18

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
outdata.txt contains:

Enter x then y coords pressing return after each:
//used IO redirection for input, and output//

Initial and Final verticies:
(x,y)i = (20,10), (x,y)f = (30,18)

Initial constants: 
dY = 8, twodY= 16, twodYdX= -4, initial pnot = 6

Vector elements are: 
------------------
 X0: 20 |  Y0: 10
 X1: 21 |  Y1: 11
 X2: 22 |  Y2: 12
 X3: 23 |  Y3: 12
 X4: 24 |  Y4: 13
 X5: 25 |  Y5: 14
 X6: 26 |  Y6: 15
 X7: 27 |  Y7: 16
 X8: 28 |  Y8: 16
 X9: 29 |  Y9: 17
X10: 30 | Y10: 18

*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
//includes and namespace declarations
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
//struct data type to hold objects with an (x,y) set of values
struct vertecies
{
    int xval;
    int yval;
};
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*
pass in a vector of type verticies to print out a 
formatted table of (x,y) coordiantes.
*/
void displayVector(vector<vertecies> v)
{
    cout << "\nVector elements are: " << endl;
    cout << "------------------" << endl;
    for (int i = 0; i < v.size(); i++)
    {
        if (i < 10)
        {
            cout << " X" << i << ": " << v[i].xval << " | "
                 << " Y" << i << ": " << v[i].yval << endl;
        }
        else
        {
            cout << "X" << i << ": " << v[i].xval << " | "
                 << "Y" << i << ": " << v[i].yval << endl;
        }
    }
}
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*
pass in initial and final verticies in vector form
with maxX and maxY vetex to ensure these values 
aren't popped prematurely.
*/
void bresenhamIt(vector<vertecies> ver, int mx, int my)
{
    //lots if initally calculated constants
    int xtemp, ytemp = 0;
    int finalx = mx;
    int finaly = my;
    vertecies temper;
    temper = ver.front();
    int tempX = temper.xval;
    int tempY = temper.yval;
    int dY = finaly - tempY;
    int dX = finalx - tempX;
    ver.pop_back();
    int twodY = 2 * dY;
    int fuckyou = dY - dX;
    int twodYdX = 2 * fuckyou;
    int k = 0;

    //initial decision
    int pnot = 2 * dY - dX;

    //cout initially calculated constants
    cout << "Initial constants: \ndY = " << dY << ", twodY= " 
    << twodY << ", twodYdX= " << twodYdX << ", initial pnot = " << pnot << endl;
    vertecies temp;
    //for size of vector
    for (int i = 0; i < ver.size(); i++)
    {   
        /*
        calculated values are less than max values
        this prevents calculating verticies past final vertex given
        */
        if ((ver[i].xval < finalx) && (ver[i].yval < finaly))
        {   
            //if decision vertex is positive, increment pixel's x and y coordinate
            if (pnot >= 0)
            {
                temp.xval = (tempX += 1);
                temp.yval = (tempY += 1);
                pnot += twodYdX;
                ver.push_back(temp);
            }
            //else if negative, increment only x coordinate and keep same y value
            else
            {
                temp.xval = (tempX += 1);
                pnot += twodY;
                ver.push_back(temp);
            }
        }
    }
    //send populated vector to display
    displayVector(ver);
}
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
int main()
{
    vector<vertecies> v(2);
    //retrieves initial and final (x,y) verticies
    cout << "Enter x then y coords pressing return after each:\n\n";
    cin >> v[0].xval >> v[0].yval >> v[1].xval >> v[1].yval;

    //prints out the formatted initial and final verticies 
    cout << "Initial and Final verticies:\n" << "(x,y)i = (" 
    << v[0].xval << ',' << v[0].yval << "), "; 
    cout << "(x,y)f = (" << v[1].xval << ',' << v[1].yval << ')' << endl << endl; 

    //preserves maxX and maxY values
    int maxX = v[1].xval;
    int maxY = v[1].yval;

    //time to populate this dynamically sized array!
    bresenhamIt(v, maxX, maxY);
    return 0;
}
