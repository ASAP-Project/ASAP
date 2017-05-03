//====================================================================================================
// Program Name: FSM Eliza
// Author: Gonzales Cenelia
// Website: www.ai-search.4t.com
//
// This was one of my first atempt at writing an eliza like chatterbot, 
// this version of eliza uses an FSM (Finite State Machine) 
// for coding the main routine of the chatterbot, Finite State Machines are very well suitable
// for writing chatterbots in general. The main reason for this would be because that 
// most of the things that are found in the algorithm of chatterbots can be easealy coded by using
// predefine states of a given Finite State Machine.
// As you probably know it already, the first chatterbot was developped in the MIT laboratories
// during the year 1966 by professor Joseph Weizenbaum, the main purpose of chatterbots or chat robots
// is to simulate a conversation that ressemble a real conversation between humans.
// So far no chatterbot have really succeeded in this goal, although "Alice" a program that was
// written by Richard Wallace has won the Loebner Prize for most human chatbot three times.
// How can we explain the fact that chatterbots haven't succeeded yet in emulating a real conversation
// between huamns? Probably one the main reason for this would be simply because chatterbots in general 
// are unable to learn new keywords or even patterns by themselve during a conversation, if this specific
// feature were to ever been invented then it might solve one the biggest problems of chatbots.
// (a static database however big that it might be will never be sufficient to enable a chatbot 
// to have a coherent conversation)
//
// These code is Copyrighted and has limited warranty.
//*********************************



#pragma warning(disable: 4786)

#include "tokenizer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <cstdio>
#include <ctime>


typedef std::vector<std::string> vstring;

typedef struct  {
	std::string verbPhrase1;
	std::string verbPhrase2;
} transpos_t;

typedef struct  {
	vstring keyWords;
	vstring response;
} key_t;


void memorise();
void dump_data();
void saveData();
void saveSignOn();
void saveTransposTable();
void saveNullResponse();
void saveNoKeyWord();
void saveTopicChanger();
void saveSubjectRecall();
void saveKeyWordList();
int Random( const int ival );
void extractSubject();
void getInput( std::string &str );
bool testRepetition();
void parseScriptFile();
void Transition();
void PrintResponse();
void PrintData();
void trimPuncs( std::string &str );
void UpperCase( std::string &str );
int searchKeyWord(std::string str, std::vector<key_t> keyList);
bool transpose( std::string &str );
bool replace( std::string &str, std::string oldsubstr, std::string newsubstr );
bool remove( std::string &str, std::string substr );
void transpose_sentence( std::string &str );
void print_keyword_list();
void print_response_list();
void saveUnknownSentences();
void trimLeft(std::string &str, char c);
void trimRight(std::string &str, char c);
void trimLR(std::string &str, std::string characters);
void select_response();
void handleRepetition();
void handleWrongContext();
void handleWrongSubject();

std::string keyWord = "";
std::string sInput = "";
std::string sPreviousInput = "";
std::string sResponse = "";
std::string sSubject = "";
std::string sPreviousResponse = "";

std::string puncs = ".,;!?";
std::stack<std::string> memory;
static int nRepeatCount = 1;

vstring signOn;
vstring nullResponse;
vstring noKeyWord;
vstring topicChanger;
vstring subjectRecall;
vstring unknownSentences;
vstring responseList;
std::list<std::string> extendedResponseList;
std::vector<transpos_t> transposList; 
transpos_t thisTranspos;

key_t thisKey, _thisKey;
std::vector<key_t> keyWordList;
std::vector<key_t> keyForLearning;
std::vector<int> pos_list;

enum STATE { 
	START, SIGN_ON, GET_INPUT, RESPOND, QUIT, NULL_INPUT, BOT_REPEAT, USER_REPEAT,
	RECALL_MEMORY, SEARCH_KEY, KEY_FOUND, NO_KEY_FOUND, DEFAULT_REPLY, CHANGE_TOPIC, 
	DONT_UNDERSTAND, LEARNING, ASK_QUESTION, VERIFY_RESPONSE, MEMORISING, 
	WRONG_CONTEXT, WRONG_SUBJECT, SELECT_RESPONSE
} state;

std::string NEXT_SYMBOL = "";

std::fstream scriptfile;

Tokenizer tok;

bool bNewData = false;

int nFoundPos;


