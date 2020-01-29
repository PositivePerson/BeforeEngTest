#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void clearAr(string *ar){
	for(int i=0;i<=sizeof(ar)/sizeof(ar[0]);i++){
		ar[i]="";
	}
}

void write(string &writing, int time=0)
{
	if(time==0) time=20;
    for(int i=0; i<writing.size(); i++)
    {
        cout<<writing[i];
        Sleep(time);
    }
}
/*
void hintOut(string *currentEngWord,int index, string writing=""){
	writing=currentEngWord[index][0];
	writing+=" ";
	for(int i=1;i<currentEngWord[index].length()-1;i++){
		if((int)currentEngWord[index][i]==32) writing+="  ";//if space
		else writing+="_ ";
	} 
	writing+=currentEngWord[index][currentEngWord[index].length()-1];
	write(writing);
}*/

void firstHint(string *currentEngWord,int index, int *globalUnveils, int &globalLetters){
	bool repeat=false;
	int arIndex=0;
	string writing="";
	int wordLength=currentEngWord[index].length();
	int dashes;
	globalLetters=0;
	
	if(currentEngWord[index].length()==2){
		writing+="_ " + currentEngWord[index][1];
	}
	else{
		//-------------unveil-all-em-dashes----------------------
		for(int i=0;i<currentEngWord[index].length();i++){
			if(currentEngWord[index][i]=='-'){
				globalLetters++;
				globalUnveils[globalLetters-1] = i;
				//wordLength--;
			}
		}
		
		dashes=globalLetters;
		
		//for(int i=0;i<globalLetters;i++) cout<<globalUnveils[i]<<" ";
		//cout<<'\n';
		
		if(wordLength%2!=0){
			//----unveil (length/2) chars
			globalLetters = wordLength/2;
			//cout<<"globalLetters: "<<letters<<'\n';
		}
		else{
			//----unveil (length/2-1) chars
			globalLetters = wordLength/2-1;
			//cout<<"letters: "<<letters<<'\n';
		}
			
			//for(int i=0;i<letters;i++) globalUnveils[i]=-1;
			
			for(int i=dashes;i<globalLetters;i++){
				do{
				repeat=false;
				globalUnveils[i]=(rand()% (wordLength));
				for(int j=0;j<i;j++){
					if(globalUnveils[j]==globalUnveils[i]){
					 	repeat=true;
						break;
					}
				}
				}while(repeat);
			}
			
			//for(int i=0;i<globalLetters;i++) cout<<globalUnveils[i]<<" ";
		//cout<<'\n';
			
			sort(globalUnveils, globalUnveils+globalLetters);
			
			if(globalUnveils[arIndex]==0){
				writing=currentEngWord[index][0];
				arIndex++;
			}
			else writing="_";
			
			for(int i=1;i<wordLength;i++){
				if(globalUnveils[arIndex]==i){
					writing+=" ";
					writing+=currentEngWord[index][i];
					arIndex++;
				}
				else{
				writing+=" _";
				}
			}
	}
		cout<<"	";
		write(writing);
}

void secondHint(string *currentEngWord,int index, int *globalUnveils, int &globalLetters){
	bool repeat=false;
	int arIndex=0;
	string writing="";
		
	if(currentEngWord[index].length()<3){
		writing+="Second hint does not exist";
	}
	else{
			globalLetters++;
			//for(int i=0;i<globalLetters;i++) globalUnveils[i]=-1;
			
				do{
				repeat=false;
				globalUnveils[globalLetters-1]=(rand()% (currentEngWord[index].length()));
				for(int j=0;j<globalLetters-1;j++){
					if(globalUnveils[j]==globalUnveils[globalLetters-1]){
					 	repeat=true;
						break;
					}
				}
				}while(repeat);
			
			sort(globalUnveils, globalUnveils+globalLetters);
			
			if(globalUnveils[arIndex]==0){
				writing=currentEngWord[index][0];
				arIndex++;
			}
			else writing="_";
			
			for(int i=1;i<currentEngWord[index].length();i++){
				if(globalUnveils[arIndex]==i){
					writing+=" ";
					writing+=currentEngWord[index][i];
					arIndex++;
				}
				else{
				writing+=" _";
				}
			}
	}
	cout<<"	";
	write(writing);
}

void splitUpWords(string &engWord, string *currentEngWord, int &answers){
	//----------split_up_engWord_s-------------------------
		size_t pos=51;
		do{
		pos = engWord.find("OR");
		
		if(pos<50){
			
			currentEngWord[answers] = engWord.substr(0, pos-1);
			answers++;
			engWord.erase(0, pos+3);
			
		}
		else{			
			currentEngWord[answers]=engWord;
			answers++;
			
		}
	
		}while(pos<50);
}

