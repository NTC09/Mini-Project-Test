
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include<iostream>
using namespace std;


#define _N 0LL
#define _t template
#define _n typename
#define _r return
_t<_n __T>
struct __sm{
bool operator()(const __T&t1,const __T&t2){_r t1<t2;}};
_t<_n __T,_n _c=__sm<__T>>
class AVLTree{
    private:
    class __J{public:__J*__l,*__r;int __h;__T __d;__J(){__l=__r=_N;__h=1;}__J(__T __nd){__l=__r=_N;
    __d=__nd;__h=1;}};__J*__o;_c __c;__J*__ii(__J*__o,__T&__nd){if(__o==_N){_r new __J(__nd);
    }else{if(__c(__nd,__o->__d))__o->__l=__ii(__o->__l,__nd);else __o->__r=__ii(__o->__r,__nd);}
    _r __b(__o);}__J*__dn(__J*__o,__T __d){if(__o==_N)_r __o;if(__c(__d,__o->__d))__o->__l=__dn
    (__o->__l,__d);else if(__c(__o->__d,__d))__o->__r=__dn(__o->__r,__d);else{if((__o->__l==_N)||
    (__o->__r==_N)){__J*__t=__o->__l?__o->__l:__o->__r;if(__t==_N){__t=__o;__o=_N;}else*__o=*__t;
    delete __t;}else{__J*__t=__gm(__o->__r);__o->__d=__t->__d;__o->__r=__dn(__o->__r,__t->__d);}}
    _r __b(__o);}__J*__b(__J*__o){if(__o==_N)_r __o;__o->__h=1+__m(__h(__o->__l),__h(__o->__r));
    int __b=__gb(__o);if(__b>1&&__gb(__o->__l)>=0)_r __rr(__o);if(__b>1&&__gb(__o->__l)<0){__o->__l
    =__lr(__o->__l);_r __rr(__o);}if(__b<-1&&__gb(__o->__r)<=0)_r __lr(__o);if(__b<-1&&__gb(__o->__r
    )>0){__o->__r=__rr(__o->__r);_r __lr(__o);}_r __o;}__J*__gm(__J*__o){if(__o==_N||__o->__l==_N)
    _r __o;_r __gm(__o->__l);}int __gb(__J*N){if(N==_N)_r 0;_r __h(N->__l)-__h(N->__r);}
    int __m(int _v1_,int _v2_){_r(_v1_<_v2_)?_v2_:_v1_;}__J*__rr(__J*y){__J*x=y->__l,*t=x->__r;
    x->__r=y;y->__l=t;y->__h=1+__m(__h(y->__l),__h(y->__r));x->__h=1+__m(__h(x->__l),__h(x->__r));
    _r x;}__J*__lr(__J*x){__J*y=x->__r;__J*t=y->__l;y->__l=x;x->__r=t;x->__h=1+__m(__h(x->__l),__h
    (x->__r));y->__h=1+__m(__h(y->__l),__h(y->__r));_r y;}__T*__fi(__J*__o,__T&_v_){__T*t=__lb(_v_);
    _r(t==_N||__c(_v_,*t))?_N:t;}__T*__up(__T&_v_){__J*t=__o,*r;while(t!=_N){r=t;if(__c(_v_,t->__d))
    t=t->__l;else t=t->__r;}_r(r==_N)?_N:&r->__d;}__T*__lb(__T&_v_){__J*t=__o,*r;while(t!=_N){r=t;
    if(__c(t->__d,_v_))t=t->__r;else if(__c(_v_,t->__d))t=t->__l;else _r&t->__d;}_r(r==_N)?_N:&r->
    __d;}void __d(__J*__o){if(__o==_N)_r;__d(__o->__l);__d(__o->__r);delete __o;}void __io(__J*__o)
    {if(__o!=_N){__io(__o->__l);cout<<__o->__d<<endl;__io(__o->__r);}}void __pi(__J*__o){if(__o!=_N)
    {__pi(__o->__r);cout<<__o->__d<<endl;__pi(__o->__l);}}int __h(__J*N){if(N==_N)_r 0;_r N->__h;}
    public:AVLTree(){__o=_N;}~AVLTree(){__d(__o);}void insert(__T __nd){if(__o==_N)__o=new __J(__nd)
    ;else __o=__ii(__o,__nd);}__T*find(__T __d){_r __fi(__o,__d);}void clear(){__d(__o);}void erase
    (__T __d){__o=__dn(__o,__d);}__T*lower(__T __d){__T*t=__lb(__d);_r(t==_N)?_N:((__c(*t,__d))?_N:t
    );}__T*upper(__T __d){__T*t=__up(__d);_r(t==_N)?_N:((__c(__d,*t))?t:_N);}void preOrder(){}
    void inOrder(){__io(__o);}void postOrder(){__pi(__o);}
};

#endif