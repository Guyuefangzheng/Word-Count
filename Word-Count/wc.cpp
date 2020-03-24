#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>


int CharCount(char *file){	//字符数统计 
	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(fp==NULL){
		printf("没有找到此文件！\n");
		exit(-1);
	}
	
	int Ccount = 0;
	char temp;
	while(!feof(fp)){	//文件结束判断 
		temp = fgetc(fp);
		if(temp!=' '&&temp!='\n'&&temp!='\t'&&temp!=EOF)
			Ccount++;
	} 
	fclose(fp);
	return Ccount; 
}


int WordCount(char *file){	//词数统计 
	if(CharCount(file)==0)
		return 0;
		
	int Wcount = 0;
	bool b = 0;	//用来标记是否是字符 
	char temp;
	FILE *fp = NULL;
	fp = fopen(file,"r");
	while(!feof(fp)){
		temp = fgetc(fp);
		if(temp==' '||temp=='\t'||temp=='\n'||temp==EOF){	//四种情况，包括文件结束 
			if(b==1){	 //前面是字符，词数+1 
				Wcount++;
				b = 0;
			}
		} 
		else
			b = 1;	//如果是字符，b标记为1 
	}
	fclose(fp);
	return Wcount;
}



int LineCount(char *file){	//行数统计 
	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(fp==NULL){
		printf("没有找到此文件！\n");
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




int SearchFile(){	//处理目录下符合条件的文件
    struct _finddata_t fileinfo;	//文件存储信息结构体 
    long fHandle;	//保存文件句柄
    int t=0;	//文件数记录器
    fHandle = _findfirst("*.txt",&fileinfo);	//查找当前目录下的txt文件
	 
    if(fHandle==-1L)
    	printf( "当前目录下没有txt文件\n");
    else
    	do{
    		t++; 
    		printf("找到文件：%s\n",fileinfo.name);
    		printf("字符数为：%d\n",CharCount(fileinfo.name));
    		printf("词数为：%d\n",WordCount(fileinfo.name));
    		printf("行数为：%d\n\n",LineCount(fileinfo.name));
		}while(_findnext(fHandle,&fileinfo)==0);
		_findclose(fHandle);	//关闭文件链接
		return t; 
} 


int MoreLine(char *file){	//返回更复杂的数据（代码行 / 空行 / 注释行）
	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(fp==NULL){
		printf("没有找到此文件！\n");
		exit(-1);
	}
	
	int nNum = 0,cNum = 0,aNum = 0;
	bool b = 0;	// 
	int c;
	char temp;
	while(!feof(fp)){
		temp = fgetc(fp);
		if(temp=='\n'||temp==EOF){	//换行或者文件结束 
		//在换行或者文件结束时判断出类型 
			if(c==0)	//空行 
				nNum++;
			else if(c==1){	//代码行 
				cNum++;
				c = 0;
			}
			else{	//注释行 
				aNum++;
				c = 0;
			}
		}
		else if(temp!=' '&&temp!='\t'&&temp!='{'&&temp!='}'){
			//判断出代码行和注释行，剩下的即是空行 
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
	printf("空行数为：%d\n",nNum);
	printf("代码行数为：%d\n",cNum);
	printf("注释行数为：%d\n",aNum);
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
		printf("请输入正确的指令！\n");
		exit(1);
	}
	finish_t = clock();
		Total_time = (double)(finish_t - start_t) / CLOCKS_PER_SEC;//将时间转换为秒
		printf("%f seconds\n",Total_time);
}
