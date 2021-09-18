# CodeBook-Sample
> An example for codebook

## Info

### codebook.tex
> base information (ex. team name)
```tex
\fancyhead[C]{標題一}
\fancyhead[L]{標題二}
```

### content.tex
> contents (ex. codes, theorems)
```tex
\section{Section1}
    \subsection{Subsection1}
        \lstinputlisting{route/to/your/code}
        \input{route/to/your/theorem.tex}
```


## How to use

### easy

1. copy git link

<img src="https://i.imgur.com/9xEftSA.png" alt="drawing" width="300"/>

2. click `Import repository`

<img src="https://i.imgur.com/QiaSRcf.png" alt="drawing" width="300"/>

3. paste git link, set your repository name

<img src="https://i.imgur.com/T7wQkEZ.png" alt="drawing" width="500"/>



### old

* create a new repository without init on GitHub

* clone this repository
```
git clone https://github.com/HJackH/CodeBook-Sample.git
```

* push to your new repository
```
cd CodeBook-Sample
rm -rf .git
git init
git add .
git commit -m "init files"
git branch -M main
git remote add origin https://github.com/Yourname/new-repository.git
git push -u origin main
```
