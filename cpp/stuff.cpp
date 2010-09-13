//Inserta un elemento (n) en un vector ordenado conservando el orden
    vector.insert(lower_bound(all(vector),n),n);
// Quita todos los espacios de un string
    while(s.find(" ") != string::npos) s.replace(s.find(" "), 1, "");
// Interseccion entre dos sets. Saca los elementos comunes a otro contenedor
    set_intersection(all(nums),all(pares),inserter(both,both.end())); //A un set
    set_intersection(all(nums),all(pares),back_inserter(vector));       //A un vector

//Convierte un numero N en base B a decimal
int toDecimal(int n, int b){
    int result=0, multiplier=1;
    while(n>0){
	result += (n%10 * multiplier);
	multiplier *= b;
	n/=10;
    }
    return result;
}
//En Java se puede utilizar: return Integer.parseInt(""+n,b);

//Retorna un numero N (decimal) en una base B
int fromDecimal(int n, int b){
    int result=0, multiplier=1;
    while(n>0){
	result+= (n%b * multiplier);
	multiplier *= 10;
	n/=b;
    }
    return result;
}

//Para bases >= 10
string fromDecimal2(int n, int b){
    string chars="0123456789ABCDEFGHIJ", result = "";
    while(n>0){
	result=chars[n%b] + result;
	n/=b;
    }
    return result;
}
