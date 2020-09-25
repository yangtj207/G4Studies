{
  double mpi = 139.570;
  //read g4 prediction
  ifstream in;
  in.open("../../sim/pion/XS_pi+_G4_H.out");
  vector<double> g4Epi;
  vector<double> g4ElXS;
  vector<double> g4TotElXS;

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
    g4TotElXS.push_back(x4*1e3);
  }

  TCanvas *c1 = new TCanvas("c1","c1");

  TGraph *grg4piElXS = new TGraph(g4Epi.size(), &g4Epi[0], &g4ElXS[0]);
  grg4piElXS->SetLineColor(2);
  grg4piElXS->SetLineWidth(4);
  grg4piElXS->Draw("ac");
  grg4piElXS->SetTitle("");
  grg4piElXS->GetXaxis()->SetTitle("KE_{#pi^{+}} (MeV)");
  grg4piElXS->GetYaxis()->SetTitle("#sigma (mb)");
  gPad->SetLogx();
  //gPad->SetLogy();

  TGraph *grg4piTotElXS = new TGraph(g4Epi.size(), &g4Epi[0], &g4TotElXS[0]);
  grg4piTotElXS->SetLineColor(4);
  grg4piTotElXS->SetLineWidth(4);
  grg4piTotElXS->Draw("c");

  TLegend *leg = new TLegend(0.5,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetHeader("Geant4 v4_10_6_p01");
  leg->AddEntry(grg4piTotElXS,"Total #pi^{+}p cross section","l");
  leg->AddEntry(grg4piElXS,"Elastic #pi^{+}p cross section","l");
  leg->Draw();

  
  //read data 
  in.close();
  in.clear();
  in.open("../../data/pion/rpp2020-pipp_total.dat");
  vector<double> dataEpi;
  vector<double> dataEpiep;
  vector<double> dataEpiem;
  vector<double> dataElXS;
  vector<double> dataElXSep;
  vector<double> dataElXSem;

  int nlines = 0;

  while(1){
    in.getline(line, 1024);
    if (!in.good()) break;
    ++nlines;
    if (nlines<12) continue;
    //cout<<line<<endl;
    double x0, x1, x2, x3, x4, x5, x6, x7, x8;
    int n;
    sscanf(line, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &n, &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);
    //cout<<x0<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<x5<<" "<<x6<<" "<<x7<<" "<<x8<<endl;
//    if (n==297){
//      x7 = 0;
//      x8 = 0;
//    }
    double ke = sqrt(pow(x1*1e3,2) + mpi*mpi)-mpi;
    double ke0 = sqrt(pow(x2*1e3,2) + mpi*mpi)-mpi;
    double ke1 = sqrt(pow(x3*1e3,2) + mpi*mpi)-mpi;

    dataEpi.push_back(ke);
    dataEpiem.push_back(ke-ke0);
    dataEpiep.push_back(ke1-ke);
    dataElXS.push_back(x4);
    dataElXSep.push_back(sqrt(x5*x5+x7*x7));
    dataElXSem.push_back(sqrt(x6*x6+x8*x8));
  }

  TGraphAsymmErrors *grdataEl = new TGraphAsymmErrors(dataEpi.size(), &dataEpi[0], &dataElXS[0], &dataEpiem[0], &dataEpiep[0], &dataElXSem[0], &dataElXSep[0]);
  grdataEl->SetMarkerStyle(20);
  grdataEl->SetMarkerSize(0.5);
  grdataEl->Draw("pe");

  in.close();
  in.clear();
  in.open("../../data/pion/rpp2020-pipp_elastic.dat");
  vector<double> dataEpiTot;
  vector<double> dataEpiTotep;
  vector<double> dataEpiTotem;
  vector<double> dataTotXS;
  vector<double> dataTotXSep;
  vector<double> dataTotXSem;

  nlines = 0;

  while(1){
    in.getline(line, 1024);
    if (!in.good()) break;
    ++nlines;
    if (nlines<12) continue;
    //cout<<line<<endl;
    double x0, x1, x2, x3, x4, x5, x6, x7, x8;
    int n;
    sscanf(line, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &n, &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);

    double ke = sqrt(pow(x1*1e3,2) + mpi*mpi)-mpi;
    double ke0 = sqrt(pow(x2*1e3,2) + mpi*mpi)-mpi;
    double ke1 = sqrt(pow(x3*1e3,2) + mpi*mpi)-mpi;

    dataEpiTot.push_back(ke);
    dataEpiTotem.push_back(ke-ke0);
    dataEpiTotep.push_back(ke1-ke);
    dataTotXS.push_back(x4);
    dataTotXSep.push_back(sqrt(x5*x5+x7*x7));
    dataTotXSem.push_back(sqrt(x6*x6+x8*x8));
  }

  TGraphAsymmErrors *grdataTot = new TGraphAsymmErrors(dataEpiTot.size(), &dataEpiTot[0], &dataTotXS[0], &dataEpiTotem[0], &dataEpiTotep[0], &dataTotXSem[0], &dataTotXSep[0]);
  grdataTot->SetMarkerStyle(24);
  grdataTot->SetMarkerSize(0.5);
  grdataTot->Draw("pe");

  c1->Print("../../figures/pion/pipxs.png");
  c1->Print("../../figures/pion/pipxs.pdf");

}
