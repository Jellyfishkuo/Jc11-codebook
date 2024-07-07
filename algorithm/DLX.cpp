struct DLX {
    int seq, resSize;
    int col[maxn], row[maxn];
    int U[maxn], D[maxn], R[maxn], L[maxn];
    int rowHead[maxn], colSize[maxn];
    int result[maxn];
    DLX(int r, int c) {
        for(int i=0; i<=c; i++) {
            L[i] = i-1, R[i] = i+1;
            U[i] = D[i] = i;
        }
        L[R[seq=c]=0]=c;
        resSize = -1;
        memset(rowHead, 0, sizeof(rowHead));
        memset(colSize, 0, sizeof(colSize));
    }
    void insert(int r, int c) {
        row[++seq]=r, col[seq]=c, ++colSize[c];
        U[seq]=c, D[seq]=D[c], U[D[c]]=seq, D[c]=seq;
        if(rowHead[r]) {
            L[seq]=rowHead[r], R[seq]=R[rowHead[r]];
            L[R[rowHead[r]]]=seq, R[rowHead[r]]=seq;
        } else {
            rowHead[r] = L[seq] = R[seq] = seq;
        }
    }
    void remove(int c) {
        L[R[c]] = L[c], R[L[c]] = R[c];
        for(int i=D[c]; i!=c; i=D[i]) {
            for(int j=R[i]; j!=i; j=R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --colSize[col[j]];
            }
        }
    }
    void recover(int c) {
        for(int i=U[c]; i!=c; i=U[i]) {
            for(int j=L[i]; j!=i; j=L[j]) {
                U[D[j]] = D[U[j]] = j;
                ++colSize[col[j]];
            }
        }
        L[R[c]] = R[L[c]] = c;
    }
    bool dfs(int idx=0) {   // 判斷其中一解版
        if(R[0] == 0) {
            resSize = idx;
            return true;
        }
        int c = R[0];
        for(int i=R[0]; i; i=R[i]) {
            if(colSize[i] < colSize[c]) c = i;
        }
        remove(c);
        for(int i=D[c]; i!=c; i=D[i]) {
            result[idx] = row[i];
            for(int j=R[i]; j!=i; j=R[j])
                remove(col[j]);
            if(dfs(idx+1)) return true;
            for(int j=L[i]; j!=i; j=L[j])
                recover(col[j]);
        }
        recover(c);
        return false;
    }
    void dfs(int idx=0) {   // 判斷最小 dfs depth 版
        if(R[0] == 0) {
            resSize = min(resSize, idx); // 注意init值
            return;
        }
        int c = R[0];
        for(int i=R[0]; i; i=R[i]) {
            if(colSize[i] < colSize[c]) c = i;
        }
        remove(c);
        for(int i=D[c]; i!=c; i=D[i]) {
            for(int j=R[i]; j!=i; j=R[j])
                remove(col[j]);
            dfs(idx+1);
            for(int j=L[i]; j!=i; j=L[j])
                recover(col[j]);
        }
        recover(c);
    }
};