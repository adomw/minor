/*
gdúńsczé (?)
gf (gdúńsczi fùnt), ct (cetnar)
*/

#include<map>
#include<queue>
#include<string>
#include<iostream>

void printHelp(std::queue<std::string> h){
    while(!h.empty()){
        std::cout << h.front();
        h.pop();
    }
}

int main(){

    std::map<std::string, std::string> categories = {
        {"mm", "length"}, {"cm", "length"}, {"m", "length"}, {"km", "length"}, {"in", "length"}, {"ft", "length"}, {"ya", "length"}, {"mi", "length"}, {"pm", "length"},//m
        {"mg", "mass"}, {"g", "mass"}, {"kg", "mass"}, {"t", "mass"}, {"oz", "mass"}, {"lb", "mass"},//kg
        {"sm", "area"}, {"a", "area"}, {"ha", "area"}, {"skm", "area"}, {"sin", "area"}, {"sft", "area"}, {"smi", "area"}, {"ac", "area"},//a
        {"ml", "volume"}, {"l", "volume"}, {"gal", "volume"}, {"bbl", "volume"}, {"qm", "volume"}, {"qkm", "volume"}, {"qft", "volume"}, {"piw", "volume"},//l
        {"hp", "power"}, {"w", "power"}, {"kw", "power"}, {"mw", "power"},//w
        {"f", "temperature"}, {"c", "temperature"}, {"k", "temperature"},//k
        {"ms", "time"}, {"s", "time"}, {"min", "time"}, {"h", "time"}, {"d", "time"}, {"we", "time"}, {"y", "time"}//s
    };

    std::map<std::string, double> factors = {
        {"mm", 0.001}, {"cm", 0.01}, {"m", 1}, {"km", 1000}, {"in", 0.0254}, {"ft", 0.3048}, {"ya", 0.9144}, {"mi", 1609.344}, {"pm", 7146},//m
        {"mg", 0.000001}, {"g", 0.001}, {"kg", 1}, {"t", 1000}, {"oz", 0.0283495231}, {"lb", 0.4535923696},//kg
        {"sm", 0.01}, {"a", 1}, {"ha", 100}, {"skm", 10000}, {"sin", 0.0000064516}, {"sft", 0.0009290304}, {"smi", 25899.8811}, {"ac", 40.468564224},//a
        {"ml", 0.001}, {"l", 1}, {"gal", 3.785411784}, {"bbl", 158.987294928}, {"qm", 1000}, {"qkm", 1000000000000}, {"qft", 28.316846592}, {"piw", 0.5},//l
        {"hp", 745.699872}, {"w", 1}, {"kw", 1000}, {"mw", 1000000},//w
        {"f", 9.0 / 5.0}, {"c", 1}, {"k", 1},//k
        {"ms", 0.001}, {"s", 1}, {"min", 60}, {"h", 3600}, {"d", 86400}, {"we", 604800}, {"y", 31558149.504}//s
    };

    std::queue<std::string> helpMessage;

    helpMessage.push("------------------------------------------------------------------------------------------------\n");
    helpMessage.push("Syntax:\nXXX Units = Other Units\nE.g.:\n47.3kg = lb\n200hp = kw\nSpaces are ignored. Supported units:\n");
    helpMessage.push("Length: Milimetre[mm], Centimetre[cm], Metre[m], Kilometre[km], Inch[in], Foot[ft], Yard[ya],\n\tMile[mi], Polish Mile[pm];\n");
    helpMessage.push("Mass: Miligramme[mg], Gramme[g], Kilogramme[kg], Tonne[t], Ounce[oz], Pound[lb];\n");
    helpMessage.push("Area: Square Metre[sm], Are[a], Hectare[ha], Square Kilometre[skm], Square Inch[sin],\n\tSquare Foot[sft], Square Mile[smi], Acre[ac];\n");
    helpMessage.push("Volume: Mililitre[ml], Litre[l], Gallon[gal], Barrel[bbl], Cubic Metre[qm], Cubic Kilimetre[qkm],\n\tCubic Foot[qft], Piwo[piw];\n");
    helpMessage.push("Power: Horsepower[hp], Watt[w], Kilowatt[kw], Megawatt[mw];\n");
    helpMessage.push("Temperature: Degree Celsius[c], Degree Fahrenheit[f], Kelvin[k];\n");
    helpMessage.push("Time: Milisecond[ms], Second[s], Minute[min], Hour[h], Day[d], Week[we], Year[y];\n");
    helpMessage.push("\nAll units must be typed using lowercase characters. To exit, type \"exit\".\n");
    helpMessage.push("------------------------------------------------------------------------------------------------\n");

    std::string input, unit1, unit2;
    double value1 = 1, value2;
    printHelp(helpMessage);

    while(1){
        //std::cin.clear();
        std::cout << "\n\tEnter your query:\n";
        std::getline(std::cin, input);
        if(input == "exit")
            break;
        if(input == "help")
            printHelp(helpMessage);
        else{
            //remove spaces
            for(int i = 0; i < input.length(); i++)
                while((i < input.length()) && (input[i] == ' '))
                    input.erase(input.begin() + i);

            //assign new strings: units and original value int
            unit1 = input.substr(0, input.find('='));
            value1 = 0;
            while(((int)unit1[0] >= 48) && ((int)unit1[0] < 58)){
                value1 *= 10;
                value1 += (int)unit1[0];
                value1 -= 48;
                unit1.erase(unit1.begin());
            }
            if((unit1[0] == '.') || (unit1[0] == ',')){
                unit1.erase(unit1.begin());
                float coefficient = 0.1;
                while(((int)unit1[0] >= 48) && ((int)unit1[0] < 58)){
                    value1 += coefficient * ((int)unit1[0] - 48);
                    coefficient *= 0.1;
                    unit1.erase(unit1.begin());
                }
            }
            unit2 = input.substr(input.find('=') + 1, input.length() - 1);

            //calculate
            if((categories.find(unit1) != categories.end()) && (categories.find(unit2) != categories.end())){ //if both units are on the list
                if(categories[unit1] == categories[unit2]){
                    if(categories[unit1] == "temperature"){//for temperatures, units are expressed using specific scales
                        if(unit1 == unit2)
                            value2 = value1;
                        else{
                            if(unit1 == "f"){//f
                                value2 = (value1 - 32) / factors["f"];
                                if(unit2 == "k")
                                    value2 += 273.15;
                            }else
                            if(unit1 == "k"){//k
                                if(unit2 == "f")
                                    value2 = (value1 - 273.15) * factors["f"] + 32;
                                else//k -> c
                                    value2 = value1 - 273.15;
                            }
                            else{//c
                                if(unit2 == "f")
                                    value2 = value1 * factors["f"] + 32;
                                else//c -> k
                                    value2 = value1 + 273.15;
                            }
                        }
                    }
                    else
                        value2 = 1.0 * value1 * factors[unit1] / factors[unit2];//non-temperature units can simply be multiplied and divided to get the right result
                    std::cout << value1 << unit1 << " = " << value2 << unit2 << "\n";
                }
                else //if units belong to different categories
                    std::cout << "Units not interchangable.\n";
            }
            else //if a unit is not present on the list
                std::cout << "Unknown units or incorrect syntax." << "\n";
        }
   }
    //system("pause");
    return 0;

}

