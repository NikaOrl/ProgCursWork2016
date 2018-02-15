#include "stdafx.h"
#include <iostream>
#include <fstream> 
#include <string.h>//strcpy()-копирование строк
#include <cstring>//strcmp()-сравнение строк
#pragma warning(disable : 4996)//необходимо для strcpy() на VS2012
using namespace std;

void Chose(struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead);
struct Clients* NewOrder(struct Clients* ClHead, struct Orders* OrdHead);
struct Orders* CreateNewOrder(struct Clients* b);
struct Products* CreateNewProduct(struct Products* ProdHead);
struct Clients* ReadNewOrder(struct Clients* ClHead, struct Orders* OrdHead);
struct Products* ReadNewProduct(struct Products* ProdHead);
struct Clients* OneStep1(struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead); 
struct Clients* OneStep2(struct Clients* c, struct Clients* b, struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead);
void WriteClients(struct Clients* ClHead);
void WriteOrders(struct Orders* OrdHead, struct Clients* b);
void WriteProducts(struct Products* ProdHead);
void FOUT(struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead);

const int MAX=40;
struct Products{ //список предлагаемых портным изделий
	int ProdMat;
	char ProdName[MAX];
	Products* next;
};

struct Orders{ //список заказов каждого клиента
	char OrdName[MAX];
	int Num;
	Orders* next;
};

struct Clients{ //список клиентов, каждый элемент которого содержит в себе список заказов
	char ClName[MAX];
	int ColOrd;
	Orders* OrdHead;
	Clients* next;
};

struct  Products* ProdHead=NULL;
struct  Orders* OrdHead=NULL;
struct  Clients* ClHead=NULL;

int main()
{
	setlocale (0, "rus");
	cout<<"Курсовая работа Орловой В. гр.5381\nМоделирование работы (очереди) портного\n\n";
	Chose(ClHead, OrdHead, ProdHead);
	system("pause");
	return 0;
}

void Chose(struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead)
{
	while(true)
	{
		cout<<"\n 1. Новый заказ?\n 2. Добавить изделие\n 3. Выполнить заказ \n 4. Вывести список клиентов\n 5. Вывести список предлагаемой продукции\n 6. Выйти из программы\n";
		int ch, vv, v;
		cin>>ch;
		switch(ch)
		{
		case 1:
			cout<<"Введите:\n 1, если хотите ввести с клавиатуры\n 2, если хотите загрузить из файла\n 3, если хотите выйти из программы \n";
			cin>>v;
			switch(v)
			{
			case 1:
				ClHead=NewOrder(ClHead, OrdHead);
				break;
			case 2:
				ClHead=ReadNewOrder(ClHead, OrdHead);
				break;
			case 3:
				exit(0);
				break;
			default:
				cout<<"Пожалуйста, вводите 1, 2 или 3!\n";
				Chose(ClHead, OrdHead, ProdHead);
			}
			break;
		
		case 2:
			cout<<"Введите:\n 1, если хотите ввести продукцию с клавиатуры\n 2, если хотите загрузить продукцию из файла\n 3, если хотите выйти из программы \n";
			cin>>vv;
			switch(vv)
			{
			case 1:
				ProdHead=CreateNewProduct(ProdHead);
				break;
			case 2:
				ProdHead=ReadNewProduct(ProdHead);
				break;
			case 3:
				exit(0);
				break;
			default:
				cout<<"Пожалуйста, вводите 1, 2 или 3!\n";
				Chose(ClHead, OrdHead, ProdHead);
			}
			break;
		
		case 3:
			ClHead=OneStep1(ClHead, OrdHead, ProdHead);
			break;
		
		case 4:
			WriteClients(ClHead);
			break;
		
		case 5:
			WriteProducts(ProdHead);
			break;
		
		case 6:
			exit(0);
			break;
		
		default:
			cout<<"Пожалуйста, вводите 1, 2, 3, 4, 5 или 6!\n";
			Chose(ClHead, OrdHead, ProdHead);
		}
		FOUT(ClHead, OrdHead, ProdHead);
	}
}

