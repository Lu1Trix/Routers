#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include <map>
#include <vector>


class router{

private:
    // Router name and map conections;

    std::string I_D; std::map<std::string,int> Conections;

public:
    // Main funtions of router´s;
    router(std::string);
    void Show();
    void Conect(router&, int);
    void Disconect(router&);
    std::string getI_D();
    void setI_D(std::string newI_D);
    std::map<std::string, int> getConections();
    inline void setConections(const std::map<std::string, int> newConections);
};



class red{

private:
    // Interconections between routers;
    std::map<std::string, router*> table;

public:
   // Main funtions of red;
   red();
   std::map<std::string, router*> getTable();
   void setTable(std::map<std::string, router*> &newTable);
   void Join(router*);
   void Leave(router*);
   int Cheap(router*, router*);
   std::string Path(router*, router*);
   void Refresh();
   void Show();


};





#endif // CLASES_H
