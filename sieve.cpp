#include<bits/stdc++.h>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> smallestPrime;
    vector<int> primes;

     for (int p = 2; p < n; p++) {
        smallestPrime[p] = p;
     }

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                smallestPrime[i] = p;
                isPrime[i] = false;
            }
        }
    }

    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            primes.push_back(p);
        }
    }
  return primes;
}


//--------------------------- 


// unordered_set<int> getPrimeFactors(int n){
//     unordered_set<int> factors;
//         while(n > 1) {
//             factors.insert(smallestPrime[n]);
//             n /= smallestPrime[n];
//         }
//  return factors;
// }


//-----------------------------------------

//Euler Totient function - return count of relatively coprimes in [1,n)
// ...... O(sqrt(n))
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// -------------------------------------------

//Euler Totient function for all numbers in 1 to n
// ...... O(n * log(log(n)))
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

// ------------------------------------------


int main()
{
    // vector<int> primes = sieveOfEratosthenes(1000);
    for(int i=0; i<=20; i++) {
        cout<<i<<" "<<phi(i)<<endl;
    }
    return 0;
}
