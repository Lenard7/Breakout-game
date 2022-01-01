/***********************************************/
#include <cstdio> // TODO [lpavic]: test which libraries are not needed here
#include <cstdlib>
#include <string>
#include <exception>

#include "Level.h"


#define LEVELNUM 1
#define NAMELEVEL "Level"
#define NAMEEXTENSION ".xml"
//#define PATHRESOURCES "" 

//#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
#define PATHRESOURCES "\.\.\\\.\.\\Resources\\" // ..\..\resources\


// TODO [lpavic]: Implement main program here, loading levels, see when is last level...
int main()
{
    for (unsigned int i = 0; i < LEVELNUM; i++)
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError docError;
        errno_t err;
        char* levelFileName;
        size_t fileNameLength;
        char* levelOrdinalNum;

        levelOrdinalNum = (char*) malloc(floor(log10(i + 1) + 2)); // handle warning
        snprintf(levelOrdinalNum, strlen(levelOrdinalNum) + 1, "%d", i + 1);

        fileNameLength = strlen(PATHRESOURCES) + strlen(NAMELEVEL) + strlen(levelOrdinalNum) + strlen(NAMEEXTENSION) + 1;
        levelFileName = (char*)malloc(sizeof(char*) * fileNameLength);
        snprintf(levelFileName, fileNameLength, "%s%s%s%s", PATHRESOURCES, NAMELEVEL, levelOrdinalNum, NAMEEXTENSION);
        // levelFileName = std::string(PATHRESOURCES) + std::string(NAMELEVEL) + std::to_string(i + 1) + ".xml";

        FILE* fp;
        err = fopen_s(&fp, levelFileName, "rb");
        if (err == 0)
        {
            // print message that file is correctly opened
        }
        else
        {
            // print message that file is correctly opened
            return -1;
        }

        try
        {
            std::cout << levelFileName << "\n"; // testing purpose only // TODO [lpavic]: erase later
            docError = doc.LoadFile(fp);
            std::cout << docError << "\n\n"; // testing purpose only // TODO [lpavic]: erase later


            // TODO [lpavic]: implement error handling
            // Getting parsed data from xml into levelObject object
            Level levelObject(doc);



            //TODO [lpavic]: implement Graphics here

            ////////////////////
            
            //delete &levelObject; // TODO [lpavic]: not sure if this is OK
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << "\n";
            return -1;
        }



    }

    return 0;
}








// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
