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
