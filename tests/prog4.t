{
	int BLANK; int TAB; int NEWLINE; int peek; int line; int readch;

	while( true ) {
		if( peek == BLANK || peek == TAB )
			;
		else
			if( peek == NEWLINE ) 
				line = line + 1;
			else
				
			break;
		peek = readch;
	}
}
/// 把函数作为核心,
const f32 g = 9.8;

f32 x = func( f32 x)->x;


f32 x = func( f32 t )->0.5 * g * t * t;

// if else 语句是合理的
f32 f = func(f32 x ){ 
	return  3 * x + x * x + 4;
}


f32 sin = func(f32 x )-> x * x - 3 *x + 9;

f(sin(10))
/// 可以被传递
f32 f = func( f32 x )-> 3 *x + x * x + 4;
f32 f = func( f32 x, f32 y )-> sin(x,x +y);
f32 g = func(f32 x)-> f( x, 1);

f = grad[f,x]
f = grad[f,y]
f = grad[f,y]


f = func(f32 x,f32 y)-> sin( x ,1)->cos(y, . )->g( . ) /// g( cos(y,sin(x,1))


class vec{
public:
	
private:
	f32 x,y,z;
};

class Obj{

	

};