struct Clients* NewOrder(struct Clients* ClHead, struct Orders* OrdHead)
{
	cout<<"Введите имя клиента: ";
	char Name[MAX];
	cin.sync();// очищает поток от имеющихся в нем символов.
	cin.getline(Name, MAX);
	struct Clients* b=ClHead; 
	int k =1;
	while((b!=NULL)&&(b->next!=NULL))  
	{
		if(b!=NULL)
			k=strcmp((b->ClName),Name);
		if(k==0)
			break; 
		b=b->next;
	}
	if((b!=NULL)&&(k==0))
	{
		cout<<"У этого клиента уже есть заказы: ";
		struct Orders* c= b->OrdHead;
		WriteOrders(c,b); 
	}
	else
	{
		if(b==NULL)
		{
			b = new struct Clients;
			ClHead = b;
		}
		else
		{
			b -> next = new struct Clients;
			b=b->next;
		}
		b->next=NULL;
		b->OrdHead = NULL;
		strcpy((b->ClName),Name); 
	}
	b->OrdHead=CreateNewOrder(b);
	struct Orders *e = b->OrdHead;//цикл while кончается после того, как был создан новый элемент. И этот лишний элемент удаляется:
	while((e!= NULL)&&(e -> next!= NULL)&&(e -> next -> next != NULL)) 
		e = e -> next;
	e -> next = NULL;
	cout<<endl;
	WriteClients(ClHead);//убрать
	return ClHead;
}

struct Orders* CreateNewOrder(struct Clients* b)
{
	struct Orders* a= b->OrdHead;
	while((a!=NULL)&&(a->next!=NULL))  
		a=a->next;
	if(a==NULL)
	{
		a = new struct Orders;
		b->OrdHead = a;
	}
	else
	{
		a->next = new struct Orders;
		a=a->next;
	}
	a->next=NULL;
	while(true)
	{
		cout<<"Введите заказ:";
		cin.sync();// очищает поток от имеющихся в нем символов.
		cin.getline(a -> OrdName, MAX);
		a -> next = new struct Orders;
		a = a -> next; 
		a -> next = NULL;
		cout<<"Добавить еще заказ?(y/n)";
		char ans;
		cin>>ans; 
		if(ans=='n')
			break;
	}
	return b->OrdHead;
}

struct Clients* ReadNewOrder(struct Clients* ClHead, struct Orders* OrdHead)
{
	ifstream Fin("Clients.txt");
	if(Fin.good())
	{
		char s[MAX];
		Fin.getline(s, MAX);
		int ind = 0;
		struct Clients* H = ClHead;
		while((H!=NULL)&&(H->next!=NULL))
			H=H->next;
		if(H==NULL)
		{
			H = new struct Clients;
			ClHead = H;
		}
		else
		{
			H->next = new struct Clients;
			H=H->next;
		}
		H->next=NULL;
		Fin.unsetf(ios::skipws);
		while(!Fin.eof())
		{
			char Full[MAX];
			for(int i=0; i<MAX-1; i++)
				Full[i]='\0';
			Fin.getline(Full, MAX);
			int d=0, f=0, g[MAX], r=0;
			for (int i=0; i < MAX-1; i++)
			{
				if(Full[i]==',')
				{
					d++;
					g[r]=i;
					r++;
				}
				if(Full[i]==':')
					f=i;
			}
			int i=0, j=0, t=0;
			if((d!=0)&&(f!=0))
				for (i=0; i < f; i++)
				{
					H->ClName[i]=Full[i];
				}
			H->ClName[i]='\0';
			if((d!=0)&&(f!=0))
			{
				struct Orders* W=H->OrdHead;
				W = new struct Orders;
				H->OrdHead = W;
				W->next=NULL;
				int r=0;
				for (t=0; t < d; t++)
				{
					int rr=0;
					for (j=i+1; j < g[r]; j++)
					{
						W->OrdName[rr]=Full[j];	
						rr++;
					}
					W->OrdName[rr]='\0';
					W->next = new struct Orders;
					W=W->next;
					W->next=NULL;
					i=g[r]+1;
					r++;
				}
				struct Orders *e = H->OrdHead;//цикл while кончается после того, как был создан новый элемент. И этот лишний элемент удаляется:
				while((e!= NULL)&&(e -> next!= NULL)&&(e -> next -> next != NULL)) 
					e = e -> next;
				e -> next = NULL;
				H->next = new struct Clients;
				H=H->next;
				H->next=NULL;
			}
		}
		struct Clients *ee = ClHead;//цикл while кончается после того, как был создан новый элемент. И этот лишний элемент удаляется:
			while((ee!= NULL)&&(ee -> next!= NULL)&&(ee -> next -> next != NULL)) 
				ee = ee -> next;
			ee -> next = NULL;
	}
	else
	{
		cout << "\nОшибка файла\n";
	}

