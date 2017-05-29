// ROOT macro to plot hv-scan and work out the beam center
// see stonehenge.ps in this directory
// Expects a data file in the following format ***********************
// #tag_chans   steps   start   step_size       v_off   h_off    radius
// 352          180     0.0     2.0             0.0     0.0      60.0
// step 0
// 0
// 142
// 140
// ..
// ..
// step 1
//
// etc
//
// *******************************************************************
//
// After each step 0 line there should be "normalised" photon spectra
// beginning with the lowest photon energy bin up to the no of tagger channels
// eg. see  scan_phi_default.txt in this directory
// The normalisation should have been done by dividing the coherent spectrum
// by an incoherent one from an amorphous radiator and multiplying by a factor
// which sets the baseline to about 1
// In practice get the normalisation value from a high photon energy bin where
// the coherent contributions are expected to be low.
// eg.
// norm_val = 100*amorph_data[0.9*tagger_chan_max]/crystal_data[0.9*tagger_chan_max];
// for(n=0;n<tagger_chan_max;n++){
//      if((amorph_data[n])==0){
//               norm_data[n]=norm_data[n-1];
//      }
//      else{
//              norm_data[n]=norm_val*crystal_data[n]/amorph_data[n];
//      }
// }
// Notice that for any dead tagger channels (ie amorph_data[n] == 0 )
// data is copied from the previous channel to keep things smooth
// For very inefficient tagger channels it is best to set their value to
// zero by editing the amorphous reference spectrum in an editor before proceeding

// To run this code do
// >root
// root> .x hv.C("filename", type, point0,point1,point2,point3);
// The type can be 0 or 1
// The points are the angles in degrees of where you think the 022 vectors
// hit the edge of the inner circle
// 0 will mean the values of the points are ignored and only the polar graph drawn
// 1 means the points will be used draw orthogonal lines an work out offsets
//
// Try with file scan_phi_default.txt in this directory as follows:
// root> .x hv.C("scan_phi_default.txt",0,0,0,0,0);
//      this should just draw the plot
// root> .x hv.C("scan_phi_default.txt",1,92,231,271,313)
//      this should fit it correctl
//
// Try to guess your own values with the file "scan_phi_default180.txt"
// where the crystal was rotated by 180 deg.
//
// If the data acquisition can produce output directly in the format described above
// then it is possible to repeatedly run hv.C on the data file while the data is accummulating.

//in this version we use a map of the energy bins for the enhancement.


TCanvas *cLinPol;               // the canvas
Int_t xRange=352;
Int_t steps=180;
Float_t start=0;
Float_t stepSize=2;
Float_t aoff=0;
Float_t voff=0;
Float_t hoff=0;
Float_t radius=60.0;
Float_t vother,hother;

TH1F *slice;            // for slice
TH2F *scan;            // for slice
Float_t data[600], data2[600];      // to read the data

