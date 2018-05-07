#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
class Words
{
    private:
        int minLen, maxLen;
        int count;
        string *choices;
    public:
        Words(int min, int max);
        int count_candidates();
        void load_words();
        string pick_word();
};


Words::Words(int min, int max)
{
    minLen = min;
    maxLen = max;
    count = count_candidates();
    choices = new string[count];
    if(count != 0)
        load_words();
}

int Words::count_candidates()
{
    string filename = "enable1.txt";
    ifstream infile(filename.c_str());
    if(!infile.is_open())
    {
        cout << "Error opening file " << filename <<endl;
        return 0;
    }
    else
    {
        string word;
        int total = 0;
        while(infile >> word)
        {
            if(word.length() >= minLen && word.length() <=maxLen)
                total++;
        }
        infile.close();
        return total;
    }
}

void Words::load_words()
{
    string filename = "enable1.txt";
    ifstream infile(filename.c_str());
    if(!infile.is_open())
    {
        cout << "Error opening file " << filename <<endl;
    }
    else
    {
        string word;
        int index = 0;
        while(infile >> word)
        {
            if(word.length() >= minLen && word.length() <=maxLen)
                choices[index++] = word;
        }
        infile.close();
    }

}
string Words::pick_word()
{
    if(count == 0)
        return "";
    int index = rand() % count;
    return choices[index];
}

int main()
{
    int min, max;
    cout << "Enter min: ";
    cin >> min;
    cout << "Enter max: ";
    cin >> max;
    Words words(min, max);
    cout << words.pick_word() << endl;

}
