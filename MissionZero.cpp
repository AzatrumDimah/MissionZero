#include <iostream>
#include <cmath>
#include <string>
#define p0 1000       //p0 is initial population
#define V0 100000  // initial economic value
#define taxrate 10    // given in percentage

using namespace std;

int H(float t);
int I(int state, float t, float e);
int D(int Ch, float t);
int T(int Ct, float t);
int Tax (float t , int Inv);
void Input (int &state , float &e , int &Ct , int & Ch , int &Inv, int &purse);
void display (float t1, float t2 , int &purse , int Inv,int _I[1500] , int _D[1500], int _T[1500], int _H[1500] );
void Run(int _I[1500] , int _D[1500], int _T[1500], int _H[1500] , int state , float e , int Ct , int Ch ,float t1 , float t2);
int V (float t , int Inv);
void finaldisplay (float t1, float t2 , int &purse , int Inv);
void startdisplay();

int _I[1500] , _D[1500] , _T[1500], _H[1500];
float z= 0.4;






int main()
{
//cout << p0<< endl;	
startdisplay();
int state=3,Ct = 5, Ch= 50, Inv =0 , purse = 100000 ;
float e= 0 ; 

for ( int r= 0; r!= 200 ; r++)
{
	_I[r]= 1 ; _D[r]=0 ; _T[r]=0; _H[r]=0;
}

Input (state ,e ,Ct ,Ch ,Inv,purse);
Run(_I ,_D,_T,_H ,state ,e , Ct , Ch, 20, 40);
display (20, 40 , purse , Inv,_I ,_D,_T,_H);

Input (state ,e ,Ct ,Ch ,Inv,purse);
Run(_I,_D,_T,_H,state ,e , Ct , Ch, 40 , 60);
display (40, 60 , purse , Inv,_I,_D,_T,_H);


Input (state ,e ,Ct ,Ch ,Inv,purse);
Run(_I ,_D,_T,_H ,state ,e , Ct , Ch, 60, 80);
display (60, 80 , purse , Inv,_I,_D,_T,_H);

/*Input (state ,e ,Ct ,Ch ,Inv,purse);
Run(_I ,_D,_T,_H ,state ,e , Ct , Ch, 80, 100);
display (80, 100 , purse , Inv,_I ,_D,_T,_H);*/

finaldisplay (20, 100 , purse ,Inv);
/*
cout<<endl;
int sum = 0;
int sum1=0;
int sum2;
for (int i= 0 ; i != 1000 ; i++)
{
	sum = sum + _I[i];
	sum1 = sum1 + _H[i] +_T[i];
	sum2 =0 ;
	for (int j =i -200 ; j!= i ; j++)
	{
		sum2= sum2 + _I[j];
	}
	cout << i*0.1 <<"\t"<< _I[i]<<"\t"<<_H[i]<<"\t"<< _D[i]<<"\t"<< _T[i]<<"\t" << sum*0.1 <<"\t"<< (sum2*0.1 /(p0 )) << endl;
}
*/
return 0;	
	
}








void startdisplay()
{
	cout << "  WELCOME USER \n please enter name ";
	string name ;
	getline(cin,  name );  
	cout << " Colonel " << name << " , you were a decorated public official who did a great service to the society before you retired .\n ";
	cout << "However these special times have forced officials to ask you to come out of retirement for a final MISSION ZERO. \n";
	cout << " YOU START WITH  \n  HOSPITAL CAPACITY = 50 \n TESTING CAPACITY = 5 \n FUNDS = 100000 \n\n\n\n";
	

}











void display (float t1, float t2 , int &purse , int Inv,int _I[1500] , int _D[1500], int _T[1500], int _H[1500] )
{
	int sumT=0,sumI=0,sumH=0,sumD=0;
	for ( int i = t1*10 ; i < t2 * 10 ; i++)
	{
		sumH= sumH + 0.1*_H[i];
		sumD= sumD + 0.1 *_D[i];
		sumT = sumT  +0.1* _T[i];
		sumI = sumI +0.1*_I[i];
	}
	cout << "\n PURSE REMAINING     "<<  purse <<  endl; 
	cout << "\n\n  NO OF NEW"<< endl;
	cout<< "DEATHS  =  "<< sumD<< endl;
	cout<< "POSITIVE TESTED CASES  =  "<<  sumT<< endl;
	purse = purse + Tax(t2,Inv);
	cout << "\n TAX COLLECTED = " << Tax(t2 , Inv);
}





// made to store required values in arrays

void Run(int _I[1500] , int _D[1500], int _T[1500], int _H[1500] , int state , float e , int Ct , int Ch, float t1 , float t2)
{
	for ( int i = t1*10 ; i <= t2 *10 ; i++)
	{
		_I[i] =  I(state,0.1*i,e);
		_H[i] = H(0.1*i);
		_D[i] = D(Ch, 0.1*i);
		_T[i] = T(Ct, 0.1*i);
	}
}