unsigned int nSignOnSize;
unsigned int nNullSize;
unsigned int nNoKeySize;
unsigned int nTopicChangerSize;
unsigned int nSubjectRecallSize;
unsigned int nKeyWordsSize;
unsigned int nTransPosNum;
unsigned int nNokeyFound;
unsigned int nKeyForLearning;
unsigned int nKeyPos;
unsigned int nSelection;
unsigned int nKeyNum;



int main() {
	std::cout << "Eliza 2006: Smarter Eliza,Copyright(c) Gonzales Cenelia.\n" << std::endl;
	parseScriptFile();
	nNokeyFound = 0;
	nSignOnSize = signOn.size();
	nNullSize = nullResponse.size();
	nNoKeySize = noKeyWord.size();
	nTopicChangerSize = topicChanger.size();
	nSubjectRecallSize = subjectRecall.size();
	nKeyForLearning = keyForLearning.size();
	nKeyWordsSize = keyWordList.size();
	nTransPosNum = transposList.size();
	srand( ( unsigned )time( NULL ) );
	while(state != QUIT) {
		Transition();
	}
	if(bNewData) {
		saveData();
	}
	return 0;
}

void Transition() {
	switch(state){
	case START:
		state = SIGN_ON;
		break;
	case SIGN_ON:
		responseList = signOn;
		state = SELECT_RESPONSE;
		break;
	case GET_INPUT:
		sPreviousInput = sInput;
		getInput(sInput);
		NEXT_SYMBOL = sInput;
		if(NEXT_SYMBOL.length() == 0) {
			state = NULL_INPUT;
		} else if(NEXT_SYMBOL == " QUIT " || NEXT_SYMBOL == " BYE ") {
			sResponse = "BYE USER,SEE YOU NEXT TIME.";
			state = RESPOND;
		} else if(testRepetition() == 1) {
			if(nRepeatCount  < 2) {
				state = SEARCH_KEY;
			} else {
				state = USER_REPEAT;
			}
		} else if(NEXT_SYMBOL.find("MY ") != std::string::npos) {
			keyWord = "MY ";
			extractSubject();
			memory.push(sInput);
			nRepeatCount = 0;
			state = SEARCH_KEY;
		} else {
			nRepeatCount = 0;
			state = SEARCH_KEY;
		}
		break;
	case SEARCH_KEY: {
			nFoundPos = searchKeyWord(NEXT_SYMBOL, keyWordList);
			if(nFoundPos == -1 && pos_list.size() > 0) {
				int index = rand() % pos_list.size();
				nFoundPos = pos_list[index];
			}
			if(nFoundPos == -1) {
				unknownSentences.push_back(NEXT_SYMBOL);
				state = NO_KEY_FOUND;
			} else {
				state = KEY_FOUND;
			}
		}
		break;
	case RESPOND:
		PrintResponse();
		if(NEXT_SYMBOL == " QUIT " || NEXT_SYMBOL == " BYE ") {
			saveUnknownSentences();
			state = QUIT;
		} else {
			extendedResponseList.push_back(sResponse);
			state = GET_INPUT;
		}
		break;
	case NULL_INPUT:
		responseList = nullResponse;
		state = SELECT_RESPONSE;
		break;
	case BOT_REPEAT:
		handleRepetition();
		state = RESPOND;
		break;
	case USER_REPEAT:
		state = RESPOND;
		break;
	case KEY_FOUND:
		responseList = keyWordList[nFoundPos].response;
		state = SELECT_RESPONSE;
		break;
	case NO_KEY_FOUND:
		if(memory.size() == 0) {
			++nNokeyFound;
			if(rand() % 3) {
				state = DEFAULT_REPLY;
			} else {
				state = CHANGE_TOPIC;
			}
		} else {
			state = RECALL_MEMORY;
		}
		break;
	case SELECT_RESPONSE:
		sPreviousResponse = sResponse;
		nKeyNum = responseList.size();
		nSelection = Random(nKeyNum);
		sResponse = responseList[nSelection];
		if(sResponse == sPreviousResponse) {
			state = BOT_REPEAT;
		}
		else {
			extractSubject();
			transpose_sentence(sSubject);
			replace(sResponse, "*", " " + sSubject);
			state = RESPOND;
		}
		break;
	case DEFAULT_REPLY:
		responseList = noKeyWord;
		state = SELECT_RESPONSE;
		break;
	case RECALL_MEMORY:
		nSelection = Random(nSubjectRecallSize);
		sResponse = subjectRecall[nSelection];
		trimLR(memory.top(), " ");
		transpose_sentence(memory.top());
		replace(sResponse, "*", " " + memory.top());
		memory.pop();
		state = RESPOND;
		break;
	case CHANGE_TOPIC:
		nSelection = Random(nTopicChangerSize);
		sResponse = topicChanger[nSelection];
		nNokeyFound = 0;
		state = RESPOND;
		break;
	case MEMORISING:
		memorise();
		state = KEY_FOUND;
		break;
	}
}

