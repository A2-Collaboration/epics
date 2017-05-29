// A simple macro to read taggerscalers and make an enhancement.
//
// This has a simple job
// 1. Read all the relevant scalers and energy maps to make up the photon energy spectrum.
// 2. Make a single array and histogram from these.
// 3. Write out an EPICS waverform for the whole tagger.
// 4. Make an enhancement by dividing from a recent amouphous spectrum
// 5. If the radiator is a diamond, fit the coherent edge and write to EPICS.
//
// All information comes from EPICS channels
//
//Uses a library which is a wrapper to ezca
//The data types are already enumerated in the lib / header.
//They are:
//enum EEpicsTypes{kEpicsBYTE, kEpicsSTRING, kEpicsSHORT, kEpicsLONG, kEpicsFLOAT, kEpicsDOUBLE};


Char_t Prefix[50];     //The Epics $(P) marco.
Char_t Grefix[50];     //The Epics $(G) marco.

//and variables for any pv names required.


Char_t HodoEmapPV[50];     //PV names for tagger related scalers
Char_t MicroEmapPV[50];
Char_t HodoScalerPV[50];
Char_t MicroScalerPV[50];
Char_t LowGScalerPV[50];

Char_t HeartbeatPV[50];   //PV to flag that this process is going
Char_t RadiatorPV[50];    //PV for radiator ID on GONI ioc
Char_t IndexPV[50];       //PV for radiator Index on GONI ioc
Char_t ReqEdgePV[50];     //Approximate required coh edge energy MeV
Char_t EdgeMapPV[50];     //Approximate required coh edge energy MeV
Char_t NormEnergyPV[50];  //Energy of the point to normalise the doofer.
Char_t NormCountsPV[50];  //Energy of the point to normalise the doofer.
Char_t BeamCurrentPV[50]; 
Char_t EdgePV[50];        //Coherent edge from the fit.
Char_t WidthPV[50];       //Coherent peak sigma from the fit.

Char_t EmapPV[50];        //PV names for waveforms on CBREM ioc
Char_t RawScalerPV[50];
Char_t EnhScalerPV[50];
Char_t DeadScalerPV[50];
Char_t NscalersPV[50];
Char_t AmoScalerPV[50];
Char_t RefPV[50];

Char_t HodoStatePV[50];  //PV names for status flags on CBREM ioc
Char_t MirocoStatePV[50];
Char_t LowGStatePV[50];  


//Allow 500 channels in each

Double_t HodoEmap[500];
Double_t HodoEmapRev[500];
Double_t HodoScalerRev[500];
Double_t HodoBins[500];
Double_t HodoEmap[500];
Double_t HodoBins[500];
Double_t HodoBins[500];
Double_t MicroEmap[500];
Double_t MicroEmapRev[500];
Double_t MicroScalerRev[500];
Double_t MicroBins[500];
Double_t DeadScalerChans[100];

Double_t Emap[500];
Double_t Ebins[500];

Double_t *Raw;  //pointers to the data buffers of histogram
Double_t *EnhTagger;
Double_t *Amo;
Double_t *Enh;

Int_t    NBins=0;
Int_t    HodoMin=0;
Int_t    HodoMax=0;

Double_t nChanD=0;          //Need the double versions for these for the EPICS read
Int_t    nChan=0;
Double_t radiatorIDD;
Int_t    radiatorID;
Double_t radiatorIndexD;
Int_t    radiatorIndex;
Double_t req_edge;         //desired pos od coh edge
Double_t norm_energy;
Double_t norm_counts;
Double_t beam_current;
Int_t    norm_bin;
Double_t heartbeat=1.0;


Double_t coh_edge;         //actual fitted coherent edge
Double_t coh_width;        //actual fitted peak sigma

//No of channels read from waveform arrays
ULong_t  nHodo=0,nMicro=0,NTotal=0;
Double_t HodoStateD  = 0.0;  //Need the double versions fo these for the EPICS read
Double_t MicroStateD = 0.0;
Double_t LowGStateD  = 0.0;
Int_t    HodoState   = 0;    //Default to not using any
Int_t    MicroState  = 0;
Int_t    LowGState   = 0;

