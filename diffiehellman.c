#include<stdio.h>
#include<gmp.h>
#include<string.h>
#include<stdlib.h>

char * squareandmultiply(char *,char *,char *);
int primalityss(char *);
char * squareandmultiply(char * x, char * y, char * n)
{
	mpz_t z,a,pow,p;
	mpz_init(z);
	mpz_init_set_str(a,x,10);
	mpz_init_set_str(pow,y,10);
	mpz_init_set_str(p,n,10);
	mpz_set_ui(z,(unsigned long int)1);
	unsigned long int len,i;
	char * c=mpz_get_str(NULL,2,pow);
	len=strlen(c);
	for(i=0;i<len;i++)
	{
		mpz_mul(z,z,z);
		mpz_mod(z,z,p);
		if(c[i]=='1')
		{
			mpz_mul(z,z,a);
			mpz_mod(z,z,p);
		}
	}
	char * r=NULL;
	r=mpz_get_str(r,10,z);
	printf("res %s\n",r);
	return r;
}

int primalityss(char * x)
{
	gmp_randstate_t rs;
	long int n,q;
        long int i,j=3;
        char * r = (char *)malloc(10000*sizeof(char));
	unsigned long int c=1,d=0;
	mpz_t a,res,b,p;
	mpz_init(a);
	mpz_init_set_str(p,x,10);
	mpz_init(res);
	gmp_randinit_mt(rs);
	i=mpz_get_ui(p);
	mpz_init_set_ui(b,(i-1)/2);
	for(i=0;i<j;i++)
	{
		mpz_urandomm(a,rs,p);
		if(mpz_cmp_ui(a,d)==0)
		mpz_set_ui(a,c);
		n=mpz_jacobi(a,p);
		r=squareandmultiply(mpz_get_str(NULL,10,a),mpz_get_str(NULL,10,b),mpz_get_str(NULL,10,p));
		if(n<0)
		{
		q=mpz_get_ui(p);
		n=q+n;
		}
		mpz_init_set_str(res,r,10);
		if(n==0 || n!=mpz_get_ui(res))
		{
			return -1;
		}
	}
	return 1;
}

char ** diffiehellman()
{
	char  *j,*i,*pr1,*pr2,*a1,*b1,*d1,*d2;
	char ** r;
	r=(char **)malloc(3*sizeof(char*));
	i=(char*)malloc(10000*sizeof(char));
	j=(char*)malloc(10000*sizeof(char));
	d1=(char*)malloc(10000*sizeof(char));
	d2=(char*)malloc(10000*sizeof(char));
	a1 = (char*)malloc(10000*sizeof(char));
	b1 = (char*)malloc(10000*sizeof(char));
	pr1 = (char*)malloc(10000*sizeof(char));
	int flag=0,ans;
	char *x,*y,*res;
	x = (char*)malloc(10000*sizeof(char));
	y = (char*)malloc(10000*sizeof(char));
	res = (char*)malloc(10000*sizeof(char));
	unsigned long int range;
	mpz_t prime,prime1,d3,d4;
	mpz_t p,g,result;
	mpz_t a,b;
	mpz_t x1,y1;
	mpz_t rand_num;
	mpz_init(p);
	mpz_init(result);
	mpz_init(a);
	mpz_init(b);
	mpz_init(x1);
	mpz_init(y1);
	mpz_init(prime1);
	mpz_init(prime);
	mpz_init(g);
	mpz_init(d4);
	mpz_init(d3);
	gmp_randstate_t rand;
	range = 456789;
	gmp_randinit_mt(rand);
	gmp_randseed_ui(rand,range);
	mpz_init(rand_num);
	mpz_set_ui (d4,2);
	mpz_set_ui (d3,1);
	int flag2=0,flag1 =0;
	int k;
	for(k=0;k<3;k++)
	{
		r[k]=(char *)malloc(10000*sizeof(char));
	}	
	do
	{	

		printf("Enter a prime number p\n");
		scanf("%s",i);
		mpz_init_set_str(p,i,10);		
		ans = primalityss(i);
		if(ans == 1)
		{
			flag2=1;
			gmp_printf ("%Zd is prime \n", p);
			mpz_mul(prime,p,d4);
			gmp_printf("2p = %Zd\n",prime);
			mpz_add(prime1,prime,d3);
			gmp_printf("2p+1 is = %Zd\n",prime1);
			mpz_get_str(pr1,10,prime1);
			ans = primalityss(pr1);
			if(ans == 1)
			{	
				do
				{	
										
					printf("Enter a number for primitive modulo checking less than p :\n");
					scanf("%s",j);
					mpz_init_set_str(g,j,10);					
					printf("\n");
					mpz_powm (result, g,d4,p);
					if(mpz_cmp(result,d3)!=0)
					{
						res = squareandmultiply(j,pr1,i);
						mpz_init_set_str(result,res,10);
						if(mpz_cmp(result,d3)!=0)
						{
							flag= 1;						
							gmp_printf("%Zd is primitive modulo\n",g);
							mpz_urandomb(a,rand,19);
							mpz_get_str(a1,10,a);
							//gmp_printf ("%Zd is alice random number \n", a);
							mpz_urandomb(b,rand,10);
							mpz_get_str(b1,10,b);
							//gmp_printf ("%Zd is bob random number \n", b);
						}
						else
						{
							gmp_printf("%Zd is not primitive modulo \n",g);
						}
					}
					else						
					{
						gmp_printf("%Zd is not primitive modulo \n",g);
					}
				}while(flag!=1);
			}
			else
			{
				printf("Enter other number as 2p+1 is not prime\n");
				exit(1);
			}
		}
		else
		{
			gmp_printf("Enter other number as %Zd is not prime :\n",p);
		}
	}while(flag2 !=1);
	x = squareandmultiply(j,a1,i);
	mpz_init_set_str(x1,x,10);
	gmp_printf ("Alice computes = %Zd \n", x1);
	y = squareandmultiply(j,b1,i);
	mpz_init_set_str(y1,y,10);
	gmp_printf ("Bob computes = %Zd\n", y1);
	res = squareandmultiply(y,a1,i);
	mpz_init_set_str(result,res,10);
	printf("Alice and Bob share secret :\n" );
	gmp_printf ("Alice secret = %Zd\n", result);
	strcpy(r[0],mpz_get_str(NULL,10,result));
	res = squareandmultiply(x,b1,i);
	mpz_init_set_str(result,res,10);
	gmp_printf ("Bob secret = %Zd\n", result);
	strcpy(r[1],mpz_get_str(NULL,10,result));
	gmp_randclear (rand); 
	return r;
}
