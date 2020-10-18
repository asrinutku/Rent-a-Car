#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <string.h>
COORD coord = {0,0};
struct insan
{
	char isim[20];
	int  telno;
	int kiralamagunsayisi; 
	char kiralananarac[20];
	int odenecekucret;
	char kayitkontrol;

};

struct arac
{
	char otomobil[20];
	int saatlikucret;
	int kayitnumarasi;
	char kayitkonrol;
};

 void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void login()
{	
    int i=0,denemehakki=0;
	char c=' ';
	char kullanici[10];
	char sifre[10];
    
    while(1)
	{
	
		gotoxy(30,0);
		printf("---Kullanici Giris Ekrani---");
		gotoxy(16,2);
		printf("Kullanici Adi:");
		gets(kullanici);
		gotoxy(24,4);
		printf("Sifre:");
	    while(i<10)
	    {
	      sifre[i]=getch();
	      c=sifre[i];
	      if(c==13) break;
		  else printf("*");
	      i++;
     	}
     	sifre[i]='\0';
     	
     	if(strcmp(kullanici,"root")==0 && strcmp(sifre,"toor")==0)
     	{
     		
     		gotoxy(15,7);
     		printf("-----Arac Kiralama Sistemine Hosgeldiniz-----");
     		gotoxy(15,9);
     		printf("Yukleniyor Lutfen Bekleyin");
     		 for(i=0; i<5; i++)
             {
                printf(".");
                Sleep(500);
             }
            gotoxy(30,15);
            printf("Devam Etmek Icin Herhangi Bir Tusa Basin");
            getch();
            break;
		 }
		 else 
		 {
		 	gotoxy(7,7);
		 	printf("Hatali Kullanici Adi Yada Sifre Lutfen Programi Kapatip Tekrar Deneyin.");
		 	gotoxy(30,15);
		 	Sleep(1000);
            printf("Sonlandirmak Icin Herhangi Bir Tusa Basin");
		 	getch();
		 	exit(1);
		 	
		 }
    }
    system("cls");	
}	 

void aracekle(FILE *fp)
{
    gotoxy(30,0);
	printf("Arac Ekleme\n");
    struct arac araba;
    int a,i;
	   for(i=0;i<30;i++)
	{
	     
	   	fseek(fp,i*sizeof(struct arac),SEEK_SET);
	    fread(&araba,sizeof(struct arac),1,fp);
	    
	    if (araba.kayitkonrol=='B'){
		
		araba.kayitkonrol='D';
	    gotoxy(0,2);
	    printf("Kayit Numarasi:");
	    scanf("%d",&araba.kayitnumarasi);
	  
	    gotoxy(0,4);
		printf("Eklenecek Aracin Marka ve Modeli(Birlesik Halde Yazin):");
	    scanf("%s",&araba.otomobil);
	    
	    gotoxy(0,6);
	    printf("Eklemek Istediniz Aracin Gunluk Ucreti:");
	    scanf("%d",&araba.saatlikucret);
	   
	    
	    fseek(fp,i*sizeof(struct arac),SEEK_SET);
	    fwrite(&araba,sizeof(struct arac),1,fp);
	
     	gotoxy(2,8);
     	printf("Arac Basariyla Eklendi");
    	getch();
    	return ;
        }
    }
}

