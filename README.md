

# description	

sequence of parabolic points on the boundary of main cardioid tending to 1/3 

see:
* [wikibooks](https://en.wikibooks.org/wiki/Fractals/Mathematics/sequences#sequence_of_parabolic_points_on_the_boundary_of_main_cardioid)




# functions

## Give_t


$`t = \sum_{ k \mathop =1}^n \frac{3}{10^k}`$



```c
double Give_t(int nMax){

	double t = 0.0; // = p/q 
	// ratio
	long long  int p = 3; // numerator of t
	long long int q = 10; // denominator of t
	
	int n = 1;
	
	
	// bounds check 
	if (nMax < 1) {printf(" error nMax < 1 \n"); return t;}
	if (nMax > 20) {printf(" error nMax > 20 \n"); return t;}
	
	while ( n< nMax){
		
		p = p + 3*q;
		q = q*10;
		n++;
	
	
	}
	 
	t = (double)p/q; // compute floating point value 
	printf( "for n = %2d  p/q = %18Ld / %18Ld  \tt =  %.16f \n",n, p, q, t); 
	
	
	return t; 
}

```



Results:
```bash
for n =  1  p/q =                  3 /                 10  	t =  0.3000000000000000 
for n =  2  p/q =                 33 /                100  	t =  0.3300000000000000 
for n =  3  p/q =                333 /               1000  	t =  0.3330000000000000 
for n =  4  p/q =               3333 /              10000  	t =  0.3333000000000000 
for n =  5  p/q =              33333 /             100000  	t =  0.3333300000000000 
for n =  6  p/q =             333333 /            1000000  	t =  0.3333330000000000 
for n =  7  p/q =            3333333 /           10000000  	t =  0.3333333000000000 
for n =  8  p/q =           33333333 /          100000000  	t =  0.3333333300000000 
for n =  9  p/q =          333333333 /         1000000000  	t =  0.3333333330000000 
for n = 10  p/q =         3333333333 /        10000000000  	t =  0.3333333333000000 
for n = 11  p/q =        33333333333 /       100000000000  	t =  0.3333333333300000 
for n = 12  p/q =       333333333333 /      1000000000000  	t =  0.3333333333330000 
for n = 13  p/q =      3333333333333 /     10000000000000  	t =  0.3333333333333000 
for n = 14  p/q =     33333333333333 /    100000000000000  	t =  0.3333333333333300 
for n = 15  p/q =    333333333333333 /   1000000000000000  	t =  0.3333333333333330 
for n = 16  p/q =   3333333333333333 /  10000000000000000  	t =  0.3333333333333333 

```




# License

This project is licensed under the  Creative Commons Attribution-ShareAlike 4.0 International License - see the [LICENSE.md](LICENSE.md) file for details  

# technical notes
GitLab uses:
* the Redcarpet Ruby library for [Markdown processing](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md)
* KaTeX to render [math written with the LaTeX syntax](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md), but [only subset](https://khan.github.io/KaTeX/function-support.html)




## Git
```
cd existing_folder
git init
git remote add origin git@gitlab.com:adammajewski/sequence_of_parabolic_points_on_the_boundary_of_main_cardioid_3.git
git add .
git commit -m "Initial commit"
git push -u origin master
```
