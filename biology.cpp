#include <iostream>
#include <set>
#include<vector>
#include <math.h>
#include <algorithm>
using namespace std;
void generating(int** &population,int &length_individual,int &th_time,int &randomSeed,int &length_population){
    for (int i=0;i<length_population*2;i++){
        population[i] = new int[length_individual];
    }
    randomSeed += th_time ;
    srand(randomSeed);
    for (int i=0;i<length_population;i++){
        for (int j=0;j<length_individual;j++){
        population[i][j] = rand()%2;
     //   cout<<population[i][j]<<' ';
    }
      //  cout<<endl;
    }
   // cout<<endl;
}
int fitness(int* &individual,int &length_individual){
    int dem =0 ;
    for (int i=0;i<length_individual;i++){
        dem += individual[i];
    }
  //  if (dem == 10) cout<<"cacccccccc"<<endl;
   // if (dem < length_individual) return length_individual - dem -1; //trapFunction
    return dem;
}
void laimotdiem(int ** &population,int &length_population,int &length_individual){
//    cout<<"before variation"<<endl;
//    for (int i=0;i<length_population*2;i++){
//    for (int j=0;j<length_individual;j++){
//        cout<<population[i][j]%2<<' ';
//    }
//    cout<<endl;
//    }
    for (int i=0;i<length_population/2;i++){
        int x = rand()%length_individual;
       // cout<<x<<endl;
        for (int j=0;j<=x;j++){
               // cout<<endl;
               // cout<<(&population[length_population+i*2][j])<<"test"<<endl;
            population[length_population+i*2][j] = population[i*2][j];
              //  cout<<(&population[length_population+i*2][j])<<"test2"<<endl;
            population[length_population+i*2+1][j] = population[i*2+1][j];
        }
        for (int j=x+1;j<length_individual;j++){
            population[length_population+i*2][j] = population[i*2+1][j];
            population[length_population+i*2+1][j] = population[i*2][j];
        }
    }
//    cout<<"after variation"<<endl;
//    for (int i=0;i<length_population*2;i++){
//    for (int j=0;j<length_individual;j++){
//        cout<<population[i][j]%2<<' ';
//    }
//    cout<<endl;
//    }
}
void laidongnhat(int ** &population,int &length_population,int &length_individual){
     for (int i=0;i<length_population/2;i++){
      //  cout<<x<<endl;
        for (int j=0;j<length_individual;j++){
            int x = rand()%2;
            if (x==1){
            population[length_population+i*2][j] = population[i*2][j];
            population[length_population+i*2+1][j] = population[i*2+1][j];
            }
            else {
                population[length_population+i*2][j] = population[i*2+1][j];
            population[length_population+i*2+1][j] = population[i*2][j];
            }
        }
    }
}
void tournament_selection_randomAccess(int** &population,int &length_population,int &length_individual){
    set<int> kt;
    vector <int*> tmp ;
//        cout<<"after variation"<<endl;
//    for (int i=0;i<length_population*2;i++){
//    for (int j=0;j<length_individual;j++){
//        cout<<population[i][j]<<' ';
//    }
//    cout<<endl;
//    }
    while (tmp.size()!=length_population){
          //  cout<<"paticipant"<<endl;
        while (kt.size()<4){
            kt.insert(rand()%(length_population*2));
        }
        int maximum=-1;
        int* index_maximum;
        for (set<int>::iterator it=kt.begin(); it!=kt.end(); ++it){
          //  cout<<*it<<' ';
            int tmp = fitness(population[*it],length_individual);
            if (tmp > maximum) {
                maximum = tmp;
                index_maximum = population[*it];
            }
        }
        kt.clear();
        tmp.push_back(index_maximum);
        //cout<<endl;
    }
    //cout<<"winner"<<endl;
    for (int i=0;i<length_population;i++){
            for (int j=0;j<length_individual;j++)
        population[i][j] = tmp[i][j];
     //   for (int j=0;j<length_individual;j++)
      //      cout<<population[i][j]<<' ';
  //      cout<<endl;
    }
//    cout<<endl;
}
int myrandom (int i) { return rand()%i;}
void tournament_selection_teacher(int** &population,int &length_population,int &length_individual){
    vector <int*> tmp ;
        int maximum=-1;
        int *index_maximum;
        for (int it = 0 ;it <length_population*2;it++){
            int cur_fitness = fitness(population[it],length_individual);
            if (cur_fitness > maximum) {
                maximum = cur_fitness;
                index_maximum = population[it];
            }
            if (it%4 == 3){
                tmp.push_back(index_maximum);
                maximum=-1;
            }
        }
    std::random_shuffle ( population+0, population+length_population*2-1 );
    std::random_shuffle ( population+0, population+length_population*2-1, myrandom);
         for (int it = 0 ;it <length_population*2;it++){
            int cur_fitness = fitness(population[it],length_individual);
            if (cur_fitness > maximum) {
                maximum = cur_fitness;
                index_maximum = population[it];
            }
        //    cout<<cur_fitness<<' '<<it<<' '<<tmp.size()<<endl;
            if (it%4 == 3){

                tmp.push_back(index_maximum);
                maximum=-1;
            }
        }
    //cout<<tmp.size()<<endl;
   // exit(0);
    if (tmp.size()!=length_population) {
            cout<<tmp.size()<<endl;
        cout<<"ngu lzz"<<endl;
        exit(0);
    }
          for (int i=0;i<length_population;i++){
                //cout<<tmp[i][0]<<endl;
            for (int j=0;j<length_individual;j++)
        population[i][j] = tmp[i][j];
     //   for (int j=0;j<length_individual;j++)
      //      cout<<population[i][j]<<' ';
  //      cout<<endl;
    }
   // exit(0);
}
void deletePopulation(int**  &population,int &length_population){
    for (int i=0;i<length_population*2;i++){
          //  cout<<i<<"cac"<<population<<population[i]<<endl;
//        for (int j=0;j<length_individual;j++)
            delete [] population[i];
    }
    delete [] population;
}
double averagedFitness(int** &population,int &length_population,int &length_individual){
    double dem = 0;
    for (int i=0;i<length_population;i++)
        dem += fitness(population[i],length_individual);
    return dem/length_population;
}
bool success(int randomSeed,int &th_time,int &length_population,int &length_individual){
    int ** population = new int*[length_population*2];
    generating(population,length_individual,th_time,randomSeed,length_population);
    int dem = 0, best_population = 0;
    while (dem < log2(length_population)){
        laimotdiem(population,length_population,length_individual);
        //laidongnhat(population,length_population,length_individual);
        tournament_selection_randomAccess(population,length_population,length_individual);
        //tournament_selection_teacher(population,length_population,length_individual);

        for (int i=0;i<length_population;i++){
            if (fitness(population[i],length_individual) == length_individual) {
                    deletePopulation(population,length_population);
                    return true;
            }
        }
        double tmp = averagedFitness(population,length_population,length_individual);
        if (tmp <= best_population) dem ++ ;
        else {
            dem = 0 ;
            best_population = tmp;
        }
    }
//    for (int i=0;i<length_population;i++){
//    for (int j=0;j<length_individual;j++){
//        cout<<population[i][j]<<' ';
//    }
//    cout<<endl;
//    }

    deletePopulation(population,length_population);
   // return true;
    return false;
}
bool check(int &length_population,int &length_individual,int &runtime){
    for (int i=1;i<=10;i++){
        if (success(19520109+runtime*10,i,length_population,length_individual)) return 1 ;
    }
    return (0);
}
int main(){
    //freopen("submission.out","w",stdout);
    for (int i=0;i<10;i++){
            int r = 2;
        int length_individual = 160;
    while (r<=8192){
      //      cout<<r<<endl;
        if (check(r,length_individual,i)) break;
        else {
                if (r == 8192) break;
                r <<= 1;
        }
    }
    //break;
    if (r == 8192) {
            cout << "A[" <<i<<"]: -1"<<endl;
            continue;
    }
    double upper = r ;
    double lower = upper/2;
    lower /= 2;
    upper /= 2;
    //int c = 1022,b = 2;
  //  cout<<check(c,length_individual,b)<<endl;
    int res = -1;
    int mid ;
    //cout<<"found upper!!"<<endl;
    while (lower<=upper)   {
        mid = (upper + lower) / 2;
        mid = mid *2;
       // cout<<mid<<' '<<lower<<' '<<upper<<endl;
        if (check(mid,length_individual,i)) {
            res = mid ;
            upper = mid/2-1  ;
        }
        else lower = mid/2 + 1 ;
    //    if (upper - lower <=2) break;
    }
    cout << "A[" <<i<<"]: ";
    if (res == -1) cout<<upper<<endl;
    else cout<<res<<endl;
    }
}
