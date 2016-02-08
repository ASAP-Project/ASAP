/* 
 * File:   Python.cpp
 * Author: codecaine aka Jerome Scott II
 * 
 * Created on July 29, 2010, 5:01 PM
 */


#pragma once
#include <string>
#include <vector>
typedef unsigned int uint;

using namespace std;

#ifndef PYTHON_H
#define	PYTHON_H

class Python
{
public:
    //python ports
    Python(); //default Python constructor to initialize any decalred header constants
    string ascii_lowercase() const; //returns lowercase letters
    string ascii_uppercase() const; //returns uppercase letters
    string octaldigits() const; //returns ocal digits
    string digits() const; //returns decimal numbers
    string hexdigits() const; //returns hexidecimal numbers
    string ascii_letters() const; //returns lowercase and uppercase letters
    string punctuation() const; //returns punctuation characters
    string whitespace() const; //returns whitespace characters
    string printable() const; //returns printable characters
    string lower(const string str); //converts string to lowercase
    string upper(const string str); //converts string to uppercase
    vector<string> split(const string str); //split each chacter of a string to a vector array and returns the vector as a vector<string>
    vector<string> split(const string str, string sep); //split a string from a character seperator
    vector<string> split(const string str, string sep, const uint max);// split a string from a character seperator to a count specified
    string lstrip(const string str); //removes leading spaces from a string and returns the string
    string rstrip(const string str);//removes trialing spaces from a string and returns the string
    string strip(const string str); //removes trailing spaces from the beginning and end of a string
    string strip(string str, const string invalids); //strip characters from a string and return a string without the characters stripped
    bool startswith(const string str, const string start); //check if a string starts with matching characters then return true if yes or false if no
    bool endswith(const string str, const string end); //check if a string ends with matching characters then returns true if yes or false if no
    string swapcase(string str); //returns a string with their cases swapped
    string capitalize(string str); //returns a string with the first letter capitalized
    string title(const string str); //capitalize each inception of a word
    vector<string> capwords(const string str); //capitalize each word and add each word to a vector then returns the vector
    string zfill(const string str, uint fill); //pad a string with 0's from the left
    string join(vector<string> vstr); //join a vector of strings to one string
    string join(vector<string> vstr, const char sep); //join a vector of string to one string with a seperator character between each vector element
    char slice(const string str, const uint index); //returns a character from a giving index if the index is out of range returns nothing
    string slice(const string str, const uint index1, unsigned const int index2); //returns a substring from a giving index to a count
    string slice(const string str, const uint index1, const uint index2, uint step); //returns a substring from a giving index to a count with steps
    size_t find(const string str, const string substr); //search for a substring in a string if there is a match return substring index else string::npos
    size_t find(const string str, const string substr, const uint count); //returns the index of string from count for example if count is 2 it returns the index of the second found substr. if not found return string::npos
    size_t rfind(const string str, const string substr); //search backwards in a string and returns the first index of a match. if not found returns string::npos
    size_t rfind(const string str, const string substr, const uint count); //search backwards in a string and the index from count for example if count is 2 it reutnrs the seconds to last substr found. if not found returns string::npos
    size_t count(const string str, const string substr); //returns number of occurances of a substring in a string. if nothing if found returns 0
    string replace(string str, const string sub_str, const string new_str); //replaces all occurances of a substring to a new string in a string
    string replace(string str, const string sub_str, const string new_str, const uint count); //replaces all occurances of a substring to a number of matches
    string ljust(string str, const uint count); //return a string with padded spaces to the left until the string is the length of count
    string ljust(string str, const uint count, const char fill); //return a string with padded character that is giving to fill argument until the string is the length of count
    string rjust(string str, const uint count); //return a string with padded spaces to the right until the string is the length of count
    string rjust(string str, const uint count, const char fill); //return a string with padded character that is giving to fill argument until the string is the length of count
    string center(string str, const uint count); //return a string with padded spaces on the left and right of a string
    string center(string str, const uint count, const char fill);
    bool is_digit(const string str); //returns true if the string is a digit else false
    bool is_alpha(const string str); //return true if the string is all letter else false
    bool is_alphanum(const string str); //returns true if the string is a constains only numbers are letters
    bool is_lower(const string str); //returns true if all the letters are lowercase else false
    bool is_upper(const string str); //returns true if all the letters are uppercase else false
    bool is_space(const string str); //returns true if string contains only spaces else false
    bool is_title(const string str); //returns true only if the first letter is uppercase
    string translate(string str, string remove_chars); // returns a string removing all character from remove_chars argument
    vector<string> partition(const string str, const string sep); //returns a vector with 3 items first item is the first part of the string second is the sperator third is the last part of a string if no septerator is found in the string the full string is the first time in the vector and the last two items are empty strings
    vector<string> rpartition(const string str, const string sep); //same as partition except it looks for the seperator from the end to the front of the string
    /* not part of python addon string functions */
    string reverse_str(const string str); //return a string reversed
    string delete_vowels(string str); //returns a string with vowel characters removed
    void list_print(vector<string> vec1); //out all the element of a string vector to terminal or console only
    string squeeze(const string str); //delete duplicate values in adjacent to each other and return the string
    string dupe_string(const string str, const uint count); //duplicate a string to a giving count and return the string
    string tab_to_space(const string str); //convert a string tabs to a single space and return the string
    string quote(const string str); //enclose a string in quotes and returns the string
    string insert(const string str, const string insert_str, const uint index); //insert a string in a string at a giving index
    string shuffle(const string str); //returns a giving string with it letters shuffled
    string del_duplicate_chars(const string str); //remove any duplicate characters in a string and return the string
    uint file_line_count(const string filename); //count how many lines in a file
    string getDateTime(); //returns current date time
    vector<string> list_append(vector<string> vec1, vector<string> vec2); //return a vector<string> with another vector<string>
    vector<string> list_reverse(vector<string>vec1); //return a vector<string> in reverse order
    vector<string> list_shuffle(vector<string>vec1); //return a vector<string> in random orders
    vector<string> list_sort(vector<string>vec1); //return a list sorted in ascending order
    vector<string> list_sort(vector<string>vec1,bool ascdec); //reverse a list in ascending or descending set ascdec to true for ascending order or false for descending order
    vector<string> list_remove_duplicate(vector<string>vec1); //sort & remove duplicates from a vector<string> and return the vector
    unsigned long list_count(vector<string>vec1, string search); //returns the number of elements that matches a giving string
    vector<string> list_tolower(vector<string>vec1); //returns a vector<string> with all lowercase letters
    vector<string> list_toupper(vector<string>vec1); //returns a vector<string> with all capital letters
    vector<string> list_title(vector<string>vec1); //return a vector<string> with each string starting with a uppercase letter
    vector<string> list_swapcase(vector<string>vec1); //return a vector<string> swaping each character case
    vector<string> list_capwords(vector<string>vec1); // return a vector<string> with each word having a capital letter
    vector<string> list_strip(vector<string>vec1); //return a vector<string> stripping white spaces from the front and back of each element
    vector<string> list_lstrip(vector<string>vec1); //return a vector<string> stripping white spaces from the left side of each element
    vector<string> list_rstrip(vector<string>vec1); //return a vector<string> stripping white spaces from the right side of each element
    vector<string> list_center(vector<string>vec1, const uint count); //return a vector<string> centered with white spaces from a giving count
    vector<string> list_center(vector<string>vec1, const uint count, const char fillchar); //return a vector<string> centered with a filler character to a giving count
    vector<string> list_ljust(vector<string>vec1, const uint count); //return a vector<string> with each element padded with white spaces on the left side to a giving count
    vector<string> list_ljust(vector<string>vec1, const uint count, const char fillchar); //return a vector<string> the left side of each element padded to a giving count and with a choosen filler character
    vector<string> list_rjust(vector<string>vec1, const uint count); //return a vector<string> with each element padded with white spaces on the right side to a giving count
    vector<string> list_rjust(vector<string>vec1, const uint count, const char fillchar); //return a vector<string> the right side of each element padded to a giving count and with a choosen filler character
    vector<string> list_zfill(vector<string>vec1, const uint count); //return a vector<string> with padded 0's on the left side of each element to a giving count
    vector<string> list_translate(vector<string>vec1, const string remove_chars); //remove characters from each element in a vector<string> and return the vector
    vector<string> list_delete_vowels(vector<string>vec1); //delete all vowel characters from each element of a vector<string> and return the vector
    vector<string> list_delete_dup_elements(vector<string>vec1); //delete duplicate string elements from a vector and return the new vector
    vector<string> list_loadfile(const string filename); //load a text file contents in a vector and return the vector
    bool list_isalpha(vector<string>vec1); //checks each element in a vector<string> and returns true if all the elements are uppercase strings else false
    bool list_isdigit(vector<string>vec1); //checks each element of a vector<string> and returns true if all the elements are digits else false
    bool list_isalphanum(vector<string>vec1); //checks each element of a vector<string> and returns true if all the elements are alphabet letters or digits
    bool list_islower(vector<string>vec1); //checks each element of a vector<string> and returns true if all the elements are lowercase else false
    bool list_isupper(vector<string>vec1); //checks each element of a vector<string> and returns true if all the elements are uppercase else false
    bool list_isspace(vector<string>vec1); //checks each element of a vector<string> and returns true if all the elements are just spaces else false
    bool list_istitle(vector<string>vec1); //checks each element of a vector<string> and returns true f all the elements start with a uppercase letter else false
private:
    string temp_str; //holds a temporary string
    vector<string>temp_vec; //holds a temporary vector<string>
    vector<string>::iterator vi; //hold iterator poisitions for a vector<string>
    const unsigned short ZERO;
};
#endif