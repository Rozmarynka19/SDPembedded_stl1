#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <map>

//ile znakow nie rozpoczynajacych sie od 10... sklada sie string
size_t utf8Len(std::string s)
{ 
    //funkcja lambda sprawdza, czy znak jest angielskim znakiem (pierwsze 128 znakow z ASCII)
    return std::count_if(s.begin(),s.end(),[](char c){return (static_cast<unsigned char>(c) & 0xC0) != 0x80; });
}

int main(void)
{
    std::ifstream input("../slowa.txt");
    std::string line;

    std::multimap<std::string,std::string> dictionary;

    std::cout<<"Loading dictionary...\n";
    while(std::getline(input,line))
    {
        std::getline(input,line);

        line.erase(std::remove(line.begin(),line.end(),'\r'),line.end());
        if(line.size() == utf8Len(line))
        {
            std::string sorted = line;
            std::sort(sorted.begin(),sorted.end());
            dictionary.insert(std::pair<std::string,std::string>(sorted,line));
        }
    }

    std::cout<<"Insert letters you have (0 to quit, . if you have blank block):"<<std::endl;
    std::string in;
    std::cin>>in;

    std::vector<std::string> result;
    while (in!="0")
    {
        int initialLength = in.size();
        std::sort(in.begin(),in.end());
        in.erase(std::remove(in.begin(),in.end(),'.'),in.end());
        
        for(auto it=dictionary.begin();it!=dictionary.end();it++)
            if(it->first.size()<=initialLength && std::includes(it->first.begin(),it->first.end(),in.begin(),in.end()))
                result.push_back(it->second);


        for(auto it = result.begin(); it!=result.end();++it)
            std::cout<<*it<<std::endl;

        std::cout<<"Insert letters you have (0 to quit, . if you have blank block):"<<std::endl;
        std::cin>>in;
        result.clear();
    }
    
    return 0;
}