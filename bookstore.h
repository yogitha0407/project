#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//STUDENT ENTITY
struct student{
	char id[15];
	char password[10];
	char name[20];
	char branch[5];
	int year;
	struct student *lc;
	struct student *rc;
	struct student *link;
};
struct student *first=NULL,*curr,*t1,*t2;
//GLOBAL VARIABLES
char smn[10];
char suid[10];
//BOOK ENTITY
struct book{
	char name[25];
	char author[25];
	float price;
	int uid;
	char sid[15];
	char sname[20];
	char sbranch[5];
	struct book *l1;
	struct book *p1;
};
struct book *head=NULL,*btfirst=NULL,*temp,*t3,*t4,*t5;

//FUNCTIONS PROTOTYPE
int bstsearch(struct student *root,char user[10]);
int signup();
int signin();
struct book *create();
int check();
int sell();
int pupdate();
int bupdate();
int deletb();
int deleta();
int hcreate(int ,int );
int namesearch(int );
int uidsearch(int ,int );
int authorsearch(int );
int pricesearch(int a[],int,int);
int hash(char br[]);
int bhbooks();
int allbooks();
int buy();
int shistory();
int bhistory();
int yhistory();

//LOGIN MODULE
//BINARY SRARCH TREE FOR LOGIN MODULE
int bstsearch(struct student *root,char user[10])
{
	t2=root;
	while(1)
	{
	    if(strcmp(t2->id,user)>0)
        {
		    t2=t2->lc;
		}
		else if(strcmp(t2->id,user)<0)
		{
		    t2=t2->rc;
		}
		else
			return 0;
		if(t2==NULL)
			return 1;
	}	      
}
//SIGN UP (NEW USER)
int signup()
{
	struct student s3,*root=NULL;
	FILE *fp;
	fp=fopen("studentlogin.txt","a+");
	if(fp==NULL)
	{
		printf("Cant open file\n");
		return 0;
	}
	while(fscanf(fp,"%d,%[^,],%[^,],%[^,],%s\n",&s3.year,s3.id,s3.password,s3.name,s3.branch)!=EOF)
	{
		curr=(struct student *)malloc(sizeof(struct student));
		curr->year=s3.year;
		strcpy(curr->id,s3.id);
		strcpy(curr->password,s3.password);
		strcpy(curr->name,s3.name);
		strcpy(curr->branch,s3.branch);
		curr->rc=NULL;
		curr->lc=NULL;
		if(root==NULL)
			root=curr;
		else
		{
			t1=root;
			while(1)
		    {
		        if(strcmp(t1->id,curr->id)>0)
		        {
		            if(t1->lc == NULL)
		            {
		                t1->lc=curr;
		                break;
		            }
		            else
		                t1=t1->lc;
		        }
		        else
		        {
		            if(t1->rc == NULL)
		            {
		                t1->rc=curr;
		                break;
		            }
		            else
		                t1=t1->rc;
		        }
		    }
		}
	}
	struct student s;
	int b=0;
	printf("ENTER YOUR USERID(MOBILE NUMBER):");
	fflush(stdin);
	while(1)
	{
		scanf("%s",s.id);
		if(strlen(s.id)==10)
		{
			if(root==NULL)
				break;
			else
			{
				b=bstsearch(root,s.id);
				if(b==1)
				{
					break;
				}
				else
					printf("\n\tUSERID ALREADY EXIST.\nPLEASE TRY AGAIN:");
			}
		}
		else
			printf("USERID(MOBILE NUMBER) MUST BE OF 10 DIGITS.\nPLEASE TRY AGAIN:");
	}
	printf("ENTER YOUR PASSWORD:");
	fflush(stdin);
	scanf("%s",s.password);
	printf("ENTER YOUR NAME:");
	fflush(stdin);
	scanf("%[^\n]s",s.name);
	printf("ENTER YOUR BRANCH:");
	fflush(stdin);
	scanf("%s",s.branch);
	printf("ENTER YOUR YEAR:");
	fflush(stdin);
	scanf("%d",&s.year);
	fprintf(fp,"%d,%s,%s,%s,%s\n",s.year,s.id,s.password,s.name,s.branch);
	fclose(fp);
	return 1;
}
//SIGN IN (EXISTING USER)
int signin(){
	struct student s2,s3;
	int flag=0,count=3,c=0,t=0;	
	FILE *fp;
	char ch;
	printf("ENTER USERID:");
	fflush(stdin);
	while(1)
	{
		scanf("%s",s2.id);
		fp=fopen("studentlogin.txt","r");
		while(fscanf(fp,"%d,%[^,],%[^,],%[^,],%s\n",&s3.year,s3.id,s3.password,s3.name,s3.branch) !=EOF)
		{
			if(strlen(s2.id)!=10)
			{
				printf("USERNAME MUST BE OF 10 DIGITS.\nPLEASE TRY AGAIN:");
				t=1;
				break;
			}
			if(strcmp(s3.id,s2.id)==0)
			{
				printf("ENTER PASSWORD:");
				fflush(stdin);
				while(count>=0){
					scanf("%s",s2.password);
					if(strcmp(s2.password,s3.password)==0)
					{
						printf("\t\tLOGIN SUCCESS!!\n");
						strcpy(suid,s3.id);
						flag=1;
						break;
					}
					else{
						printf("INCORRECT CREDENTIALS.\nPLEASE ENTER AGAIN(%d ATTEMPTS LEFT):",count);
						count--;
					}
				}
				if(count<0)
				{
					printf("YOU HAVE EXCEEDED YOUR LIMIT.\n");
					exit(0);
				}	
			}
		}
		if(flag==1)
			break;
		if(t!=1)
		{
			printf("USERNAME NOT FOUND.\n");
			c=1;
			break;
		}
	}
	if(c==1){
		printf("PLEASE CREATE NEW ACCOUNT.\n");
	}
	fclose(fp);
	if(flag==1)	
		return 1;
	else 
		return 0;
}