//got the EMAP from here: caget HD:CBREM:EMAP
Double_t emap[500] = {1, 1412.44, 1440.11, 1467.9, 1495.62, 1523.46, 1551.19, 1578.97, 1606.75, 1634.53, 1662.31, 1690.1, 1717.88, 1744.38, 1772.17, 1799.89, 1827.67, 1855.46, 1883.24, 1911.02, 1938.8, 1966.58, 1995.7, 2023.43, 2051.26, 2079.1, 2106.27, 2134.17, 2162.45, 2190.17, 2217.96, 2245.68, 2272.3, 2300.08, 2328.97, 2355.65, 2384.54, 2411.15, 2439.99, 2466.72, 2495.5, 2522.23, 2551.06, 2577.74, 2605.57, 2633.36, 2661.14, 2690.03, 2717.87, 2745.65, 2773.43, 2800.66, 2829, 2856.72, 2884.51, 2912.23, 2938.9, 2966.68, 2995.58, 3022.3, 3051.14, 3077.87, 3106.65, 3133.38, 3162.16, 3188.94, 3217.78, 3244.62, 3272.45, 3300.24, 3328.07, 3356.8, 3384.58, 3412.37, 3440.15, 3467.93, 3495.71, 3523.49, 3551.22, 3579.06, 3605.95, 3634.62, 3653.4, 3661.63, 3669.85, 3677.07, 3685.19, 3693.35, 3700.52, 3708.58, 3709.75, 3715.3, 3720.86, 3726.41, 3731.97, 3737.53, 3743.08, 3748.64, 3754.2, 3759.75, 3765.31, 3770.87, 3776.42, 3781.98, 3787.26, 3792.81, 3798.09, 3803.65, 3809.21, 3814.48, 3819.76, 3825.32, 3830.6, 3836.15, 3841.43, 3846.71, 3851.99, 3857.27, 3862.82, 3867.83, 3873.38, 3878.38, 3883.94, 3888.94, 3894.5, 3899.5, 3904.5, 3910.05, 3915.05, 3920.33, 3925.61, 3930.61, 3935.61, 3941.17, 3946.17, 3951.17, 3956.17, 3961.17, 3966.73, 3971.73, 3976.73, 3981.73, 3986.73, 3991.73, 3996.73, 4001.74, 4006.74, 4011.74, 4016.74, 4021.74, 4026.74, 4031.46, 4036.46, 4041.19, 4046.19, 4051.19, 4056.19, 4060.91, 4065.63, 4070.63, 4075.36, 4080.08, 4085.08, 4089.8, 4094.53, 4099.53, 4104.25, 4108.97, 4113.7, 4118.42, 4123.14, 4127.87, 4132.59, 4137.31, 4142.03, 4146.76, 4151.48, 4155.93, 4160.93, 4165.37, 4169.82, 4174.82, 4179.26, 4183.71, 4188.43, 4193.15, 4197.6, 4202.04, 4206.77, 4211.49, 4214.27, 4223.99, 4234.44, 4244.83, 4254.39, 4264.72, 4274.89, 4284.28, 4294.39, 4304.45, 4313.67, 4323.56, 4333.4, 4342.51, 4352.18, 4361.9, 4370.85, 4380.41, 4389.96, 4398.74, 4408.08, 4417.52, 4426.08, 4435.3, 4444.53, 4452.92, 4461.97, 4471.03, 4479.31, 4488.2, 4497.09, 4505.2, 4513.93, 4522.59, 4530.54, 4539.15, 4547.65, 4555.49, 4563.88, 4572.27, 4579.88, 4588.1, 4596.33, 4603.83, 4611.89, 4619.94, 4627.28, 4635.17, 4643.11, 4650.28, 4660.23, 4672.45, 4683.84, 4696.01, 4707.12, 4719.01, 4729.96, 4741.57, 4752.3, 4763.69, 4774.19, 4785.36, 4795.58, 4806.42, 4816.47, 4827.09, 4836.87, 4848.42, 4860.48, 4872.98, 4884.65, 4896.76, 4908.1, 4919.88, 4930.88, 4942.33, 4952.99, 4964.11, 4974.5, 4985.28, 4995.28, 5005.73, 5015.45, 5025.56, 5035.01, 5044.79, 5053.95, 5063.46, 5072.29, 5081.51, 5090.07, 5101.52, 5114.85, 5128.19, 5140.8, 5153.47, 5165.42, 5177.42, 5188.75, 5200.14, 5210.87, 5221.59, 5231.76, 5241.93, 5251.54, 5261.15, 5270.27, 5279.27, 5287.82, 5297.6, 5308.16, 5318.44, 5328.22, 5337.78, 5346.78, 5355.67, 5364, 5372.17, 5379.84, 5387.4, 5394.45, 5401.4, 5407.9, 5414.29, 5420.29, 5426.12, 5431.62, 5437.01, 5442.07, 5447.02, 5451.68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


Double_t bin[500];

StoneDraw(char *filename, Int_t stype, Double_t pk0, Double_t pk1,Double_t pk2,Double_t pk3){
  Float_t uL=360.0;       // limits of histograms
  Float_t lL=0.0;
  Int_t i,n;              // general indices
  FILE *fp;               // for data file
  Int_t npeaks;           // no of peak
  Double_t peaks[20];     // to hold peaks
  Float_t pkx[4],pky[4];  //
 TLine *line[4];         // lines drawn on canvas
 TArrow *arrow;          // arrow on canvas
 Double_t const  PI        = 3.14159265358979323846;
 Double_t grad[2];       // gradients, offsets for line eqns
 Double_t offset[2];
 Double_t beam[2];       // beam position coords
 TLatex *t;              // for latex text
 TPaveText *lab1;        // text label thing
 Char_t labstring[128];  // to hold label strings
 Char_t linet[300];      // for reading lines from input file
 TEllipse *el = new TEllipse();
 TLine *prot;
 float ptheta;
 float prad;
 float px1,px2,py1,py2;
 

  if((fp = fopen(filename,"r")) == NULL){	//open file
    fprintf(stderr,"couldn't open file: %s\n",filename);
    //   exit (-1);
  }


  fscanf(fp,"%d%d%f%f%f%f%f%f%f\n",	//read scan details
	  &xRange,
	 &steps,
	 &start,
	 &stepSize,
	 &vother,
	 &hother,
	 //	 &type,
	 &voff,
	 &hoff,
	 &aoff);
  //	 &lL, 
  //	 &uL);

  radius = vother;	//radius of scan in deg
  //create hist of appropriate dimensions

  bin[0]=0.0;
  bin[1]=emap[xRange-1];
  for(int i=0;i<xRange;i++){
    bin[i+2]=emap[i]+emap[xRange-1];
  }
  
  
  // scan = new TH2F(filename,filename,steps,lL, uL, xRange,0,(Float_t)xRange);
  scan = new TH2F(filename,filename,steps,lL, uL, xRange,bin);

  npeaks = 0;
  //besttotal = 0;

  for(int j=0;j<steps;j++){  	// for each step in scan
    float total=0;
    for(int i=0;i<xRange;i++){	// for each scaler channel
    //    for(int i=xRange-1;i>=0;i--){	// for each scaler channel
      data[i]=100.0;			//zero the data
      if(fscanf(fp,"%f",&data[i])!=1){	//read the data
	//if((data[i]>400.0)||(data[i]<90.0))	  data[i]=data[i-1];	
	//fprintf(stdout,"data %f\n",data[i]);
	j=steps;			//force out of loop in no data left
	break;
      }
      data[i]*=100.0;
      //cout << "i = " << i << ", data[i] = " << data[i] << endl; 
      total+=data[i];
    }

    int k=0;
    for(int i=0;i<xRange;i++){
      scan->Fill(start+j*stepSize+(0.5*stepSize),bin[i+2]+0.5,data[i]);
    }

  }
  fclose(fp);		// close the file

  cLinPol = new TCanvas("cLinPol","Canvas Example",200,10,800,800); //create square canvas
  cLinPol->SetFillColor(0);
  gStyle->SetOptStat(0); //switch off the annoying statistics box
  gStyle->SetPalette(1); //Make the colours look nicer

  lL=0.0;                       //lower and upper limits for histogram
  uL=steps*stepSize;



  scan->SetMinimum(100.0);      //set some good limits for nice contours
  scan->SetMaximum(300.0);
  //  scan->GetYaxis()->SetRangeUser(emap[1]+emap[xRange-1],2*emap[xRange-2]);
  scan->Draw("polcont4");       // draw the histogram
  scan->GetXaxis()->SetAxisColor(0);
  scan->GetYaxis()->SetAxisColor(0);
  scan->GetXaxis()->SetLabelColor(0);
  scan->GetYaxis()->SetLabelColor(0);
  scan->GetXaxis()->SetTickLength(0);
  scan->GetYaxis()->SetTickLength(0);
  

  //put the big white circle in the middle
  prad=0.295;
  el->SetFillColor(0);
  el->DrawEllipse(0.0,0.0,prad,prad,0,360,90);
  //put on some axes to guide guessing of angles
  // and protractor
  arrow = new TArrow(-1.05*0.575,-1.05*0.575*(sin(PI*(stepSize/2)/180)),
                      1.1*0.575,1.05*0.575*(sin(PI*(stepSize/2)/180)),
                      0.01,"|>");
  arrow->SetFillColor(1);
  arrow->Draw();
  arrow = new TArrow(1.05*0.575*(sin(PI*(stepSize/2)/180)),-1.05*0.575,
                     -1.05*0.575*(sin(PI*(stepSize/2)/180)),1.1*0.575,
                      0.01,"|>");
  arrow->SetFillColor(1);
  arrow->Draw();

  for(ptheta=0.0;ptheta<359.5;ptheta+=1.0){
    px1=(0.995*prad*cos(PI*(ptheta+stepSize/2)/180));
    py1=(0.995*prad*sin(PI*(ptheta+stepSize/2)/180));
    px2=(prad*cos(PI*(ptheta+stepSize/2)/180));
    py2=(prad*sin(PI*(ptheta+stepSize/2)/180));
    prot= new TLine(px1,py1,px2,py2);
    prot->Draw();
  }
  for(ptheta=0.0;ptheta<359.5;ptheta+=10.0){
    px1=(0.95*prad*cos(PI*(ptheta+stepSize/2)/180));
    py1=(0.95*prad*sin(PI*(ptheta+stepSize/2)/180));
    px2=(prad*cos(PI*(ptheta+stepSize/2)/180));
    py2=(prad*sin(PI*(ptheta+stepSize/2)/180));
    prot= new TLine(px1,py1,px2,py2);
    prot->Draw();
  }
  t = new TLatex();
  t->SetTextFont(22);
  t->SetTextColor(1);
  t->SetTextSize(0.03);
  t->SetTextAlign(12);
  t->DrawLatex(-0.05,0.6, "pitch^{#circ}");
  t->DrawLatex(0.590,-0.05, "yaw^{#circ}");

  if(stype==0) return;  //if type 0 retutn after drawing plot


  //    Next section works out the offsets and phi

  peaks[0]=pk0;         // store the peaks
  peaks[1]=pk1;
  peaks[2]=pk2;
  peaks[3]=pk3;

  // Get coords of peaks rel to origin
  for(int n=0;n< 4;n++){
    pkx[n]=radius*cos(PI*(peaks[n]/180.0));
    pky[n]=radius*sin(PI*(peaks[n]/180.0));
  }

  //get gradients of 2 lines
  grad[0]= (pky[2]-pky[0])/((pkx[2]-pkx[0])+0.001);
  grad[1]= (pky[3]-pky[1])/((pkx[3]-pkx[1])+0.001);

  // get offsets of 2 lines
  offset[0] = pky[0]-(grad[0]*pkx[0]);
  offset[1] = pky[1]-(grad[1]*pkx[1]);

  beam[0]=(offset[1]-offset[0])/((grad[0]-grad[1])+0.001);
  beam[1]= (grad[0]*beam[0])+offset[0];



  float phi0 = 180*atan(grad[0])/PI;
  float phi1 = 180*atan(grad[1])/PI;

  if(phi0>45.0){
    while(phi0>45.0) phi0-=90.0;
  }
  if(phi0<-45.0){
    while(phi0<-45.0) phi0+=90.0;
  }
  if(phi1>45.0){
    while(phi0>45.0) phi0-=90.0;
  }
  if(phi1<-45.0){
    while(phi0<-45.0) phi0+=90.0;
  }

  float phi_mean=0.5*(phi0+phi1);
   lab1 = new TPaveText(-0.7,-0.7,0.7,-0.6);
   lab1->SetTextFont(22);
   //   lab1->SetTextAlign(12);
   //   beam[0]+=voff;
   // beam[1]+=hoff;
   //   sprintf(labstring,"Beam(SB)=(SB_{v}, SB_{h})=(%6.3f,%6.3f) deg,  #phi_{0}=%6.2f deg\n",beam[0],beam[1],phi_mean);
  sprintf(labstring,"Beam(SB)=(SB_{v}, SB_{h})=(%6.3f,%6.3f) deg,  #phi_{0}=%6.1f deg\n",beam[0],beam[1],phi0);
   lab1->AddText(labstring);
   sprintf(labstring,"Beam to Crystal vector BC = -(S+SB) = (%6.3f,%6.3f) deg",-(beam[0]+voff),-(beam[1]+hoff));
   lab1->AddText(labstring);
   lab1->Draw();

   fprintf(stdout,"\n phi0 = Mean(%6.2f,%6.2f) = %6.2f\n",phi0,phi1,phi_mean);
   fprintf(stdout,"\nBeam phi0,theta_v,theta_h = %6.2f, %6.3f, %6.3f, %6.2f \n",phi_mean,phi1,beam[0],beam[1]);

   fprintf(stdout,"\nNew values for offsets:\n");
   fprintf(stdout,"off_yaw: %6.3f deg\noff_pitch: %6.3f deg\nPHI022: %6.1f deg\n",
           beam[0]+voff,
           beam[1]+hoff,
           aoff-phi0);
   //   fprintf(stdout,"Where xxx means leave as original value\n");


  // To do the drawing we need know that the plot is rotated by 0.5 * step size
  // since the data goes at the bin centres
  // add 0.5 to peak angles and recalculate for the purposes of drawing

  for(int pk=0;pk<4;pk++){
    peaks[pk]+=0.5*stepSize;
  }
  // Get coords of peaks rel to origin
  for(int n=0;n< 4;n++){
    pkx[n]=radius*cos(PI*(peaks[n]/180.0));
    pky[n]=radius*sin(PI*(peaks[n]/180.0));
  }

  //get gradients of 2 lines
  grad[0]= (pky[2]-pky[0])/((pkx[2]-pkx[0])+0.001);
  grad[1]= (pky[3]-pky[1])/((pkx[3]-pkx[1])+0.001);

  // get offsets of 2 lines
  offset[0] = pky[0]-(grad[0]*pkx[0]);
  offset[1] = pky[1]-(grad[1]*pkx[1]);

  beam[0]=(offset[1]-offset[0])/((grad[0]-grad[1])+0.001);
  beam[1]= (grad[0]*beam[0])+offset[0];



  //  float phi0 = 180*atan(grad[0])/PI;
  //if(phi0<0.0) phi0+=90.0;
  //float phi1 = 180*atan(grad[1])/PI;
  //if(phi1<0.0) phi1+=90.0;
  //phi_mean=0.5*(phi0+phi1);

  line[0] = new TLine(0.295*pkx[0]/radius,0.295*pky[0]/radius,0.295*pkx[2]/radius,0.295*pky[2]/radius);
  line[0]->SetLineColor(2);
  line[0]->SetLineWidth(3);
  line[0]->Draw();
  line[0] = new TLine(0.295*pkx[1]/radius,0.295*pky[1]/radius,0.295*pkx[3]/radius,0.295*pky[3]/radius);
  line[0]->SetLineColor(2);
  line[0]->SetLineWidth(3);
  line[0]->Draw();

  for(Float_t angle=phi_mean+45.0+stepSize/2;angle<phi_mean+362.0;angle+=45.0){
    Float_t x,y;
    x=2.0*radius*cos(PI*angle/180.0);
    y=2.0*radius*sin(PI*angle/180.0);
    line[2] = new TLine(0.295*beam[0]/radius,0.295*beam[1]/radius,
                        0.295*(beam[0]+x)/radius,0.295*(beam[1]+y)/radius);
    line[2]->SetLineColor(2);
    line[2]->Draw();
  }
   t->DrawLatex(-0.03,-0.03, "S");
   t->DrawLatex(0.295*beam[0]/radius-0.03,0.295*beam[1]/radius-0.03, "B");
   sprintf(labstring,"Scan  radius = %2.1fdeg",radius);
   t->DrawLatex(-0.7,0.590, labstring);
   sprintf(labstring,"Scan origin(S_{v}, S_{h}) =");
   t->DrawLatex(-0.7,0.530, labstring);
   sprintf(labstring,"(%-6.2f,%-6.2f) deg",voff,hoff);
   t->DrawLatex(-0.7,0.490, labstring);



  return;
 }
