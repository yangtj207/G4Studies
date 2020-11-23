{
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1");

  TFile f1_FTFP_BERT("../../sim/proton/pC_diff_FTFP_BERT.root");
  TFile f1_FTFP_BERT_TRV("../../sim/proton/pC_diff_FTFP_BERT_TRV.root");

  TH1D *diff_FTFP_BERT = (TH1D*)f1_FTFP_BERT.Get("diff");
  TH1D *diff_FTFP_BERT_TRV = (TH1D*)f1_FTFP_BERT_TRV.Get("diff");

  diff_FTFP_BERT->Draw("hist c");
  diff_FTFP_BERT_TRV->SetLineColor(3);
  diff_FTFP_BERT_TRV->Draw("hist c same");

  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();

  TFile f2("../../data/proton/HEPData-ins135538-v1-root.root");
  TGraph *gr = (TGraph*)f2.Get("Table 2/Graph1D_y1");
  gr->SetMarkerColor(2);
  gr->SetLineColor(2);
  gr->Draw("p");

  ifstream in;
  in.open("../../data/proton/p_C_PhysRevLett.18.1200.txt");
  vector<double> vx;
  vector<double> vy;
  vector<double> ve;

  char line[1024];
  while(1){
    in.getline(line, 1024);
    if (!in.good()) break;
    if (line[0]=='-' || line[0] == '#' || line[4] == 'N') continue;
    double x, y, e;
    sscanf(line, "%lf %lf %lf", &x, &y, &e);
    //cout<<x0<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<endl;
    vx.push_back(x);
    vy.push_back(y*1e3);
    ve.push_back(e*1e3);
  }

  TGraphErrors *gr_prl_18_1200 = new TGraphErrors(vx.size(), &vx[0], &vy[0], 0, &ve[0]);
  gr_prl_18_1200->SetMarkerColor(4);
  gr_prl_18_1200->SetLineColor(4);
  gr_prl_18_1200->SetLineWidth(3);
  gr_prl_18_1200->Draw("p");

  TLegend *leg = new TLegend(0.4,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->AddEntry(diff_FTFP_BERT,"Geant4 v4_10_6_p01 FTFP_BERT","l");
  leg->AddEntry(diff_FTFP_BERT_TRV,"Geant4 v4_10_6_p01 FTFP_BERT_TRV","l");
  leg->AddEntry(gr_prl_18_1200,"Phys.Rev.Lett.18, 1200, (1967)","pe");
  leg->AddEntry(gr,"Phys.Rept.42, 89, (1978)","pe");
  leg->Draw();

  c1->Print("../../figures/proton/pC1GeVdiff.png");
  c1->Print("../../figures/proton/pC1GeVdiff.pdf");
  
}
