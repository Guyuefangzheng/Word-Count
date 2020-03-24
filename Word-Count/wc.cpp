#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>


int CharCount(char *file){	//�ַ���ͳ�� 
	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(fp==NULL){
		printf("û���ҵ����ļ���\n");
		exit(-1);
	}
	
	int Ccount = 0;
	char temp;
	while(!feof(fp)){	//�ļ������ж� 
		temp = fgetc(fp);
		if(temp!=' '&&temp!='\n'&&temp!='\t'&&temp!=EOF)
			Ccount++;
	} 
	fclose(fp);
	return Ccount; 
}


int WordCount(char *file){	//����ͳ�� 
	if(CharCount(file)==0)
		return 0;
		
	int Wcount = 0;
	bool b = 0;	//��������Ƿ����ַ� 
	char temp;
	FILE *fp = NULL;
	fp = fopen(file,"r");
	while(!feof(fp)){
		temp = fgetc(fp);
		if(temp==' '||temp=='\t'||temp=='\n'||temp==EOF){	//��������������ļ����� 
			if(b==1){	 //ǰ�����ַ�������+1 
				Wcount++;
				b = 0;
			}
		} 
		else
			b = 1;	//������ַ���b���Ϊ1 
	}
	fclose(fp);
	return Wcount;
}



int LineCount(char *file){	//����ͳ�� 
	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(fp==NULL){
		printf("û���ҵ����ļ���\n");
		exit(-1);
	}
	
	int Lcount = 1;
	char temp;
	while(!feof(fp)){
		temp = fgetc(fp);
		if(temp=='\n')
			Lcount++;
	}
	fclose(fp);
	return Lcount;
} 




int SearchFile(){	//����Ŀ¼�·����������ļ�
    struct _finddata_t fileinfo;	//�ļ��洢��Ϣ�ṹ�� 
    long fHandle;	//�����ļ����
    int t=0;	//�ļ�����¼��
    fHandle = _findfirst("*.txt",&fileinfo);	//���ҵ�ǰĿ¼�µ�txt�ļ�
	 
    if(fHandle==-1L)
    	printf( "��ǰĿ¼��û��txt�ļ�\n");
    else
    	do{
    		t++; 
    		printf("�ҵ��ļ���%s\n",fileinfo.name);
    		printf("�ַ���Ϊ��%d\n",CharCount(fileinfo.name));
    		printf("����Ϊ��%d\n",WordCount(fileinfo.name));
    		printf("����Ϊ��%d\n\n",LineCount(fileinfo.name));
		}while(_findnext(fHandle,&fileinfo)==0);
		_findclose(fHandle);	//�ر��ļ�����
		return t; 
} 


int MoreLine(char *file){	//���ظ����ӵ����ݣ������� / ���� / ע���У�
	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(fp==NULL){
		printf("û���ҵ����ļ���\n");
		exit(-1);
	}
	
	int nNum = 0,cNum = 0,aNum = 0;
	bool b = 0;	// 
	int c;
	char temp;
	while(!feof(fp)){
		temp = fgetc(fp);
		if(temp=='\n'||temp==EOF){	//���л����ļ����� 
		//�ڻ��л����ļ�����ʱ�жϳ����� 
			if(c==0)	//���� 
				nNum++;
			else if(c==1){	//������ 
				cNum++;
				c = 0;
			}
			else{	//ע���� 
				aNum++;
				c = 0;
			}
		}
		else if(temp!=' '&&temp!='\t'&&temp!='{'&&temp!='}'){
			//�жϳ������к�ע���У�ʣ�µļ��ǿ��� 
			if(temp=='/'){
				if(c==0&&b==0)
					b = 1;
				else if(c==0&&b==1){
					c = 2;
					b = 0;
				}
			} 
			else if(c!=2)
				c = 1;	 
		}
	}
	fclose(fp);
	printf("������Ϊ��%d\n",nNum);
	printf("��������Ϊ��%d\n",cNum);
	printf("ע������Ϊ��%d\n",aNum);
	return nNum+cNum+aNum;
}



int main(int argc,char *argv[]){
	clock_t start_t,finish_t;
	double Total_time;
	start_t = clock();
	if(!strcmp(argv[1],"-c"))
		printf("charnumber: %d\n",CharCount(argv[2]));
	else if(!strcmp(argv[1],"-w"))
		printf("wordnumber: %d\n",WordCount(argv[2]));
	else if(!strcmp(argv[1],"-l"))
		printf("linenumber: %d\n",LineCount(argv[2]));
	else if(!strcmp(argv[1],"-s"))
		printf("find txt number: %d\n",SearchFile());
	else if(!strcmp(argv[1],"-a"))
		MoreLine(argv[2]);
	else{ 
		printf("��������ȷ��ָ�\n");
		exit(1);
	}
	finish_t = clock();
		Total_time = (double)(finish_t - start_t) / CLOCKS_PER_SEC;//��ʱ��ת��Ϊ��
		printf("%f seconds\n",Total_time);
}
