Float_t v[3][6];
Float_t h[3][6];
Float_t axesx[5];
Float_t axesy[5];
Float_t phiplanex[2];
Float_t phiplaney[2];
Float_t orthplanex[2];
Float_t orthplaney[2];

TGraph *paraGraph,*perpGraph,*axes,*phiplane,*orthplane;
TCanvas *modeCanvas=NULL;
TArc *arc;
TLatex *t;
TEllipse *e;

Int_t modes[3];
Float_t Eb, Eg, cdeg,cmrad,ideg,imrad;

void drawModes(Int_t type=0, Float_t in1=12000, Float_t in2=9000, Float_t phi=0, Float_t yawoff=0, Float_t pitchoff=0, Int_t para_mode=0, Int_t perp_mode=0, Char_t *outfile="modes.png"){
  Float_t cosphi=cos(phi*0.0174532925);
  Float_t sinphi=sin(phi*0.0174532925);

  cout << "phi " << phi << "  outfile" << outfile << endl;

  modes[1]=para_mode; modes[2]=perp_mode;
  
  Int_t width=800;
  //use xwininfo to get the width from the display size (in a rather fudged way);
  //sscanf(gSystem->GetFromPipe("xwininfo -root | grep geom | awk \'{gsub(\"x\",\" \");gsub(\"+\",\" \");print $2,$3,$4,$5;exit}\'").Data(),"%d",&width);
  //width/=3;
  
  
  if(type==0){    //inputs are Eb, Eg
    Eb=in1; Eg=in2;
    cmrad=1000.0*26.5601/(2*Eb*Eb*((1/Eg)-(1/Eb))); 
    imrad=1000.0*26.5601/(2*Eb*Eb*((1/((5.0/6.0)*Eb))-(1/Eb))); 
  }
  else{           //inputs are cmrad, imrad
    cmrad=in1; imrad=in2;
  }
  cdeg=cmrad*0.057;ideg=imrad*0.057;
  
  v[1][1] =  ideg*sinphi - cdeg*cosphi + yawoff; h[1][1] = -ideg*cosphi - cdeg*sinphi + pitchoff; 
  v[1][2] =  ideg*sinphi + cdeg*cosphi + yawoff; h[1][2] = -ideg*cosphi + cdeg*sinphi + pitchoff; 
  v[1][3] = -ideg*sinphi + cdeg*cosphi + yawoff; h[1][3] =  ideg*cosphi + cdeg*sinphi + pitchoff;
  v[1][4] = -ideg*sinphi - cdeg*cosphi + yawoff; h[1][4] =  ideg*cosphi - cdeg*sinphi + pitchoff;
  v[1][5] = v[1][1]; h[1][5]=h[1][1];
  
  v[2][1] =  ideg*cosphi + cdeg*sinphi + yawoff; h[2][1] =  ideg*sinphi - cdeg*cosphi + pitchoff;      
  v[2][2] =  ideg*cosphi - cdeg*sinphi + yawoff; h[2][2] =  ideg*sinphi + cdeg*cosphi + pitchoff;      
  v[2][3] = -ideg*cosphi - cdeg*sinphi + yawoff; h[2][3] = -ideg*sinphi + cdeg*cosphi + pitchoff;      
  v[2][4] = -ideg*cosphi + cdeg*sinphi + yawoff; h[2][4] = -ideg*sinphi - cdeg*cosphi + pitchoff;      
  v[2][5] = v[2][1]; h[2][5]=h[2][1];
  
  axesx[0] = yawoff-1.5*ideg; axesy[0] = pitchoff;
  axesx[1] = yawoff+1.5*ideg; axesy[1] = pitchoff;
  axesx[2] = yawoff;          axesy[2] = pitchoff;
  axesx[3] = yawoff;          axesy[3] = pitchoff-1.5*ideg;          
  axesx[4] = yawoff;          axesy[4] = pitchoff+1.5*ideg;          
   
  phiplanex[0]  = -1.5*ideg*cosphi+yawoff; phiplaney[0] = -1.5*ideg*sinphi+pitchoff; 
  phiplanex[1]  =  1.5*ideg*cosphi+yawoff; phiplaney[1] =  1.5*ideg*sinphi+pitchoff; 
  orthplanex[0] =  1.5*ideg*sinphi+yawoff; orthplaney[0] = -1.5*ideg*cosphi+pitchoff; 
  orthplanex[1] = -1.5*ideg*sinphi+yawoff; orthplaney[1] =  1.5*ideg*cosphi+pitchoff; 


  if(!modeCanvas) modeCanvas = new TCanvas("modeCanvas","modeCanvas",-10,10,width,width);
  
  axes = new TGraph(5,axesx,axesy);
  axes->Draw("ALP");
  axes->GetHistogram()->SetTitle("Coherent bremsstrahlung modes;yaw (deg);pitch (deg)");
  axes->GetXaxis()->SetLabelSize(0.025);
  axes->GetYaxis()->SetLabelSize(0.025);
  axes->GetXaxis()->SetTickLength(0.01);
  axes->GetYaxis()->SetTickLength(0.01);
  width=2.4*TMath::Sqrt(ideg*ideg+cdeg+cdeg);
  axes->GetXaxis()->SetLimits(-width+yawoff,width+yawoff);  //some sort of bug in root
  axes->GetYaxis()->SetRangeUser(-width+pitchoff,width+pitchoff); //in setting limits. fudge like this. 
  
  t = new TLatex();
  t->SetTextAlign(11);
  t->SetTextSize(0.025);
  
  arc= new TArc(yawoff,pitchoff,0.57*width,0,phi);
  arc->SetFillColor(8);
  arc->SetFillStyle(3004);
  arc->Draw();
  t->DrawLatex(yawoff+0.65*width*cos(0.5*0.0175*phi),pitchoff+0.65*width*sin(0.5*0.0174*phi),"#phi_{022}");
  
  phiplane  =  new TGraph(2,phiplanex, phiplaney);
  orthplane =  new TGraph(2,orthplanex,orthplaney);
  phiplane->SetLineColor(3);
  orthplane->SetLineColor(4);
  phiplane->SetLineWidth(3);
  orthplane->SetLineWidth(3);
  
  phiplane->Draw("LP");
  orthplane->Draw("LP");
  
  e = new TEllipse();
  e->DrawEllipse(yawoff,pitchoff,0.05*ideg,0.05*ideg,0,360,90);
  
  
  paraGraph = new TGraph(5,&v[1][1],&h[1][1]);
  perpGraph = new TGraph(5,&v[2][1],&h[2][1]);
  
  paraGraph->SetLineColor(3);
  paraGraph->SetLineStyle(3);
  paraGraph->SetMarkerStyle(20);
  paraGraph->SetMarkerSize(2);
  paraGraph->SetMarkerColor(3);
  paraGraph->Draw("LPsame");
  
  perpGraph->SetLineColor(4);
  perpGraph->SetLineStyle(3);
  perpGraph->SetMarkerStyle(20);
  perpGraph->SetMarkerSize(2);
  perpGraph->SetMarkerColor(4);
  perpGraph->Draw("LPsame");
  
  

  Char_t mstring[100];
  t->SetTextAlign(22);
  for(int p=1;p<=2;p++){
    t->SetTextColor(2+p);
    for(int m=1;m<=4;m++){
      sprintf(mstring,"%d",m);
      if(modes[p]==m)strcat(mstring,"#heart");
      t->DrawLatex(1.2*(v[p][m]-yawoff)+yawoff  ,1.2*(h[p][m]-pitchoff)+pitchoff, mstring);
    }
  }
  t->SetTextAlign(12);
  t->SetTextColor(3);
  sprintf(mstring,"PARA: #phi_{022} = %2.1f^{#circ}",phi);
  t->DrawLatex(yawoff-0.9*width,pitchoff+0.9*width,mstring);
  t->SetTextColor(4);
  if(phi>=0.0)sprintf(mstring,"PERP: #phi_{02#bar{2}} = %2.1f^{#circ}",phi-90.0);
  else sprintf(mstring,"PERP: #phi_{02#bar{2}} = %2.1f^{#circ}",phi+90.0);
  t->DrawLatex(yawoff-0.9*width,pitchoff+0.8*width,mstring);
   
  t->SetTextColor(2);
  t->DrawLatex(yawoff-0.1*width,0.1*width+pitchoff,"B");
  sprintf(mstring,"Beam (B) = (yaw_off, pitch_off)   =    (%4.3f, %4.3f)",yawoff,pitchoff);
  t->DrawLatex(yawoff-0.9*width,pitchoff+0.7*width,mstring);
  
  t->SetTextColor(1);
  t->DrawLatex(yawoff-0.9*width,pitchoff-0.72*width,"For PARA and PERP respectively, solid lines show pol. plane angle");
  t->DrawLatex(yawoff-0.9*width,pitchoff-0.8*width,"Points show mode coords (current modes are indicated with #heart)");
  t->DrawLatex(yawoff-0.9*width,pitchoff-0.88*width,"[There are 4 possible modes (orientations) for each setting]");
  
  modeCanvas->SaveAs(outfile);
}
