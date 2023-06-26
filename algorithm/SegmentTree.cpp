struct node{
    int val;
    node *l,*r;
    node(int v=0):val(v){};
    node(node* l,node* r):l(l),r(r){pull();}
    void pull(){val=min(l->val,r->val);}
    //l->val就是(*l).val，注意.的優先順序比*還高
};

int v[N];//原數列
node* build(int l,int r){
    if(l+1==r) return new node(v[l]);
    int mid=(l+r)/2;
    return new node(build(l,mid),build(mid,r));
}

void modify(node* a,int l,int r,int pos,int k){
    //把pos位置的值換成k
    if(l+1==r){a->val=k;return;};
    int mid=(l+r)/2;
    if(pos<mid) modify(a->l,l,mid,pos,k);
    else modify(a->r,mid,r,pos,k);
    a->pull();
}

int query(node* a,int l,int r,int ql,int qr){
    //查詢[ql,qr)範圍的最小值
    if(r<=ql||qr<=l) return inf;
    if(ql<=l&&r<=qr) return a−>val;
    int mid=(l+r)/2;
    return min(query(a−>l,l,mid,ql,qr),
                query(a−>r,mid,r,ql,qr));
}