import networkx as nx
import matplotlib.pyplot as plt
import sys
G = nx.DiGraph()
prev = []
cur = []
line = raw_input().split()
def CommonLetters(s1, s2):
    l1=list(''.join(s1.split()))
    l2=list(''.join(s2.split()))
    return [x for x in l1 if x in l2]
for i in line:
	G.add_edge(' ',i)
	prev.append(i)
for lines in sys.stdin:
	line = lines.split()
	for item in line:
		cur.append(item);
		itemName = item.split(',')[0]
		for p in prev:
			pName = p.split(',')[0]
			if(len(CommonLetters(pName,itemName))==len(pName)):
				G.add_edge(p,item)
	prev = cur
	cur = []

nx.draw_networkx(G)
nx.write_dot(G,'graph.dot')