//SELL MODULE
//CRETION OF NODE FOR SELL MODULE
struct book *create()
{
	struct student s;
	char m[10];
	int flag=0;
	FILE *fp;
	t5=(struct book*)malloc(sizeof(struct book));
	printf("ENTER BOOK NAME:");
	fflush(stdin);
	scanf("%[^\n]s",t5->name);
	fflush(stdin);
	printf("ENTER AUTHOR NAME:");
	scanf("%[^\n]s",t5->author);
	fflush(stdin);
	printf("ENTER PRICE OF THE BOOK:");
	scanf("%f",&t5->price);
	fflush(stdin);
	printf("STUDENT DETAILS:\n");	
	fp=fopen("studentlogin.txt","r");
	if(fp==NULL)
	{
		printf("NO DATA AVAILABLE");
	}
	else
	{
		printf("ENTER USERID FOR CONFIRMATION:");
		fflush(stdin);
		while(1)
		{
			scanf("%s",m);
			if(strcmp(m,suid)==0)
				break;
			else
				printf("\nUserId not match.\nPlease try again:");
		}
		while(fscanf(fp,"%d,%[^,],%[^,],%[^,],%s",&s.year,s.id,s.password,s.name,s.branch)!=EOF)
		{
			if(strcmp(s.id,m)==0)
			{
				strcpy(t5->sbranch,s.branch);
				strcpy(t5->sname,s.name);
				strcpy(t5->sid,s.id);
				printf("NAME:");
				puts(s.name);
				printf("BRANCH:%s\nYEAR:%d\nMOBILE NO:%s\n",s.branch,s.year,s.id);
				strcpy(smn,s.id);
				flag=0;
				break;
			}
			else
			{
				flag=1;
			}
		}
		fclose(fp);
	}
	if(flag==1)
		return NULL;
	else
		return t5;
}
//AUTOMATIC GENERATION OF UNIQUR ID FOR BOOKS SOLD
int check()
{
	int x=0;
	struct book b,b1;
	FILE *fp,*fp1;
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch)!=EOF)
	{
		x=b.uid;
	}
	fclose(fp);
	fp1=fopen("SELL_HISTORY.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b1.uid,b1.name,b1.author,&b1.price,b1.sname,b1.sid,b1.sbranch)!=EOF)
	{
		if(x<b1.uid)
			x=b1.uid;
	}
	return x+1;
}
//APPENDING BOOKS TO FILE
int sell()
{
	char c;
	struct student s;
	int flag;
	FILE *fp,*fp1;
	printf("DO YOU WANT TO SELL THE BOOK(Y/N):");
	fflush(stdin);
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
		t4=create();
		if(t4==NULL)
		{
			return 0;
		}
		fp=fopen("SELL_BOOKS.txt","a+");
		fp1=fopen("studentlogin.txt","r");
		t4->uid=check();
		while(fscanf(fp1,"%d,%[^,],%[^,],%[^,],%s\n",&s.year,s.id,s.password,s.name,s.branch) != EOF)
		{
			if(strcmp(s.id,smn)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
			fprintf(fp,"%d %s,%s,%f,%s,%s,%s\n",t4->uid,t4->name,t4->author,t4->price,t4->sname,t4->sid,t4->sbranch);
		fclose(fp1);
		fclose(fp);
	}
	else
		return 0;
	if(flag==1)
		return 1;
	else 
		return 0;
}

//UPDATE MODULE
//UPDATION OF PERSONAL DETAILS
int pupdate()
{
	char num[10];
	struct student s;
	int s1,s2=0;
	FILE *fp;
	fp=fopen("studentlogin.txt","r");
	while(fscanf(fp,"%d,%[^,],%[^,],%[^,],%s\n",&s.year,s.id,s.password,s.name,s.branch) != EOF)
	{
		if(first==NULL){
			curr=(struct student *)malloc(sizeof(struct student));
			strcpy(curr->id,s.id);
			strcpy(curr->password,s.password);
			strcpy(curr->name,s.name);
			strcpy(curr->branch,s.branch);
			curr->year=s.year;
			curr->link=NULL;
			first=curr;
		}
		else
		{
			curr=(struct student *)malloc(sizeof(struct student));
			t1=first;
			while(t1->link!=NULL)
			{
				t1=t1->link;
			}
			strcpy(curr->id,s.id);
			strcpy(curr->password,s.password);
			strcpy(curr->name,s.name);
			strcpy(curr->branch,s.branch);
			curr->year=s.year;
			curr->link=NULL;
			t1->link=curr;
		}
	}
	fclose(fp);
	printf("\nPLEASE ENTER YOUR USERID FOR CONFIRMATION:");
	scanf("%s",num);
	if(strcmp(suid,num)==0)
	{
		t1=first;
		while(t1!=NULL)
		{
			if(strcmp(t1->id,num)==0)
				break;
			t1=t1->link;
		}
		printf("\n\t\tUSERID AND BRANCH CAN'T BE UPDATED.\n");
		while(1)
		{
			printf("1.UPDATE NAME\n2.UPDATE PASSWORD\n3.UPDATE YEAR\n4.BACK TO MAIN MENU\nENTER YOUR CHOICE:"); 
			scanf("%d",&s1);
			switch(s1){
				case 1:
					printf("ENTER NEW NAME:");
					fflush(stdin);
					scanf("%[^\n]s",t1->name);
					s2=1;
					break;
				case 2:
					printf("ENTER NEW PASSWORD:");
					fflush(stdin);
					scanf("%s",t1->password);
					s2=1;
					break;
				case 3:
					printf("UPDATE YEAR:");
					fflush(stdin);
					scanf("%d",&t1->year);
					s2=1;
					break;
				case 4:
					if(s1==4)
						break;
				default:
					printf("INVALID INPUT.\n");
			}
			if(s1==4||s2==1)
				break;
		}
		FILE *fp1;
		fp1=fopen("studentlogin.txt","w");
		t2=first;
		while(t2!=NULL)
		{
			fprintf(fp1,"%d,%s,%s,%s,%s\n",t2->year,t2->id,t2->password,t2->name,t2->branch);
			t2=t2->link;
		}
		fclose(fp1);
		first->link=NULL;
		free(first);
		first=NULL;
		return 1;
	}
	else
	{
		printf("THE USERID DOESN'T MATCH.\n");
		first->link=NULL;
		free(first);
		first=NULL;
		return 0;	
	}
}
//UPDATION OF BOOK DETAILS
int bupdate()
{
	char num[10];
	int arr[50];
	int u,d=0;
	struct book b;
	int s1,s2=0,i=0;
	FILE *fp;
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) != EOF)
	{
		if(head==NULL){
			temp=(struct book *)malloc(sizeof(struct book));
			temp->uid=b.uid;
			strcpy(temp->name,b.name);
			strcpy(temp->author,b.author);
			temp->price=b.price;
			strcpy(temp->sid,b.sid);
			strcpy(temp->sname,b.sname);
			strcpy(temp->sbranch,b.sbranch);
			temp->l1=NULL;
			head=temp;
		}
		else
		{
			temp=(struct book*)malloc(sizeof(struct book));
			t3=head;
			while(t3->l1!=NULL)
			{
				t3=t3->l1;
			}
			temp->uid=b.uid;
			strcpy(temp->name,b.name);
			strcpy(temp->author,b.author);
			temp->price=b.price;
			strcpy(temp->sid,b.sid);
			strcpy(temp->sname,b.sname);
			strcpy(temp->sbranch,b.sbranch);
			temp->l1=NULL;
			t3->l1=temp;
		}
	}
	fclose(fp);
	printf("\nPLEASE ENTER YOUR MOBILE NUMBER:");
	scanf("%s",num);
	if(strcmp(suid,num)==0)
	{
		t3=head;
		while(t3!=NULL)
		{
			if(strcmp(t3->sid,num)==0)
			{
				printf("%d %s,%s,%f\n",t3->uid,t3->name,t3->author,t3->price);
				arr[i]=t3->uid;
				i++;
			}
			t3=t3->l1;
		}
		if(i==0)
		{
			head->l1=NULL;
			free(head);
			head=NULL;
			return 2;
		}
		printf("\n\tPLEASE SELECT THE BOOK UNIQUE ID FROM ABOVE SHOWN:");
		scanf("%d",&u);
		int j;
		for(j=0;j<i;j++)
		{
			if(arr[j]==u)
			{
				d=1;
			}
		}
		if(d==1)
		{
			printf("\n\t\tUSERID CAN'T BE UPDATED.\n");
			while(1)
			{
				t3=head;
				while(t3!=NULL)
				{
					if(t3->uid==u)
					{
						printf("\n\n\t\tBOOK DETAILS:\t%d %s,%s,%f\n",t3->uid,t3->name,t3->author,t3->price);
						break;
					}
					t3=t3->l1;
				}
				printf("1.UPDATE NAME OF THE BOOK\n2.UPDATE BOOK AUTHOR NAME\n3.UPDATE PRICE\n4.BACK TO MAIN MENU\nENTER YOUR CHOICE:"); 
				scanf("%d",&s1);
				switch(s1){
					case 1:
						printf("ENTER NAME OF THE BOOK:");
						fflush(stdin);
						scanf("%[^\n]s",t3->name);
						s2=1;
						break;
					case 2:
						printf("ENTER BOOK AUTHOR NAME:");
						fflush(stdin);
						scanf("%[^\n]s",t3->author);
						s2=1;
						break;
					case 3:
						printf("UPDATE PRICE:");
						fflush(stdin);
						scanf("%f",&t3->price);
						s2=1;
						break;
					case 4:
						if(s1==4)
							break;
					default:
						printf("INVALID INPUT.\n");
				}
				if(s1==4||s2==1)
					break;
			}
			FILE *fp1;
			fp1=fopen("SELL_BOOKS.txt","w");
			t3=head;
			while(t3!=NULL)
			{
				fprintf(fp1,"%d %s,%s,%f,%s,%s,%s\n",t3->uid,t3->name,t3->author,t3->price,t3->sname,t3->sid,t3->sbranch);
				t3=t3->l1;
			}
			fclose(fp1);
			head->l1=NULL;
			free(head);
			head=NULL;
			return 1;
		}
		else
		{
			printf("\n\t\tINVALID INPUT.\n");
			head->l1=NULL;
			free(head);
			head=NULL;
			return 0;
		}
	}
	else
	{
		printf("THE USERID DOESN'T MATCH.\n");
		head->l1=NULL;
		free(head);
		head=NULL;
		return 0;	
	}
}

