#include <math.h>

int satisfies(int a, int b, int c) {
   int result;
int modmin=0;
int sum2=0;
int max=0;
int min=0;

if (a<0 && b<0 && c<0)
   {
       if (a<b && a<c)
       {
           modmin=abs(a);
           sum2=b+c;
       }
       else if (b<a && b<c)
       {
         modmin=abs(b);
           sum2=a+c;
       }
       else if (c<a && c<b)
       {
         modmin=abs(c);
           sum2=a+b;
       }
       else
       {
           result=0;
       }


if (sum2<-256 &&
       modmin==1,2,4,8,16,32,64,128,256 &&
       modmin<256)
       {
           result=1;
       }


    else if (fabs(sum2)>16 || modmin>8)
        {
            result=1;
        }

    else
    {
        result=0;
    }
   }


else if (a<0 || b<0 || c<0)
{
    if (a<0 && b>=0 && c>=0) {
    if (a>-256)
       {
           result=1;
       }
    else
    {
        result=0;
    }
}
}
else if (a>=0 && b<0 && c>=0) {
     if (b>-256)
       {
           result=1;
       }
    else
    {
        result=0;
    }
}
else if (a>=0 && b>=0 && c<0) {
     if (c>-256)
       {
           result=1;
       }
    else
    {
        result=0;
    }
}


else if (a<0 && b<0 && c>=0)
    {
        if (((a+b)*(1+2))>-256)
        {
            result=1;
        }
        else
        {
            result=0;
        }
    }
else if (a<0 && b>=0 && c<0 )
    {
        if (((a+c)*(1+2))>-256)
        {
            result=1;
        }
        else
        {
            result=0;
        }
    }
else if (c<0 && b<0 && a>=0)
    {
         if (((c+b)*3)>-256)
            {
                result=1;
            }
          else
        {
            result=0;
        }
    }


else if (a>=0, b>=0, c>=0)
    {
       if (a>c && a>b)
       {
           max=a;
       }
       else if (b>c && b>a)
       {
           max=b;
       }
       else if (c>a && c>b)
       {
           max=c;
       }
       else
       {
           result=0;
       }

    }
if ((max+min)<256)
{
    result=1;
}
else
{
    result=0;
}

   return result;
}

