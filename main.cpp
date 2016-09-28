#include <iostream>
#include <vector>
#include "bigint.h"
#include <memory.h>
#include <fstream>
#define MAX_SIZE 200000000
using namespace std;

bool prime[MAX_SIZE];
//int Location[MAX_SIZE+1];

bool violent(bint n){
    if(n == 2){
        return true;
    }
    bint max_factor = n.sqrt();
    bint i = 2;
    while(i <= max_factor){
        if((n % i) == 0)
            return false;
        i = i + 1;
    }
    return true;
}

long long sieve(long long n) {
    memset(prime, 1, sizeof(prime));
    prime[0]=false;
    prime[1]=false;
    long long total = 0;
    long long max_factor = n * 20;
    for (long long i=2;  i < max_factor;  i++){
        if (prime[i]) {
            for (long long k=i + i; k < max_factor; k+=i){
                prime[k]=false;
            }
            total ++;
            if(total == n)
                return i;
//            cout<<i<<endl;
        }
    }
}


bint getPrime(string k){ //output the k th prime
    bint n(k);
    if(n > 10000000){
        bint now = 179424673;
        bint total = 10000000;
        int m = 0;
        while(total < k){
            if(violent(now)){
                total = total + 1;
                m += 1;
//                if (m % 100 == 0)
//                    cout<<now.toString()<<endl;
            }
            now = now + 1;
        }
        return now - 1;
    }
    else{
        long long n;
        stringstream ss;
        ss<<k;
        ss>>n;
        bint ans(sieve(n));
        return ans;
    }
}

int main()
{
    ofstream out("out.txt");
    if (out.is_open())
    {
//        cout<<getPrime("10000").toString()<<endl;
        out << getPrime("10000").toString()<<endl;
        out << getPrime("100000").toString()<<endl;
        out << getPrime("1000000").toString()<<endl;
        out.close();
    }

    return 0;
}
