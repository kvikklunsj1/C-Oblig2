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

    


    std::fstream theFile("input.txt", std::ios::in);

    std::vector<std::string> vecBygning;
    std::vector<float> vecRom;
    
    float x, y;

    if (theFile.is_open())
    {
        std::cout << "Open!" << std::endl;

        std::string inputLinje;
        while (theFile >> x)
        {
            //std::cout << inputLinje << std::endl;
            vecRom.push_back(x);
        }
        theFile.close();
    }
    else 
    return 1;
    

 
   for (auto i: vecRom)
   {
    std::cout << i << std::endl;
   }

   std::cout << "Antall Bygg: " << vecRom[1] << std::endl;

    return 0;
}