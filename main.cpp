#include <iostream>
#include <fstream> //ifstreamobject
#include <vector>
#include <string> //getline


struct Bygg 
{
    public:
        float height;
        float width;
        float area;

        //defualt constructor
        Bygg()
        {
            height = 0;
            width = 0;
            area = height * width;
        }

        //Parameterized constructor
        Bygg(float height_a, float width_a)
        {
            height = height_a;
            width = width_a;
            area = width * height;
        }

        void print()
        {
            std::cout << "Bygg height: " << height << " width: " << width << std::endl;
        } 
};


struct Rom 
{
    public:
        float height;
        float width;
        float area;

        //defualt constructor
        Rom()
        {
            height = 0;
            width = 0;
            area = height * width;
        }

        //Parameterized constructor
        Rom(float height_a, float width_a)
        {
            height = height_a;
            width = width_a;
            area = width * height;
        }

        void print()
        {
            std::cout << "Rom: height: " << height << " width: " << width << std::endl;
        } 
};


class GreedyOptimizer
{
    public:
        //vector med bygninger og rom
        std::vector<Bygg> vecbygg;
        std::vector<Rom> vecrom;

        GreedyOptimizer(std::vector<Bygg> vecbygg_a, std::vector<Rom> vecrom_a)
        {
            vecbygg = vecbygg_a;
            vecrom = vecrom_a;
        }
        
};





int main()
{

    std::fstream theFile("input.txt", std::ios::in);
    std::vector<float> vec;
    float input;

    if (theFile.is_open())
    {
        while (theFile >> input)
        {
            vec.push_back(input);
        }
        theFile.close();
    }
    else 
    std::cout << "jeg er dum hahahahhah" << std::endl;

    



    std::vector<Bygg> byggVec;
    int antallbygg = vec[1];
    int n = vec.size();
    float height_B, width_B;

    //henter ut bygg fra input.txt og konstruerer objects
    for(int i = 0; i < antallbygg; ++i)
    {
        width_B = vec.back();
        vec.pop_back();

        height_B = vec.back();
        vec.pop_back();

        Bygg b(height_B, width_B); //create object with overloading the constructor
        byggVec.push_back(b);
        b.print();
    }


    //henter ut rom fra input.txt og konstruerer objects
    std::vector<Rom> romVec;
    int antallrom = vec[0];
    float height_R, width_R;

    for(int i = 0; i < antallrom; ++i)
    {
        width_R = vec.back();
        vec.pop_back();

        height_R = vec.back();
        vec.pop_back();

        Rom r(height_R, width_R);
        romVec.push_back(r);
        r.print();
    }

    
    GreedyOptimizer greed(byggVec, romVec);
    





    
   
    


    return 0;
}