//DELETE MODULE
//CREATION OF LINKED LIST
struct book *bfirst=NULL,*blast=NULL,*btemp,*bt1,*bt2,*bt3;
struct book *createll()
{
	struct book b;
	FILE *fp;
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) != EOF)
	{
		if(bfirst==NULL)
		{
			btemp=(struct book *)malloc(sizeof(struct book));
			strcpy(btemp->name,b.name);
			btemp->uid=b.uid;
			strcpy(btemp->author,b.author);
			btemp->price=b.price;
			strcpy(btemp->sid,b.sid);
			strcpy(btemp->sname,b.sname);
			strcpy(btemp->sbranch,b.sbranch);
			btemp->l1=NULL;
			bfirst=btemp;
		}
		else
		{
			btemp=(struct book *)malloc(sizeof(struct book));
			bt1=bfirst;
			while(bt1->l1!=NULL)
			{
				bt1=bt1->l1;
			}
			strcpy(btemp->name,b.name);
			btemp->uid=b.uid;
			strcpy(btemp->author,b.author);
			btemp->price=b.price;
			strcpy(btemp->sid,b.sid);
			strcpy(btemp->sname,b.sname);
			strcpy(btemp->sbranch,b.sbranch);
			btemp->l1=NULL;
			bt1->l1=btemp;
		}
	}
	fclose(fp);
	return bfirst;
}
//DELETE A BOOK IN THE PROFILE
int deletb()
{
	char db[10];
	int r,j=0,i=0;
	int arr[50];
	char c;
	printf("PLEASE ENTER YOUR USERID FOR CONFIRMATION:");
	scanf("%s",db);
	if(strcmp(suid,db)==0)
	{
		bt2=createll();
		while(bt2!=NULL)
		{
			if(strcmp(db,bt2->sid)==0)
			{
				printf("BOOK ID=%d\tBOOK NAME=%s\t\tBOOK AUTHOR=%s\tBOOK PRICE=%.2f\n",bt2->uid,bt2->name,bt2->author,bt2->price);
				arr[i]=bt2->uid;
				i++;
			}
			bt2=bt2->l1;
		}
		if(i==0)
			return 2;
		printf("\n\tPLEASE SELECT THE BOOK UNIQUE ID FROM ABOVE:");
		scanf("%d",&r);
		int k;
		for(j=0;j<i;j++)
		{
			if(arr[j]==r)
				k=1;
		}
		if(k==1)
		{
			bt2=bfirst;
			while(bt2!=NULL)
			{
				if(bt2->uid==r)
				{
					printf("\n\n\t\tBOOK DETAILS:\t%d %s,%s,%.2f\n",bt2->uid,bt2->name,bt2->author,bt2->price);
					break;
				}
				bt2=bt2->l1;
			}
			
			bt1=bfirst;
			btemp=bfirst;
			while(btemp!=NULL)
			{
				if(bt2->uid==btemp->uid)
				{
					if(bfirst->uid==btemp->uid)
					{
						bfirst=bfirst->l1;
					}
					bt1->l1=btemp->l1;
					btemp->l1=NULL;
					FILE *fp2;
					fp2=fopen("SELL_HISTORY.txt","a+");
					fprintf(fp2,"%d %s,%s,%f,%s,%s,%s\n",btemp->uid,btemp->name,btemp->author,btemp->price,btemp->sname,btemp->sid,btemp->sbranch);
					fclose(fp2);
					free(btemp);
					bt1=bt1->l1;
					break;
				}
				bt1=btemp;
				btemp=btemp->l1;
			}
			FILE *fp1;
			fp1=fopen("SELL_BOOKS.txt","w");
			bt2=bfirst;
			if(bfirst==NULL)
				bt2=NULL;
			while(bt2!=NULL)
			{
				fprintf(fp1,"%d %s,%s,%f,%s,%s,%s\n",bt2->uid,bt2->name,bt2->author,bt2->price,bt2->sname,bt2->sid,bt2->sbranch);
				bt2=bt2->l1;
			}
			fclose(fp1);
			bfirst->l1=NULL;
			if(bfirst!=NULL)
				free(bfirst);
			bfirst=NULL;
			return 1;
		}
	}
	else
	{
		printf("\n\t\tUSERID DOSEN'T MATCH!!\n");
		bfirst->l1=NULL;
		free(bfirst);
		bfirst=NULL;
		return 0;
	}
}

