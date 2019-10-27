//
// Created by filipe on 26/10/2019.
//

#include <deque>
#include <map>
#include <bits/stdc++.h>

#ifndef SO_2019_2_T1_OPT_H
#define SO_2019_2_T1_OPT_H


class OPT {
public:
    std::vector<int> pages;
    int numframes;
    int pageFaults=0;
    explicit OPT(std::vector<int> pages, int numframes){
        this->pages = std::move(pages);
        this->numframes = numframes;
    }
    void execute();
    static bool pageIsAlreadyLoaded(int page,const std::deque<int>& frames);
    int longestToAccess(std::vector<int> pages, unsigned long pageCurrentIndex,const std::deque<int>& frames);
};

/*
 * retorna se a página em questão já está em algum quadro
 */
bool OPT::pageIsAlreadyLoaded(int page,const std::deque<int>& frames){
    for(int loadedpage : frames){
        if(loadedpage==page){
            return true;
        }
    }
    return false;
}

/*
 * retorna o índice do quadro que contém a página que vai demorar mais pra ser acessada
 */
int OPT::longestToAccess(std::vector<int> pages, unsigned long pageCurrentIndex,const std::deque<int>& frames) {
    std::unordered_map<int,int> nextUsage;
    //nextUsage = <pageindex on frames, nextposition on pages>
    for (unsigned long j=0; j<frames.size(); j++) {
        for(unsigned long k = pageCurrentIndex; k<pages.size(); k++) {
            if(frames[j] == pages[k]){
                nextUsage[j] = k;
                break;
            }else{
                nextUsage[j] = pages.size();
            }
        }
    }

    std::pair<int,int> less = std::make_pair(0,0);
    for(auto u :nextUsage){
        if(u.second>less.second)
            less = u;
    }

    return less.first;
}

void OPT::execute(){
    std::deque<int> frames;
    for(unsigned long i = 0; i<this->pages.size();i++) {

        int page = this->pages[i];
        if(pageIsAlreadyLoaded(page,frames)){//Se página ja está carregada nos quadros, não faz nada e pula pra próxima
            continue;
        }

        if (frames.size() == this->numframes) {//Se quadros estão cheios, escolhe uma página para ser removida e colocar nova página no lugar
            int index = longestToAccess(this->pages,i,frames);
            frames[index]=page;
        }else{//senão, só adiciona nova página
            frames.push_back(page);
        }

        this->pageFaults++;
    }
}


#endif //SO_2019_2_T1_OPT_H
