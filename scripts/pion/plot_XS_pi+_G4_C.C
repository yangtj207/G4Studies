{
  double mpi = 139.570;
  //read g4 prediction
  ifstream in;
  in.open("../../sim/pion/XS_pi+_G4_C.out");
  vector<double> g4Epi;
  vector<double> g4ElXS;
  vector<double> g4TotXS;
  vector<double> g4ReacXS;

  char line[1024];
  while(1){
    in.getline(line, 1024);
    if (!in.good()) break;
    if (line[0]=='-' || line[0] == '#' || line[4] == 'N') continue;
    double x0, x1, x2, x3, x4, x5;
    sscanf(line, "%lf %lf %lf %lf %lf", &x0, &x1, &x2, &x3, &x4);
    //cout<<x0<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<endl;
    g4Epi.push_back(x1);
    g4ElXS.push_back(x2*1e3);
    g4ReacXS.push_back(x3*1e3);
    g4TotXS.push_back(x4*1e3);
    if(x1>1000) break;
  }

  TCanvas *c1 = new TCanvas("c1","c1");



  TGraph *grg4piTotElXS = new TGraph(g4Epi.size(), &g4Epi[0], &g4TotXS[0]);
  grg4piTotElXS->SetLineColor(4);
  grg4piTotElXS->SetLineWidth(4);
  grg4piTotElXS->Draw("ac");
  grg4piTotElXS->SetTitle("#pi^{+}-C cross-section");
  grg4piTotElXS->GetXaxis()->SetTitle("KE_{#pi^{+}} (MeV)");
  grg4piTotElXS->GetYaxis()->SetTitle("#sigma (mb)");

  TGraph *grg4piElXS = new TGraph(g4Epi.size(), &g4Epi[0], &g4ElXS[0]);
  grg4piElXS->SetLineColor(2);
  grg4piElXS->SetLineWidth(4);
  grg4piElXS->Draw("c");

  TGraph *grg4piReacXS = new TGraph(g4Epi.size(), &g4Epi[0], &g4ReacXS[0]);
  grg4piReacXS->SetLineColor(3);
  grg4piReacXS->SetLineWidth(4);
  grg4piReacXS->Draw("c");
 
  // gPad->SetLogx();
  //gPad->SetLogy();

 

  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetHeader("Geant4 v4_10_6_p01");
  leg->AddEntry(grg4piTotElXS,"Total #pi^{+}C cross section","l");
  leg->AddEntry(grg4piElXS,"Elastic #pi^{+}C cross section","l");
  leg->AddEntry(grg4piReacXS,"Reaction #pi^{+}C cross section","l");
  leg->Draw();

  
  //read data Ashery
  in.close();
  in.clear();
  in.open("../../data/pion/pi_C_Ashery.dat");
  vector<double> dataEpi;
  vector<double> dataEpiep;
  vector<double> dataEpiem;
  vector<double> dataElXS;
  vector<double> dataElXSep;
  vector<double> dataElXSem;
  vector<double> dataReacXS;
  vector<double> dataReacXSep;
  vector<double> dataReacXSem;
  vector<double> dataTotXS;
  vector<double> dataTotXSep;
  vector<double> dataTotXSem;


  int nlinesS = 0;

  while(1){
    in.getline(line, 1024);
    if (!in.good()) break;
    ++nlinesS;
    if (nlinesS<=3) continue;
    //cout<<line<<endl;
    double x1, x2, x3, x4, x5, x6, x7;
    int n;
    sscanf(line, "%lf %lf %lf %lf %lf %lf %lf", &x1, &x2, &x3, &x4, &x5, &x6, &x7);
  
    double ke = x1;
    //  double ke0 = ;
    // double ke1 = sqrt(pow(x3*1e3,2) + mpi*mpi)-mpi;

    dataEpi.push_back(ke);
    // dataEpiem.push_back(ke-ke0);
    // dataEpiep.push_back(ke1-ke);
    // dataEpiem.push_back(0);
    // dataEpiep.push_back(0);
    dataElXS.push_back(x2);
    dataElXSep.push_back(x3);
    dataElXSem.push_back(x3);
    dataReacXS.push_back(x4);
    dataReacXSep.push_back(x5);
    dataReacXSem.push_back(x5);
    dataTotXS.push_back(x6);
    dataTotXSep.push_back(x7);
    dataTotXSem.push_back(x7);
  }

  TGraphAsymmErrors *grdataEl = new TGraphAsymmErrors(dataEpi.size(), &dataEpi[0], &dataElXS[0], &dataEpiem[0], &dataEpiep[0], &dataElXSem[0], &dataElXSep[0]);
  grdataEl->SetMarkerStyle(20);
  grdataEl->SetMarkerColor(2);
  grdataEl->SetMarkerSize(1);
  grdataEl->Draw("pe");

  TGraphAsymmErrors *grdataReac = new TGraphAsymmErrors(dataEpi.size(), &dataEpi[0], &dataReacXS[0], &dataEpiem[0], &dataEpiep[0], &dataReacXSem[0], &dataReacXSep[0]);
  grdataReac->SetMarkerStyle(20);
  grdataReac->SetMarkerColor(3);
  grdataReac->SetMarkerSize(1);
  grdataReac->Draw("pe");

 TGraphAsymmErrors *grdataTot = new TGraphAsymmErrors(dataEpi.size(), &dataEpi[0], &dataTotXS[0], &dataEpiem[0], &dataEpiep[0], &dataTotXSem[0], &dataTotXSep[0]);
  grdataTot->SetMarkerStyle(20);
  grdataTot->SetMarkerColor(4);
  grdataTot->SetMarkerSize(1);
  grdataTot->Draw("pe");
  TLegend *legdata = new TLegend(0.7,0.5,0.9,0.7);
  legdata->SetFillStyle(0);
  legdata->SetHeader("Ashery etal");
  legdata->AddEntry(grdataTot,"Total #pi^{+}C cross section","pe");
  legdata->AddEntry(grdataEl,"Elastic #pi^{+}C cross section","pe");
  legdata->AddEntry(grdataReac,"Reaction #pi^{+}C cross section","pe");
  legdata->Draw();
  /////////

  //read data Saunders
  in.close();
  in.clear();
  in.open("../../data/pion/pi_C_Saunders.dat");
  vector<double> dataEpiS;
  vector<double> dataEpiepS;
  vector<double> dataEpiemS;
  vector<double> dataElXSS;
  vector<double> dataElXSepS;
  vector<double> dataElXSemS;
  vector<double> dataReacXSS;
  vector<double> dataReacXSepS;
  vector<double> dataReacXSemS;
  vector<double> dataTotXSS;
  vector<double> dataTotXSepS;
  vector<double> dataTotXSemS;


  int nlines = 0;

  while(1){
    in.getline(line, 1024);
    if (!in.good()) break;
   
    ++nlines;
     if (nlines<=3) continue;
    //cout<<line<<endl;
    double x1, x2, x3, x4, x5, x6, x7;
    int n;
    sscanf(line, "%lf %lf %lf %lf %lf %lf %lf", &x1, &x2, &x3, &x4, &x5, &x6, &x7);
  
    double ke = x1;
    //  double ke0 = ;
    // double ke1 = sqrt(pow(x3*1e3,2) + mpi*mpi)-mpi;

    dataEpiS.push_back(ke);
    // dataEpiemS.push_back(ke-ke0);
    // dataEpiepS.push_back(ke1-ke);
    // dataEpiemS.push_back(0);
    // dataEpiepS.push_back(0);
    dataElXSS.push_back(x2);
    dataElXSepS.push_back(x3);
    dataElXSemS.push_back(x3);
    dataReacXSS.push_back(x4);
    dataReacXSepS.push_back(x5);
    dataReacXSemS.push_back(x5);
    dataTotXSS.push_back(x6);
    dataTotXSepS.push_back(x7);
    dataTotXSemS.push_back(x7);
  }
  // std::cout<<"data size "<<dataTotXSS.size()<<"  "<<dataEpiS[0]<<std::endl;
  TGraphAsymmErrors *grdataElS = new TGraphAsymmErrors(dataEpiS.size(), &dataEpiS[0], &dataElXSS[0], &dataEpiemS[0], &dataEpiepS[0], &dataElXSemS[0], &dataElXSepS[0]);
  grdataElS->SetMarkerStyle(24);
  grdataElS->SetMarkerColor(2);
  grdataElS->SetMarkerSize(1);
  grdataElS->Draw("pe");

  TGraphAsymmErrors *grdataReacS = new TGraphAsymmErrors(dataEpiS.size(), &dataEpiS[0], &dataReacXSS[0], &dataEpiemS[0], &dataEpiepS[0], &dataReacXSemS[0], &dataReacXSepS[0]);
  grdataReacS->SetMarkerStyle(24);
  grdataReacS->SetMarkerColor(3);
  grdataReacS->SetMarkerSize(1);
  grdataReacS->Draw("pe");

 TGraphAsymmErrors *grdataTotS = new TGraphAsymmErrors(dataEpiS.size(), &dataEpiS[0], &dataTotXSS[0], &dataEpiemS[0], &dataEpiepS[0], &dataTotXSemS[0], &dataTotXSepS[0]);
  grdataTotS->SetMarkerStyle(24);
  grdataTotS->SetMarkerColor(4);
  grdataTotS->SetMarkerSize(1);
  grdataTotS->Draw("pe");
  TLegend *legdataS = new TLegend(0.5,0.7,0.7,0.9);
  legdataS->SetFillStyle(0);
  legdataS->SetHeader("Saunders etal");
  legdataS->AddEntry(grdataTotS,"Total #pi^{+}C cross section","pe");
  legdataS->AddEntry(grdataElS,"Elastic #pi^{+}C cross section","pe");
  legdataS->AddEntry(grdataReacS,"Reaction #pi^{+}C cross section","pe");
  legdataS->Draw();





  c1->Print("../../figures/pion/pipxs_C.png");
  c1->Print("../../figures/pion/pipxs_C.pdf");

}
