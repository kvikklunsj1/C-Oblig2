void add_room_by_size(std::vector<Rom> r, std::vector<Bygg> b)
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
                    if (i >= antallRom) //nødløsning fordi jeg øker i til slutten av denne loopen. Uten denne så kan "i" bli større enn antall Rom, og da berøres minne som ikke skal berøres
                    {
                        break;
                    }
                    else if (vecbygg[j].area < vecrom[i].area) //sjekker om det er nok areal tilgjengelig
                    {
                        leftoverRooms.push_back(vecrom[i]);
                        j--;
                    }
                    else if (vecbygg[j].height < vecrom[i].height) //sjekker romhøyde overstiger tilgjengelig høyde
                    {
                        leftoverRooms.push_back(vecrom[i]);
                        j--;
                    }
                    else if (vecbygg[j].width < vecrom[i].width) //sjekker om rombredde overstiger tilgjengelig bredde
                    {
                        leftoverRooms.push_back(vecrom[i]);
                        j--;
                    }
                    else
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
                                vecbygg[j].area = vecbygg[j].area - tempArea1;
                                //vecbygg[j].wastedArea =
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
                std::cout << "ByggNr: " <<it-> first <<" ---- "<< "romNr: " <<it-> second << std::endl;
            }

            if(leftoverRooms.size() > 0)
            {
                for(int i = 0; i < leftoverRooms.size(); ++i)
                {
                    std::cout << "RomNr: " << leftoverRooms[i].romNr << " fikk ikke plass. " << std::endl; 
                }
            }
        }