#include "aes.h"

void Aes::aes_enc() {
    int extendedlength=0;
    string myText;
    ifstream File;
    string filepath = "encryption.aes";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail())
    {
    File.close();
    printf("\nError : failed to erase file content !");
    }
    File.close();
    fstream newfile;
    newfile.open("input.txt",ios::in);
    if (newfile.is_open()){ 
    sleep(1);
    string tp;
    sleep(1);
    sleep(1);
    sleep(1);
    while(getline(newfile, tp)){ 
    int messlength=tp.length();
    int extendedlength;
    if((messlength%16)!=0)
    {
    extendedlength=messlength+(16-(messlength%16));
    }
    else
    {
    extendedlength=messlength;
    }
    unsigned char* encryptedtext=new unsigned char[extendedlength];
    for(int i=0;i<extendedlength;i++)
    {
    if(i<messlength)
    encryptedtext[i]=tp[i];
    else
    encryptedtext[i]=0;
    }
    string k;
    ifstream infile;
    infile.open("key.txt");
    if (infile.is_open())
    {
    getline(infile, k); 
    infile.close();
    }

    istringstream tempkey(k);
    unsigned char key[16];
    unsigned int x;
    for(int i=0;i<16;i++)
    {
    tempkey>>hex>>x;
    key[i] = x;
    }
    unsigned char extendedkeys[176];
    Key_extenxion(key,extendedkeys);

    for(int i=0;i<extendedlength;i+=16)
    {
    unsigned char* temp=new unsigned char[16];
    for(int j=0;j<16;j++)
    {
    temp[j]=encryptedtext[i+j];
    }	
    encryption(temp , extendedkeys);
    for(int j=0;j<16;j++)
    {
    encryptedtext[i+j]=temp[j];
    }	
    }
    ofstream fout;  
    ifstream fin;
    fin.open("encryption.aes");
    fout.open ("encryption.aes",ios::app); 
    if(fin.is_open())
    fout<<encryptedtext<<"\n"; 
    fin.close();
    fout.close(); 
    }
    newfile.close(); 
    }
}

void Aes::aes_dec() {

    int extendedlength=0;
    string myText;

    
    sleep(1);
    string tp;
    sleep(1);
    sleep(1); 
    sleep(1);
    ifstream File;
    string filepath = "outputtext.txt";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail())
    {
    File.close();
    printf("\nError : failed to erase file content !");
    }
    File.close();

    ifstream MyReadFile;
    MyReadFile.open("encryption.aes", ios::in | ios::binary);
    if(MyReadFile.is_open())
    {
    while( getline (MyReadFile, myText) )
    {
    cout.flush();
    char * x;
    x=&myText[0];
    int messlength=strlen(x);
    char * msg = new char[myText.size()+1];

    strcpy(msg, myText.c_str());

    int n = strlen((const char*)msg);
    unsigned char * decryptedtext = new unsigned char[n];
    
    for (int i = 0; i < n; i++) {
    decryptedtext[i] = (unsigned char)msg[i];
    }

    string k;
    ifstream infile;
    infile.open("key.txt");
    if (infile.is_open())
    {
    getline(infile, k);
    infile.close();
    }

    else cout << "Unable to open file";
    istringstream tempkey(k);
    unsigned char key[16];
    unsigned int x1;
    for(int i=0;i<16;i++)
    {
    tempkey>>hex>>x1;
    key[i] = x1;
    }
    
    unsigned char extendedkeys[176];
    Key_extenxion(key,extendedkeys);
    
    for (int i = 0; i < messlength; i += 16)
    {
    unsigned char * temp=new unsigned char[16];
    for(int j=0;j<16;j++)
    temp[j]=decryptedtext[i+j];
    decryption(temp , extendedkeys);
    for(int j=0;j<16;j++)
    decryptedtext[i+j]=temp[j];
    }
    for(int i=0;i<messlength;i++)
    {
    cout<<decryptedtext[i];
    if(decryptedtext[i]==0 && decryptedtext[i-1]==0 )
    break;
    }
    cout<<endl;
    ofstream fout;  
    ifstream fin;
    fin.open("outputtext.txt");
    fout.open ("outputtext.txt",ios::app); 
    if(fin.is_open())
    fout<<decryptedtext<<"\n";

    fin.close();
    fout.close(); 
    sleep(5);
    }
    }
    else
    {
    cout<<"Can not open input file\n ";
    }
    cout<<"\n Data has been appended to file outputtext.txt";
    MyReadFile.close();
}