	Fin.close();
	return ClHead;
}

struct Products* CreateNewProduct(struct Products* ProdHead)
{
	struct Products* b=ProdHead;
	while((b!=NULL)&&(b->next!=NULL))  
		b=b->next;
	if(b==NULL)
	{
		b = new struct Products;
		b->next=NULL;
		ProdHead=b;
	}
	else
	{
		b->next = new struct Products;
		b=b->next;
		b->next=NULL;
	}
	while(true)
		{
			cout<<"Введите название нового изделия:";
			cin.sync();// очищает поток от имеющихся в нем символов.
			cin.getline(b -> ProdName, MAX);
			cout<<"Введите количество материала, необходимое для его изготовления:";
			cin>>(b -> ProdMat); //
			b -> next = new struct Products;;
			b = b -> next;
			b -> next = NULL;
			cout<<"Добавить еще изделие?(y/n)";
			char ans;
			cin>>ans; 
			if(ans=='n')
				break;
		}
	struct Products *e = ProdHead;//цикл while кончается после того, как был создан новый элемент. И этот лишний элемент удаляется:(в ф-цию)
	while(e -> next -> next != NULL) e = e -> next;
	e -> next = NULL;
	return ProdHead;
}

struct Products* ReadNewProduct(struct Products* ProdHead)
{
	ifstream Fin("ProdNames.txt");
	if(!Fin.eof())
	{
		Fin.close();
		Fin.open("ProdNames.txt");
		struct Products* b=ProdHead;
		while((b!=NULL)&&(b->next!=NULL)) 
			b=b->next;
		if(b==NULL)
		{
			b = new struct Products;
			b->next=NULL;
			ProdHead=b;
		}
		else
		{
			b->next = new struct Products;
			b=b->next;
			b->next=NULL;
		}
		struct Products* c=b;
		char s[MAX];
		Fin.getline(s, MAX);
		while(!Fin.eof())
		{
			Fin.getline(b -> ProdName, MAX);
			b -> next = new struct Products;;
			b = b -> next;
			b -> next = NULL;
		}
		Fin.close();
		struct Products *e = ProdHead;//цикл while кончается после того, как был создан новый элемент. И этот лишний элемент удаляется:(в ф-цию)
			while(e -> next -> next != NULL)
				e = e -> next;
			e -> next = NULL;
		ifstream Fin("ProdMats.txt");
		if((!Fin.eof()) && (Fin.good()))
		{
			Fin.close();
			Fin.open("ProdMats.txt");
			Fin.getline(s,MAX);
			while((!Fin.eof())&&(c!=NULL))
			{
				Fin>>(c -> ProdMat);
				c = c -> next;
			}
			Fin.close();
		}
		else
			cout <<"Файл ProdMats пуст или данные введены не корректно!\nВведите данные в файл или проверьте их корректность!\n"<<endl;
	}
	else
		cout <<"Файл ProdNames пуст или данные введены не корректно!\nВведите данные в файл или проверьте их корректность!\n"<<endl;
	return ProdHead;
}