int H(float t)
{
	if (t < 20)
	{
	 return 0;
	}
	else
	{
	
	float sum;	
	for(int i= (t-20)*10 ; i< t*10 ; i++)
	{
		
		sum = sum +(_I[i]-_D[i]-_T[i])*0.1;
		
		}
	sum = sum * 0.2;
	int ans = floor(sum);
     if (ans > 0)
{
	return ans;
 } 
 else 
{
	return 0;
 } 
}
}
	


	
int I(int state, float t, float e)
{
	if(t<20)
	{
		return 1;
	}
	else
	{
	float sum=0;	
	for(int x= (t-20)*10 ; x< t*10 ; x++)
	{
		
		sum = sum +(_I[x] - _D[x] - _T[x] )*0.1 ;
		
		}
	float sum1=0;		
		for(int x= 0 ; x< t*10 ; x++)
	{
		
		sum1 = sum1 +(_I[x])*0.1 ;
		
		}		
	int s = floor(sum);	
	int s1= floor (sum1);
	
	float pc = (p0*1.0- s1)/p0; // pc stands for population constant and it denotes the ratio of unaffected people in the population

float result;

	if (state == 1)//complete lockdown
	{
		 result = ((z-0.1-e)*s)*pc;
	}
	
	else if (state == 2)//partial lockdown
	{
		 result= ((z-0.05-e)*s)*pc;
	}
	
	else //no lockdown
	{
		 result = ((z-e)*s)*pc;
	}
	
int ans = floor(result);
if (ans > 0)
{
	return ans;
 } 
 else 
{
	return 0;
 } 

 
}
}








int D(int Ch, float t)//Ch is hospital capacity
{
	int i = t*10 ;
	if (_H[i]>Ch)
	{
		return (_H[i]-Ch);
	}
	else 
	{
		return 0;
	}
}





int T(int Ct, float t)//Ct is testing capacity
{
	if ( t <20)
	{
		return 0;
	}
	else 
	{
	
	float sum =0;
		for(int x= 10*(t-20) ; x< t*10 ; x++)
	{
		
		sum = sum + (_I[x])*0.1;
		
		}
	int s= floor (sum);
	
	float sum1=0;
		for(int x= 0 ; x< t*10 ; x++)
	{
		
		sum1= sum1+ (_H[x]+_T[x])*0.1;
		
		}	
	int s1 = floor(sum1);
	float result =(s*(1.0)/(p0))*Ct*Ct;
	//float result =double(s/(p0-s1))*Ct*Ct*Ct; //
	int ans = floor (abs (result));
	
	if (ans > Ct)
	{
		return Ct;
	}
	else 
	{
		return ans;
	}
	/*else
	{
		return 0;
	}*/
}
}

	
int V (float t , int Inv)	//Inv is investment made
	
	{
	
	float c1, c2,sum;
	
	c1= 2/(1+exp(-Inv/1000));
	
	sum =0;
		for(int x= 0 ; x< t*10 ; x++)
	{
		
		sum = sum + (_D[x]*0.1);
		
		}
	c2 = ((p0-sum)/p0)*((p0-sum)/p0);
	
	float result = c1*c2*V0;
	int ans = floor (result);
	
	return ans;
	
}





int Tax(float t, int Inv)
{
	return floor(taxrate*0.01*V(t,Inv));
}





