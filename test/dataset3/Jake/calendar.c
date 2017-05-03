
/* Created By: Mr. Jake R. Pomperada */
/* Email Address: jakerpomperada@yahoo.com */
/* July 20, 2010 */
/* Bacolod City */

#include<stdio.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include <iostream.h>

void zerospace(int z)
{
	if(z==0)
		printf("   ");
	else if(z>=1&&z<=9)
		printf(" %d ",z);
	else
		printf("%d ",z);
}

 main()
{
int za=0,hd=0,vd=0,bar=0,en=0,sp=0,yl=0,fe=0,y=0,jan=0,feb=0,mar=0,apr=0,may=0,jun=0,jul=0,aug=0,sep=0,oct=0,nov=0,dec=0;
int jana[43],feba[43],mara[43],apra[43],maya[43],juna[43],jula[43],auga[43],sepa[43],octa[43],nova[43],deca[43];
int naj=0,bef=0,ram=0,rpa=0,yam=0,nuj=0,luj=0,gua=0,pes=0,tco=0,von=0,ced=0;
char a,b,sa[]="Sa",su[]="Su",mo[]="Mo",tu[]="Tu",we[]="We",th[]="Th",fr[]="Fr";

do
{
do
{
system("cls");
printf("\t\t === CALENDAR VERSION 1.0 ===");
printf("\n\n");
printf("\t\tEnter the Year :=>");
scanf("%d",&y);

 if (y< 0 ) {
	system("cls");
	printf("\n\n\n");
printf("\t   The year must be a positive number (Valid range starts from 1751)\n");
printf("\n\n");
printf("\t\t\tDo you want to try again (Y/N) ");
a=getch();

 }

else if (y>=1751) {
    break;
}
else if(y < 1751)
	{
printf("\n\n\n");
printf("\t   The valid Year starts from 1751 \n");
printf("\n\n");
printf("\t\t\tDo you want to try again (Y/N) ");
a=getch();
	 }

}
while(a=='y'||a=='Y');

system("cls");
en=4;
for(yl=0;yl<=y-1;yl++)
	{

	for(jan=1;jan<=31;jan++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	if((yl%4==0&&yl%100!=0)||yl%400==0)
		{
		fe=29;
		}
	else if(yl<=1752&&yl%4==0)
		{
		fe=29;
		}
	else
		{
		fe=28;
		}
	for(feb=1;feb<=fe;feb++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	for(mar=1;mar<=31;mar++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	for(apr=1;apr<=30;apr++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	for(may=1;may<=31;may++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	for(jun=1;jun<=30;jun++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	for(jul=1;jul<=31;jul++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}


	for(aug=1;aug<=31;aug++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}

	for(sep=1;sep<=30;sep++)
		{
		en=en+1;
		if(yl==1752&&sep==3)
			{
			sep=14;
			}
		if(en==7)
			{
			en=0;
			}
		}

	for(oct=1;oct<=31;oct++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}


	for(nov=1;nov<=30;nov++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}


	for(dec=1;dec<=31;dec++)
		{
		en=en+1;
		if(en==7)
			{
			en=0;
			}
		}
	}


for(za=0;za<=42;za++)
	{
		jana[za]=0;
		feba[za]=0;
		mara[za]=0;
		apra[za]=0;
		maya[za]=0;
		juna[za]=0;
		jula[za]=0;
		auga[za]=0;
		sepa[za]=0;
		octa[za]=0;
		nova[za]=0;
		deca[za]=0;
	}

for(sp=1;sp<=en;sp++)
	{
	jana[sp]=0;
	}
sp=sp-1;
for(jan=1;jan<=31;jan++)
	{
	en=en+1;
	sp++;
	jana[sp]=jan;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	feba[sp]=0;
	}
	sp=sp-1;
if((y%4==0&&y%100!=0)||y%400==0)
	{
	fe=29;
	}
else if(y<=1752&&y%4==0)
		{
		fe=29;
		}
else
	{
	fe=28;
	}
for(feb=1;feb<=fe;feb++)
	{
	en=en+1;
	sp++;
	feba[sp]=feb;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	mara[sp]=0;
	}
sp=sp-1;
for(mar=1;mar<=31;mar++)
	{
	en=en+1;
	sp++;
	mara[sp]=mar;
	if(en==7)
		{
		en=0;
		}
	}


for(sp=1;sp<=en;sp++)
	{
	apra[sp]=0;
	}
sp=sp-1;
for(apr=1;apr<=30;apr++)
	{
	en=en+1;
	sp++;
	apra[sp]=apr;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	maya[sp]=0;
	}
sp=sp-1;
for(may=1;may<=31;may++)
	{
	en=en+1;
	sp++;
	maya[sp]=may;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	juna[sp]=0;
	}
sp=sp-1;
for(jun=1;jun<=30;jun++)
	{
	en=en+1;
	sp++;
	juna[sp]=jun;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	jula[sp]=0;
	}
sp=sp-1;
for(jul=1;jul<=31;jul++)
	{
	en=en+1;
	sp++;
	jula[sp]=jul;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	auga[sp]=0;
	}
sp=sp-1;
for(aug=1;aug<=31;aug++)
	{
	en=en+1;
	sp++;
	auga[sp]=aug;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	sepa[sp]=0;
	}
sp=sp-1;
for(sep=1;sep<=30;sep++)
	{
	en=en+1;
	sp++;
	if(y==1752&&sep==3)
		{
		sep=14;
		}
	sepa[sp]=sep;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	octa[sp]=0;
	}
sp=sp-1;
for(oct=1;oct<=31;oct++)
	{
	en=en+1;
	sp++;
	octa[sp]=oct;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	nova[sp]=0;
	}
sp=sp-1;
for(nov=1;nov<=30;nov++)
	{
	en=en+1;
	sp++;
	nova[sp]=nov;
	if(en==7)
		{
		en=0;
		}
	}

for(sp=1;sp<=en;sp++)
	{
	deca[sp]=0;
	}
sp=sp-1;
for(dec=1;dec<=31;dec++)
	{
	en=en+1;
	sp++;
	deca[sp]=dec;
	if(en==7)
		{
		en=0;
		}
	}

printf("\n\t\t\t\t  Year: %d\n\n",y);

for(hd=0;hd<=79;hd++)
	{
	if(hd==79)
		printf("\n");
	else
		printf("=");
	}
/*for(vd=0;vd<=79;vd++)
	{
	if(vd==79)
		{
		printf("\n");
		}
	else if(((vd==0||vd==26)||vd==52)||vd==78)
		printf("|");
	else
		{
		printf(" ");
		}
	}*/

printf("|         January         |         February        |          March          |\n");


for(hd=0;hd<=79;hd++)
	{
	if(hd==79)
		printf("\n");
	else
		printf("-");
	}


for(bar=0;bar<=3;bar++)
	{
	if(bar==3)
		{
		printf("|\n");
		}
	else
		{
		printf("|   %s %s %s %s %s %s %s  ",su,mo,tu,we,th,fr,sa);
		}
	}

for(vd=0;vd<=79;vd++)
	{
	if(vd==79)
		{
		printf("\n");
		}
	else if(((vd==0||vd==26)||vd==52)||vd==78)
		printf("|");
	else
		{
		printf(" ");
		}
	}

printf("|   ");
for(naj=1;naj<=7;naj++)
{
	zerospace(jana[naj]);
}
printf(" |   ");

for(bef=1;bef<=7;bef++)
{
	zerospace(feba[bef]);
}
printf(" |   ");

for(ram=1;ram<=7;ram++)
{
	zerospace(mara[ram]);
}
printf(" |\n");

printf("|   ");
for(naj=8;naj<=14;naj++)
{
	zerospace(jana[naj]);
}
printf(" |   ");

for(bef=8;bef<=14;bef++)
{
	zerospace(feba[bef]);
}
printf(" |   ");

for(ram=8;ram<=14;ram++)
{
	zerospace(mara[ram]);
}
printf(" |\n");

printf("|   ");
for(naj=15;naj<=21;naj++)
{
	zerospace(jana[naj]);
}
printf(" |   ");

for(bef=15;bef<=21;bef++)
{
	zerospace(feba[bef]);
}
printf(" |   ");

for(ram=15;ram<=21;ram++)
{
	zerospace(mara[ram]);
}
printf(" |\n");

printf("|   ");
for(naj=22;naj<=28;naj++)
{
	zerospace(jana[naj]);
}
printf(" |   ");

for(bef=22;bef<=28;bef++)
{
	zerospace(feba[bef]);
}
printf(" |   ");

for(ram=22;ram<=28;ram++)
{
	zerospace(mara[ram]);
}
printf(" |\n");

printf("|   ");
for(naj=29;naj<=35;naj++)
{
	zerospace(jana[naj]);
}
printf(" |   ");

for(bef=29;bef<=35;bef++)
{
	zerospace(feba[bef]);
}
printf(" |   ");

for(ram=29;ram<=35;ram++)
{
	zerospace(mara[ram]);
}
printf(" |\n");

printf("|   ");
for(naj=36;naj<=42;naj++)
{
	zerospace(jana[naj]);
}
printf(" |   ");

for(bef=36;bef<=42;bef++)
{
	zerospace(feba[bef]);
}
printf(" |   ");

for(ram=36;ram<=42;ram++)
{
	zerospace(mara[ram]);
}
printf(" |\n");



for(hd=0;hd<=79;hd++)
	{
	if(hd==79)
		printf("\n");
	else
		printf("=");
	}

printf("|          April          |           May           |           June          |\n");

for(hd=0;hd<=79;hd++)
	{
	if(hd==79)
		printf("\n");
	else
		printf("-");
	}

for(bar=0;bar<=3;bar++)
	{
	if(bar==3)
		{
		printf("|\n");
		}
	else
		{
		printf("|   %s %s %s %s %s %s %s  ",su,mo,tu,we,th,fr,sa);
		}
	}

for(vd=0;vd<=79;vd++)
	{
	if(vd==79)
		{
		printf("\n");
		}
	else if(((vd==0||vd==26)||vd==52)||vd==78)
		printf("|");
	else
		{
		printf(" ");
		}
	}

printf("|   ");
for(rpa=1;rpa<=7;rpa++)
{
	zerospace(apra[rpa]);
}
printf(" |   ");

for(yam=1;yam<=7;yam++)
{
	zerospace(maya[yam]);
}
printf(" |   ");

for(nuj=1;nuj<=7;nuj++)
{
	zerospace(juna[nuj]);
}
printf(" |\n");

printf("|   ");
for(rpa=8;rpa<=14;rpa++)
{
	zerospace(apra[rpa]);
}
printf(" |   ");

for(yam=8;yam<=14;yam++)
{
	zerospace(maya[yam]);
}
printf(" |   ");

for(nuj=8;nuj<=14;nuj++)
{
	zerospace(juna[nuj]);
}
printf(" |\n");


printf("|   ");
for(rpa=15;rpa<=21;rpa++)
{
	zerospace(apra[rpa]);
}
printf(" |   ");

for(yam=15;yam<=21;yam++)
{
	zerospace(maya[yam]);
}
printf(" |   ");

for(nuj=15;nuj<=21;nuj++)
{
	zerospace(juna[nuj]);
}
printf(" |\n");

printf("|   ");
for(rpa=22;rpa<=28;rpa++)
{
	zerospace(apra[rpa]);
}
printf(" |   ");

for(yam=22;yam<=28;yam++)
{
	zerospace(maya[yam]);
}
printf(" |   ");

for(nuj=22;nuj<=28;nuj++)
{
	zerospace(juna[nuj]);
}
printf(" |\n");

printf("|   ");
for(rpa=29;rpa<=35;rpa++)
{
	zerospace(apra[rpa]);
}
printf(" |   ");

for(yam=29;yam<=35;yam++)
{
	zerospace(maya[yam]);
}
printf(" |   ");

for(nuj=29;nuj<=35;nuj++)
{
	zerospace(juna[nuj]);
}
printf(" |\n");

printf("|   ");
for(rpa=36;rpa<=42;rpa++)
{
	zerospace(apra[rpa]);
}
printf(" |   ");

for(yam=36;yam<=42;yam++)
{
	zerospace(maya[yam]);
}
printf(" |   ");

for(nuj=36;nuj<=42;nuj++)
{
	zerospace(juna[nuj]);
}
printf(" |\n");


for(hd=0;hd<=79;hd++)
	{

	if(hd==79)
		printf("\n");
	else
		printf("=");
	}


printf("|           July          |          August         |        September        |\n");


for(hd=0;hd<=79;hd++)
	{

	if(hd==79)
		printf("\n");
	else
		printf("-");
	}


for(bar=0;bar<=3;bar++)
	{
	if(bar==3)
		{
		printf("|\n");
		}
	else
		{
		printf("|   %s %s %s %s %s %s %s  ",su,mo,tu,we,th,fr,sa);
		}
	}

for(vd=0;vd<=79;vd++)
	{
	if(vd==79)
		{
		printf("\n");
		}
	else if(((vd==0||vd==26)||vd==52)||vd==78)
		printf("|");
	else
		{
		printf(" ");
		}
	}

printf("|   ");
for(luj=1;luj<=7;luj++)
{
	zerospace(jula[luj]);
}
printf(" |   ");

for(gua=1;gua<=7;gua++)
{
	zerospace(auga[gua]);
}
printf(" |   ");

for(pes=1;pes<=7;pes++)
{
	zerospace(sepa[pes]);
}
printf(" |\n");

printf("|   ");
for(luj=8;luj<=14;luj++)
{
	zerospace(jula[luj]);
}
printf(" |   ");

for(gua=8;gua<=14;gua++)
{
	zerospace(auga[gua]);
}
printf(" |   ");

for(pes=8;pes<=14;pes++)
{
	zerospace(sepa[pes]);
}
printf(" |\n");


printf("|   ");
for(luj=15;luj<=21;luj++)
{
	zerospace(jula[luj]);
}
printf(" |   ");

for(gua=15;gua<=21;gua++)
{
	zerospace(auga[gua]);
}
printf(" |   ");

for(pes=15;pes<=21;pes++)
{
	zerospace(sepa[pes]);
}
printf(" |\n");


printf("|   ");
for(luj=22;luj<=28;luj++)
{
	zerospace(jula[luj]);
}
printf(" |   ");

for(gua=22;gua<=28;gua++)
{
	zerospace(auga[gua]);
}
printf(" |   ");

for(pes=22;pes<=28;pes++)
{
	zerospace(sepa[pes]);
}
printf(" |\n");

printf("|   ");
for(luj=29;luj<=35;luj++)
{
	zerospace(jula[luj]);
}
printf(" |   ");

for(gua=29;gua<=35;gua++)
{
	zerospace(auga[gua]);
}
printf(" |   ");

for(pes=29;pes<=35;pes++)
{
	zerospace(sepa[pes]);
}
printf(" |\n");

printf("|   ");
for(luj=36;luj<=42;luj++)
{
	zerospace(jula[luj]);
}
printf(" |   ");

for(gua=36;gua<=42;gua++)
{
	zerospace(auga[gua]);
}
printf(" |   ");

for(pes=36;pes<=42;pes++)
{
	zerospace(sepa[pes]);
}
printf(" |\n");



for(hd=0;hd<=79;hd++)
	{

	if(hd==79)
		printf("\n");
	else
		printf("=");
	}


printf("|         October         |         November        |         December        |\n");


for(hd=0;hd<=79;hd++)
	{

	if(hd==79)
		printf("\n");
	else
		printf("-");
	}


for(bar=0;bar<=3;bar++)
	{
	if(bar==3)
		{
		printf("|\n");
		}
	else
		{
		printf("|   %s %s %s %s %s %s %s  ",su,mo,tu,we,th,fr,sa);
		}
	}

for(vd=0;vd<=79;vd++)
	{
	if(vd==79)
		{
		printf("\n");
		}
	else if(((vd==0||vd==26)||vd==52)||vd==78)
		printf("|");
	else
		{
		printf(" ");
		}
	}

printf("|   ");
for(tco=1;tco<=7;tco++)
{
	zerospace(octa[tco]);
}
printf(" |   ");

for(von=1;von<=7;von++)
{
	zerospace(nova[von]);
}
printf(" |   ");

for(ced=1;ced<=7;ced++)
{
	zerospace(deca[ced]);
}
printf(" |\n");

printf("|   ");
for(tco=8;tco<=14;tco++)
{
	zerospace(octa[tco]);
}
printf(" |   ");

for(von=8;von<=14;von++)
{
	zerospace(nova[von]);
}
printf(" |   ");

for(ced=8;ced<=14;ced++)
{
	zerospace(deca[ced]);
}
printf(" |\n");

printf("|   ");
for(tco=15;tco<=21;tco++)
{
	zerospace(octa[tco]);
}
printf(" |   ");

for(von=15;von<=21;von++)
{
	zerospace(nova[von]);
}
printf(" |   ");

for(ced=15;ced<=21;ced++)
{
	zerospace(deca[ced]);
}
printf(" |\n");

printf("|   ");
for(tco=22;tco<=28;tco++)
{
	zerospace(octa[tco]);
}
printf(" |   ");

for(von=22;von<=28;von++)
{
	zerospace(nova[von]);
}
printf(" |   ");

for(ced=22;ced<=28;ced++)
{
	zerospace(deca[ced]);
}
printf(" |\n");

printf("|   ");
for(tco=29;tco<=35;tco++)
{
	zerospace(octa[tco]);
}
printf(" |   ");

for(von=29;von<=35;von++)
{
	zerospace(nova[von]);
}
printf(" |   ");

for(ced=29;ced<=35;ced++)
{
	zerospace(deca[ced]);
}
printf(" |\n");

printf("|   ");
for(tco=36;tco<=42;tco++)
{
	zerospace(octa[tco]);
}
printf(" |   ");

for(von=36;von<=42;von++)
{
	zerospace(nova[von]);
}
printf(" |   ");

for(ced=36;ced<=42;ced++)
{
	zerospace(deca[ced]);
}
printf(" |\n");



for(hd=0;hd<=79;hd++)
	{

	if(hd==79)
		printf("\n");
	else
		printf("=");
	}

if(a=='n'||a=='N')
	{
	system("cls");
	printf("\n\n");
	printf("\n\t\t\t THANK YOU FOR USING THIS SOFTWARE  ");
	printf("\n\n");
	break;
	}
else
{
printf("\nDo you want to see the calendar of another year? (Y/N) ");
b=getch();
putch(b);
}
printf("\n\t\t\t   ");

}
while(b=='y'||b=='Y');

}

/* End of Code */

