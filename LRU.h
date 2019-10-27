//
// Created by filipe on 26/10/2019.
//

#ifndef SO_2019_2_T1_LRU_H
#define SO_2019_2_T1_LRU_H


class LRU {
public:
    std::vector<int> pages;
    int numframes;
    int pageFaults=0;
    explicit LRU(std::vector<int> pages, int numframes){
        this->pages = std::move(pages);
        this->numframes = numframes;
    }
    void execute();
    static bool pageIsAlreadyLoaded(int page,const std::deque<int>& frames, std::map<int,int>* timestamps, int index);
    int leastRecent(const std::deque<int>& frames, const std::map<int,int>& timestamps);
};

/*
 * retorna se a página em questão já está em algum quadro e atualiza seu timestamp
 */
bool LRU::pageIsAlreadyLoaded(int page,const std::deque<int>& frames,std::map<int,int>* timestamps, int index){
    for(unsigned long i=0;i<frames.size();i++){
        if(frames[i]==page){
            ((*timestamps)[i]) = index;
            return true;
        }
    }
    return false;
}
/*
 * Retorna índice do quadro que contem a página acessada a mais tempo.
 */
int LRU::leastRecent(const std::deque<int>& frames, const std::map<int, int>& timestamps ) {

    std::pair<int,int> older = std::make_pair(100000,100000);
    for(auto timestamp :timestamps){
        if(timestamp.second<older.second)
            older = timestamp;
    }
    return older.first;
}

void LRU::execute(){
    std::deque<int> frames;
    std::map<int, int> timestamps;
    for(unsigned long i = 0; i<this->pages.size();i++) {

        int page = this->pages[i];
        if(pageIsAlreadyLoaded(page,frames,&timestamps,i)){
            continue;//Se página já está carregada, pula para próxima
        }

        if (frames.size() >= this->numframes) {
            //se quadros estão cheios, remove a página do acessado a mais tempo,
            // adiciona nova página e atualiza timestamp do quadro com nova página

            int index = leastRecent(frames, timestamps);
            timestamps.erase(index);
            frames[index]=page;
            timestamps[index]=i;
        }else{
            //senão adiciona nova página e adiciona timestamp dessa página
            frames.push_back(page);
            timestamps[frames.size()-1]=i;
        }

        this->pageFaults++;
    }
}

#endif //SO_2019_2_T1_LRU_H
