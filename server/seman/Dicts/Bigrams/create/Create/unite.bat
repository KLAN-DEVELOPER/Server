gsort -m C:\Moshkow\01.src\bigrams.hmm C:\Moshkow\01a.src\bigrams.hmm C:\Moshkow\02.src\bigrams.hmm C:\Moshkow\03.src\bigrams.hmm  | gawk -f C:/Sokirko/awk/unite_bigrams.awk | grep -v  "OPEN_TAG" > bigrams.hm