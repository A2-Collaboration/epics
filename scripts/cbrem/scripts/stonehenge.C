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
// which sets the baseline to about 100
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




TCanvas *cLinPol;               // the canvas
Int_t xRange=352;
Int_t steps=180;
Float_t start=0;
Float_t stepSize=2;
Float_t aoff=0;
Float_t voff=0;
Float_t hoff=0;
Int_t radius=60;
Float_t vother,hother;

TH1F *slice;            // for slice
TH2F *scan;            // for slice
Float_t data[600], data2[600];      // to read the data


StoneDraw(char *filename, Int_t stype, Double_t pk0, Double_t pk1,Double_t pk2,Double_t pk3){
Float_t uL=360.0;             // limits of histograms
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
  scan = new TH2F(filename,filename,steps,lL, uL, xRange,0,(Float_t)xRange);

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
    //renorm
    //    for(int i=0;i<xRange;i++){
    //  data[i]*=100.0/data[280];
    // }
//     for(int i=0;i<xRange;i++){	// for each scaler channel
//       data2[i]=100.0;			//zero the data
//       if(fscanf(fp,"%f",&data2[i])!=1){	//read the data
// 	if((data2[i]>400.0)||(data2[i]<90.0))
// 	  data2[i]=data2[i-1];	
// 	fprintf(stdout,"data %f\n",data2[i]);
// 	j=steps;			//force out of loop in no data left
// 	break;
//       }
//       total+=data2[i];
    //    }

    //normalise to the total no of counts in the spectrum
    //to try to cope with beam instability
    //    for(int i=0;i<xRange;i++){	// for each scaler channel
    // data[i]=(100000.0/total)*data[i];
    //fprintf(stdout,"data %f\n",data[i]);
    //}
    int k=0;
    for(int i=xRange/2;i<xRange;i++){
      // fill the slice of the 2d hist
      k+=2;
      //    scan->Fill(start+j*stepSize+(0.5*stepSize),i,(data[k]+data[k+1]+data2[k]+data2[k+1])/2.0);
    scan->Fill(start+j*stepSize+(0.5*stepSize),i,(data[k]+data[k+1])/2.0);
    }

  }
  fclose(fp);		// close the file

  cLinPol = new TCanvas("cLinPol","Canvas Example",200,10,800,800); //create square canvas
  cLinPol->SetFillColor(0);
  gStyle->SetOptStat(0); //switch off the annoying statistics box
  gStyle->SetPalette(1); //Make the colours look nicer

  lL=0.0;                       //lower and upper limits for histogram
  uL=steps*stepSize;



  scan->SetMinimum(85.0);      //set some good limits for nice contours
  scan->SetMaximum(175.0);
  scan->Draw("polcont4");       // draw the histogram
  scan->GetXaxis()->SetAxisColor(0);
  scan->GetYaxis()->SetAxisColor(0);
  scan->GetXaxis()->SetLabelColor(0);
  scan->GetYaxis()->SetLabelColor(0);

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

  prad=0.295;
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
  while((phi0<=0.0)||(phi0>90.0)){      //get angle into 0-90deg range
    phi0+=90.0;
    if(phi0>=360.0)phi0-=360.0;
  }
  float phi1 = 180*atan(grad[1])/PI;
  while((phi1<=0.0)||(phi1>90.0)){      //get angle into 0-90deg range
    phi1+=90.0;
    if(phi1>=360.0)phi1-=360.0;
  }
  phi_mean=0.5*(phi0+phi1);

   t = new TLatex();
   t->SetTextFont(22);
   t->SetTextColor(1);
   t->SetTextSize(0.03);
   t->SetTextAlign(12);
   t->DrawLatex(-0.05,0.590, "#theta_{h}");
   t->DrawLatex(0.590,-0.05, "#theta_{v}");

   lab1 = new TPaveText(-0.7,-0.7,0.7,-0.6);
   lab1->SetTextFont(22);
   //   lab1->SetTextAlign(12);
   //   beam[0]+=voff;
   // beam[1]+=hoff;
   sprintf(labstring,"Beam(SB)=(SB_{v}, SB_{h})=(%6.2f,%6.2f) deg,  #phi_{0}=%6.2f deg\n",beam[0],beam[1],phi_mean);
   lab1->AddText(labstring);
   sprintf(labstring,"Beam to Crystal vector BC = -(S+SB) = (%6.2f,%6.2f) deg",-(beam[0]+voff),-(beam[1]+hoff));
   lab1->AddText(labstring);
   lab1->Draw();

   fprintf(stdout,"\n phi0 = Mean(%6.2f,%6.2f) = %6.2f\n",phi0,phi1,phi_mean);
   fprintf(stdout,"\nBeam phi0,theta_v,theta_h = %6.2f, %6.2f, %6.2f, %6.2f \n",phi_mean,phi1,beam[0],beam[1]);

   fprintf(stdout,"\nNew values for offsets:\n");
   fprintf(stdout,"yaw_off: %4.2f\npitch_off: %4.2f\naoff: %4.2f\n",
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



  float phi0 = 180*atan(grad[0])/PI;
  if(phi0<0.0) phi0+=90.0;
  float phi1 = 180*atan(grad[1])/PI;
  if(phi1<0.0) phi1+=90.0;
  phi_mean=0.5*(phi0+phi1);

  line[0] = new TLine(0.295*pkx[0]/radius,0.295*pky[0]/radius,0.295*pkx[2]/radius,0.295*pky[2]
/radius);
  line[0]->SetLineColor(2);
  line[0]->SetLineWidth(3);
  line[0]->Draw();
  line[0] = new TLine(0.295*pkx[1]/radius,0.295*pky[1]/radius,0.295*pkx[3]/radius,0.295*pky[3]
/radius);
  line[0]->SetLineColor(2);
  line[0]->SetLineWidth(3);
  line[0]->Draw();

  for(Float_t angle=phi_mean+45.0;angle<phi_mean+362.0;angle+=45.0){
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
   sprintf(labstring,"Scan  radius = %2.0fdeg",radius);
   t->DrawLatex(-0.7,0.590, labstring);
   sprintf(labstring,"Scan origin(S_{v}, S_{h}) =");
   t->DrawLatex(-0.7,0.530, labstring);
   sprintf(labstring,"(%-6.2f,%-6.2f) deg",voff,hoff);
   t->DrawLatex(-0.7,0.490, labstring);



  return;
 }
