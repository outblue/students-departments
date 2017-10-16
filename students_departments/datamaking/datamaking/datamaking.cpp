#include<iostream>
#include<stdio.h>
#include<string>
#include<set>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<sstream>
#include<fstream>
#include"cJSON.h"

using namespace std;

const int Numstu=5000;
const int Numdep=100;


class Depatrments
{
	public:
	string depID;
	int need;
	set<string> dep_tag;
	set<string> dep_time;

}depart[Numdep];

class Students
{
	public:
	string stuID;
	double gpa;
	set<string> stu_tag;
	set<string> aspi;
	
}stu[Numstu];

string change_tag(int n)
{
	string str;

	switch(n)
	{
		case 0:str="study";break;
		case 1:str="read";break;
		case 2:str="exercise";break;
		case 3:str="relax";break;
		case 4:str="science";break;
		case 5:str="art";break;
		case 6:str="music";break;
		case 7:str="history";break;
		case 8:str="interact";break;
		case 9:str="write";break;
		default:break;
	}

	return str;
}

string change_actime(int n)
{
	string str;

	switch(n)
	{
		case 0:str="Monday-evening";break;
		case 1:str="Tuesday-evening";break;
		case 2:str="Wednesday-evening";break;
		case 3:str="Thursday-evening";break;
		case 4:str="Firday-evenday";break;
		case 5:str="Saturday-morning";break;
		case 6:str="Saturday-afternoon";break;
		case 7:str="Saturday-evening";break;
		case 8:str="Sunday-morning";break;
		case 9:str="Sunday-afternoon";break;
		case 10:str="Sunday-evening";break;
		default:break;
	}

	return str;
}



