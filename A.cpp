#include<bits/stdc++.h>
using namespace std;
double lo=0,up=1,cdf[100008],pro[1000008],minProb=10000000.0,curtag;
int k,op,n;
string charSet,seq,out="",tag;

int retInd(char ch){
    for(int i=0;i<charSet.size();i++){
        if(charSet[i]==ch)return i;
    }
}

int getK(){

    // 2 ^ -k  = minProb => k = -log2(minProb)
    return ceil(log2(minProb)*-1);
}
double getNewTag(string str){
    double temp=0.0;
    for(int i=0;i<str.size();i++){
        if(str[i]=='1'){
            temp += 1/ pow(2,i+1);
        }
    }
    return temp;
}

int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    cout<<"press --> 1 for encoding \n press --> 2 for decoding :  ";
    cin>>op;

    if(op==1)
    {
        cout<<"Please input the character set that you will use for encoding :"<<endl;
        cin>>charSet;
        cout<<"Please input the sequence you want to encode it :"<<endl;
        cin>>seq;
        cout<<"Please insert the probabilities for the character set :"<<endl;
        for(int i=0;i<charSet.size();++i)
        {
            cin>>pro[i];
            cdf[i+1]=pro[i]+cdf[i];
        }

        cout<<"The Result od encoding is :"<<endl;
        for(int i=0;i<seq.size();++i)
        {
            int indx=retInd(seq[i]);
            double diff = (up-lo);
            double lower = lo;
            lo = lower+diff*cdf[indx];
            up = lower+diff*cdf[indx+1];
            while((lo>=0 && lo<0.5) && (up>=0 && up<0.5)||(lo>=0.5 && lo<1) && (up>=0.5 && up<1)){
                if((lo>=0 && lo<0.5) && (up>=0 && up<0.5)){
                    out+="0";
                    lo*=2;
                    up*=2;
                }else if((lo>=0.5 && lo<1) && (up>=0.5 && up<1)){
                    out+="1";
                    lo=2*(lo-0.5);
                    up=2*(up-0.5);
                }
            }
        }
        out+="1";
        while(out.size()<32)out+="0";
        cout<<out<<endl;
    }
    else if(op==2)
    {
        cout<<"Please input the character set that you will use for decoding :"<<endl;
        cin>>charSet;
        cout<<"Please input the code to be decoded :"<<endl;
        cin>>tag;
        cout<<"Please insert the probabilities for the character set :"<<endl;
        for(int i=0;i<charSet.size();++i)
        {
            cin>>pro[i];
            if(pro[i]<minProb)
            {
                minProb = pro[i];
            }
            cdf[i+1]=pro[i]+cdf[i];
        }
        cout<<"Please insert the message size (num of character in decoded massage) :"<<endl;
        cin>>n;
        cout<<"The Result od decoding is :"<<endl;
        k= getK();
        int  indx=0;
        for(int i=0;i<n;++i)
        {
            curtag = getNewTag(tag.substr(indx,k));
            double diff = (up-lo);
            double lower = lo;
            for(int j=0;j<charSet.size();j++){
                //cout<<"lo " <<lo<<" up "<<up<<" cdf "<<cdf[j]<<"  "<<cdf[j+1]<<" ctag "<<curtag<<endl;
                lo = lower+diff*cdf[j];
                up = lower+diff*cdf[j+1];
                if(curtag>=lo && curtag<up){
                    out+=charSet[j];
                    break;
                }
            }


            //cout<<"scall::  lo " <<lo<<" up "<<up<<endl;
            while((lo>=0 && lo<0.5) && (up>=0 && up<0.5)||(lo>=0.5 && lo<1) && (up>=0.5 && up<1)){
                if((lo>=0 && lo<0.5) && (up>=0 && up<0.5)){
                    lo*=2;
                    up*=2;
                }else if((lo>=0.5 && lo<1) && (up>=0.5 && up<1)){
                    lo=2*(lo-0.5);
                    up=2*(up-0.5);
                }
                indx++;

            }

        }
        cout<<out<<endl;
    }
}
