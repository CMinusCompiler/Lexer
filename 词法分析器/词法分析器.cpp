#include<iostream>
#include<string>
using namespace std;
#define ELSE 3
#define IF 4
#define INT 5
#define RETURN 6
#define VOID 7
#define WHILE 8
#define N 6
#define FILENAME "a.cpp"
char ch;
string code;
int ptr=0;
string strToken;
string reserveList[N]={"else","if","int","return","void","while"};//�����ֱ�
FILE* fp;
int index;
int value;
bool loadFile(char* fileName);
void GetChar();
void GetBC();
void Concat();
bool IsLetter();
bool IsDigit();
int Reserve();
void Retract();
string InsertId();
string InsertConst();
void detectOneWord();
bool deleteNote();//ȥ��ע��
int main()
{
	if(!loadFile(FILENAME))
    {
        cout<<"Error in loading."<<endl;
        return 0;
    }
	if(!deleteNote())
	{
		cout<<"Error in deletint note."<<endl;
        return 0;
	}
	cout<<code<<endl;
	while(ptr<code.length())
		  detectOneWord();
   
}
bool loadFile(char* fileName)
{
    FILE* fp;
    char c;
    fp=fopen(FILENAME,"r");
    if(!fp)
        return false;
    while((c=fgetc(fp))!=EOF)
    {
        code.push_back(c);
    }
    return true;
}
void GetChar()
{
	if(code.at(ptr)=='\0')
	{
		printf("Error in GetChar(): ptr pointing at the end");
	}
	ch=code.at(ptr);
	ptr++;
	
}
void GetBC()
{
    while(ch=='\n'||ch=='\t'||ch==' ')
	if(ptr<code.length ())
        GetChar();
	else
		break;

}
void Concat()
{
    strToken.push_back(ch);
}
bool IsLetter()
{
    return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}
bool IsDigit()
{
    return ch>='0'&&ch<='9';
}
int Reserve()
{//��strToken�е��ַ������ұ����ֱ������Ǳ������򷵻��ֱ���룬���򷵻�0��
	for(int i=0;i<N;i++)
	{
		if(strToken.compare(reserveList[i])==0)
		  return i+3;
	}
	return 0;
}
void Retract()
{//������ָʾ���ص�һ���ַ�λ�ã���ch��Ϊ�հ���
	if(ptr>0)
		ptr--;
	else
		cout<<"ERROR:�ѻص�����ʼλ�ã��޷������ص���"<<endl;
	ch=NULL;
}
string InsertId()
{//��strToken�б�ʶ��������ű����ط��ű�ָ��
	cout<<strToken<<endl;
	return "null";
}
string InsertConst()
{//��strToken�г������볣�������س�����ָ��
	cout<<strToken<<endl;
	return "null";
}
void detectOneWord()
{
	strToken.clear();
	 GetChar();
    GetBC();
    if(IsLetter())
    {
        while(IsLetter())
        {
            Concat();
            GetChar();
        }
        Retract();
        index=Reserve();
        if(index==0)
        {
            //value=InsertId();
			//cout<<"#ID,"<<value;
			InsertId();
            cout<<"#ID,"<<strToken<<endl;
        }
        else
            cout<<index<<",-"<<endl;
    }
    else if(IsDigit())
    {
        while(IsDigit())
        {
            Concat();
            GetChar();
        }
        Retract();
        //value=InsertConst();
		//cout<<"#NUM,"<<value;
		InsertConst();
        cout<<"#NUM,"<<strToken<<endl;
    }
	else if(ch=='+') cout<<"#PLUS,-"<<endl;
	else if(ch=='-') cout<<"#MINUS,-"<<endl;
	else if(ch=='*') cout<<"#MULI,-"<<endl;
	else if(ch=='/') cout<<"#DIV,-"<<endl;
	else if(ch=='<')//<=
		{
			GetChar();
			if(ch=='=') cout<<"#LETHAN,-"<<endl;
			else Retract();cout<<"#LTHAN,-"<<endl;
		}
	else if(ch=='>')//>=
		{
			GetChar();
			if(ch=='=') cout<<"#GETHAN,-"<<endl;
			else Retract();cout<<"#GTHAN,-"<<endl;
		}
	else if(ch=='=')//==
		{
			GetChar();
			if(ch=='=') cout<<"#EQUAL,-"<<endl;
			else Retract();cout<<"#ASSIGN,-"<<endl;
		}
	else if(ch=='!')
		{
			GetChar();
			if(ch=='=') cout<<"#NEQUAL,-"<<endl;
			else cout<<"ERROR:!"<<endl;
		}
	else if(ch==';') cout<<"#SEMICOLON,-"<<endl;
	else if(ch==',') cout<<"#COMMA,-"<<endl;
	else if(ch=='(') cout<<"#LBRACKET,-"<<endl;
	else if(ch==')') cout<<"#RBRACKET,-"<<endl;
	else if(ch=='[') cout<<"#LSRACKET,-"<<endl;
	else if(ch==']') cout<<"#RSRACKET,-"<<endl;
	else if(ch=='{') cout<<"#CLRACKET,-"<<endl;
	else if(ch=='}') cout<<"#CRRACKET,-"<<endl;
	else if(ch==' ') ;//ĩβ�ո�Ĵ�������
	else cout<<"error"<<endl;
}
bool deleteNote()
{//ȥ��ע�ͣ���Ϊ�ո�
    while(1)
    {
        size_t pos1=code.find("/*");
        if(pos1==string::npos)
		   if(code.find("*/")==string::npos)
                return true;
		   else 
			   return false;
		else
			code.replace (pos1,2,"  ");//��ֹ/*/   ����
        size_t pos2=code.find("*/");
        if(pos2==string::npos)
            return false;
        else
            code.replace(pos1,pos2-pos1+2," ");
		
    }
}


