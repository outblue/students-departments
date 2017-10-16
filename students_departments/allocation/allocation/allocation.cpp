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

const int Numstu = 5000;
const int Numdep = 100;


struct Applylist
{
	string ID;
	double csm;
};

struct Departments
{
	string depID;
	int need;
	vector<string> dep_tag;
	vector<string> dep_time;
	
	vector<string> ID_list;
	vector<double> csm_list;
	Applylist list[Numstu];
	
	int num_mem;
	
	vector<string> apply; 
}depart[Numdep];

struct Students
{
	string stuID;
	double gpa;
	vector<string> stu_tag;
	vector<string> stu_aspi;

	int num_aspi; 
	
	vector<string> dep_join;
	
}stu[Numstu];

//��ѧ��ID�Ͷ�Ӧ���ۺ����ִ���ò��Ŷ�Ӧ��list��
void depart_list(Departments dep[])
{
	int i;
	for(i = 0; i < Numdep; i++)
	{
		int a = 0;
		int b = 0;
		for (vector<double>::iterator it1 = dep[i].csm_list.begin(); it1 != dep[i].csm_list.end(); ++it1)    
    	{
    		dep[i].list[a].csm = *it1;
    		a++;
    	}
    	
    	for (vector<string>::iterator it2 = dep[i].ID_list.begin(); it2 != dep[i].ID_list.end(); ++it2)    
    	{
    		dep[i].list[b].ID = *it2;
    		b++;
    	}
	}
} 


//ͨ�����ű�Ż�ȡ�����±� 
int get_department(string str)
{
	for(int i = 0; i < Numdep; i++)
	{
		if(str == depart[i].depID) return i;
	}
}

//ͨ��ѧ����Ż�ȡѧ���±�
int get_student(string str)
{
	for(int i = 0; i < Numstu; i++)
	{
		if(str == stu[i].stuID) return i;
	}
}

//����ѧ����������־Ը������Խ��÷�Խ�� 
int point_num_aspi(Students stu)
{
	int n, point;
	n = stu.stu_aspi.size();
	point = 6-n;

	return point;
}

//����ѧ��tag�벿��tag�غϵ����������ڸ���ĵ÷� 
int point_num_tag(Students stu,Departments dep)
{
	int n=0;
	
	for (vector<string>::iterator it_s = stu.stu_tag.begin(); it_s != stu.stu_tag.end(); ++it_s)    
    {
    	for (vector<string>::iterator it_d = dep.dep_tag.begin(); it_d != dep.dep_tag.end(); ++it_d)    
    	{
         	if(*it_s == *it_d) n++;
		}
	}
	
	return n*5;
}

//����ѧ��־Ը�����Ĳ���֮��ʱ���غϵ����� 
int stu_dep_time(Students stu,Departments dep)
{
	int n = 0;
	int k;
	
	for (vector<string>::iterator it_s = stu.stu_aspi.begin(); it_s != stu.stu_aspi.end(); ++it_s)    
    {
    	if(dep.depID == *it_s) continue;
    	else
    	{
    		k = get_department(*it_s);
    		
    		for (vector<string>::iterator it_d1 = dep.dep_time.begin(); it_d1 != dep.dep_time.end(); ++it_d1)    
    		{
    			for (vector<string>::iterator it_d2 = depart[k].dep_time.begin(); it_d2 != depart[k].dep_time.end(); ++it_d2)    
    			{
         			if(*it_d1 == *it_d2) n++;
				}
			}
    	}
	}
    
    return n * (-3);
}

//����ѧ�������������Ĳ��ŵ��ۺϵ÷� 
void calculate(Students stu)
{
	int i = 0; 
	for (vector<string>::iterator it_s = stu.stu_aspi.begin(); it_s != stu.stu_aspi.end(); ++it_s)      
    {
    	double sum = 0;
    	int k;
		k = get_department(*it_s);
		
		sum += stu.gpa * 0.18;    // ����Ȩ��Ϊ0.18 
		sum += point_num_aspi(stu) * 0.25;		//־ԸȨ��Ϊ0.25 
	
		sum += point_num_tag(stu ,depart[k]) * 0.32;		//�غϵ�tag���÷�Ȩ��Ϊ0.32 
		
		sum += stu_dep_time(stu ,depart[k]) * (-3) * 0.25;		//�غϵĲ��Żʱ��÷�Ȩ��Ϊ0.25 
		
		depart[k].csm_list.push_back(sum);
		depart[k].ID_list.push_back(stu.stuID);
		depart[k].num_mem += 1;
	}		

}

