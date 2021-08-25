#include<iostream>
#include<cmath>
#include<string.h>
#include<stdio.h>
using namespace std;
class Stack
{
    char symbols[300];
    float number[300];
    int top; int top2;
    public:
        Stack(){top=-1; top2=-1;}
        void push(char c){symbols[++top]=c;}
        void pop(){top--;}
        void pushNum(float x){number[++top2]=x;}
        void popNum(){top2--;}
        int returnNumberOfElements(){return (top+1);}
        char returnTopElement(){return symbols[top];}
        float returnTopNum(){return number[top2];}
        float returnSecondNum(){return number[(top2-1)];}
};
class bracket
{
    char s[200];
    int top;
    public:
        bracket(){top=-1;}
        void push(char c){ s[++top]=c;}
        void pop(){top--;}
        char returnTopCharacter(){return s[top];}
        int checkForEmptyStack()
        {
            if(top==-1)
                return 1;
            else
                return 0;
        }
};
int checkForPrecedence(char encounter, char topOfStack)  /* returning 1 means encountered operator has higher precedence
                                                           than operator currently on top of stack*/
                                                           /// returning 2 means operator precedence is equal,0 means lesser
{
    int valueToReturn;
    switch(encounter)
    {
        case '^':{
            if(topOfStack=='^')
                valueToReturn=2;
            else
                valueToReturn=1;
            break;
            }
        case '+':
            {
                if(topOfStack=='+'||topOfStack=='-')
                    valueToReturn=2;
                else
                    valueToReturn=0;
                 break;
            }
       case '-':
            {
                if(topOfStack=='+'||topOfStack=='-')
                    valueToReturn=2;
                else
                    valueToReturn=0;
                 break;
            }
       case '*':
           {
               if(topOfStack=='+' || topOfStack=='-')
                    valueToReturn=1;
               else
               if(topOfStack=='*'||topOfStack=='/')
                    valueToReturn=2;
               else
                    valueToReturn=0;
                break;
           }
      case '/':
           {
               if(topOfStack=='+' || topOfStack=='-')
                    valueToReturn=1;
               else
               if(topOfStack=='*'||topOfStack=='/')
                    valueToReturn=2;
               else
                    valueToReturn=0;
                break;
           }
    }
    return valueToReturn;
}
void convertAndEvaluate(char s[])
{
    char postfix[300]={'\0'}; int c=0;
    Stack obj;
    int length=strlen(s);
    for(int x=0;x<length;x++)
    {
        if(isdigit(s[x]))
            postfix[c++]=s[x];
        if(s[x]=='.')
            postfix[c++]=s[x];
        if(s[x]=='+'||s[x]=='-'||s[x]=='*'||s[x]=='/'||s[x]=='^')
        {
            postfix[c++]=' ';
            if(obj.returnNumberOfElements()==0 || checkForPrecedence(s[x],obj.returnTopElement())==1
               || obj.returnTopElement()=='(')
                obj.push(s[x]);
            else
            {
                while(checkForPrecedence(s[x],obj.returnTopElement())==0 || checkForPrecedence(s[x],obj.returnTopElement())==2)
                {
                    postfix[c++]=obj.returnTopElement();
                    postfix[c++]=' ';
                    obj.pop();
                    if(obj.returnNumberOfElements()==0 || obj.returnTopElement()=='(')
                        break;
                }
                obj.push(s[x]);
            }
        }
        if(s[x]=='(')
            obj.push(s[x]);
        if(s[x]==')')
        {
            postfix[c++]=' ';
            while(obj.returnTopElement()!='(')
            {
              postfix[c++]=obj.returnTopElement();
              obj.pop();
            }
           obj.pop();
        }
    }
    postfix[c++]=' ';
    while(obj.returnNumberOfElements()!=0)
    {
        postfix[c++]=obj.returnTopElement();
        postfix[c++]=' ';
        obj.pop();
    }
    for(int x=0;x<c;)
    {
        if(isdigit(postfix[x]))
        {
            int checkForDecimal=0,checkIndex=x;
            while(postfix[checkIndex]!=' ')
            {
                checkIndex++;
                if(postfix[checkIndex]=='.')
                {
                    checkForDecimal++;
                    break;
                }
            }
            if(checkForDecimal==1)
            {
                int index=x,numberOfDigits=0,numberOfDigitsAfterDecimal=0;
                while(postfix[index]!='.')
                {
                    numberOfDigits++; index++;
                }
                double answer=0; int value=numberOfDigits-1;
                for(int var=x;var<index;var++)
                {
                    answer+=(postfix[var]-48)*pow(10,value);
                    value--;
                }
                int decimal=index+1;
                while(postfix[index]!=' ')
                {
                    numberOfDigitsAfterDecimal++; index++;
                }
                int bunty=numberOfDigitsAfterDecimal-1;
                for(int var2=index-1;var2>=decimal;var2--)
                {
                    answer+=(postfix[var2]-48)*pow(10,-bunty);
                    bunty--;
                }
                obj.pushNum(answer);
                x=index+1;
            }
            else
            {
                int index=x,numberOfDigits=0;
                while(postfix[index]!=' ')
                {
                    numberOfDigits++; index++;
                }
                double answer=0; int value=numberOfDigits-1;
                for(int var=x;var<index;var++)
                {
                    answer+=(postfix[var]-48)*pow(10,value);
                    value--;
                }
                obj.pushNum(answer);
                x=index+1;
            }
        }
        else
        {
            switch(postfix[x])
            {
                case '+':
                {
                    double answer=obj.returnTopNum()+obj.returnSecondNum();
                    obj.popNum(); obj.popNum();
                    obj.pushNum(answer); x+=2;
                    break;
                }
                case '-':
                {
                    double answer=-obj.returnTopNum()+obj.returnSecondNum();
                    obj.popNum(); obj.popNum();
                    obj.pushNum(answer); x+=2;
                    break;
                }
                case '*':
                {
                    double answer=obj.returnTopNum()*obj.returnSecondNum();
                    obj.popNum(); obj.popNum();
                    obj.pushNum(answer); x+=2;
                    break;
                }
                case '/':
                {
                    double answer=obj.returnSecondNum()/obj.returnTopNum();
                    obj.popNum(); obj.popNum();
                    obj.pushNum(answer); x+=2;
                    break;
                }
                case '^':
                {
                    double answer=pow(obj.returnSecondNum(),obj.returnTopNum());
                    obj.popNum(); obj.popNum();
                    obj.pushNum(answer); x+=2;
                    break;
                }
            }
        }
    }
    cout<<obj.returnTopNum();
}
int main()
{
    char infix[200]; bracket obj;
    cout<<"Input the infix expression?"; gets(infix);
    int length=strlen(infix); int check=0;
    for(int x=0;x<length;x++)
    {
        if(infix[0]==')')
        {
            check++; goto a;
        }

        if(infix[x]=='(')
            obj.push(infix[x]);
        if(infix[x]==')')
        {
            if(obj.checkForEmptyStack()==1
            || obj.returnTopCharacter()!='('&& infix[x]==')')
            {
                check++; goto a;
            }
            else
                obj.pop();
        }
    }
    if(obj.checkForEmptyStack()!=1)
        check++;
    a:
     if(check==1)
        cout<<"Invalid input. Clear expression and input again\n";
     else
        convertAndEvaluate(infix);  /// SAMPLE INPUT 12.21*71221^2-212.9212/218-(23^3.32)+88.21/2121-10^5.43
    return 0;
}