Double_t LowGScaler  = 0;        //for the data read from the scalers 
Double_t *HodoScaler;
Double_t *MicroScaler;

Double_t LowGScalerS  = 0;       //Sim
Double_t *HodoScalerS;            
Double_t *MicroScalerS;

Bool_t libsLoaded   = kFALSE;          //flag that these libs get loaded
Bool_t taggerLoaded = kFALSE;          //flag that the tagger info got loaded

Bool_t sim          = kFALSE;
Double_t isDiam     = kFALSE;
Double_t forceDiam  = kFALSE;

//Histograms
//Make all hists Doubles because the waveform arays are doubles.
TH1D *hHodo, *hMicro, *hRaw, *hEnh, *hPol, *hAmo, *hRef;
TH1D *hHodoS,*hMicroS;                 //Simulated versions.

TCanvas *CbremCanvas;

TRandom1 *random;                      //General random

//For fitting the edge

Double_t GausOnBase(Double_t *, Double_t *);
TF1 *edgeFit=NULL;

//fit of a gaussian on a baseline, for gausFit,
Double_t GausOnBase(Double_t *x, Double_t *par) {
  Double_t arg = 0;
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];
   Double_t fitval = par[3] + par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}

void setReadStatus(Char_t *hbPV, Double_t state, Int_t period){
  Double_t zero=0.0;
  Double_t hb=state;
  gSystem->Sleep(450*period); 
  epicsPut(hbPV,kEpicsDOUBLE,1,&zero);
  gSystem->Sleep(200); 
  epicsPut(hbPV,kEpicsDOUBLE,1,&hb);
  gSystem->Sleep(450*period); 
  epicsPut(hbPV,kEpicsDOUBLE,1,&zero);
}


void loadLibs(){
  Char_t ezcaLib[200];
  //make correct path+name for the library and load it
  // sprintf(ezcaLib,"%s/cbrem/ezcaRoot/lib/%s/libRootEzca.so",gSystem->Getenv("HOME"),gSystem->Getenv("EPICS_HOST_ARCH"));
  sprintf(ezcaLib,"%s/cbrem/ezcaRoot/lib/%s/libRootEzca.so",gSystem->Getenv("HOME"),"linux-x86_64");
  gSystem->Load(ezcaLib);
  libsLoaded=kTRUE;
  epicsSetTimeout(0.1);
  epicsSetRetryCount(2);
}


