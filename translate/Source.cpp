#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    typedef multimap<string, string> strMap;
    strMap enru;
    strMap::iterator it;
    stringstream ss;
    string en;
    string ru;
    string str;
    ifstream fin("Trans.txt", ios::in | ios::binary);
    string buff;
    while (!fin.eof())
    {
        getline(fin, buff);
        ss << buff;
        ss >> en >> ru;

        enru.insert(make_pair(en, ru));
    }
    while (true)
    {
        cout << "Введите слово/предложение. Для выхода из программы введите символ q:\n";
        getline(cin, buff);
        for (int i = 0; i < buff.size(); ++i)
        {
            if (ispunct((unsigned char)buff[i]))
                buff[i] = ' ';
        }
        for_each(buff.begin(), buff.end(), [](char& c) { c = tolower(c); });

        replace_if(buff.begin(), buff.end(), ispunct, ' ');
        ru.clear();
        ss.clear();
        ss << buff;
        for (ss >> en; !en.empty(); ss >> en)
        {
            if (buff == "q")
            {
                return 0;
            }
            it = enru.find(en);
            if (it != enru.end())
            {
                
                ru += it->second;
            }
            else
            {
                cout << "<Слово отсутствует, дополните словарь>\n";
            }
            ru += " ";
            en.clear();
        }
        cout << "Перевод: " << ru << endl;
    }
}