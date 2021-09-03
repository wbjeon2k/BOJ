#### 1. Types of bit operations
Bit by bit AND : `A & B`. For example, `(3 & 1) == 1`  
Bit by bit OR : `A | B`. For example, `(1 | 0) == 1`  
Bit by bit XOR : `A ^ B`  
Bit by bit NOT : `~A`  

Left shift B bits : `A << B`  
  - Left shift is equivalent to multiplying by $2^B$.  
  - `eg) (2<<1) == 4`  

Right shift B bits : `A >> B`  
  - Right shift is equivalent to dividing by $2^B$.  
  - `eg) (8>>1) == 4`

*Beware that **left & right shift returns an integer**, not a boolean value!*

#### 2. Usage with examples.

Bit masking is used to represent a set and manipulate them.  
We can represent a set of `32` elements with a `32` bit integer `int`.  
We can turn on the bit if it is in the set, turn off if it is not.  

For example, `int Set = 2;` means that the 2nd element is in the set (turned on),  
and every other elements are not in the set(turned off).  

Imagine a pizza store with `20` toppings, from topping number from `0` to `19`.  

1. Full set. a.k.a All the toppings  
`int fullPizza = (1<<20) - 1;`  
To represent a pizza with every `20` toppings, turn on the `20` least significant bits.  
`0` represents an empty set, because every bits are turned off!  
2. Add an element. a.k.a Add pepperoni `p`  
To add the `p`th topping, you can turn on the `p`th least significant bit.  
`toppings |= (1<<p);`  
4. Check an element.  
`if(toppings & (1<<p)) cout << "pepperoni is in!" << endl;`
5. Remove an element.  
`toppings &= ~(1 << p);`  
Why does it works?  
`~(1 << p);` generates an integer with all bits on except the `p`th.  
Bit by bit AND operation keeps all other states, and always turn off the `p`th bit.  
6. Toggle  
Turn off the bit if it is on,  
turn on the bit if it is off.  
Using the XOR operation, it is very easy to make.  
`toppings ^= (1 << p);`  
7. Set operations  
`int Union = (A | B);` : Gets the union of A and B.  
`int Intersection = (A & B);` : Gets the intersection of A and B.  
`int Removed = (A & ~B);` : Equivalent to `A - B`.  
`int toggled = (A ^ B);` : Get elements either in A or B, **but not both**.  
8. Counting the size of the set  
Check if the `i`th bit is turned on. For example:  
```
int SET;
int set_size =0;
for(int i=0;i<size;++i){
  if(SET % 2) ++set_size;
  // check the least significat bit is on.
  // if it is on, add the size.
  set_size >> 1;
  // remove the least significant bit.
}
```
9. Iterating every subset  
For example, if we want to iterate all the subsets of `pizza = {cheese, pepperoni}`,  
we might want to iterate ` {cheese}, {cheese, pepperroni}, {pepperoni} `.  
This is how we do it.  
```
for(int subset = pizza ; subset ; subset = ((subset-1) & pizza) ){
  // iterate through all subsets
}
```
