Compile the code as follows:
g++11 parallel1.cpp -o parallel1 -lpthread

execute it as : 
./parallel1 > out.txt

it will automatically read input from the input.txt file in the folder

generating graph in python
python graph.py < out.txt

creating png file of the graph
dot -Tpng graph.dot > graph.png
