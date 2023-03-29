#include <iostream>
#include <fstream> //ifstreamobject
#include <vector>
#include <string> //getline
#include <algorithm> //sort
#include <map> //multimap

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
        float usableHeight;
        float usableWidth;
        float useableArea;
        float wastedArea;

        //defualt constructor
        Bygg()
        {
            height = 0;
            width = 0;
            byggNr = 0;
            area = 0;
            wastedArea = 0;
            usableHeight = 0;
            usableWidth = 0;
            useableArea = 0;
        }

        //Parameterized constructor
        Bygg(float height_a, float width_a)
        {
            height = height_a;
            width = width_a;
            area = width * height;
            usableWidth = width_a;
            usableHeight = height_a;
            useableArea = usableWidth * usableHeight;

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
            romNr = 0;
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
        std::vector<Bygg>& vecbygg;
        std::vector<Rom>& vecrom;
        std::multimap<int, int> map;
        std::vector<Rom> leftoverRooms;

        //constructor 
        GreedyOptimizer(std::vector<Bygg>& vecbygg_a, std::vector<Rom>& vecrom_a)   
            : vecbygg(vecbygg_a), vecrom(vecrom_a)
        {
        

            //sorterer byggene etter areal, og gir dem unikt nummer
            std::sort(vecbygg.begin(), vecbygg.end(), [](Bygg& x, Bygg& y){return x.area > y.area;}); //Lambda expression, fancy greier              
            for(int i = 0; i < vecbygg.size(); ++i)
            {
                vecbygg[i].byggNr = i + 1;
            }
     
            //sorterer rommene etter areal, og gir dem unikt nummer
            std::sort(vecrom.begin(), vecrom.end(), [](Rom& x, Rom& y){return x.area > y.area;}); //Lambda expression, fancy greier
            for(int i = 0; i < vecrom.size(); ++i)
            {
                vecrom[i].romNr = i + 1;
            } 
            
        }
        
        //forsøk på å fordele rom ved hjelp av en "greedy"-tilnærming
        void add_room_by_size(std::vector<Rom>& vecrom, std::vector<Bygg>& vecbygg)
        {
            int antallRom = vecrom.size();
            int antallBygg = vecbygg.size();
 
    
            for (int i = 0; i < antallRom; i++)
            {
                for (int j = 0; j < antallBygg; j++)
                {
                    if (i >= antallRom) //nødløsning fordi jeg øker i til slutten av denne loopen. Uten denne så kan "i" bli større enn antall Rom, og da berøres minne som ikke skal berøres
                    {
                        break;
                    }
                    else if (vecbygg[j].useableArea < vecrom[i].area) //sjekker om det er nok areal tilgjengelig
                    {
                        leftoverRooms.push_back(vecrom[i]);
                        j--;
                    }
                    else if (vecbygg[j].usableHeight < vecrom[i].height) //sjekker romhøyde overstiger tilgjengelig høyde
                    {
                        leftoverRooms.push_back(vecrom[i]);
                        j--;
                    }
                    else if (vecbygg[j].usableWidth < vecrom[i].width) //sjekker om rombredde overstiger tilgjengelig bredde
                    {
                        leftoverRooms.push_back(vecrom[i]);
                        j--;
                    }
                    else
                    { 
                        //finner resterende areal etter rommet har blitt lagt til
                        vecbygg[j].useableArea = vecbygg[j].area - vecrom[i].area;
                        map.insert(std::pair <int, int> (vecbygg[j].byggNr, vecrom[i].romNr));  

                        //herifra og ned er for å finne resterende areal som faktisk kan brukes videre
                        float tempHeight;
                        float tempWidth;

                        tempHeight = vecbygg[j].usableHeight - vecrom[i].height;
                        tempWidth = vecbygg[j].usableWidth - vecrom[i].width;

                        float tempArea1;
                        float tempArea2;

                        tempArea1 = tempHeight * vecbygg[j].usableWidth; 
                        tempArea2 = vecbygg[j].usableHeight * tempWidth;
                    
                        if (tempArea1 > tempArea2)
                        {
                            vecbygg[j].usableHeight = tempHeight;
                        }
                        else if (tempArea1 < tempArea2)
                        {
                            vecbygg[j].usableWidth = tempWidth;
                        }
                    }

                    //hindrer at vi går til nest rom i det loopen brytes, da den yttereste loopen vil gå til neste rom
                    if ((j + 1) < antallBygg)
                    {
                        i++;
                    }                
                }
            }
        }

        //funksjon som lager output.txt og fyller den ut
        void writeToFile()
        {
            std::ofstream output ("output.txt");

            output << "Romfordeling:" << std::endl;
            for (auto it = map.begin(); it != map.end(); it++)
            {
                output << "ByggNr: " <<it-> first <<" ---- "<< "romNr: " <<it-> second << std::endl;
            }

            output << "\n" << std::endl;
            output << "Rom uten bygg:" << std::endl;
            
            if (leftoverRooms.size() > 0)
            {   
                for(int i = 0; i < leftoverRooms.size(); ++i)
                {
                    output << "RomNr: " << leftoverRooms[i].romNr << " fikk ikke plass. " << std::endl; 
                }
            }
            else
            output << "Alle rommene fikk plass." << std::endl;

            
            //printer ut info om rom
            output << std::endl;
            output << std::endl;
            output << "Info om rom" << std::endl; 
            output << "-----------" << std::endl;

            for (int i = 0; i < vecrom.size(); i++)
            {
                output << std::endl;
                output << "RomNr: " << vecrom[i].romNr << std::endl;
                output << "Areal: " <<vecrom[i].area << std::endl;
                output << "Høyde " << vecrom[i].height << std::endl;
                output << "Bredde: " << vecrom[i].width << std::endl;
                output << "-----------" << std::endl;
                output << "-----------" << std::endl;
            }

            //printer ut info om bygg
            output << std::endl;
            output << std::endl;
            output << "Info om bygg" << std::endl; 
            output << "-----------" << std::endl;

            for (int i = 0; i < vecbygg.size(); i++)
            {
                output << std::endl;
                output << "ByggNr: " << vecbygg[i].byggNr << std::endl;
                output << "Areal: " <<vecbygg[i].area << std::endl;
                output << "Høyde " << vecbygg[i].height << std::endl;
                output << "Bredde: " << vecbygg[i].width << std::endl;
                output << "Ubrukt areal: " << vecbygg[i].wastedArea << std::endl;
                output << "Brukt areal: " << vecbygg[i].useableArea << std::endl;
                output << "-----------" << std::endl;
                output << "-----------" << std::endl;
            }
            output.close();
        };        
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


    for(int i = 0; i < byggVec.size(); i++)
    {
        std::cout << "b4: " << byggVec[i].usableWidth << std::endl;
    }

    greed.add_room_by_size(romVec, byggVec);
    


    greed.writeToFile();
    
    for(int i = 0; i < byggVec.size(); i++)
    {
        std::cout << byggVec[i].usableWidth << std::endl;
    }
  
    
    
    





  


    



    return 0;
}