struct student *afirst=NULL,*atemp,*at1,*at2;
//DELETE STUDENT ACCOUNT
int deleta()
{
	struct student s;
	char da[10];
	char c;
	FILE *fp;
	fp=fopen("studentlogin.txt","r");
	while(fscanf(fp,"%d,%[^,],%[^,],%[^,],%s\n",&s.year,s.id,s.password,s.name,s.branch) != EOF)
	{
		if(afirst==NULL)
		{
			atemp=(struct student *)malloc(sizeof(struct student));
			strcpy(atemp->id,s.id);
			strcpy(atemp->password,s.password);
			strcpy(atemp->name,s.name);
			strcpy(atemp->branch,s.branch);
			atemp->year=s.year;
			atemp->link=NULL;
			afirst=atemp;;
		}
		else
		{
			atemp=(struct student *)malloc(sizeof(struct student));
			at1=afirst;
			while(at1->link!=NULL)
			{
				at1=at1->link;
			}
			strcpy(atemp->id,s.id);
			strcpy(atemp->password,s.password);
			strcpy(atemp->name,s.name);
			strcpy(atemp->branch,s.branch);
			atemp->year=s.year;
			atemp->link=NULL;
			at1->link=atemp;
		}
	}
	fclose(fp);
	printf("PLEASE ENTER YOUR USERID FOR CONFIRMATION:");
	scanf("%s",da);
	if(strcmp(suid,da)==0)
	{
		at2=afirst;
		while(at2!=NULL)
		{
			if(strcmp(da,at2->id)==0)
			{
				printf("NAME=%s\tUSERID=%s\n",at2->name,at2->id);
				printf("\n\t\tDO YOU WANT TO DELETE(Y/N):");
				fflush(stdin);
				scanf("%c",&c);
				if(c=='y'||c=='Y')
					break;
				else
				{
					afirst->link=NULL;
					free(afirst);
					afirst=NULL;
					return 2;
				}
			}
			at2=at2->link;
		}
		at1=afirst;
		atemp=afirst;
		while(atemp!=NULL)
		{
			if(strcmp(atemp->id,at2->id)==0)
			{
				if(strcmp(afirst->id,atemp->id)==0)
					afirst=afirst->link;
				at1->link=atemp->link;
				atemp->link=NULL;
				free(atemp);
				at1=at1->link;
				break;
			}
			at1=atemp;
			atemp=atemp->link;
		}
		FILE *fp1;
		fp1=fopen("studentlogin.txt","w");
		at2=afirst;
		while(at2!=NULL)
		{
			fprintf(fp1,"%d,%s,%s,%s,%s\n",at2->year,at2->id,at2->password,at2->name,at2->branch);
			at2=at2->link;
		}
		fclose(fp1);
		afirst->link=NULL;
		free(afirst);
		afirst=NULL;
		return 1;
	}
	else
	{
		printf("\n\t\tUSERID DOSEN'T MATCH!!\n");
		afirst->link=NULL;
		free(afirst);
		afirst=NULL;
		return 0;
	}
}

