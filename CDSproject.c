#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bookstore.h"
//MAIN MENU FUNCTION
int  main()
{
	int c,choice,choice1,choice2,choice3,choice4,count,count1,count2,count3,count4,da,db,b,s,sb,sh,yh,u,i,z,p,t;
	printf("\t\t\t\tWELCOME TO KMIT SECOND HAND BOOK STORE\n");
	while(1)
	{
		printf("\n\t\t1.SIGN UP\n\t\t2.SIGN IN\nENTER YOUR CHOICE:");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				u=signup();
				if(u==1){
					printf("Your account has been created.\nPlease login again to Continue\n");
				}
				else
				{
					printf("\n\t\tLogin failed..\n");
				}
				break;
			case 2:
				i=signin();
				if(i==1){
					while(1)
					{
						printf("\n\t\t1.BUY/SELL\n\t\t2.UPDATE YOUR PROFILE\n\t\t3.SETTINGS\n\t\t4.LOGOUT\nEnter your choice:");
						scanf("%d",&choice);
						switch(choice)
						{
							case 1:
								do
								{
									printf("\n\t\t1.BUY the book\n\t\t2.SELL the book\n\t\t3.GO BACK TO LOGIN PAGE\nEnter your choice:");
									scanf("%d",&choice1);
									switch(choice1)
									{
										case 1:
											printf("\n\t-----------SEARCHING BOOKS------------\n");
											b=buy();
											break;
										case 2:
											s=sell();
											if(s==1)
												printf("YOUR BOOK DETAILS HAS BEEN SUCCESSFULLY ADDED :)\n");
											else
												printf("\n\t\tTHERE IS A PROBLEM ADDING YOUR DETAILS :( \n");
											break;
										case 3:
											count=1;
											break;
										default:
											printf("INVALID INPUT\n");
									}
									if(count==1)
										break;
								}while(1);
								count=0;
								break;
							case 2:
								while(1){
									printf("\n\tDO YOU WANT TO UPDATE:\n\t\t1.YOUR PERSONAL DETAILS\n\t\t2.BOOK DETAILS\n\t\t3.BACK TO LOGIN PAGE\nENTER YOUR CHOICE:");
									fflush(stdin);
									scanf("%d",&choice2);
									switch(choice2)
									{
										case 1:
											p=pupdate();
											if(p==1)
												printf("YOUR PERSONAL DETAILS HAS BEEN UPDATED :) \n");
											else
												printf("\n\t\t!!THERE IS A PROBLEM IN UPDATING :( \n");
											break;
										case 2:
											t=bupdate();
											if(t==1)
												printf("Your BOOK Details has been updated :) \n");
											else if(t==2)
												printf("NO BOOK ENTRY\n");
											else
												printf("\n\t\t!!THERE IS A PROBLEM IN UPDATING :( \n");
											break;
										case 3:
											count1=1;
											break;
										default:
											printf("INVALID INPUT\n");
									}
									if(count1==1)
										break;
								}	
								break;
							case 3:
								while(1)
								{
									printf("\n\t\t1.DELETE\n\t\t2.HISTORY\n\t\t3.BACK TO MAIN MENU\nENTER YOUR CHOICE:");
									scanf("%d",&choice3);
									switch(choice3)
									{
										case 1:
											while(1){
											printf("\n\t\t1.DELETE ACCOUNT\n\t\t2.DELETE BOOK\n\t\t3.BACK TO LOGIN PAGE\nENTER YOUR CHOICE:");
											fflush(stdin);
											scanf("%d",&choice3);
											switch(choice3)
											{
												case 1:
													da=deleta();
													if(da==1)
													{
														printf("YOUR ACCOUNT HAS BEEN DELETED :) \n");
														exit(0);
													}
													if(da==0)
														printf("\n\t\t!!SERVER NOT RESPONDING :( \n");
													break;
												case 2:
													db=deletb();
													if(db==1)
														printf("YOUR BOOK DETAILS HAS BEEN DELETED :) \n");
													else if(db==2)
														printf("NO BOOK ENTRY\n");
													else
														printf("\n\t\t!!SERVER NOT RESPONDING :( \n");
													break;
												case 3:
													count3=1;
													break;
												default:
													printf("INVALID INPUT\n");
											}
											if(count3==1)
												break;
										}
											break;
										case 2:
											while(1)
											{
												printf("\n\t\t1.SOLD BOOKS HISTORY\n\t\t2.BOUGHT BOOKS HISTORY\n\t\t3.YOUR BOOKS IN STORE\n\t\t4.BACK TO MENU\nENTER YOUR CHOICE:");
												scanf("%d",&choice4);
												switch(choice4)
												{
													case 1:
														sh=shistory();
														if(sh==2)
															printf("\n\tNO BOOK ENTRIES\n\n");
														break;
													case 2:
														sb=bhistory();
														if(sb==2)
															printf("\n\tNO BOOK ENTRIES\n\n");
														break;
													case 3:
														yh=yhistory();
														if(yh==2)
															printf("\n\tNO BOOK ENTRIES\n\n");
														break;
													case 4:
														count4=1;
														break;
													default:
														printf("\nINVALID CHOICE\n");
												}
												if(count4==1)
													break;
											}
											break;
										case 3:
											count2=1;
											break;
										default:
											printf("INVALID INPUT.\n");
									}
									if(count2=1)
										break;
								}
								break;
							case 4:
								printf("\n\t\tLOGGING out...");
								printf("\n\t\tLOGGED OUT.");
								exit(0);
							default:
								printf("INVALID INPUT\n");
						}
					}
				}
				break;
			default:
				printf("\n\t\tYOU MUST LOGIN TO VIEW THE BOOKS\n"); 	
		}
	}
}
