//Tyler Evans
//Assign #1 Postfix
// Due Sept 5th (Thursday) 11:59 pm


#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


using namespace std;

string convertInfxToPfx(const string& infx) {
    string pfx = "";
    stack<string> s;
    string sym = "";
    int location = 0;
    
    while(location < infx.size()){
            string sym = infx.substr(location, 1);
                    if(sym.compare(" ") != 0){//if it is not a space than check what it is

                            if(sym.compare("0") == 0 || sym.compare("1") == 0 || sym.compare("2") == 0 || sym.compare("3") == 0 || sym.compare("4") == 0 || sym.compare("5") == 0 || sym.compare("6") == 0 || sym.compare("7") == 0 || sym.compare("8") == 0 || sym.compare("9") == 0){//append operand to pfx
                                int stopLoop = location;
                                while(stopLoop <= infx.size()){
                                    sym = infx.substr(location, 1);
                                    if(sym.compare("0") == 0 || sym.compare("1") == 0 || sym.compare("2") == 0 || sym.compare("3") == 0 || sym.compare("4") == 0 || sym.compare("5") == 0 || sym.compare("6") == 0 || sym.compare("7") == 0 || sym.compare("8") == 0 || sym.compare("9") == 0){
                                         pfx += sym;
                                         location++; 
                                         stopLoop++;
                                    }
                                    else{
                                        location--;
                                        stopLoop = infx.size() + 10;
                                        pfx += " ";
                                    }
                                }
                            }//----end--is operand

                            else if(sym.compare("(") == 0){//push '(' to the stack
                                    s.push(sym);
                            }//----end--is '('

                            else if(sym.compare(")") == 0){//top everything to pfx
                                    while(s.top().compare("(") != 0){//append higher operands as long as there is no '('
                                            pfx += s.top();
											pfx += " ";
                                            s.pop();
                                    }
									if(s.top().compare("(") == 0){
										s.pop();
									}
                            }//----end--is ')'

                            else if(sym.compare("+") == 0 || sym.compare("-") == 0 || sym.compare("*") == 0 || sym.compare("/") == 0 || sym.compare("^") == 0){//is sym an operator

                                    if(sym.compare("+") == 0 || sym.compare("-") == 0){//----begin--lower operand ---- operator is either '+' or '-'
                                        int stopLoop = 0;
                                        while(stopLoop < s.size()){
                                             if(s.top().compare("(") == 0){//append operands equal to or higher than '+' or '-' as long as there is no '('
                                                 stopLoop = s.size();
                                            }
                                             else{
                                                    pfx += s.top();
													pfx += " ";
                                                    s.pop();
                                                    stopLoop++;
                                             }
                                        }
                                        s.push(sym);
                                    }//----end--lower operator compare and loop

                                    else if(sym.compare("*") == 0 || sym.compare("/") == 0){//----begin--mid operand ---- operator is either '*' or '/'
                                        int stopLoop = 0;
										stack<string> temp;//initiate a temporary stack to hold operators that are of lesser precedence
                                        while(stopLoop < s.size()){//append operands equal to or higher than '*' or '/' as long as there is no '('
                                            if(s.top().compare("+") == 0 || s.top().compare("-") == 0){//'+' and '-" are not higher operands than '*' or '/'
                                                    temp.push(s.top());
                                                    s.pop();
													stopLoop++;
                                            }
                                            else if(s.top().compare("(") == 0){
                                                    stopLoop = s.size();
                                            }
											else{
												pfx += s.top();
												s.pop();
												stopLoop++;
											}
                                        }
										while(temp.size() > 0){//push  lower operators back onto the stack
											s.push(temp.top());
											temp.pop();
                                        }
										s.push(sym);
                                    }//----end--mid operator compare and loop

                                    else if(sym.compare("^") == 0){//----begin--high operand ---- operator is '^'
										int stopLoop = 0;
										stack<string> temp;//initiate a temporary stack to hold operators that are of lesser precedence
                                        while(stopLoop < s.size()){//append operands equal to or higher than '^' as long as there is no '('
												if(s.top().compare("(") == 0){
                                                    stopLoop = s.size();
												}
                                                else if(s.top().compare("^") != 0){
                                                        temp.push(s.top());
                                                        s.pop();
                                                }
                                                else{
                                                        pfx += s.top();
                                                        s.pop();
                                                }
                                        }
										while(temp.size() > 0){//push  lower operators back onto the stack
                                            s.push(temp.top());
                                            temp.pop();
                                        }
										s.push(sym);
                                    }//----end--high operator compare and loop
                            }//----end--is operator
						/*cout << "infx is: " << infx << endl;
						cout << "PFX is: " << pfx << endl;
						cout << "sym is: " << sym << endl;
						if(s.size() > 0){
							cout << "top is: " << s.top() << endl;
						}*/
                    }//----end--compare ' '
            location++;
        }
    while(s.size() > 0){
        if(s.top().compare("(") != 0){
                pfx += s.top();
				pfx += " ";
        }
        s.pop();
     }
    return pfx.substr(0, (pfx.size()-1));
}



