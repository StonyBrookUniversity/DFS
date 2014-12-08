networkControlLogic2module.so:
	g++ -g -shared -fpermissive -std=c++0x networkControlLogic2.cpp MininetMessages.cpp networkControlLogic2Flow.cpp randomGraph.cpp compElephent.cpp computTopoFuncts.cpp GenerateFattree.cpp -o networkControlLogic2module.so -fPIC -I/usr/include/python2.7 -lpython2.7 -lboost_python -lboost_system

clean:
	rm networkControlLogic2module.so 
	
