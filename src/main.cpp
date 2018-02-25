#include "base.h"
#include "op.h"
#include "connector.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cstring>
using namespace std;
using namespace boost;

//Declares execute functions
void execute1(string);
void execute2(string);
void execute3(string);
int checkSpaces(string); 
string testCommand(string );
string userPromptParsing(string);
int isDirectory(string );
int FileExists(string );
string bracketParse(string);
vector<string> parse(vector<string>);
void singleRedirect(string );
void doubleRedirect(string );
void exec1(int ,int ,string );
void exec2(int ,int ,string );
void exec3(int ,int ,string );
void exec4(int ,int ,string );

int main ()
{
    Connector* c = new Connector();
    
    string userPrompt = "";
    
    //keep looping till 
    while (1 == 1)
    {
    	//takes in userprompt
		cout << "$ ";
		getline(cin, userPrompt);
		
		//parses string to make sure there's space before and after connector
		userPrompt = userPromptParsing(userPrompt);
		
		for ( unsigned i = 0; i < userPrompt.size(); i++)
		{
			if (userPrompt.find(" | ") != string::npos)
			{
				int i = userPrompt.find(" | ");
				userPrompt.replace(i + 1, 1, "4");
				//cout << userPrompt << endl;
			}
		}
		
		//split string by using 3 delimiters: ' '
		split(c->cmds, userPrompt, is_any_of(" "));
		
		//combines commands into one element
		
		if (userPrompt.find("||") != string::npos || userPrompt.find("4") != string::npos || userPrompt.find("&&") != string::npos || userPrompt.find(";") != string::npos)
		{
			c->cmds = parse(c->cmds);//just added
		}
		
		for (unsigned int i = 0;i < c->cmds.size(); i++)
		{
			if (c->cmds.at(i) == "")
			{
				//gets rid of empty elements
				c->cmds.pop_back();
			}
		}
		
		//if "||", "4", "&&", ";" is found in userPrompt then change to respective numbers
		if ((userPrompt.find("||") != string::npos) || (userPrompt.find("4") != string::npos) || (userPrompt.find("&&") != string::npos) || (userPrompt.find(";") != string::npos))
		{
			for (unsigned int i = 0; i < c->cmds.size(); i++)
			{
				//Assigns or with value of 1
				if(c->cmds.at(i) == "||")
				{
					c->cmds.at(i) = "1";	
				}
				//Assigns and with value of 2
				else if (c->cmds.at(i) == "&&")
				{
					c->cmds.at(i) = "2";
				}
				//Assigns semicolon with value of 3
				else if (c->cmds.at(i) == ";")
				{
					c->cmds.at(i) = "3";
				}
				else if (c->cmds.at(i) == "4")
				{
					c->cmds.at(i) = "4";
				}
				//cout << c->cmds.at(i) << endl;
			}
			//Tree vector of type Connector
			vector<Connector*> tree;
			//Initializing new objects of type Op
			Op * a = new Op(c->cmds.at(0));
			Op * b = new Op(c->cmds.at(2));
			
			//Initializing new objects of type Connector
			Connector * r = new Connector((c->cmds.at(1)));
			
			r->lhs = a;
			r->rhs = b;
			
			
			//Push into vector
			tree.push_back(r);
			int count = 1;
			//if root of r equals 4(|) then execute
			if (r->eVal() == "4")
			{
				string left = r->lhs->eVal();
				if (left.find(" ") == string::npos)
				{
					execute1(left);
				}
				else
				{
					int c = checkSpaces(left);
					//if 1 space
					if ( c == 1)
					{	
						execute2(left);
					}
					//if 2 spaces
					else if ( c == 2)
					{
						if ((left.find("<") != string::npos) && (left.find(">") != string::npos) && (left.find(">>") != string::npos))
						{
							execute3(left);
						}
						if (left.find(">>") != string::npos)
						{
							doubleRedirect(left);
						}
						else if (left.find("<") != string::npos || left.find(">") != string::npos)
						{
							singleRedirect(left);
						}
					}
					//if 3 spaces
					else if ( c == 3)
					{
						if ((left.find("<") != string::npos) && (left.find(">") != string::npos) && (left.find(">>") != string::npos))
						{
							string newString = bracketParse(left);
							execute3(newString);
						}
						if (left.find(">>") != string::npos)
						{
							doubleRedirect(left);
						}
						else if (left.find("<") != string::npos || left.find(">") != string::npos)
						{
							singleRedirect(left);
						}
					}
					else 
					{
						if (left.find(">>") != string::npos)
						{
							doubleRedirect(left);
						}
						else
						{
							singleRedirect(left);
						}
					}
						
				}
				string right = r->rhs->eVal();
				if (right.find(" ") == string::npos)
				{
					execute1(right);
				}
				else
				{
					//cout << "|:right side " << endl;
					int c = checkSpaces(right);
					//if 1 space
					if ( c == 1)
					{
						execute2(right);
					}
					//if 2 spaces
					else if (c == 2)
					{
						if ((right.find("<") != string::npos) && (right.find(">") != string::npos) && (right.find(">>") != string::npos))
						{
							execute3(right);
						}
						if (right.find(">>") != string::npos)
						{
							doubleRedirect(right);
						}
						else if (right.find("<") != string::npos || right.find(">") != string::npos)
						{
							singleRedirect(right);
						}
					}
					//if 3 spaces
					else if ( c == 3)
					{
						if ((right.find("<") != string::npos) && (right.find(">") != string::npos) && (right.find(">>") != string::npos))
						{
							string newString = bracketParse(right);
							execute3(newString);
						}
						if (right.find(">>") != string::npos)
						{
							doubleRedirect(right);
						}
						else if (right.find("<") != string::npos || right.find(">") != string::npos)
						{
							singleRedirect(right);
						}
					}
					else 
					{
						if (right.find(">>") != string::npos)
						{
							doubleRedirect(right);
						}
						else
						{
							singleRedirect(right);
						}
					}
				}
			}
			if (r->eVal() == "3" || r->eVal() == "2")
			{
				//cout << "in &&, ; cases " << endl;
				string left = r->lhs->eVal();
				if (left.find(" ") == string::npos)
				{
					execute1(left);
				}
				else
				{
					//cout << left << " is left side" << endl;
					int c = checkSpaces(left);
						//if 1 space
						if ( c == 1)
						{	
							
							execute2(left);
						}
						//if 2 spaces
						else if ( c == 2)
						{
							if ((left.find("<") != string::npos) && (left.find(">") != string::npos) && (left.find(">>") != string::npos))
							{
								execute3(left);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						//if 3 spaces
						else if ( c == 3)
						{
							if ((left.find("<") != string::npos) && (left.find(">") != string::npos) && (left.find(">>") != string::npos))
							{	
								string newString = bracketParse(left);
								execute3(newString);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						else 
						{
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
				}
				string right = r->rhs->eVal();
				if (right.find(" ") == string::npos)
				{
					execute1(right);
				}
				else
				{
					int c = checkSpaces(right);
					if (c == 1)
					{
						execute2(right);
					}
					else if (c == 2)
					{
						if ((right.find("<") != string::npos) && (right.find(">") != string::npos) && (right.find(">>") != string::npos))
						{
							execute3(right);
						}
						if (right.find(">>") != string::npos)
						{
							doubleRedirect(right);
						}
						else
						{
							singleRedirect(right);
						}
					}
					else if (c == 3)
					{
						if ((right.find("<") != string::npos) && (right.find(">") != string::npos) && (right.find(">>") != string::npos))
						{
							string newString = bracketParse(right);
							execute3(newString);
						}
						if (right.find(">>") != string::npos)
						{
							doubleRedirect(right);
						}
						else
						{
							singleRedirect(right);
						}
					}
					else if (c >= 4)
					{
						if (right.find(">>") != string::npos)
						{
							doubleRedirect(right);
						}
						else
						{
							singleRedirect(right);
						}
					}
				}
			}
			//if root of r equals 1(||) then execute
			else if (r->eVal() == "1"){
			    //cout << "in || cases " << endl;
			
				string left = r->lhs->eVal();
				
				if (left.find(" ") == string::npos)
				{
					execute1(left);
				}
				else
				{
					int c = checkSpaces(left);
					if ( c == 1)
					{
						execute2(left);
					}
					else if (c == 2)
					{
						if ((left.find("<") != string::npos) && (left.find(">") != string::npos) && (left.find(">>") != string::npos))
						{
							execute3(left);
						}
						if (left.find(">>") != string::npos)
						{
							doubleRedirect(left);
						}
						else
						{
							singleRedirect(left);
						}
					}
					else if ( c == 3)
					{
						if ((left.find("<") != string::npos) && (left.find(">") != string::npos) && (left.find(">>") != string::npos))
						{
							string newString = bracketParse(left);
							execute3(newString);
						}
						if (left.find(">>") != string::npos)
						{
							doubleRedirect(left);
						}
						else
						{
							singleRedirect(left);
						}
					}
					else 
					{
						if (left.find(">>") != string::npos)
						{
							doubleRedirect(left);
						}
						else
						{
							singleRedirect(left);
						}
					}
					
				}
			}
			
			//loop to create a tree starting from the third element
			for (unsigned i = 3; i + 1 < c->cmds.size(); i = i + 2)
			{
				
				Connector * temp;
				tree.pop_back();
				//removes last Connector object from tree vector
				Connector * next = new Connector(c->cmds.at(i));
				
				//loops after initial tree
				if (i == 3)
				{
					next->lhs = r;
				}
				else
				{
					next->lhs = temp;	
				}
				//Assigns previous next value(temp) to lhs of root
				next->rhs = new Op(c->cmds.at(i+1));
				//Assigns to rhs of root
				
				count = count + 1;
				
				if (r->eVal() == "4")
				{
					string left = next->lhs->eVal();
					if (left.find(" ") == string::npos)
					{
						execute1(left);
					}
					else
					{
						//if one space then do execute2 if two spaces do execute 3
						int c = checkSpaces(left);
						if ( c == 1)
						{
							execute2(left);
						}
						else if (c == 2)
						{
							if ((left.find("<") == string::npos) && (left.find(">") == string::npos) && (left.find(">>") == string::npos))
							{
								execute3(left);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						else if ( c == 3)
						{
							if ((left.find("<") == string::npos) && (left.find(">") == string::npos) && (left.find(">>") == string::npos))
							{
								string newString = bracketParse(left);
								execute3(newString);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						else 
						{
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
					}
					string right = next->rhs->eVal();
					
					if (right.find(" ") == string::npos)
					{
						execute1(right);
					}
					else
					{
						int c = checkSpaces(right);
						//if one space then do execute2 if two spaces do execute 3
						if ( c == 1)
						{
							execute2(right);
						}
						else if (c == 2)
						{
							if ((right.find("<") == string::npos) && (right.find(">") == string::npos) && (right.find(">>") == string::npos))
							{
								execute3(left);
							}
							if (right.find(">>") != string::npos)
							{
								doubleRedirect(right);
							}
							else
							{
								singleRedirect(right);
							}
						}
						else if ( c == 3)
						{
							if ((right.find("<") == string::npos) && (right.find(">") == string::npos) && (right.find(">>") == string::npos))
							{
								string newString = bracketParse(right);
								execute3(newString);
							}
							if (right.find(">>") != string::npos)
							{
								doubleRedirect(right);
							}
							else
							{
								singleRedirect(right);
							}
						}
						else 
						{
							if (right.find(">>") != string::npos)
							{
								doubleRedirect(right);
							}
							else
							{
								singleRedirect(right);
							}
						}
					}
				}
				//checks connectors and tells tree to execute certain commands based on connectors
				else if (next->eVal() == "3" || next->eVal() == "2")
				{
					string left = next->lhs->eVal();
					if (left.find(" ") == string::npos)
					{
						execute1(left);
					}
					else
					{
						//if one space then do execute2 if two spaces do execute 3
						int c = checkSpaces(left);
						if ( c == 1)
						{
							execute2(left);
						}
						else if (c == 2)
						{
							if ((left.find("<") == string::npos) && (left.find(">") == string::npos) && (left.find(">>") == string::npos))
							{
								execute3(left);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						else if ( c == 3)
						{
							if ((left.find("<") == string::npos) && (left.find(">") == string::npos) && (left.find(">>") == string::npos))
							{
								string newString = bracketParse(left);
								execute3(newString);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						else
						{
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
							
						}
					}
					string right = next->rhs->eVal();
					
					if (right.find(" ") == string::npos)
					{
						execute1(right);
					}
					else
					{
						int c = checkSpaces(right);
						//if one space then do execute2 if two spaces do execute 3
						if ( c == 1)
						{
							execute2(right);
						}
						else if (c == 2)
						{
							if ((right.find("<") == string::npos) && (right.find(">") == string::npos) && (right.find(">>") == string::npos))
							{
								execute3(right);
							}
							if (right.find(">>") != string::npos)
							{
								doubleRedirect(right);
							}
							else
							{
								singleRedirect(right);
							}
						}
						else if ( c == 3)
						{
							if ((right.find("<") == string::npos) && (right.find(">") == string::npos) && (right.find(">>") == string::npos))
							{
								string newString = bracketParse(right);
								execute3(newString);
							}
							if (right.find(">>") != string::npos)
							{
								doubleRedirect(right);
							}
							else
							{
								singleRedirect(right);
							}
						}
						else 
						{
							if (right.find(">>") != string::npos)
							{
								doubleRedirect(right);
							}
							else
							{
								singleRedirect(right);
							}
						}
					}
				}
				else if (next->eVal() == "1")
				{
					string left = next->lhs->eVal();
					if (left.find(" ") == string::npos)
					{
						execute1(left);
					}
					else
					{
						//if one space then do execute2 if two spaces do execute 3
						int c = checkSpaces(left);
						if ( c == 1)
						{
							execute2(left);
						}
						else if (c == 2)
						{
							if ((left.find("<") == string::npos) && (left.find(">") == string::npos) && (left.find(">>") == string::npos))
							{
								execute3(left);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}//if 3 spaces
						else if ( c == 3)
						{
							if ((left.find("<") == string::npos) && (left.find(">") == string::npos) && (left.find(">>") == string::npos))
							{
								string newString = bracketParse(left);
								execute3(newString);
							}
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
						else 
						{
							if (left.find(">>") != string::npos)
							{
								doubleRedirect(left);
							}
							else
							{
								singleRedirect(left);
							}
						}
					}
				}
				//pushes next into tree
				tree.push_back(next);
				//assigns next to temp
				temp = next;
				
			}
		}
		else
		{
			//To exit program
			if (userPrompt == "exit")
			{
				exit(1);
			}
			else if (c->cmds.size() == 2)
			{
				if(userPrompt.find("test") != string::npos)
				{
					cout << "test: missing an argument" << endl;
				}
				else
				{
					execute2(userPrompt);
				}
			}
			else if (c->cmds.size() == 1)
			{
				execute1(userPrompt);
			}
			else if (c->cmds.size() == 3)
			{
				if ((userPrompt.find("<") == string::npos) && (userPrompt.find(">") == string::npos) && (userPrompt.find(">>") == string::npos))
				{
					execute3(userPrompt);
				}
				if (userPrompt.find(">>") != string::npos)
				{
					doubleRedirect(userPrompt);
				}
				else if(userPrompt.find(">") != string::npos || userPrompt.find("<") != string::npos)
				{
					singleRedirect(userPrompt);
				}
			}
			else if (c->cmds.size() == 4)
			{
				if (userPrompt.find("[") != string::npos)
				{
					string newString = bracketParse(userPrompt);
					//int index = userPrompt.find('[');
					execute3(newString);
				}
				if (userPrompt.find(">>") != string::npos)
				{
					//Calls DoubleRedirect function if >> is found
					doubleRedirect(userPrompt);
				}
				else
				{
					//Calls SingleRedirect function if > is found
					singleRedirect(userPrompt);
				}
			}
			else
			{
				if (userPrompt.find(">>") != string::npos)
				{ 
					//Calls DoubleRedirect function if >> is found
					doubleRedirect(userPrompt);
				}
				else
				{
					//Calls SingleRedirect function if > is found
					singleRedirect(userPrompt);
				}
			}
		}
    }
    return 0;
}

//execute function with two arguments
void execute1(string command)
{
	//if it's exit command don't use execvp just use exit(1)
	if(command == "exit")
	{
		exit(1);	
	}
	else
	{
		vector<string> parts;
		split(parts, command, is_any_of(" "));
		
		for(unsigned i = 0; i < parts.size(); i++)
		{
			if(parts.at(i).find("(") != string::npos)
			{
				parts.at(i).erase(parts.at(i).find("("), 1);
			}
		}
		
		
		char* args[2];
		args[0] = (char*)parts.at(0).c_str();
		args[1] = NULL;
		
		
				
		pid_t pid = fork();
		if (pid == 0)
		{
			//child process is run 
			if (execvp (args[0], args) == -1)
			{
				perror("exec");
			}
		}
		if (pid > 0)
		{
			//parent process resumes after child process is done executing
			if (wait(0) == -1)
			{
				perror("wait");
			}
		}
	}
}

//execute function with 3 arguments
void execute2 (string command)
{
	vector<string> parts;
	split(parts, command, is_any_of(" "));
	
	//if parts strings have "(" or ")" erase it from the string
	for(unsigned i = 0; i < parts.size(); i++)
	{
		if(parts.at(i).find("(") != string::npos)
		{
			parts.at(i).erase(parts.at(i).find("("), 1);
		}
		if(parts.at(i).find(")") != string::npos)
		{
			parts.at(i).erase(parts.at(i).find(")"), 1);
		}
	}
	

	char* args[3];
	
	args[0] = (char*)parts.at(0).c_str();
	args[1] = (char*)parts.at(1).c_str();
	args[2] = NULL;
	
			
	pid_t pid = fork();
	
	if(pid == 0)
	{
		//child process is run 
		if (execvp (args[0], args) == -1)
		{
			perror("exec");
		}
	}
	if(pid > 0)
	{
		//parent process resumes after child process is done executing
		if(wait(0) == -1)
		{
			perror("wait");
		}
	}
}

//execute function with 3 arguments
void execute3 (string command)
{
	//if test command use custom test instead of using exec sys call
	if(command.find("test") != string::npos)
	{
			cout << testCommand(command.c_str()) << endl;
	}
	else
	{
		vector<string> parts;
		split(parts, command, is_any_of(" "));
		
		for(unsigned i = 0; i < parts.size(); i++)
		{
			if(parts.at(i).find("(") != string::npos)
			{
				parts.at(i).erase(parts.at(i).find("("), 1);
			}
			if(parts.at(i).find(")") != string::npos)
			{
				parts.at(i).erase(parts.at(i).find(")"), 1);
			}
		}
	
		//four arguments
		char* args[4];
		
		// puts in the args 
		args[0] = (char*)parts.at(0).c_str();
		args[1] = (char*)parts.at(1).c_str();
		args[2] = (char*)parts.at(2).c_str();
		args[3] = NULL;
		
				
		pid_t pid = fork();
		
		if(pid == 0)
		{
			//child process is run 
			if (execvp (args[0], args) == -1)
			{
				perror("exec");
			}
		}
		if(pid > 0)
		{
			//parent process resumes after child process is done executing
			if(wait(0) == -1)
			{
				perror("wait");
			}
		}
	}
}


//converts vector to separate commands
vector<string> parse(vector<string> okay)
{
	//New string vector, will combine strings and push to this vector
	vector<string> done;
    
    string str = "";
    for (unsigned i = 0; i < okay.size(); i++)
    {
    	//checks if string is not equal to '||', '&&', ';', "4"
        if ((okay.at(i) != "||") && (okay.at(i) != "4") && (okay.at(i) != "&&") && (okay.at(i) != ";"))
        {
            if (str == "")
            {
                str = okay.at(i);
            }
            else 
            {
            	//str gets incremented by okay.at(i)
                str = str + " " + okay.at(i);
            }
        }
        
        //if string equals || then push str and || to the done vector
        else if ((okay.at(i) == "||"))
        {
            
            done.push_back(str);
            done.push_back(okay.at(i));
            //str.resize(0);
            str = "";
        }
        //if string equals 4 then push str and && to the done vector
        else if (okay.at(i) == "4")
        {
            done.push_back(str);
            done.push_back(okay.at(i));
            //str.resize(0);
            str = "";
        }
        //if string equals && then push str and && to the done vector
        else if (okay.at(i) == "&&")
        {
            done.push_back(str);
            done.push_back(okay.at(i));
            //str.resize(0);
            str = "";
        }
        //if string equals ; then push str and ; to the done vector
        else if (okay.at(i) == ";")
        {
            done.push_back(str);
            done.push_back(okay.at(i));
            //str.resize(0);
            str = "";
        }
        
        
        
    }
    
    //checks to see if last six strings in okay vector are not equal to '||', '&&', ";", "4", then pushes them into the done vector
    if ((okay.size() >= 6) && ((okay.at(okay.size() - 1) != "||" && okay.at(okay.size() - 2) != "||" && okay.at(okay.size() - 3) != "||" && okay.at(okay.size() - 4) != "||" && okay.at(okay.size() - 5) != "||" && okay.at(okay.size() - 6) != "||") && (okay.at(okay.size() - 1) != "4" && okay.at(okay.size() - 2) != "4" && okay.at(okay.size() - 3) != "4" && okay.at(okay.size() - 4) != "4" && okay.at(okay.size() - 5) != "4" && okay.at(okay.size() - 6) != "4") && (okay.at(okay.size() - 1) != ";" && okay.at(okay.size() - 2) != ";" && okay.at(okay.size() - 3) != ";" && okay.at(okay.size() - 4) != ";" && okay.at(okay.size() - 5) != ";" && okay.at(okay.size() - 6) != ";") && (okay.at(okay.size() - 1) != "&&" && okay.at(okay.size() - 2) != "&&" && okay.at(okay.size() - 3) != "&&" && okay.at(okay.size() - 4) != "&&" && okay.at(okay.size() - 5) != "&&" && okay.at(okay.size() - 6) != "&&")))
    {
        done.push_back(okay.at(okay.size() - 6) + " " + okay.at(okay.size() - 5) + " " + okay.at(okay.size() - 4) + " " + okay.at(okay.size() - 3) + " " + okay.at(okay.size() - 2) + " " + okay.at(okay.size() - 1));
    }
    //checks to see if last five strings in okay vector are not equal to '||', '&&', ";", "4", then pushes them into the done vector
    else if ((okay.size() >= 5) && ((okay.at(okay.size() - 1) != "||" && okay.at(okay.size() - 2) != "||" && okay.at(okay.size() - 3) != "||" && okay.at(okay.size() - 4) != "||" && okay.at(okay.size() - 5) != "||") && (okay.at(okay.size() - 1) != "4" && okay.at(okay.size() - 2) != "4" && okay.at(okay.size() - 3) != "4" && okay.at(okay.size() - 4) != "4" && okay.at(okay.size() - 5) != "4") && (okay.at(okay.size() - 1) != ";" && okay.at(okay.size() - 2) != ";" && okay.at(okay.size() - 3) != ";" && okay.at(okay.size() - 4) != ";" && okay.at(okay.size() - 5) != ";") && (okay.at(okay.size() - 1) != "&&" && okay.at(okay.size() - 2) != "&&" && okay.at(okay.size() - 3) != "&&" && okay.at(okay.size() - 4) != "&&" && okay.at(okay.size() - 5) != "&&")))
    {
        done.push_back(okay.at(okay.size() - 5) + " " + okay.at(okay.size() - 4) + " " + okay.at(okay.size() - 3) + " " + okay.at(okay.size() - 2) + " " + okay.at(okay.size() - 1));
    }
    //checks to see if last four strings in okay vector are not equal to '||', '&&', ";", "4", then pushes them into the done vector
    else if ((okay.size() >= 4) && ((okay.at(okay.size() - 1) != "||" && okay.at(okay.size() - 2) != "||" && okay.at(okay.size() - 3) != "||" && okay.at(okay.size() - 4) != "||") && (okay.at(okay.size() - 1) != "4" && okay.at(okay.size() - 2) != "4" && okay.at(okay.size() - 3) != "4" && okay.at(okay.size() - 4) != "4") && (okay.at(okay.size() - 1) != ";" && okay.at(okay.size() - 2) != ";" && okay.at(okay.size() - 3) != ";" && okay.at(okay.size() - 4) != ";") && (okay.at(okay.size() - 1) != "&&" && okay.at(okay.size() - 2) != "&&" && okay.at(okay.size() - 3) != "&&" && okay.at(okay.size() - 4) != "&&")))
    {
        done.push_back(okay.at(okay.size() - 4) + " " + okay.at(okay.size() - 3) + " " + okay.at(okay.size() - 2) + " " + okay.at(okay.size() - 1));
    }
    //checks to see if last three strings in okay vector are not equal to '||', '&&', ";", "4", then pushes them into the done vector
    else if ((okay.size() >= 3) && ((okay.at(okay.size() - 1) != "||" && okay.at(okay.size() - 2) != "||" && okay.at(okay.size() - 3) != "||") && (okay.at(okay.size() - 1) != "4" && okay.at(okay.size() - 2) != "4" && okay.at(okay.size() - 3) != "4") && (okay.at(okay.size() - 1) != ";" && okay.at(okay.size() - 2) != ";" && okay.at(okay.size() - 3) != ";") && (okay.at(okay.size() - 1) != "&&" && okay.at(okay.size() - 2) != "&&" && okay.at(okay.size() - 3) != "&&")))
    {
        done.push_back(okay.at(okay.size() - 3) + " " + okay.at(okay.size() - 2) + " " + okay.at(okay.size() - 1));
    }
    //checks to see if last two strings in okay vector are not equal to '||', '&&', ";", "4", then pushes them into the done vector
    else if ((okay.size() >= 2) && ((okay.at(okay.size() - 1) != "||" && okay.at(okay.size() - 2) != "||") && (okay.at(okay.size() - 1) != "4" && okay.at(okay.size() - 2) != "4") && (okay.at(okay.size() - 1) != ";" && okay.at(okay.size() - 2) != ";") && (okay.at(okay.size() - 1) != "&&" && okay.at(okay.size() - 2) != "&&")))
    {
        done.push_back(okay.at(okay.size() - 2) + " " + okay.at(okay.size() - 1));
    }
    //checks to see if the last string in okay vector is not equal to '||', '&&', ";", then pushes it into the done vector
    else 
    {
        done.push_back(okay.at(okay.size() - 1));
    }
    return done;
}

//Checks for spaces
int checkSpaces(string prompt)
{
	int count = 0;
	for(unsigned i = 0; i < prompt.size(); i++)
	{
		if(prompt.at(i) == ' ')
		{
			count++;
		}
	}
	return count;
}

//Runs the test command
string testCommand (string name) {
	vector<string> parts;
	split(parts, name, is_any_of(" "));
	struct stat buf;
	for(unsigned i = 0; i < name.size(); i++)
	{
		//Checks for -d flag
		if(name.find("-d") != string::npos)
		{
			 if (isDirectory(parts.at(2)) == 0)
			 {
			 	return "(TRUE)";
			 }
			 else
			 {
			 	return "(FALSE)";
			 }
		}
		//Checks for -f flag
		else if (name.find("-f") != string::npos)
		{
			if(FileExists(parts.at(2)) == 0)
			{
				return "(TRUE)";
			}
			else
			{
				return "(FALSE)";
			}
		}
		//Checks for -e flag
		else if (name.find("-e") != string::npos)
		{
			if( ((stat(parts.at(2).c_str(), &buf)) * -1) == 0)
			{
			 	return "(TRUE)";
			}
			else
			{
			 	return "(FALSE)";
			}
		}
	}
	return "-1";
}

//Checks for directory and returns 0 if true and 1 if false 
int isDirectory(string fileName) {
	struct stat path;
	if( stat(fileName.c_str(), &path) == 0) {
    	if(path.st_mode & S_IFDIR) {
    		return 0;
    	}
    	else {
    		return 1;
    	}
	}
 
  return 1;
}

//Checks to see if file exists
int FileExists(string fileName)
{
    struct stat fileStat; 
    if( stat(fileName.c_str(), &fileStat) == 0) {
    	if(fileStat.st_mode & S_IFREG) {
    		return 0;
    	}
    	else {
    		return 1;
    	}
	}
    return 1;
}
//adds space before and after delimiters
string userPromptParsing(string userPrompt)
{
	for (unsigned i = 0; i < userPrompt.size(); ++i)
		{
			if ((userPrompt.at(i) == ';')) 
			{
				if (userPrompt.at(i-1) != ' ')
				{
					userPrompt.insert(i, " ");
				}
				else if (userPrompt.at(i+1) != ' ')
				{
					userPrompt.insert(i+1, " ");
				}
			}
			if (userPrompt.at(i) == '|' && userPrompt.at(i+1) == '|') 
			{
				if (userPrompt.at(i-1) != ' ')
				{
					userPrompt.insert(i, " ");
				}
				else if (userPrompt.at(i+2) != ' ')
				{
					userPrompt.insert(i+2, " ");
				}
			}
			if (userPrompt.at(i) == '&' && userPrompt.at(i+1) == '&') 
			{
				if (userPrompt.at(i-1) != ' ')
				{
					userPrompt.insert(i, " ");
				}
				else if (userPrompt.at(i+2) != ' ')
				{
					userPrompt.insert(i+2, " ");
				}
			}
		}
	return userPrompt;
}

//removes brackets and adds test replacing '['
string bracketParse(string prompt)
{
	prompt.insert(0,"test",4);
	prompt.erase(prompt.find("["), 1);
	prompt.erase(prompt.find("]"), 1);
	return prompt;
}

//for commands with <, >
void singleRedirect(string com)
{
	//splits command
	//cout << "singleRedirect" << endl;
	
	int fds[2];
	int defout;
	int fd = 0;
	vector<string> parts;
	split(parts, com, is_any_of(" "));
	
	//cat stuff
	if (parts.at(0) == "cat")
	{
		for (unsigned i = 0; i < parts.size(); ++i)
		{
			if(parts.at(i) == "<")
			{
				parts.erase(parts.begin()+i);
			}
		}
	}
	else
	{
		defout = dup(1);
	}
	if(pipe(fds) == -1) {
    	 perror("pipe:");
	}
	
    //the last element is the file so gave open the last element
    //gave it create, read, write and truncate permissions
    if(parts.at(0) != "cat")
    {
		fd = open((char*)parts.at(parts.size() - 1).c_str(), O_CREAT | O_RDWR | O_TRUNC , S_IRWXU);
		dup2(fd, 1); // redirect output to the file
    }
	
	//checks to make sure fd is not 2 which is stderror
	
	if (fd != 2)
	{
		
		if (parts.size() == 2)
		{
			execute2(parts.at(0) + " " + parts.at(1));
		}
		else if (parts.size() == 3) //if 3 parts use execute one
		{
			exec1(0, 1,parts.at(0));
			close(1);
		}
		//if 4 parts use execute two
		else if(parts.size() == 4)
		{
			//combine parts with a space
			exec2(0, 1, parts.at(0) + " " +  parts.at(1));
			close(1);
		}
		else if(parts.size() == 5)
		{
			//combine parts with a space
			exec3(0, 1, parts.at(0) + " " + parts.at(1) + " " + parts.at(2));
			close(1);
		}
		else if(parts.size() == 6)
		{
			//combine parts with a space
			exec4(0, 1, parts.at(0) + " " + parts.at(1) + " " + parts.at(2) + " " + parts.at(3));
			close(1);
		}
	}
	if(parts.at(0) != "cat")
	{
		dup2(defout, 1); // redirect output back to stdout
		close(fd);
		close(defout);
		close(fds[1]);
		wait(NULL); // wait until child finishes
	}
}


void doubleRedirect(string com)
{
	//splits command
	cout << "doubleRedirect" << endl;
	vector<string> parts;
	split(parts, com, is_any_of(" "));
	
	
	int fds[2];
	int fd = 0;
    int defout = dup(1);
    
  
	if(pipe(fds) == -1) {
    	 perror("pipe:");
	}
    
    //the last element is the file so gave open the last element
    //gave it create, read, write and append permissions
	fd = open((char*)parts.at(parts.size() - 1).c_str(), O_CREAT | O_RDWR | O_APPEND , S_IRWXU);
	
	dup2(fd, 1); // redirect output to the file
	if (fd != 2)
	{
		//if 3 parts use execute 1
		if (parts.size() == 3)
		{
			execute1(parts.at(0));
			close(1);
		}
		//if 4 parts use execute 2
		else if(parts.size() == 4)
		{
			//combine first parts with a space
			exec2(0, 1, parts.at(0) + " " +  parts.at(1));
			close(1);
		}
		else if(parts.size() == 5)
		{
			exec3(0, 1, parts.at(0) + " " + parts.at(1) + " " + parts.at(2));
			close(1);
		}
	}
	dup2(defout, 1); // redirect output back to stdout
	close(fd);
	close(defout);
	close(fds[1]);
	wait(NULL); 	// wait until child finishes
}

void exec4(int in, int out, string com)
{
	vector<string> parts;
	split(parts, com, is_any_of(" "));
	
	for(unsigned i = 0; i < parts.size(); i++)
	{
		if(parts.at(i).find("(") != string::npos)
		{
			parts.at(i).erase(parts.at(i).find("("), 1);
		}
	}
	
	int fds[2];

	if(pipe(fds) == -1) {
    	 perror("pipe:");
	}
	
	char* args[5];
	args[0] = (char*)parts.at(0).c_str();
	args[1] = (char*)parts.at(1).c_str();
	args[2] = (char*)parts.at(2).c_str();
	args[3] = (char*)parts.at(3).c_str();
	args[4] = NULL;

	pid_t pid = fork();    //Creating child process
   
    if(pid == -1) {                            
        perror("fork error:");                        
    }
    else if (pid == 0) 
    {
        if(dup2(in,0) == -1) 
        {
            perror("dup2 error:");
        }
        if(dup2(out,1) == -1) 
        {
            perror("dup2 error:");
        }
		if(execvp(args[0], args) == -1) {
            perror("execvp error:");
            exit(1);
        }
    }
    else if(pid > 0) {                          //Otherwise continue to the parent process
      int status;
      if(waitpid(pid,&status,0) == -1) {       //pause the parent process
          perror("wait");
      }
      if(WEXITSTATUS(status) != 0) {
          cout << "false" << endl;
      }
    }

    
    return;
}

void exec3(int in, int out, string com)
{
	vector<string> parts;
	split(parts, com, is_any_of(" "));
	
	for(unsigned i = 0; i < parts.size(); i++)
	{
		if(parts.at(i).find("(") != string::npos)
		{
			parts.at(i).erase(parts.at(i).find("("), 1);
		}
	}
	
	int fds[2];

	if(pipe(fds) == -1) {
    	 perror("pipe:");
    	 //return false;
	}
	
	char* args[4];
	args[0] = (char*)parts.at(0).c_str();
	args[1] = (char*)parts.at(1).c_str();
	args[2] = (char*)parts.at(2).c_str();
	args[3] = NULL;

	pid_t pid = fork();    //Creating child process
   
    if(pid == -1) {                            
        perror("fork error:");                        
    }
    else if (pid == 0) 
    {
        if(dup2(in,0) == -1) 
        {
            perror("dup2 error:");
        }
        if(dup2(out,1) == -1) 
        {
            perror("dup2 error:");
        }
		if(execvp(args[0], args) == -1) {
            perror("execvp error:");
            exit(1);
        }
    }
    else if(pid > 0) {                          //Otherwise continue to the parent process
      int status;
      if(waitpid(pid,&status,0) == -1) {       //pause the parent process
          perror("wait");
      }
      if(WEXITSTATUS(status) != 0) {
          cout << "false" << endl;
      }
    }

    
    return;
}


void exec2(int in, int out, string com)
{
	vector<string> parts;
	split(parts, com, is_any_of(" "));
	
	for(unsigned i = 0; i < parts.size(); i++)
	{
		if(parts.at(i).find("(") != string::npos)
		{
			parts.at(i).erase(parts.at(i).find("("), 1);
		}
	}
	
	int fds[2];

	if(pipe(fds) == -1) {
    	 perror("pipe:");
    	 //return false;
	}
	
	char* args[3];
	args[0] = (char*)parts.at(0).c_str();
	args[1] = (char*)parts.at(1).c_str();
	args[2] = NULL;

	pid_t pid = fork();    //Creating child process
   
    if(pid == -1) {                            
        perror("fork error:");                        
    }
    else if (pid == 0) 
    {
        if(dup2(in,0) == -1) 
        {
            perror("dup2 error:");
        }
        if(dup2(out,1) == -1) 
        {
            perror("dup2 error:");
        }
		if(execvp(args[0], args) == -1) {
            perror("execvp error:");
            exit(1);
        }
    }
    else if(pid > 0) {                          //Otherwise continue to the parent process
      int status;
      if(waitpid(pid,&status,0) == -1) {       //pause the parent process
          perror("wait");
      }
      if(WEXITSTATUS(status) != 0) {
          ////ret = false;
          cout << "false" << endl;
      }
    }

    
    return;
}


void exec1(int in, int out, string command)
{
	if(command == "exit")
	{
		exit(1);	
	}
	else
	{
		vector<string> parts;
		split(parts, command, is_any_of(" "));
		
		for(unsigned i = 0; i < parts.size(); i++)
		{
			if(parts.at(i).find("(") != string::npos)
			{
				parts.at(i).erase(parts.at(i).find("("), 1);
			}
		}
	
	
		char* args[2];
		args[0] = (char*)parts.at(0).c_str();
		args[1] = NULL;
		
		pid_t pid = fork();    //Creating child process
		
		if(pid == -1) {                            
		    perror("fork error:");                        
		}
		else if (pid == 0) 
		{
		    if(dup2(in,0) == -1) 
		    {
		        perror("dup2 error:");
		    }
		    if(dup2(out,1) == -1) 
		    {
		        perror("dup2 error:");
		    }
			if(execvp(args[0], args) == -1) {
		        perror("execvp error:");
		        exit(1);
		    }
		}
		else if(pid > 0) {                          //Otherwise continue to the parent process
		  int status;
		  if(waitpid(pid,&status,0) == -1) {       //pause the parent process
		      perror("wait");
		  }
		  if(WEXITSTATUS(status) != 0) {
		      cout << "false" << endl;
		  }
		}
	}

    
    return;
}