// Ken Livingston 2nd Oct 2012

Bool_t loaded=kFALSE;          //flag that these libs get loaded

//The data types are already enumerated in the lib / header.
//They are:
//enum EEpicsTypes{kEpicsBYTE, kEpicsSTRING, kEpicsSHORT, kEpicsLONG, kEpicsFLOAT, kEpicsDOUBLE};

//define some global arrays for different data types

void loadLibs(){
  Char_t ezcaLib[200];
  //make correct path+name for the library and load it
  sprintf(ezcaLib,"./lib/%s/libRootEzca.so",gSystem->Getenv("EPICS_HOST_ARCH"));
  gSystem->Load(ezcaLib);
  loaded=kTRUE;
}


void readAll(){
  if(!loaded)loadLibs();    //load the libs if required  
  
  Double_t TestTemp;
  epicsGet("TestTemp",kEpicsDOUBLE,1,&TestTemp);
  cout << "TestTemp = " << TestTemp << endl;

  Double_t TestArrayDouble[32];
  epicsGet("TestArrayDouble",kEpicsDOUBLE,20,TestArrayDouble);
  cout  << "TestArray = ";
  for(int n=0;n<20;n++){
    cout  << TestArrayDouble[n] << "  ";
  }
  cout << endl;  
}

void writeAll(){
  if(!loaded)loadLibs();    //load the libs if required  
  
  Double_t TestTemp;
  TestTemp=gRandom->Uniform(-100,100);
  epicsPut("TestTemp",kEpicsDOUBLE,1,&TestTemp);
  cout << "Setting TestTemp = " << TestTemp << endl;

  Double_t TestArrayDouble[32];

  for(int n=0;n<20;n++){
    TestArrayDouble[n]=gRandom->Uniform(-10,10);
  }
  
  epicsPut("TestArrayDouble",kEpicsDOUBLE,20,TestArrayDouble);
  cout  << "Setting TestArray = ";
  for(int n=0;n<20;n++){
    cout  << TestArrayDouble[n] << "  ";
  }
  cout << endl;  
}


