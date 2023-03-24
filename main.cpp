#include <iostream>
#include <fstream> //ifstreamobject
#include <vector>
#include <string> //getline
#include <algorithm> //sort
#include <map>


struct Bygg 
{
    public:
        float height;
        float width;
        float area;
        int byggNr; //bygg Nr 1 har størst areal osv...

        //defualt constructor
        Bygg()
        {
            height = 0;
            width = 0;
            int byggNr = 0;
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

        //constructor 
        GreedyOptimizer(std::vector<Bygg> vecbygg_a, std::vector<Rom> vecrom_a)
        {
            vecbygg = vecbygg_a;
            vecrom = vecrom_a;
        }


        void sort_Bygg()
        {
            std::sort(vecbygg.begin(), vecbygg.end(), [](const Bygg& x, const Bygg& y){return x.area > y.area;}); //Lambda funksjon, fancy greier
                        
            //gir de sorterte byggene hvert sitt nr etter areal
            for(int i = 0; i < vecbygg.size(); ++i)
            {
                vecbygg[i].byggNr = i + 1;
            }
        }

        void sort_Rom()
        {
            for(int i = 0; i < vecrom.size(); ++i)
            {
                std::cout << "Før: " << vecrom[i].romNr << std::endl; //skal slettes
            }
 
            std::sort(vecrom.begin(), vecrom.end(), [](const Rom& x, const Rom& y){return x.area > y.area;}); //Lambda funksjon, fancy greier

            //gir de sorterte rommene hvert sitt nr etter areal
            for(int i = 0; i < vecrom.size(); ++i)
            {
                vecrom[i].romNr = i + 1;
                std::cout << "Etter: " << vecrom[i].romNr << std::endl; //skal slettes
            }
        }


        void add_room_by_size()
        {
            int antallRom = vecrom.size();
            int antallBygg = vecbygg.size();

            float newArea = 0;
            float areaWasted = 0; 
            std::vector<Rom> leftoverRooms;
            std::multimap<int, int> map;
    
            for (int i = 0; i < antallRom; i++)
            {
                for (int j = 0; j < antallBygg; j++)
                {
                    float tempHeight;
                    float tempWidth;

                    tempHeight = vecbygg[j].height - vecrom[i].height;
                    tempWidth = vecbygg[j].width - vecrom[i].width;

                    float tempArea1;
                    float tempArea2;

                    tempArea1 = tempHeight * vecbygg[j].width; 
                    tempArea2 = vecbygg[j].height * tempWidth;


                    if (tempArea1 > tempArea2)
                    {
                        if (tempArea1 < 0) // om arealet er negativt betyr det at det ikke er plass til rommet i bygget
                        {
                            leftoverRooms.push_back(vecrom[i]);
                        }
                        else
                        {
                            vecbygg[j].height = tempHeight;
                            map.insert(std::pair <int, int> (vecbygg[j].byggNr, vecrom[i].romNr));
                        }
                    }
                    else if (tempArea1 < tempArea2)
                    {
                        if (tempArea2 < 0) // om arealet er negativt betyr det at det ikke er plass til rommet i bygget
                        {
                            leftoverRooms.push_back(vecrom[i]);
                        }
                        else
                        {
                            vecbygg[j].width = tempWidth;
                            map.insert(std::pair <int, int> (vecbygg[j].byggNr, vecrom[i].romNr));
                        }
                    }
            

                    //hindrer at vi går til nest rom i det loopen brytes, da den yttereste loopen vil gå til neste rom
                    if ((j + 1) < antallBygg)
                    {
                        i++;
                    }
                }
            }

            for(auto it = map.begin(); it != map.end(); it++)
            {
                std::cout <<it-> first <<"----"<<it-> second << std::endl;
            }

            for(int i = 0; i < leftoverRooms.size(); ++i)
            {
                std::cout << "Disse fikk ikke plass: " << leftoverRooms[i].romNr << std::endl; 
            }
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
    for (int i = 0; i < antallbygg; ++i)
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

    for (int i = 0; i < antallrom; ++i)
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
    
    

    greed.sort_Bygg();
    greed.sort_Rom();
    greed.add_room_by_size();
   
    


    return 0;
}