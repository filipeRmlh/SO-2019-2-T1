//
// Created by filipe on 26/10/2019.
//

#ifndef SO_2019_2_T1_FIFO_H
#define SO_2019_2_T1_FIFO_H

#include <deque>

class FIFO {
public:
    std::vector<int> pages;
    int numframes;
    int pageFaults = 0;
    explicit FIFO(std::vector<int> pages, int numframes){
        this->pages = std::move(pages);
        this->numframes = numframes;
    }
    void execute();
    static bool pageIsAlreadyLoaded(int page,const std::deque<int>& frames);
};

/*
 * retorna se a página em questão já está em algum quadro
 */
bool FIFO::pageIsAlreadyLoaded(int page,const std::deque<int>& frames){
    for(int loadedpage : frames){
        if(loadedpage==page){
            return true;
        }
    }
    return false;
}

void FIFO::execute(){
    std::deque<int> frames;
    for(int page : this->pages) {
        if(pageIsAlreadyLoaded(page,frames)){//se página já está carregada não faz nada e pula pra próxima.
            continue;
        }else  if (frames.size() >= this->numframes) {//senão, remove a mais antiga a ser adicionada
            frames.pop_front();
        }

        frames.push_back(page);//adiciona nova página
        this->pageFaults++;
    }
}

#endif //SO_2019_2_T1_FIFO_H
