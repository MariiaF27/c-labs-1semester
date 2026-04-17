#include <stdio.h>
#include <limits.h>

int main()
{
        int i;
        int reverse(int n)
        {
                int reverse_n=0;
                while(n!=0)
                {
                        reverse_n*=10;
                        reverse_n+=n%10;
                        n/=10;
                }
                return reverse_n;
        }
        int square_reverse(int reverse_n)
        {
                int reverse_n2=0;
                int n2;
                n2=reverse_n*reverse_n;
                while(n2!=0)
                {
                        reverse_n2*=10;
                        reverse_n2+=n2%10;
                        n2/=10;
                }
                return reverse_n2;
        }
        for(i=1;i<=INT_MAX;i++)
        {
                if(i*i==square_reverse(reverse(i)))
                {
                        printf("%d\t",i);
                }
                if(i*i>=INT_MAX-2*i)
                {
                        printf("Limit reached:%d\n",i);
                break;
                }
        }
        return 0;
}
