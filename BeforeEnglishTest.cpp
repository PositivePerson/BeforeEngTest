#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
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

void hintOut(string *currentEngWord,int index, string writing=""){
	writing=currentEngWord[index][0];
	writing+=" ";
	for(int i=1;i<currentEngWord[index].length()-1;i++){
		if((int)currentEngWord[index][i]==32) writing+="  ";//if space
		else writing+="_ ";
	} 
	writing+=currentEngWord[index][currentEngWord[index].length()-1];
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

bool doesWordAppeared(string *currentEngWord, int index, string word){
	for(int i=0;i<index;i++){
		if(currentEngWord[i]==word) return true;
	}
	return false;
}

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
	cout<<"\n	";
	
	do{
	cin>>whichSubject;
	//whichSubject=_getche()-48;
	
	switch(whichSubject){
		case 1:
			choosenEngFile="engFamily.txt";
			choosenUrFile="polFamily.txt";
			break;
		case 2:
			choosenEngFile="engHome.txt";
			choosenUrFile="polHome.txt";
			break;
		case 3:
			choosenEngFile="engInHouse.txt";
			choosenUrFile="polInHouse.txt";
			break;
		case 4:
			choosenEngFile="engKitchenWare.txt";
			choosenUrFile="polKitchenWare.txt";
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
		clearAr(currentEngWord);
		countIncorrect=1;
		answers=0;
		
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
		
		writing="'" + word + "' to po angielsku: ";
		write(writing);
		
		//------------input_answer-----------------------------
		do{
		getline(cin, inputAnswer);
		
		if(inputAnswer=="end" && !doesWordAppeared(currentEngWord, answers, "end")){
			system("CLS");
			goto end_credits;
		}
		
		if(inputAnswer=="exit" && !doesWordAppeared(currentEngWord, answers, "exit")){
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
			cout<<"not correct\n";
			
			if(countIncorrect==3 || (countIncorrect>3 && wantHint==0)){
		//-------------hint_suggestion----------------------
				writing="Do you want to get a hint?\n";
				write(writing);
				
				cout<<"1 - yes			0 - no\n";
				
				do{
				wantHint=_getche()-48;
				cout<<'\n';
				
				if(wantHint==1){
					hintOut(currentEngWord, 0);
					
					if(answers>1)
					for(int i=1;i<answers;i++){
						cout<<"	or	";
						hintOut(currentEngWord, i);
					}
					
					cout<<'\n';
				}
				
				else if(wantHint==0){
					
				}
				
				else{
					writing="Choose 1 or 0 (again)\n";
					write(writing);
				}
				
				}while(wantHint!=0 && wantHint!=1);
			}
			
			else if(countIncorrect>3 && wantHint==1){
				cout<<"skip?\n";
				cout<<"1 - yes			0 - no\n";
				
				do{
				wantHint=_getche()-48;
				cout<<'\n';
				
				if(wantHint==1){
					blanks++;
					wordsToLearn[toLearnIndex]++;
					for(int i=0;i<answers;i++) cout<<"	"<<currentEngWord[i]<<'\n';
					Sleep(500);
					system("CLS");
					goto surrender;
				}
				
				else if(wantHint==0){
					wantHint=1;
				}
				
				else{
					writing="Yes(1) or No(0)\n";
					write(writing);
				}
				
				}while(wantHint!=0 && wantHint!=1);
			}
			countIncorrect++;
		}
		else{
			
			if(countIncorrect==1){
				spot_on++;
			}
			
			else{
				corrected++;
				wordsToLearn[toLearnIndex]++;
			}
			
			cout<<"correct\n\n";
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
			
			writing="'" + urWordsToLearn[i] + "' to po angielsku: ";
			write(writing);
			
			clearAr(currentEngWord);
			countIncorrect=1;
			answers=0;
			
			splitUpWords(engWordsToLearn[i], currentEngWord, answers);
			
			do{
		getline(cin, inputAnswer);
		
		if(inputAnswer=="end" && !doesWordAppeared(currentEngWord, answers, "end")){
			system("CLS");
			goto end_credits;
		}
		
		if(inputAnswer=="exit" && !doesWordAppeared(currentEngWord, answers, "exit")){
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
			cout<<"not correct\n";
			
			if(countIncorrect==3 || (countIncorrect>3 && wantHint==0)){
		//-------------hint_suggestion----------------------
				writing="Do you want to get a hint?\n";
				write(writing);
				
				cout<<"1 - yes			0 - no\n";
				
				do{
				wantHint=_getche()-48;
				cout<<'\r'<<'\n';
				
				if(wantHint==1){
					hintOut(currentEngWord, 0);
					
					if(answers>1)
					for(int i=1;i<answers;i++){
						cout<<"	or	";
						hintOut(currentEngWord, i);
					}
					
					cout<<'\n';
				}
				
				else if(wantHint==0){
					
				}
				
				else{
					writing="Choose 1 or 0 (again)\n";
					write(writing);
				}
				
				}while(wantHint!=0 && wantHint!=1);
			}
			
			else if(countIncorrect>3 && wantHint==1){
				cout<<"skip?\n";
				cout<<"1 - yes			0 - no\n";
				
				do{
				wantHint=_getche()-48;
				cout<<'\n';
				
				if(wantHint==1){
					blanks++;
					//wordsToLearn[toLearnIndex]++;
					system("CLS");
					goto surrender1;
				}
				
				else if(wantHint==0){
					wantHint=1;
				}
				
				else{
					writing="Yes(1) or No(0)\n";
					write(writing);
				}
				
				}while(wantHint!=0 && wantHint!=1);
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
			
			cout<<"correct\n\n";
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