//BUY MODULE
struct book *arrptr[10];
struct book *ht;
//CREATION OF LINKED LIST IN BUY MODULE
int hcreate(int u,int j)
{
	struct book b;
	ht=(struct book *)malloc(sizeof(struct book));
	FILE *fp1;
	fp1=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp1,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch)!=EOF)
	{
		if(u==b.uid)
		{
			ht->uid=b.uid;
			ht->price=b.price;
			strcpy(ht->name,b.name);
			strcpy(ht->author,b.author);
			strcpy(ht->sname,b.sname);
			strcpy(ht->sid,b.sid);
			strcpy(ht->sbranch,b.sbranch);
			ht->l1=NULL;
			if(arrptr[j]==NULL)
				arrptr[j]=ht;
			else
			{
				t5=arrptr[j];
				while(t5->l1!=NULL)
					t5=t5->l1;
				t5->l1=ht;
			}
			break;
		}
	}
	fclose(fp1);
}
//SEARCHING
//SEARCH THE BOOK WITH UNIQUE ID PROVIDED BY STUDENT
int uidsearch(int u,int i)
{
	struct book b;
	struct student s;
	char c;
	FILE *fp,*fp1,*fp2,*fp3,*fp4;
	fp1=fopen("studentlogin.txt","r");
	while(fscanf(fp1,"%d,%[^,],%[^,],%[^,],%s",&s.year,s.id,s.password,s.name,s.branch) !=EOF )
	{
		if(strcmp(suid,s.id)==0)
			break;
	}
	fclose(fp1);
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) !=EOF )
	{
		if(b.uid==u)
		{
			printf("\nID=%d\tBOOK NAME=%s\nBOOK AUTHOR=%s\nBOOK PRICE=%.2f",b.uid,b.name,b.author,b.price);
			break;
		}
	}
	fclose(fp);
	fp3=fopen("SELL_HISTORY.txt","a+");
	fp4=fopen("BUY_BOOKS.txt","a+");
	printf("\nENTER YOUR STATUS(Y-BUY,N-NOT INTRESTED):");
	fflush(stdin);
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
		bt2=createll();
		bt3=bt2;
		while(bt3!=NULL)
		{
			if(bt3->uid==b.uid)
				break;
			bt2=bt3;
			bt3=bt3->l1;
		}
		bt2->l1=bt3->l1;
		if(bt2->uid==bfirst->uid)
			bfirst=bt2->l1;
		fprintf(fp3,"%d %s,%s,%f,%s,%s,%s\n",bt3->uid,bt3->name,bt3->author,bt3->price,bt3->sname,bt3->sid,bt3->sbranch);
		fprintf(fp4,"%d %s,%s,%f,%s,%s,%s\n",bt3->uid,bt3->name,bt3->author,bt3->price,s.name,s.id,s.branch);
		fclose(fp3);
		fclose(fp4);
		bt3->l1=NULL;
		free(bt3);
		fp2=fopen("SELL_BOOKS.txt","w+");
		bt2=bfirst;
		while(bt2!=NULL)
		{
			fprintf(fp2,"%d %s,%s,%f,%s,%s,%s\n",bt2->uid,bt2->name,bt2->author,bt2->price,bt2->sname,bt2->sid,bt2->sbranch);
			bt2=bt2->l1;
		}
		fclose(fp2);
		bfirst->l1=NULL;
		free(bfirst);
		bfirst=NULL;
		return 1;
	}
	else 
		return 0;
}
//SEARCH BY PRICE
int pricesearch(int a[],int j,int i)
{
	float l,h;
	char c;
	int k,u,ui,flag=0;
	printf("\n\t\tEnter the price range:\n");
	printf("Enter the lowest value:");
	scanf("%f",&l);
	printf("Enter the highest value:");
	scanf("%f",&h);
	printf("\n\t\t--------------------------------\n");
	if(i!=4)
		t4=arrptr[i];
	else
		t4=head;
	while(t4!=NULL)
	{
		for(k=0;k<j;k++)
		{	
			if(l<=t4->price&&t4->price<=h)
			{
				if(t4->uid==a[k])
				{
					printf("\nID=%d\tName of the book=",t4->uid);
					puts(t4->name);
					printf("Author of theBook=");
					puts(t4->author);
					printf("Price=%.2f",t4->price);
					printf("\n-------------------------------------------------------------\n");
					flag=1;
				}
			}
		}
		t4=t4->l1;
	}
	if(flag==0)
	{
		printf("\n\t\tNO BOOKS IN RANGE.\n\n");
		return 0;
	}
	printf("SELECT THE UNIQUE ID FROM ABOVE MENTIONED BOOKS:");
	int f1;
	while(1)
	{
		scanf("%d",&u);
		for(k=0;k<j;k++)
		{
			if(a[k]==u)
			{
					f1=1;
					break;
			}
		}
		if(f1==1)
			break;
		else
			printf("\nPLEASE SELECT A VALID UNIQUE ID:");
	}
	ui=uidsearch(u,i);
	if(ui==1)
		return 1;
	else return 0;
}
//SEARCH BY NAME
int namesearch(int i)
{
	int flag=0,f1,k,pr,au,u,j=0,m,a[100];
	char p,c,h,s;
	char b[50];
	if(i!=4)
	{
		t5=arrptr[i];
		while(t5!=NULL)
		{
			printf("\nID=%d\nBOOK NAME=",t5->uid);
			puts(t5->name);
			printf("AUTHOR OF THE BOOK=");
			puts(t5->author);
			printf("PRICE=%.2f",t5->price);
			printf("\n-------------------------------------------------------------\n");
			t5=t5->l1;
		}
	}
	printf("\n\nENTER BOOK NAME:");
	fflush(stdin);
	gets(b);
	printf("\n\t\tBOOKS:");
	if(i!=4)
		t4=arrptr[i];
	else
		t4=head;
	while(t4!=NULL)
	{
		strlwr(b);
		strlwr(t4->name);
		if(strcmp(t4->name,b)==0)
		{
			a[j]=t4->uid;
			j++;
			printf("\nID=%d\nBOOK NAME=",t4->uid);
			puts(t4->name);
			printf("AUTHOR OF THE BOOK=");
			puts(t4->author);
			printf("PRICE=%.2f",t4->price);
			printf("\n-------------------------------------------------------------\n");
			flag=1;
		}
		else if(strstr(t4->name,b))
		{
			a[j]=t4->uid;
			j++;
			printf("\nID=%d\nBook name=",t4->uid);
			puts(t4->name);
			printf("Author of theBook=");
			puts(t4->author);
			printf("Price=%.2f",t4->price);
			printf("\n-------------------------------------------------------------\n");
			flag=2;
		}
		t4=t4->l1;
	}
	if(flag==0)
		printf("\n\tBOOKS NOT FOUND\n");
	else
	{
		printf("\nDO YOU WANT TO BUY ANY BOOK(Y/N):");
		scanf("%c",&h);
		if(h=='y'||h=='Y')
		{
			printf("\nPLEASE SELECT THE VALID UNIQUE ID:");
			while(1)
			{
				scanf("%d",&k);
				for(m=0;m<j;m++)
				{
					if(a[m]==k)
					{
						f1=1;
						break;
					}
				}
				if(f1==1)
					break;
				else
					printf("\nPLEASE SELECT A VALID UNIQUE ID:");
			}
			u=uidsearch(k,i);
			if(u==1)
				return 1;
		}
		else
		{
			printf("DO you want to search by price range(Y/N):");
			fflush(stdin);
			scanf("%c",&p);
			if(p=='y'||p=='Y')
			{
				pr=pricesearch(a,j,i);
				if(pr==1)
					return 1;
			}
		}
		printf("DO YOU WANT TO SEARCH BY BOOK AUTHOR(Y/N):");
		fflush(stdin);
		scanf("%c",&c);
		if(c=='Y'||c=='y')
		{
			au=authorsearch(i);
			if(au==1)
				return 1;
		}
		else return 0;
	}
}
//SEARCH BY AUTHOR
int authorsearch(int i)
{
	int flag,k,u,n,pr,j=0,a[100];
	char p,c;
	char b[50];
	printf("\n\nENTER THE AUTHOR NAME:");
	fflush(stdin);
	gets(b);
	printf("\n\t\tBOOKS:");
	if(i!=4)
		t4=arrptr[i];
	else
		t4=head;
	while(t4!=NULL)
	{
		strlwr(b);
		strlwr(t4->author);
		if(strcmp(t4->author,b)==0)
		{
			a[j]=t4->uid;
			j++;
			printf("\nID=%d\nBook name=",t4->uid);
			puts(t4->name);
			printf("AUTHOR OF THE BOOK=");
			puts(t4->author);
			printf("PRICE=%.2f",t4->price);
			printf("\n-------------------------------------------------------------\n");
			flag=1;
		}
		else if(strstr(t4->author,b))
		{
			a[j]=t4->uid;
			j++;
			printf("\nID=%d\nBook name=",t4->uid);
			puts(t4->name);
			printf("Author of theBook=");
			puts(t4->author);
			printf("Price=%.2f",t4->price);
			printf("\n-------------------------------------------------------------\n");
			flag=2;
		}
		t4=t4->l1;
	}
	if(flag==0)
	{
		printf("\n\tBOOKS NOT FOUND\n");
		printf("DO YOU WANT TO SEARCH BY BOOK NAME(Y/N):");
		scanf("%c",&c);
		if(c=='Y'||c=='y')
		{
			n=namesearch(i);
			if(n==1)
				return 1;
		}
	}
	else 
	{
		printf("\nDO YOU WANT TO SEARCH BY PRICE RANGE(Y/N):");
		scanf("%c",&p);
		if(p=='y'||p=='Y')
		{
			pr=pricesearch(a,j,i);
			if(pr==1)
				return 1;
			else return 0;
		}
		else
		{
			printf("PLEASE SELECT THE VALID UNIQUE ID:");
			scanf("%d",&k);
			u=uidsearch(k,i);
			if(u==1)
				return 1;
			else return 0;
		}
	}
}
//SEARCH BOOKS BY BRANCH
int bhbooks()
{
	struct book b;
	int i,n,k;
	FILE *fp;
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch)!=EOF)
	{
		if(strcmp(suid,b.sid)!=0)
		{
			i=hash(b.sbranch);
			hcreate(b.uid,i);
		}
	}
	fclose(fp);
	int ch;
	while(1)
	{
		printf("\n1.ECE\n2.EIE\n3.CSE\n4.IT\n5.BACK TO MENU\nPLEASE ENTER YOUR CHOICE:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				i=0;
				break;
			case 2:
				i=1;
				break;
			case 3:
				i=2;
				break;
			case 4:
				i=3;
				break;
			case 5:
				i=4;
				break;
			default:
				printf("\nINVALID INPUT\n");
		}
		if(i<4)
			break;
		if(i==4)
			return 3;
	}
	n=namesearch(i);
	for(k=0;k<4;k++)
	{
		//arrptr[k]->l1=NULL;
		arrptr[k]=NULL;
	}
	if(n==1)
		return 1;
	else
		return 0;
}
//HASHING FUNTION FOR BRANCH SEARCHING
int hash(char br[5])
{
	strlwr(br);
	int i;
	if(strcmp(br,"ece")==0)
	{
		i=0;
		return i;
	}
	else if(strcmp(br,"eie")==0)
	{
		i=1;
		return i;
	}
	else if(strcmp(br,"cse")==0)
	{
		i=2;
		return i;
	}
	else if(strcmp(br,"it")==0)
	{
		i=3;
		return i;
	}
	else 
		return 4;
}
//CREATION OF LINKED LIST EXCLUDING USER BOOK DETAILS
struct book *createll2()
{
	struct book b;
	FILE *fp;
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) != EOF)
	{
		if(strcmp(suid,b.sid)!=0)
		{
			if(btfirst==NULL)
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				btemp->l1=NULL;
				btfirst=btemp;
			}
			else
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				bt1=btfirst;
				while(bt1->l1!=NULL)
				{
					bt1=bt1->l1;
				}
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				btemp->l1=NULL;
				bt1->l1=btemp;
			}
		}
	}
	fclose(fp);
	return btfirst;
}
//SEARCH BY ALL BOOKS AVAILABLE IN STORE
int allbooks()
{
	struct book *trav;
	FILE *fp;
	fp=fopen("SELL_BOOKS.txt","r");
	head=createll2();
	trav=head;
	while(trav!=NULL)
	{
		printf("\nID=%d\nBOOK NAME=",trav->uid);
		puts(trav->name);
		printf("AUTHOR OF THE BOOK=");
		puts(trav->author);
		printf("PRICE=%.2f",trav->price);
		printf("\n-------------------------------------------------------------\n");
		trav=trav->l1;
	}
	int n=4,na;
	na=namesearch(n);
	head=NULL;
	btfirst->l1=NULL;
	free(btfirst);
	btfirst=NULL;
	if(na==1)
		return 1;
	else return 0;
}
//BUY MENU
int buy()
{
	struct book b;
	int c,count,bh,ab;	
	while(1)
	{
		printf("\n\tSEARCH\n\t\t1.BY BRANCH\n\t\t2.ALL BOOKS\n\t\t3.BACK TO MAIN MENU\nENTER YOUR CHOICE:");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				bh=bhbooks();
				if(bh==1)
				{
					printf("\n\tBOOK BOUGHT SUCCESSFULLY\n");
					return 1;
				}
				break;
			case 2:
				ab=allbooks();
				if(ab==1)
				{
					printf("\n\tBOOK BOUGHT SUCCESSFULLY\n");
					return 1;
				}
				break;
			case 3:
				return 0;
			default:
				printf("\nINVALID INPUT\n");
		}
	}
}