int searchKeyWord(std::string str, std::vector<key_t> keyList) {
	std::string thisKey = "";
	std::string bestKey = "";
	int nKeyNum, nFoundPos = -1;
	int nBestPos = -1, nPos;
	int nkeyListSize = keyList.size();
	pos_list.clear();
	for(int i = 0; i < nkeyListSize; ++i) {
		nKeyNum = keyList[i].keyWords.size();
		for(int j = 0; j < nKeyNum; ++j) {
			thisKey = keyList[i].keyWords[j];
			thisKey.insert(0, " ");
			nPos = str.find(thisKey);
			if(nPos != std::string::npos) {
				if(thisKey.length() > bestKey.length() ||
					(nPos != nBestPos && thisKey.length() == bestKey.length())) {
					if(thisKey.length() > bestKey.length()) {
						nBestPos = nPos;
						bestKey = thisKey;
						nFoundPos = i;
					} else {
						nFoundPos = -1;
						pos_list.push_back(i);
					}
				}
			}
		}
	}
	keyWord = bestKey;
	nKeyPos = nFoundPos;
	return nFoundPos;
}

void PrintResponse() {
	std::cout << sResponse << std::endl << std::endl;
}

int Random( const int ival ) {
	if( ival == 0 ) {
		return 0;
	} else { 
		return rand() % ival;
	}
}

void UpperCase( std::string &str ) {
	int len = str.length();
	for(int i = 0; i < len; ++i) {
		if ( str[i] >= 'a' && str[i] <= 'z' ) {
			str[i] -= 'a' - 'A';
		}
	}
}

void trimPuncs( std::string &str ) {
	std::string temp = "";
	int nStrLen = str.length();
	for(int i = 0; i < nStrLen; ++i) {
		if(puncs.find(str[i]) == std::string::npos) {
			temp += str[i];
		} else if(str[i + 1] != ' ') {
			temp += " ";
		}
	}
	trimRight(temp, ' ');
	str = temp;
}

void getInput( std::string &str ) {
 	std::cout << ">";
	std::getline(std::cin, str);
	if(str.length() > 0) {
		trimPuncs(str);
		UpperCase(str);
		str.insert(0, " ");
		str.append(" ");
	}
}

bool testRepetition() {
	bool bRetVal = false;
	if(sPreviousInput.length() != 0 
		&& sInput == sPreviousInput) {
		++nRepeatCount;
		if(nRepeatCount == 2) {
			sResponse =  "YOU ARE REPEATING YOURSELF.";
		} else if(nRepeatCount == 3) {
			sResponse = "KEEP DOING THAT,IT'S PRETTY FUNNY!?";
		} else if(nRepeatCount == 4) {
			sResponse = "COMMON,YOU CAN DO BETTER THAN THIS.";
		} else if(nRepeatCount >= 5) {
			sResponse = "ALRIGHT,THAT'S ENOUGH FOR TODAY.";
			NEXT_SYMBOL = "QUIT";
		}
		bRetVal = true;
	}
	return bRetVal;
}

// removes a substring from a given string
bool remove(std::string &str, std::string substr) {
	int pos = str.find(substr);
	if(pos != std::string::npos) {
		str.erase( pos, substr.length());
	}
	return (pos != std::string::npos);
}

// trim the left character of a given string
void trimLeft(std::string &str, char c) {
	for(int pos = 0; str[pos] == c; ++pos)
		;
	str.erase( 0, pos );
}

// trim the right character of a given string
void trimRight(std::string &str, char c) {
	int pos = str.length();
	if( pos == 0 ) return;
	for(--pos; str[pos] == c; --pos)
		;
	str.erase(++pos, str.length() - pos);
}

// trim all left and right characters that is specified by
// the string "characters"
void trimLR(std::string &str, std::string characters) {
	int len = characters.length();
	for(int i = 0; i < len; ++i) {
		trimLeft( str, characters[i] );
		trimRight( str, characters[i] );
	}
}

