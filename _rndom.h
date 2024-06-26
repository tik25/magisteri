//****************************************************************************
//****************************************************************************
//********************************MISC****************************************
//****************************************************************************
//****************************************************************************
double rnd()
{
    return (double)rand() / (double)RAND_MAX ;
}
//****************************************************************************
int rnd_int(int intnum)
{
    double rndnum=rnd();
    double deltanum=1./(intnum*1.);
    int returnnum=0;
    for (int i=1; i<=intnum; i++){
        if( (i-1)*deltanum<rndnum && rndnum<i*deltanum){
            returnnum=i;
            break;
        }
    }
    
    return returnnum;
}
//****************************************************************************
double GaussianVariate()
{
    
    double sum1=0;
    for(int i=1; i<=6; i++){
        sum1+=rnd();
    }
    
    double sum2=0;
    for(int i=7; i<=12; i++){
        sum2+=rnd();
    }
    
    return sum1-sum2;
}
//****************************************************************************
