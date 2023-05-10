#include <iostream>
#include <string>
using namespace std;

struct binTree {
    char a;
    binTree *left, *right;
};

string al(string str){// remove spaces and ()
    string crt = "", ntw = ""; int l = 0; bool t = true;
    /* delete */
    for (int i=0; i<str.length(); i++)
        if (str[i] != ' ') crt+=str[i];
    /* check to () */
    if (crt[0] == '(' && crt[crt.length()-1] == ')'){
    /* counting () */
    for (int i=1; i<crt.length()-1; i++){
        if (crt[i] == '(') l++;
        if (crt[i] == ')') l--;
        if (l < 0) {t = false; break;}
        ntw += crt[i];}}
    else t = false;
    /*removing ()*/
    if (l==0 && t) return ntw;
    return crt;}

binTree *add(binTree *rt, string st) {
    string str = al(st);
    /* malloc pointer binTree */
    if(rt == NULL) {
        rt = (binTree*)malloc(sizeof(binTree));
        rt->left = rt->right = NULL;}
    /* analizer */
    int pl, ct=0; char c='~';
    for (int i=0; i<str.length(); i++){
        if (str[i] == '(') ct++;
        if (str[i] == ')') ct--;
        if (ct == 0){
            if (str[i] == '+' || str[i] == '-'){
                pl = i; c = (str[i] == '+') ? '+' : '-';}
            else if (str[i]== '*' || str[i] == '/'){
                if (c == '~'){
                pl = i; c = (str[i] == '*') ? '*' : '/';}}
        }}
    /* checker */
    if (ct > 0){ cout << "too many (" << endl; return NULL;}
    if (ct < 0){ cout << "too many )" << endl; return NULL;}
    /* division binary equalization */
    bool tr = false; string lt = "", rd = "";
    for (int i=0; i<str.length(); i++){
        if (i == pl) {tr = true; continue;}
        if (tr) rd += str[i];
        if (!tr) lt += str[i];}
    /*connecter*/
    if (c != '~'){ rt->a = c;
        if (lt != "") rt->left = add(rt->left, lt);
        if (rd != "") rt->right = add(rt->right, rd);}
    else {
        if (lt != "") rt->a = lt[0];
        if (rd != "") rt->a = rd[0];}
    return rt;}

void del(binTree * ap){// simple deleting tree node
    delete ap->left; delete ap->right;
    ap->left = NULL; ap->right = NULL;}

void srt(binTree *p){
    if(p == NULL) return;
    /* recursive launch to srt from ending nodes */
    srt(p->left);
    srt(p->right);
    /* rules */
    if (p->a == '+'){
        if (p->left->a == '0'){
            p->a = p->right->a;
            p->right->a = p->right->right->a; del(p->right);
            p->left->a = p->right->left->a; del(p->left);}
        if (p->right->a == '0'){
            p->a = p->left->a;
            p->right->a = p->left->right->a; del(p->right);
            p->left->a = p->left->left->a; del(p->left);}}
    if (p->a == '-'){
        if (p->left->a == '0'){
            p->a = p->right->a;
            p->right->a = p->right->right->a; del(p->right);
            p->left->a = p->right->left->a; del(p->left);}
        if (p->right->a == '0'){
            p->a = p->left->a;
            p->right->a = p->left->right->a; del(p->right);
            p->left->a = p->left->left->a; del(p->left);}}
    if (p->a == '*'){
        if (p->left->a == '1'){
            p->a = p->right->a;
            p->right->a = p->right->right->a; del(p->right);
            p->left->a = p->right->left->a; del(p->left);}
        if (p->right->a == '1'){
            p->a = p->left->a;
            p->right->a = p->left->right->a; del(p->right);
            p->left->a = p->left->left->a; del(p->left);}
        if (p->left->a == '0'){
            p->a = p->right->a;
            p->right->a = p->right->right->a; del(p->right);
            p->left->a = p->right->left->a; del(p->left);}
        if (p->right->a == '0'){
            p->a = p->left->a;
            p->right->a = p->left->right->a; del(p->right);
            p->left->a = p->left->left->a; del(p->left);}}
    if (p->a == '/'){
        if (p->left->a == '1'){
            p->a = p->right->a;
            p->right->a = p->right->right->a; del(p->right);
            p->left->a = p->right->left->a; del(p->left);}
        if (p->right->a == '1'){
            p->a = p->left->a;
            p->right->a = p->left->right->a; del(p->right);
            p->left->a = p->left->left->a; del(p->left);}
        if (p->right->a == '0' || p->left->a == '0'){
            cout << "Деление на ноль, выход из программы"; exit(1);
        }}
    if (p->left->a == 'e' || p->right->a == 'e'){
        if (p->left->a == p->right->a) del(p);
        else if (p->left->a == 'e'){ p->a = p->right->a; del(p);}
        else{ p->a = p->left->a; del(p);}
        }
    }

string cl(binTree *p){
    string lt, rt, al;
    if(p == NULL) return "";
    lt = cl(p->left);
    rt = cl(p->right);
    if (p->left != NULL || p->right != NULL)
    al = "("+lt+p->a+rt+")";
    else al = p->a;
    return al;}

string lg(binTree *a, int lvl=0 ) {
    if (a == NULL) return "";
    string all = "";
    all += lg(a->left, lvl+1);
    all += a->a + to_string(lvl);
    all += lg(a->right, lvl+1);
    return all;}

void tp(binTree * root, int space = 0) {
    if (!root) return; int a = 0, b;
    string str = lg(root); b = str.length()/2;
    for (int i=1; i<str.length(); i+=2){
        int nm = int(str[i]-48);
        if (nm > a) a = nm;}
    char arr[++a][b]; for (int i=0; i<a; i++)
    for (int j=0; j<b; j++) arr[i][j] = ' ';
    
    for (int i=1, c=0; i<str.length(); i+=2){
        int nm = int(str[i]-48);
        arr[nm][c] = str[i-1]; c++;}
    
    for (int x=0; x<a; x++){
    for (int y=0; y<b; y++){
    cout << arr[x][y] << ' ';} cout << endl;}
    }

int main() {
    binTree *ext = NULL;
    string ur; ur = "(a*b+0*1)*(c*0)+(b-1)*(d*-0)";
    ext = add(ext, ur); tp(ext);
    cout << al(cl(ext)) << endl;
    srt(ext); tp(ext);
    cout << al(cl(ext)) << endl;
    return 0;
}
