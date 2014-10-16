# ilouds

木構造を表現する簡潔データ構造である [LOUDS][louds] の実装。  
過去の [rank/select][ibary] の実装を利用している。  
ROUDS の解説について [ここ][aspe] が非常にわかりやすくおすすめです。  

[louds]: http://www.cs.cmu.edu/afs/cs/project/aladdin/wwwlocal/compression/00063533.pdf "Space-efficient Static Trees and Graphs"
[ibary]: https://github.com/masakazu-ishihata/ibary "masakazu-ishihata/ibary"
[aspe]: http://d.hatena.ne.jp/takeda25/20120421/1335019644 "簡潔データ構造 LOUDS の解説（全12回、練習問題付き） - アスペ日記"

## 使い方

### new / free

    ilouds *ilouds_new(ui _N, ui _M, ui **_A);

_N x _M 行列 _A で表現された木を表現する LOUDS を構成する。  
_N は木の節点数、_M は木の幅である。  
_A は幅優先順序で与えれた節点の子リストとする。  

    void ilouds_free(void *_p);

LOUDS _p を free する。


### import / export

    void ilouds_show(FILE *_fp, ilouds *_p);

LOUDS _p を _fp に出力する。

    ilouds *ilouds_export(ilouds *_p, char *_bits);

LOUDS _p をビット列 _bits に変換する。

    ilouds *ilouds_import(const char *_bits);

ビット列 _bits が表す LOUDS を構成する。


### accessors

    int ilouds_get_index(ilouds *_p, ui _i);

節点 _i の LOUDS 内でのインデックスを返す。  
(_i に対応する "1" の位置を返す。)

    int ilouds_get_head(ilouds *_p, ui _i);

節点 _i の子リストの先頭を返す。  
(_i の最初の子のインデックスを返す。)

    int ilouds_get_parent(ilouds *_p, ui _i);

節点 _i の親の ID を返す。  
(LOUDS 内のインデックスではなく、節点の ID を返す。）

    int ilouds_get_child(ilouds *_p, ui _i, ui _j);

節点 _i の _j 番目の子の ID を返す。  
(子は 0 番目から数える。)

    int ilouds_get_num_children(ilouds *_p, ui _i);

節点 _i の子の数を返す。