//�ò��ű����嵥����
Departments list_rank(Departments dep)
{
	int i,j;
	Applylist app;
	for(i = 0; i < dep.num_mem-1 ; i++)
	{
		for(j = 0; j < dep.num_mem-1-i; j++)
		{
			if(dep.list[j].csm < dep.list[j+1].csm)
			{
				app = dep.list[j];
				dep.list[j] = dep.list[j+1];
				dep.list[j+1] = app;
			}
		}
	}

	return dep;
} 

//������¼ȡѧ������,ѧ��������Ĳ��� 
Departments get_member(Departments dep)
{
	int k = dep.need;
	for(int i = 0; i < k ; i++)
	{
		dep.apply.push_back(dep.list[i].ID);
		int l = get_student(dep.list[i].ID);
		stu[l].dep_join.push_back(dep.depID);
		stu[l].num_aspi += 1;
	}

	return dep;
}


int main()
{
	int i,j;
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int num4 = 0;
	
	
	ifstream in;
	in.open("s5000-d100-in.json");

	string line;
	string content;
	while(getline(in,line))
	{
		content += line;
	}

//��ȡ�ļ��е�����
	cJSON* json = cJSON_Parse(content.c_str()); 

//��ȡ��������
	cJSON* departments=cJSON_GetObjectItem(json,"departments");

	cJSON* department_no;
	cJSON* member_limit;
	cJSON* tags;
	cJSON* event_schedules;

	char* no;
	char* limit;

	for(j = 0;j < Numdep; j++)
	{
		cJSON* tdep = NULL;
		tdep = cJSON_GetArrayItem(departments, j);
		department_no = cJSON_GetObjectItem(tdep,"department_no");
		member_limit = cJSON_GetObjectItem(tdep,"member_limit");

		tags = cJSON_GetObjectItem(tdep,"tags");
		int size1 = cJSON_GetArraySize(tags);
		cJSON* ttag = NULL;
		for(i=0;i<size1;i++)
		{
			ttag = cJSON_GetArrayItem(tags,i);
			depart[j].dep_tag.push_back(ttag->valuestring);

	    }

		event_schedules= cJSON_GetObjectItem(tdep,"event_schedules");
		int size2 = cJSON_GetArraySize(event_schedules);
		cJSON* tevent = NULL;
		for(i=0;i<size2;i++)
		{
			tevent = cJSON_GetArrayItem(event_schedules,i);
			depart[j].dep_tag.push_back(tevent->valuestring);

	    }

		no = cJSON_Print(department_no);
		depart[j].depID = no;
		limit = cJSON_Print(member_limit);
		int li = stoi(limit);
		depart[j].need = li;

		free(no);
		free(limit);

	}


//��ȡѧ������
	cJSON* students=cJSON_GetObjectItem(json,"students");
	
	cJSON* student_no;
	cJSON* student_gpa;
	cJSON* student_tags;
	cJSON* student_aspirations;

	char* sno;
	char* sgpa;

	for(j = 0;j < Numstu; j++)
	{
		cJSON* tstu = NULL;
		tstu = cJSON_GetArrayItem(students, j);
		student_no = cJSON_GetObjectItem(tstu,"student_no");
		student_gpa = cJSON_GetObjectItem(tstu,"student_gpa");

		student_tags = cJSON_GetObjectItem(tstu,"tags");
		int size3 = cJSON_GetArraySize(student_tags);
		cJSON* ttags = NULL;
		for(i = 0; i < size3; i++)
		{
			ttags = cJSON_GetArrayItem(student_tags,i);
			stu[j].stu_tag.push_back(ttags->valuestring);

	    }

		student_aspirations= cJSON_GetObjectItem(tstu,"student_aspirations");
		int size5 = cJSON_GetArraySize(student_aspirations);
		cJSON* taspi = NULL;
		for(i=0;i<size5;i++)
		{
			taspi = cJSON_GetArrayItem(student_aspirations,i);

			char* saspi;
			saspi = cJSON_Print(taspi);
			stu[j].stu_aspi.push_back(saspi);

			free(saspi);

	    }

		sno = cJSON_Print(student_no);
		stu[j].stuID = sno;
		sgpa = cJSON_Print(student_gpa);
		double sg = stod(sgpa);
		stu[j].gpa = sg;

		free(sno);
		free(sgpa);

	}

	//ȥ��ѧ�����ǰ�󸽴��ġ�"��
	for(i = 0; i < Numstu; i++)
	{
		string s1,s2,s3;
		s1 = stu[i].stuID; 
		s2 = s1.erase(0,1);
		s3 = s2.erase(5,1);
		stu[i].stuID = s3;

	}


//���з���
	for(i = 0; i < Numstu; i++)
	{
		calculate(stu[i]);		//Ϊ��ѧ�������ۺϷ���
	}

	//ȥ�����ű��ǰ�󸽴��ġ�"��
		for(i = 0; i < Numdep; i++)
	{
		string s1,s2,s3;
		s1 = depart[i].depID; 
		s2 = s1.erase(0,1);
		s3 = s2.erase(5,1);
		depart[i].depID = s3;

	}

	depart_list(depart);		//�Ѹ����ŵ��嵥¼��

	for(i = 0; i < Numdep; i++)
	{
		Departments D = list_rank(depart[i]);		//�������ŵ��嵥�ɸߵ����Ų�
		D = get_member(D);		//���ݸò����������������³�Ա�嵥��ѧ��������Ĳ������� 
		depart[i] = D;	
	
	}

	

//���������
	 //�ȴ����ն���
    cJSON *jsonout = cJSON_CreateObject();

//������ų�Ա
    //�������
    cJSON *array = NULL;
    cJSON_AddItemToObject(jsonout,"matched_department_view",array=cJSON_CreateArray());
    //����������Ӷ���

	cJSON *objout = NULL;
//	cJSON_AddItemToArray(array,obj=cJSON_CreateObject());
	for(i=0;i<Numdep;i++)
	{
		if((depart[i].need != 0) && (depart[i].num_mem != 0) )
		{
			cJSON_AddItemToArray(array,objout=cJSON_CreateObject());
			const char *k = depart[i].depID.c_str();
			cJSON_AddItemToObject(objout,"department_no",cJSON_CreateString(k));	//�������ID
			//�������������Ա
			cJSON *array = NULL;
			cJSON_AddItemToObject(objout,"members",array=cJSON_CreateArray());
			for (vector<string>::iterator it1 = depart[i].apply.begin(); it1 != depart[i].apply.end(); ++it1)    
			{
				string temp1 = *it1;
				const char *a = temp1.c_str();
				cJSON_AddItemToArray(array,cJSON_CreateString(a));
			}
			
			num3++;
		}
		
	}
//���ѧ�����벿��
	cJSON_AddItemToObject(jsonout,"matched_student_view",array=cJSON_CreateArray());
    //����������Ӷ���

	cJSON *objout1 = NULL;
	for(i=0;i<Numstu;i++)
	{
		if(stu[i].num_aspi != 0)
		{
			cJSON_AddItemToArray(array,objout1=cJSON_CreateObject());
			const char *n = stu[i].stuID.c_str();
			cJSON_AddItemToObject(objout1,"student_no",cJSON_CreateString(n));	//���ѧ��ID
			//���ѧ�������벿��
			cJSON *array = NULL;
			cJSON_AddItemToObject(objout1,"department_join",array=cJSON_CreateArray());
			for (vector<string>::iterator it2 = stu[i].dep_join.begin(); it2 != stu[i].dep_join.end(); ++it2)    
			{
				string temp2 = *it2;
				const char *b = temp2.c_str();
				cJSON_AddItemToArray(array,cJSON_CreateString(b));
			}

			num1++;
		}

	}

//���δ���յ�ѧ���Ĳ���
    cJSON_AddItemToObject(jsonout,"standalone_departments",array=cJSON_CreateArray());

	for(i = 0; i < Numdep; i++)
	{
		if((depart[i].need == 0) || (depart[i].num_mem == 0) )
		{
			string temp3 = depart[i].depID;
			const char *c = temp3.c_str();
			cJSON_AddItemToArray(array,cJSON_CreateString(c));
			
			num4++;
		}
	}

//���δ���κβ���¼ȡ��ѧ��
	cJSON_AddItemToObject(jsonout,"standalone_students",array=cJSON_CreateArray());

	for(i = 0; i < Numstu; i++)
	{
		if(stu[i].num_aspi == 0)
		{
			string temp4 = stu[i].stuID;
			const char *d = temp4.c_str();
			cJSON_AddItemToArray(array,cJSON_CreateString(d));

			num2++;
		}
	}


	//������
    FILE *fp_out = fopen("s5000-d100-out.json","w");
    char *buf_out = cJSON_Print(jsonout);
    fwrite(buf_out,strlen(buf_out),1,fp_out);
    fclose(fp_out);
    cJSON_Delete(jsonout);

	cout << num1 << " " << num2 << endl;
	cout << num3 << " " << num4 << endl;

	system("pause");
	return 0;
}
