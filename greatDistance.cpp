#include<bits/stdc++.h>
using namespace std;

#define lat_user 19.2856
#define lon_user 72.8691
#define earth_radius 6371.0
#define N 30.0000

ifstream cabs_list("input.json");
ofstream output("output.json");


struct json {
    string latitude,longitude,id,name;
    int c;
    double lat_cab,lon_cab;
    void find_cabs(){
        double delta = lon_cab - lon_user;
        double angle = acos((sin(lat_user)*sin(lat_cab)) + (cos(lat_user)*cos(lat_cab)*cos(delta))); 
        double distance = 2*M_PI*earth_radius*(angle/360.0);

        if(distance<=N){
            cout<<"User id : "<<id<<endl;
            cout<<"User name : "<<name<<endl;
            cout<<distance<<endl;
            output<<"{\"id\": "<<id<<", \"name\": "<<"\""<<name<<"\""<<"},"<<endl;
        }
    }
    void parser(){
        if(cabs_list.is_open()){
            string line;
            output<<"["<<endl;
            while(getline(cabs_list, line)){
                c=0;
                int size = line.length();
                // if(size==1)continue;
                if(size<=2)continue;
                // cout<<line<<endl;
                for(int j=1;j<size-2;j++){
                    char var = line[j];
                    if(var == ':'){
                        c++;
                    }
                    if(c==1 && latitude.size()==0){
                        j+=2;
                        while(line[j]!='"'){
                            latitude.push_back(line[j]);
                            j++;
                        }
                    }else if(c==2 && longitude.size()==0){
                        j+=2;
                        while(line[j]!='"'){
                            longitude.push_back(line[j]);
                            j++;
                        }
                    }
                    else if(c==3 && id.size()==0){
                        j+=2;
                        while(line[j]!='"'){
                            id.push_back(line[j]);
                            j++;
                        }
                    }else if(c==4 && name.size()==0){
                        j+=2;
                        while(line[j]!='"'){
                            name.push_back(line[j]);
                            j++;
                        }
                    }
                }
                lat_cab = stod(latitude);
                lon_cab = stod(longitude);
                // cout<<lat_cab<<endl;
                // cout<<lon_cab<<endl;
                // cout<<id<<endl;
                // cout<<name<<endl;
                // cout<<endl;
                find_cabs();
                cout<<endl;
                latitude.erase();
                longitude.erase();
                id.erase();
                name.erase();
            }
            cabs_list.close();
            output<<"{}"<<endl;
            output<<"]"<<endl;
            output.close();
        }
    }
};
int main(){
    // cout<<"hello world"<<endl;
    json obj;
    obj.parser();
    return 0;
}