int main(void)
{
	srand((unsigned)time(NULL));
	int i,j;

//部门信息随机取值

	string depart_name[Numdep];  //保存已有的部门名称

	//部门编号随机取值
	 for(i=0;i<Numdep;i++)
	{
		depart[i].depID="D";

		if(i<10)
		{
			stringstream stream;
			depart[i].depID += "000";
			string s;
			stream << i;
			stream >> s;
			depart[i].depID += s;
		}
		else if(i<100)
		{
			stringstream stream;
			depart[i].depID += "00";
			string s;
			stream << i;
			stream >> s;
			depart[i].depID += s;
		}
		else if(i<1000)
		{
			stringstream stream;
			depart[i].depID += "0";
			string s;
			stream << i;
			stream >> s;
			depart[i].depID += s;
		}
		else
		{
			stringstream stream;
			string s;
			stream << i;
			stream >> s;
			depart[i].depID += s;
		}
		depart_name[i] = depart[i].depID;
	}

	 //部门所需人数随机取值
	for(i=0;i<Numdep;i++)
	{
		int p=rand()%15;
		depart[i].need=p;
	//		cout << depart[i].need << endl; 
	}

	//部门tag随机取值
	for(i=0;i<Numdep;i++)
	{
		int p=rand()%5+1;
		for(j=0;j<p;j++)
		{
			int q=rand()%10;
			string temp;
			temp = change_tag(q); 
			depart[i].dep_tag.insert(temp);
		}
	}

	//部门活动时间随机取值
	for(i=0;i<Numdep;i++)
	{
		int p=rand()%3+1;
		for(j=0;j<p;j++)
		{
			int q=rand()%9;
			string temp;
			temp = change_actime(q);
			depart[i].dep_time.insert(temp);
		}
	}  

//输出部门信息
    		
    //先创建空对象
    cJSON *json = cJSON_CreateObject();

    //添加数组
    cJSON *array = NULL;
    cJSON_AddItemToObject(json,"departments",array=cJSON_CreateArray());
    //在数组上添加对象

	cJSON *obj = NULL;
	for(i=0;i<Numdep;i++)
	{
		cJSON_AddItemToArray(array,obj=cJSON_CreateObject());

		const char *k = depart[i].depID.c_str();
		cJSON_AddItemToObject(obj,"department_no",cJSON_CreateString(k));	//输出部门ID
		cJSON_AddNumberToObject(obj,"member_limit",depart[i].need);		//输出部门招收人数
		//输出部门tag
		cJSON *array = NULL;
		cJSON_AddItemToObject(obj,"tags",array=cJSON_CreateArray());
		for (set<string>::iterator it1 = depart[i].dep_tag.begin(); it1 != depart[i].dep_tag.end(); ++it1)    
		{
			string temp1 = *it1;
			const char *l = temp1.c_str();
			cJSON_AddItemToArray(array,cJSON_CreateString(l));
		}
		//输出部门活动时间
		cJSON_AddItemToObject(obj,"event_schedules",array=cJSON_CreateArray());
		for (set<string>::iterator it2 = depart[i].dep_time.begin(); it2 != depart[i].dep_time.end(); ++it2)    
		{
			string temp2 = *it2;
			const char *m = temp2.c_str();
			cJSON_AddItemToArray(array,cJSON_CreateString(m));
		}

	}

//学生信息随机取值
	
	//学生编号取值 
	for(i=0;i < Numstu;i++)
	{
		stu[i].stuID="S";

		if(i<10)
		{
			stringstream stream;
			stu[i].stuID += "000";
			string s;
			stream << i;
			stream >> s;
			stu[i].stuID += s;
		}
		else if(i<100)
		{
			stringstream stream;
			stu[i].stuID += "00";
			string s;
			stream << i;
			stream >> s;
			stu[i].stuID += s;
		}
		else if(i<1000)
		{
			stringstream stream;
			stu[i].stuID += "0";
			string s;
			stream << i;
			stream >> s;
			stu[i].stuID += s;
		}
		else
		{
			stringstream stream;
			string s;
			stream << i;
			stream >> s;
			stu[i].stuID += s;
		}
	}

	//学生绩点随机取值	
	for(i=0;i<Numstu;i++)
	{
		stu[i].gpa=rand()%500/100.0;
	}
	
	//	cout << stu[2].gpa << endl;

	//学生tag随机取值
	for(i=0;i<Numstu;i++)
	{
		int p=rand()%5+1;
		for(j=0;j<p;j++)
		{
			int q=rand()%9;
			string temp;
			temp = change_tag(q);
			stu[i].stu_tag.insert(temp);
		}
	} 

	//学生志愿随机填写
	for(i=0;i<Numstu;i++)
	{
		int p=rand()%5+1;
		for(j=0;j<p;j++)
		{
			int q=rand()%Numdep;
			stu[i].aspi.insert(depart_name[q]);
		}
	}

//输出学生信息

    //添加数组
    cJSON_AddItemToObject(json,"students",array=cJSON_CreateArray());
    //在数组上添加对象

	cJSON *obj1 = NULL;
	for(i=0;i<Numstu;i++)
	{
		cJSON_AddItemToArray(array,obj1=cJSON_CreateObject());

		const char *n = stu[i].stuID.c_str();
		cJSON_AddItemToObject(obj1,"student_no",cJSON_CreateString(n));	//输出部门ID
		cJSON_AddNumberToObject(obj1,"student_gpa",stu[i].gpa);		//输出部门招收人数
		//输出部门tag
		cJSON *array = NULL;
		cJSON_AddItemToObject(obj1,"tags",array=cJSON_CreateArray());
		for (set<string>::iterator it3 = stu[i].stu_tag.begin(); it3 != stu[i].stu_tag.end(); ++it3)    
		{
			string temp3 = *it3;
			const char *o = temp3.c_str();
			cJSON_AddItemToArray(array,cJSON_CreateString(o));
		}
		//输出部门活动时间
		cJSON_AddItemToObject(obj1,"student_aspirations",array=cJSON_CreateArray());
		for (set<string>::iterator it4 = stu[i].aspi.begin(); it4 != stu[i].aspi.end(); ++it4)    
		{
			string temp4 = *it4;
			const char *r = temp4.c_str();
			cJSON_AddItemToArray(array,cJSON_CreateString(r));
		}

	}
    
    //清理工作
    FILE *fp = fopen("C:\\Users\\lenovo\\Desktop\\students_departments\\allocation\\allocation\\s5000-d100-in.json","w+");
    char *buf = cJSON_Print(json);
    fwrite(buf,strlen(buf),1,fp);
    fclose(fp);
    cJSON_Delete(json);
    return 0;
}

