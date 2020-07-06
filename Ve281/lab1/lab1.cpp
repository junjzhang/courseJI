#include <iostream>
#include<vector>
#include<algorithm>

std::vector<std::vector<int> > findTriplet(std::vector<int>& num, int n){
    std::vector<std::vector<int> > result;
    std::vector<std::vector<int> >::size_type first, second, third;
    //sort firt
    std::sort(num.begin(),num.end());
    std::cout<<num[0]<<std::endl;
    //check
    for(std::vector<std::vector<int> >::size_type ii=0; ii<n-2; ii++){
        //pre-condition
        if(ii!=0){
            if(num[ii-1]==num[ii]) continue;
        }
        else if(num[ii]>0) continue;
        first = ii;
        second = ii+1;
        third = n-1;
        //check one by one
        while(second<third){
            if(num[first]+num[second]+num[third]==0){
                result.push_back(std::vector<int>({num[first],num[second],num[third]}));
                while(num[second]==num[second+1]&&second<third){
                        second ++;
                }
                second ++;
                third --;
                std::cout<<num[first]<<num[second]<<num[third]<<std::endl;
            }
            else if (num[first]+num[second]+num[third]>0) third --;
            else if (num[first]+num[second]+num[third]<0) second ++;
        }
    }
    return result;
}

int main(){
    std::vector<int> a({-1,-2,0,2,1,8,1});
    std::vector<std::vector<int> > b = findTriplet(a,5);
    return 0;
}