// replace a substring by another substring
bool replace(std::string &str, std::string oldsubstr, std::string newsubstr) {
	int pos = str.find(oldsubstr);
	if( pos != std::string::npos ) {
		remove( str, oldsubstr );
		str.insert( pos, newsubstr );
	}
	return (pos != std::string::npos);
}

// transposes a word
bool transpose( std::string &str ) {
	std::string _str = " " + str + " ";
	std::string backup = str;
	std::string verbP1 = "";
	std::string verbP2 = "";
	for(int i = 0; i < nTransPosNum; ++i) {
		verbP1 = transposList[i].verbPhrase1;
		verbP2 = transposList[i].verbPhrase2;
		if(replace(_str, verbP1, verbP2)) {
			break;
		} else if(replace(_str, verbP2, verbP1)) {
			break;
		} 
	}
	str = _str.substr(1, _str.length() - 2);
	return backup != str;
}

// transpose a complete sentence
void transpose_sentence( std::string &str ) {
	std::string thisWord = "";
	std::string tempStr = "";
	vstring stringToken;
	tok.setDelim(" !?,-");
	trimRight(str, '.');
	tok.tokenize(str, stringToken);
	int nTokNum = stringToken.size();
	for(int i = 0; i < nTokNum; ++i) {
		thisWord = stringToken[i];
		transpose(thisWord);
		tempStr += thisWord + " ";
	}
	str = tempStr;
	trimRight(str, ' ');
}

void extractSubject() {
	sSubject = "";
	int pos = sInput.find(keyWord);
	if(pos != std::string::npos) {
		pos += keyWord.length();
		sSubject = sInput.substr(pos, sInput.length() - pos);
	}
}

void saveUnknownSentences() {
	int nUnknownSentencesSize = unknownSentences.size();
	std::fstream outfile;
	outfile.open("unkown.txt", std::ios::out | std::ios::app);
	for(int i = 0; i < nUnknownSentencesSize; ++i) {
		outfile << unknownSentences[i] << std::endl;
	}
	outfile.flush();
	outfile.close();
}

// parses the scripts file associated with the bot
void parseScriptFile() {
	std::fstream fin("script.txt", std::ios::in);
	if(fin.fail()) {
		std::cerr << "Error while loading script file" << std::endl;
		assert(fin.good());
	}
	std::string buffer = "";
	int counter = 0;
	char cSymbol;
	bool good_symbol = true;
	while(std::getline(fin, buffer, '\n')) {
		cSymbol = buffer[0];
		buffer.erase(0, 1);
		switch(cSymbol) {
		case ';':
			dump_data();
			break;
		case 'S':
			signOn.push_back(buffer);
			break;
		case 'T':
			++counter;
			buffer.erase(buffer.length() - 1, 1);
			if(counter % 2 == 1) {
				thisTranspos.verbPhrase1 = buffer;
			}
			else {
				thisTranspos.verbPhrase2 = buffer;
				transposList.push_back(thisTranspos);
			}
			break;
		case 'K':
			buffer.erase(buffer.length() - 1, 1);
			thisKey.keyWords.push_back(buffer);
			break;
		case 'R':
			thisKey.response.push_back(buffer);
			break;
		case 'M':
			subjectRecall.push_back(buffer);
			break;
		case 'N':
			nullResponse.push_back(buffer);
			break;
		case 'X':
			noKeyWord.push_back(buffer);
			break;
		case 'Z':
			topicChanger.push_back(buffer);
			break;
		case 'L':
			buffer.erase(buffer.length() - 1, 1);
			_thisKey.keyWords.push_back(buffer);
			break;
		}
	}
	fin.close();
}

void dump_data() {
	if(thisKey.keyWords.size() > 0) {
		keyWordList.push_back(thisKey);
		thisKey.keyWords.clear();
		thisKey.response.clear();
	}
	if(_thisKey.keyWords.size() > 0) {
		_thisKey.response = thisKey.response;
		keyForLearning.push_back(_thisKey);
		_thisKey.keyWords.clear();
		_thisKey.response.clear();
		thisKey.response.clear();
	}
}