void Input (int &state , float &e , int &Ct , int & Ch , int &Inv, int &purse)
{
	bool q=1;
	cout << "\n REMAINING FUNDS  = " << purse << endl;
	while (q)// input for lockdown enforcement
	{
	cout << "\n ENTER STATE - FOR COMPLETE LOCKDOWN(COST 35000) -- 1 \n FOR PARTIAL LOCKDOWN(COST 20000) -- 2  \n  FOR NO LOCKDOWN(COST 0) -- 3  \n ";
	cin >> state;
	if (state == 1 || state == 2|| state == 3)
	{
		if ( state == 3)
		{
		q=0;
	    }
		if (state == 1  )
		{
			if (purse >= 35000)
			{purse = purse -35000;
			q=0;}
			
			else 
		     cout << " \n NOT ENOUGH MONEY"<< endl;	
		}
		if (state == 2 )
		{
			if (purse >= 20000)
			{
			purse = purse - 20000;
			q=0;
			
	        }
		else 
		     cout << " \n NOT ENOUGH MONEY"<< endl;
    	
		}
	}
	else 
		cout << "\n INVALID INPUT "<< endl;
	
    }
    
	cout << "\n REMAINING FUNDS  = " << purse << endl;
	q=1; //input for installation of a sanitisation centre
	int w = 0;
    while (q)
    {
    	cout<< "\n DO YOU WANT TO INSTALL A SANITISATION STATION(COST - 3000 ) \n ENTER 1 FOR YES AND 0 FOR NO \n ";
    	cin >> w;
    	if (w == 1 )
    	{
    		if (purse >= 3000)
    		{
			q=0;
    		e = e+0.01;
    		cout << "\n CONGRATULATIONS \n \n";
    		purse = purse -3000;
    	     }
    	     else 
    	     {
    	     	cout << "\n NOT ENOUGH MONEY"<<endl;
			 }
		
		}
		else if (w==0)
		{
			q=0;
		}
		else 
		{
			cout << "\n INVALID INTPUT  \n ";
		}
	}
	
		q=1; //input for distribution of face masks;
	w = 0;
	cout << " \n REMAINING FUNDS  = " << purse << endl;
    while (q)
    {
    	cout<< " \n DO YOU WANT TO DISTRIBUTE MASKS ( COST - 2000 ) \n ENTER 1 FOR YES AND 0 FOR NO \n ";
    	cin >> w;
    	if (w == 1)
    	{
    		if (purse >= 2000)
			{
			q=0;
    		e = e+0.01;
    		cout << "\n CONGRATULATIONS \n \n";
    		purse = purse -2000;
    	    }
    	    else 
    	    {
    	    	cout << "\n NOT ENOUGH MONEY "<< endl;
			}
		
		}
		else if (w==0)
		{
			q=0;
		}
		else 
		{
			cout << "\n INVALID INTPUT  \n ";
		}
	}
	
	
	q=1; //input for increasing hospital capacity
	w = 0;
	cout << "\n REMAINING FUNDS  = " << purse << endl;
    while (q)
    {
    	cout<< "\n DO YOU WANT TO INCREASE HOSPITAL CAPACITY BY 10 PERSONS ( COST 10000 ) \n ENTER 1 FOR YES AND 0 FOR NO \n ";
    	cin >> w;
    	if (w == 1 )
    	{
    		if (purse >= 10000)
    		{
			q=0;
    		Ch = Ch +10;
    		cout << "\n CONGRATULATIONS \n \n";
    		purse = purse -10000;
    	}
    	else 
    	{
		 cout << "\n NOT ENOUGH MONEY"<< endl;
    	}
		
		}
		else if (w==0)
		{
			q=0 ;
		}
		else 
		{
			cout << "\n INVALID INTPUT  \n ";
		}
	} 
	q=1; //input for increasing hospital capacity
    w = 0;
	cout << "\n REMAINING FUNDS  = " << purse << endl;
    while (q)
    {
    	cout<< "\n DO YOU WANT TO INCREASE TESTING CAPACITY BY 5 PERSON A DAY ( COST 10000 ) \n ENTER 1 FOR YES AND 0 FOR NO \n ";
    	cin >> w;
    	if (w == 1)
    	{
    		if (purse >= 10000)
    		{
			q=0;
    		Ct = Ct +5 ;
    		cout << "\n CONGRATULATIONS \n \n";
    		purse  = purse -10000;
         	}
    	else 
    	{
		    cout << "\n NOT ENOUGH MONEY"<< endl;
    	}
    	
	}
		else if (w==0)
		{
			q=0 ;
		}
		else 
		{
			cout << "\n INVALID OUTPUT  \n ";
		}
	}
	q=1; //input for investment
    w = 0;
	cout << "\n REMAINING FUNDS  = " << purse << endl;
    while (q)
    {
    	cout<< "\n DO YOU WANT TO INVEST ( COST 10000 ) \n ENTER 1 FOR YES AND 0 FOR NO \n ";
    	cin >> w;
    	if (w == 1)
    	{
    		if (purse >= 10000)
    		{
			q=0;
    		Inv = Inv + 10000 ;
    		cout << "\n CONGRATULATIONS \n \n";
    		purse = purse -10000;
        	}
    	else 
    	{
		    cout << "\n NOT ENOUGH MONEY "<< endl;
    	}
    	
	}
		else if (w==0)
		{
			q=0 ;
		}
		else 
		{
			cout << "\n INVALID OUTPUT  \n ";
		}
	}
	
	
}
	       



void finaldisplay (float t1, float t2 , int &purse , int Inv)
{
	int sumT=0,sumI=0,sumH=0,sumD=0;
	for ( int i = t1*10 ; i < t2 * 10 ; i++)
	{
		sumH= sumH + 0.1*_H[i];
		sumD= sumD + 0.1 *_D[i];
		sumT = sumT  +0.1* _T[i];
		sumI = sumI +0.1*_I[i];
	}
	cout << "\n PURSE REMAINING     "<<  purse <<  endl; 
	cout<< "\n TOTAL NO OF DEATHS  =  "<< sumD<< endl;
	cout << "\n FINAL ECONOMIC VALUE = " << Tax(t2 , Inv) *10 ;
	float eg= ((Tax(t2 , Inv) *10.0 - V0)/V0)*100;
	cout <<"\n ECONOMIC GROWTH  = "<< eg<< "%"<< endl;
}
