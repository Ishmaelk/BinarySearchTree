#include<iostream>
#include<string>
#include"Dictionary.h"

int main() {
    std::string str="abcedbee";

    Dictionary<char,unsigned short> dict;

    if(dict.IsEmpty()) std::cout<<"Empty\n"; // The message should appear on the screen

    for(int i=0; i<str.size(); i++)
    {
        if(dict.Count(str[i])==0) dict[str[i]]=1;
        else dict[str[i]]+=1;
    }

    std::cout<<"The number of unique letters is "<<dict.Size()<<std::endl; // Should show 5
    std::cout<<"The height of the tree is "<<dict.Height()<< std::endl;     // Should show 4
    std::cout<<"The letter a happened "<<dict['a']<<" times\n";        //Should show 1
    std::cout<<"The letter e happened "<<dict['e']<<" times\n\n";      //Should show 3

    dict.Remove('c');
    std::cout<<"The number of unique letters is "<<dict.Size()<<std::endl; // Should show 4
    std::cout<<"The height of the tree is "<<dict.Height()<<std::endl;     // Should show 4
    std::cout<<"The letter a happened "<<dict['d']<<" times\n";        //Should show 1
    if(dict.Count('c')==0) std::cout<<"Now the letter e is absent\n\n"; //This message should appear on the screen

    dict.Balance();
    std::cout<<"The height of the tree is "<<dict.Height()<< std::endl;     // Should show 3

    dict.Clear();
    std::cout<<"The number of unique letters is "<<dict.Size()<<std::endl; // Should show 0
    std::cout<<"The height of the tree is "<<dict.Height()<< std::endl;     // Should show 0

    return 0;
}
