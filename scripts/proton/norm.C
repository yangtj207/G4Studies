#include <iostream>
#include <TFile.h>
#include <TAxis.h>
#include <cmath>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TFrame.h>
using namespace std;
// convert into steradians 
const double avogadro=6.02214e23;
// Pb:
//const double rho=11.35;
//const double A = 207.217;
// C
const double rho=2.;
const double A = 12.011;
const double nevts = 10000000000;
const double thickness=1;
const double convert=A/(avogadro*rho*thickness);
double sterad(double tmin,double tmax)
{
  const double degtorad=M_PI/180.;
  double sr= 2.*M_PI*(cos(tmin*degtorad)-cos(tmax*degtorad));
  return sr;
}

void norm()
{
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1");
  TFile *_file0 = TFile::Open("../../sim/proton/B5.root");
  TH1D* hist1 = (TH1D*)_file0->Get("diff");
  //cout<<hist1->GetMean()<<endl;
  for (int i=1;i<hist1->GetNbinsX()+1;i++)
    {
      /*
      cout << i<< "  "<< hist1->GetXaxis()->GetBinLowEdge(i)
	   << "  "<< hist1->GetXaxis()->GetBinUpEdge(i)
	   <<endl;
      */
      hist1->SetBinContent(i, ((1e27*convert)/nevts)*(hist1->GetBinContent(i)/sterad(hist1->GetXaxis()->GetBinLowEdge(i),hist1->GetXaxis()->GetBinUpEdge(i))));
    }
  hist1->SetTitle("Elastic proton scattering on ^{12}C at T = 1 GeV");
  hist1->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  hist1->GetYaxis()->SetTitleOffset(1.1);
  hist1->GetXaxis()->SetTitle("#theta");
  hist1->Draw("hist c");
  gPad->SetLogy();

  double sigmaE = 0;
  for (int i = 1; i<=hist1->GetNbinsX(); ++i){
    double theta = hist1->GetBinCenter(i)*TMath::Pi()/180.;
    sigmaE += hist1->GetBinContent(i)*hist1->GetBinWidth(1)*TMath::Pi()/180.*sin(theta);
  }
  sigmaE *= 2*TMath::Pi();
  std::cout<<"Total elastic cross section "<<sigmaE<<" mb."<<std::endl;

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

  TLegend *leg = new TLegend(0.5,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->AddEntry(hist1,"Geant4 v4_10_6_p01","l");
  leg->AddEntry(gr_prl_18_1200,"Phys.Rev.Lett.18, 1200, (1967)","ple");
  leg->AddEntry(gr,"Phys.Rept.42, 89, (1978)","ple");
  leg->Draw();

  c1->Print("../../figures/proton/pC1GeVdiff.png");
  c1->Print("../../figures/proton/pC1GeVdiff.pdf");
}

