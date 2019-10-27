#include <iostream>
#include <vector>
#include "OPT.h"
#include "FIFO.h"
#include "LRU.h"

using namespace std;
const int MAXSIZE = 5000;
vector<int> readInput();


int main(int argc, char* argv[]) {
    if(argc!=2) {
        cout << "Número incorreto de argumentos" << endl;
        return 1;
    }
    int frames = atoi(argv[1]);
    vector<int> pages = readInput();

    OPT opt = OPT(pages, frames);
    LRU lru = LRU(pages, frames);
    FIFO fifo = FIFO(pages, frames);
    fifo.execute();
    opt.execute();
    lru.execute();
    printf ("%5d quadros, %7d refs: FIFO: %5d PFs, LRU: %5d PFs, OPT: %5d PFs\n", frames, (int) pages.size(), fifo.pageFaults, lru.pageFaults, opt.pageFaults) ;

    return 0;
}


vector<int> readInput(){
    vector<int> pages;
    int s;
    while (cin >> s && !cin.eof() && pages.size() <= MAXSIZE){
        pages.push_back(s);
    }
    return pages;
}


