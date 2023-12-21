#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

void add_to_file(string x){
        ofstream myfile (x);
        if (myfile.is_open())
         {
            myfile << "This is a line.\n";
            myfile << "This is another line.\n";
            myfile << "And this is a different line.\n";
            myfile.close();
         }
         else cout << "Unable to open file";

    }

int max_line_len(string file_name){
    string line;
    int max = 0;
    ifstream myfile;
    myfile.open(file_name);
    if (myfile.is_open())
    {
        while (getline(myfile,line)){
                if (line.length()>max){
                    max = line.length();
                }
            }
       myfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
    return max;
}

//zwraca numer gdzie sie slowo koñczy od lewej, a dok³adnie pozycje gdzie po slowie jest spacja
int next_word(string line, int position){
    int i=position;

    //znajdujemy spacje po wyrazie
    while (line[i]!=' ' && i < line.length()){
        //cout << line[i] << endl;
        i++;
    }
    //w przypadku jak miedzy wyrazami jest wiecej spacji to znajdujemy pozycje ostatniej
    while (line[i+1]==' ' && i < line.length()){
        i++;
    }
    //if else ze jak i dojdzie do koñca lini to cofa sie do 0 i szuka spacji od pocz¹tku
    if (i>=line.length()){
        return next_word(line,0);
    }else{
        return i;
    }
}

//zwraca numer gdzie sie s³owo zaczyna od prawej, a dok³adnie pozycje gdzie przed slowem jest spacja
int rev_next_word(string line, int position){
    int i=position;

    while (line[i]!=' '&& i>=0){
            //cout <<line[i] << line.length()-1 << "  -  " << i<< "\n";
            i--;
    }
    //w przypadku jak miedzy wyrazami jest wiecej spacji to znajdujemy pozycje ostatniej
    while (line[i-1]==' ' && i >= 0){
        i--;
    }
    if (i<=0){
        return rev_next_word(line,(line.length()-1));
    }else{
        return i;
    }
}

string fill_spaces(string line, int line_len)
{
    bool left = true;
    int i=0;
    int j=line.length();
    if (line!=""){
        while (line.length()<line_len){
            if(j<=i){
                i=0;
                j=line.length();
                left=true;
            }
            if (left==true){
                i=next_word(line,i);
                if(j>i){
                    line.insert(i," ");
                    //cout << line << " i =" << i << " left=" << left << endl;
                    i=i+2;
                    j++;
                    left = false;
                }
            }else{
                j=rev_next_word(line,j);

                if(j>i){
                    line.insert(j," ");
                    //cout << line << " j =" << j << " left=" << left<< endl;
                    j=j-2;
                    left = true;
                }
            }
        }
    }else{
        //cout << line << "\n";
    }
    //cout << line << "\n";
    return line;
}

//The function saves justificated text to file and prints the output in console as well
void print_file(string file_name, int max_line_len){
    string line;
    vector<string> text_array{};
    ifstream myfile;
    myfile.open(file_name);
    if (myfile.is_open())
    {
        while (getline(myfile,line)){

                if (line!=""){
                    line=fill_spaces(line,max_line_len);
                    cout << line << "\n";
                }else{
                    cout << line << "\n" ;
                }
                text_array.push_back(line);
            }
        myfile.close();
        ofstream myfile ("example.txt");
        if (myfile.is_open())
        {
            for (int i = 0; i < text_array.size(); i++)
                myfile << text_array[i]<< "\n";

            myfile.close();
        }
        else cout << "Unable to open file";
    }
    else {
        cout << "Unable to open file" << endl;
    }
}


int main() {
  //add_to_file("example.txt");
  //string s = "In the morning, glad, I see";
  //int max_line_l = max_line_len("file.txt");

  //cout << rev_next_word(s,5) << endl;
  //cout << fill_spaces(s,60) << endl;
  print_file("file.txt",37);
  //system("pause");
}