string uncodeIt(string codedWord, int move=5){
	string result="";
	int newChar;
	
	for(int i=0;i<codedWord.length();i++){
		if(codedWord[i]==(char)(37)) result+=(char)(32);
		else if(codedWord[i]==(char)(163)) result+=(char)(79);
		else if(codedWord[i]==(char)(161)) result+=(char)(82);
		else if(codedWord[i]==(char)(50)) result+=(char)(45);
		else{
			newChar=(int)codedWord[i]-move;
			if(newChar<97){
				result+=(char)(newChar+26);
			}
			else result+=(char)(newChar);
		}
	}
	return result;
}

bool doesWordAppeared(string *currentEngWord, int index, string word){
	for(int i=0;i<index;i++){
		if(currentEngWord[i]==word) return true;
	}
	return false;
}

int globalLetters=0;
int *globalUnveils=new int[globalLetters];

string currentEngWord[5];

bool wordsToLearn[200];

//--------------------------MAX_200_WORDS-(in_arrays)---------------
string urWordsToLearn[200];
string engWordsToLearn[200];


//string *wordsToLearn=string new;

int main(){
	
  SetConsoleTitle("FACE THAT ENGLISH");
	
	while(true){
		
	//ifstream EnglishWords("engWords.txt");
	//ifstream UrLanguage("urWords.txt");
	
	string choosenEngFile;
	string choosenUrFile;
	
	string smthToFixWeirdError;
	
	string engWord="";
	string word="";
	string inputAnswer="";
	
	string writing="";
	
	bool correct=false;
	bool restartProgram=false;
	
	int whichSubject=0;
	
	int spot_on=0;
	int corrected=0;
	int blanks=0;
	
	int q=0;
	int endChoice;
	int wantHint;
	int dataHolding=0;
	int countIncorrect=0;
	int answers=1;
	int toLearnIndex=0;
	//string *currentEngWord = new string[answers];
	
	
	//----------------------------MENU----------------------
	cout<<'\n';
	writing="	Choose subject:";
	write(writing);
	cout<<"\n\n";
	cout<<"   1 - Family"<<'\n';
	cout<<"   2 - Home"<<'\n';
	cout<<"   3 - In the house"<<'\n';
	cout<<"   4 - KitchenWare"<<'\n';
	cout<<"			Ending round: 'end'\n	";
	cout<<"		Exit: 'exit'\n	";
	
	do{
		whichSubject=0;
	cin>>whichSubject;
	//whichSubject=_getche()-48;
	
	switch(whichSubject){
		case 1:
			choosenEngFile="engFamilyCoded.txt";
			choosenUrFile="polFamilyCoded.txt";
			break;
		case 2:
			choosenEngFile="engHomeCoded.txt";
			choosenUrFile="polHomeCoded.txt";
			break;
		case 3:
			choosenEngFile="engInHouseCoded.txt";
			choosenUrFile="polInHouseCoded.txt";
			break;
		case 4:
			choosenEngFile="engKitchenWareCoded.txt";
			choosenUrFile="polKitchenWareCoded.txt";
			break;
		default:
			cout<<"Mistake in command\n	";
			continue;
	}
	}while(whichSubject<1 || whichSubject>4);
	
	getline(cin, smthToFixWeirdError);
	Sleep(200);
	system("CLS");
	
	ifstream EnglishWords(choosenEngFile.c_str());
	ifstream UrLanguage(choosenUrFile.c_str());
	
	while(getline(UrLanguage,word) && getline(EnglishWords,engWord)){
		word = uncodeIt(word);
		engWord = uncodeIt(engWord);
		
		clearAr(currentEngWord);
		countIncorrect=1;
		answers=0;
		wantHint=0;
		
		//\
		cout<<"PL: "<<word<<'\n';\
		cout<<"Eng: "<<engWord<<'\n';
		
		urWordsToLearn[toLearnIndex]=word;
		engWordsToLearn[toLearnIndex]=engWord;
		

		splitUpWords( engWord, currentEngWord, answers);
		/*
		//----------split_up_engWord_s-------------------------
		size_t pos=51;
		do{
		pos = engWord.find("OR");
		
		if(pos<50){
			
			currentEngWord[answers] = engWord.substr(0, pos-1);
			answers++;
			engWord.erase(0, pos+3);
			
		}
		else{			
			currentEngWord[answers]=engWord;
			answers++;
			
		}
	
		}while(pos<50);
		*/
		/*
		
		//cout<<"\ntablica_sprawdzenie\n";
		while(currentEngWord[q]!=""){
		//cout<<currentEngWord[q]<<" ";
		q++;
		}
		
		cout<<"\n\n";
		*/
		
		writing=" '" + word + "' to po angielsku:\n";
		write(writing);
		
		//------------input_answer-----------------------------
		do{
		cout<<"	";
		getline(cin, inputAnswer);
		
		if(inputAnswer=="end" && !doesWordAppeared(currentEngWord, answers, "end")){
			system("CLS");
			goto end_credits;
		}
		
		if(inputAnswer=="exit" && !doesWordAppeared(currentEngWord, answers, "exit")){
			delete[] globalUnveils;
			_Exit(0);
		}
	
		//------------------does-any-of-answer-match-----------
		correct=false;
		q=0;
		while(q<answers){
			if(inputAnswer==currentEngWord[q]){
				correct=true;
				break;
			}
			q++;
		}
		
		
		if(!correct){
			cout<<"	not correct\n";
			
			if(countIncorrect==2 || (countIncorrect>2 && wantHint==0)){
		//--------------first_hint_suggestion-----------------
				writing="	Do you want to get a hint?\n";
				write(writing);
				
				cout<<"	1 - yes			0 - no\n";
				
				do{
				cout<<"	";
				wantHint=_getche()-48;
				cout<<'\n';
				
				if(wantHint==1){
					firstHint(currentEngWord, 0, globalUnveils, globalLetters);
					
					if(answers>1)
					for(int i=1;i<answers;i++){
						cout<<"	or	";
						firstHint(currentEngWord, i, globalUnveils, globalLetters);
					}
					
					cout<<'\n';
				}
				
				else if(wantHint==0){
					
				}
				
				else{
					writing="	Choose 1 or 0 (again)\n";
					write(writing);
				}
				
				}while(wantHint!=0 && wantHint!=1);
			}
			
			else if(countIncorrect==3 || (countIncorrect>3 && wantHint==1)){
		//--------------second_hint_suggestion-----------------
				writing="	Do you want to get one more hint?\n";
				write(writing);
				
				cout<<"	1 - yes			0 - no\n";
				
				do{
				cout<<"	";
				wantHint=_getche()-47;
				cout<<'\n';
				
				if(wantHint==2){
					secondHint(currentEngWord, 0, globalUnveils, globalLetters);
					
					if(answers>1)
					for(int i=1;i<answers;i++){
						cout<<"	or	";
						secondHint(currentEngWord, i, globalUnveils, globalLetters);
					}
					
					cout<<'\n';
				}
				
				else if(wantHint==1){
					
				}
				
				else{
					writing="	Choose 1 or 0 (again)\n";
					write(writing);
				}
				
				}while(wantHint!=1 && wantHint!=2);
			}
			
			else if(countIncorrect>3 && wantHint==2){
				cout<<"	skip?\n";
				cout<<"	1 - yes			0 - no\n";
				
				do{
				cout<<"	";
				wantHint=_getche()-46;
				cout<<'\n';
				
				if(wantHint==3){
					blanks++;
					wordsToLearn[toLearnIndex]++;
					for(int i=0;i<answers;i++) cout<<"	"<<currentEngWord[i]<<'\n';
					Sleep(500);
					system("CLS");
					goto surrender;
				}
				
				else if(wantHint==2){
					//wantHint=1;
				}
				
				else{
					writing="	Yes(1) or No(0)\n";
					write(writing);
				}
				
				}while(wantHint!=2 && wantHint!=3);
			}
			countIncorrect++;
		}
		else{
		//-----------------count-final-scores------------
			if(countIncorrect==1){
				spot_on++;
			}
			
			else{
				corrected++;
				wordsToLearn[toLearnIndex]++;
			}
			
			cout<<"	correct\n\n";
			Sleep(175);
			system("CLS");
		} 
		
		}while(!correct);

		surrender:
		toLearnIndex++;
	}
	
	//----------------end_credits---------------------------
	end_credits:
	
	cout<<"\n";
	
	cout<<" Spot-on: "<<spot_on<<'\n';
	cout<<" Corrected: "<<corrected<<'\n';
	cout<<" Blanks: "<<blanks<<'\n';
	
	cout<<"\n\n";
	
	writing=" Words to learn:\n";
	write(writing);
	
	for(int i=0;i<toLearnIndex;i++){
		if(wordsToLearn[i]==1){
			writing="  "+ urWordsToLearn[i] + "\n";
			write(writing, 20/(corrected+blanks));
		}
	}
	
	
	cout<<"\n	1 - face all again		2 - face described words		3 - exit\n";
	
	do{
		endChoice=_getche()-48;
		
		if(endChoice==1){
			cout<<"\x1B[2J\x1B[H";
			restartProgram = true;
		}
		
		if(endChoice==2){
			cout<<"\x1B[2J\x1B[H";
			goto face_described_words;
		}
		
		if(endChoice==3){
			cout<<"\x1B[2J\x1B[H";
			writing="See ya";
			delete[] globalUnveils;
			write(writing);
			_Exit(0);
		}
		
	}while(endChoice<1 || endChoice>3);
	
	if(restartProgram==true) continue;
	
	//-----------------------face_described_words---------------------------------
	face_described_words:
		
	
	countIncorrect=1;
	
	cout<<"\n";
	
	for(int i=0;i<toLearnIndex;i++){
		if(wordsToLearn[i]==1){
			//cout<<"engWordsToLearn: "<<engWordsToLearn[i]<<'\n';
			
			writing=" '" + urWordsToLearn[i] + "' to po angielsku:\n";
			write(writing);
			
			clearAr(currentEngWord);
			countIncorrect=1;
			answers=0;
			wantHint=0;
			
			splitUpWords(engWordsToLearn[i], currentEngWord, answers);
			
			do{
		cout<<"	";
		getline(cin, inputAnswer);
		
		if(inputAnswer=="end" && !doesWordAppeared(currentEngWord, answers, "end")){
			system("CLS");
			goto end_credits;
		}
		
		if(inputAnswer=="exit" && !doesWordAppeared(currentEngWord, answers, "exit")){
			delete[] globalUnveils;
			_Exit(0);
		}
	
	
		correct=false;
		q=0;
		while(q<answers){
			if(inputAnswer==currentEngWord[q]){
				correct=true;
				break;
			}
			q++;
		}
		
		
		if(!correct){
			cout<<"	not correct\n";
			
			if(countIncorrect==2 || (countIncorrect>2 && wantHint==0)){
		//--------------first_hint_suggestion-----------------
				writing="	Do you want to get a hint?\n";
				write(writing);
				
				cout<<"	1 - yes			0 - no\n";
				
				do{
				cout<<"	";
				wantHint=_getche()-48;
				cout<<'\n';
				
				if(wantHint==1){
					firstHint(currentEngWord, 0, globalUnveils, globalLetters);
					
					if(answers>1)
					for(int i=1;i<answers;i++){
						cout<<"	or	";
						firstHint(currentEngWord, i, globalUnveils, globalLetters);
					}
					
					cout<<'\n';
				}
				
				else if(wantHint==0){
					
				}
				
				else{
					writing="	Choose 1 or 0 (again)\n";
					write(writing);
				}
				
				}while(wantHint!=0 && wantHint!=1);
			}
			
			else if(countIncorrect==3 || (countIncorrect>3 && wantHint==1)){
		//--------------second_hint_suggestion-----------------
				writing="	Do you want to get one more hint?\n";
				write(writing);
				
				cout<<"	1 - yes			0 - no\n";
				
				do{
				cout<<"	";
				wantHint=_getche()-47;
				cout<<'\n';
				
				if(wantHint==2){
					secondHint(currentEngWord, 0, globalUnveils, globalLetters);
					
					if(answers>1)
					for(int i=1;i<answers;i++){
						cout<<"	or	";
						secondHint(currentEngWord, i, globalUnveils, globalLetters);
					}
					
					cout<<'\n';
				}
				
				else if(wantHint==1){
					
				}
				
				else{
					writing="	Choose 1 or 0 (again)\n";
					write(writing);
				}
				
				}while(wantHint!=1 && wantHint!=2);
			}
			
			else if(countIncorrect>3 && wantHint==2){
				cout<<"	skip?\n";
				cout<<"	1 - yes			0 - no\n";
				
				do{
				cout<<"	";
				wantHint=_getche()-46;
				cout<<'\n';
				
				if(wantHint==3){
					blanks++;
					//wordsToLearn[toLearnIndex]++;
					system("CLS");
					goto surrender1;
				}
				
				else if(wantHint==2){
					wantHint=1;
				}
				
				else{
					writing="	Yes(1) or No(0)\n";
					write(writing);
				}
				
				}while(wantHint!=2 && wantHint!=3);
			}
			countIncorrect++;
		}
		else{
			
			if(countIncorrect==1){
				spot_on++;
			}
			
			else{
				corrected++;
				//wordsToLearn[toLearnIndex]++;
			}
			
			cout<<"	correct\n\n";
			Sleep(175);
			system("CLS");
		}
		
		}while(!correct);
		surrender1:
			continue;
		//toLearnIndex++;
		}
	}
	
	goto end_credits;
	
	//delete[] currentEngWord;
	}
}
