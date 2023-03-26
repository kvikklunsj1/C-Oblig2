#include <iostream>
#include <fstream> //ifstreamobject
#include <vector>
#include <string> //getline
#include <algorithm> //sort
#include <map>

void printMap(std::multimap<int, int> &map)
{
     for(auto it = map.begin(); it != map.end(); it++)
    {
        std::cout << "ByggNr: " <<it-> first <<" ---- "<< "romNr: " <<it-> second << std::endl;
    }
}

/* void printBygg(struct Bygg, std::vector<Bygg>)
{
    for (int i)
} */




struct Bygg 
{
    public:
        float height;
        float width;
        float area;
        int byggNr; //bygg Nr 1 har størst areal osv...
        float useableArea;
        float wastedArea;

        //defualt constructor
        Bygg()
        {
            height = 0;
            width = 0;
            int byggNr = 0;
            area = height * width;
            useableArea = area;
            wastedArea = 0;
            
        }

        //Parameterized constructor
        Bygg(float height_a, float width_a)
        {
            height = height_a;
            width = width_a;
            area = width * height;
        }     
};

struct Rom 
{
    public:
        float height;
        float width;
        float area;
        int romNr; //rom Nr 1 har størst areal osv...

        //defualt constructor
        Rom()
        {
            height = 0;
            width = 0;
            int romNr = 0;
            area = height * width;
        }

        //Parameterized constructor
        Rom(float height_a, float width_a)
        {
            height = height_a;
            width = width_a;
            area = width * height;
        }
};

class GreedyOptimizer
{
    public:
        //vector med bygninger og rom
        std::vector<Bygg> vecbygg;
        std::vector<Rom> vecrom;

        //constructor 
        GreedyOptimizer(std::vector<Bygg> &vecbygg_a, std::vector<Rom> &vecrom_a)
        {
            vecbygg = vecbygg_a;
            vecrom = vecrom_a;

            //sorterer byggene etter areal, og gir dem unikt nummer
            std::sort(vecbygg.begin(), vecbygg.end(), [](const Bygg& x, const Bygg& y){return x.area > y.area;}); //Lambda expression, fancy greier              
            for(int i = 0; i < vecbygg.size(); ++i)
            {
                vecbygg[i].byggNr = i + 1;
            }
     
            //sorterer rommene etter areal, og gir dem unikt nummer
            std::sort(vecrom.begin(), vecrom.end(), [](const Rom& x, const Rom& y){return x.area > y.area;}); //Lambda expression, fancy greier
            for(int i = 0; i < vecrom.size(); ++i)
            {
                vecrom[i].romNr = i + 1;
            }

            printBygg(vecbygg);
            printRom(vecrom);
        }









        void printBygg(std::vector <Bygg> vector)
        {
            for (int i = 0; i < vector.size(); i++)
            {
                std::cout << vector[i].byggNr << std::endl;
            }
        }

        void printRom(std::vector <Rom> vector)
        {
            for (int i = 0; i < vector.size(); i++)
            {
                std::cout << vector[i].romNr << std::endl;
            }
        }
};



int main()
{

    //leser inn hele input.txt inn i vec som floats
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
    return 1;

    

    std::vector<Bygg> byggVec;
    int antallbygg = vec[1];
    int n = vec.size();
    float height_B, width_B;

    //henter ut bygg fra vec og konstruerer objects
    //leser bakerste verdi i vec, for å så slette verdien
    for (int i = 0; i < antallbygg; ++i)
    {
        width_B = vec.back();
        vec.pop_back();

        height_B = vec.back();
        vec.pop_back();

        Bygg b(height_B, width_B); //create object with overloading av constructor
        byggVec.push_back(b);
    }



    //henter ut rom fra vec og konstruerer objects på samme måte som med bygg
    std::vector<Rom> romVec;
    int antallrom = vec[0];
    float height_R, width_R;

    for (int i = 0; i < antallrom; ++i)
    {
        width_R = vec.back();
        vec.pop_back();

        height_R = vec.back();
        vec.pop_back();

        Rom r(height_R, width_R);
        romVec.push_back(r);
    }

    //sender rommene til optimizeren, hvor de automagically blir fordelt i de ulike byggene
    GreedyOptimizer greed(byggVec, romVec);
  
    
    
    





    std::ofstream output ("output.txt");

    output << "yalla yalla" << std::endl;

    output.close();


    



    return 0;
}