int  getTaggerInfo(){
  Char_t pv[100];
  Int_t epicsErr=0;
  if(!libsLoaded)loadLibs();       //load the libs if required

  random = new TRandom1();

  //The names of the channels for scalers and emaps are stored in CBREM ioc as stringout PVs.
  //Get the names here
  sprintf(pv,"%sHODO_EMAP_NAME",   Prefix);  epicsErr += epicsGet(pv,kEpicsSTRING,1,HodoEmapPV);
  cout << pv << " = " <<  HodoEmapPV << endl;
  sprintf(pv,"%sHODO_SCALER_NAME", Prefix);  epicsErr += epicsGet(pv,kEpicsSTRING,1,HodoScalerPV);
  cout << pv << " = " <<  HodoScalerPV << endl;
  sprintf(pv,"%sMICRO_EMAP_NAME",  Prefix);  epicsErr += epicsGet(pv,kEpicsSTRING,1,MicroEmapPV);
  cout << pv << " = " << MicroEmapPV << endl; 
  sprintf(pv,"%sMICRO_SCALER_NAME",Prefix);  epicsErr += epicsGet(pv,kEpicsSTRING,1,MicroScalerPV);
  cout << pv << " = " << MicroScalerPV << endl;
  sprintf(pv,"%sLOWG_SCALER_NAME", Prefix);  epicsErr += epicsGet(pv,kEpicsSTRING,1,LowGScalerPV);
  cout << pv << " = " << LowGScalerPV << endl;
  
  
  // figure out which of these things is getting used
  sprintf(pv,"%sHODO_STATE",       Prefix); epicsErr += epicsGet(pv,kEpicsDOUBLE,1,&HodoStateD);  HodoState  = (Int_t)HodoStateD;
  cout << pv << " = " <<  HodoState << endl;
  sprintf(pv,"%sMICRO_STATE",      Prefix); epicsErr += epicsGet(pv,kEpicsDOUBLE,1,&MicroStateD); MicroState = (Int_t)MicroStateD;
  cout << pv << " = " <<  MicroState << endl;
  sprintf(pv,"%sLOWG_STATE",       Prefix); epicsErr += epicsGet(pv,kEpicsDOUBLE,1,&LowGStateD);  LowGState  = (Int_t)LowGStateD; 
  cout << pv << " = " <<  LowGState << endl;

  sprintf(IndexPV,"%sRADIATOR_INDEX",Grefix);   //This is the only info that comes from the GONI ioc
  sprintf(RadiatorPV,"%sRADIATOR_ID",Grefix);   //This is the only info that comes from the GONI ioc
  sprintf(ReqEdgePV,"%sREQ_EDGE",Prefix);   
  sprintf(EdgeMapPV,"%sEDGE_LINE_MAP",Prefix);   
  sprintf(EdgePV,"%sEDGE",Prefix);   
  sprintf(WidthPV,"%sWIDTH",Prefix);   
  sprintf(RawScalerPV,"%sRAW_SCALERS",Prefix);
  sprintf(AmoScalerPV,"%sAMO_SCALERS",Prefix);
  sprintf(EnhScalerPV,"%sENH_SCALERS",Prefix);
  sprintf(DeadScalerPV,"%sDEAD_SCALERS",Prefix);
  sprintf(NormEnergyPV,"%sNORM_ENERGY",Prefix);
  sprintf(NormCountsPV,"%sNORM_COUNTS",Prefix);
  sprintf(BeamCurrentPV,"IBCAD00CRCUR6");
  sprintf(RefPV,"%sENH_REF",Prefix);
  sprintf(HeartbeatPV,"%sHEARTBEAT",Prefix);
  
	  
  if(epicsErr){
    cout << "FATAL ERROR reading EPICS Channels. Exiting." << endl;
    return -1;
  }
  
  if(HodoState){
    //read no of hodo elements
    sprintf(pv,"%s.NELM",HodoEmapPV); epicsGet(pv,kEpicsLONG,1,&nHodo);
    if(HodoState==1)epicsGet(HodoEmapPV, kEpicsDOUBLE, nHodo, HodoEmap);
    else{                               //reversed order in GeV
      epicsGet(HodoEmapPV, kEpicsDOUBLE, nHodo, HodoEmapRev);
      for(int n=0;n<nHodo;n++){
        HodoEmap[n]=1000.0*HodoEmapRev[(nHodo-1)-n];
      }
    }
    //make bins for hodo histogram
    cout << "pv=" << pv << ", nHodo =" << nHodo << endl;
    for(int n=1;n<nHodo-1;n++) HodoBins[n]=0.5*(HodoEmap[n-1]+HodoEmap[n]);
    HodoBins[0]       =   HodoBins[1]       - (HodoBins[2]        -   HodoBins[1]);
    HodoBins[nHodo-1] =   HodoBins[nHodo-2] + (HodoBins[nHodo-2]  -   HodoBins[nHodo-3]);    
    HodoBins[nHodo]   =   HodoBins[nHodo-1] + (HodoBins[nHodo-1]  -   HodoBins[nHodo-2]);    
    hHodo  = new TH1D("hHodo", "Hodoscope Scalers;E_{g}/MeV",      nHodo, HodoBins); //make the hists
    hHodo->SetMinimum(0); hHodo->SetStats(0);
    HodoScaler = hHodo->GetArray();     //point to 1st bin of histogram epics will read straight to here

    if(sim){                              //if sim, make hists for simulated data
      hHodoS = new TH1D("hHodoS", "Hodoscope Scalers Sim;E_{g}/MeV", nHodo, HodoBins);
      hHodoS->SetMinimum(0);hHodoS->SetStats(0);
      HodoScalerS = hHodoS->GetArray(); //point to 1st bin of histogram epics will write straight from here
    }

  }
  
  
  if(MicroState){
    //read no of micro elements
    sprintf(pv,"%s.NELM",MicroEmapPV); epicsGet(pv,kEpicsLONG,1,&nMicro);
    if(MicroState==1) epicsGet(MicroEmapPV, kEpicsDOUBLE, nMicro, MicroEmap);
    else{                               //reversed order in GeV
      epicsGet(MicroEmapPV, kEpicsDOUBLE, nMicro, MicroEmapRev);
      for(int n=0;n<nMicro;n++){
        MicroEmap[n]=1000.0*MicroEmapRev[(nMicro-1)-n];
      }
    }

    //make bins for micro histogram
    for(int n=1;n<nMicro-1;n++) MicroBins[n]=0.5*(MicroEmap[n-1]+MicroEmap[n]);
    MicroBins[0]        =   MicroBins[1]        - (MicroBins[2]         -   MicroBins[1]);
    MicroBins[nMicro-1] =   MicroBins[nMicro-2] + (MicroBins[nMicro-2]  -   MicroBins[nMicro-3]);    
    MicroBins[nMicro]   =   MicroBins[nMicro-1] + (MicroBins[nMicro-1]  -   MicroBins[nMicro-2]);    
    hMicro  = new TH1D("hMicro","Microscope Scalers;E_{g}/MeV",      nMicro,MicroBins); //make the hists
    hMicro->SetMinimum(0); hMicro->SetStats(0);
    MicroScaler = hMicro->GetArray();   //point to 1st bin of histogram epics will read straight to here

    if(sim){                              //if sim, make hists for simulated data
    hMicroS = new TH1D("hMicroS","Microscope Scalers Sim;E_{g}/MeV", nMicro,MicroBins);
    hMicroS->SetMinimum(0);hMicroS->SetStats(0);
    MicroScalerS = hMicroS->GetArray(); //point to 1st bin of histogram epics will write straight from here
    }

  }
  
  //Figure out how to construct the full tagger spectrum from up to 3 components
  Emap[nChan++] = 1.0;            //Make a 1.0 MeV point for low Energy scaler.
  if((!HodoState)&&(!MicroState)&&(!LowGState)){
    cout << "FATAL ERROR No photon detectors enabled. Exiting." << endl;
    return -1;
  }
  
  if ((HodoState)&&(!MicroState)){       //Hodo only
    for(int n=0;n<nHodo;n++){            //Copy hodo channels to main Emap
      Emap[nChan++]=HodoEmap[n];
    }
  }
  else if((!HodoState)&&(MicroState)){   //Micro only
    for(int n=0;n<nMicro;n++){           //Copy micro channels to main Emap
      Emap[nChan++]=MicroEmap[n];
    }    
  }
  else if((HodoState)&&(MicroState)){    //hodo and micro
    int h=0;
    while(HodoEmap[h]<MicroEmap[0]){     //use hodo until we hot the micro
      Emap[nChan++]=HodoEmap[h++];
    }
    h--;
    HodoMin = h;
    for(int n=0;n<nMicro;n++){           //Copy micro channels to main Emap
      Emap[nChan++]=MicroEmap[n];
    }    
    while(HodoEmap[h++]<=MicroEmap[nMicro-1]);  //get to 1st hodo chan greater than last micro chan
    h--;
    HodoMax=h;
    for(int n=HodoMax;n<nHodo;n++){           //Copy micro channels to main Emap
      Emap[nChan++]=HodoEmap[n];
    }    
  }
  

  //make bins for histograms
  //Like this:  n   0   1                          2      3   ...     nChan       
  //Emap =          1   2                          40    46      
  //Ebins=        0   2                         37    43    49
  //            n 0   1                         2     3     4 ...       nChan+1
  //A histogram axis with a low energy bin and bin centres from the EMap.
  Ebins[0] = 0.0; Ebins[1] = 2.0;              //Force a 0 MeV bin
  Ebins[2] = Emap[1]-0.5*(Emap[2]-Emap[1]);    
  for(n=1;n<nChan-1;n++) Ebins[n+2] = 0.5*(Emap[n]+Emap[n+1]);
  Ebins[nChan+1] = Emap[nChan-1]+0.5*(Emap[nChan-1]-Emap[nChan-2]);

  hRaw   = new TH1D("hRaw",  "Raw Tagger Scalers;E_{g}/MeV",       nChan+1, Ebins); //make the hists
  Raw = hRaw->GetArray();
  hEnh   = new TH1D("hEnh",  "Tagger Enhancement;E_{g}/MeV",       nChan+1, Ebins); 
  Enh    = hEnh->GetArray();
  hAmo   = new TH1D("hAmo",  "Amorphous Scalers (Ref); E_{g}/MeV", nChan+1, Ebins); 
  Amo    = hAmo->GetArray();
  hRef   = new TH1D("hRef",  "Tagger Enhancememt (Ref);E_{g}/MeV", nChan+1, Ebins); 

  hRaw->SetMinimum(0);  hRaw->SetStats(0);
  hEnh->SetMinimum(0);  hEnh->SetStats(0);
  hAmo->SetMinimum(0);  hAmo->SetStats(0);
  hRef->SetMinimum(0);  hRef->SetStats(0);

  //Write these things out to EPICS
  sprintf(EmapPV,"%sEMAP",Prefix);
  epicsPut(EmapPV,kEpicsDOUBLE,nChan,Emap);
  nChanD = nChan;
  sprintf(NscalersPV,"%sN_SCALERS",Prefix);
  epicsPut(NscalersPV,kEpicsDOUBLE,1,&nChanD);

  taggerLoaded=kTRUE; //flag that all the stuff is loaded up

  CbremCanvas = new TCanvas("CbremCanvas","CbremCanvas",20,20,800,600);
  
  return 0;
  
}



