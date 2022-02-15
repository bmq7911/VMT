
func main( 	i32 argc, i32 argv)->i32{
	i32 sum = argc + argv;
	i32 a,b,c,d,e,f,g,h;
	a,b+c,e+f,g*h;
	bool bInit = false;

	for ( i32 t = 10; t + 100; t = t + 1 ){
		sum = sum + 2;
		if( sum == 100 ){
			break;
		}
		else{
			sum = sum + 3;
			continue;
		}
	}
	
	if( a == 10 ){
		a = a + 1;
	}
	else if( a == 20 ){
		a = a + 2;
	}
	else if( a == 30 ){
		a = a + 3;
	}
	else {
		a = a + 4;
	}
	
	if( bInit ) {
		return argc + argv;
	}
	else{
		return argc * argv;
	}
	
	do{
		i32 t   =  g + (a + b+ c);
		g = g + t;
		
		if( g > 10 ){
			break;
		}
		else{
			while( t < 100 ){
				if( t == 99 ){
					t = t * 100;
					break;
				}
				else{
					t = t * 101;
					continue;
				}
			}
		
			continue;
		}
	}while( bInit );
	
}