//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

    //get rid of spaces
    whatItIs.erase(whatItIs.begin(), std::find_if(whatItIs.begin(), whatItIs.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    whatItIs.erase(std::find_if(whatItIs.rbegin(), whatItIs.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), whatItIs.end());
            
	if (whatItShouldBe == whatItIs) {
		cout << "Passed test " << testName << " ***  Output was \""<< whatItIs << "\"" << endl;
		return true;
	}
	else { 
		if (whatItShouldBe == "") {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was \""<< whatItIs << "\"" << endl << "  Output should have been blank. " << endl;
		} else {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was \""<< whatItIs << "\"" << endl << "  Output should have been \"" << whatItShouldBe << "\"" << endl;
		}
		return false;
	}
}

int main() {
	
	/*string expression = "";
	string result = "";*/

	string expression = "(2+3)";
	string result = convertInfxToPfx(expression);
    checkTest("Test #1", "2 3 +", result);
    
    expression = "2+3";
	result = convertInfxToPfx(expression);
    checkTest("Test #2", "2 3 +", result);

 	expression = "(123+456)";
    result = convertInfxToPfx(expression);
    checkTest("Test #3", "123 456 +", result);

	expression = "(8-5)";
    result = convertInfxToPfx(expression);
    checkTest("Test #4", "8 5 -", result);

	expression = "((3-4)-5)";
	result = convertInfxToPfx(expression);
    checkTest("Test #5", "3 4 - 5 -", result);

    expression = "(3 - (4 - 5))";
	result = convertInfxToPfx(expression);
    checkTest("Test #6", "3 4 5 - -", result);

    expression = "(3*(8/2))";
	result = convertInfxToPfx(expression);
    checkTest("Test #7", "3 8 2 / *", result);

    expression = "3 + 8 / 2";
	result = convertInfxToPfx(expression);
    checkTest("Test #8", "3 8 2 / +", result);

    expression = "24 / 3 + 2";
	result = convertInfxToPfx(expression);
    checkTest("Test #9", "24 3 / 2 +", result);

    expression = "((1 + 2) * (3 + 4))";
	result = convertInfxToPfx(expression);
    checkTest("Test #10", "1 2 + 3 4 + *", result);

    expression = "2^3";
	result = convertInfxToPfx(expression);
    checkTest("Test #11", "2 3 ^", result);

    expression = "8 + 3^4";
	result = convertInfxToPfx(expression);
    checkTest("Test #12", "8 3 4 ^ +", result);

	expression = "(((3+12)-7)*120)/(2+3)";
	result = convertInfxToPfx(expression);
    checkTest("Test #13", "3 12 + 7 - 120 * 2 3 + /", result);

    expression = "((((9+(2*(110-(20/2))))*8)+1000)/2)-((400*2500)-1000001)";
	result = convertInfxToPfx(expression);
    checkTest("Test #14", "9 2 110 20 2 / - * + 8 * 1000 + 2 / 400 2500 * 1000001 - -", result);



    system("pause");
	return 0;
}