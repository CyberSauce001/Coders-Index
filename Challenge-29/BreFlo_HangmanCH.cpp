#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <time.h> 
#include <cstdlib>
#include <sstream>
#include <string>
#include <ctype.h>

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
            minlen = min;
            maxlen = max;
            count=count_candidates();
            load_words();
        }
        void reset(int min, int max)
        {
            if (choices != NULL)
                delete [] choices;
            minlen = min;
            maxlen = max;

            count_candidates();
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
            while(infile>>word){
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
            while(infile>>word){
                if(infile.eof()) break;
                if(word.length() >= minlen && word.length() <= maxlen)
                {
                    choices[i++] = word;
                }
            }
            infile.close(); 
        }
        string pick_word()
        {
            int randNum;
            srand (time(NULL));
            randNum = rand() % count;
            return choices[randNum]; 
        }
};

void get_range_num(string prompt, int min, int max, int &number) {
            do {
                cout << "Current Min:" << min << endl << "Current Max: " << max << endl;
                cout << prompt << endl;
                cin >> number;
            }while(number <= 0 || number > 47);
            
            
}
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
void second_main()
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
}



void show_menu()
{
    for (int i = 1; i < 5; i++) {
       cout << i << ". Play the computer ";
       switch (i) {
        case 1:
            cout << "(auto select random range)\n";
            break;
        case 2:
            cout << "(min: 7, max 12)\n";
            break;
        case 3:
            cout << "(user selects/changes range)\n";
            break;
        case 4:
            cout << "(use same range stored in 3)\n";
            break;
        }
    }
   cout << "5. Two player mode (user1 enters the word, user2 guesses)\n";
   cout << "\nEnter choice:\n";
} 
int program(int choices) {   
   switch(choices) {
       case 1: {
            second_main();
            break;
       }
       case 2: {
           int min, max;
           srand(time(NULL));
           int num = rand() % 45 + 1;
           int num2 = rand() % 45 + 1;
           if (num < num2) {
               min = num;
               max = num2;
           }
           else if (num > num2) {
               max = num;
               min = num2;
           }

           cout << "Guess the word. " << endl <<"Type 'give up' to show answer " << endl; 
           Words words(min,max);
           string guess;
           string help = "give up";
           string answer = words.pick_word();
           
           cin.ignore();
           cin.clear();
           while (guess != words.pick_word()) {
                    cout <<"\nGuess: \n"; 
                    getline(cin, guess);
                if (guess.compare(help) == 0 )
                    cout << "Answer: " << answer << endl; 
                if (guess == answer)
                    break;
            }
           break;
       }
       case 3: {
                string prompt = "Choose within range of 1 to 46  ";
                int check; 
                int min = 0, max = 46;
                int number;
                cout << "Dear User: Please choose a number for selected range. " << endl;
                cout << "Range is for min: \n";
                cin >> number;
                if (number <=0 || number > 46) {
                    get_range_num(prompt, min, max, number);
                } else
                    min = number;
                cin.clear();
                cin.ignore();
                cout << "Range is for max: (3 digit apart)\n";
                cin >> number;

                while (number < (min+3) || number > 46) {
                  get_range_num(prompt, min, max, number);
                } 
                max = number;
                string tmp;
                Words words(min,max);
                cin.clear();
                cin.ignore();
                cout <<"Would you like to change the range? ( Y or N)\n";
                getline(cin, tmp);
                cout << tmp << endl;
                if(tmp == "Y" || tmp == "yes" || tmp == "Yes" || tmp == "y") {
                    cout << "Enter new min: ";
                    cin >> number;
                    if (number <=0 || number > 46) {
                        get_range_num(prompt, min, max, number);
                    } else
                        min = number;
                    cin.clear();
                    cin.ignore();
                    cout << "Enter new max (3 digit apart):  ";
                    cin >> number;
                    while (number < (min+3) || number > 46) {
                        get_range_num(prompt, min, max, number);
                    } 
                    max = number;
                    words.reset(min,max);
                    cin.clear();
                    cin.ignore();
                }
                cout << "Current Min:" << min << endl << "Current Max: " << max << endl;
                cout << "Guess the word. " << endl <<"Type 'give up' to show answer " << endl;
                string guess;
                string help = "give up";
                string answer = words.pick_word(); 
                while (guess != answer) {
                    cout <<"Guess: \n"; 
                    getline(cin, guess);
                    if (guess == help )
                        cout << "Answer: " << answer << endl; 
                    if (guess == answer) {
                        break;
                    }
                }
                ofstream file;
                file.open("data.txt");
                file << min << " " << max;
                file.close();
                break;
               
        }
       case 4:
       {   string line;
           int min=7, max=12;
           ifstream file("data.txt");
           if(file.is_open()) {
               while(!file.eof()) {
                    if(getline(file,line)) {
                        getline(file,line);
                        istringstream iss(line);
                        iss >> min >> max;

                    }
               } 
           }
           string guess;
           Words words(min, max);
           string answer = words.pick_word(); 
           cout << "Guess the word \n";
           string help = "give up";
           cin.ignore();
           cin.clear();
           getline(cin ,guess); 
                while (guess != answer) {
                    cout <<"\nGuess: \n"; 
                    getline(cin, guess);
                    if (guess.compare(help) == 0 )
                        cout << "Answer: " << answer << endl; 
                    if (guess == answer) {
                        break;
                    }
                }         
           file.close();
           break;
       }
       case 5: {
                   string word;
                   string guess;
                   int count = 0;
                   int hint = 3;
                   char char_word[46];
                   char guess_word[46];
                   cout <<"User 1 Please Enter a Word: \n";
                   cin.clear();
                   cin.ignore();
                   getline(cin,word);
                   strcpy(char_word,word.c_str());
                   system("clear");
                   cout << "You may begin\n\n\n";
                   for (int i = 0; char_word[i] != '\0'; i++) 
                   {
                           
                           cout << "_ ";
                   }
                   cout <<"\nUser 2 Please Guess The Word: \n";
                   getline(cin,guess);

                   do {
                       if (guess != word) {
                           cout <<"Nope guess again.\n";
                           getline(cin,guess);
                           count++;
                       }
                       if ((count == 3 || count == 6 || count == 9) && hint != 0 && word != guess) {
                            cout <<"Ask User 1 for hints ( Max Hint Left: " << hint << ")\n\n";
                            hint--;
                        }                            
                       if(count == 10){
                            cout <<"Give up? If so type 'yes' and answer will be given.\n";
                            cout <<"If not, type 'no'\n";
                            getline(cin,guess);
                            for (int i = 0; guess[i] != '\0'; i++) 
                            {
                                    tolower(guess[i]);
                            }

                            if(guess == "yes") {
                                cout << "ANSWER: " << char_word << endl << "GAME OVER\n";
                                return 0;
                            }
                            if(guess == "no") {
                                cout <<"To bad User 1 have a life, you will never know the answer." 
                                     << endl << "GAME OVER\n";
                                return 0;
                            }
                            else {
                                cout << "GAME OVER, regardless the choice!" << endl;
                                return 0;
                            }
                       }
                   }while(word != guess);

               }
           break;
   }
}

int main()
{   
    int choices;
    show_menu();
    cin >> choices;
    program(choices);
    return 0;
}


