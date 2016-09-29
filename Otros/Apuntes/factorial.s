Fact iterativa

int fact(ind d)
{
	int res;
	for(res=1; d>0, res*= d)
	return res;
}

Toda las funciones recursivas de cola pueden convertirse en iteraciones. Una funcion es recursiva de cola (tail recursive) si:
	- devuelve una exprension simple
	- deuvelve invocaciones a si misma pero sin operaciones posteriores a la invocacion
	
Ej:
int fact(ind d)
{
	id(d==0) return 1;
	else return d*fact(d-1)
}

No es recursiva de cola ya que tiene operaciones posteriores a la invocacion

Una forma de escribir fact para que sea tail recursive es:

inf factr(int d, int res)
{
	if (d==0) return 1
	else return factr(d-1, res*d)
}

fact(n) = factr(n, 1), donde fact(n) es una recursive tail

Como convertimos factr en una iteracion:
inf facti(ind d, int res)
{
	while(d!=0)
	{
		res*=d;
		d--;
	}
	return res;
}
fact(n) = facti(n, 1), donde facti(n) es recursive tail


