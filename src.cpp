#include <bits/stdc++.h>
#include <chrono> 
#include <random> 
 

int randint(std::mt19937_64& rng, int lbound, int ubound) 
{ 
    return rng() % (ubound - lbound + 1) + lbound; 
} 
using namespace std;


vector<long long>primes;
vector<char>buffer_characters={'!','@','#','$','%','^','&','*','(',')','-','_','+','=','}','{','|','`'};

vector<char>random_characters={'1','2','3','4','5','6','7','8','9','0','-','_','+','=',')','(','*','&','^','%','$','#','@','!','q','w','e','r','t','y','u','i','o','p','[','{','}',']','|','a','s','d','f','g','h','j','k','l',';',':','z','x','c','v','b','n','m','<','>','?','/'};
vector<long long> sieve(int n) {
    int*arr = new int[n + 1](); 
    vector<long long> vect; 
    for (int i = 2; i <= n; i++)
        if (arr[i] == 0) {
            vect.push_back(i); 
            for (int j = 2 * i; j <= n; j += i)
                arr[j] = 1;
        } 
    return vect;
}


long long binpow(long long a, long long b,long long m) {
    if (b == 0){
        return 1;
    }
    long long res = binpow(a, b / 2,m)%m;

    if (b & 1){
        return (res*res*a)%m;
    }
    else{
        return (res*res)%m;
    }
}

long long diffie_hellman(long long G,long long a,long long b){
    long long int P, x, y, ka, kb;
    P=7919;
    x = binpow(G, a, P);
    y = binpow(G, b, P); 
    ka = binpow(y, a, P); 
    kb = binpow(x, b, P); 
    // cout << ka << " " << kb << endl;
    return ka;

}


string add_buffer(long long key){
    long long inverted_number=0;
    long long buffer_characters_count=buffer_characters.size();
    string buffer_string="";
    for (int i=62;i>=0;i--){
        if ((key>>i) & 1){
        }
        else{
            inverted_number+=(1LL<<i);
        }
    }
    long long diff=key-inverted_number;
    if (diff<0){
        diff*=-1;
    }
    long long start_index=inverted_number%buffer_characters_count;
    long long end_index=diff%buffer_characters_count;
    buffer_string+=buffer_characters[start_index];
    // cout << buffer_characters[start_index] << " " << buffer_characters[end_index] << endl;
    int random_number=rand();
    random_number%=25;
    while(random_number>0){
        int l=0;
        int r=random_characters.size();
        int idx=rand();
        idx%=random_characters.size();
        if (random_characters[idx]!=buffer_characters[start_index] && random_characters[idx]!=buffer_characters[end_index]){
            buffer_string+=random_characters[idx];
            random_number--;
        }


    }
    buffer_string+=buffer_characters[end_index];




    


    return buffer_string;


}


vector<char> calculate_start_and_end(long long key){
    long long inverted_number=0;
    long long buffer_characters_count=buffer_characters.size();
    string buffer_string="";
    for (int i=62;i>=0;i--){
        if ((key>>i) & 1){
        }
        else{
            inverted_number+=(1LL<<i);
        }
    }
    long long diff=key-inverted_number;
    if (diff<0){
        diff*=-1;
    }
    long long start_index=inverted_number%buffer_characters_count;
    long long end_index=diff%buffer_characters_count;
    return {buffer_characters[start_index],buffer_characters[end_index]};
}


string encrypt(string message,long long key){
    int n=message.length();
    int primes_count=primes.size();
    string encrypted_text="";
    int j=0;
    long long current_index=key+((key>>j & 1)<<(j));
    long long skips=key+((key>>j & 1)<<(j));
    current_index=current_index%primes_count;
    int i=0;
    // encrypted_text+=add_buffer(skips);
    while(i<n){
        long long multiplication=primes[current_index]*int(message[i]);
        string multiplication_string=to_string(multiplication);
        encrypted_text+=multiplication_string;
        encrypted_text+=add_buffer(skips);
        j++;
        i++;
        if (j==63){
            j=0;
        }
        skips=key+((key>>j & 1)<<(j));
        current_index+=skips;
        current_index=current_index%primes_count;

    }
    return encrypted_text;


}

string decrypt(string cypher,long long key){
    int n=cypher.length();
    int primes_count=primes.size();
    string decrypted_text="";

    int j=0;
    long long current_index=key+((key>>j & 1)<<(j));
    long long skips=key+((key>>j & 1)<<(j));
    current_index=current_index%primes_count;
    int i=0;
    string num="";
    while(i<n && cypher[i]>='0' && cypher[i]<='9'){
        num+=cypher[i];
        i++;

    }
    // cout << num << endl;
    long long d=stoll(num);
    long long current_prime_number=primes[current_index];
    d=d/current_prime_number;
    decrypted_text+=char(d);
    vector<char>start_and_end=calculate_start_and_end(skips);
    // cout << start_and_end[0] << " " << start_and_end[1] << endl;
    while(cypher[i]!=start_and_end[1]){
        i++;
    }
    i++;
    while(i<n){
        string num="";
        while(i<n && cypher[i]>='0' && cypher[i]<='9'){
            num+=cypher[i];
            i++;
        }
        // cout << num << endl;
        long long number=stoll(num);
        j++;
        if (j==63){
            j=0;
        }
        skips=key+((key>>j & 1)<<(j));
        current_index+=skips;
        current_index=current_index%primes_count;
        long long current_prime_number=primes[current_index];
        number=number/current_prime_number;
        decrypted_text+=char(number);
        start_and_end=calculate_start_and_end(skips);
        // cout << start_and_end[0] << " " << start_and_end[1] << endl;
        while(cypher[i]!=start_and_end[1]){
            i++;
        }
        i++;

    }
    return decrypted_text;



}










int main()
{
    int N=1e6;
    primes=sieve(N);
    unsigned long long key=diffie_hellman(7911,1567689892,292787734);
    string message="";
    string curr;
    while(getline(cin,curr)){
        message+=curr;
        message+="\n";

    }
    string encrypted_text=encrypt(message,key);
    cout << encrypted_text << endl;
    string decrypted_text=decrypt(encrypted_text,key);
    cout << decrypted_text << endl;

    return 0;
}