void print_keyword_list() {
	std::fstream fout("test.txt", std::ios::out);
	if(fout.fail()) {
		std::cerr << "Error while opening \"test.txt\"" << std::endl;
		assert(fout.good());
	}
	vstring keyWords;
	vstring responses;
	int numOfKeyword, numOfResponse;
	fout << "Keyword List:\n";
	std::cout << "Keyword List:\n";
	for(int i = 0; i < nKeyWordsSize; ++i) {
		keyWords = keyWordList[i].keyWords;
		responses = keyWordList[i].response;
		numOfKeyword = keyWords.size();
		numOfResponse = responses.size();
		for(int j = 0; j < numOfKeyword; ++j) {
			fout << "  " << keyWords[j] << std::endl;
			std::cout << "  " << keyWords[j] << std::endl;
			
		}
		for(int k = 0; k < numOfResponse; ++k) {
			fout << "     " << responses[k] << std::endl;
			std::cout << "     " << responses[k] << std::endl;
		}
		fout << std::endl;
		std::cout << std::endl;
	}
	fout.flush();
	fout.close();
}

void print_response_list() {
	vstring keyWords;
	vstring responses;
	int numOfKeyword;
	int numOfResponse;
	keyWords = keyWordList[nKeyPos].keyWords;
	responses = keyWordList[nKeyPos].response;
	numOfKeyword = keyWords.size();
	numOfResponse = responses.size();
	for(int j = 0; j < numOfKeyword; ++j) {
		std::cout << "  " << keyWords[j] << std::endl;
	}
	for(int k = 0; k < numOfResponse; ++k) {
		std::cout << "     " << responses[k] << std::endl;
	}
}

void memorise() {
	if(sPreviousInput.length() > 0) {
		bNewData = true;
		thisKey.keyWords.clear();
		thisKey.response.clear();
		sResponse = sInput + ".";
		transpose_sentence(sResponse);
		keyWord = sPreviousInput;
		thisKey.keyWords.push_back(keyWord);
		thisKey.response.push_back(sResponse);
		keyWordList.push_back(thisKey);
		nKeyWordsSize++;
	}
}

void saveData() {
	scriptfile.open("script.txt", std::ios::out);
	if(scriptfile.fail()) {
		std::cerr << "Error while opening \"script.txt\"";
		assert(scriptfile.good());
	}
	scriptfile << ";" << std::endl;
	scriptfile << "; ELIZA SCRIPT FILE" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << "; Copyright 2006 Gonzales Cenelia" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << "; FORMAT:" << std::endl;
	scriptfile << "; Sxxxxxx    - DEFINE SIGNON MESSAGE" << std::endl;
	scriptfile << "; Txxxxx" << std::endl;
	scriptfile << "; Txxxxx     - DEFINE PAIR OF WORDS TO TRANSPOSE" << std::endl;
	scriptfile << "; Nxxxxxx    - RESPONSE FOR NULL ENTRY" << std::endl;
	scriptfile << "; Mxxxxxx    - DEFINE RESPONSE FOR LATER USE OF \"MY\"" << std::endl;
	scriptfile << "; Xxxxxxx    - DEFINE RESPONSE FOR NO KEYWORD FOUND" << std::endl;
	scriptfile << "; Zxxxxxx    - DEFINE CONVERSATION TOPICS" << std::endl;
	scriptfile << "; Kxxxxxx    - DEFINE KEYWORD" << std::endl;
	scriptfile << "; Rxxxxxx    - DEFINE RESPONSE FOR PREVIOUS KEYWORD" << std::endl;
	scriptfile << "; Lxxxxxx    - DEFINES KEYWORD FOR TEATCHING NEW CONCEPT" << std::endl;
	scriptfile << "; Dxxxxxx    - DEFINES KEYWORD FOR WHEN THE PROGRAM DOESN'T UNDERSTAND" << std::endl;
	scriptfile << "; Cxxxxxx    - DEFINES KEYWORD FOR REPLYING BY USING CONTEXT" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << "; NOTE:  FOR \"T\" AND \"K\", THE LAST CHARACTER IS DISCARDED TO MAKE IT EASY" << std::endl;
	scriptfile << ";        TO ENTER TRAILING SPACES." << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << ";        FOR \"R\" AND \"M\" THE STRING FOLLOWING THE KEYWORD IN THE USER'S" << std::endl;
	scriptfile << ";        INPUT IS INSERTED AT THE *" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << ";        IF A KEYWORD HAS NO RESPONSES, THEN IT WILL USE THE RESPONSES OF" << std::endl;
	scriptfile << ";        THE NEXT KEYWORD WITH RESPONSES" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << "; GOAL: THE PROGRAM SHOULD HANDLE EVERY SUBTILITIES OF THE ENGLISH LANGUAGE" << std::endl;
	saveSignOn();
	saveTransposTable();
	saveNullResponse();
	saveSubjectRecall();
	saveNoKeyWord();
	saveTopicChanger();
	saveKeyWordList();
	scriptfile.flush();
	scriptfile.close();
}

