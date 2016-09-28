# BigPrimeNumber
MSRA homework, implement a big integer packet and generate the k th prime.
Personal Project Report
By Yutai Hou 


Contents
Personal Project Report	1
By Yutai Hou	1
1.	Big Integer Packet Design: Implement & optimization	1
1.1	Implemented functions	1
1.2	Use vector< int > as the data structure of big integer	1
1.3	Use 1 billion decimal rather than 2^31	1
1.4	The application of binary search	2
2.	Prime generator: Implement & optimization	2
2.1	Combination of violence and sieve method	2
2.2	Optimization of sieve method	2
3	Result of 10000th ,100000th ,1000000th	2
3.1     Prime result:	2
3.2	Time cost:	3



1.	Big Integer Packet Design: Implement & optimization
1.1	Implemented functions
a.	Override of +, -, *, /, %, >, <, >=, <=, =, == (for both big integer type and int type)
b.	Root function sqrt(), Shift function.
c.	Constructor with string, vector, int type.
1.2	Use vector< int > as the data structure of big integer
1)	Good space efficiency
Because an “int” can represent 2^31 different numbers, so by using “int” in each position, we can get a maximum of 2^31 decimal integer, which is only 10 decimal integer when using string as data structure.
2)	Good time efficiency
One of the most expensive operations is multiplication, which is difficult to optimize. With the help of vector< int >, the big integer is divided into several big block. That is quicker than doing the multiplication digit by digit.
1.3	Use 1 billion decimal rather than 2^31 
1)	Output efficiency
We have transform big integer back into string. With the decimal number divisible by 10, the transformation become just a matter of adding “0”. This is a great advantage, comparing to other decimal number choice. Because the other choices have to experience a complex calculation of transformation.
2)	Enough space efficiency
1 billion is the max decimal number divisible by 10, which offers enough digital representation capability.
1.4	The application of binary search
I used this algorithm in the division and root operations. And of course, these contribute great improvement dealing with large size input.
2.	    Prime generator: Implement & optimization
2.1	Combination of violence and sieve method
Tradeoff between time and space. The time complexity of violence is too high, and the sieve method is limited by space. Therefore, we adopt the method of screening in space to allow the use of the premise of the possible
2.2	Optimization of sieve method
The time complexity is reduced to O (n) by using the Euler method, which is 
O(n Log Log n) in normal model. And certainly, I used the sqrt to reduce search space either.

3	Result of 10000th ,100000th ,1000000th 
3.1	Prime result:
 
3.2	Time cost:
 
