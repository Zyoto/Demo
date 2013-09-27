p = P
q = Q
paq = p&q
poq = p+q
piq = p->q
pbq = p<->q
drawtable(paq)
dRawtable(poq)
drAwtable(piq)
draWtable(pbq)
p = R
q = S
drawtable(paq)
dRawtable(poq)
drAwtable(piq)
draWtable(pbq)

dma = -(P&Q)<->(-P+-Q)
drawtable(dma)
isanything(dma)

dmb = -(P+Q)<->(-P&-Q)
drawtable(dmb)
isanything(dmb)

dmc = -(-P&-Q)<->(P+Q)
drawtable(dmc)
isanything(dmc)

dmd = -(-P+-Q)<->(P&Q)
drawtable(dmd)
isanything(dmd)

a = P&(P->Q)&(Q->R)
Implication(a: R)
p = P
equivalence(p, P)

fundamentals
expressions
operators
truth tables

architecture
compiler tools

http://flex.sourceforge.net/
