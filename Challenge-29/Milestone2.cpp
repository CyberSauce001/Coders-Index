#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <time.h> 

using namespace std;

class Words
{
    private:
        int minlen, maxlen;
        int count; 
        string *choices;
    public:

        Words(){}
        Words(int min, int max)
        {
            minlen=min;
            maxlen=max;
            count=count_candidates();
            load_words();
        }
        int count_candidates()
        {
            count=0;
            ifstream infile("enable1.txt");
            if (infile.fail()) {
                cout << "Error no enable1.txt.\\n";
                exit(0);
            }
            string word;
            while(!infile.eof()){
                infile>>word;
                if(infile.eof()) break;
                if(word.length()>=minlen&& word.length()<=maxlen)
                {
                    count++;
                }
            }
            infile.close();
            return count;
        }
        void load_words()
        {
            choices=new string[count];
            ifstream infile("enable1.txt");
            if (infile.fail()) {
                cout << "Error no enable1.txt.\\n";
                exit(0);
            }
            int i=0;
            string word;
            while(!infile.eof()){
                infile>>word;
                if(infile.eof()) break;
                if(word.length()>=minlen&& word.length()<=maxlen)
                {
                    choices[i++]=word;
                }
            }
            infile.close(); 
        }
        string pick_word()
        {
            srand (time(NULL));
            int randNum=1+rand() % count; 
            return choices[randNum]; 
        }
};

class Hangman
{
    private:
    char word[40];
    char progress[40];
    int word_length;
   void clear_progress(int length)
    {
        int i=0;
        for(i=0;i<length;i++)
        {
            progress[i]='-';
        }   
            progress[i]='\0';
    }
    protected:
        int matches;
        char last_guess;
        string chars_guessed;
        int wrong_guesses;
        int remaining;
        void initialize(string start)
        {
            chars_guessed="";
            wrong_guesses=6;
            strcpy(word,start.c_str());
            word_length=strlen(word);
            remaining=6;
            clear_progress(word_length);
        }
    public:
        Hangman(string start)
        {
            initialize(start);
        }
        int get_remaining()
        {
            return remaining;
        }
        char* getWord()
        {
            return word;
        }
        char* get_progress()
        {
            return progress;
        }
        bool is_word_complete()
        {
            if(strcmp(progress, word)==0)
                return true;
            else
                return false;
        }
    protected:
        bool check(char user_guess){
            if(last_guess!=user_guess){
                matches=0; 
                bool flag=false; 
                if(strchr(word,user_guess)!=NULL)
                {
                    for(int i=0;i<strlen(word);i++)
                    {
                        if(word[i]==user_guess)
                        {
                            progress[i]=user_guess;
                            flag=true;
                            chars_guessed+=user_guess;
                            matches++;
                        }
                    }
                }      
                else
                {
                    wrong_guesses -= 1;
                }
                    remaining--;
                    last_guess=user_guess;
            }
        }
};

class HangmanConsole : public Hangman
{
    public:
        HangmanConsole(string start) : Hangman(start){}
        void show_man(int stage) {
            switch (stage) {
                case 6:
                    cout << "  +--- " << endl;
                    cout << "  |    " << endl;
                    cout << "  |    " << endl;
                    cout << "__|__  " << endl;
                break;
                case 5:
                    cout << "  +--- " << endl;
                    cout << "  |  O " << endl;
                    cout << "  |    " << endl;
                    cout << "__|__  " << endl;
                break;
                case 4:
                    cout << "  +--- " << endl;
                    cout << "  |  O " << endl;
                    cout << "  |   \\" << endl;
                    cout << "__|__  " << endl;
                break;
                case 3:
                    cout << "  +--- " << endl;
                    cout << "  |  O " << endl;
                    cout << "  | / \\" << endl;
                    cout << "__|__  " << endl;
                break;
                case 2:
                    cout << "  +--- " << endl;
                    cout << "  |  O " << endl;
                    cout << "  | /|\\" << endl;
                    cout << "__|__  " << endl;
                break;
                case 1:
                    cout << "  +--- " << endl;
                    cout << "  |  O " << endl;
                    cout << "  | /|\\" << endl;
                    cout << "__|_/   " << endl;
                    break;
                case 0:
                    cout << "  +--- " << endl;
                    cout << "  |  O " << endl;
                    cout << "  | /|\\" << endl;
                    cout << "__|_/ \\" << endl;
                    cout<<"Game over";
                break;
            }
        }
        void show_info() {
            chars_guessed=get_progress();
            show_man(wrong_guesses);
            cout<< endl << matches <<" matches were found "<< endl << "Last guessed:" << last_guess;
            cout << endl << remaining <<" attempts are remaining\n";
            cout << endl << chars_guessed <<" letters have been guessed so far \n";

        }   

        friend void operator >> ( istream  &input,HangmanConsole &game ) { 
            char ch;
            cin >> ch;
            if(!game.is_word_complete())
            {
                bool status=game.check(ch); 
            }   
        }
};
int main()
{
    Words words(7,10); 
    HangmanConsole game(words.pick_word());
    cout << "HANGMAN" << endl <<"-------" << endl << endl;
    cout << "Your word is: " <<game.get_progress() << endl;
    while (!game.is_word_complete() && game.get_remaining() > 0)
    {
       cout << endl;
       cout << "Enter your guess:";
       cin >> game;
       system("clear"); // NON-PORTABLE,ONLY WORKS ON LINUX
       game.show_info();
       if (game.get_remaining() == 0)
           cout << "Sorry, you lose." << endl;
    }
    return 0;
}


