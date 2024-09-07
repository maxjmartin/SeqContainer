# SeqContainer
The SeqContainer class implements an expression template for general math operations.

It is part of a massive rework I am doing to try and get my arbitrary math lib, at least some what comparative with Boost Multiprecision.   

Testing 1,000,000,000 an addition calculation on my machine took 225220389200ns, or 3 minutes 45.22 seconds.  The limiting factor being it caused my machine to exceed its 16 gig of ram.   But most of that was two for loops placing elements into two `std::vector<double>`s.  Once the actual calculation started, ram was no longer pegged.  

As an example this expression `m += (n * n * n) / m;` run 1,000,000,000 times executed in 266046394600ns. Not that far off of the single `m  += n` expression.  But ram was pegged during that calculation.  

Any feedback or recommendations are welcome.  

Example runtime are below.  

```
number_of_elms = 10          calc at = 1300ns
number_of_elms = 100         calc at = 2300ns
number_of_elms = 1000        calc at = 10200ns         Thousands
number_of_elms = 10000       calc at = 70000ns
number_of_elms = 100000      calc at = 399000ns
number_of_elms = 1000000     calc at = 2372100ns       Millions
number_of_elms = 10000000    calc at = 22046100ns
number_of_elms = 100000000   calc at = 233425600ns
number_of_elms = 1000000000  calc at = 225220389200ns  Billions
```

The test code I ran.
```
Oliver::SeqContainer<double> m = {};
Oliver::SeqContainer<double> n = {};

int number_of_elms = 10;
//int number_of_elms = 100;
//int number_of_elms = 1000;          // Thousands
//int number_of_elms = 10000;
//int number_of_elms = 100000;
//int number_of_elms = 1000000;       // Millions
//int number_of_elms = 10000000;
//int number_of_elms = 100000000;
//int number_of_elms = 1000000000;    // Billions

m.reserve(number_of_elms);
n.reserve(number_of_elms);

for (int i = number_of_elms; i > 0; --i) {
    m[i] = (i + 4.0 * 5.0) / 3.0;
}
for (int i = 0; i < number_of_elms; ++i) {
    n[i] = i;
}

fmt::println("Executing Calculation");
auto start = std::chrono::system_clock::now();

m += n;

auto end = std::chrono::system_clock::now();

auto elapsed_time = duration_cast<std::chrono::nanoseconds>(end - start).count();
fmt::println("Elapsed Time = {}ns", elapsed_time);
```