void makeEnh(const Char_t *P="HD:CBREM:", const Char_t *G="HD:GONI:", Int_t simulated = 0, Int_t period=2){
  Int_t chan;
  Double_t fitmin,fitmax,maxgrad;
  Double_t edgemap[2];
  
  strcpy(Prefix,P);
  strcpy(Grefix,G);

  if(simulated) sim = kTRUE;  //assume its simulated mode
  
  if(!taggerLoaded){
    //    if( getTaggerInfo() < 0) exit();
    if( getTaggerInfo() < 0) return;
  }

  //Now were going into a loop reading the scalers from all required counters, making an enhancemnent if required
  //and if the current radiator is a diamond, try to fit the coherent edge.
  while(1){    //loop forever

    while(1){    //loop until there's a decent count in the specified norm_channel
                 //ie the beam is actually on
      
      epicsGet(IndexPV,   kEpicsDOUBLE,1,&radiatorIndexD); radiatorIndex  = (Int_t)radiatorIndexD; //Get radiator Index
      epicsGet(RadiatorPV,kEpicsDOUBLE,1,&radiatorIDD);    radiatorID     = (Int_t)radiatorIDD;    //Get radiator ID
      epicsGet(ReqEdgePV, kEpicsDOUBLE,1,&req_edge); 
      epicsGet(NormEnergyPV, kEpicsDOUBLE,1,&norm_energy); 
      epicsGet(NormCountsPV, kEpicsDOUBLE,1,&norm_counts);
      epicsGet(BeamCurrentPV, kEpicsDOUBLE,1,&beam_current);
      epicsGet(DeadScalerPV, kEpicsDOUBLE,100,DeadScalerChans); 
      
      norm_bin=hRaw->FindBin(norm_energy);
      
      if((radiatorID&&radiatorIndex)||forceDiam) isDiam=kTRUE;
      else isDiam=kFALSE; 
      
      if(sim)simulateTaggerSimple(); //if were in sim mode, fill the required PVs from simulation.
      if(LowGState) epicsGet(LowGScalerPV,kEpicsDOUBLE,1,&LowGScaler);
      if(HodoState==1) epicsGet(HodoScalerPV,kEpicsDOUBLE,nHodo,HodoScaler);
      else if(HodoState==2){
        epicsGet(HodoScalerPV,kEpicsDOUBLE,nHodo,HodoScalerRev);
        for(int n=0;n<nHodo;n++){
          HodoScaler[n]=HodoScalerRev[(nHodo-1)-n];
        }
      }
      if(MicroState==1) epicsGet(MicroScalerPV,kEpicsDOUBLE,nMicro,MicroScaler);
      else if(MicroState==2){
        epicsGet(MicroScalerPV,kEpicsDOUBLE,nMicro,MicroScalerRev);
        for(int n=0;n<nMicro;n++){
          MicroScaler[n]=MicroScalerRev[(nMicro-1)-n];
        }
      }
      
      
      chan=0;
      Raw[chan++]=LowGScaler;    
      Raw[chan++]=0.0;    
      //Make up the raw tagger
      
      if ((HodoState)&&(!MicroState)){       //Hodo only
        for(int n=0;n<nHodo;n++){            //Copy hodo channels to main Emap
          Raw[chan++]=HodoScaler[n];
        }
      }
      
      else if((!HodoState)&&(MicroState)){   //Micro only
        for(int n=0;n<nMicro;n++){           //Copy micro channels to main Emap
          Raw[chan++]=MicroEmap[n];
        }    
      }
      
      else{    //hodo and micro
        for(int n=0;n<=HodoMin;n++){
          Raw[chan++]=HodoScaler[n];
        }
        for(int n=0;n<nMicro;n++){           //Copy micro channels to main Emap
          Raw[chan++]=MicroScaler[n];
        }    
        for(int n=HodoMax;n<=nHodo;n++){
          Raw[chan++]=HodoScaler[n];
        }        
      }
      cout << "Beam Current: " << beam_current << ",   threshold:" << norm_counts << endl;
      //     cout << hRaw->GetBinContent(norm_bin) << " <   " << norm_counts << endl;
      //if(hRaw->GetBinContent(norm_bin) > norm_counts) {
      if(beam_current > norm_counts){
	setReadStatus(HeartbeatPV,1.0,period);
        break;
      }
      else
        setReadStatus(HeartbeatPV,-1.0,period);
    }
    
    chan--;
    epicsPut(RawScalerPV,kEpicsDOUBLE,chan,Raw);
    
    //Read the amo current reference
    epicsGet(AmoScalerPV,kEpicsDOUBLE,chan,Amo);
    for(int n=0;n<chan;n++){ 
      Enh[n]=Raw[n];    //copy the Raw to the Enh histogram
    }
    hEnh->Divide(hAmo);  //divide by the amo
    //hEnh->Scale(hAmo->GetBinContent(hAmo->FindBin(1.2*req_edge))/hRaw->GetBinContent(hAmo->FindBin(1.2*req_edge)));
    hEnh->Scale(1.0/hEnh->GetBinContent(norm_bin));


    for(int n=0;n<100;n++){                      //loop over list of bad chans, and for those above 20, copy the 
      if(DeadScalerChans[n] < 0.0) break;        //-1 is the end of the list
      if(DeadScalerChans[n] < 20.0 ) continue;   //content of the previous channel
      else hEnh->SetBinContent(DeadScalerChans[n],hEnh->GetBinContent(DeadScalerChans[n]-1));
    }    

    epicsPut(EnhScalerPV,kEpicsDOUBLE,chan,Enh);

    if(isDiam){
      //try to fit the coherent edge if running with diamond
      //find the maximum bin with 20% of the required peak pos. 
      fitmin=0.0;fitmax=0.0;
      for(int n=hEnh->FindBin(0.95*req_edge);n<hEnh->FindBin(1.05*req_edge);n++){
	if(hEnh->GetBinContent(n)>fitmax){
	  fitmax=hEnh->GetBinContent(n);
	  fitmin=hEnh->GetBinCenter(n);
	}
      }
      if(!edgeFit)edgeFit=new TF1("edgeFit",GausOnBase,0,100,4);
      edgeFit->SetRange(fitmin,1.1*fitmin);
      edgeFit->SetParameter(0,fitmax);
      edgeFit->FixParameter(1,fitmin);
      edgeFit->SetParameter(2,10.0);
      edgeFit->SetParameter(3,1.0);
      cout << fitmin << "   " << fitmax << endl;
      hEnh->Fit("edgeFit","R");
      
      if(strstr(gMinuit->fCstatu.Data(),"FAILED")){ //check if fit failed
	coh_edge=-1.0;                              //the make edge = -1
        coh_width=-1.0;
      }
      else{
        coh_width = edgeFit->GetParameter(2);                            //sigma
        coh_edge  = edgeFit->GetParameter(1) + edgeFit->GetParameter(2);   //edge is mean +sigma
      }
      edgemap[0]=coh_edge;edgemap[1]=coh_edge;
      epicsPut(EdgePV,kEpicsDOUBLE,1,&coh_edge);
      epicsPut(EdgeMapPV,kEpicsDOUBLE,2,&edgemap);

      epicsPut(WidthPV,kEpicsDOUBLE,1,&coh_width);
    
      cout << "Peak = " << fitmin << " MeV,  Edge = " << coh_edge << " MeV,  Width = " << coh_width << " MeV" << endl;
    }
    hEnh->Draw();
    CbremCanvas->Update();
    gSystem->ProcessEvents();
    
  }
}