void saveSignOn() {
	scriptfile << ";" << std::endl;
	scriptfile << "; SIGNON MESSAGE" << std::endl;
	scriptfile << ";" << std::endl;
	for(int i = 0; i < nSignOnSize; ++i) {
		scriptfile << "S" << signOn[i] << std::endl;
	}
}

void saveTransposTable() {
	scriptfile << ";" << std::endl;
	scriptfile << "; TRANSPOSITION TABLE" << std::endl;
	scriptfile << ";" << std::endl;
	for(int i = 0; i < nTransPosNum; ++i) {
		scriptfile << "T" << transposList[i].verbPhrase1 << "\"" << std::endl;
		scriptfile << "T" << transposList[i].verbPhrase2 << "\"" << std::endl;
	}
}

void saveNullResponse() {
	scriptfile << ";" << std::endl;
	scriptfile << "; NULL RESPONSES" << std::endl;
	scriptfile << ";" << std::endl;
	for(int i = 0; i < nNullSize; ++i) {
		scriptfile << "N" << nullResponse[i] << std::endl;
	}
}

void saveNoKeyWord() {
	scriptfile << ";" << std::endl;
	scriptfile << "; NO KEYWORD FOUND" << std::endl;
	scriptfile << ";" << std::endl;
	for(int i = 0; i < nNoKeySize; ++i) {
		scriptfile << "X" << noKeyWord[i] << std::endl;
	}
}

void saveTopicChanger() {
	scriptfile << ";" << std::endl;
	scriptfile << "; THE FOLLOWING RESPONSES WILL HOPEFULLY TRY TO 'STEER'" << std::endl;
	scriptfile << "; THE CONVERSATION TO A TOPIC THAT MAY POSSIBLY PRODUCE" << std::endl;
	scriptfile << "; MORE RECOGNIZABLE WORDS (KEYWORDS)." << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << ";" << std::endl;
	for(int i = 0; i < nTopicChangerSize; ++i) {
		scriptfile << "Z" << topicChanger[i] << std::endl;
	}
}

void saveSubjectRecall() {
	scriptfile << ";" << std::endl;
	scriptfile << "; RESPONSES FOR \"MY\"" << std::endl;
	scriptfile << "; TO USE IF NO KEYWORD WAS FOUND." << std::endl;
	scriptfile << ";" << std::endl;
	for(int i = 0; i < nTopicChangerSize; ++i) {
		scriptfile << "M" << topicChanger[i] << std::endl;
	}
}

void saveKeyWordList() {
	scriptfile << ";" << std::endl;
	scriptfile << "; DEFINE KEYWORDS AND RESPONSES" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << ";" << std::endl;
	scriptfile << "; BOT KNOWLEDGE" << std::endl;
	scriptfile << ";" << std::endl;
	vstring keyWords;
	vstring responses;
	int numOfKeyword;
	int numOfResponse;
	for(int i = 0; i < nKeyWordsSize; ++i) {
		keyWords = keyWordList[i].keyWords;
		responses = keyWordList[i].response;
		numOfKeyword = keyWords.size();
		numOfResponse = responses.size();
		for(int j = 0; j < numOfKeyword; ++j) {
			scriptfile << "K" << keyWords[j] << "\"" << std::endl;
		}
		for(int k = 0; k < numOfResponse; ++k) {
			scriptfile << "R" << responses[k] << std::endl;
		}
		scriptfile << ";" << std::endl;
	}
}

void select_response() {
	std::string sTempResponse = sResponse;
	for(;;) {
		nSelection = Random(nKeyNum);
		sResponse = responseList[nSelection];
		if(sResponse != sTempResponse) {
			break;
		}
		else if(nKeyNum > 1) {
			responseList.erase(responseList.begin() + nSelection);
			nKeyNum = responseList.size();
		}
	}
}

void handleRepetition() {
	std::list<std::string>::iterator iter;
	if(nKeyNum > 1) {
		responseList.erase(responseList.begin() + nSelection);
	}
	else if(nKeyNum == 1) {
		responseList = topicChanger;
		nKeyNum = nTopicChangerSize;
	}
	select_response();
	iter = std::find(extendedResponseList.begin(), extendedResponseList.end(), sResponse);
	if(iter != extendedResponseList.end() && nKeyNum > 1) {
		responseList.erase(responseList.begin() + nSelection);
		select_response();
	}
}






	





