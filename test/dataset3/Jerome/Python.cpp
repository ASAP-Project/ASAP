/* 
 * File:   Python.cpp
 * Author: codecaine aka Jerome Scott II
 * 
 * Created on July 29, 2010, 5:01 PM
 */

#include "StdAfx.h"
#include "Python.h"
#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

Python::Python()
    : ZERO(0)
{

}

string Python::ascii_lowercase() const
{
    return "abcdefghijklmnopqrstuvwxyz";
}

string Python::ascii_uppercase() const
{
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

string Python::digits() const
{
    return "0123456789";
}

string Python::octaldigits() const
{
    return "01234567";
}
string Python::hexdigits() const
{
    return "0123456789abcdefABCDEF";
}

string Python::ascii_letters() const
{
    return ascii_lowercase() + ascii_uppercase();
}

string Python::punctuation() const
{
    return "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
}

string Python::whitespace() const
{
    return "\t\n\x0b\x0c\r ";
}

string Python::printable() const
{
    return digits() + ascii_letters() + punctuation() + whitespace();
}

string Python::lower(const string str)
{
    temp_str.clear();
    if(str.length() != ZERO)
    {
        for(uint x = ZERO; x < str.length(); x++)
        {
            //if the current index of the string is not lowercase convert it to lowercase else just append the character
            if(!islower(str[x]))
                temp_str += tolower(str[x]);
            else
                temp_str += str[x];
        }
    }
    return temp_str;
}

string Python::upper(const string str)
{
    temp_str.clear();
    if(str.length() != ZERO)
    {
        for(uint x = ZERO; x < str.length(); x++)
        {
            //if the current index of the string is not uppercase convert it to uppercase else just append the character
            if(!isupper(str[x]))
                temp_str += toupper(str[x]);
            else
                temp_str += str[x];
        }
    }
    return temp_str;
}

vector<string> Python::split(const string str)
{
    temp_vec.clear();
    temp_str.empty();
    if(!str.empty())
    {
        for(uint x = ZERO; x < str.length(); x++)
        {
            temp_str = str[x];
            temp_vec.push_back(temp_str); //add each character to a vector as a string
            temp_str.clear();
        }
    }
    return temp_vec;
}

/* This is a modified version of pythons.
 * Spaces will not be added to the vector and a string can be choosen for a seperator *
 * Also seperaters that are right next to each other are counted as 1 whole seperator *
 *                                                                                    */
vector<string> Python::split(const string str, string sep)
{
    temp_vec.clear();
    if(!str.empty())
    {
        const unsigned short STRLEN = 255;
        //converting str to a c string
        char temp_str[STRLEN];
        strcpy(temp_str,str.c_str());

        //converting sep to a cstring
        char temp_sep[STRLEN];
        strcpy(temp_sep,sep.c_str());

        char *ptemp;

        //retrieve first token from string
        ptemp = strtok (temp_str,temp_sep);

        //while the string has tokens continue
        while (ptemp != NULL)
        {
            temp_vec.push_back(static_cast<string>(ptemp)); //cast the c string to a string and append it to the vector
            ptemp = strtok (NULL, temp_sep); //retrieve more tokens
        }
    }
    return temp_vec;
}

/* This is a modified version of pythons.
 * Spaces will not be added to the vector and a string can be choosen for a seperator *
 * Also seperaters that are right next to each other are counted as 1 whole seperator *
 *                                                                                    */
vector<string> Python::split(const string str, const string sep, const uint max)
{
    temp_vec.clear();
    if(!str.empty())
    {
        uint count = ZERO;
        const uint STRLEN = 255;
        //converting sep to a c string
        char ctemp_str[STRLEN];
        strcpy(ctemp_str,str.c_str());

        //converting sep to a c string
        char temp_sep[STRLEN];
        strcpy(temp_sep,sep.c_str());

        char *ptemp;

        //retriving first token
        ptemp = strtok (ctemp_str,temp_sep);

        //continue loop while there are tokens
        while (ptemp != NULL)
        {
            count++;
            //if count is less then maxium amount of tokens to retrieve continue getting tokens
            if(count < max)
            {
                temp_vec.push_back(static_cast<string>(ptemp)); //case a c string to a string and append it to a vector
                ptemp = strtok (NULL, temp_sep); //retrieve more tokens
            }
            else
            {
                //once the max tokens have been retrieve append the rest of the string to the vector
                temp_vec.push_back(static_cast<string>(ptemp)); //convert a c string to a string
                ptemp = strtok (NULL, "\0"); //retrieve the rest of the string by making the token null
            }
      }
    }
    return temp_vec;
}

string Python::lstrip(const string str)
{
    temp_str = str;
    if (str.length() != ZERO)
    {
        for(uint x = ZERO; x < str.length(); x++)
        {
            //if the starting postions of a string is a space remove it else break the loop and return the string
            if(str[x] == ' ')
            {
                temp_str = str.substr(x + 1,str.length()); //return the string without the space
            }
            else
            {
                break;
            }
        }
    }
    return temp_str;
}

string Python::rstrip(const string str)
{
    temp_str = str;
    if(str.length() != ZERO)
    {
        for(uint x = str.length() - 1; x > ZERO; x--)
        {
            //if the end of the string is a space remove it else break the loop and return the string
            if(str[x] == ' ')
            {
                temp_str = str.substr(ZERO,x); //return the string without the space at the end
            }
            else
            {
                break;
            }
        }
    }
    return temp_str;
}

string Python::strip(string str)
{
    if(!str.empty())
    {
        str = rstrip(str); //strip spaces from the end of the string
        str = lstrip(str); //strip spaces from the beginning of the string
    }
    return str;
}

string Python::strip(string str, const string invalids)
{
    if(str.length() != ZERO)
    {
        const int INVALIDS_MAX = invalids.length();

        size_t pos;

        for(int y = ZERO; y < INVALIDS_MAX; y++)
        {
            for(uint x = ZERO; x < str.length(); x++)
            {
                pos = str.find(invalids[y]); //retrieve the index of an invalid character
                if (pos != string::npos) //if there is a invalid character position remove it
                    str.erase(pos,1);
            }
        }
  }
  return str;
}

bool Python::startswith(const string str, const string start)
{
    if(str.length() != ZERO)
    {
        //compare if the strings are equal
        const short int value = start.compare(str.substr(ZERO,start.length()));
        //if the return value is not 0 then the strings are not equal else they are equal
        if(value != ZERO)
            return false;
        else
            return true;
   }
    else
        return false;
}

bool Python::endswith(const string str, const string end)
{
    if(str.length() != ZERO)
    {
        //compare if the strings are equal
        const short int value = end.compare(str.substr(str.length() - end.length(), end.length()));
        //if the return value is not 0 then the strings are not equal else they are equal
        if(value != ZERO)
            return false;
        else
            return true;
    }
    else
        return false;
}

string Python::swapcase(string str)
{
    if(str.length() != ZERO)
    {
        for(uint x = ZERO; x < str.length(); x++)
        {
            //if the current string index character is lowercase convert it to uppercase else convert it to lowercase
            if(islower(str[x]))
                str[x] = toupper(str[x]);
            else
                str[x] = tolower(str[x]);
        }
    }
    return str;
}

string Python::capitalize(string str)
{
if(str.length() != ZERO)
    //if the first character of the string is lowercase convert it to uppercase
    if(islower(str[ZERO]))
        str[ZERO] = toupper(str[ZERO]);
return str;
}

string Python::title(const string str)
{
    temp_vec.clear();
    if(!str.empty())
    {
        const unsigned short STRLEN = 255;
        //convert str to a c string
        char temp_str[STRLEN];
        strcpy(temp_str,str.c_str());

        string dummy_str = "";
        string change_case = "";
        char *ptemp;

        ptemp = strtok (temp_str," "); //retrieve first token

        //while there are tokens continue the loop
        while (ptemp != NULL)
        {
            temp_vec.push_back(static_cast<string>(ptemp)); //cast a c string to a string and append it to the vector
            ptemp = strtok (NULL, " "); //retrieve more tokens
        }
        for(vi = temp_vec.begin(); vi != temp_vec.end(); vi++)
        {
            change_case = *vi; //retrieve string from current iterator index
            //if the first character is lowercase convert it to uppercase
            if(islower(change_case[ZERO]))
                change_case[ZERO] = toupper(change_case[ZERO]);
            dummy_str += " " + change_case; //append uppercase strings to vector
        }
        return lstrip(dummy_str); //return the string with all uppercase words and remove and left spaces
    }
    else
        return str;
}

vector<string> Python::capwords(const string str)
{
    temp_vec.clear();
    if(!str.empty())
    {
        temp_str = str;
        temp_str = title(str); //capitalize all words in str
        return split(temp_str," "); //return a vector with each word added
    }
    return temp_vec;
}

string Python::zfill(const string str, uint fill)
{
    uint pad = ZERO;
    //if fill is less then the string length there is no need to pad 0's so return the string as it is
    if(fill < str.length())
        return str;
    pad = fill - str.length(); //calculate how many 0's are need to append to the string
    string temp_str(pad,'0'); //pad the left of the string with 0's
    return temp_str + str;
}


string Python::join(vector<string> vstr)
{
    temp_str.clear();
    if(!vstr.empty())
    {
        for(vi = vstr.begin(); vi != vstr.end(); vi++)
            temp_str += *vi; //append current vector iterator string to a temporary string
    }
    return temp_str;
}

/* This is not part of python but I just wanted to add it */
string Python::join(vector<string> vstr, const char sep)
{
    temp_str.clear();
    if(!vstr.empty())
    {
    for(vi = vstr.begin(); vi != vstr.end(); vi++)
        temp_str += *vi + sep; //append current vector iterator string to a temporary string with a seperator character at the end
    }
    return temp_str;
}

char Python::slice(const string str, const uint index)
{
    //if the index is a valid range return the character at the giving index
    if( index < str.length() )
        return str[index];
    else
        return NULL;
}

string Python::slice(const string str, const uint index1, const uint index2)
{
    if(!str.empty())
    {
        //if the index is out of range return a empty string
        if( index1 >= str.length() )
            return "";
        else if (index1 < index2)
        {
            return str.substr(index1,index2); //return a substring from giving indexes
        }
        else
            return ""; //if index2 was greater than index1 return a empty string
    }
    else
        return "";
}

string Python::slice(const string str, const uint index1, const uint index2, uint step)
{
    temp_str.clear();
    if(!str.empty())
    {
        //if the index is out of range return a empty string or step is less than 1 return a empty string
        if( index1 >= str.length() )
            return "";
        else if (index1 < index2)
        {
            for(uint x = index1; x < index2; x = x + step)
                temp_str += str[x]; //append characters to a string skipping indexes
            return temp_str;
        }
        else
            return ""; //return a empty string if other conditions occur for example index2 is greater then index1
    }
    else
        return "";
}

size_t Python::find(const string str, const string substr)
{
    return str.find(substr);
}

size_t Python::find(const string str, const string substr, unsigned const int count)
{
    size_t index = str.find(substr);
    if(count > 1)
    {
        for(uint x = ZERO; x < count - 1; x++)
        {
            index = str.find(substr, index+1);
            if(index == string::npos)
                return string::npos;
        }
        return index;
    }
    else if(count == 1)
        return index;
    else
        return string::npos;
}

size_t Python::rfind(const string str, const string substr)
{
    return str.find_last_of(substr);
}

size_t Python::rfind(const string str, const string substr, const uint count)
{
    size_t index = str.find_last_of(substr);
    if(count > 1)
    {
        for(uint x = ZERO; x < count - 1; x++)
        {
            index = str.find_last_of(substr, index-1);
            if(index == string::npos)
                return string::npos;
        }
        return index;
    }
    else if(count == 1)
        return index;
    else
        return string::npos;
}

size_t Python::count(const string str, const string substr)
{
    size_t matches = ZERO;
    size_t m_count = ZERO;
    matches = str.find(substr);
    while(matches != string::npos)
    {
        m_count++;
        matches = str.find(substr, matches + 1);
    }
    return m_count;
}

string Python::replace(string str, const string sub_str, string new_str)
{
    size_t index = str.find(sub_str); //search for a string
    if(index != string::npos) //if string is file erase the old string and replace it with a new string
    {
        str.erase(index, sub_str.length());
        str.insert(index,new_str);
    }
    while(index != string::npos) //while there are matches continue to replace old substrings with new strings
    {
        index = str.find(sub_str);
        if(index == string::npos)
            return str;
        else
        {
            str.erase(index, sub_str.length());
            str.insert(index,new_str);
        }
    }
    return str;
}

string Python::replace(string str, string sub_str, string new_str, const uint count)
{
    uint ncount = ZERO;
    size_t index = str.find(sub_str); //search for a string
    if(index != string::npos) //if string is file erase the old string and replace it with a new string
    {
        str.erase(index, sub_str.length());
        str.insert(index,new_str);
        ncount++;
    }
    while(index != string::npos) //while there are matches continue to replace old substrings with new strings
    {
        if(ncount == count)
            break;
        index = str.find(sub_str);
        if(index == string::npos)
            return str;
        else
        {
            str.erase(index, sub_str.length());
            str.insert(index,new_str);
        }
        ncount++;
    }
    return str;
}

string Python::ljust(string str, const uint count)
{
    uint pad = ZERO;
    //if count is less then the string length there is no need to pad spaces so return the string as it is
    if(count < str.length())
        return str;
    pad = count - str.length(); //calculate how many spaces are need to append to the string
    string temp_str(pad,' '); //pad the left of the string with spaces
    return temp_str + str;
}

string Python::ljust(string str, const uint count, const char fill)
{
    uint pad = ZERO;
    //if count is less then the string length there is no need to pad spaces so return the string as it is
    if(count < str.length())
        return str;
    pad = count - str.length(); //calculate how many spaces are need to append to the string
    string temp_str(pad,fill); //pad the left of the string with spaces
    return temp_str + str;
}

string Python::rjust(string str, const uint count)
{
    uint pad = ZERO;
    //if count is less then the string length there is no need to pad spaces so return the string as it is
    if(count < str.length())
        return str;
    pad = count - str.length(); //calculate how many spacess are need to append to the string
    string temp_str(pad,' '); //pad the left of the string with spaces
    return str + temp_str;
}

string Python::rjust(string str, const uint count, const char fill)
{
    uint pad = ZERO;
    //if count is less then the string length there is no need to pad spaces so return the string as it is
    if(count < str.length())
        return str;
    pad = count - str.length(); //calculate how many spacess are need to append to the string
    string temp_str(pad,fill); //pad the left of the string with spaces
    return str + temp_str;
}



string Python::center(string str, const uint count)
{
    uint pad = ZERO;
    bool side = true;
    //if count is less then the string length there is no need to pad spaces so return the string as it is
    if(count < str.length())
        return str;
    pad = count - str.length(); //calculate how many spacess are need to append to the string
    for(uint x = ZERO; x < pad; x++)
    {
        if(side == true) //if else statment to swap padding to string
        {
            str = " " + str;
            side = false;
        }
        else
        {
            str = str + " ";
            side = true;
        }
    }
    return str;
}

string Python::center(string str, const uint count, const char fill)
{
    uint pad = ZERO;
    bool side = true;
    //if count is less then the string length there is no need to pad spaces so return the string as it is
    if(count < str.length())
        return str;
    pad = count - str.length(); //calculate how many spacess are need to append to the string
    for(uint x = ZERO; x < pad; x++)
    {
        if(side == true) //if else statement to swap padding to string
        {
            str = fill + str;
            side = false;
        }
        else
        {
            str = str + fill;
            side = true;
        }
    }
    return str;
}

bool Python::is_digit(const string str)
{
    if(!str.empty())
    {
        temp_str = digits();
        size_t pos = ZERO;
        for(uint x = ZERO; x < str.length(); x++)
        {
            pos = temp_str.find(str[x]); //check if the character is a digit
            if(pos == string::npos) //if the string character is not a digit return false
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::is_alpha(const string str)
{
    if(!str.empty())
    {
        temp_str = ascii_letters();
        size_t pos = ZERO;
        for(uint x = ZERO; x < str.length(); x++)
        {
            pos = temp_str.find(str[x]); //check if the character is a letter
            if(pos == string::npos) //if the string character is not a letter return false
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::is_alphanum(const string str)
{
    if(!str.empty())
    {
        temp_str = ascii_letters() + digits();
        size_t pos = ZERO;
        for(uint x = ZERO; x < str.length(); x++)
        {
            pos = temp_str.find(str[x]); //check if the character is a letter or number
            if(pos == string::npos) //if the string character is not a letter return false
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::is_lower(const string str)
{
    if(!str.empty())
    {
        temp_str.clear();
        for(uint x = ZERO; x < str.length(); x++)
        {
            temp_str = str[x];
            if( is_alpha(temp_str) == true)
                if(islower(str[x]))
                    continue;
                else
                    return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::is_upper(const string str)
{
    if(!str.empty())
    {
        temp_str.clear();
        for(uint x = ZERO; x < str.length(); x++)
        {
            temp_str = str[x];
            if( is_alpha(temp_str) == true)
                if(isupper(str[x]))
                    continue;
                else
                    return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::is_space(const string str)
{
    if(!str.empty())
    {
        temp_str = whitespace();
        size_t pos = ZERO;;
        for(uint x = ZERO; x < str.length(); x++)
        {
            pos = temp_str.find(str[x]); //check if the character is a letter or number
            if(pos == string::npos) //if the string character is not a letter return false
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::is_title(const string str)
{
    if(!str.empty())
        return isupper(str[ZERO]) ? true : false;
    else
        return false;
}

string Python::translate(string str, string remove_chars)
{
    if(!str.empty())
    {
        size_t pos;
        for(uint y = ZERO; y < remove_chars.length(); y++)
        {
            for(uint x = ZERO; x < str.length(); x++)
            {
                pos = str.find(remove_chars[y]); //if a character from remove_char is found remove is from the string
                if (pos != string::npos)
                    str.erase(pos,1);
            }
        }
        return str;
    }
    else
        return str;
}

vector<string> Python::partition(const string str, const string sep)
{
    temp_vec.clear();
    if(!str.empty() && !sep.empty())
    {
        size_t pos;
        pos = str.find(sep); //find first occurance of seperator in a string
        if(pos != string::npos) //if the seperator is found add sections of the string
        {
            temp_vec.push_back(str.substr(ZERO,pos)); //add first half of the string from to where the last seperator is found
            temp_vec.push_back(sep); //add seperator
            temp_vec.push_back(str.substr(pos + sep.length(),str.length())); //add last half of the string from where the last seperator was found
            return temp_vec;
        }
        else
        {
            temp_vec.push_back(str); //add full string
            temp_vec.push_back(""); //add empty string
            temp_vec.push_back(""); //add empty string
            return temp_vec;
        }
    }
    else
    {
        temp_vec.push_back(str); //add full string
        temp_vec.push_back(""); //add empty string
        temp_vec.push_back(""); //add empty string
        return temp_vec;
    }
}

vector<string> Python::rpartition(const string str, const string sep)
{
    temp_vec.clear();
    if(!str.empty() && !sep.empty())
    {
        size_t pos;
        pos = str.rfind(sep); //find last occurance of seperator in a string
        if(pos != string::npos) //if the seperator is found add sections of the string
        {
            temp_vec.push_back(str.substr(ZERO,pos)); //add first half of the string from to where the last seperator is found
            temp_vec.push_back(sep); //add seperator
            temp_vec.push_back(str.substr(pos + sep.length(),str.length())); //add last half of the string from where the last seperator was found
            return temp_vec;
        }
        else
        {
            temp_vec.push_back(str); //add full string
            temp_vec.push_back(""); //add empty string
            temp_vec.push_back(""); //add empty string
            return temp_vec;
        }
    }
    else
    {
        temp_vec.push_back(str); //add full string
        temp_vec.push_back(""); //add empty string
        temp_vec.push_back(""); //add empty string
        return temp_vec;
   }
}

/* not part of python addon string functions */

string Python::reverse_str(const string str)
{
    if(!str.empty())
    {
        temp_str = str;
        reverse(temp_str.begin(),temp_str.end());
        return temp_str;
    }
    else
        return str;
}


string Python::delete_vowels(string str)
{
    if(!str.empty())
    {
        const string VOWELS = "aeiou";
        return translate(str, VOWELS);
    }
    else
        return str;
}

string Python::squeeze(string str)
{
    temp_str.clear();
    if(!str.empty())
    {
        const long STR_SIZE = str.length(); //holds str length
        for(uint x = ZERO; x < STR_SIZE-1; x++) //loop through entire string
        {
            if(str[x] != str[x+1]) //if string next character is not equal append the character to temp string
                temp_str += str[x];
        }
        const long TEMP_STR_SIZE = temp_str.length(); //holds temp_str length
        if( str[TEMP_STR_SIZE-1] != str[STR_SIZE-1]) //check if the last character of str is not equal to temp_str if it is not append the last character
            temp_str += str[STR_SIZE-1];
        return temp_str; //return the squeezed string
    }
    else
        return str;
}

string Python::dupe_string(const string str, const uint count)
{
    if(!str.empty())
    {
        temp_str = str;
        for(uint x = ZERO; x < count; x++)
        {
            temp_str += str;
        }
        return temp_str;
    }
    else
        return str;
}

string Python::tab_to_space(const string str)
{
    if(!str.empty())
        return replace(str,"\t", " ");
    else
        return str;
}

string Python::quote(const string str)
{
    if(!str.empty())
        return "\"" + str + "\"";
    else
        return str;
}

string Python::insert(const string str, const string insert_str, const uint index)
{
    if(!str.empty())
    {
        temp_str.clear();
        if( (index < str.length()-1) )
        {
            temp_str = str.substr(ZERO,index);
            temp_str += insert_str;
            temp_str += str.substr(index,str.length());
        }
        return temp_str;
    }
    else
        return str;
}

string Python::shuffle(const string str)
{

    if(str.length() > 1)
    {
        srand(time(NULL));  //set random seed to time
        temp_str = str;
        random_shuffle(temp_str.begin(),temp_str.end());
        return temp_str;
    }
    else
        return str;
}

string Python::del_duplicate_chars(const string str)
{
    if(!str.empty())
    {
        temp_str = str;
        set<char>str_set(temp_str.begin(),temp_str.end());
        set<char>::iterator si;
        temp_str.clear();
        for(si = str_set.begin(); si != str_set.end(); si++)
            temp_str += *si;
        return temp_str;
    }
    else
        return str;
}

uint Python::file_line_count(const string filename)
{
    if(!filename.empty())
    {
        uint line_count = 0;
        const unsigned short LINE_SIZE = 255;
        char line[LINE_SIZE];
        try
        {
            ifstream fin(filename.c_str());
            if(!fin)
            {
                cerr<<"Error: Unable to open " + filename<<endl;
                return 0;
            }
            else
            {
                while(fin.getline(line,LINE_SIZE))
                {
                    line_count++;
                }
            }
            fin.close();
        }
        catch(exception &e)
        {
            cerr<<e.what()<<endl;
        }
        return line_count;
    }
    else
        return ZERO;
}

string Python::getDateTime()
{
    time_t rawtime;
    time ( &rawtime );
    return ctime(&rawtime);
}

void Python::list_print(vector<string> vec1)
{
    if(!vec1.empty())
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            cout<<*vi<<endl;
    else
        cout<<"vector is empty"<<endl;
}

vector<string> Python::list_append(vector<string> vec1, vector<string> vec2)
{
    for(vi = vec2.begin(); vi != vec2.end(); vi++)
        vec1.push_back(static_cast<string>(*vi));
    return vec1;
}

vector<string> Python::list_reverse(vector<string> vec1)
{
    temp_vec = vec1;
    if(!vec1.empty())
        reverse_copy(vec1.begin(),vec1.end(),temp_vec.begin());
    return temp_vec;
}

vector<string> Python::list_shuffle(vector<string> vec1)
{
    temp_vec = vec1;
    if(!temp_vec.empty())
    {
        srand(time(NULL)); //set the random seed to current time
        random_shuffle(temp_vec.begin(),temp_vec.end());
    }
    return temp_vec;
}

vector<string> Python::list_sort(vector<string> vec1)
{
    temp_vec = vec1;
    if(!temp_vec.empty())
        sort(temp_vec.begin(),temp_vec.end());
    return temp_vec;
}

vector<string> Python::list_sort(vector<string> vec1, bool ascdec)
{
    temp_vec = list_sort(vec1);
    if( ascdec == true )
        return temp_vec;
    else
    {
        if(!vec1.empty())
        {
            sort(vec1.begin(),vec1.end());
            reverse_copy(vec1.begin(),vec1.end(),temp_vec.begin());
        }
        return temp_vec;
    }
}

vector<string> Python::list_remove_duplicate(vector<string> vec1)
{
    temp_vec = vec1;
    if(!temp_vec.empty())
    {
        sort(temp_vec.begin(), temp_vec.end());
        temp_vec.erase (unique(temp_vec.begin(), temp_vec.end()), temp_vec.end());
    }
    return temp_vec;
}

unsigned long Python::list_count(vector<string>vec1, string search)
{
    if(!vec1.empty())
    {
        //added std::count so the compiler cannot get confustions with the count function for strings in the Python class
        return std::count(vec1.begin(),vec1.end(),search);
    }
    else
        return 0;
}

vector<string> Python::list_tolower(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(lower(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_toupper(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(upper(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_title(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            temp_vec.push_back(title(static_cast<string>(*vi)));
        }
    }
    return temp_vec;
}

vector<string> Python::list_swapcase(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(swapcase(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_capwords(vector<string> vec1)
{
    temp_str.clear();
    if(!vec1.empty())
    {
        vector<string>dummy_vec; //dummy vector holds a temporary vector with all capital words
        temp_vec.clear();
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            dummy_vec = capwords(static_cast<string>(*vi)); //assign dummy_vec with a vector with all capital words
            temp_str = join(dummy_vec,' '); //join the vector back into a string maintaing a space between each word
            temp_vec.push_back(temp_str); //append the temporary string to temp_vec
        }
    }
    return temp_vec;
}

vector<string> Python::list_strip(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(strip(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_lstrip(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(lstrip(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_rstrip(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(rstrip(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_center(vector<string> vec1, const uint count)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(center(static_cast<string>(*vi),count));
    }
    return temp_vec;
}

vector<string> Python::list_center(vector<string> vec1, const uint count, const char fillchar)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(center(static_cast<string>(*vi),count,fillchar));
    }
    return temp_vec;
}

vector<string> Python::list_ljust(vector<string> vec1, const uint count)
{
    temp_vec.clear();
    for(vi = vec1.begin(); vi != vec1.end(); vi++)
    {
        temp_vec.push_back(ljust(static_cast<string>(*vi),count));
    }
    return temp_vec;
}

vector<string> Python::list_ljust(vector<string> vec1, const uint count, const char fillchar)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(ljust(static_cast<string>(*vi),count,fillchar));
    }
    return temp_vec;
}

vector<string> Python::list_rjust(vector<string> vec1, const uint count)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(rjust(static_cast<string>(*vi),count));
    }
    return temp_vec;
}

vector<string> Python::list_rjust(vector<string> vec1, const uint count, const char fillchar)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(rjust(static_cast<string>(*vi),count,fillchar));
    }
    return temp_vec;
}

vector<string> Python::list_zfill(vector<string> vec1, const uint count)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(zfill(static_cast<string>(*vi),count));
    }
    return temp_vec;
}

vector<string> Python::list_translate(vector<string> vec1, const string remove_chars)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(translate(static_cast<string>(*vi),remove_chars));
    }
    return temp_vec;
}

vector<string> Python::list_delete_vowels(vector<string> vec1)
{
    temp_vec.clear();
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
            temp_vec.push_back(delete_vowels(static_cast<string>(*vi)));
    }
    return temp_vec;
}

vector<string> Python::list_delete_dup_elements(vector<string> vec1)
{
    temp_vec = vec1;
    if(!vec1.empty())
    {
        set<string>str_set(temp_vec.begin(),temp_vec.end());
        temp_vec.clear();
        set<string>::iterator si;
        for(si = str_set.begin(); si != str_set.end(); si++)
            temp_vec.push_back(*si);
    }
    return temp_vec;
}

vector<string> Python::list_loadfile(const string filename)
{
    temp_vec.clear();
    temp_str.clear();
    try
    {
        ifstream fin(filename.c_str());
        if(!fin)
        {
            cerr<<"Error: Unable to open " + filename<<endl;
            return temp_vec;
        }
        else
        {
            while(!fin.eof())
            {
                getline(fin,temp_str);
                temp_vec.push_back(temp_str);
            }
        }
        fin.close();
    }
    catch(exception &e)
    {
        cerr<<e.what()<<endl;
    }
    return temp_vec;
}

bool Python::list_isalpha(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if( is_alpha(static_cast<string>(*vi) ) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::list_isalphanum(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if(is_alphanum(static_cast<string>(*vi)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::list_isdigit(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if(is_digit(static_cast<string>(*vi)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::list_islower(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if(is_lower(static_cast<string>(*vi)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::list_isupper(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if(is_upper(static_cast<string>(*vi)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::list_isspace(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if(is_space(static_cast<string>(*vi)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Python::list_istitle(vector<string> vec1)
{
    if(!vec1.empty())
    {
        for(vi = vec1.begin(); vi != vec1.end(); vi++)
        {
            if(is_title(static_cast<string>(*vi)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    else
        return false;
}