struct Clients* OneStep1(struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead)
{
	if(ClHead!=NULL)
	{
		while ((ClHead->OrdHead)==NULL)
		{
			if(ClHead->next!=NULL)
			{
				struct Clients* del=ClHead;
				ClHead=ClHead->next;
				delete del;
			}
			else
			{
				ClHead=NULL;
				return ClHead;
			}
		}
		if (ProdHead!=NULL)
		{
			struct Orders* a=ClHead->OrdHead;
			if(ClHead->OrdHead->next!=NULL)
			{
				ClHead->OrdHead=a->next;
				delete a;
			}
			else
			{
				if(ClHead->next!=NULL)
				{
					struct Clients* del=ClHead;
					ClHead=ClHead->next;
					delete del;
					return ClHead;
				}
				else
				{
					ClHead=NULL;
					return ClHead;
				}
			}
			struct Clients* v=ClHead;
			struct Clients* b=NULL;
			if((v!=NULL)&&(v->next!=NULL))
			{
				while ((v!=NULL)&&(v->next!=NULL))
				{
					v=v->next;
					int k=1;
					if((v->OrdHead)!=NULL)
					{
						k=strcmp((v->OrdHead->OrdName),(ClHead->OrdHead->OrdName));
						if(k==0)
							b=v;
					}
				}
				struct Clients* c=ClHead;
				if(b!=NULL)
				{
					ClHead=ClHead->next;
					c->next=b->next;
					b->next=c;
				}
				ClHead=OneStep2(c, b, ClHead, OrdHead, ProdHead);
			}
		}
		else
			cout<<"Изделий на продажу пока нет\n";
	}
	WriteClients(ClHead);
	return ClHead;
}

struct Clients* OneStep2(struct Clients* c, struct Clients* b, struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead)
{
	if((c!=NULL)&&(c->next!=NULL))
		{
			int MatC=0, MatD=0;
			struct Clients* d=c->next;
			do
			{
				int MatC=0, MatD=0;
				struct Clients* d=c->next;
				do
				{
					struct Products* o=ProdHead;
					while(o!=NULL)
					{
						int k=1;
						k=strcmp((c->OrdHead->OrdName),(o->ProdName));
						if(k==0)	
						{
							MatC=o->ProdMat;
							break;
						}
						o=o->next;
					}
					if(MatC==0)
					{
						cout<<"В базе данных нет следующего заказа клиента "<<(c->ClName)<<". Он будет удален.\n";
						if(c->OrdHead->next!=NULL)
						{
							struct Orders* y=c->OrdHead;
							c->OrdHead=c->OrdHead->next;//
							delete y;
						}
						else
						{
							if(b!=NULL)
							{
								struct Clients* del=c;
								b->next=d;
								delete del;
								return ClHead;
							}
							else
							{
								struct Clients* del=ClHead;
								ClHead=ClHead->next;
								delete del;
								return ClHead;
							}
						}
					}
				}
				while(MatC==0);
				do
				{
					while ((d->OrdHead)==NULL)
					{
						if(d->next!=NULL)
						{
							struct Clients* del=d;
							c->next=d->next;
							d=d->next;
							delete del;
						}
						else
						{
							c->next=NULL;
							return ClHead;
						}
					}
					struct Products* oo=ProdHead;
					while(oo!=NULL)
					{
						int k=1;
						k=strcmp((d->OrdHead->OrdName),(oo->ProdName));//
						if(k==0)
						{
							MatD=oo->ProdMat;
							break;
						}
						oo=oo->next;
					}
					if(MatD==0)
					{
						cout<<"В базе данных нет следующего заказа клиента "<<(d->ClName)<<". Он будет удален.\n";
						//
						if(d->OrdHead->next!=NULL)
						{
							struct Orders* y=d->OrdHead;
							d->OrdHead=d->OrdHead->next;
							delete y;
						}
						else
						{
							if(d->next!=NULL)
							{
								struct Clients* del=d;
								c->next=d->next;
								d=d->next;
								delete del;
							}
							else
							{
								c->next=NULL;
								return ClHead;
							}
						}
					}
				}
				while(MatD==0);

				if(MatC>MatD)//b для NULL
				{
					if(b!=NULL)
					{
						c->next=d->next;
						d->next=c;
						b->next=d;
						if(c->next!=NULL)
						{
							d=c->next;
							b=b->next;
						}
						else
							return ClHead;
					}
					else
					{
						c->next=d->next;
						d->next=c;
						ClHead=d;
						if(c->next!=NULL)
							b=ClHead;
						else
							return ClHead;
					}

				}
				else
					break;
			}
			while(true); 
		}
		return ClHead;
}

