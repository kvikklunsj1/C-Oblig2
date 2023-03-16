#include <iostream>
#include <fstream> //ifstreamobject
#include <vector>
#include <string> //getline

class Bygning 
{
    public:
        float areaBygning;
        float heightBygning;
        float widthBygning;
        float areaWasted;

        Bygning(float heightB, float widthB)
        {
            heightBygning = heightB;
            widthBygning = widthB;
        }

   
};



int main()
{


    Bygning B[2] = 
    {
        Bygning(5, 10),
        Bygning(7,7)
    };

    


    std::fstream theFile("rotte.txt", std::ios::in);

    std::vector<std::string> vecBygning;
    std::vector<float> vecRom;
    
    

    if (theFile.is_open())
    {
        std::cout << "Open!" << std::endl;

        std::string inputLinje;
        while (std::getline(theFile, inputLinje))
        {
            //std::cout << inputLinje << std::endl;
            vecBygning.push_back(inputLinje);
        }
        theFile.close();
    }
    else 
    return 1;
    

   std::cout << vecBygning[0] << std::endl;
   std::cout << vecBygning[2] << std::endl;
    

    

    return 0;
}