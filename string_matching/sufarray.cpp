// Solution to substr using suffix arrays.
// David Garcia Soriano.
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int maxlen = 40000;
char str[maxlen + 2];
int n, mintimes;

int suf[maxlen], llcp[maxlen], rlcp[maxlen], hgt[3 * maxlen];
bool bh[maxlen + 1], b2h[maxlen + 1];

int hoja;

int lcp(int a, int b) {
  if (a == b) return n - suf[a];

  a += hoja + 1; b += hoja;
  int res = min(hgt[a], hgt[b]);
  while (a >> 1 != b >> 1) {
    if (!(a & 1)) res = min(res, hgt[a + 1]);
    if (b & 1) res = min(res, hgt[b - 1]);
    a >>= 1; b >>= 1;
  }
  return res;
}


/* Calcula llcp[m] = lcp(sufijo l, sufijo m) y rlcp = lcp(sufijo m, sufijo r), donde (l, m, r)
 * son los valores que pueden aparecer en una búsqueda binaria y los sufijos están ordenados
 * lexicográficamente. Además devuelve lcp(sufijo l, sufijo r) */
int calclcp(int l, int r) {
  if (r - l > 1) {
    int m = (r + l) / 2;
    return min(llcp[m] = calclcp(l, m), rlcp[m] = calclcp(m, r));
  } else return hgt[hoja + r];
}

/* El interval tree tiene n - 1 hojas que contienen los valores de
 * lcp(cad + suf[i - 1], cad + suf[i]), i = 1..n - 1 */
void preprocesa(char *cad) { // asume caracteres <= 127 (si no usar unsigned char)
  int i, j, t;
  hoja = 1;            // posición de la primera hoja en el interval tree
  while (hoja < n - 1) hoja <<= 1;
  hoja--;                           // resta 1 para poder indexar el árbol por 1

  // Bucket sort por la primera letra
  int *prm = llcp, *cnt = rlcp;        // utiliza arrays que por ahora no hacen falta
  memset(cnt, 0, 128 * sizeof(*cnt));
  memset(b2h, 0, (n + 1) * sizeof(*b2h));
  fill(&hgt[0], &hgt[hoja + n], n + 1);
  for (i = 0; i < n; i++) cnt[cad[i]]++;
  for (i = 1; i < 128; i++) cnt[i] += cnt[i - 1];
  for (i = n - 1; i >= 0; i--) suf[prm[i] = --cnt[cad[i]]] = i;
  bh[0] = bh[n] = true;
  for (i = 1; i < n; i++) if (bh[i] = cad[suf[i]] != cad[suf[i - 1]]) hgt[hoja + i] = 0;
  for (i = (hoja + n - 1) >> 1; i > 0; i--) hgt[i] = min(hgt[i << 1], hgt[(i << 1) + 1]);

  /* En cada iteración, los sufijos están ordenados según el orden parcial de los H
   * primeros elementos */
  for (int h = 1; h < n; h <<= 1) {
    for (i = 0; i < n; i++) { cnt[i] = 0; if (!bh[i]) prm[suf[i]] = prm[suf[i - 1]]; }

    /* prm[i] contiene la posición de inicio del 2H-bucket que contiene a cad + i;
     * si cad + suf[i] es el primero de un 2H-bucket, cnt[i] es el tamaño del bucket;
     * si cad + suf[i] es el primero de un 2H-bucket, bh[i] = true */
    int l = 0; // inicio del H-bucket actual
    for (i = n - h; i < n; i++)  b2h[prm[i] += cnt[prm[i]]++] = true;
    for (i = 0; i < n; i++) { // índice en suf 
      if ((t = suf[i] - h) >= 0) b2h[prm[t] += cnt[prm[t]]++] = true;
      if (bh[i + 1])  // suf[i] es final de bucket
        for (; l <= i; l++)
          if ((t = suf[l] - h) >= 0 && b2h[prm[t]]) 
            for (j = prm[t] + 1; j < n && !bh[j] && b2h[j]; j++)
              b2h[j] = false;
    }
    for (i = 0; i < n; i++) suf[prm[i]] = i;
    
    // Si la height es < h, está bien puesta
    for (i = 1; i < n; i++) {
      if (b2h[i] && !bh[i]) { // hay que recalcular height del sufijo suf[i]
        int a = suf[i - 1] + h, b = suf[i] + h;
        if (a >= n || b >= n) hgt[hoja + i] = h;
        else {
          a = prm[a]; b = prm[b];
          if (a > b) swap(a, b);
          // Calcula minheight(a + 1, b)
          hgt[hoja + i] = lcp(a, b) + h;
        }
        for (a = (hoja + i) >> 1; a > 0; a >>= 1) hgt[a] = min(hgt[2 * a], hgt[2 * a + 1]);
      }
      bh[i] = b2h[i];
    }    
  } 
  calclcp(0, n - 1);  // calcula llcp y rlcp
}

int main() {
  while (scanf("%i\n", &mintimes), mintimes) {
    gets(str);
    n = strlen(str);
    preprocesa(str);

    int longest = 0;
    for (int i = 0; i <= n - mintimes; ++i)
      longest = max(longest, lcp(i, i + mintimes - 1));

    int best = -1;
    for (int i = 0; i < n;) {
      if (suf[i] + longest > n) { ++i; continue; }

      int pos = 0, j = i;
      while (j < n && lcp(i, j) >= longest) {
        pos = max(pos, suf[j]);
        ++j;
      }
      if (j - i >= mintimes) best = max(best, pos);
      i = j;
    }
    if (longest == 0) puts("none");
    else printf("%i %i\n", longest, best);
  }
  return 0;
}