void WriteClients(struct Clients* ClHead)
{
	if(ClHead!=NULL)
	{
	cout<<"Заказы:\n";
	int i=0;
	struct Clients* w=ClHead;
	while(w!=NULL)
	{
		i++;
		cout<<i<<". "<<(w->ClName)<<": ";
		WriteOrders(w->OrdHead, w);
		//cout<<endl;
		w=w->next;
	}
	}
	else
		cout<<"Клиентов пока нет\n";
}

void WriteOrders(struct Orders* OrdHead, struct Clients* b)
{
	if (b->OrdHead!= NULL)
	{
		struct Orders* Curr = b->OrdHead;
		while((Curr != NULL)&&(Curr -> next != NULL))
		{
			cout << Curr -> OrdName << " -> ";
			Curr = Curr -> next;
		}
		cout << Curr -> OrdName<<endl;
	}
	else
		cout << "\nСписок пуст\n";
}

void WriteProducts(struct Products* ProdHead)
{
	if (ProdHead != NULL)
	{
		struct Products* Curr = ProdHead;
		cout << "\nПредлагаемые изделия:\n";
		int i=1;
		while(Curr -> next != NULL && Curr != NULL)
		{
			cout << i<<". "<< Curr -> ProdName << " - "<<Curr->ProdMat<<" единиц материала\n";
			i++;
			Curr = Curr -> next;
		}
		cout << i<<". "<< Curr -> ProdName << " - "<<Curr->ProdMat<<" единиц материала\n";
	}
	else
		cout << "\nИзделий пока нет\n";
}

void FOUT(struct Clients* ClHead, struct Orders* OrdHead, struct Products* ProdHead)
{
	ofstream fout("Протокол.txt");  
	fout<<"--------Протокол работы программы--------";
	if (ProdHead != NULL)
	{
		struct Products* Curr = ProdHead;
		fout << "\nПредлагаемые изделия:\n";
		int i=1;
		while(Curr -> next != NULL && Curr != NULL)
		{
			fout << i<<". "<< Curr -> ProdName << " - "<<Curr->ProdMat<<" единиц материала\n";
			i++;
			Curr = Curr -> next;
		}
		fout << i<<". "<< Curr -> ProdName << " - "<<Curr->ProdMat<<" единиц материала\n";
	}
	else
		fout << "\nИзделий пока нет\n\n";
	if(ClHead!=NULL)
	{
		fout<<"Заказы:\n";
		int i=0;
		struct Clients* w=ClHead;
		while(w!=NULL)
		{
			i++;
			fout<<i<<". "<<(w->ClName)<<": ";
			if (w->OrdHead!= NULL)
			{
				struct Orders* rr = w->OrdHead;
				while((rr != NULL)&&(rr -> next != NULL))
				{
					fout << rr -> OrdName << " -> ";
					rr = rr -> next;
				}
				fout << rr -> OrdName<<endl;
			}
			else
				fout << "\nЗаказов нет\n";
			w=w->next;
		}
	}
	else
		fout<<"Клиентов пока нет";
	fout.close();
}