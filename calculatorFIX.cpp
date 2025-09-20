#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <string>
#include <map>
using namespace std;


string vvod;
vector <int> input;
vector <int> output;
vector <int> stak;
int smcode;
bool b=1;
int token=0;



void do_operation (int sign)
{
 int helper;
    if(sign==-5)// +
    {
        helper=*(output.end()-1);
        output.pop_back();
        helper=*(output.end()-1)+helper;
        output.pop_back();
        output.push_back(helper);
    }
    if(sign==-3)// -
    {
        helper=*(output.end()-1);
        output.pop_back();
        helper=*(output.end()-1)-helper;
        output.pop_back();
        output.push_back(helper);
    }
    if(sign==-6)// *
    {
        helper=*(output.end()-1);
        output.pop_back();
        helper=*(output.end()-1)*helper;
        output.pop_back();
        output.push_back(helper);
    }
    if(sign==-1)// /
    {
        helper=*(output.end()-1);
        output.pop_back();
        helper=*(output.end()-1)/helper;
        output.pop_back();
        output.push_back(helper);
    }

}



void string_to_input (int pos)
     {

        if(pos<vvod.length())
        {
         smcode=vvod[pos]-48;

         if(smcode>-1)
            token=token*10+smcode;
         else
          {
             if(((token!=0)||(smcode>-8))&&(b==1))
              input.push_back(token);

            input.push_back(smcode);
            token=0;

             if(smcode==-7)
                  b=0;
              else
                  b=1;
          }
          string_to_input(pos+1);
        }
        else
        {if(*(input.end()-1)!=-7)
             input.push_back(token);
        }
     }



int main()
{

string sprob;
getline(cin,sprob);
vvod="";

 for(int i=0;i<sprob.length();i++)
 if(sprob[i]!=' ')
  vvod+=sprob[i];

 //PREC - perevod recurs
  string_to_input(0);

 //SSA - sorting station algorithm
 for(int i=0;i<input.size();i++)
  {
    if(input[i]>=0)
         output.push_back(input[i]);


    if((input[i]==-5)||(input[i]==-3))
        //nizkiy prior
        {while((stak.size()>0)&&(*(stak.end()-1)!=-8))
            {
                do_operation(*(stak.end()-1));
                stak.pop_back();
            }
            stak.push_back(input[i]);}


    if((input[i]==-6)||(input[i]==-1))
        //visokiy prior
          {while((stak.size()>0)&&(*(stak.end()-1)!=-3)&&(*(stak.end()-1)!=-5)&&(*(stak.end()-1)!=-8))
            {
                do_operation(*(stak.end()-1));
                stak.pop_back();
            }
            stak.push_back(input[i]);}


    if(input[i]==-8)
        //skobka otkr
            stak.push_back(-8);


    if(input[i]==-7)
        //skobka zakr
            {
             while((stak.size()>0)&&(*(stak.end()-1)!=-8))
                  {
                do_operation(*(stak.end()-1));
                stak.pop_back();
                  }
             stak.pop_back();
            }
   }


      while(stak.size()>0)
      {
        do_operation(*(stak.end()-1));
        stak.pop_back();
      }

cout<<output[0];
return 0;
}