void simulateTaggerSimple(Double_t counts=10000000.0, Double_t sigma = 40.0){
  //If the radiator amo, generate a 1/E distro with some randomness.
  Double_t val;
  Double_t edge;
  Int_t hodoPeakBin=0,microPeakBin=0;
  Double_t sigma;
  Double_t lcounts;
  Int_t b=0;

  lcounts=random->Uniform(0.2*counts, 5.0*counts);

  
  if(isDiam){
    //    edge  = random->Uniform(Ebins[(int)(0.2*nChan)],Ebins[(int)(0.8*nChan)]); //choose bin for coh peak
    edge  = random->Uniform(0.9*req_edge,1.1*req_edge); //choose bin for coh peak
    if(HodoState) hodoPeakBin   = hHodo->FindBin(edge);
    if(MicroState) microPeakBin = hMicro->FindBin(edge);   
    //cout << "edge= " << edge << "  hodoPeakBin= " << hodoPeakBin<< endl;
  }

  if(HodoState){
    for(int n=1; n<=hHodoS->GetNbinsX(); n++){
      if(HodoState==2) b = nHodo-n;
      else b=n;
      val=lcounts*hHodoS->GetBinWidth(n)/hHodoS->GetBinCenter(n);      //1/E part
      if((isDiam)&&(hodoPeakBin>0)&&(hodoPeakBin<nHodo)){          //if diamond and peak in range
	if(n>=hodoPeakBin) val+= (10000.0/(edge*edge))*lcounts*hHodoS->GetBinWidth(n)*TMath::Gaus(hHodoS->GetBinCenter(n),edge,sigma);
	else val+= (10000.0/(edge*edge))*lcounts*hHodoS->GetBinWidth(n)*TMath::Gaus(hHodoS->GetBinCenter(n),edge,5.0*sigma);
      }
      hHodoS->SetBinContent(b, random->Gaus(val,TMath::Sqrt(val))); //error from sqrt of lcounts
    }
    epicsPut(HodoScalerPV,kEpicsDOUBLE,nHodo,HodoScalerS);
  }
  
  if(MicroState){
    for(int n=1; n<=hMicroS->GetNbinsX(); n++){
      if(MicroState==2) b = nMicro-n;
      else b=n;
      val=lcounts*hMicroS->GetBinWidth(n)/hMicroS->GetBinCenter(n);    //1/E part
      if((isDiam)&&(microPeakBin>0)&&(microPeakBin<nMicro)){          //if diamond and peak in range
	if(n>=microPeakBin) val+= (10000.0/(edge*edge))*lcounts*hMicroS->GetBinWidth(n)*TMath::Gaus(hMicroS->GetBinCenter(n),edge,sigma);
	else val+= (10000.0/(edge*edge))*lcounts*hMicroS->GetBinWidth(n)*TMath::Gaus(hMicroS->GetBinCenter(n),edge,5.0*sigma);
      }
      hMicroS->SetBinContent(b, random->Gaus(val,TMath::Sqrt(val)));
    }
    epicsPut(MicroScalerPV,kEpicsDOUBLE,nMicro,MicroScalerS);
  }
}