void araclistele(FILE *fp)
{
    struct arac araba;
	int i;
	gotoxy(30,0);
	printf("Arac Listesi");
	printf("\n");
	printf("%10s%20s%20s%20s","Kayit Numarasi","Marka-Model","Gunluk Ucret","Doluluk Durumu");
	printf("\n");
	for(i=0;i<30;i++)
	{
		fseek(fp,i*sizeof(struct arac),SEEK_SET);
		fread(&araba,sizeof(struct arac),1,fp);  
		
		if(araba.kayitkonrol=='D')
		{   
		   
			printf("%8d %18s %20d %16c",araba.kayitnumarasi,araba.otomobil,araba.saatlikucret,araba.kayitkonrol);
			printf("\n");
		}
	}
	
	getch();
}
void aracsec(FILE *fp,FILE *fp1)
{
	int i,kayitno,kiralamagunsayisi,secilenaraba,bulundumu;
	char kontrol;
	int toplamucret;
	struct arac araba;
	struct insan musteri;
	
	gotoxy(25,0);
	printf("Arac Secimi ve Kiralama Bilgileri");
    gotoxy(0,5);
	printf("Aracin Kiralanacagi Gun Sayisi:");
	scanf("%d",&kiralamagunsayisi);
	
	gotoxy(0,8);
	printf("Secmek Istediginiz Aracin Kayit Numarasini Girin:");
    scanf("%d",&kayitno);
	printf("\n");
	for(i=0;i<30;i++)
	{ 
	    bulundumu=0;
		fseek(fp,i*sizeof(struct arac),SEEK_SET);
	    fread(&araba,sizeof(struct arac),1,fp);
	    
	    if(araba.kayitkonrol=='D')
		{   
		   if(kayitno==araba.kayitnumarasi)
		   {
		   	    secilenaraba=i;
		   	    bulundumu=1;
		   }	
		}
	    if(bulundumu==1) break;
	}
    
	toplamucret=kiralamagunsayisi*araba.saatlikucret;
	printf("Secilen Aracin Istenilen Gun Sayisinda Toplam Ucreti=%d TL",toplamucret);
	printf("\n");
	printf("Kiralama Islemine Devam Etmek Istiyormusunuz?(e/h)");
	scanf("%s",&kontrol);
	
    if(kontrol=='e')
	{
	    
	    for(i=0;i<30;i++)
	    { 
	        bulundumu=0;
		    fseek(fp1,i*sizeof(struct insan),SEEK_SET);
	        fread(&musteri,sizeof(struct insan),1,fp1);
	    
	        if(musteri.kayitkontrol=='B')
	        {   
	        	gotoxy(0,13);
	            printf("Isim:");
	            scanf("%s",musteri.isim);
            	gotoxy(0,15);
	            printf("Telefon Numarasi:");
	            scanf("%d",&musteri.telno);
	            musteri.kiralamagunsayisi=kiralamagunsayisi;
		        musteri.kayitkontrol='D';
		        musteri.odenecekucret=toplamucret;
		        strcpy(musteri.kiralananarac,araba.otomobil);
		           
		        fseek(fp1,i*sizeof(struct insan),SEEK_SET);
	            fwrite(&musteri,sizeof(struct insan),1,fp1);
	            printf("\n");
	            printf("Arac Basariyla Kiralandi.Iyi Yolculuklar Dileriz.");
				bulundumu=1;
		    }    
	        if(bulundumu==1) break;
	    }
	}
	else {
		printf("Kiralama Ýsleminden Vazgecildi");
	}
	getch();
}
void aracsil(FILE *fp)
{
	int i,sil,silinecekaraba,bulundumu;
	char kontrol;
	struct arac araba;
	fflush(stdin);
	gotoxy(30,0);
	printf("Arac Kaydi Sil");
	
	gotoxy(0,3);
	printf("Kaydini Silmek Istediginiz Aracin Kayit Numarasini Girin:");
    scanf("%d",&sil);
    printf("\n");
	for(i=0;i<30;i++)
	{ 
	   
	    bulundumu=0;
		fseek(fp,i*sizeof(struct arac),SEEK_SET);
	    fread(&araba,sizeof(struct arac),1,fp);
	    
	    if(araba.kayitkonrol=='D')
		{   
		   if(sil==araba.kayitnumarasi)
		   {
		   	    printf("%10s%20s%20s%20s","Kayit Numarasi","Marka-Model","Saatlik Ucret","Kayit Kontrol");
	            printf("\n");
	            printf("%8d %18s %20d %16c",araba.kayitnumarasi,araba.otomobil,araba.saatlikucret,araba.kayitkonrol);
		   	    gotoxy(0,8);
	            printf("Bu Aracin Kaydini Silmek Ýstediginize Eminmisiniz?(e/h)\n\n");
	            scanf("%s",&kontrol);
	            
	            if (kontrol=='e')
	            {
	            	araba.kayitkonrol='B';
	            	fseek(fp,i*sizeof(struct arac),SEEK_SET);
	                fwrite(&araba,sizeof(struct arac),1,fp);
	            	printf("Arac Kaydi Basariyla Silindi");
	            	bulundumu=1;
				}
				else {
				    printf("Kayit Silme Ýsleminden Vazgecildi");
					bulundumu=1;
				 }
		   	    
		   }
			if(bulundumu==1) break;
		}
	}
	if(bulundumu==0) printf("Bu kayit numarasina uygun arac bulunamadi");
	getch();
}
void kiralamabilgileri(FILE *fp,FILE *fp1)
{
	int i;
	struct arac araba;
	struct insan musteri;
	
	gotoxy(30,0);
	printf("Kiralanan Arac Bilgileri");
	gotoxy(0,2);
	printf("%10s%10s%20s%20s","Isim","Telno","Toplam Ucret","Kiralanan Arac");
	printf("\n\n");
	for(i=0;i<30;i++)
	{
		fseek(fp1,i*sizeof(struct insan),SEEK_SET);
		fread(&musteri,sizeof(struct insan),1,fp1);  
		
		if(musteri.kayitkontrol=='D')
		{   
			printf("%8s %9d %15d %17s",musteri.isim,musteri.telno,musteri.odenecekucret,musteri.kiralananarac);
			printf("\n\n");
		}
		
	}
	getch();
}
void secimekrani()
{
	int ilkcalistirmakontrol,ilkcalistirmakontrol1;
	int secim,Boyut,i;
	FILE *fp,*fp1;
	struct arac araba={" ",0,0,'B'};
	struct insan musteri={" ",0,0," ",0,'B'};
	
    if((fp=fopen("MP.txt","r+"))==0)
    {
        fp=fopen("MP.txt","w+");
        fclose(fp);
        fp=fopen("MP.txt","r+");          //ARAC KAYIT BÝLGÝLERÝ DOSYASI
        ilkcalistirmakontrol=1;
    }
    
    if((fp1=fopen("MP1.txt","r+"))==0)
    {
        fp1=fopen("MP1.txt","w+");
        fclose(fp1);                        //MUSTERÝ KAYIT BÝLGÝLERÝ DOSYASI
        fp1=fopen("MP1.txt","r+");
        ilkcalistirmakontrol1=1;
    }
    
    if(ilkcalistirmakontrol==1){
    for(i=0;i<30;i++)
        {
            fseek(fp,i*sizeof(struct arac),SEEK_SET);
            fwrite(&araba,sizeof(struct arac),1,fp);
        }
    }
	if(ilkcalistirmakontrol1==1){
    for(i=0;i<30;i++)
        {
            fseek(fp1,i*sizeof(struct insan),SEEK_SET);
            fwrite(&musteri,sizeof(struct insan),1,fp1);
        }
    }
	while(1){
	
	system("cls");
	gotoxy(25,0);
	printf("---Secim Ekranina Hosgeldiniz---");
	gotoxy(0,2);
	printf("Lutfen Yapmak Istediginiz Islemi Secin");
	gotoxy(0,4);
	printf("1-Yeni Arac Ekle");
	gotoxy(0,6);
	printf("2-Arac Listesi");
	gotoxy(0,8);
	printf("3-Arac Kayit Sil");
	gotoxy(0,10);
	printf("4-Arac Kirala");
	gotoxy(0,12);
	printf("5-Kiralanan Bilgileri");
	gotoxy(0,14);
	printf("6-Cikis"); 
	
	
	secim=getch(); 
    switch(secim)
    {
    	case '1':
		    system("cls");
    		aracekle(fp);
    		break;
        case '2':
		    system("cls");
    		araclistele(fp);
    		break;
    	case '3':
    		system("cls");
			aracsil(fp);
		    break ;
		case '4':
    		system("cls");
			aracsec(fp,fp1);
		    break ;
		case '5':
    		system("cls");
			kiralamabilgileri(fp,fp1);
		    break ;
		case '6':
			fclose(fp);
		    exit(1);	 	 	 	
	}
    }
}
int main(){
	login();
	secimekrani();
	return 0;
}
