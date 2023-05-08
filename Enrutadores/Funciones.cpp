#include <Clases.h>
#include <vector>
// Definition of router and red clases;

// *router clases;
bool buscar(std::vector <std::string> A, std::string B){

    for (int C = 0; C < A.size(); C++)
    {
        if (A[C] == B) return true;
    }
    return false;

}

router::router(std::string name){
    //  Constructor;
   I_D = name;
   Conections.insert(std::pair(name, 0));
}

std::string router::getI_D()
{
    return I_D;
}

void router::setI_D(std::string newI_D)
{
    I_D = newI_D;
}

std::map<std::string, int> router::getConections()
{
    return Conections;
}

void router::setConections(const std::map<std::string, int> newConections)
{
    Conections.clear();
    Conections.insert(newConections.begin(), newConections.end());
}

void router::Show(){

    std::map<std::string, int>::iterator itr;

    for (itr = Conections.begin(); itr != Conections.end(); itr++ ){
        std::cout << "\t" << itr->first << "\t" << itr->second << std::endl;
    }

}

void router::Conect(router& added, int latency)
{
    Conections.insert(std::pair(added.getI_D(), latency));
    std::map<std::string,int> swap = added.getConections();
    swap.insert(std::pair(I_D, latency));

    added.setConections(swap);
}

void router::Disconect(router& quit)
{
  Conections.erase(quit.getI_D());
  std::map<std::string,int> swap = quit.getConections();
  swap.erase(I_D);
  quit.setConections(swap);
}

// *red clases;

red::red()
{

}

inline std::map<std::string, router *> red::getTable()
{
  return table;
}

inline void red::setTable(std::map<std::string, router *> &newTable)
{
  table = newTable;
}

void red::Join(router* Added)
{
  table.insert(std::pair((*Added).getI_D(), Added));
  std::map<std::string, router *>::iterator itr;
  for (itr = table.begin(); itr != table.end(); itr++)
  {
        itr->second->Conect(*Added,-101);
  }

}

void red::Leave(router * quited)
{
  table.erase((*quited).getI_D());
  std::map<std::string, router *>::iterator itr;
  for (itr = table.begin(); itr != table.end(); itr++)
  {
        itr->second->Disconect(*quited);
  }
}

int red::Cheap(router * A, router * B){

  std::string init = A->getI_D(), exit = B->getI_D(), adyacente, anterior;
  std::map<std::string, int> Conexiones =  table[init]->getConections();
  std::map<std::string, int>::iterator itr = Conexiones.find(exit);
  long int min = 0, min1 = 256, contadorIt = 0, aux = 256; bool continuar = true;
  std::vector <std::string> vec;
  vec.push_back(init);

  if (itr->second != -101)
  {
        min1 = itr->second;
  }
  itr = Conexiones.begin();

  while(continuar){
        if (init == exit)
        {
            if (min < min1){
                return min;
            }
            continuar = false;
        }
        else if (itr == Conexiones.end())
        {
            anterior = table[init]->getI_D();
            init = adyacente;
            vec.push_back(init);
            Conexiones = table[init]->getConections();
            itr = Conexiones.begin();
            min += aux;
            aux = 256;
        }
        else if (itr->second < aux && itr->second != -101 && itr->first != A->getI_D() && anterior != itr->first && buscar(vec, itr->first) == false )
        {
            aux = itr->second;
            adyacente = itr->first;
            itr++;
        }
        else
        {
            contadorIt++;
            itr++;
            if (contadorIt == 1000){
                return min1;
            }
        }


  }
  return min1;
}

void red::Refresh()
{
  std::map<std::string, router*>::iterator itr, itrto;
  int aux, cont = 0;

  for (itr = table.begin(); itr != table.end(); itr++)
  {
        for (itrto = table.begin(); itrto != table.end(); itrto++)
        {
            cont++;
            aux = this->Cheap(itr->second, itrto->second);
            itr->second->Disconect(*itrto->second);
            itr->second->Conect(*itrto->second, aux);
        }

  }



}

void red::Show()
{
  std::map<std::string, router*>::iterator Red; std::map<std::string, int>::iterator Router; std::map<std::string, int> A;

  for (Red = table.begin(); Red != table.end(); Red++)
  {
        std::cout << "\t" << Red->first;
  }
  std::cout << std::endl;
  for (Red = table.begin(); Red != table.end(); Red++)
  {
        A = Red->second->getConections();
        std::cout << Red->first << "  \t";
        for (Router = A.begin(); Router != A.end(); Router++)
        {
            std::cout << Router->second << "\t";
        }
        std::cout << std::endl;

  }

}

std::string red::Path(router * A, router * B)
{
  std::string init = A->getI_D(), exit = B->getI_D(), adyacente, anterior;
  std::map<std::string, int> Conexiones =  table[init]->getConections();
  std::map<std::string, int>::iterator itr = Conexiones.find(exit);
  long int min = 0, min1 = 256, contadorIt = 0, aux = 256; bool continuar = true;
  std::vector <std::string> vec;
  vec.push_back(init); std::string path = "";

  if (itr->second != -101)
  {
        min1 = itr->second;
  }
  itr = Conexiones.begin();

  while(continuar){
        if (init == exit)
        {
            continuar = false;
        }
        else if (itr == Conexiones.end())
        {
            anterior = table[init]->getI_D();
            init = adyacente;
            vec.push_back(init);
            Conexiones = table[init]->getConections();
            itr = Conexiones.begin();
            min += aux;
            aux = 256;
        }
        else if (itr->second < aux && itr->second != -101 && itr->first != A->getI_D() && anterior != itr->first && buscar(vec, itr->first) == false )
        {
            aux = itr->second;
            adyacente = itr->first;
            itr++;
        }
        else
        {
            contadorIt++;
            itr++;
            if (contadorIt == 1000){
                return exit;
            }
        }


  }
  for (int C = 0; C < vec.size(); C++){
        path += "->" + vec[C];

  }
  return path;
}

