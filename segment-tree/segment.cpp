/*
como cuestion util vale la pena mencionar que todo arbol binario se puede representar en un arreglo de la siguiente manera:
la raiz es el elemento en posicion 0
el hijo izquierdo de un nodo en posicion x es x * 2 + 1
el hijo derecho de un nodo en posicion x es x * 2 + 2
de esta manera no necesitamos usar mas que un arreglo para almacenar nuestro segment tree, que es un arbol binario

este segment tree tiene dos operaciones
update(pos, by): actualiza el arbol de manera que el elemento de la lista de numeros (no del arbol) en posicio pos 
		 aumente en un valor igual a by
sum(from, to): determina la suma de los elementos en la lista de numeros en el intervalo [from, to]

lo importante del segment tree es que permite hacer en tiempo log(n) muchas operaciones que suelen ser lineales y no es dificil de implementar
*/

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

//numero maximo de elementos en la lista de numeros
#define N 200000 

int tree[N * 4]; //se necesita menos de N * 4 nodos para representar una lista de numeros de tamaño N, pero este numero es adecuado
int n; //numero de elementos en el input

//actualiza en el arbol un valor de la lista de numeros
void update(int pos, int by){
	int node = 0, left = 0, right = n - 1; //intervalo inicial [0, n -1]

	while(left != right){ //mientras tengamos que dividir el intervalo actual
		tree[node] += by;
		int mid = (left + right) / 2;
		if(pos <= mid){
			node = node * 2 + 1; //hijo de la izquierda [left, mid]
			right = mid;
		}else{
			node = node * 2 + 2; //hijo de la derecha [mid + 1, right]
			left = mid + 1;
		}
	}

	tree[node] += by;
}

/*
determina la suma de los elementos del intervalo [from, to]
la funcion es tal que node representa el intervalo [left, right] y [from, to] siempre es subconjunto de [left, right]
*/
int sum(int from, int to, int node = 0, int left = 0, int right = n - 1){
	if(from == left && to == right) // si el segmento [left, right] es parte de lo que queremos sumar
		return tree[node];

	int mid = (left + right) / 2;
	int res = 0;
	
	if(from <= mid) //si necesitamos ir por la izquierda
		res += sum(from, min(to, mid), node * 2 + 1, left, mid);

	if(to > mid) //si necesitamos ir por la derecha
		res += sum(max(mid + 1, from), to, node * 2 + 2, mid + 1, right);

	return res;
}

//inicializa todo el arbol con cero
int init(){
	for(int i = 0; i < 4 * n; i++) tree[i] = 0;
}

int main(){
	cin >> n; //se lee el numero de elementos
	init();
	
	for(int i = 0; i < n; i++){ //se lee la lista de numeros
	 int x; scanf("%d", &x);
	 update(i, x);
	}
	
	int a, b;
	while(cin >> a >> b){ //se lee muchos queries del tipo 'a b' y se imprime la suma del intervalo [a, b]
		cout << sum(a, b) << endl;
	}
}
