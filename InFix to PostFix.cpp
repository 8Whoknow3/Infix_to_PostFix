#include "bits/stdc++.h"
#include <iostream>
#include <string>
#include "pbPlots.cpp"
#include "supportLib.cpp"

using namespace std;

bool check(char first, char second){
    if(first == '(') return false;
    if(first == second) return true;
    if(first == '^') return true;
    if(second == '^') return false;
    if(first == '*' || first == '/' && second == '+' || second == '-') return true;
    if(first == '-' || first == '+' && second == '*' || second == '/' ) return false;
    if(first == '-' && second == '+' || first == '+' && second == '-') return true;
    if(first == '*' && second == '/' || first == '/' && second == '*') return true;
}

bool isAmalgar(string s){
    if(s == "-" || s == "+" || s == "*" || s == "/" || s == "^") return true;
    return false;
}

bool amalvand(char s){
    if(s >= '0' && s <= '9' || s >= 'a' && s <= 'z' || s >= 'A' && s <= 'Z' || s == '.')
        return true;
    return false;
}

int main(){
    cout << "Enter String :";
    string S; cin >> S;
    cout << endl << "Your infix is :" << S << endl;
    bool number = false;
    for(auto i : S){
        if(i >= '0' && i <= '9'){
            number = true;
            break;
        }
    }
    stack<string> PostFix;
    stack<char> Amalgar;
    if(number){
        bool flag = false;
        for (int i = 0; i < (int) S.size(); i++) {
            if (S[i] == '(') {
                flag = false;
                Amalgar.push(S[i]);
                continue;
            }
            if (S[i] == '-' && !flag) {
                flag = true;
                string p;
                string temp(1, S[i]);
                p += temp;
                while (true) {
                    i++;
                    if (amalvand(S[i])) {
                        string t(1, S[i]);
                        p += t;
                    } else {
                        i--;
                        break;
                    }
                }
                PostFix.push(p);
            }
            else if (amalvand(S[i])) {
                string p;
                string temp(1, S[i]);
                p += temp;
                while (true) {
                    i++;
                    if (amalvand(S[i])) {
                        string t(1, S[i]);
                        p += t;
                    } else {
                        i--;
                        break;
                    }
                }
                PostFix.push(p);
            }
            else {
                while (true) {
                    if (Amalgar.empty()) {
                        Amalgar.push(S[i]);
                        break;
                    }
                    else if (S[i] == ')') {
                        while (Amalgar.top() != '(') {
                            string temp(1, Amalgar.top());
                            PostFix.push(temp);
                            Amalgar.pop();
                        }
                        Amalgar.pop();
                        break;
                    }
                    else if (check(Amalgar.top(), S[i])) {
                        string temp(1, Amalgar.top());
                        PostFix.push(temp);
                        Amalgar.pop();
                        continue;
                    }
                    else if (!check(Amalgar.top(), S[i])) {
                        Amalgar.push(S[i]);
                        break;
                    }
                }
            }
        }
        while (!Amalgar.empty()) {
            string temp(1, Amalgar.top());
            PostFix.push(temp);
            Amalgar.pop();
        }
    }
    else if(!number){
        for(char i : S){
            if(i == '-' || i == '*' || i == '+' || i == '(' || i == ')' || i == '^' || i == '/'){
                while(true) {
                    if(Amalgar.empty()){
                        Amalgar.push(i);
                        break;
                    }
                    else if(i == '('){
                        Amalgar.push(i);
                        break;
                    }
                    else if(i == ')'){
                        while(Amalgar.top() != '('){
                            string temp(1, Amalgar.top());
                            PostFix.push(temp);
                            Amalgar.pop();
                        }
                        Amalgar.pop();
                        break;
                    }
                    else if(check(Amalgar.top(), i)) {
                        string temp(1, Amalgar.top());
                        PostFix.push(temp);
                        Amalgar.pop();
                        continue;
                    }
                    else if(!check(Amalgar.top(), i)) {
                        Amalgar.push(i);
                        break;
                    }
                }
            }
            else{
                string temp(1, i);
                PostFix.push(temp);
            }
        }
        while(!Amalgar.empty()){
            string temp(1, Amalgar.top());
            PostFix.push(temp);
            Amalgar.pop();
        }
    }
    stack<string> ans;
    while(!PostFix.empty()){
        ans.push(PostFix.top());
        PostFix.pop();
    }
    PostFix = ans;
    cout << "Your Postfix is :";
    while(!PostFix.empty()){
        cout << PostFix.top() << " ";
        PostFix.pop();
    }
    stack<string> result;
    if(number){
        while (!ans.empty()) {
            if(isAmalgar(ans.top())){
                double answer = 0;
                double two = stod(result.top());
                result.pop();
                double one = stod(result.top());
                result.pop();
                string amal = ans.top();
                ans.pop();
                if (amal == "+") {
                    answer = one + two;
                    result.push(to_string(answer));
                }
                else if (amal == "-") {
                    answer = one - two;
                    result.push(to_string(answer));
                }
                else if (amal == "*") {
                    answer = one * two;
                    result.push(to_string(answer));
                }
                else if (amal == "^") {
                    answer = pow(one, two);
                    result.push(to_string(answer));
                }
                else if (amal == "/") {
                    answer = one / two;
                    result.push(to_string(answer));
                }
            }
            else {
                result.push(ans.top());
                ans.pop();
            }
        }
        cout << endl << "Your result is :" << result.top() << endl;
    }
    else{
        vector<double> X{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; vector<double> Y;
        if(ans.size() == 1)
            for(double i = 1; i <= 15; i++)
                Y.push_back(i);
        else {
            for (double i = 1; i <= 15; i++) {
                stack<string>assist;
                assist = ans;
                while (!assist.empty()) {
                    if (isAmalgar(assist.top())) {
                        double answer = 0;
                        double two = stod(result.top());
                        result.pop();
                        double one = stod(result.top());
                        result.pop();
                        string amal = assist.top();
                        assist.pop();
                        if (amal == "+") {
                            answer = one + two;
                            result.push(to_string(answer));
                        } else if (amal == "-") {
                            answer = one - two;
                            result.push(to_string(answer));
                        } else if (amal == "*") {
                            answer = one * two;
                            result.push(to_string(answer));
                        } else if (amal == "^") {
                            answer = pow(one, two);
                            result.push(to_string(answer));
                        } else if (amal == "/") {
                            answer = one / two;
                            result.push(to_string(answer));
                        }
                    }
                    else {
                        result.push(to_string(i));
                        assist.pop();
                    }
                }
                Y.push_back(stod(result.top()));
                result.pop();
            }
        }
        bool success;
        StringReference *errorMessage = new StringReference();
        RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
        success = DrawScatterPlot(imageReference, 600, 400, &X, &Y, errorMessage);
        if(success) {
            vector<double> *pngdata = ConvertToPNG(imageReference->image);
            WriteToFile(pngdata, "Graph.png");
            DeleteImage(imageReference->image);
        }
        else{
            cerr << "Error: ";
            for(wchar_t c : *errorMessage->string){
                wcerr << c;
            }
            cerr << endl;
        }
    }
    return 0;
}