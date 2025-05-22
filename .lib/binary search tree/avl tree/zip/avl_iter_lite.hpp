template <typename _T_>
struct s_{bool operator()(const _T_& t1, const _T_& t2){return t1<t2;}};
template <typename _T_, typename c_=s_<_T_>>
    class AVLTree{
   private:
    struct _N_{_N_* _l,* _r,* _p;int _h;_T_ _d;_N_(){}_N_(_T_ _d_){_l=_r=
    _p=nullptr;_d=_d_;_h=1;}};
    class _i{
        using v_=_T_;using p_=_T_*;
       private:
        _N_* _n;
       public:
        friend class AVLTree;
        _i(){}_i(_N_* _n){this->_n=_n;}v_ operator*() const{ return _n->_d;}
        p_ operator->(){ return &_n->_d; }_i& operator++(){this->_n=n_
        (this->_n, this->_n);return *this;}_i& operator++(int){this->_n=n_
        (this->_n, this->_n);return *this;}bool operator!=(const _i& i) const{
        return this->_n != i._n;}};
    _N_* _o;c_ _c;unsigned long long _s;
    _N_* i_(_N_* _o, _T_& _d_){if (_o==nullptr){return new _N_(_d_);} else 
   {if (_c(_d_, _o->_d)){_o->_l=i_(_o->_l, _d_);_o->_l->_p=_o;} else{
    _o->_r=i_(_o->_r, _d_);_o->_r->_p=_o;}}return a_(_o);}_N_* e_(_N_* _o, 
    _T_ _d){if (_o==nullptr)return _o;if (_c(_d, _o->_d)){_o->_l=e_(_o->
    _l, _d);if (_o->_l != nullptr)_o->_l->_p=_o;} else if (_c(_o->_d, _d)){
    _o->_r=e_(_o->_r, _d);if (_o->_r != nullptr)_o->_r->_p=_o;} else{
    if ((_o->_l==nullptr)||(_o->_r==nullptr)){_N_* _t=_o->_l ? _o->_l :
    _o->_r;if (_t==nullptr){ _t=_o;_o=nullptr;} else{_N_* p=_o->_p;
    *_o=*_t; _o->_p=p;} delete _t;--_s;} else{ _N_* _t=g_(_o->_r);_o->_d
    =_t->_d;_o->_r=e_(_o->_r, _t->_d);if (_o->_r != nullptr)_o->_r->_p=_o;}}
    return a_(_o);}_N_* a_(_N_* _o){if (_o==nullptr)return _o;_o->_h=1 + m_
    (_h(_o->_l), _h(_o->_r));int b=b_(_o);if (b > 1 && b_(_o->_l) >= 0)return 
    rr_(_o);if (b > 1 && b_(_o->_l) < 0){_o->_l=lr_(_o->_l);return rr_(_o);}
    if (b < -1 && b_(_o->_r) <= 0)return lr_(_o);if (b < -1 && b_(_o->_r) > 0){
    _o->_r=rr_(_o->_r);return lr_(_o);}return _o;}static _N_* g_(_N_* _o){
    if (_o==nullptr || _o->_l==nullptr)return _o;return g_(_o->_l);}int b_
    (_N_* N){if (N==nullptr)return 0;return _h(N->_l)-_h(N->_r);}_N_* rr_(_N_
    * y){_N_* x=y->_l;_N_* T2=x->_r;x->_r=y;y->_l=T2;x->_p=y->_p;y->
    _p=x;if (T2 != nullptr){T2->_p=y;}y->_h=1 + m_(_h(y->_l), _h(y->_r));
    x->_h=1 + m_(_h(x->_l), _h(x->_r));return x;}_N_* lr_(_N_* x){_N_* y=
    x->_r;_N_* T2=y->_l;y->_l=x;x->_r=T2;y->_p=x->_p;x->_p=y;if (T2 !=
    nullptr){T2->_p=x;}x->_h=1 + m_(_h(x->_l), _h(x->_r));y->_h=1 + m_(_h
    (y->_l), _h(y->_r));return y;}_N_* f_(_N_* _o, _T_& value){_N_* t=l_
    (value);return (t==nullptr || _c(value, t->_d)) ? nullptr : t;}_N_* u_(_T_
    & value){_N_ *t=_o, *r=nullptr;while (t != nullptr){if (_c(value, t->_d
    ))r=t, t=t->_l;else t=t->_r;}return r;}_N_* l_(_T_& value){_N_ *t=_o, 
    *r=nullptr;while (t != nullptr){if (!_c(t->_d, value))r=t, t=t->_l;else
    t=t->_r;}return r;}void d_(_N_* _o){if (_o==nullptr)return;d_(_o->_l);
    d_(_o->_r);delete _o;}int _h(_N_* N){if (N==nullptr)return 0;return N->_h;}
    int m_(int a, int b){ return (a > b) ? a : b; }static _N_* n_(_N_* _o, _N_* 
    next){if (_o->_r != nullptr){return g_(_o->_r);} else if (_o==_o->_p->_r) 
   {while (_o->_p != nullptr && _o==_o->_p->_r)_o=_o->_p;return _o->_p;}
    return _o->_p;}
   public:
    AVLTree(){_o=nullptr;_s=0;}~AVLTree(){d_(_o);}void insert(_T_ _d_){if
    (_o==nullptr){_o=new _N_(_d_);} else{_o=i_(_o, _d_);}++_s;}_i find(_T_ _d)
    {return _i(f_(_o, _d));}void clear(){d_(_o);_o=nullptr;_s=0;}void erase(_T_
    _d){_o=e_(_o, _d);}_i lower_bound(_T_ _d){return _i(l_(_d));}_i upper_bound
    (_T_ _d){return _i(u_(_d));}_i begin(){return _i(g_(_o));}_i end(){return _i
    (nullptr);}unsigned long long size(){ return _s; }
};
