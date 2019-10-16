//
//  Dictionary.cpp
//  project2
//
//  Created by Mohib Shah on 3/28/18.
//  Copyright © 2018 Mohib Shah. All rights reserved.
//
// Professor Shanker
// CSCI 135 software analysis and design
// Project 2
//
//
// this project will get user input, go through dictionary to get the pronunciation, identical word, add phoneme,
// replace phoneme, and remove phoneme to find words
//
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void splitOnSpace(string s, string & before, string & after); //  splitspace
void Pronunciation(string word, string& pronunciation); // gets the pronunciation
string makeUppercase(string word); // make user input uppercase incase they enter lowercase
string identical(string pronunciation, string word); // get identical word using their pronunciations
int spaceCheck(string words); // count spaces to find other function addphoneme,replace...
string replacephoneme(string input, string pronunciation); // replace to find word
string removePhoneme(string pronunciation); // remove to find word
string addPhoneme(string pronunciation);
bool check(string l); // check for non alphabetic characters

int main() {
    string input, pronunciation,same,replace,remove,add;
    
    cin >> input;
    input = makeUppercase(input);
    
    Pronunciation(input, pronunciation);
    cout << "Pronunciation    :" << pronunciation << endl;
    cout << endl;
    
    same = identical(pronunciation, input);
    cout << "Identical        :" << same << endl;
    
    add = addPhoneme(pronunciation);
    cout << "Add phoneme      :" << add << endl;
    
    remove = removePhoneme(pronunciation);
    cout << "Remove phoneme   :" << remove << endl;
    
    replace = replacephoneme(input, pronunciation);
    cout << "Replace phoneme  :" << replace << endl;
    
    
    return 0;
}

void splitOnSpace(string s, string & before, string & after) {
    // reset strings
    before = "";
    after = "";
    // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) { before += s[i]; i++; }
    // skip the space
    i++;
    // accumulate after space
    while (i < s.size()) { after += s[i]; i++; }
}
bool check(string l){
    int count = 0;

    
    for(int i = 0;i < l.length(); i++){
        if(((l[i] > 64)&&(l[i] < 91 ))||((l[i] > 96 )&&(l[i] < 123 ))|| l[i] == 39 || l[i] == ' '||(l[i] <= 50 && l[i] >=48)){
            
            count += 1;
        }
    }
    if(count == l.length()){
        return true;
    }
    
    return 0;
}
void Pronunciation(string word, string& pronunciation){
    string before, after, line;
    bool match = false;  //use this to check if word is in dictionary
    ifstream f_handle;

    f_handle.open("cmudict.0.7a");
    if(f_handle.fail()){
        cout << "file unable to open";
        exit(1);
    }
    while(getline(f_handle,line)){
        splitOnSpace(line, before, after);
        if(word == before){
            pronunciation = after;
            match = true;
        }
    
    }
    if(!match){
        cout << "not found" << endl;
    }
    

    f_handle.close();

}
string makeUppercase(string word){   // use to make sure all inout is converted to upper case
    string temp;
    for (int i = 0; i < word.length(); i++){
        temp = temp + (char)toupper(word[i]);
        
    }
    return temp;
}
string identical(string pronunciation, string word){
    string before, after, line, same;
    ifstream f_handle;
    f_handle.open("cmudict.0.7a");
    
    while(getline(f_handle,line)){
        splitOnSpace(line, before, after);
            if(pronunciation == after && before != word){
                same += " ";
                same += before;
         
            }
    }
    f_handle.close();
    return same;
}

int spaceCheck(string words){ //space check to get other functions working because you have to compare spaces.
    int counter = 0;
    for(int i = 0; i < words.length(); i++ ){
        if(words[i] == ' '){
            counter++;
            
        }
    }
    return counter;
}
string replacephoneme(string word, string pronunciation){
    string line, before, after, tempbefore, tempafter, spacebefore, spaceafter, left, spaceleft, spacetemp, replace;
    
    int spaces = spaceCheck(pronunciation);
    
    spacetemp = pronunciation;
    
    ifstream f_handle;
    f_handle.open("cmudict.0.7a");
    
    while(getline(f_handle, line)){
        if(check(line)){
            splitOnSpace(line, before, after);
            int spaces2 = spaceCheck(after);
        
        if(word != before && pronunciation != after && spaces == spaces2){
                for(int i=0; i<spaces; i++){
                    splitOnSpace(spacetemp, spacebefore, spaceafter);
                    splitOnSpace(after, tempbefore, tempafter);
                    if(i == 0){
                        if(spaceafter == tempafter){
                            replace += " " + before;
                            }
                        spaceleft = spacebefore;
                        left = tempbefore;
                        
                    }
                    
                    else{
                        if(spaceleft + " " + spaceafter == left + " " + tempafter){
                            replace += " " + before;
                        }
                        left += " " + tempbefore;
                        spaceleft += " " + spacebefore;
                        
                        if(spaceleft == left &&  i == spaces - 1){
                            
                            replace += " " + before;
                        }
                    }
                    
                    spacetemp = spaceafter;
                    after = tempafter;
                }
            }
            
            spacetemp = pronunciation;
            
        
        }
    }
    return replace;
}


string removePhoneme(string pronunciation){
    string line, before, after, spacebefore, spaceafter, left, spacetemp, remove;

    int spaces = spaceCheck(pronunciation);

    spacetemp = pronunciation;
    ifstream f_handle;
    f_handle.open("cmudict.0.7a");
   
    while(getline(f_handle, line)){
        if(check(line)){
        splitOnSpace(line, before, after);
        
        for(int i=0; i<spaces; i++){
            splitOnSpace(spacetemp, spacebefore, spaceafter);
            if(i == 0){
                if(spaceafter == after){
                    remove += " " + before;

                }

                    left = spacebefore;

            }

            else{
                if(left + " " + spaceafter == after){
                    remove += " " + before;

                }

                    left += " " + spacebefore;

                if(left == after && i == spaces-1){
                    remove += " " + before;

                }
            }

                spacetemp = spaceafter;
            }

                spacetemp = pronunciation;
        }
    }
    return remove;
}
string addPhoneme(string pronunciation){
    string line, before, after, tempbefore, tempafter, left, spaces, add;
    
    ifstream f_handle;
    f_handle.open("cmudict.0.7a");
    
    while(getline(f_handle, line)){
        if(check(line)){
            splitOnSpace(line, before, after);
            int spaces = spaceCheck(after);
        
            for(int i=0; i<spaces; i++){
                splitOnSpace(after, tempbefore, tempafter);
                if(i == 0){
                    if(tempafter == pronunciation){
                        add += " " + before;
                    }
                        left = tempbefore;
                    
                }
            else{
                if(left + " " + tempafter == pronunciation){
                        add += " " + before;
                }
                        left += " " + tempbefore;
                    
                if(left == pronunciation && i == spaces-1){
                        add += " " + before;
                }
            }
                
                after = tempafter;
                
            }
        }
    }
    return add;
}