//DISPLAY MODULE
//DISPLAY BOOKS WHICH ARE SOLD BY STUDENT
int shistory()
{
	struct book b,b1;
	FILE *fp,*fp1;
	fp=fopen("SELL_HISTORY.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) != EOF)
	{
		if(strcmp(suid,b.sid)==0)
		{	
			if(bfirst==NULL)
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				btemp->l1=NULL;
				btemp->p1=NULL;
				bfirst=btemp;
			}
			else
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				bt1=bfirst;
				while(bt1->l1!=NULL)
				{
					bt1=bt1->l1;
				}
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				bt1->l1=btemp;
				btemp->l1=NULL;
				btemp->p1=bt1;
				blast=btemp;
			}
		}
	}
	if(bfirst==NULL)
	{
		return 2;
	}
	int ch;
	printf("FILTER:\n1.OLDEST TO LATEST\n2.LATEST TO OLDEST\nENTER YOUR CHOICE:");
	scanf("%d",&ch);
	if(ch==1)
	{
		bt2=bfirst;
		printf("\n\tBOOKS:\n");
		while(bt2!=NULL)
		{
			printf("ID:%d\tNAME:%s\nAUTHOR:%s\nPRICE:%.2f\t\n",bt2->uid,bt2->name,bt2->author,bt2->price);
			printf("\n---------------------------------------------\n");
			bt2=bt2->l1;
		}
	}
	else if(ch==2)
	{
		bt2=blast;
		printf("\n\tBOOKS:\n");
		while(bt2!=NULL)
		{
			printf("ID:%d\tNAME:%s\nAUTHOR:%s\nPRICE:%.2f\t\n",bt2->uid,bt2->name,bt2->author,bt2->price);
			printf("\n---------------------------------------------\n");
			bt2=bt2->p1;
		}
	}
	bfirst->l1=NULL;
	bfirst->p1=NULL;
	free(bfirst);
	bfirst=NULL;
	return 1;
}
//DISPLAY BOOKS WHICH ARE BOUGHT BY STUDENT
int bhistory()
{
	struct book b,b1;
	int ch;
	FILE *fp,*fp1;
	fp=fopen("BUY_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) != EOF)
	{
		if(strcmp(suid,b.sid)==0)
		{	
			if(bfirst==NULL)
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				btemp->l1=NULL;
				btemp->p1=NULL;
				bfirst=btemp;
			}
			else
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				bt1=bfirst;
				while(bt1->l1!=NULL)
				{
					bt1=bt1->l1;
				}
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				bt1->l1=btemp;
				btemp->l1=NULL;
				btemp->p1=bt1;
				blast=btemp;
			}
		}
	}
	if(bfirst==NULL)
	{
		return 2;
	}
	fp1=fopen("SELL_HISTORY.txt","r");
	printf("FILTER:\n1.OLDEST TO LATEST\n2.LATEST TO OLDEST\nENTER YOUR CHOICE:");
	scanf("%d",&ch);
	printf("\n\tBOOKS:\n");
	if(ch==1)
	{
		bt2=bfirst;
		while(bt2!=NULL)
		{
			while(fscanf(fp1,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b1.uid,b1.name,b1.author,&b1.price,b1.sname,b1.sid,b1.sbranch) != EOF)
			{
				if(b1.uid==bt2->uid)
					break;
			}
			printf("ID:%d\tNAME:%s\nAUTHOR:%s\nPRICE:%.2f\t\nBOUGHT FROM\tNAME:%s\tPHONE NUMBER:%s",bt2->uid,bt2->name,bt2->author,bt2->price,b1.sname,b1.sid);
			printf("\n---------------------------------------------\n");
			bt2=bt2->l1;
		}
	}
	else if(ch==2)
	{
		bt2=blast;
		while(bt2!=NULL)
		{
			while(fscanf(fp1,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b1.uid,b1.name,b1.author,&b1.price,b1.sname,b1.sid,b1.sbranch) != EOF)
			{
				if(b1.uid==bt2->uid)
					break;
			}
			printf("ID:%d\tNAME:%s\nAUTHOR:%s\nPRICE:%.2f\t\nBOUGHT FROM\tNAME:%s\tPHONE NUMBER:%s",bt2->uid,bt2->name,bt2->author,bt2->price,b1.sname,b1.sid);
			printf("\n---------------------------------------------\n");
			bt2=bt2->p1;
		}
	}
	bfirst->l1=NULL;
	bfirst->p1=NULL;
	free(bfirst);
	bfirst=NULL;
	return 1;
}
//DISPLAY BOOKS WHICH ARE TO BE SOLD
int yhistory()
{
	struct book b;
	int ch;
	FILE *fp;
	fp=fopen("SELL_BOOKS.txt","r");
	while(fscanf(fp,"%d %[^,],%[^,],%f,%[^,],%[^,],%s\n",&b.uid,b.name,b.author,&b.price,b.sname,b.sid,b.sbranch) != EOF)
	{
		if(strcmp(suid,b.sid)==0)
		{	
			if(bfirst==NULL)
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				btemp->l1=NULL;
				btemp->p1=NULL;
				bfirst=btemp;
			}
			else
			{
				btemp=(struct book *)malloc(sizeof(struct book));
				bt1=bfirst;
				while(bt1->l1!=NULL)
				{
					bt1=bt1->l1;
				}
				strcpy(btemp->name,b.name);
				btemp->uid=b.uid;
				strcpy(btemp->author,b.author);
				btemp->price=b.price;
				strcpy(btemp->sid,b.sid);
				strcpy(btemp->sname,b.sname);
				strcpy(btemp->sbranch,b.sbranch);
				bt1->l1=btemp;
				btemp->l1=NULL;
				btemp->p1=bt1;
				blast=btemp;
			}
		}
	}
	if(bfirst==NULL)
	{
		return 2;
	}
	printf("FILTER:\n1.OLDEST TO LATEST\n2.LATEST TO OLDEST\nENTER YOUR CHOICE:");
	scanf("%d",&ch);
	printf("\n\tBOOKS:\n");
	if(ch==1)
	{
		bt2=bfirst;
		while(bt2!=NULL)
		{
			printf("ID:%d\tNAME:%s\nAUTHOR:%s\nPRICE:%.2f\t\n",bt2->uid,bt2->name,bt2->author,bt2->price);
			printf("\n---------------------------------------------\n");
			bt2=bt2->l1;
		}
	}
	else if(ch==2)
	{
		bt2=blast;
		while(bt2!=NULL)
		{
			printf("ID:%d\tNAME:%s\nAUTHOR:%s\nPRICE:%.2f\t\n",bt2->uid,bt2->name,bt2->author,bt2->price);
			printf("\n---------------------------------------------\n");
			bt2=bt2->p1;
		}
	}
	bfirst->l1=NULL;
	bfirst->p1=NULL;
	free(bfirst);
	bfirst=NULL;
	return 1;
}
